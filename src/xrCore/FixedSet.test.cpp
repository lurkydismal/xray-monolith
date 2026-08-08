#include "stdafx.h"

#include "FixedSet.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace
{

using Set = FixedSET<int>;

std::vector<int> g_keys;

void __fastcall CollectKey(Set::TNode* node)
{
	g_keys.push_back(node->key);
}

class FixedSetTest : public ::testing::Test
{
protected:
	Set set;

	void SetUp() override
	{
		g_keys.clear();
	}
};

} // namespace

// -----------------------------------------------------------------------------
// Basic state
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, StartsEmpty)
{
	EXPECT_EQ(set.size(), 0u);
	EXPECT_EQ(set.begin(), set.end());
}

TEST_F(FixedSetTest, FirstInsertCreatesRoot)
{
	auto* node = set.insert(42);

	ASSERT_NE(node, nullptr);

	EXPECT_EQ(node->key, 42);
	EXPECT_EQ(node->left, nullptr);
	EXPECT_EQ(node->right, nullptr);
	EXPECT_EQ(set.size(), 1u);
}

TEST_F(FixedSetTest, InsertReturnsInsertedNode)
{
	auto* node = set.insert(42);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(set.begin(), node);
}

TEST_F(FixedSetTest, InsertDuplicateReturnsExistingNode)
{
	auto* first = set.insert(42);
	auto* second = set.insert(42);

	ASSERT_NE(first, nullptr);
	ASSERT_NE(second, nullptr);

	EXPECT_EQ(first, second);
	EXPECT_EQ(set.size(), 1u);
}

// -----------------------------------------------------------------------------
// BST structure
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, InsertPlacesSmallerKeyOnLeft)
{
	auto* root = set.insert(50);
	auto* left = set.insert(25);

	ASSERT_NE(root, nullptr);
	ASSERT_NE(left, nullptr);

	EXPECT_EQ(root->left, left);
	EXPECT_EQ(root->right, nullptr);
}

TEST_F(FixedSetTest, InsertPlacesLargerKeyOnRight)
{
	auto* root = set.insert(50);
	auto* right = set.insert(75);

	ASSERT_NE(root, nullptr);
	ASSERT_NE(right, nullptr);

	EXPECT_EQ(root->left, nullptr);
	EXPECT_EQ(root->right, right);
}

TEST_F(FixedSetTest, InsertBuildsExpectedTree)
{
	auto* root = set.insert(50);
	auto* left = set.insert(25);
	auto* right = set.insert(75);
	auto* leftLeft = set.insert(10);
	auto* leftRight = set.insert(40);
	auto* rightLeft = set.insert(60);
	auto* rightRight = set.insert(90);

	ASSERT_NE(root, nullptr);
	ASSERT_NE(left, nullptr);
	ASSERT_NE(right, nullptr);
	ASSERT_NE(leftLeft, nullptr);
	ASSERT_NE(leftRight, nullptr);
	ASSERT_NE(rightLeft, nullptr);
	ASSERT_NE(rightRight, nullptr);

	EXPECT_EQ(root->left, left);
	EXPECT_EQ(root->right, right);

	EXPECT_EQ(left->left, leftLeft);
	EXPECT_EQ(left->right, leftRight);

	EXPECT_EQ(right->left, rightLeft);
	EXPECT_EQ(right->right, rightRight);

	EXPECT_EQ(leftLeft->left, nullptr);
	EXPECT_EQ(leftLeft->right, nullptr);
	EXPECT_EQ(leftRight->left, nullptr);
	EXPECT_EQ(leftRight->right, nullptr);
	EXPECT_EQ(rightLeft->left, nullptr);
	EXPECT_EQ(rightLeft->right, nullptr);
	EXPECT_EQ(rightRight->left, nullptr);
	EXPECT_EQ(rightRight->right, nullptr);
}

// -----------------------------------------------------------------------------
// find equivalent behavior through insert
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, DuplicateDoesNotIncreaseSize)
{
	set.insert(10);
	set.insert(20);
	set.insert(30);
	set.insert(20);

	EXPECT_EQ(set.size(), 3u);
}

TEST_F(FixedSetTest, MultipleUniqueKeysAreStored)
{
	const int keys[] = {50, 25, 75, 10, 40, 60, 90};

	for (int key : keys)
		set.insert(key);

	EXPECT_EQ(set.size(), 7u);

	for (int key : keys)
	{
		auto* node = set.insert(key);

		ASSERT_NE(node, nullptr);
		EXPECT_EQ(node->key, key);
	}
}

// -----------------------------------------------------------------------------
// insertInAnyWay
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, InsertInAnyWayAllowsDuplicateKeys)
{
	auto* first = set.insertInAnyWay(10);
	auto* second = set.insertInAnyWay(10);
	auto* third = set.insertInAnyWay(10);

	ASSERT_NE(first, nullptr);
	ASSERT_NE(second, nullptr);
	ASSERT_NE(third, nullptr);

	EXPECT_NE(first, second);
	EXPECT_NE(second, third);
	EXPECT_EQ(set.size(), 3u);

	EXPECT_EQ(first->key, 10);
	EXPECT_EQ(second->key, 10);
	EXPECT_EQ(third->key, 10);
}

TEST_F(FixedSetTest, InsertInAnyWayPlacesDuplicatesOnLeft)
{
	auto* first = set.insertInAnyWay(10);
	auto* second = set.insertInAnyWay(10);
	auto* third = set.insertInAnyWay(10);

	ASSERT_NE(first, nullptr);
	ASSERT_NE(second, nullptr);
	ASSERT_NE(third, nullptr);

	EXPECT_EQ(first->left, second);
	EXPECT_EQ(second->left, third);

	EXPECT_EQ(first->right, nullptr);
	EXPECT_EQ(second->right, nullptr);
	EXPECT_EQ(third->right, nullptr);
}

TEST_F(FixedSetTest, InsertInAnyWayPlacesLargerKeysOnRight)
{
	auto* root = set.insertInAnyWay(10);
	auto* right = set.insertInAnyWay(20);

	ASSERT_NE(root, nullptr);
	ASSERT_NE(right, nullptr);

	EXPECT_EQ(root->right, right);
	EXPECT_EQ(root->left, nullptr);
}

TEST_F(FixedSetTest, InsertInAnyWayMixesDuplicatesAndUniqueKeys)
{
	auto* root = set.insertInAnyWay(10);
	auto* duplicate = set.insertInAnyWay(10);
	auto* larger = set.insertInAnyWay(20);
	auto* duplicate2 = set.insertInAnyWay(10);

	ASSERT_NE(root, nullptr);
	ASSERT_NE(duplicate, nullptr);
	ASSERT_NE(larger, nullptr);
	ASSERT_NE(duplicate2, nullptr);

	EXPECT_EQ(root->left, duplicate);
	EXPECT_EQ(root->right, larger);
	EXPECT_EQ(duplicate->left, duplicate2);

	EXPECT_EQ(set.size(), 4u);
}

// -----------------------------------------------------------------------------
// Traversal
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, TraverseLRProducesSortedOrder)
{
	set.insert(50);
	set.insert(25);
	set.insert(75);
	set.insert(10);
	set.insert(40);
	set.insert(60);
	set.insert(90);

	g_keys.clear();
	set.traverseLR(&CollectKey);

	EXPECT_EQ(
		g_keys,
		(std::vector<int>{10, 25, 40, 50, 60, 75, 90})
	);
}

TEST_F(FixedSetTest, TraverseRLProducesReverseSortedOrder)
{
	set.insert(50);
	set.insert(25);
	set.insert(75);
	set.insert(10);
	set.insert(40);
	set.insert(60);
	set.insert(90);

	g_keys.clear();
	set.traverseRL(&CollectKey);

	EXPECT_EQ(
		g_keys,
		(std::vector<int>{90, 75, 60, 50, 40, 25, 10})
	);
}

TEST_F(FixedSetTest, TraverseAnyVisitsEveryNode)
{
	const int keys[] = {50, 25, 75, 10, 40, 60, 90};

	for (int key : keys)
		set.insert(key);

	g_keys.clear();
	set.traverseANY(&CollectKey);

	ASSERT_EQ(g_keys.size(), 7u);

	std::sort(g_keys.begin(), g_keys.end());

	EXPECT_EQ(
		g_keys,
		(std::vector<int>{10, 25, 40, 50, 60, 75, 90})
	);
}

TEST_F(FixedSetTest, TraverseAnyUsesPoolOrder)
{
	auto* first = set.insert(50);
	auto* second = set.insert(25);
	auto* third = set.insert(75);

	ASSERT_NE(first, nullptr);
	ASSERT_NE(second, nullptr);
	ASSERT_NE(third, nullptr);

	g_keys.clear();
	set.traverseANY(&CollectKey);

	EXPECT_EQ(
		g_keys,
		(std::vector<int>{50, 25, 75})
	);
}

// -----------------------------------------------------------------------------
// Reallocation
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, FirstAllocationContains64Nodes)
{
	set.insert(0);

	// There is no allocated() accessor, but last() exposes the end
	// of the allocated region.
	EXPECT_EQ(set.last() - set.begin(), 64);
}

TEST_F(FixedSetTest, ReallocationOccursAfter64Nodes)
{
	for (int i = 0; i < 64; ++i)
		set.insert(i);

	EXPECT_EQ(set.size(), 64u);
	EXPECT_EQ(set.last() - set.begin(), 64);

	set.insert(64);

	EXPECT_EQ(set.size(), 65u);
	EXPECT_EQ(set.last() - set.begin(), 128);
}

TEST_F(FixedSetTest, ReallocationPreservesAllNodes)
{
	for (int i = 0; i < 128; ++i)
		set.insert(i);

	EXPECT_EQ(set.size(), 128u);

	for (int i = 0; i < 128; ++i)
	{
		auto* node = set.insert(i);

		ASSERT_NE(node, nullptr);
		EXPECT_EQ(node->key, i);
	}
}

TEST_F(FixedSetTest, ReallocationPreservesTreePointers)
{
	const int keys[] = {
		64,
		32,
		96,
		16,
		48,
		80,
		112,
		8,
		24,
		40,
		56,
		72,
		88,
		104,
		120,
	};

	for (int key : keys)
		set.insert(key);

	// Force a reallocation.
	for (int key = 1000; key < 1060; ++key)
		set.insert(key);

	EXPECT_EQ(set.size(), 75u);
	EXPECT_EQ(set.last() - set.begin(), 128);

	// Verify that every existing tree link points at a node in the
	// current allocation and preserves the BST relationship.
	for (u32 i = 0; i < set.size(); ++i)
	{
		auto* node = set.begin() + i;

		ASSERT_NE(node, nullptr);

		if (node->left)
		{
			EXPECT_GE(node->left, set.begin());
			EXPECT_LT(node->left, set.begin() + set.size());
			EXPECT_LT(node->left->key, node->key);
		}

		if (node->right)
		{
			EXPECT_GE(node->right, set.begin());
			EXPECT_LT(node->right, set.begin() + set.size());
			EXPECT_GT(node->right->key, node->key);
		}
	}
}

TEST_F(FixedSetTest, LargeSetRemainsSearchableThroughInsert)
{
	for (int i = 0; i < 1000; ++i)
		set.insert(i);

	EXPECT_EQ(set.size(), 1000u);

	for (int i = 0; i < 1000; ++i)
	{
		auto* node = set.insert(i);

		ASSERT_NE(node, nullptr);
		EXPECT_EQ(node->key, i);
	}
}

// -----------------------------------------------------------------------------
// clear
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, ClearMakesSetEmpty)
{
	for (int i = 0; i < 100; ++i)
		set.insert(i);

	ASSERT_EQ(set.size(), 100u);

	set.clear();

	EXPECT_EQ(set.size(), 0u);
	EXPECT_EQ(set.begin(), set.end());
}

TEST_F(FixedSetTest, ClearKeepsAllocation)
{
	for (int i = 0; i < 100; ++i)
		set.insert(i);

	const auto allocated_before = set.last() - set.begin();

	ASSERT_EQ(allocated_before, 128);

	set.clear();

	EXPECT_EQ(set.last() - set.begin(), allocated_before);
	EXPECT_EQ(set.size(), 0u);
}

TEST_F(FixedSetTest, InsertAfterClearReusesAllocation)
{
	for (int i = 0; i < 100; ++i)
		set.insert(i);

	const auto* allocation_begin = set.begin();
	const auto allocated_before = set.last() - set.begin();

	set.clear();

	auto* node = set.insert(42);

	ASSERT_NE(node, nullptr);

	EXPECT_EQ(set.begin(), allocation_begin);
	EXPECT_EQ(set.last() - set.begin(), allocated_before);
	EXPECT_EQ(node->key, 42);
	EXPECT_EQ(set.size(), 1u);
}

// -----------------------------------------------------------------------------
// operator[]
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, SubscriptReturnsNodesByPoolIndex)
{
	auto* first = set.insert(50);
	auto* second = set.insert(25);
	auto* third = set.insert(75);

	EXPECT_EQ(&set[0], first);
	EXPECT_EQ(&set[1], second);
	EXPECT_EQ(&set[2], third);

	EXPECT_EQ(set[0].key, 50);
	EXPECT_EQ(set[1].key, 25);
	EXPECT_EQ(set[2].key, 75);
}

// -----------------------------------------------------------------------------
// begin / end
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, BeginPointsToFirstNode)
{
	auto* node = set.insert(42);

	ASSERT_NE(node, nullptr);

	EXPECT_EQ(set.begin(), node);
}

TEST_F(FixedSetTest, EndIsBeginPlusSize)
{
	set.insert(10);
	set.insert(20);
	set.insert(30);

	EXPECT_EQ(set.end(), set.begin() + set.size());
}

// -----------------------------------------------------------------------------
// for_each
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, ForEachVisitsEntireAllocatedPool)
{
	set.insert(10);
	set.insert(20);
	set.insert(30);

	g_keys.clear();
	set.for_each(&CollectKey);

	// Current implementation iterates to limit, not pool.
	EXPECT_EQ(g_keys.size(), 64u);

	EXPECT_EQ(g_keys[0], 10);
	EXPECT_EQ(g_keys[1], 20);
	EXPECT_EQ(g_keys[2], 30);

	for (size_t i = 3; i < g_keys.size(); ++i)
		EXPECT_EQ(g_keys[i], 0);
}

TEST_F(FixedSetTest, ForEachAfterReallocationVisitsEntireAllocation)
{
	for (int i = 0; i < 65; ++i)
		set.insert(i);

	g_keys.clear();
	set.for_each(&CollectKey);

	EXPECT_EQ(g_keys.size(), 128u);

	for (int i = 0; i < 65; ++i)
		EXPECT_EQ(g_keys[i], i);

	for (size_t i = 65; i < g_keys.size(); ++i)
		EXPECT_EQ(g_keys[i], 0);
}

// -----------------------------------------------------------------------------
// Duplicate stress
// -----------------------------------------------------------------------------

TEST_F(FixedSetTest, InsertInAnyWayCanStoreManyDuplicateKeys)
{
	std::vector<Set::TNode*> nodes;

	for (int i = 0; i < 100; ++i)
		nodes.push_back(set.insertInAnyWay(42));

	ASSERT_EQ(nodes.size(), 100u);
	EXPECT_EQ(set.size(), 100u);

	for (auto* node : nodes)
	{
		ASSERT_NE(node, nullptr);
		EXPECT_EQ(node->key, 42);
	}

	for (size_t i = 1; i < nodes.size(); ++i)
	{
		EXPECT_EQ(nodes[i - 1]->left, nodes[i]);
	}
}

TEST_F(FixedSetTest, InsertDoesNotCreateDuplicateAfterInsertInAnyWay)
{
	set.insertInAnyWay(42);
	set.insertInAnyWay(42);
	set.insertInAnyWay(42);

	ASSERT_EQ(set.size(), 3u);

	auto* node = set.insert(42);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(set.size(), 3u);
}
