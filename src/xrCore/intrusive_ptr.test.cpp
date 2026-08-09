#include "stdafx.h"

#include "intrusive_ptr.h"

#include <gtest/gtest.h>

namespace
{

// -----------------------------------------------------------------------------
// Test objects
// -----------------------------------------------------------------------------

struct TestObject : intrusive_base
{
    static inline int destroyed = 0;

    int value = 0;

    explicit TestObject(int v = 0)
        : value(v)
    {
    }

    ~TestObject()
    {
        ++destroyed;
    }

    static void reset()
    {
        destroyed = 0;
    }
};

struct TestObjectNonAtomic : intrusive_base_nonatomic
{
    static inline int destroyed = 0;

    int value = 0;

    explicit TestObjectNonAtomic(int v = 0)
        : value(v)
    {
    }

    ~TestObjectNonAtomic()
    {
        ++destroyed;
    }

    static void reset()
    {
        destroyed = 0;
    }
};

struct TestBase : intrusive_base
{
    static inline int destroyed = 0;

    virtual ~TestBase()
    {
        ++destroyed;
    }

    static void reset()
    {
        destroyed = 0;
    }
};

struct TestDerived : TestBase
{
    static inline int destroyed = 0;

    ~TestDerived() override
    {
        ++destroyed;
    }

    static void reset()
    {
        destroyed = 0;
        TestBase::reset();
    }
};

// Used to test Deferred deletion.
struct DeferredTestObject : intrusive_base_deferred
{
    static inline int deferred_releases = 0;
    static inline int destroyed = 0;

    int value = 0;

    explicit DeferredTestObject(int v = 0)
        : value(v)
    {
    }

    ~DeferredTestObject()
    {
        ++destroyed;
    }

    void on_deferred_release()
    {
        ++deferred_releases;
    }

    static void reset()
    {
        deferred_releases = 0;
        destroyed = 0;
    }
};

// Strict objects must have a non-public destructor.
// This also verifies the intended Strict-policy usage.
struct StrictTestObject : intrusive_base_strict
{
    static inline int destroyed = 0;

    int value = 0;

    explicit StrictTestObject(int v = 0)
        : value(v)
    {
    }

    static void reset()
    {
        destroyed = 0;
    }

protected:
    ~StrictTestObject() override
    {
        ++destroyed;
    }
};

} // namespace

// =============================================================================
// ref_count_storage
// =============================================================================

TEST(IntrusivePtr, AtomicRefCountStartsAtZero)
{
    ref_count_storage<CounterPolicy::Atomic> storage;

    EXPECT_EQ(storage.intrusive_ref_count(), 0u);
}

TEST(IntrusivePtr, NonAtomicRefCountStartsAtZero)
{
    ref_count_storage<CounterPolicy::NonAtomic> storage;

    EXPECT_EQ(storage.intrusive_ref_count(), 0u);
}

TEST(IntrusivePtr, AtomicRefCountAddReturnsNewCount)
{
    ref_count_storage<CounterPolicy::Atomic> storage;

    EXPECT_EQ(storage.intrusive_ref_add(), 1u);
    EXPECT_EQ(storage.intrusive_ref_count(), 1u);

    EXPECT_EQ(storage.intrusive_ref_add(), 2u);
    EXPECT_EQ(storage.intrusive_ref_count(), 2u);

    EXPECT_EQ(storage.intrusive_ref_add(), 3u);
    EXPECT_EQ(storage.intrusive_ref_count(), 3u);
}

TEST(IntrusivePtr, NonAtomicRefCountAddReturnsNewCount)
{
    ref_count_storage<CounterPolicy::NonAtomic> storage;

    EXPECT_EQ(storage.intrusive_ref_add(), 1u);
    EXPECT_EQ(storage.intrusive_ref_count(), 1u);

    EXPECT_EQ(storage.intrusive_ref_add(), 2u);
    EXPECT_EQ(storage.intrusive_ref_count(), 2u);
}

TEST(IntrusivePtr, AtomicRefCountSubReturnsNewCount)
{
    ref_count_storage<CounterPolicy::Atomic> storage;

    storage.intrusive_ref_add();
    storage.intrusive_ref_add();
    storage.intrusive_ref_add();

    EXPECT_EQ(storage.intrusive_ref_sub(), 2u);
    EXPECT_EQ(storage.intrusive_ref_count(), 2u);

    EXPECT_EQ(storage.intrusive_ref_sub(), 1u);
    EXPECT_EQ(storage.intrusive_ref_count(), 1u);

    EXPECT_EQ(storage.intrusive_ref_sub(), 0u);
    EXPECT_EQ(storage.intrusive_ref_count(), 0u);
}

TEST(IntrusivePtr, NonAtomicRefCountSubReturnsNewCount)
{
    ref_count_storage<CounterPolicy::NonAtomic> storage;

    storage.intrusive_ref_add();
    storage.intrusive_ref_add();

    EXPECT_EQ(storage.intrusive_ref_sub(), 1u);
    EXPECT_EQ(storage.intrusive_ref_sub(), 0u);
}

// =============================================================================
// Default construction / nullptr
// =============================================================================

TEST(IntrusivePtr, DefaultConstructedIsNull)
{
    intrusive_ptr<TestObject> ptr;

    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(ptr);
    EXPECT_TRUE(!ptr);
    EXPECT_EQ(ptr.size(), 0u);
}

TEST(IntrusivePtr, NullptrComparisons)
{
    intrusive_ptr<TestObject> ptr;

    EXPECT_TRUE(ptr == nullptr);
    EXPECT_TRUE(nullptr == ptr);
    EXPECT_FALSE(ptr != nullptr);
    EXPECT_FALSE(nullptr != ptr);
}

// =============================================================================
// Raw pointer construction
// =============================================================================

TEST(IntrusivePtr, ConstructFromRawPointerIncrementsReferenceCount)
{
    TestObject::reset();

    auto* object = xr_new<TestObject>(42);

    EXPECT_EQ(object->intrusive_ref_count(), 0u);

    {
        intrusive_ptr<TestObject> ptr(object);

        EXPECT_EQ(ptr.get(), object);
        EXPECT_EQ(ptr->value, 42);
        EXPECT_EQ(object->intrusive_ref_count(), 1u);
        EXPECT_EQ(ptr.size(), 1u);
        EXPECT_TRUE(ptr);
        EXPECT_FALSE(!ptr);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}

TEST(IntrusivePtr, ConstructFromNullPointer)
{
    intrusive_ptr<TestObject> ptr(static_cast<TestObject*>(nullptr));

    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.size(), 0u);
    EXPECT_FALSE(ptr);
}

// =============================================================================
// Copy construction
// =============================================================================

TEST(IntrusivePtr, CopyConstructionIncrementsReferenceCount)
{
    TestObject::reset();

    {
        auto ptr1 = make_intrusive<TestObject>(123);

        ASSERT_TRUE(ptr1);
        ASSERT_EQ(ptr1.size(), 1u);

        {
            intrusive_ptr<TestObject> ptr2(ptr1);

            EXPECT_EQ(ptr1.get(), ptr2.get());
            EXPECT_EQ(ptr1, ptr2);
            EXPECT_EQ(ptr1.size(), 2u);
            EXPECT_EQ(ptr2.size(), 2u);
        }

        EXPECT_EQ(ptr1.size(), 1u);
        EXPECT_EQ(TestObject::destroyed, 0);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}

// =============================================================================
// Move construction
// =============================================================================

TEST(IntrusivePtr, MoveConstructionTransfersOwnership)
{
    TestObject::reset();

    {
        auto ptr1 = make_intrusive<TestObject>(123);

        ASSERT_TRUE(ptr1);
        auto* object = ptr1.get();

        intrusive_ptr<TestObject> ptr2(std::move(ptr1));

        EXPECT_EQ(ptr1.get(), nullptr);
        EXPECT_EQ(ptr1.size(), 0u);

        EXPECT_EQ(ptr2.get(), object);
        EXPECT_EQ(ptr2->value, 123);
        EXPECT_EQ(ptr2.size(), 1u);
        EXPECT_EQ(TestObject::destroyed, 0);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}

// =============================================================================
// Copy assignment
// =============================================================================

TEST(IntrusivePtr, CopyAssignment)
{
    TestObject::reset();

    {
        auto first = make_intrusive<TestObject>(1);
        auto second = make_intrusive<TestObject>(2);

        ASSERT_NE(first.get(), second.get());

        second = first;

        EXPECT_EQ(second.get(), first.get());
        EXPECT_EQ(first.size(), 2u);
        EXPECT_EQ(second.size(), 2u);

        // The old object must have been released.
        EXPECT_EQ(TestObject::destroyed, 1);
    }

    EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(IntrusivePtr, SelfCopyAssignmentKeepsOwnership)
{
    TestObject::reset();

    {
        auto ptr = make_intrusive<TestObject>(42);

        auto* object = ptr.get();

        ptr = ptr;

        EXPECT_EQ(ptr.get(), object);
        EXPECT_EQ(ptr.size(), 1u);
        EXPECT_EQ(TestObject::destroyed, 0);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}

// =============================================================================
// Move assignment
// =============================================================================

TEST(IntrusivePtr, MoveAssignmentTransfersOwnership)
{
    TestObject::reset();

    {
        auto first = make_intrusive<TestObject>(1);
        auto second = make_intrusive<TestObject>(2);

        auto* first_object = first.get();

        second = std::move(first);

        EXPECT_EQ(first.get(), nullptr);
        EXPECT_EQ(first.size(), 0u);

        EXPECT_EQ(second.get(), first_object);
        EXPECT_EQ(second->value, 1);
        EXPECT_EQ(second.size(), 1u);

        // The object previously owned by second must have been released.
        EXPECT_EQ(TestObject::destroyed, 1);
    }

    EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(IntrusivePtr, SelfMoveAssignmentKeepsOwnership)
{
    TestObject::reset();

    {
        auto ptr = make_intrusive<TestObject>(42);

        auto* object = ptr.get();

        ptr = std::move(ptr);

        EXPECT_EQ(ptr.get(), object);
        EXPECT_EQ(ptr.size(), 1u);
        EXPECT_EQ(TestObject::destroyed, 0);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}

// =============================================================================
// Raw pointer assignment
// =============================================================================

TEST(IntrusivePtr, AssignmentFromRawPointer)
{
    TestObject::reset();

    auto* first = xr_new<TestObject>(1);
    auto* second = xr_new<TestObject>(2);

    {
        intrusive_ptr<TestObject> ptr(first);

        ASSERT_EQ(first->intrusive_ref_count(), 1u);

        ptr = second;

        EXPECT_EQ(ptr.get(), second);
        EXPECT_EQ(second->intrusive_ref_count(), 1u);
        EXPECT_EQ(TestObject::destroyed, 1);
    }

    EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(IntrusivePtr, AssignmentFromNullPointerReleasesObject)
{
    TestObject::reset();

    {
        auto ptr = make_intrusive<TestObject>(42);

        ASSERT_TRUE(ptr);

        ptr = nullptr;

        EXPECT_EQ(ptr.get(), nullptr);
        EXPECT_EQ(ptr.size(), 0u);
        EXPECT_FALSE(ptr);
        EXPECT_EQ(TestObject::destroyed, 1);
    }
}

// =============================================================================
// Access
// =============================================================================

TEST(IntrusivePtr, DereferenceOperators)
{
    auto ptr = make_intrusive<TestObject>(123);

    EXPECT_EQ((*ptr).value, 123);
    EXPECT_EQ(ptr->value, 123);
}

TEST(IntrusivePtr, GetReturnsOwnedPointer)
{
    auto ptr = make_intrusive<TestObject>(123);

    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr.get()->value, 123);
}

// =============================================================================
// set()
// =============================================================================

TEST(IntrusivePtr, SetRawPointer)
{
    TestObject::reset();

    auto* first = xr_new<TestObject>(1);
    auto* second = xr_new<TestObject>(2);

    {
        intrusive_ptr<TestObject> ptr(first);

        ptr.set(second);

        EXPECT_EQ(ptr.get(), second);
        EXPECT_EQ(ptr->value, 2);
        EXPECT_EQ(second->intrusive_ref_count(), 1u);
        EXPECT_EQ(TestObject::destroyed, 1);
    }

    EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(IntrusivePtr, SetSelfPointerDoesNotDestroyObject)
{
    TestObject::reset();

    {
        auto ptr = make_intrusive<TestObject>(42);

        auto* object = ptr.get();

        ptr.set(object);

        EXPECT_EQ(ptr.get(), object);
        EXPECT_EQ(ptr.size(), 1u);
        EXPECT_EQ(TestObject::destroyed, 0);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}

TEST(IntrusivePtr, SetFromAnotherPointer)
{
    TestObject::reset();

    {
        auto first = make_intrusive<TestObject>(42);
        intrusive_ptr<TestObject> second;

        second.set(first);

        EXPECT_EQ(first.get(), second.get());
        EXPECT_EQ(first.size(), 2u);
        EXPECT_EQ(second.size(), 2u);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}

// =============================================================================
// swap
// =============================================================================

TEST(IntrusivePtr, MemberSwap)
{
    auto first = make_intrusive<TestObject>(1);
    auto second = make_intrusive<TestObject>(2);

    auto* first_object = first.get();
    auto* second_object = second.get();

    first.swap(second);

    EXPECT_EQ(first.get(), second_object);
    EXPECT_EQ(second.get(), first_object);

    EXPECT_EQ(first->value, 2);
    EXPECT_EQ(second->value, 1);

    EXPECT_EQ(first.size(), 1u);
    EXPECT_EQ(second.size(), 1u);
}

TEST(IntrusivePtr, FreeSwap)
{
    auto first = make_intrusive<TestObject>(1);
    auto second = make_intrusive<TestObject>(2);

    auto* first_object = first.get();
    auto* second_object = second.get();

    swap(first, second);

    EXPECT_EQ(first.get(), second_object);
    EXPECT_EQ(second.get(), first_object);
}

// =============================================================================
// equal / comparison operators
// =============================================================================

TEST(IntrusivePtr, Equal)
{
    auto first = make_intrusive<TestObject>(1);
    intrusive_ptr<TestObject> second(first);

    auto third = make_intrusive<TestObject>(2);

    EXPECT_TRUE(first.equal(second));
    EXPECT_FALSE(first.equal(third));
}

TEST(IntrusivePtr, EqualityOperators)
{
    auto first = make_intrusive<TestObject>(1);
    intrusive_ptr<TestObject> second(first);
    auto third = make_intrusive<TestObject>(2);

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);

    EXPECT_FALSE(first == third);
    EXPECT_TRUE(first != third);
}

TEST(IntrusivePtr, OrderingOperators)
{
    auto first = make_intrusive<TestObject>(1);
    auto second = make_intrusive<TestObject>(2);

    ASSERT_NE(first.get(), second.get());

    EXPECT_EQ(first < second, first.get() < second.get());
    EXPECT_EQ(first > second, first.get() > second.get());
}

// =============================================================================
// Polymorphic conversion
// =============================================================================

TEST(IntrusivePtr, DerivedToBaseCopyConstruction)
{
    TestDerived::reset();

    {
        intrusive_ptr<TestDerived> derived = make_intrusive<TestDerived>();
        intrusive_ptr<TestBase> base(derived);

        EXPECT_EQ(base.get(), derived.get());
        EXPECT_EQ(derived.size(), 2u);
        EXPECT_EQ(base.size(), 2u);
    }

    EXPECT_EQ(TestDerived::destroyed, 1);
    EXPECT_EQ(TestBase::destroyed, 1);
}

TEST(IntrusivePtr, DerivedToBaseAssignment)
{
    TestDerived::reset();

    {
        intrusive_ptr<TestDerived> derived = make_intrusive<TestDerived>();
        intrusive_ptr<TestBase> base;

        base = derived;

        EXPECT_EQ(base.get(), derived.get());
        EXPECT_EQ(base.size(), 2u);
        EXPECT_EQ(derived.size(), 2u);
    }

    EXPECT_EQ(TestDerived::destroyed, 1);
    EXPECT_EQ(TestBase::destroyed, 1);
}

// =============================================================================
// Non-atomic policy
// =============================================================================

TEST(IntrusivePtr, NonAtomicReferenceCounting)
{
    TestObjectNonAtomic::reset();

    {
        auto first = make_intrusive<TestObjectNonAtomic>(42);

        EXPECT_EQ(first.size(), 1u);

        intrusive_ptr<TestObjectNonAtomic> second(first);

        EXPECT_EQ(first.size(), 2u);
        EXPECT_EQ(second.size(), 2u);

        second = nullptr;

        EXPECT_EQ(first.size(), 1u);
        EXPECT_EQ(TestObjectNonAtomic::destroyed, 0);
    }

    EXPECT_EQ(TestObjectNonAtomic::destroyed, 1);
}

// =============================================================================
// Deferred deletion
// =============================================================================

TEST(IntrusivePtr, DeferredPolicyCallsDeferredRelease)
{
    DeferredTestObject::reset();

    {
        auto ptr = make_intrusive<DeferredTestObject>(42);

        ASSERT_TRUE(ptr);
        ASSERT_EQ(ptr.size(), 1u);

        ptr = nullptr;

        EXPECT_EQ(DeferredTestObject::deferred_releases, 1);
        EXPECT_EQ(DeferredTestObject::destroyed, 0);
    }

    EXPECT_EQ(DeferredTestObject::deferred_releases, 1);
    EXPECT_EQ(DeferredTestObject::destroyed, 0);
}

TEST(IntrusivePtr, DeferredPolicyDoesNotCallDeferredReleaseUntilLastReference)
{
    DeferredTestObject::reset();

    {
        auto first = make_intrusive<DeferredTestObject>();
        intrusive_ptr<DeferredTestObject> second(first);

        first = nullptr;

        EXPECT_EQ(DeferredTestObject::deferred_releases, 0);
        EXPECT_EQ(DeferredTestObject::destroyed, 0);

        second = nullptr;

        EXPECT_EQ(DeferredTestObject::deferred_releases, 1);
        EXPECT_EQ(DeferredTestObject::destroyed, 0);
    }
}

// =============================================================================
// Strict policy
// =============================================================================

TEST(IntrusivePtr, StrictPolicyReferenceCounting)
{
    StrictTestObject::reset();

    {
        auto first = make_intrusive<StrictTestObject>(42);

        ASSERT_TRUE(first);
        EXPECT_EQ(first->value, 42);
        EXPECT_EQ(first.size(), 1u);

        {
            intrusive_ptr<StrictTestObject> second(first);

            EXPECT_EQ(first.size(), 2u);
            EXPECT_EQ(second.size(), 2u);
        }

        EXPECT_EQ(first.size(), 1u);
        EXPECT_EQ(StrictTestObject::destroyed, 0);
    }

    EXPECT_EQ(StrictTestObject::destroyed, 1);
}

// =============================================================================
// make_intrusive
// =============================================================================

TEST(IntrusivePtr, MakeIntrusiveConstructsObject)
{
    TestObject::reset();

    {
        auto ptr = make_intrusive<TestObject>(123);

        ASSERT_TRUE(ptr);
        ASSERT_NE(ptr.get(), nullptr);

        EXPECT_EQ(ptr->value, 123);
        EXPECT_EQ(ptr.size(), 1u);
    }

    EXPECT_EQ(TestObject::destroyed, 1);
}
