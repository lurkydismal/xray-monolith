#include "stdafx.h"

#include "buffer_vector.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace
{

template <typename T, size_t Capacity>
struct Buffer
{
	alignas(T) std::byte storage[sizeof(T) * Capacity];

	void* data()
	{
		return storage;
	}
};

// A non-trivial type is important here. buffer_vector manually constructs and
// destroys objects, so testing only int would miss lifetime regressions.
struct LifetimeTracked
{
	static inline int alive = 0;
	static inline int constructed = 0;
	static inline int destroyed = 0;
	static inline int copied = 0;

	int value = 0;

	LifetimeTracked()
	{
		++alive;
		++constructed;
	}

	explicit LifetimeTracked(int value) : value(value)
	{
		++alive;
		++constructed;
	}

	LifetimeTracked(const LifetimeTracked& other) : value(other.value)
	{
		++alive;
		++constructed;
		++copied;
	}

	LifetimeTracked& operator=(const LifetimeTracked&) = default;

	~LifetimeTracked()
	{
		--alive;
		++destroyed;
	}

	static void reset()
	{
		alive = 0;
		constructed = 0;
		destroyed = 0;
		copied = 0;
	}
};

template <typename T>
std::vector<T> ToVector(const buffer_vector<T>& value)
{
	return {value.begin(), value.end()};
}

} // namespace

TEST(BufferVector, DefaultConstructor)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	EXPECT_TRUE(value.empty());
	EXPECT_EQ(value.size(), 0u);
	EXPECT_EQ(value.capacity(), 8u);
	EXPECT_EQ(value.max_size(), 8u);
	EXPECT_EQ(value.begin(), value.end());
}

#if 0
TEST(BufferVector, CountValueConstructor)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 4, 42);

	EXPECT_FALSE(value.empty());
	EXPECT_EQ(value.size(), 4u);
	EXPECT_EQ(value.capacity(), 8u);
	EXPECT_EQ(value.max_size(), 8u);

	for (const int element : value)
		EXPECT_EQ(element, 42);
}
#endif

TEST(BufferVector, RangeConstructor)
{
	Buffer<int, 8> buffer;
	const std::vector<int> source{1, 2, 3, 4};

	buffer_vector<int> value(
		buffer.data(),
		8,
		source.begin(),
		source.end()
	);

	EXPECT_EQ(ToVector(value), source);
}

#if 0
TEST(BufferVector, CopyConstructor)
{
	Buffer<int, 8> source_buffer;
	buffer_vector<int> source(source_buffer.data(), 8, 3, 17);

	Buffer<int, 8> destination_buffer;
	buffer_vector<int> destination(
		destination_buffer.data(),
		8,
		source
	);

	EXPECT_EQ(ToVector(destination), (std::vector<int>{17, 17, 17}));

	// The two vectors own independent storage.
	destination[0] = 99;
	EXPECT_EQ(source[0], 17);
	EXPECT_EQ(destination[0], 99);
}
#endif

#if 0
TEST(BufferVector, Assignment)
{
	Buffer<int, 8> source_buffer;
	buffer_vector<int> source(source_buffer.data(), 8);

	source.push_back(1);
	source.push_back(2);
	source.push_back(3);

	Buffer<int, 8> destination_buffer;
	buffer_vector<int> destination(destination_buffer.data(), 8, 5, 99);

	// Do not test the return value: the current implementation does not
	// return *this from operator=.
	destination = source;

	EXPECT_EQ(ToVector(destination), (std::vector<int>{1, 2, 3}));
	EXPECT_EQ(destination.size(), 3u);
	EXPECT_EQ(destination.capacity(), 8u);
}
#endif

#if 0
TEST(BufferVector, AssignRange)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 4, 99);

	const std::vector<int> source{10, 20, 30};

	value.assign(source.begin(), source.end());

	EXPECT_EQ(ToVector(value), source);
	EXPECT_EQ(value.size(), 3u);
}
#endif

#if 0
TEST(BufferVector, AssignCountAndValue)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 4, 99);

	value.assign(buffer_vector<int>::size_type{2}, 123);

	EXPECT_EQ(ToVector(value), (std::vector<int>{123, 123}));
	EXPECT_EQ(value.size(), 2u);
}
#endif

#if 0
TEST(BufferVector, Clear)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 5, 42);

	value.clear();

	EXPECT_TRUE(value.empty());
	EXPECT_EQ(value.size(), 0u);
	EXPECT_EQ(value.capacity(), 8u);

	// The buffer can be reused after clear.
	value.push_back(7);

	EXPECT_EQ(value.size(), 1u);
	EXPECT_EQ(value.front(), 7);
}
#endif

TEST(BufferVector, ResizeGrowing)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(1);
	value.push_back(2);

	value.resize(5);

	EXPECT_EQ(value.size(), 5u);
	EXPECT_EQ(value[0], 1);
	EXPECT_EQ(value[1], 2);

	// resize() default-constructs the additional objects.
	EXPECT_EQ(value[2], 0);
	EXPECT_EQ(value[3], 0);
	EXPECT_EQ(value[4], 0);
}

#if 0
TEST(BufferVector, ResizeShrinking)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 5, 42);

	value.resize(2);

	EXPECT_EQ(value.size(), 2u);
	EXPECT_EQ(value[0], 42);
	EXPECT_EQ(value[1], 42);
}
#endif

#if 0
TEST(BufferVector, ResizeToSameSize)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 3, 42);

	int* begin = value.begin();
	int* end = value.end();

	value.resize(3);

	EXPECT_EQ(value.begin(), begin);
	EXPECT_EQ(value.end(), end);
	EXPECT_EQ(value.size(), 3u);
}
#endif

#if 0
TEST(BufferVector, ReserveDoesNothing)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 2, 42);

	int* begin = value.begin();
	int* end = value.end();

	value.reserve(8);

	EXPECT_EQ(value.begin(), begin);
	EXPECT_EQ(value.end(), end);
	EXPECT_EQ(value.capacity(), 8u);
	EXPECT_EQ(value.size(), 2u);
}
#endif

TEST(BufferVector, PushBackAndPopBack)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(10);
	value.push_back(20);
	value.push_back(30);

	EXPECT_EQ(value.size(), 3u);
	EXPECT_EQ(value.back(), 30);

	value.pop_back();

	EXPECT_EQ(value.size(), 2u);
	EXPECT_EQ(value.back(), 20);

	value.pop_back();

	EXPECT_EQ(value.size(), 1u);
	EXPECT_EQ(value.front(), 10);
}

TEST(BufferVector, FrontBackAndIndexAccess)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(10);
	value.push_back(20);
	value.push_back(30);

	EXPECT_EQ(value.front(), 10);
	EXPECT_EQ(value.back(), 30);

	EXPECT_EQ(value[0], 10);
	EXPECT_EQ(value[1], 20);
	EXPECT_EQ(value[2], 30);

	EXPECT_EQ(value.at(0), 10);
	EXPECT_EQ(value.at(1), 20);
	EXPECT_EQ(value.at(2), 30);

	value[1] = 200;

	EXPECT_EQ(value.at(1), 200);
}

#if 0
TEST(BufferVector, ConstAccess)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> mutable_value(buffer.data(), 8, 3, 42);

	const buffer_vector<int>& value = mutable_value;

	EXPECT_EQ(value.front(), 42);
	EXPECT_EQ(value.back(), 42);
	EXPECT_EQ(value[0], 42);
	EXPECT_EQ(value.at(0), 42);

	static_assert(std::is_same_v<
		decltype(value.begin()),
		buffer_vector<int>::const_iterator
	>);

	static_assert(std::is_same_v<
		decltype(value.rbegin()),
		buffer_vector<int>::const_reverse_iterator
	>);
}
#endif

TEST(BufferVector, ForwardIteration)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	for (int i = 1; i <= 5; ++i)
		value.push_back(i);

	std::vector<int> result;

	for (auto it = value.begin(); it != value.end(); ++it)
		result.push_back(*it);

	EXPECT_EQ(result, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(BufferVector, ReverseIteration)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	for (int i = 1; i <= 5; ++i)
		value.push_back(i);

	std::vector<int> result;

	for (auto it = value.rbegin(); it != value.rend(); ++it)
		result.push_back(*it);

	EXPECT_EQ(result, (std::vector<int>{5, 4, 3, 2, 1}));
}

#if 0
TEST(BufferVector, InsertSingleAtBeginning)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(2);
	value.push_back(3);

	value.insert(value.begin(), buffer_vector<int>::size_type{1});

	EXPECT_EQ(ToVector(value), (std::vector<int>{1, 2, 3}));
}
#endif

#if 0
TEST(BufferVector, InsertSingleInMiddle)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(1);
	value.push_back(3);

	value.insert(value.begin() + 1, 2);

	EXPECT_EQ(ToVector(value), (std::vector<int>{1, 2, 3}));
}
#endif

#if 0
TEST(BufferVector, InsertSingleAtEnd)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(1);
	value.push_back(2);

	value.insert(value.end(), 3);

	EXPECT_EQ(ToVector(value), (std::vector<int>{1, 2, 3}));
}
#endif

#if 0
TEST(BufferVector, InsertMultipleAtBeginning)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 2, 9);

	value.insert(value.begin(), buffer_vector<int>::size_type{3}, 7);

	EXPECT_EQ(
		ToVector(value),
		(std::vector<int>{7, 7, 7, 9, 9})
	);
}
#endif

#if 0
TEST(BufferVector, InsertMultipleInMiddle)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(1);
	value.push_back(4);

	value.insert(value.begin() + 1, buffer_vector<int>::size_type{2}, 2);

	EXPECT_EQ(
		ToVector(value),
		(std::vector<int>{1, 2, 2, 4})
	);
}
#endif

#if 0
TEST(BufferVector, InsertRange)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(1);
	value.push_back(4);

	const std::vector<int> source{2, 3};

	value.insert(value.begin() + 1, source.begin(), source.end());

	EXPECT_EQ(
		ToVector(value),
		(std::vector<int>{1, 2, 3, 4})
	);
}
#endif

TEST(BufferVector, EraseSingle)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	for (int i = 1; i <= 5; ++i)
		value.push_back(i);

	value.erase(value.begin() + 2);

	EXPECT_EQ(
		ToVector(value),
		(std::vector<int>{1, 2, 4, 5})
	);
}

TEST(BufferVector, EraseRange)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	for (int i = 1; i <= 6; ++i)
		value.push_back(i);

	value.erase(value.begin() + 1, value.begin() + 4);

	EXPECT_EQ(
		ToVector(value),
		(std::vector<int>{1, 5, 6})
	);
}

#if 0
TEST(BufferVector, EraseEmptyRange)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8, 3, 42);

	value.erase(value.begin() + 1, value.begin() + 1);

	EXPECT_EQ(value.size(), 3u);
	EXPECT_EQ(ToVector(value), (std::vector<int>{42, 42, 42}));
}
#endif

TEST(BufferVector, Swap)
{
	Buffer<int, 8> left_buffer;
	buffer_vector<int> left(left_buffer.data(), 8);

	left.push_back(1);
	left.push_back(2);

	Buffer<int, 8> right_buffer;
	buffer_vector<int> right(right_buffer.data(), 8);

	right.push_back(10);
	right.push_back(20);
	right.push_back(30);

	left.swap(right);

	EXPECT_EQ(ToVector(left), (std::vector<int>{10, 20, 30}));
	EXPECT_EQ(ToVector(right), (std::vector<int>{1, 2}));

	EXPECT_EQ(left.capacity(), 8u);
	EXPECT_EQ(right.capacity(), 8u);
}

#if 0
TEST(BufferVector, NonMemberSwap)
{
	Buffer<int, 8> left_buffer;
	buffer_vector<int> left(left_buffer.data(), 8, 2, 1);

	Buffer<int, 8> right_buffer;
	buffer_vector<int> right(right_buffer.data(), 8, 3, 2);

	swap(left, right);

	EXPECT_EQ(ToVector(left), (std::vector<int>{2, 2, 2}));
	EXPECT_EQ(ToVector(right), (std::vector<int>{1, 1}));
}
#endif

TEST(BufferVector, CapacityIsFixed)
{
	Buffer<int, 16> buffer;
	buffer_vector<int> value(buffer.data(), 16);

	EXPECT_EQ(value.capacity(), 16u);
	EXPECT_EQ(value.max_size(), 16u);

	value.push_back(1);
	value.push_back(2);

	EXPECT_EQ(value.capacity(), 16u);
	EXPECT_EQ(value.max_size(), 16u);

	value.clear();

	EXPECT_EQ(value.capacity(), 16u);
	EXPECT_EQ(value.max_size(), 16u);
}

TEST(BufferVector, StorageIsUsedInPlace)
{
	Buffer<int, 8> buffer;
	buffer_vector<int> value(buffer.data(), 8);

	value.push_back(123);

	EXPECT_EQ(value.begin(), reinterpret_cast<int*>(buffer.data()));
	EXPECT_EQ(&value[0], reinterpret_cast<int*>(buffer.data()));
}

TEST(BufferVector, ObjectLifetime)
{
	LifetimeTracked::reset();

	{
		Buffer<LifetimeTracked, 8> buffer;
		buffer_vector<LifetimeTracked> value(buffer.data(), 8);

		EXPECT_EQ(LifetimeTracked::alive, 0);

		value.resize(3);

		EXPECT_EQ(value.size(), 3u);
		EXPECT_EQ(LifetimeTracked::alive, 3);

		value.resize(1);

		EXPECT_EQ(value.size(), 1u);
		EXPECT_EQ(LifetimeTracked::alive, 1);

		value.push_back(LifetimeTracked{10});

		EXPECT_EQ(value.size(), 2u);
		EXPECT_EQ(LifetimeTracked::alive, 2);

		value.pop_back();

		EXPECT_EQ(value.size(), 1u);
		EXPECT_EQ(LifetimeTracked::alive, 1);

		value.clear();

		EXPECT_TRUE(value.empty());
		EXPECT_EQ(LifetimeTracked::alive, 0);
	}

	EXPECT_EQ(LifetimeTracked::alive, 0);
	EXPECT_EQ(
		LifetimeTracked::constructed,
		LifetimeTracked::destroyed
	);
}

TEST(BufferVector, ObjectLifetimeDuringInsertAndErase)
{
	LifetimeTracked::reset();

	{
		Buffer<LifetimeTracked, 8> buffer;
		buffer_vector<LifetimeTracked> value(buffer.data(), 8);

		LifetimeTracked one(1);
		LifetimeTracked two(2);
		LifetimeTracked three(3);

		value.push_back(one);
		value.push_back(two);
		value.push_back(three);

		ASSERT_EQ(value.size(), 3u);
		ASSERT_EQ(LifetimeTracked::alive, 6);
		// 3 local objects + 3 objects in buffer_vector.

		value.insert(value.begin() + 1, one);

		EXPECT_EQ(value.size(), 4u);
		EXPECT_EQ(value[0].value, 1);
		EXPECT_EQ(value[1].value, 1);
		EXPECT_EQ(value[2].value, 2);
		EXPECT_EQ(value[3].value, 3);

		value.erase(value.begin() + 1);

		EXPECT_EQ(value.size(), 3u);
		EXPECT_EQ(value[0].value, 1);
		EXPECT_EQ(value[1].value, 2);
		EXPECT_EQ(value[2].value, 3);
	}

	EXPECT_EQ(LifetimeTracked::alive, 0);
	EXPECT_EQ(
		LifetimeTracked::constructed,
		LifetimeTracked::destroyed
	);
}
