#include "stdafx.h"

#include "PPMdType.h"
#include "SubAlloc.hpp"

#include <gtest/gtest.h>

class SubAllocatorTest : public ::testing::Test
{
protected:
	void TearDown() override
	{
		StopSubAllocator();
	}
};

TEST_F(SubAllocatorTest, StartsAllocator)
{
	EXPECT_TRUE(StartSubAllocator(1));
}

TEST_F(SubAllocatorTest, CanRestartWithSameSize)
{
	ASSERT_TRUE(StartSubAllocator(1));

	// Starting with the same size is explicitly handled as a no-op.
	EXPECT_TRUE(StartSubAllocator(1));
}

TEST_F(SubAllocatorTest, CanRestartWithDifferentSize)
{
	ASSERT_TRUE(StartSubAllocator(1));

	EXPECT_TRUE(StartSubAllocator(2));
}

TEST_F(SubAllocatorTest, CanStopAllocator)
{
	ASSERT_TRUE(StartSubAllocator(1));

	StopSubAllocator();

	// StopSubAllocator() is intended to be idempotent.
	StopSubAllocator();
}

TEST_F(SubAllocatorTest, CanStartAfterStop)
{
	ASSERT_TRUE(StartSubAllocator(1));

	StopSubAllocator();

	EXPECT_TRUE(StartSubAllocator(1));
}

TEST_F(SubAllocatorTest, CanResizeAllocatorRepeatedly)
{
	ASSERT_TRUE(StartSubAllocator(1));

	for (UINT size = 2; size <= 8; ++size)
	{
		EXPECT_TRUE(StartSubAllocator(size))
			<< "Failed to allocate " << size << " MiB";
	}

	for (UINT size = 8; size >= 1; --size)
	{
		EXPECT_TRUE(StartSubAllocator(size))
			<< "Failed to allocate " << size << " MiB";

		if (size == 1)
			break;
	}
}
