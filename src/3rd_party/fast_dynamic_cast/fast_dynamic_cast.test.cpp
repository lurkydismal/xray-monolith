#include "fast_dynamic_cast.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <type_traits>

namespace
{

struct Base
{
    virtual ~Base() = default;

    int base_value = 10;
};

struct Derived : Base
{
    int derived_value = 20;
};

struct OtherDerived : Base
{
    int other_value = 30;
};

struct Unrelated
{
    virtual ~Unrelated() = default;

    int unrelated_value = 40;
};

// Multiple inheritance is important here because the destination pointer
// may require a non-zero pointer adjustment.
struct Left
{
    virtual ~Left() = default;

    int left_value = 50;
};

struct Right
{
    virtual ~Right() = default;

    int right_value = 60;
};

struct MultipleDerived : Left, Right
{
    int derived_value = 70;
};

struct NonPolymorphic
{
    int value = 80;
};

} // namespace


// -----------------------------------------------------------------------------
// Pointer casts
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, NullPointerReturnsNull)
{
    Base* base = nullptr;

    auto result = fast_dynamic_cast<Derived*>(base);

    EXPECT_EQ(result, nullptr);
}

TEST(FastDynamicCast, SuccessfulDowncast)
{
    Derived object;
    Base* base = &object;

    auto result = fast_dynamic_cast<Derived*>(base);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &object);
    EXPECT_EQ(result->base_value, 10);
    EXPECT_EQ(result->derived_value, 20);
}

TEST(FastDynamicCast, FailedDowncastReturnsNull)
{
    OtherDerived object;
    Base* base = &object;

    auto result = fast_dynamic_cast<Derived*>(base);

    EXPECT_EQ(result, nullptr);
}

TEST(FastDynamicCast, CastToUnrelatedTypeReturnsNull)
{
    Derived object;
    Base* base = &object;

    auto result = fast_dynamic_cast<Unrelated*>(base);

    EXPECT_EQ(result, nullptr);
}

TEST(FastDynamicCast, CastingToSameTypeReturnsSamePointer)
{
    Derived object;
    Derived* derived = &object;

    auto result = fast_dynamic_cast<Derived*>(derived);

    EXPECT_EQ(result, derived);
}


// -----------------------------------------------------------------------------
// Multiple inheritance / pointer adjustment
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, MultipleInheritanceAdjustsPointerCorrectly)
{
    MultipleDerived object;

    Left* left = &object;
    Right* right = &object;

    ASSERT_NE(left, nullptr);
    ASSERT_NE(right, nullptr);

    // These pointers are normally different addresses.
    EXPECT_NE(
        reinterpret_cast<void*>(left),
        reinterpret_cast<void*>(right));

    auto result_from_left =
        fast_dynamic_cast<Right*>(left);

    auto result_from_right =
        fast_dynamic_cast<Left*>(right);

    ASSERT_NE(result_from_left, nullptr);
    ASSERT_NE(result_from_right, nullptr);

    EXPECT_EQ(result_from_left, right);
    EXPECT_EQ(result_from_right, left);

    EXPECT_EQ(result_from_left->right_value, 60);
    EXPECT_EQ(result_from_right->left_value, 50);
}

TEST(FastDynamicCast, MultipleInheritanceDowncastFromNonPrimaryBase)
{
    MultipleDerived object;

    Right* right = &object;

    auto result =
        fast_dynamic_cast<MultipleDerived*>(right);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &object);
    EXPECT_EQ(result->derived_value, 70);
}


// -----------------------------------------------------------------------------
// Const pointer casts
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, ConstPointerSuccessfulCast)
{
    const Derived object;
    const Base* base = &object;

    auto result =
        fast_dynamic_cast<const Derived*>(base);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &object);
    EXPECT_EQ(result->derived_value, 20);
}

TEST(FastDynamicCast, ConstPointerFailedCastReturnsNull)
{
    const OtherDerived object;
    const Base* base = &object;

    auto result =
        fast_dynamic_cast<const Derived*>(base);

    EXPECT_EQ(result, nullptr);
}

TEST(FastDynamicCast, ConstNullPointerReturnsNull)
{
    const Base* base = nullptr;

    auto result =
        fast_dynamic_cast<const Derived*>(base);

    EXPECT_EQ(result, nullptr);
}


// -----------------------------------------------------------------------------
// Reference casts
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, SuccessfulReferenceCast)
{
    Derived object;
    Base& base = object;

    Derived& result =
        fast_dynamic_cast<Derived&>(base);

    EXPECT_EQ(&result, &object);
    EXPECT_EQ(result.derived_value, 20);
}

TEST(FastDynamicCast, FailedReferenceCastThrowsBadCast)
{
    OtherDerived object;
    Base& base = object;

    EXPECT_DEATH(
        fast_dynamic_cast<Derived&>(base),
        "");
}

TEST(FastDynamicCast, ConstReferenceSuccessfulCast)
{
    const Derived object;
    const Base& base = object;

    const Derived& result =
        fast_dynamic_cast<const Derived&>(base);

    EXPECT_EQ(&result, &object);
    EXPECT_EQ(result.derived_value, 20);
}

TEST(FastDynamicCast, ConstReferenceFailedCastThrowsBadCast)
{
    const OtherDerived object;
    const Base& base = object;

    EXPECT_DEATH(
        fast_dynamic_cast<const Derived&>(base),
        "");
}


// -----------------------------------------------------------------------------
// Shared pointer casts
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, SharedPointerSuccessfulCast)
{
    auto derived = std::make_shared<Derived>();
    std::shared_ptr<Base> base = derived;

    auto result =
        fast_dynamic_pointer_cast<Derived>(base);

    ASSERT_TRUE(result);
    EXPECT_EQ(result.get(), derived.get());
    EXPECT_EQ(result->derived_value, 20);

    // The result must share ownership with the original pointer.
    EXPECT_EQ(result.use_count(), base.use_count());
}

TEST(FastDynamicCast, SharedPointerFailedCastReturnsEmptyPointer)
{
    auto other = std::make_shared<OtherDerived>();
    std::shared_ptr<Base> base = other;

    auto result =
        fast_dynamic_pointer_cast<Derived>(base);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.get(), nullptr);

    // Failed cast must not destroy/change ownership.
    EXPECT_EQ(base.get(), other.get());
}

TEST(FastDynamicCast, EmptySharedPointerReturnsEmptyPointer)
{
    std::shared_ptr<Base> base;

    auto result =
        fast_dynamic_pointer_cast<Derived>(base);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.get(), nullptr);
}

TEST(FastDynamicCast, SharedPointerMultipleInheritance)
{
    auto object = std::make_shared<MultipleDerived>();

    std::shared_ptr<Left> left = object;

    auto right =
        fast_dynamic_pointer_cast<Right>(left);

    ASSERT_TRUE(right);

    auto expected =
        dynamic_cast<Right*>(left.get());

    EXPECT_EQ(right.get(), expected);
    EXPECT_EQ(right->right_value, 60);
}


// -----------------------------------------------------------------------------
// Identity overload
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, IdentityPointerCastReturnsOriginalPointer)
{
    Derived object;
    Derived* ptr = &object;

    auto result =
        fast_dynamic_cast<Derived*>(ptr);

    EXPECT_EQ(result, ptr);
}

#if 0
TEST(FastDynamicCast, IdentityValueCastReturnsOriginalValue)
{
    int value = 123;

    auto result =
        fast_dynamic_cast<int>(value);

    EXPECT_EQ(result, value);
}
#endif


// -----------------------------------------------------------------------------
// Repeated casts
//
// These are particularly important for the fast implementation because the
// first cast populates the thread-local cache and subsequent casts use it.
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, RepeatedSuccessfulCasts)
{
    Derived object;
    Base* base = &object;

    for (int i = 0; i < 10000; ++i)
    {
        auto result =
            fast_dynamic_cast<Derived*>(base);

        ASSERT_EQ(result, &object);
    }
}

TEST(FastDynamicCast, RepeatedFailedCasts)
{
    OtherDerived object;
    Base* base = &object;

    for (int i = 0; i < 10000; ++i)
    {
        auto result =
            fast_dynamic_cast<Derived*>(base);

        ASSERT_EQ(result, nullptr);
    }
}

TEST(FastDynamicCast, RepeatedCrossCasts)
{
    MultipleDerived object;

    Left* left = &object;

    for (int i = 0; i < 10000; ++i)
    {
        auto result =
            fast_dynamic_cast<Right*>(left);

        ASSERT_EQ(result, static_cast<Right*>(&object));
    }
}


// -----------------------------------------------------------------------------
// Different objects with the same dynamic type
//
// This matters for the cache implementation: the cached offset must be valid
// for every object having the same source vtable.
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, SameDynamicTypeDifferentObjects)
{
    Derived first;
    Derived second;

    Base* first_base = &first;
    Base* second_base = &second;

    auto first_result =
        fast_dynamic_cast<Derived*>(first_base);

    ASSERT_EQ(first_result, &first);

    auto second_result =
        fast_dynamic_cast<Derived*>(second_base);

    ASSERT_EQ(second_result, &second);
}

TEST(FastDynamicCast, SameDynamicTypeDifferentObjectsMultipleInheritance)
{
    MultipleDerived first;
    MultipleDerived second;

    Left* first_left = &first;
    Left* second_left = &second;

    auto first_result =
        fast_dynamic_cast<Right*>(first_left);

    ASSERT_EQ(first_result, static_cast<Right*>(&first));

    auto second_result =
        fast_dynamic_cast<Right*>(second_left);

    ASSERT_EQ(second_result, static_cast<Right*>(&second));
}


// -----------------------------------------------------------------------------
// Cache invalidation / different dynamic types
//
// The same From/To template specialization is used for both casts, but the
// dynamic type changes. The implementation must not reuse the previous
// object's offset blindly.
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, DifferentDynamicTypesDoNotReuseWrongResult)
{
    Derived derived;
    OtherDerived other;

    Base* base1 = &derived;
    Base* base2 = &other;

    auto first =
        fast_dynamic_cast<Derived*>(base1);

    ASSERT_EQ(first, &derived);

    auto second =
        fast_dynamic_cast<Derived*>(base2);

    EXPECT_EQ(second, nullptr);
}

TEST(FastDynamicCast, DifferentDynamicTypesMultipleInheritance)
{
    MultipleDerived multiple;
    OtherDerived other;

    Left* left = &multiple;
    Base* base = &other;

    auto first =
        fast_dynamic_cast<Right*>(left);

    ASSERT_EQ(first, static_cast<Right*>(&multiple));

    auto second =
        fast_dynamic_cast<Right*>(base);

    EXPECT_EQ(second, nullptr);
}


// -----------------------------------------------------------------------------
// Compare against the standard dynamic_cast
//
// This is useful as a broad semantic oracle. The fast implementation should
// return exactly what dynamic_cast returns.
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, MatchesDynamicCastForDowncast)
{
    Derived derived;
    Base* base = &derived;

    EXPECT_EQ(
        fast_dynamic_cast<Derived*>(base),
        dynamic_cast<Derived*>(base));
}

TEST(FastDynamicCast, MatchesDynamicCastForFailedCast)
{
    OtherDerived other;
    Base* base = &other;

    EXPECT_EQ(
        fast_dynamic_cast<Derived*>(base),
        dynamic_cast<Derived*>(base));
}

TEST(FastDynamicCast, MatchesDynamicCastForCrossCast)
{
    MultipleDerived object;
    Left* left = &object;

    EXPECT_EQ(
        fast_dynamic_cast<Right*>(left),
        dynamic_cast<Right*>(left));
}

TEST(FastDynamicCast, MatchesDynamicCastForNonPrimaryBaseDowncast)
{
    MultipleDerived object;
    Right* right = &object;

    EXPECT_EQ(
        fast_dynamic_cast<MultipleDerived*>(right),
        dynamic_cast<MultipleDerived*>(right));
}


// -----------------------------------------------------------------------------
// Compile-time properties
// -----------------------------------------------------------------------------

TEST(FastDynamicCast, TypesHaveExpectedProperties)
{
    static_assert(std::is_polymorphic_v<Base>);
    static_assert(std::is_polymorphic_v<Derived>);
    static_assert(std::is_polymorphic_v<MultipleDerived>);

    SUCCEED();
}

TEST(FastDynamicCast, MatchesDynamicCastAcrossHierarchy)
{
    MultipleDerived object;

    Left* left = &object;
    Right* right = &object;

    EXPECT_EQ(
        fast_dynamic_cast<Right*>(left),
        dynamic_cast<Right*>(left));

    EXPECT_EQ(
        fast_dynamic_cast<MultipleDerived*>(left),
        dynamic_cast<MultipleDerived*>(left));

    EXPECT_EQ(
        fast_dynamic_cast<MultipleDerived*>(right),
        dynamic_cast<MultipleDerived*>(right));

    EXPECT_EQ(
        fast_dynamic_cast<Left*>(right),
        dynamic_cast<Left*>(right));
}
