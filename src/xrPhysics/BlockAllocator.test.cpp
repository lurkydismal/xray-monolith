#include "stdafx.h"

#include "BlockAllocator.h"

#include <gtest/gtest.h>

namespace
{
	struct TestValue
	{
		int value = 0;
	};

	// Small block size makes boundary conditions easy to exercise.
	using Allocator = CBlockAllocator<TestValue, 4>;
}

TEST(BlockAllocator, AddReturnsUsableStorage)
{
	Allocator allocator;

	TestValue* a = allocator.add();
	TestValue* b = allocator.add();

	ASSERT_NE(a, nullptr);
	ASSERT_NE(b, nullptr);
	EXPECT_NE(a, b);

	a->value = 10;
	b->value = 20;

	EXPECT_EQ(a->value, 10);
	EXPECT_EQ(b->value, 20);
}

TEST(BlockAllocator, AddKeepsValuesInSameBlock)
{
	Allocator allocator;

	TestValue* values[4];

	for (int i = 0; i < 4; ++i)
	{
		values[i] = allocator.add();
		values[i]->value = i + 1;
	}

	for (int i = 0; i < 4; ++i)
	{
		ASSERT_NE(values[i], nullptr);
		EXPECT_EQ(values[i]->value, i + 1);
	}

	// The first four allocations should belong to the same block.
	EXPECT_EQ(values[1], values[0] + 1);
	EXPECT_EQ(values[2], values[0] + 2);
	EXPECT_EQ(values[3], values[0] + 3);
}

TEST(BlockAllocator, AddCrossesBlockBoundary)
{
	Allocator allocator;

	TestValue* first_block[4];

	for (int i = 0; i < 4; ++i)
	{
		first_block[i] = allocator.add();
		first_block[i]->value = i;
	}

	TestValue* first_of_second_block = allocator.add();
	first_of_second_block->value = 4;

	ASSERT_NE(first_of_second_block, nullptr);

	// A new block must have been allocated.
	EXPECT_NE(first_of_second_block, first_block[0]);

	// The first element of the new block must not overlap
	// any element of the previous block.
	for (int i = 0; i < 4; ++i)
		EXPECT_NE(first_of_second_block, first_block[i]);

	// Existing values must remain intact.
	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(first_block[i]->value, i);

	EXPECT_EQ(first_of_second_block->value, 4);
}

TEST(BlockAllocator, AddAfterMultipleBlockBoundaries)
{
	Allocator allocator;

	constexpr int count = 20;
	TestValue* values[count];

	for (int i = 0; i < count; ++i)
	{
		values[i] = allocator.add();
		values[i]->value = i;
	}

	for (int i = 0; i < count; ++i)
	{
		ASSERT_NE(values[i], nullptr);
		EXPECT_EQ(values[i]->value, i);
	}

	// Verify that consecutive elements inside each block remain
	// contiguous.
	for (int i = 0; i < count; ++i)
	{
		if ((i + 1) % 4 != 0)
			EXPECT_EQ(values[i + 1], values[i] + 1);
	}
}

TEST(BlockAllocator, EmptyAllowsAllocatorToBeReused)
{
	Allocator allocator;

	TestValue* first = allocator.add();
	first->value = 123;

	allocator.add()->value = 456;
	allocator.add()->value = 789;

	allocator.empty();

	TestValue* reused = allocator.add();

	ASSERT_NE(reused, nullptr);

	// empty() should reset allocation position to the beginning
	// of the first existing block.
	EXPECT_EQ(reused, first);

	reused->value = 42;
	EXPECT_EQ(reused->value, 42);
}

TEST(BlockAllocator, EmptyReusesExistingBlocks)
{
	Allocator allocator;

	TestValue* values[8];

	for (int i = 0; i < 8; ++i)
	{
		values[i] = allocator.add();
		values[i]->value = i;
	}

	allocator.empty();

	// The allocator should reuse the existing first block rather
	// than requiring a new allocation.
	TestValue* first = allocator.add();

	ASSERT_NE(first, nullptr);
	EXPECT_EQ(first, values[0]);
}

TEST(BlockAllocator, EmptyThenAllocatesAcrossExistingBlocks)
{
	Allocator allocator;

	TestValue* original[8];

	for (int i = 0; i < 8; ++i)
	{
		original[i] = allocator.add();
		original[i]->value = i;
	}

	allocator.empty();

	TestValue* reused[8];

	for (int i = 0; i < 8; ++i)
	{
		reused[i] = allocator.add();
		reused[i]->value = 100 + i;
	}

	for (int i = 0; i < 8; ++i)
	{
		EXPECT_EQ(reused[i], original[i]);
		EXPECT_EQ(reused[i]->value, 100 + i);
	}
}

TEST(BlockAllocator, ClearAllowsAllocatorToStartAgain)
{
	Allocator allocator;

	TestValue* old_first = allocator.add();
	old_first->value = 100;

	allocator.add()->value = 200;

	allocator.clear();

	TestValue* first = allocator.add();

	ASSERT_NE(first, nullptr);

	// Do not assert that `first != old_first`: the allocator is
	// allowed to receive the same address again from the heap.
	first->value = 300;

	EXPECT_EQ(first->value, 300);
}

TEST(BlockAllocator, ClearCanBeCalledMoreThanOnce)
{
	Allocator allocator;

	allocator.add()->value = 1;
	allocator.add()->value = 2;

	allocator.clear();
	allocator.clear();

	TestValue* value = allocator.add();

	ASSERT_NE(value, nullptr);

	value->value = 42;
	EXPECT_EQ(value->value, 42);
}

TEST(BlockAllocator, EmptyOnNewAllocatorDoesNotCrash)
{
	Allocator allocator;

	allocator.empty();

	TestValue* value = allocator.add();

	ASSERT_NE(value, nullptr);

	value->value = 42;
	EXPECT_EQ(value->value, 42);
}

TEST(BlockAllocator, ForEachVisitsOnlyAllocatedElements)
{
	Allocator allocator;

	for (int i = 0; i < 3; ++i)
		allocator.add()->value = i + 10;

	std::vector<TestValue*> visited;

	allocator.for_each(
		[&visited](TestValue* value)
		{
			visited.push_back(value);
		});

	ASSERT_EQ(visited.size(), 3u);

	EXPECT_EQ(visited[0]->value, 10);
	EXPECT_EQ(visited[1]->value, 11);
	EXPECT_EQ(visited[2]->value, 12);
}

TEST(BlockAllocator, ForEachAfterExactlyFullBlock)
{
	Allocator allocator;

	for (int i = 0; i < 4; ++i)
		allocator.add()->value = i;

	std::vector<TestValue*> visited;

	allocator.for_each(
		[&visited](TestValue* value)
		{
			visited.push_back(value);
		});

	ASSERT_EQ(visited.size(), 4u);

	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(visited[i]->value, i);
}
