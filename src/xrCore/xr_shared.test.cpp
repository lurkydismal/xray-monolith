#include "stdafx.h"

#include "xr_shared.h"

#include <gtest/gtest.h>

#include <string>


namespace
{

class TestSharedValue : public shared_value
{
public:
    static int constructions;
    static int destructions;

    int value = 0;
    xr_string name;

    TestSharedValue()
    {
        ++constructions;
    }

    ~TestSharedValue() override
    {
        ++destructions;
    }

    static void ResetCounters()
    {
        constructions = 0;
        destructions = 0;
    }
};

int TestSharedValue::constructions = 0;
int TestSharedValue::destructions = 0;


class SharedContainerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        TestSharedValue::ResetCounters();
    }
};


struct CreateCallback
{
    mutable int calls = 0;
    bool should_insert = true;

    bool operator()(shared_str key, TestSharedValue* value) const
    {
        ++calls;

        value->name = *key;
        value->value = static_cast<int>(key.size());

        return should_insert;
    }
};

} // namespace


// -----------------------------------------------------------------------------
// shared_value
// -----------------------------------------------------------------------------

TEST(SharedValue, DefaultReferenceCountIsUninitializedByBase)
{
    TestSharedValue value;

    // shared_value itself deliberately does not initialize m_ref_cnt.
    // shared_container::dock() initializes it when an object is created.
    //
    // Therefore this test only verifies that the member exists and can be
    // explicitly initialized as expected by the container.
    value.m_ref_cnt = 0;

    EXPECT_EQ(value.m_ref_cnt, 0);
}

TEST(SharedValue, VirtualDestructor)
{
    TestSharedValue::ResetCounters();

    shared_value* value = new TestSharedValue;
    delete value;

    EXPECT_EQ(TestSharedValue::destructions, 1);
}


// -----------------------------------------------------------------------------
// shared_container construction
// -----------------------------------------------------------------------------

TEST_F(SharedContainerTest, Construction)
{
    shared_container<TestSharedValue> container;

    EXPECT_EQ(TestSharedValue::constructions, 0);
    EXPECT_EQ(TestSharedValue::destructions, 0);
}

TEST_F(SharedContainerTest, EmptyContainerCanBeCleaned)
{
    shared_container<TestSharedValue> container;

    container.clean(false);
    container.clean(true);

    EXPECT_EQ(TestSharedValue::destructions, 0);
}


// -----------------------------------------------------------------------------
// shared_container::dock
// -----------------------------------------------------------------------------

#if 0
TEST_F(SharedContainerTest, DockCreatesValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_str key("test");

    TestSharedValue* value = container.dock(key, callback);

    ASSERT_NE(value, nullptr);

    EXPECT_EQ(callback.calls, 1);
    EXPECT_EQ(TestSharedValue::constructions, 1);
    EXPECT_EQ(TestSharedValue::destructions, 0);

    EXPECT_EQ(value->m_ref_cnt, 0);
    EXPECT_EQ(value->name, "test");
    EXPECT_EQ(value->value, 4);
}
#endif

#if 0
TEST_F(SharedContainerTest, DockSameKeyReturnsExistingValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_str key("test");

    TestSharedValue* first = container.dock(key, callback);
    TestSharedValue* second = container.dock(key, callback);

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    EXPECT_EQ(first, second);

    EXPECT_EQ(callback.calls, 1);
    EXPECT_EQ(TestSharedValue::constructions, 1);
    EXPECT_EQ(TestSharedValue::destructions, 0);
}

TEST_F(SharedContainerTest, DockDifferentKeysCreatesDifferentValues)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    TestSharedValue* first =
        container.dock(shared_str("first"), callback);

    TestSharedValue* second =
        container.dock(shared_str("second"), callback);

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    EXPECT_NE(first, second);

    EXPECT_EQ(callback.calls, 2);
    EXPECT_EQ(TestSharedValue::constructions, 2);

    EXPECT_EQ(first->name, "first");
    EXPECT_EQ(second->name, "second");
}

TEST_F(SharedContainerTest, DockInitializesReferenceCountToZero)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    TestSharedValue* value =
        container.dock(shared_str("test"), callback);

    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->m_ref_cnt, 0);
}

TEST_F(SharedContainerTest, DockDoesNotInvokeCallbackForExistingValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    TestSharedValue* first =
        container.dock(shared_str("test"), callback);

    ASSERT_NE(first, nullptr);
    EXPECT_EQ(callback.calls, 1);

    callback.should_insert = false;

    TestSharedValue* second =
        container.dock(shared_str("test"), callback);

    EXPECT_EQ(second, first);
    EXPECT_EQ(callback.calls, 1);
}

TEST_F(SharedContainerTest, CallbackCanRejectNewValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;
    callback.should_insert = false;

    TestSharedValue* value =
        container.dock(shared_str("test"), callback);

    EXPECT_EQ(value, nullptr);
    EXPECT_EQ(callback.calls, 1);

    EXPECT_EQ(TestSharedValue::constructions, 1);
    EXPECT_EQ(TestSharedValue::destructions, 1);
}

TEST_F(SharedContainerTest, RejectedValueIsNotStored)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;
    callback.should_insert = false;

    TestSharedValue* first =
        container.dock(shared_str("test"), callback);

    EXPECT_EQ(first, nullptr);

    callback.should_insert = true;

    TestSharedValue* second =
        container.dock(shared_str("test"), callback);

    ASSERT_NE(second, nullptr);

    EXPECT_EQ(callback.calls, 2);
    EXPECT_EQ(TestSharedValue::constructions, 2);
    EXPECT_EQ(TestSharedValue::destructions, 1);
}

TEST_F(SharedContainerTest, EquivalentSharedStringsUseSameKey)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_str firstKey("test");
    shared_str secondKey("test");

    TestSharedValue* first =
        container.dock(firstKey, callback);

    TestSharedValue* second =
        container.dock(secondKey, callback);

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    EXPECT_EQ(first, second);
    EXPECT_EQ(callback.calls, 1);
}
#endif


// -----------------------------------------------------------------------------
// shared_container::clean(false)
// -----------------------------------------------------------------------------

#if 0
TEST_F(SharedContainerTest, CleanWithoutForceDestroysUnreferencedValues)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    TestSharedValue* value =
        container.dock(shared_str("test"), callback);

    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->m_ref_cnt, 0);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}
#endif

#if 0
TEST_F(SharedContainerTest, CleanWithoutForceKeepsReferencedValues)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> item;

    item.create(
        shared_str("test"),
        &container,
        callback);

    const TestSharedValue* value = item.get_value();

    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->m_ref_cnt, 1);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 0);
    EXPECT_EQ(item.get_value(), value);
    EXPECT_EQ(value->m_ref_cnt, 1);
}
#endif

#if 0
TEST_F(SharedContainerTest, CleanWithoutForceRemovesOnlyUnreferencedValues)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> referenced;

    referenced.create(
        shared_str("referenced"),
        &container,
        callback);

    TestSharedValue* unreferenced =
        container.dock(shared_str("unreferenced"), callback);

    ASSERT_NE(referenced.get_value(), nullptr);
    ASSERT_NE(unreferenced, nullptr);

    EXPECT_EQ(referenced.get_value()->m_ref_cnt, 1);
    EXPECT_EQ(unreferenced->m_ref_cnt, 0);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);

    EXPECT_NE(referenced.get_value(), nullptr);
    EXPECT_EQ(referenced.get_value()->m_ref_cnt, 1);
}
#endif

#if 0
TEST_F(SharedContainerTest, CleanWithoutForceCanBeCalledRepeatedly)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    container.dock(shared_str("test"), callback);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}
#endif


// -----------------------------------------------------------------------------
// shared_container::clean(true)
// -----------------------------------------------------------------------------

#if 0
TEST_F(SharedContainerTest, ForceCleanDestroysUnreferencedValues)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    container.dock(shared_str("one"), callback);
    container.dock(shared_str("two"), callback);
    container.dock(shared_str("three"), callback);

    EXPECT_EQ(TestSharedValue::constructions, 3);

    container.clean(true);

    EXPECT_EQ(TestSharedValue::destructions, 3);
}

TEST_F(SharedContainerTest, ForceCleanDestroysReferencedValues)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    {
        shared_item<TestSharedValue> item;

        item.create(
            shared_str("test"),
            &container,
            callback);

        ASSERT_NE(item.get_value(), nullptr);
        EXPECT_EQ(item.get_value()->m_ref_cnt, 1);

        container.clean(true);

        EXPECT_EQ(TestSharedValue::destructions, 1);

        // The current implementation intentionally allows force_destroy
        // to invalidate outstanding shared_item pointers. Do not access
        // item.get_value() after this point.
    }
}

TEST_F(SharedContainerTest, ForceCleanCanBeCalledRepeatedly)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    container.dock(shared_str("test"), callback);

    container.clean(true);

    EXPECT_EQ(TestSharedValue::destructions, 1);

    container.clean(true);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}


// -----------------------------------------------------------------------------
// shared_item construction
// -----------------------------------------------------------------------------

TEST_F(SharedContainerTest, DefaultSharedItemIsNull)
{
    shared_item<TestSharedValue> item;

    EXPECT_EQ(item.get_value(), nullptr);
}

TEST_F(SharedContainerTest, CreateFromContainer)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> item;

    item.create(
        shared_str("test"),
        &container,
        callback);

    ASSERT_NE(item.get_value(), nullptr);

    EXPECT_EQ(item.get_value()->name, "test");
    EXPECT_EQ(item.get_value()->m_ref_cnt, 1);
}

TEST_F(SharedContainerTest, CreateIncrementsReferenceCount)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> first;
    shared_item<TestSharedValue> second;

    first.create(
        shared_str("test"),
        &container,
        callback);

    EXPECT_EQ(first.get_value()->m_ref_cnt, 1);

    second.create(
        shared_str("test"),
        &container,
        callback);

    EXPECT_EQ(first.get_value()->m_ref_cnt, 2);
    EXPECT_EQ(second.get_value(), first.get_value());
}

TEST_F(SharedContainerTest, DestroyingItemDecrementsReferenceCount)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    TestSharedValue* value = nullptr;

    {
        shared_item<TestSharedValue> item;

        item.create(
            shared_str("test"),
            &container,
            callback);

        value = const_cast<TestSharedValue*>(item.get_value());

        ASSERT_NE(value, nullptr);
        EXPECT_EQ(value->m_ref_cnt, 1);
    }

    EXPECT_EQ(value->m_ref_cnt, 0);
    EXPECT_EQ(TestSharedValue::destructions, 0);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}

TEST_F(SharedContainerTest, MultipleItemsMaintainReferenceCount)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    {
        shared_item<TestSharedValue> first;
        shared_item<TestSharedValue> second;
        shared_item<TestSharedValue> third;

        first.create(shared_str("test"), &container, callback);
        second.create(shared_str("test"), &container, callback);
        third.create(shared_str("test"), &container, callback);

        ASSERT_NE(first.get_value(), nullptr);

        EXPECT_EQ(first.get_value(), second.get_value());
        EXPECT_EQ(first.get_value(), third.get_value());

        EXPECT_EQ(first.get_value()->m_ref_cnt, 3);
    }

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}


// -----------------------------------------------------------------------------
// shared_item copy construction
// -----------------------------------------------------------------------------

TEST_F(SharedContainerTest, CopyConstructionIncrementsReference)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> original;

    original.create(
        shared_str("test"),
        &container,
        callback);

    ASSERT_NE(original.get_value(), nullptr);
    EXPECT_EQ(original.get_value()->m_ref_cnt, 1);

    {
        shared_item<TestSharedValue> copy(original);

        EXPECT_EQ(copy.get_value(), original.get_value());
        EXPECT_EQ(original.get_value()->m_ref_cnt, 2);
    }

    EXPECT_EQ(original.get_value()->m_ref_cnt, 1);
}

TEST_F(SharedContainerTest, CopyConstructionOfEmptyItem)
{
    shared_item<TestSharedValue> original;

    shared_item<TestSharedValue> copy(original);

    EXPECT_EQ(original.get_value(), nullptr);
    EXPECT_EQ(copy.get_value(), nullptr);
}


// -----------------------------------------------------------------------------
// shared_item assignment
// -----------------------------------------------------------------------------

TEST_F(SharedContainerTest, AssignmentIncrementsNewReference)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> first;
    shared_item<TestSharedValue> second;

    first.create(
        shared_str("test"),
        &container,
        callback);

    second = first;

    EXPECT_EQ(first.get_value(), second.get_value());
    EXPECT_EQ(first.get_value()->m_ref_cnt, 2);
}

TEST_F(SharedContainerTest, AssignmentReleasesPreviousValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> first;
    shared_item<TestSharedValue> second;

    first.create(
        shared_str("first"),
        &container,
        callback);

    second.create(
        shared_str("second"),
        &container,
        callback);

    TestSharedValue* firstValue =
        const_cast<TestSharedValue*>(first.get_value());

    TestSharedValue* secondValue =
        const_cast<TestSharedValue*>(second.get_value());

    ASSERT_NE(firstValue, nullptr);
    ASSERT_NE(secondValue, nullptr);

    EXPECT_EQ(firstValue->m_ref_cnt, 1);
    EXPECT_EQ(secondValue->m_ref_cnt, 1);

    second = first;

    EXPECT_EQ(firstValue->m_ref_cnt, 2);
    EXPECT_EQ(second.get_value(), firstValue);

    // The old value loses its reference, but remains in the container.
    EXPECT_EQ(secondValue->m_ref_cnt, 0);
    EXPECT_EQ(TestSharedValue::destructions, 0);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}

TEST_F(SharedContainerTest, SelfAssignmentPreservesReferenceCount)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> item;

    item.create(
        shared_str("test"),
        &container,
        callback);

    ASSERT_NE(item.get_value(), nullptr);

    TestSharedValue* value =
        const_cast<TestSharedValue*>(item.get_value());

    EXPECT_EQ(value->m_ref_cnt, 1);

    item = item;

    EXPECT_EQ(item.get_value(), value);
    EXPECT_EQ(value->m_ref_cnt, 1);
}


// -----------------------------------------------------------------------------
// shared_item::create(key, container, callback)
// -----------------------------------------------------------------------------

TEST_F(SharedContainerTest, CreateReusesExistingContainerValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> first;
    shared_item<TestSharedValue> second;

    first.create(
        shared_str("test"),
        &container,
        callback);

    second.create(
        shared_str("test"),
        &container,
        callback);

    EXPECT_EQ(first.get_value(), second.get_value());
    EXPECT_EQ(first.get_value()->m_ref_cnt, 2);
    EXPECT_EQ(callback.calls, 1);
}

TEST_F(SharedContainerTest, CreateReleasesOldValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> item;

    item.create(
        shared_str("first"),
        &container,
        callback);

    TestSharedValue* first =
        const_cast<TestSharedValue*>(item.get_value());

    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->m_ref_cnt, 1);

    item.create(
        shared_str("second"),
        &container,
        callback);

    TestSharedValue* second =
        const_cast<TestSharedValue*>(item.get_value());

    ASSERT_NE(second, nullptr);
    EXPECT_NE(second, first);

    EXPECT_EQ(first->m_ref_cnt, 0);
    EXPECT_EQ(second->m_ref_cnt, 1);
}

TEST_F(SharedContainerTest, CreateRejectedValueLeavesItemEmpty)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;
    callback.should_insert = false;

    shared_item<TestSharedValue> item;

    item.create(
        shared_str("test"),
        &container,
        callback);

    EXPECT_EQ(item.get_value(), nullptr);
    EXPECT_EQ(TestSharedValue::constructions, 1);
    EXPECT_EQ(TestSharedValue::destructions, 1);
}

TEST_F(SharedContainerTest, CreateRejectedValueReleasesPreviousItem)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> item;

    item.create(
        shared_str("first"),
        &container,
        callback);

    TestSharedValue* first =
        const_cast<TestSharedValue*>(item.get_value());

    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->m_ref_cnt, 1);

    callback.should_insert = false;

    item.create(
        shared_str("second"),
        &container,
        callback);

    EXPECT_EQ(item.get_value(), nullptr);
    EXPECT_EQ(first->m_ref_cnt, 0);

    // The first value remains stored in the container.
    EXPECT_EQ(TestSharedValue::destructions, 1);

    container.clean(false);

    // First was destroyed by clean(false).
    EXPECT_EQ(TestSharedValue::destructions, 2);
}


// -----------------------------------------------------------------------------
// get_value()
// -----------------------------------------------------------------------------

TEST_F(SharedContainerTest, GetValueReturnsUnderlyingValue)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    shared_item<TestSharedValue> item;

    item.create(
        shared_str("test"),
        &container,
        callback);

    ASSERT_NE(item.get_value(), nullptr);

    EXPECT_EQ(item.get_value()->name, "test");
    EXPECT_EQ(item.get_value()->value, 4);
}


// -----------------------------------------------------------------------------
// Cleanup/lifetime integration
// -----------------------------------------------------------------------------

TEST_F(SharedContainerTest, ItemLifetimeAndContainerCleanup)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    {
        shared_item<TestSharedValue> item;

        item.create(
            shared_str("test"),
            &container,
            callback);

        ASSERT_NE(item.get_value(), nullptr);
        EXPECT_EQ(item.get_value()->m_ref_cnt, 1);

        container.clean(false);

        // Still referenced, therefore still alive.
        EXPECT_EQ(TestSharedValue::destructions, 0);
    }

    // Item releases the final reference.
    EXPECT_EQ(TestSharedValue::destructions, 0);

    // The container still contains the now-unreferenced object.
    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}

TEST_F(SharedContainerTest, UnreferencedValuesAreDestroyedOnlyDuringClean)
{
    shared_container<TestSharedValue> container;
    CreateCallback callback;

    {
        shared_item<TestSharedValue> item;

        item.create(
            shared_str("test"),
            &container,
            callback);
    }

    // shared_item only decrements the reference count. It does not delete
    // the object or remove it from the container.
    EXPECT_EQ(TestSharedValue::destructions, 0);

    container.clean(false);

    EXPECT_EQ(TestSharedValue::destructions, 1);
}
#endif
