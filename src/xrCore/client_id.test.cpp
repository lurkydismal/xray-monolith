#include "stdafx.h"

#include "client_id.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

TEST(ClientIDTest, DefaultConstructorInitializesToZero)
{
    const ClientID id;

    EXPECT_EQ(id.value(), 0u);
}

TEST(ClientIDTest, ConstructorStoresValue)
{
    const ClientID id(42u);

    EXPECT_EQ(id.value(), 42u);
}

TEST(ClientIDTest, ConstructorStoresZero)
{
    const ClientID id(0u);

    EXPECT_EQ(id.value(), 0u);
}

TEST(ClientIDTest, ConstructorStoresMaximumValue)
{
    const ClientID id(std::numeric_limits<u32>::max());

    EXPECT_EQ(id.value(), std::numeric_limits<u32>::max());
}

TEST(ClientIDTest, SetChangesValue)
{
    ClientID id;

    id.set(123u);

    EXPECT_EQ(id.value(), 123u);
}

TEST(ClientIDTest, SetCanChangeValueMultipleTimes)
{
    ClientID id(10u);

    id.set(20u);
    EXPECT_EQ(id.value(), 20u);

    id.set(30u);
    EXPECT_EQ(id.value(), 30u);

    id.set(0u);
    EXPECT_EQ(id.value(), 0u);
}

TEST(ClientIDTest, SetStoresMaximumValue)
{
    ClientID id;

    id.set(std::numeric_limits<u32>::max());

    EXPECT_EQ(id.value(), std::numeric_limits<u32>::max());
}

TEST(ClientIDTest, CompareReturnsTrueForEqualValue)
{
    const ClientID id(123u);

    EXPECT_TRUE(id.compare(123u));
}

TEST(ClientIDTest, CompareReturnsFalseForDifferentValue)
{
    const ClientID id(123u);

    EXPECT_FALSE(id.compare(124u));
}

TEST(ClientIDTest, CompareWorksForZero)
{
    const ClientID id;

    EXPECT_TRUE(id.compare(0u));
    EXPECT_FALSE(id.compare(1u));
}

TEST(ClientIDTest, EqualityReturnsTrueForEqualIds)
{
    const ClientID a(42u);
    const ClientID b(42u);

    EXPECT_TRUE(a == b);
}

TEST(ClientIDTest, EqualityReturnsFalseForDifferentIds)
{
    const ClientID a(42u);
    const ClientID b(43u);

    EXPECT_FALSE(a == b);
}

TEST(ClientIDTest, InequalityReturnsFalseForEqualIds)
{
    const ClientID a(42u);
    const ClientID b(42u);

    EXPECT_FALSE(a != b);
}

TEST(ClientIDTest, InequalityReturnsTrueForDifferentIds)
{
    const ClientID a(42u);
    const ClientID b(43u);

    EXPECT_TRUE(a != b);
}

TEST(ClientIDTest, EqualityIsSymmetric)
{
    const ClientID a(42u);
    const ClientID b(42u);

    EXPECT_EQ(a == b, b == a);
}

TEST(ClientIDTest, InequalityIsSymmetric)
{
    const ClientID a(42u);
    const ClientID b(43u);

    EXPECT_EQ(a != b, b != a);
}

TEST(ClientIDTest, LessThanReturnsTrueForSmallerValue)
{
    const ClientID a(10u);
    const ClientID b(20u);

    EXPECT_TRUE(a < b);
}

TEST(ClientIDTest, LessThanReturnsFalseForLargerValue)
{
    const ClientID a(20u);
    const ClientID b(10u);

    EXPECT_FALSE(a < b);
}

TEST(ClientIDTest, LessThanReturnsFalseForEqualValues)
{
    const ClientID a(10u);
    const ClientID b(10u);

    EXPECT_FALSE(a < b);
}

TEST(ClientIDTest, LessThanOrdersValuesNumerically)
{
    const ClientID zero(0u);
    const ClientID one(1u);
    const ClientID maximum(std::numeric_limits<u32>::max());

    EXPECT_TRUE(zero < one);
    EXPECT_TRUE(one < maximum);

    EXPECT_FALSE(one < zero);
    EXPECT_FALSE(maximum < one);
}

TEST(ClientIDTest, ComparisonOperatorsAreConsistent)
{
    const ClientID a(10u);
    const ClientID b(20u);

    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b < a);
}

TEST(ClientIDTest, EqualIdsAreNotLessThanEachOther)
{
    const ClientID a(123u);
    const ClientID b(123u);

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ClientIDTest, DifferentIdsHaveExactlyOneLessThanRelationship)
{
    const ClientID a(100u);
    const ClientID b(200u);

    EXPECT_NE(a == b, a < b);
    EXPECT_NE(a == b, b < a);

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ClientIDTest, CanBeUsedAsOrderedContainerKey)
{
    std::set<ClientID> ids;

    ids.insert(ClientID(30u));
    ids.insert(ClientID(10u));
    ids.insert(ClientID(20u));
    ids.insert(ClientID(20u));

    ASSERT_EQ(ids.size(), 3u);

    auto it = ids.begin();

    ASSERT_NE(it, ids.end());
    EXPECT_EQ(it->value(), 10u);

    ++it;
    ASSERT_NE(it, ids.end());
    EXPECT_EQ(it->value(), 20u);

    ++it;
    ASSERT_NE(it, ids.end());
    EXPECT_EQ(it->value(), 30u);
}

TEST(ClientIDTest, CanBeCopied)
{
    const ClientID original(123u);
    const ClientID copy = original;

    EXPECT_EQ(copy.value(), original.value());
    EXPECT_TRUE(copy == original);
}

TEST(ClientIDTest, CopyAssignmentPreservesValue)
{
    const ClientID original(123u);
    ClientID copy(456u);

    copy = original;

    EXPECT_EQ(copy.value(), 123u);
    EXPECT_TRUE(copy == original);
}

TEST(ClientIDTest, SetAfterCopyDoesNotModifyOriginal)
{
    const ClientID original(123u);
    ClientID copy = original;

    copy.set(456u);

    EXPECT_EQ(original.value(), 123u);
    EXPECT_EQ(copy.value(), 456u);
}

TEST(ClientIDTest, IsExactlyFourBytes)
{
    EXPECT_EQ(sizeof(ClientID), sizeof(u32));
}

TEST(ClientIDTest, IsStandardLayout)
{
    EXPECT_TRUE(std::is_standard_layout_v<ClientID>);
}

TEST(ClientIDTest, IsTriviallyCopyable)
{
    EXPECT_TRUE(std::is_trivially_copyable_v<ClientID>);
}
