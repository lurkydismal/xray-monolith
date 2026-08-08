#include "stdafx.h"

#include "FixedVector.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <vector>

namespace
{

using Vector = svector<int, 4>;
using ConstVector = const svector<int, 4>;

class SVectorTest : public ::testing::Test
{
protected:
	Vector vector;
};

} // namespace

// -----------------------------------------------------------------------------
// Construction
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, StartsEmpty)
{
	EXPECT_EQ(vector.size(), 0u);
	EXPECT_TRUE(vector.empty());
}

TEST_F(SVectorTest, DefaultConstructedBeginEqualsEnd)
{
	EXPECT_EQ(vector.begin(), vector.end());
}

TEST_F(SVectorTest, IteratorRangeIsEmptyInitially)
{
	EXPECT_EQ(
		std::distance(vector.begin(), vector.end()),
		0
	);
}

// -----------------------------------------------------------------------------
// push_back
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, PushBackIncreasesSize)
{
	vector.push_back(10);

	EXPECT_EQ(vector.size(), 1u);
	EXPECT_FALSE(vector.empty());
}

TEST_F(SVectorTest, PushBackStoresValue)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
	EXPECT_EQ(vector[2], 30);
}

TEST_F(SVectorTest, PushBackPreservesInsertionOrder)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);
	vector.push_back(40);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 20, 30, 40})
	);
}

TEST_F(SVectorTest, PushBackCanFillVectorToDimension)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);
	vector.push_back(40);

	EXPECT_EQ(vector.size(), 4u);
	EXPECT_EQ(vector.front(), 10);
	EXPECT_EQ(vector.back(), 40);
}

// -----------------------------------------------------------------------------
// clear
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, ClearMakesVectorEmpty)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.clear();

	EXPECT_EQ(vector.size(), 0u);
	EXPECT_TRUE(vector.empty());
	EXPECT_EQ(vector.begin(), vector.end());
}

TEST_F(SVectorTest, ClearAllowsReuse)
{
	vector.push_back(10);
	vector.push_back(20);

	vector.clear();

	vector.push_back(30);

	ASSERT_EQ(vector.size(), 1u);
	EXPECT_EQ(vector[0], 30);
}

// -----------------------------------------------------------------------------
// resize
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, ResizeChangesSize)
{
	vector.resize(3);

	EXPECT_EQ(vector.size(), 3u);
	EXPECT_FALSE(vector.empty());
}

TEST_F(SVectorTest, ResizeCanShrink)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.resize(1);

	EXPECT_EQ(vector.size(), 1u);
	EXPECT_EQ(vector[0], 10);
}

TEST_F(SVectorTest, ResizeToZeroMakesEmpty)
{
	vector.push_back(10);
	vector.push_back(20);

	vector.resize(0);

	EXPECT_EQ(vector.size(), 0u);
	EXPECT_TRUE(vector.empty());
}

// -----------------------------------------------------------------------------
// reserve
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, ReserveDoesNotChangeSize)
{
	vector.push_back(10);

	vector.reserve(4);

	EXPECT_EQ(vector.size(), 1u);
	EXPECT_EQ(vector[0], 10);
}

TEST_F(SVectorTest, ReserveDoesNotChangeElements)
{
	vector.push_back(10);
	vector.push_back(20);

	vector.reserve(100);

	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
	EXPECT_EQ(vector.size(), 2u);
}

// -----------------------------------------------------------------------------
// operator[]
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, SubscriptReadsElement)
{
	vector.push_back(10);
	vector.push_back(20);

	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
}

TEST_F(SVectorTest, SubscriptCanModifyElement)
{
	vector.push_back(10);
	vector.push_back(20);

	vector[0] = 100;
	vector[1] = 200;

	EXPECT_EQ(vector[0], 100);
	EXPECT_EQ(vector[1], 200);
}

TEST_F(SVectorTest, ConstSubscriptReadsElement)
{
	vector.push_back(10);
	vector.push_back(20);

	ConstVector& const_vector = vector;

	EXPECT_EQ(const_vector[0], 10);
	EXPECT_EQ(const_vector[1], 20);
}

TEST_F(SVectorTest, ConstSubscriptReflectsModification)
{
	vector.push_back(10);

	ConstVector& const_vector = vector;

	vector[0] = 42;

	EXPECT_EQ(const_vector[0], 42);
}

// -----------------------------------------------------------------------------
// front / back
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, FrontReturnsFirstElement)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	EXPECT_EQ(vector.front(), 10);
}

TEST_F(SVectorTest, BackReturnsLastElement)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	EXPECT_EQ(vector.back(), 30);
}

TEST_F(SVectorTest, FrontCanModifyFirstElement)
{
	vector.push_back(10);
	vector.push_back(20);

	vector.front() = 100;

	EXPECT_EQ(vector[0], 100);
}

TEST_F(SVectorTest, BackCanModifyLastElement)
{
	vector.push_back(10);
	vector.push_back(20);

	vector.back() = 200;

	EXPECT_EQ(vector[1], 200);
}

TEST_F(SVectorTest, ConstFrontReturnsFirstElement)
{
	vector.push_back(10);
	vector.push_back(20);

	ConstVector& const_vector = vector;

	EXPECT_EQ(const_vector.front(), 10);
}

TEST_F(SVectorTest, ConstBackReturnsLastElement)
{
	vector.push_back(10);
	vector.push_back(20);

	ConstVector& const_vector = vector;

	EXPECT_EQ(const_vector.back(), 20);
}

// -----------------------------------------------------------------------------
// last
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, LastReturnsElementImmediatelyAfterUsedRange)
{
	vector.push_back(10);
	vector.push_back(20);

	// Current implementation's last() returns array[count],
	// not the last populated element.
	vector.last() = 99;

	EXPECT_EQ(vector.size(), 2u);
	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
}

TEST_F(SVectorTest, LastDoesNotChangeSize)
{
	vector.push_back(10);
	vector.push_back(20);

	vector.last() = 99;

	EXPECT_EQ(vector.size(), 2u);
}

TEST_F(SVectorTest, ConstLastReturnsElementImmediatelyAfterUsedRange)
{
	vector.push_back(10);
	vector.push_back(20);

	ConstVector& const_vector = vector;

	EXPECT_EQ(&const_vector.last(), const_vector.begin() + 2);
}

// -----------------------------------------------------------------------------
// pop_back
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, PopBackDecreasesSize)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.pop_back();

	EXPECT_EQ(vector.size(), 2u);
}

TEST_F(SVectorTest, PopBackRemovesLastLogicalElement)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.pop_back();

	EXPECT_EQ(vector.back(), 20);
	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
}

TEST_F(SVectorTest, PopBackCanEmptyVector)
{
	vector.push_back(10);

	vector.pop_back();

	EXPECT_EQ(vector.size(), 0u);
	EXPECT_TRUE(vector.empty());
}

// -----------------------------------------------------------------------------
// inc
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, IncIncreasesSize)
{
	vector.push_back(10);

	vector.inc();

	EXPECT_EQ(vector.size(), 2u);
}

TEST_F(SVectorTest, IncCreatesAnUninitializedLogicalElement)
{
	vector.push_back(10);

	vector.inc();

	ASSERT_EQ(vector.size(), 2u);

	// inc() only increments count; it does not assign a value.
	// Explicitly initialize the new slot before inspecting it.
	vector[1] = 20;

	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
}

// -----------------------------------------------------------------------------
// erase by index
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, EraseRemovesElementByIndex)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.erase(1);

	EXPECT_EQ(vector.size(), 2u);
	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 30);
}

TEST_F(SVectorTest, EraseFirstElementShiftsRemainingElements)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);
	vector.push_back(40);

	vector.erase((u32)0);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{20, 30, 40})
	);
}

TEST_F(SVectorTest, EraseLastElementDecreasesSize)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.erase(2);

	EXPECT_EQ(vector.size(), 2u);
	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
}

TEST_F(SVectorTest, EraseMiddleElementShiftsTail)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);
	vector.push_back(40);

	vector.erase(1);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 30, 40})
	);
}

TEST_F(SVectorTest, EraseAllElements)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.erase((u32)0);
	vector.erase((u32)0);
	vector.erase((u32)0);

	EXPECT_EQ(vector.size(), 0u);
	EXPECT_TRUE(vector.empty());
}

// -----------------------------------------------------------------------------
// erase by iterator
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, EraseIteratorRemovesElement)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.erase(vector.begin() + 1);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 30})
	);
}

TEST_F(SVectorTest, EraseIteratorAtBeginRemovesFirstElement)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.erase(vector.begin());

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{20, 30})
	);
}

TEST_F(SVectorTest, EraseIteratorAtEndMinusOneRemovesLastElement)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	vector.erase(vector.end() - 1);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 20})
	);
}

// -----------------------------------------------------------------------------
// insert
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, InsertAtBeginning)
{
	vector.push_back(20);
	vector.push_back(30);

	int value = 10;
	vector.insert(0, value);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 20, 30})
	);
}

TEST_F(SVectorTest, InsertInMiddle)
{
	vector.push_back(10);
	vector.push_back(30);
	vector.push_back(40);

	int value = 20;
	vector.insert(1, value);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 20, 30, 40})
	);
}

TEST_F(SVectorTest, InsertBeforeLast)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(40);

	int value = 30;
	vector.insert(2, value);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 20, 30, 40})
	);
}

TEST_F(SVectorTest, InsertShiftsExistingElementsRight)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	int value = 99;
	vector.insert(1, value);

	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 99);
	EXPECT_EQ(vector[2], 20);
	EXPECT_EQ(vector[3], 30);
	EXPECT_EQ(vector.size(), 4u);
}

TEST_F(SVectorTest, InsertCopiesValue)
{
	vector.push_back(10);

	int value = 42;
	vector.insert(1, value);

	value = 100;

	EXPECT_EQ(vector[1], 42);
}

// -----------------------------------------------------------------------------
// assign
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, AssignCopiesElements)
{
	int source[] = {10, 20, 30};

	vector.assign(source, 3);

	EXPECT_EQ(vector.size(), 3u);

	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
	EXPECT_EQ(vector[2], 30);
}

TEST_F(SVectorTest, AssignReplacesExistingContents)
{
	vector.push_back(100);
	vector.push_back(200);

	int source[] = {10, 20, 30};

	vector.assign(source, 3);

	EXPECT_EQ(
		std::vector<int>(vector.begin(), vector.end()),
		(std::vector<int>{10, 20, 30})
	);
}

TEST_F(SVectorTest, AssignSetsExactCount)
{
	int source[] = {10, 20, 30, 40};

	vector.assign(source, 2);

	EXPECT_EQ(vector.size(), 2u);
	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
}

TEST_F(SVectorTest, IteratorRangeMatchesSize)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	EXPECT_EQ(
		static_cast<u32>(std::distance(vector.begin(), vector.end())),
		vector.size()
	);
}

// -----------------------------------------------------------------------------
// Range iteration
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, RangeCanBeCopiedIntoStdVector)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	std::vector<int> result(vector.begin(), vector.end());

	EXPECT_EQ(
		result,
		(std::vector<int>{10, 20, 30})
	);
}

TEST_F(SVectorTest, ConstIterationWorks)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	const Vector& const_vector = vector;

	std::vector<int> result(
		const_vector.begin(),
		const_vector.end()
	);

	EXPECT_EQ(
		result,
		(std::vector<int>{10, 20, 30})
	);
}

// -----------------------------------------------------------------------------
// equal
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, EqualReturnsTrueForTwoEmptyVectors)
{
	Vector other;

	EXPECT_TRUE(vector.equal(other));
}

TEST_F(SVectorTest, EqualReturnsTrueForIdenticalVectors)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	Vector other;

	other.push_back(10);
	other.push_back(20);
	other.push_back(30);

	EXPECT_TRUE(vector.equal(other));
}

TEST_F(SVectorTest, EqualReturnsFalseForDifferentSizes)
{
	vector.push_back(10);
	vector.push_back(20);

	Vector other;

	other.push_back(10);

	EXPECT_FALSE(vector.equal(other));
}

TEST_F(SVectorTest, EqualReturnsFalseForDifferentElements)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	Vector other;

	other.push_back(10);
	other.push_back(999);
	other.push_back(30);

	EXPECT_FALSE(vector.equal(other));
}

TEST_F(SVectorTest, EqualIsOrderSensitive)
{
	vector.push_back(10);
	vector.push_back(20);

	Vector other;

	other.push_back(20);
	other.push_back(10);

	EXPECT_FALSE(vector.equal(other));
}

TEST_F(SVectorTest, EqualIsSymmetric)
{
	vector.push_back(10);
	vector.push_back(20);

	Vector other;

	other.push_back(10);
	other.push_back(20);

	EXPECT_EQ(vector.equal(other), other.equal(vector));
}

// -----------------------------------------------------------------------------
// Iterator mutability
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, IteratorCanModifyElements)
{
	vector.push_back(10);
	vector.push_back(20);

	for (auto& value : vector)
		value *= 10;

	EXPECT_EQ(vector[0], 100);
	EXPECT_EQ(vector[1], 200);
}

// -----------------------------------------------------------------------------
// Constructor from pointer + count
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, PointerConstructorCopiesElements)
{
	int source[] = {10, 20, 30};

	Vector other(source, 3);

	EXPECT_EQ(other.size(), 3u);
	EXPECT_EQ(other[0], 10);
	EXPECT_EQ(other[1], 20);
	EXPECT_EQ(other[2], 30);
}

TEST_F(SVectorTest, PointerConstructorCreatesIndependentCopy)
{
	int source[] = {10, 20, 30};

	Vector other(source, 3);

	source[0] = 999;
	source[1] = 888;
	source[2] = 777;

	EXPECT_EQ(other[0], 10);
	EXPECT_EQ(other[1], 20);
	EXPECT_EQ(other[2], 30);
}

// -----------------------------------------------------------------------------
// Boundary behavior
// -----------------------------------------------------------------------------

TEST_F(SVectorTest, CanFillExactlyToDimension)
{
	for (int i = 0; i < 4; ++i)
		vector.push_back(i);

	EXPECT_EQ(vector.size(), 4u);

	EXPECT_EQ(vector[0], 0);
	EXPECT_EQ(vector[1], 1);
	EXPECT_EQ(vector[2], 2);
	EXPECT_EQ(vector[3], 3);
}

TEST_F(SVectorTest, ResizeToDimension)
{
	vector.resize(4);

	EXPECT_EQ(vector.size(), 4u);
}

TEST_F(SVectorTest, InsertAtLastValidIndex)
{
	vector.push_back(10);
	vector.push_back(20);
	vector.push_back(30);

	int value = 40;

	vector.insert(3, value);

	EXPECT_EQ(vector.size(), 4u);
	EXPECT_EQ(vector[0], 10);
	EXPECT_EQ(vector[1], 20);
	EXPECT_EQ(vector[2], 30);
	EXPECT_EQ(vector[3], 40);
}
