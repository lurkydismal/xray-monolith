#include "stdafx.h"

#include "xrPool.h"

#include <gtest/gtest.h>

namespace
{

struct PoolTestObject
{
    static int constructed;
    static int destroyed;

    int value = 0;

    PoolTestObject()
    {
        ++constructed;
    }

    explicit PoolTestObject(int v) : value(v)
    {
        ++constructed;
    }

    ~PoolTestObject()
    {
        ++destroyed;
    }
};

int PoolTestObject::constructed = 0;
int PoolTestObject::destroyed = 0;

class PoolTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        PoolTestObject::constructed = 0;
        PoolTestObject::destroyed = 0;
    }
};


// -----------------------------------------------------------------------------
// Basic allocation
// -----------------------------------------------------------------------------

TEST_F(PoolTest, CreateReturnsObject)
{
    poolSS<PoolTestObject, 4> pool;

    PoolTestObject* object = pool.create();

    ASSERT_NE(object, nullptr);
    EXPECT_EQ(PoolTestObject::constructed, 1);
    EXPECT_EQ(PoolTestObject::destroyed, 0);

    pool.destroy(object);
}

TEST_F(PoolTest, CreateValueInitializesObject)
{
    poolSS<PoolTestObject, 4> pool;

    PoolTestObject* object = pool.create();

    ASSERT_NE(object, nullptr);
    EXPECT_EQ(object->value, 0);

    pool.destroy(object);
}

#if 0
TEST_F(PoolTest, CreateConstructsEachObject)
{
    poolSS<PoolTestObject, 4> pool;

    auto* a = pool.create();
    auto* b = pool.create();
    auto* c = pool.create();

    EXPECT_NE(a, nullptr);
    EXPECT_NE(b, nullptr);
    EXPECT_NE(c, nullptr);

    EXPECT_EQ(PoolTestObject::constructed, 3);
    EXPECT_EQ(PoolTestObject::destroyed, 0);

    pool.destroy(a);
    pool.destroy(b);
    pool.destroy(c);
}
#endif

#if 0
TEST_F(PoolTest, CreateReturnsDistinctObjectsWhileAlive)
{
    poolSS<PoolTestObject, 4> pool;

    auto* a = pool.create();
    auto* b = pool.create();
    auto* c = pool.create();

    EXPECT_NE(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(b, c);

    pool.destroy(a);
    pool.destroy(b);
    pool.destroy(c);
}
#endif


// -----------------------------------------------------------------------------
// Destruction
// -----------------------------------------------------------------------------

TEST_F(PoolTest, DestroyCallsDestructor)
{
    poolSS<PoolTestObject, 4> pool;

    auto* object = pool.create();

    EXPECT_EQ(PoolTestObject::constructed, 1);
    EXPECT_EQ(PoolTestObject::destroyed, 0);

    pool.destroy(object);

    EXPECT_EQ(PoolTestObject::destroyed, 1);
}

TEST_F(PoolTest, DestroySetsPointerToNull)
{
    poolSS<PoolTestObject, 4> pool;

    auto* object = pool.create();

    ASSERT_NE(object, nullptr);

    pool.destroy(object);

    EXPECT_EQ(object, nullptr);
}

TEST_F(PoolTest, DestroyCanBeReused)
{
    poolSS<PoolTestObject, 4> pool;

    auto* first = pool.create();
    ASSERT_NE(first, nullptr);

    pool.destroy(first);
    ASSERT_EQ(first, nullptr);

    auto* second = pool.create();

    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, first);

    pool.destroy(second);

    EXPECT_EQ(PoolTestObject::constructed, 2);
    EXPECT_EQ(PoolTestObject::destroyed, 2);
}

#if 0
TEST_F(PoolTest, DestroyMultipleObjectsCanBeReused)
{
    poolSS<PoolTestObject, 4> pool;

    auto* a = pool.create();
    auto* b = pool.create();
    auto* c = pool.create();

    pool.destroy(a);
    pool.destroy(b);
    pool.destroy(c);

    ASSERT_EQ(a, nullptr);
    ASSERT_EQ(b, nullptr);
    ASSERT_EQ(c, nullptr);

    auto* d = pool.create();
    auto* e = pool.create();
    auto* f = pool.create();

    EXPECT_TRUE(
        d == c || d == b || d == a
    );
    EXPECT_TRUE(
        e == c || e == b || e == a
    );
    EXPECT_TRUE(
        f == c || f == b || f == a
    );

    EXPECT_NE(d, e);
    EXPECT_NE(d, f);
    EXPECT_NE(e, f);

    pool.destroy(d);
    pool.destroy(e);
    pool.destroy(f);
}
#endif


// -----------------------------------------------------------------------------
// Pool capacity / blocks
// -----------------------------------------------------------------------------

#if 0
TEST_F(PoolTest, AllocatesExactlyOneBlockInitially)
{
    poolSS<PoolTestObject, 4> pool;

    PoolTestObject* objects[4];

    for (auto*& object : objects)
        object = pool.create();

    EXPECT_EQ(PoolTestObject::constructed, 4);

    for (auto*& object : objects)
        pool.destroy(object);
}
#endif

#if 0
TEST_F(PoolTest, AllocatesBeyondGranularity)
{
    poolSS<PoolTestObject, 4> pool;

    PoolTestObject* objects[5];

    for (auto*& object : objects)
        object = pool.create();

    EXPECT_EQ(PoolTestObject::constructed, 5);

    for (auto*& object : objects)
        pool.destroy(object);
}
#endif

#if 0
TEST_F(PoolTest, CanAllocateMultipleBlocks)
{
    constexpr int granularity = 4;
    constexpr int count = granularity * 3;

    poolSS<PoolTestObject, granularity> pool;

    PoolTestObject* objects[count];

    for (auto*& object : objects)
    {
        object = pool.create();
        ASSERT_NE(object, nullptr);
    }

    EXPECT_EQ(PoolTestObject::constructed, count);

    for (auto*& object : objects)
        pool.destroy(object);
}

TEST_F(PoolTest, AllObjectsAreDistinctAcrossBlocks)
{
    constexpr int granularity = 4;
    constexpr int count = granularity * 2;

    poolSS<PoolTestObject, granularity> pool;

    PoolTestObject* objects[count];

    for (auto*& object : objects)
        object = pool.create();

    for (int i = 0; i < count; ++i)
    {
        for (int j = i + 1; j < count; ++j)
            EXPECT_NE(objects[i], objects[j]);
    }

    for (auto*& object : objects)
        pool.destroy(object);
}
#endif


// -----------------------------------------------------------------------------
// LIFO free-list behavior
// -----------------------------------------------------------------------------

#if 0
TEST_F(PoolTest, DestroyedObjectIsFirstObjectReused)
{
    poolSS<PoolTestObject, 4> pool;

    auto* a = pool.create();
    auto* b = pool.create();

    pool.destroy(a);

    auto* c = pool.create();

    EXPECT_EQ(c, a);
    EXPECT_NE(c, b);

    pool.destroy(b);
    pool.destroy(c);
}

TEST_F(PoolTest, DestroyedObjectsAreReusedInLifoOrder)
{
    poolSS<PoolTestObject, 8> pool;

    auto* a = pool.create();
    auto* b = pool.create();
    auto* c = pool.create();

    pool.destroy(a);
    pool.destroy(b);
    pool.destroy(c);

    auto* x = pool.create();
    auto* y = pool.create();
    auto* z = pool.create();

    EXPECT_EQ(x, c);
    EXPECT_EQ(y, b);
    EXPECT_EQ(z, a);

    pool.destroy(x);
    pool.destroy(y);
    pool.destroy(z);
}
#endif


// -----------------------------------------------------------------------------
// Object state / placement-new behavior
// -----------------------------------------------------------------------------

TEST_F(PoolTest, ReusedStorageConstructsFreshObject)
{
    poolSS<PoolTestObject, 4> pool;

    auto* first = pool.create();
    first->value = 123;

    pool.destroy(first);

    auto* second = pool.create();

    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, first);

    // The constructor initializes value back to zero.
    EXPECT_EQ(second->value, 0);

    pool.destroy(second);
}

#if 0
TEST_F(PoolTest, ObjectsCanHoldIndependentState)
{
    poolSS<PoolTestObject, 4> pool;

    auto* a = pool.create();
    auto* b = pool.create();

    a->value = 10;
    b->value = 20;

    EXPECT_EQ(a->value, 10);
    EXPECT_EQ(b->value, 20);

    pool.destroy(a);
    pool.destroy(b);
}
#endif


// -----------------------------------------------------------------------------
// clear()
// -----------------------------------------------------------------------------

#if 0
TEST_F(PoolTest, ClearDestroysAllocatedStorage)
{
    poolSS<PoolTestObject, 4> pool;

    auto* a = pool.create();
    auto* b = pool.create();

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    pool.clear();

    // Important: current clear() frees storage but does NOT call destructors.
    EXPECT_EQ(PoolTestObject::destroyed, 0);
}
#endif

#if 0
TEST_F(PoolTest, ClearAllowsAllocationAgain)
{
    poolSS<PoolTestObject, 4> pool;

    auto* first = pool.create();
    ASSERT_NE(first, nullptr);

    pool.clear();

    auto* second = pool.create();

    ASSERT_NE(second, nullptr);
    EXPECT_EQ(PoolTestObject::constructed, 2);

    pool.destroy(second);
}
#endif

#if 0
TEST_F(PoolTest, ClearRemovesPreviouslyFreedObjects)
{
    poolSS<PoolTestObject, 4> pool;

    auto* first = pool.create();

    pool.destroy(first);
    ASSERT_EQ(first, nullptr);

    pool.clear();

    auto* second = pool.create();

    ASSERT_NE(second, nullptr);

    // clear() freed the old block, so the new allocation must not reuse
    // the old storage.
    EXPECT_NE(second, first);

    pool.destroy(second);
}
#endif


// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

#if 0
TEST_F(PoolTest, PoolDestructorFreesPoolStorage)
{
    {
        poolSS<PoolTestObject, 4> pool;

        auto* a = pool.create();
        auto* b = pool.create();

        ASSERT_NE(a, nullptr);
        ASSERT_NE(b, nullptr);

        EXPECT_EQ(PoolTestObject::constructed, 2);
        EXPECT_EQ(PoolTestObject::destroyed, 0);
    }

    // poolSS::~poolSS() calls xr_free(), not T::~T().
    EXPECT_EQ(PoolTestObject::destroyed, 0);
}
#endif

#if 0
TEST_F(PoolTest, PoolDestructorDoesNotDestroyLiveObjects)
{
    {
        poolSS<PoolTestObject, 4> pool;

        pool.create();
        pool.create();
        pool.create();
    }

    // This captures the current implementation's lifetime semantics.
    EXPECT_EQ(PoolTestObject::destroyed, 0);
}
#endif


// -----------------------------------------------------------------------------
// Empty pool
// -----------------------------------------------------------------------------

TEST_F(PoolTest, EmptyPoolCanBeDestroyed)
{
    {
        poolSS<PoolTestObject, 4> pool;
    }

    EXPECT_EQ(PoolTestObject::constructed, 0);
    EXPECT_EQ(PoolTestObject::destroyed, 0);
}

TEST_F(PoolTest, EmptyPoolCanBeCleared)
{
    poolSS<PoolTestObject, 4> pool;

    pool.clear();

    auto* object = pool.create();

    ASSERT_NE(object, nullptr);

    pool.destroy(object);
}


// -----------------------------------------------------------------------------
// Different granularity
// -----------------------------------------------------------------------------

TEST_F(PoolTest, GranularityOne)
{
    poolSS<PoolTestObject, 1> pool;

    auto* a = pool.create();
    ASSERT_NE(a, nullptr);

    pool.destroy(a);

    auto* b = pool.create();
    ASSERT_NE(b, nullptr);

    EXPECT_EQ(a, b);

    pool.destroy(b);
}

#if 0
TEST_F(PoolTest, GranularityTwo)
{
    poolSS<PoolTestObject, 2> pool;

    auto* a = pool.create();
    auto* b = pool.create();

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    EXPECT_NE(a, b);

    pool.destroy(a);
    pool.destroy(b);

    auto* c = pool.create();
    auto* d = pool.create();

    EXPECT_EQ(c, b);
    EXPECT_EQ(d, a);

    pool.destroy(c);
    pool.destroy(d);
}
#endif


// -----------------------------------------------------------------------------
// Non-trivial object
// -----------------------------------------------------------------------------

struct PoolStringObject
{
    xr_string value;

    PoolStringObject() : value("constructed")
    {
    }

    ~PoolStringObject()
    {
    }
};

TEST(XrPool, NonTrivialObjectWorks)
{
    poolSS<PoolStringObject, 4> pool;

    auto* object = pool.create();

    ASSERT_NE(object, nullptr);
    EXPECT_EQ(object->value, "constructed");

    object->value = "changed";

    EXPECT_EQ(object->value, "changed");

    pool.destroy(object);

    EXPECT_EQ(object, nullptr);
}

TEST(XrPool, NonTrivialObjectIsReconstructed)
{
    poolSS<PoolStringObject, 4> pool;

    auto* first = pool.create();
    first->value = "old";

    pool.destroy(first);

    auto* second = pool.create();

    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, first);
    EXPECT_EQ(second->value, "constructed");

    pool.destroy(second);
}

} // namespace
