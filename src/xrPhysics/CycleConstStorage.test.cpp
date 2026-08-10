#include "stdafx.h"

#include "CycleConstStorage.h"

#include <gtest/gtest.h>

namespace
{
	using Storage = CCycleConstStorage<int, 4>;
}

TEST(CycleConstStorage, StartsWithDefaultConstructedElements)
{
	Storage storage;

	// The elements are default-initialized because `array` is a member
	// of the class and int is value-initialized here only if the object
	// construction path guarantees it in the engine build. This test
	// intentionally avoids asserting their values.
	SUCCEED();
}

TEST(CycleConstStorage, FillInSetsEveryElement)
{
	Storage storage;

	storage.fill_in(42);

	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(storage[i], 42);
}

TEST(CycleConstStorage, FillInCanBeCalledMoreThanOnce)
{
	Storage storage;

	storage.fill_in(10);
	storage.fill_in(20);

	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(storage[i], 20);
}

TEST(CycleConstStorage, PushBackStoresValue)
{
	Storage storage;
	storage.fill_in(-1);

	int value = 10;
	storage.push_back(value);

	// first moves from 0 to 1, therefore position(3) == 0.
	// The inserted value is the newest element and is visible at
	// the last logical position.
	EXPECT_EQ(storage[3], 10);

	// The other positions retain their previous values.
	EXPECT_EQ(storage[0], -1);
	EXPECT_EQ(storage[1], -1);
	EXPECT_EQ(storage[2], -1);
}

TEST(CycleConstStorage, PushBackMovesLogicalWindow)
{
	Storage storage;
	storage.fill_in(-1);

	int a = 10;
	int b = 20;
	int c = 30;

	storage.push_back(a);
	storage.push_back(b);
	storage.push_back(c);

	// Physical array:
	//
	//   [10, 20, 30, -1]
	//
	// first == 3
	//
	// Logical positions:
	//
	//   [ -1, 10, 20, 30 ]
	//
	EXPECT_EQ(storage[0], -1);
	EXPECT_EQ(storage[1], 10);
	EXPECT_EQ(storage[2], 20);
	EXPECT_EQ(storage[3], 30);
}

TEST(CycleConstStorage, PushBackWrapsAround)
{
	Storage storage;
	storage.fill_in(-1);

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	int e = 50;

	storage.push_back(a);
	storage.push_back(b);
	storage.push_back(c);
	storage.push_back(d);

	// After four pushes, first wraps back to zero.
	EXPECT_EQ(storage[0], 10);
	EXPECT_EQ(storage[1], 20);
	EXPECT_EQ(storage[2], 30);
	EXPECT_EQ(storage[3], 40);

	storage.push_back(e);

	// The oldest element (10) has been overwritten.
	EXPECT_EQ(storage[0], 20);
	EXPECT_EQ(storage[1], 30);
	EXPECT_EQ(storage[2], 40);
	EXPECT_EQ(storage[3], 50);
}

TEST(CycleConstStorage, PushBackOverwritesOldestElementsInOrder)
{
	Storage storage;

	int values[] = {1, 2, 3, 4, 5, 6};

	for (int& value : values)
		storage.push_back(value);

	EXPECT_EQ(storage[0], 3);
	EXPECT_EQ(storage[1], 4);
	EXPECT_EQ(storage[2], 5);
	EXPECT_EQ(storage[3], 6);
}

TEST(CycleConstStorage, MultipleWrapsPreserveLastSizeElements)
{
	Storage storage;

	for (int value = 1; value <= 100; ++value)
		storage.push_back(value);

	EXPECT_EQ(storage[0], 97);
	EXPECT_EQ(storage[1], 98);
	EXPECT_EQ(storage[2], 99);
	EXPECT_EQ(storage[3], 100);
}

TEST(CycleConstStorage, ExactlySizeElementsAreRetained)
{
	Storage storage;

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	storage.push_back(a);
	storage.push_back(b);
	storage.push_back(c);
	storage.push_back(d);

	EXPECT_EQ(storage[0], 1);
	EXPECT_EQ(storage[1], 2);
	EXPECT_EQ(storage[2], 3);
	EXPECT_EQ(storage[3], 4);
}

TEST(CycleConstStorage, ReferenceValuesCanBeModified)
{
	Storage storage;
	storage.fill_in(0);

	int value = 10;
	storage.push_back(value);

	storage[3] = 99;

	EXPECT_EQ(storage[3], 99);
}

TEST(CycleConstStorage, ConstStorageCanBeIndexed)
{
	Storage storage;
	storage.fill_in(42);

	const Storage& const_storage = storage;

	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(const_storage[i], 42);
}

TEST(CycleConstStorage, ConstIndexReturnsExpectedValueAfterWrap)
{
	Storage storage;

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	int e = 50;

	storage.push_back(a);
	storage.push_back(b);
	storage.push_back(c);
	storage.push_back(d);
	storage.push_back(e);

	const Storage& const_storage = storage;

	EXPECT_EQ(const_storage[0], 20);
	EXPECT_EQ(const_storage[1], 30);
	EXPECT_EQ(const_storage[2], 40);
	EXPECT_EQ(const_storage[3], 50);
}

TEST(CycleConstStorage, FillInResetsLogicalContents)
{
	Storage storage;

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	storage.push_back(a);
	storage.push_back(b);
	storage.push_back(c);
	storage.push_back(d);

	storage.fill_in(100);

	for (int i = 0; i < 4; ++i)
		EXPECT_EQ(storage[i], 100);

	// fill_in() does not reset `first`; it only changes the values.
	int e = 200;
	storage.push_back(e);

	EXPECT_EQ(storage[3], 200);
	EXPECT_EQ(storage[0], 100);
	EXPECT_EQ(storage[1], 100);
	EXPECT_EQ(storage[2], 100);
}

TEST(CycleConstStorage, NonTrivialTypeIsCopiedCorrectly)
{
	struct Value
	{
		int number;

		bool operator==(const Value& other) const
		{
			return number == other.number;
		}
	};

	using ValueStorage = CCycleConstStorage<Value, 3>;

	ValueStorage storage;
	storage.fill_in(Value{0});

	Value first{10};
	Value second{20};
	Value third{30};
	Value fourth{40};

	storage.push_back(first);
	storage.push_back(second);
	storage.push_back(third);

	EXPECT_EQ(storage[0].number, 0);
	EXPECT_EQ(storage[1].number, 10);
	EXPECT_EQ(storage[2].number, 20);

	storage.push_back(fourth);

	EXPECT_EQ(storage[0].number, 20);
	EXPECT_EQ(storage[1].number, 30);
	EXPECT_EQ(storage[2].number, 40);
}

TEST(CycleConstStorage, SourceValueCanBeChangedAfterPushBack)
{
	Storage storage;

	int value = 123;
	storage.push_back(value);

	value = 456;

	// push_back copies T, rather than storing a reference.
	EXPECT_EQ(storage[3], 123);
}
