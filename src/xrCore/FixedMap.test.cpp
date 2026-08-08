#include "stdafx.h"

#include "FixedMap.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace
{

using Map = FixedMAP<int, int>;

std::vector<int> g_traversal;

void __fastcall CollectKey(Map::TNode* node)
{
	g_traversal.push_back(node->key);
}

void __fastcall CollectValue(Map::TNode* node)
{
	g_traversal.push_back(node->val);
}

class FixedMapTest : public ::testing::Test
{
protected:
	Map map;

	void SetUp() override
	{
		g_traversal.clear();
	}
};

} // namespace

// -----------------------------------------------------------------------------
// Basic state
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, StartsEmpty)
{
	EXPECT_EQ(map.size(), 0u);
	EXPECT_EQ(map.allocated(), 0u);
}

TEST_F(FixedMapTest, FirstInsertCreatesRoot)
{
	auto* node = map.insert(42);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->key, 42);
	EXPECT_EQ(node->val, 0);
	EXPECT_EQ(map.size(), 1u);
	EXPECT_EQ(map.allocated(), 64u);
}

TEST_F(FixedMapTest, FirstInsertWithValue)
{
	auto* node = map.insert(42, 1234);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->key, 42);
	EXPECT_EQ(node->val, 1234);
	EXPECT_EQ(map.size(), 1u);
}

TEST_F(FixedMapTest, InsertReturnsExistingNodeForDuplicateKey)
{
	auto* first = map.insert(42, 100);
	auto* second = map.insert(42, 200);

	EXPECT_EQ(first, second);
	EXPECT_EQ(map.size(), 1u);

	// Current implementation updates the value through insert(k, v).
	EXPECT_EQ(second->val, 200);
}

TEST_F(FixedMapTest, FindReturnsInsertedNode)
{
	auto* inserted = map.insert(42, 123);

	ASSERT_NE(inserted, nullptr);

	auto* found = map.find(42);

	EXPECT_EQ(found, inserted);
	EXPECT_EQ(found->key, 42);
	EXPECT_EQ(found->val, 123);
}

TEST_F(FixedMapTest, FindReturnsNullForMissingKey)
{
	map.insert(10);
	map.insert(20);
	map.insert(30);

	EXPECT_EQ(map.find(5), nullptr);
	EXPECT_EQ(map.find(15), nullptr);
	EXPECT_EQ(map.find(25), nullptr);
	EXPECT_EQ(map.find(40), nullptr);
}

TEST_F(FixedMapTest, FindOnEmptyMapReturnsNull)
{
	EXPECT_EQ(map.find(123), nullptr);
}

// -----------------------------------------------------------------------------
// BST structure
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, InsertCreatesBinarySearchTree)
{
	auto* root = map.insert(50);
	auto* left = map.insert(25);
	auto* right = map.insert(75);
	auto* leftLeft = map.insert(10);
	auto* leftRight = map.insert(40);
	auto* rightLeft = map.insert(60);
	auto* rightRight = map.insert(90);

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
}

TEST_F(FixedMapTest, InsertPlacesSmallerKeysOnLeft)
{
	auto* root = map.insert(100);
	auto* node = map.insert(50);

	ASSERT_NE(root, nullptr);
	ASSERT_NE(node, nullptr);

	EXPECT_EQ(root->left, node);
	EXPECT_EQ(root->right, nullptr);
}

TEST_F(FixedMapTest, InsertPlacesLargerKeysOnRight)
{
	auto* root = map.insert(100);
	auto* node = map.insert(150);

	ASSERT_NE(root, nullptr);
	ASSERT_NE(node, nullptr);

	EXPECT_EQ(root->left, nullptr);
	EXPECT_EQ(root->right, node);
}

// -----------------------------------------------------------------------------
// Values
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, InsertWithValueStoresValue)
{
	map.insert(10, 100);
	map.insert(20, 200);
	map.insert(30, 300);

	EXPECT_EQ(map.find(10)->val, 100);
	EXPECT_EQ(map.find(20)->val, 200);
	EXPECT_EQ(map.find(30)->val, 300);
}

TEST_F(FixedMapTest, InsertDuplicateWithValueReplacesValue)
{
	auto* first = map.insert(10, 100);
	auto* second = map.insert(10, 200);

	EXPECT_EQ(first, second);
	EXPECT_EQ(map.size(), 1u);
	EXPECT_EQ(map.find(10)->val, 200);
}

TEST_F(FixedMapTest, InsertWithoutValueLeavesValueDefaultInitialized)
{
	auto* node = map.insert(10);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->val, 0);
}

// -----------------------------------------------------------------------------
// insertInAnyWay
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, InsertInAnyWayAllowsDuplicateKeys)
{
	auto* first = map.insertInAnyWay(10, 100);
	auto* second = map.insertInAnyWay(10, 200);
	auto* third = map.insertInAnyWay(10, 300);

	ASSERT_NE(first, nullptr);
	ASSERT_NE(second, nullptr);
	ASSERT_NE(third, nullptr);

	EXPECT_NE(first, second);
	EXPECT_NE(second, third);

	EXPECT_EQ(map.size(), 3u);

	EXPECT_EQ(first->key, 10);
	EXPECT_EQ(second->key, 10);
	EXPECT_EQ(third->key, 10);
}

TEST_F(FixedMapTest, InsertInAnyWayPlacesDuplicatesOnLeft)
{
	auto* first = map.insertInAnyWay(10, 100);
	auto* second = map.insertInAnyWay(10, 200);
	auto* third = map.insertInAnyWay(10, 300);

	ASSERT_NE(first, nullptr);
	ASSERT_NE(second, nullptr);
	ASSERT_NE(third, nullptr);

	EXPECT_EQ(first->left, second);
	EXPECT_EQ(second->left, third);
}

TEST_F(FixedMapTest, InsertInAnyWayWithRvalueStoresValue)
{
	const int value = 123;

	map.insertInAnyWay(42, std::move(value));

	auto* node = map.find(42);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->val, 123);
}

// -----------------------------------------------------------------------------
// Traversal
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, TraverseLRIsSorted)
{
	map.insert(50);
	map.insert(25);
	map.insert(75);
	map.insert(10);
	map.insert(40);
	map.insert(60);
	map.insert(90);

	g_traversal.clear();
	map.traverseLR(&CollectKey);

	EXPECT_EQ(
		g_traversal,
		(std::vector<int>{10, 25, 40, 50, 60, 75, 90})
	);
}

TEST_F(FixedMapTest, TraverseRLIsReverseSorted)
{
	map.insert(50);
	map.insert(25);
	map.insert(75);
	map.insert(10);
	map.insert(40);
	map.insert(60);
	map.insert(90);

	g_traversal.clear();
	map.traverseRL(&CollectKey);

	EXPECT_EQ(
		g_traversal,
		(std::vector<int>{90, 75, 60, 50, 40, 25, 10})
	);
}

TEST_F(FixedMapTest, TraverseAnyVisitsEveryNode)
{
	map.insert(50);
	map.insert(25);
	map.insert(75);
	map.insert(10);
	map.insert(40);
	map.insert(60);
	map.insert(90);

	g_traversal.clear();
	map.traverseANY(&CollectKey);

	ASSERT_EQ(g_traversal.size(), 7u);

	std::sort(g_traversal.begin(), g_traversal.end());

	EXPECT_EQ(
		g_traversal,
		(std::vector<int>{10, 25, 40, 50, 60, 75, 90})
	);
}

// -----------------------------------------------------------------------------
// getLR / getRL / getANY
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, GetLRReturnsValuesInSortedKeyOrder)
{
	map.insert(50, 500);
	map.insert(25, 250);
	map.insert(75, 750);
	map.insert(10, 100);
	map.insert(40, 400);
	map.insert(60, 600);
	map.insert(90, 900);

	xr_vector<int> values;

	map.getLR(values);

	EXPECT_EQ(
		std::vector<int>(values.begin(), values.end()),
		(std::vector<int>{100, 250, 400, 500, 600, 750, 900})
	);
}

TEST_F(FixedMapTest, GetRLReturnsValuesInReverseSortedKeyOrder)
{
	map.insert(50, 500);
	map.insert(25, 250);
	map.insert(75, 750);
	map.insert(10, 100);
	map.insert(40, 400);
	map.insert(60, 600);
	map.insert(90, 900);

	xr_vector<int> values;

	map.getRL(values);

	EXPECT_EQ(
		std::vector<int>(values.begin(), values.end()),
		(std::vector<int>{900, 750, 600, 500, 400, 250, 100})
	);
}

TEST_F(FixedMapTest, GetAnyReturnsAllValues)
{
	map.insert(50, 500);
	map.insert(25, 250);
	map.insert(75, 750);
	map.insert(10, 100);
	map.insert(40, 400);
	map.insert(60, 600);
	map.insert(90, 900);

	xr_vector<int> values;

	map.getANY(values);

	ASSERT_EQ(values.size(), 7u);

	std::vector<int> result(values.begin(), values.end());

	std::sort(result.begin(), result.end());

	EXPECT_EQ(
		result,
		(std::vector<int>{100, 250, 400, 500, 600, 750, 900})
	);
}

// -----------------------------------------------------------------------------
// Pointer traversal
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, GetLRPReturnsNodesInSortedOrder)
{
	map.insert(50);
	map.insert(25);
	map.insert(75);
	map.insert(10);
	map.insert(40);
	map.insert(60);
	map.insert(90);

	xr_vector<Map::TNode*> nodes;
	map.getLR_P(nodes);

	ASSERT_EQ(nodes.size(), 7u);

	std::vector<int> keys;

	for (auto* node : nodes)
		keys.push_back(node->key);

	EXPECT_EQ(
		keys,
		(std::vector<int>{10, 25, 40, 50, 60, 75, 90})
	);
}

TEST_F(FixedMapTest, GetRLPReturnsNodesInReverseSortedOrder)
{
	map.insert(50);
	map.insert(25);
	map.insert(75);
	map.insert(10);
	map.insert(40);
	map.insert(60);
	map.insert(90);

	xr_vector<Map::TNode*> nodes;
	map.getRL_P(nodes);

	ASSERT_EQ(nodes.size(), 7u);

	std::vector<int> keys;

	for (auto* node : nodes)
		keys.push_back(node->key);

	EXPECT_EQ(
		keys,
		(std::vector<int>{90, 75, 60, 50, 40, 25, 10})
	);
}

TEST_F(FixedMapTest, GetAnyPReturnsEveryNode)
{
	auto* n1 = map.insert(50);
	auto* n2 = map.insert(25);
	auto* n3 = map.insert(75);

	xr_vector<Map::TNode*> nodes;
	map.getANY_P(nodes);

	ASSERT_EQ(nodes.size(), 3u);

	EXPECT_NE(
		std::find(nodes.begin(), nodes.end(), n1),
		nodes.end()
	);

	EXPECT_NE(
		std::find(nodes.begin(), nodes.end(), n2),
		nodes.end()
	);

	EXPECT_NE(
		std::find(nodes.begin(), nodes.end(), n3),
		nodes.end()
	);
}

TEST_F(FixedMapTest, GetAnyVoidPReturnsEveryNode)
{
	auto* n1 = map.insert(50);
	auto* n2 = map.insert(25);
	auto* n3 = map.insert(75);

	xr_vector<void*> nodes;
	map.getANY_P(nodes);

	ASSERT_EQ(nodes.size(), 3u);

	EXPECT_NE(
		std::find(nodes.begin(), nodes.end(), static_cast<void*>(n1)),
		nodes.end()
	);

	EXPECT_NE(
		std::find(nodes.begin(), nodes.end(), static_cast<void*>(n2)),
		nodes.end()
	);

	EXPECT_NE(
		std::find(nodes.begin(), nodes.end(), static_cast<void*>(n3)),
		nodes.end()
	);
}

// -----------------------------------------------------------------------------
// Reallocation
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, AllocationGrowsInBlocksOf64)
{
	EXPECT_EQ(map.allocated(), 0u);

	for (int i = 0; i < 64; ++i)
		map.insert(i);

	EXPECT_EQ(map.size(), 64u);
	EXPECT_EQ(map.allocated(), 64u);

	map.insert(64);

	EXPECT_EQ(map.size(), 65u);
	EXPECT_EQ(map.allocated(), 128u);
}

TEST_F(FixedMapTest, ReallocationPreservesAllNodes)
{
	for (int i = 0; i < 128; ++i)
		map.insert(i, i * 10);

	EXPECT_EQ(map.size(), 128u);
	EXPECT_EQ(map.allocated(), 128u);

	for (int i = 0; i < 128; ++i)
	{
		auto* node = map.find(i);

		ASSERT_NE(node, nullptr);
		EXPECT_EQ(node->key, i);
		EXPECT_EQ(node->val, i * 10);
	}
}

TEST_F(FixedMapTest, ReallocationPreservesTreePointers)
{
	// Insert a balanced-ish tree first.
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
		map.insert(key, key);

	// Force Realloc().
	for (int key = 1000; key < 1060; ++key)
		map.insert(key, key);

	EXPECT_EQ(map.size(), 75u);
	EXPECT_EQ(map.allocated(), 128u);

	// Verify that every tree relationship still points inside the
	// current allocation and has the expected key.
	for (u32 i = 0; i < map.size(); ++i)
	{
		auto* node = map.get_node(i);

		ASSERT_NE(node, nullptr);

		if (node->left)
		{
			EXPECT_LT(node->left->key, node->key);
		}

		if (node->right)
		{
			EXPECT_GT(node->right->key, node->key);
		}
	}

	for (int key : keys)
	{
		auto* node = map.find(key);

		ASSERT_NE(node, nullptr);
		EXPECT_EQ(node->val, key);
	}
}

TEST_F(FixedMapTest, LargeMapRemainsSearchableAfterMultipleReallocations)
{
	for (int i = 0; i < 1000; ++i)
		map.insert(i, i * 2);

	ASSERT_EQ(map.size(), 1000u);
	ASSERT_EQ(map.allocated(), 1024u);

	for (int i = 0; i < 1000; ++i)
	{
		auto* node = map.find(i);

		ASSERT_NE(node, nullptr);
		EXPECT_EQ(node->key, i);
		EXPECT_EQ(node->val, i * 2);
	}
}

TEST_F(FixedMapTest, ReallocationPreservesInorderTraversal)
{
	for (int i = 0; i < 200; ++i)
		map.insert(i, i);

	xr_vector<int> values;
	map.getLR(values);

	ASSERT_EQ(values.size(), 200u);

	for (int i = 0; i < 200; ++i)
		EXPECT_EQ(values[i], i);
}

// -----------------------------------------------------------------------------
// clear / discard / destroy
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, ClearKeepsAllocation)
{
	for (int i = 0; i < 100; ++i)
		map.insert(i, i);

	ASSERT_EQ(map.size(), 100u);
	ASSERT_EQ(map.allocated(), 128u);

	map.clear();

	EXPECT_EQ(map.size(), 0u);
	EXPECT_EQ(map.allocated(), 128u);
}

TEST_F(FixedMapTest, ClearAllowsReuseOfExistingAllocation)
{
	for (int i = 0; i < 100; ++i)
		map.insert(i, i);

	map.clear();

	EXPECT_EQ(map.size(), 0u);

	auto* node = map.insert(42, 123);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->key, 42);
	EXPECT_EQ(node->val, 123);
	EXPECT_EQ(map.size(), 1u);
	EXPECT_EQ(map.allocated(), 128u);
}

TEST_F(FixedMapTest, DiscardReleasesAllocation)
{
	for (int i = 0; i < 100; ++i)
		map.insert(i, i);

	ASSERT_EQ(map.allocated(), 128u);

	map.discard();

	EXPECT_EQ(map.size(), 0u);
	EXPECT_EQ(map.allocated(), 0u);
}

TEST_F(FixedMapTest, DiscardAllowsReuse)
{
	for (int i = 0; i < 100; ++i)
		map.insert(i, i);

	map.discard();

	auto* node = map.insert(42, 123);

	ASSERT_NE(node, nullptr);

	EXPECT_EQ(node->key, 42);
	EXPECT_EQ(node->val, 123);
	EXPECT_EQ(map.size(), 1u);
	EXPECT_EQ(map.allocated(), 64u);
}

TEST_F(FixedMapTest, DestroyResetsMap)
{
	for (int i = 0; i < 100; ++i)
		map.insert(i, i);

	map.destroy();

	EXPECT_EQ(map.size(), 0u);
	EXPECT_EQ(map.allocated(), 0u);
}

TEST_F(FixedMapTest, DestroyAllowsReuse)
{
	map.insert(10, 100);
	map.insert(20, 200);

	map.destroy();

	auto* node = map.insert(30, 300);

	ASSERT_NE(node, nullptr);

	EXPECT_EQ(node->key, 30);
	EXPECT_EQ(node->val, 300);
	EXPECT_EQ(map.size(), 1u);
	EXPECT_EQ(map.allocated(), 64u);
}

// -----------------------------------------------------------------------------
// operator[]
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, SubscriptReturnsNodeByIndex)
{
	auto* n0 = map.insert(50, 500);
	auto* n1 = map.insert(25, 250);
	auto* n2 = map.insert(75, 750);

	EXPECT_EQ(&map[0], n0);
	EXPECT_EQ(&map[1], n1);
	EXPECT_EQ(&map[2], n2);

	EXPECT_EQ(map[0].key, 50);
	EXPECT_EQ(map[1].key, 25);
	EXPECT_EQ(map[2].key, 75);
}

TEST_F(FixedMapTest, SubscriptCanModifyNode)
{
	map.insert(42, 100);

	map[0].val = 999;

	EXPECT_EQ(map.find(42)->val, 999);
}

// -----------------------------------------------------------------------------
// begin / end
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, BeginPointsToFirstNode)
{
	auto* first = map.insert(42);

	EXPECT_EQ(map.begin(), first);
}

TEST_F(FixedMapTest, EndIsBeginPlusSize)
{
	map.insert(10);
	map.insert(20);
	map.insert(30);

	EXPECT_EQ(map.end(), map.begin() + map.size());
}

// -----------------------------------------------------------------------------
// Stable indices within the current allocation
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, GetIndexReturnsNodeIndex)
{
	auto* n0 = map.insert(50);
	auto* n1 = map.insert(25);
	auto* n2 = map.insert(75);

	EXPECT_EQ(map.get_index(n0), 0u);
	EXPECT_EQ(map.get_index(n1), 1u);
	EXPECT_EQ(map.get_index(n2), 2u);
}

TEST_F(FixedMapTest, GetNodeReturnsNodeForIndex)
{
	auto* n0 = map.insert(50);
	auto* n1 = map.insert(25);
	auto* n2 = map.insert(75);

	EXPECT_EQ(map.get_node(0), n0);
	EXPECT_EQ(map.get_node(1), n1);
	EXPECT_EQ(map.get_node(2), n2);
}

TEST_F(FixedMapTest, IndexRoundTripWorks)
{
	for (int i = 0; i < 100; ++i)
		map.insert(i, i);

	for (u32 i = 0; i < map.size(); ++i)
	{
		auto* node = map.get_node(i);

		EXPECT_EQ(map.get_index(node), i);
		EXPECT_EQ(node->key, static_cast<int>(i));
		EXPECT_EQ(node->val, static_cast<int>(i));
	}
}

// -----------------------------------------------------------------------------
// setup()
// -----------------------------------------------------------------------------

TEST_F(FixedMapTest, SetupVisitsEntireAllocatedPool)
{
	for (int i = 0; i < 3; ++i)
		map.insert(i, i);

	// setup() deliberately iterates to limit, not pool.
	// Therefore this captures the current API behavior.
	g_traversal.clear();
	map.setup(&CollectKey);

	EXPECT_EQ(g_traversal.size(), map.allocated());
	EXPECT_EQ(g_traversal.size(), 64u);

	EXPECT_EQ(g_traversal[0], 0);
	EXPECT_EQ(g_traversal[1], 1);
	EXPECT_EQ(g_traversal[2], 2);

	for (size_t i = 3; i < g_traversal.size(); ++i)
		EXPECT_EQ(g_traversal[i], 0);
}
