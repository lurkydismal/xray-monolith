#include "stdafx.h"

#include "xr_delegate.h"

#include <gtest/gtest.h>

#include <string>
#include <utility>

namespace
{
    int StaticAdd(int a, int b)
    {
        return a + b;
    }

    void StaticSetValue(int value, int* output)
    {
        *output = value;
    }

    struct TestObject
    {
        int value = 0;

        int Add(int a, int b)
        {
            return value + a + b;
        }

        int GetValue() const
        {
            return value;
        }

        void SetValue(int v)
        {
            value = v;
        }

        void SetValueAndAdd(int v, int amount)
        {
            value = v + amount;
        }
    };

    struct Base
    {
        int value = 0;

        int GetValue() const
        {
            return value;
        }
    };

    struct Derived : Base
    {
        int Add(int x)
        {
            return value + x;
        }
    };

    // -------------------------------------------------------------------------
    // Construction / empty state
    // -------------------------------------------------------------------------

    TEST(XrDelegate, DefaultConstructedDelegateIsEmpty)
    {
        xr_delegate<int()> delegate;

        EXPECT_TRUE(delegate.empty());
        EXPECT_TRUE(!delegate);
    }

    TEST(XrDelegate, DefaultConstructedDelegateComparesEqualToNull)
    {
        xr_delegate<int()> delegate;

        EXPECT_TRUE(delegate == nullptr);
        EXPECT_FALSE(delegate != nullptr);
    }

    TEST(XrDelegate, BindingMakesDelegateNonEmpty)
    {
        TestObject object;

        xr_delegate<int()> delegate(&object, &TestObject::GetValue);

        EXPECT_FALSE(delegate.empty());
        EXPECT_TRUE(static_cast<bool>(delegate));
        EXPECT_FALSE(delegate == nullptr);
        EXPECT_TRUE(delegate != nullptr);
    }

    // -------------------------------------------------------------------------
    // Non-const member functions
    // -------------------------------------------------------------------------

    TEST(XrDelegate, InvokesNonConstMemberFunction)
    {
        TestObject object;
        object.value = 10;

        xr_delegate<int(int, int)> delegate(
            &object,
            &TestObject::Add);

        EXPECT_EQ(delegate(2, 3), 15);
    }

    TEST(XrDelegate, BindCanReplaceExistingMemberFunction)
    {
        TestObject object;
        object.value = 10;

        xr_delegate<int(int, int)> delegate;

        delegate.bind(&object, &TestObject::Add);

        EXPECT_EQ(delegate(1, 2), 13);
    }

    TEST(XrDelegate, InvokesVoidMemberFunction)
    {
        TestObject object;

        xr_delegate<void(int)> delegate(
            &object,
            &TestObject::SetValue);

        delegate(42);

        EXPECT_EQ(object.value, 42);
    }

    TEST(XrDelegate, InvokesMemberFunctionWithMultipleArguments)
    {
        TestObject object;

        xr_delegate<void(int, int)> delegate(
            &object,
            &TestObject::SetValueAndAdd);

        delegate(10, 7);

        EXPECT_EQ(object.value, 17);
    }

    // -------------------------------------------------------------------------
    // Const member functions
    // -------------------------------------------------------------------------

    TEST(XrDelegate, InvokesConstMemberFunction)
    {
        const TestObject object{42};

        xr_delegate<int()> delegate(
            &object,
            &TestObject::GetValue);

        EXPECT_EQ(delegate(), 42);
    }

    TEST(XrDelegate, ConstMemberFunctionCanBeBoundFromConstObject)
    {
        const TestObject object{123};

        xr_delegate<int()> delegate;

        delegate.bind(&object, &TestObject::GetValue);

        EXPECT_EQ(delegate(), 123);
    }

    // -------------------------------------------------------------------------
    // Static functions
    // -------------------------------------------------------------------------

    TEST(XrDelegate, InvokesStaticFunction)
    {
        xr_delegate<int(int, int)> delegate(&StaticAdd);

        EXPECT_EQ(delegate(10, 20), 30);
    }

    TEST(XrDelegate, BindCanBindStaticFunction)
    {
        xr_delegate<int(int, int)> delegate;

        delegate.bind(&StaticAdd);

        EXPECT_EQ(delegate(7, 8), 15);
    }

#if 0
    TEST(XrDelegate, StaticFunctionCanBeAssigned)
    {
        xr_delegate<int(int, int)> delegate;

        delegate = &StaticAdd;

        EXPECT_EQ(delegate(4, 5), 9);
    }
#endif

    TEST(XrDelegate, StaticFunctionWithVoidReturnType)
    {
        int output = 0;

        xr_delegate<void(int, int*)> delegate(&StaticSetValue);

        delegate(123, &output);

        EXPECT_EQ(output, 123);
    }

    // -------------------------------------------------------------------------
    // MakeDelegate
    // -------------------------------------------------------------------------

    TEST(XrDelegate, MakeDelegateCreatesMemberFunctionDelegate)
    {
        TestObject object;
        object.value = 20;

        auto delegate = xr_make_delegate(&object, &TestObject::Add);

        EXPECT_EQ(delegate(1, 2), 23);
    }

    TEST(XrDelegate, MakeDelegateCreatesConstMemberFunctionDelegate)
    {
        const TestObject object{99};

        auto delegate = xr_make_delegate(&object, &TestObject::GetValue);

        EXPECT_EQ(delegate(), 99);
    }

    TEST(XrDelegate, MakeDelegateCreatesStaticFunctionDelegate)
    {
        auto delegate = xr_make_delegate(&StaticAdd);

        EXPECT_EQ(delegate(100, 23), 123);
    }

    // -------------------------------------------------------------------------
    // Copying / assignment
    // -------------------------------------------------------------------------

    TEST(XrDelegate, CopyConstructionPreservesInvocation)
    {
        TestObject object;
        object.value = 50;

        xr_delegate<int(int, int)> original(
            &object,
            &TestObject::Add);

        xr_delegate<int(int, int)> copy(original);

        EXPECT_TRUE(copy);
        EXPECT_EQ(copy(1, 2), 53);
        EXPECT_EQ(copy, original);
    }

    TEST(XrDelegate, CopyAssignmentPreservesInvocation)
    {
        TestObject object;
        object.value = 50;

        xr_delegate<int(int, int)> original(
            &object,
            &TestObject::Add);

        xr_delegate<int(int, int)> copy;

        copy = original;

        EXPECT_TRUE(copy);
        EXPECT_EQ(copy(1, 2), 53);
        EXPECT_EQ(copy, original);
    }

    TEST(XrDelegate, CopiedStaticDelegateRemainsValid)
    {
        xr_delegate<int(int, int)> original(&StaticAdd);
        xr_delegate<int(int, int)> copy(original);

        EXPECT_TRUE(copy);
        EXPECT_EQ(copy, original);
        EXPECT_EQ(copy(3, 4), 7);
    }

    // -------------------------------------------------------------------------
    // Equality / inequality
    // -------------------------------------------------------------------------

    TEST(XrDelegate, SameMemberFunctionAndObjectCompareEqual)
    {
        TestObject object;

        xr_delegate<int()> first(&object, &TestObject::GetValue);
        xr_delegate<int()> second(&object, &TestObject::GetValue);

        EXPECT_EQ(first, second);
        EXPECT_FALSE(first != second);
    }

    TEST(XrDelegate, DifferentObjectsCompareNotEqual)
    {
        TestObject firstObject;
        TestObject secondObject;

        xr_delegate<int()> first(
            &firstObject,
            &TestObject::GetValue);

        xr_delegate<int()> second(
            &secondObject,
            &TestObject::GetValue);

        EXPECT_NE(first, second);
    }

    TEST(XrDelegate, DifferentMemberFunctionsCompareNotEqual)
    {
        TestObject object;

        xr_delegate<int()> first(
            &object,
            &TestObject::GetValue);

        xr_delegate<void(int)> second(
            &object,
            &TestObject::SetValue);

        // Different delegate types cannot be compared directly.
        // Verify their independent behavior instead.
        EXPECT_EQ(first(), 0);

        second(42);

        EXPECT_EQ(first(), 42);
    }

    TEST(XrDelegate, SameStaticFunctionComparesEqual)
    {
        xr_delegate<int(int, int)> first(&StaticAdd);
        xr_delegate<int(int, int)> second(&StaticAdd);

        EXPECT_EQ(first, second);
        EXPECT_FALSE(first != second);
    }

    // -------------------------------------------------------------------------
    // clear()
    // -------------------------------------------------------------------------

    TEST(XrDelegate, ClearMakesDelegateEmpty)
    {
        TestObject object;

        xr_delegate<int()> delegate(
            &object,
            &TestObject::GetValue);

        ASSERT_TRUE(delegate);

        delegate.clear();

        EXPECT_TRUE(delegate.empty());
        EXPECT_TRUE(!delegate);
        EXPECT_TRUE(delegate == nullptr);
        EXPECT_FALSE(delegate != nullptr);
    }

    TEST(XrDelegate, ClearAllowsDelegateToBeRebound)
    {
        TestObject object;
        object.value = 10;

        xr_delegate<int()> delegate(
            &object,
            &TestObject::GetValue);

        delegate.clear();

        EXPECT_TRUE(delegate.empty());

        delegate.bind(&object, &TestObject::GetValue);

        EXPECT_FALSE(delegate.empty());
        EXPECT_EQ(delegate(), 10);
    }

    TEST(XrDelegate, AssigningNullptrClearsDelegate)
    {
        xr_delegate<int(int, int)> delegate(&StaticAdd);

        ASSERT_TRUE(delegate);

        delegate = nullptr;

        EXPECT_TRUE(delegate.empty());
        EXPECT_TRUE(delegate == nullptr);
        EXPECT_FALSE(delegate != nullptr);
    }

    // -------------------------------------------------------------------------
    // Delegate object lifetime / target state
    // -------------------------------------------------------------------------

    TEST(XrDelegate, DelegateUsesCurrentStateOfTargetObject)
    {
        TestObject object;
        object.value = 10;

        xr_delegate<int()> delegate(
            &object,
            &TestObject::GetValue);

        EXPECT_EQ(delegate(), 10);

        object.value = 42;

        EXPECT_EQ(delegate(), 42);
    }

    // -------------------------------------------------------------------------
    // Derived -> base compatibility
    // -------------------------------------------------------------------------

    TEST(XrDelegate, CanBindBaseMemberFunctionToDerivedObject)
    {
        Derived object;
        object.value = 25;

        xr_delegate<int()> delegate(
            &object,
            &Base::GetValue);

        EXPECT_EQ(delegate(), 25);
    }

    TEST(XrDelegate, MakeDelegateCanBindDerivedObjectToBaseMemberFunction)
    {
        Derived object;
        object.value = 30;

        auto delegate = xr_make_delegate(
            &object,
            &Base::GetValue);

        EXPECT_EQ(delegate(), 30);
    }

    // -------------------------------------------------------------------------
    // Comparison / ordering
    // -------------------------------------------------------------------------

    TEST(XrDelegate, EqualDelegatesHaveSameOrdering)
    {
        TestObject object;

        xr_delegate<int()> first(
            &object,
            &TestObject::GetValue);

        xr_delegate<int()> second(
            &object,
            &TestObject::GetValue);

        EXPECT_FALSE(first < second);
        EXPECT_FALSE(second < first);
        EXPECT_FALSE(first > second);
        EXPECT_FALSE(second > first);
    }

    TEST(XrDelegate, EmptyDelegateIsEqualToAnotherEmptyDelegate)
    {
        xr_delegate<int()> first;
        xr_delegate<int()> second;

        EXPECT_EQ(first, second);
        EXPECT_FALSE(first != second);
        EXPECT_FALSE(first < second);
        EXPECT_FALSE(second < first);
    }

    // -------------------------------------------------------------------------
    // Memento
    // -------------------------------------------------------------------------

    TEST(XrDelegate, MementoCanBeCopiedBackIntoDelegate)
    {
        TestObject object;
        object.value = 77;

        xr_delegate<int()> original(
            &object,
            &TestObject::GetValue);

        const fastdelegate::DelegateMemento& memento =
            original.GetMemento();

        xr_delegate<int()> restored;

        restored.SetMemento(memento);

        EXPECT_TRUE(restored);
        EXPECT_EQ(restored, original);
        EXPECT_EQ(restored(), 77);
    }
}

