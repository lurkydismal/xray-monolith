#include <cstddef>
#include "fastdelegate.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

namespace {

using fastdelegate::DelegateMemento;
using fastdelegate::FastDelegate;
using fastdelegate::MakeDelegate;

// -----------------------------------------------------------------------------
// Test fixtures / helper types
// -----------------------------------------------------------------------------

class TestObject {
public:
    int value = 0;

    void SetValue(int v) {
        value = v;
    }

    int Add(int a, int b) {
        return value + a + b;
    }

    int AddConst(int a, int b) const {
        return value + a + b;
    }

    void Append(const char* text, std::string& output) {
        output += text;
    }

    bool IsValue(int v) const {
        return value == v;
    }
};

class DerivedTestObject : public TestObject {
public:
    int Multiply(int a, int b) {
        return a * b;
    }
};

class BaseTestObject {
public:
    virtual ~BaseTestObject() = default;

    int base_value = 0;

    int GetBaseValue() const {
        return base_value;
    }
};

class DerivedFromBase : public BaseTestObject {
public:
    int GetDerivedValue() const {
        return base_value + 100;
    }
};

int AddStatic(int a, int b) {
    return a + b;
}

void SetValueStatic(int* value, int new_value) {
    *value = new_value;
}

int ReturnFortyTwo() {
    return 42;
}

void DoNothing() {
}

int Increment(int value) {
    return value + 1;
}

} // namespace

// =============================================================================
// Empty / basic state
// =============================================================================

TEST(FastDelegateTest, DefaultConstructedDelegateIsEmpty)
{
    FastDelegate<void()> delegate;

    EXPECT_TRUE(delegate.empty());
    EXPECT_TRUE(!delegate);
    EXPECT_FALSE(static_cast<bool>(delegate));
    EXPECT_EQ(delegate, nullptr);
}

TEST(FastDelegateTest, ClearMakesDelegateEmpty)
{
    FastDelegate<int()> delegate(&ReturnFortyTwo);

    ASSERT_TRUE(delegate);
    EXPECT_FALSE(delegate.empty());

    delegate.clear();

    EXPECT_TRUE(delegate.empty());
    EXPECT_TRUE(!delegate);
    EXPECT_EQ(delegate, nullptr);
}

TEST(FastDelegateTest, AssigningNullptrMakesDelegateEmpty)
{
    FastDelegate<int()> delegate(&ReturnFortyTwo);

    ASSERT_TRUE(delegate);

    delegate = nullptr;

    EXPECT_TRUE(delegate.empty());
    EXPECT_TRUE(!delegate);
    EXPECT_EQ(delegate, nullptr);
}

// =============================================================================
// Static functions
// =============================================================================

TEST(FastDelegateTest, BindsAndInvokesStaticFunction)
{
    FastDelegate<int(int, int)> delegate(&AddStatic);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(2, 3), 5);
}

TEST(FastDelegateTest, StaticFunctionWithNoArguments)
{
    FastDelegate<int()> delegate(&ReturnFortyTwo);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(), 42);
}

TEST(FastDelegateTest, StaticVoidFunction)
{
    int value = 0;

    FastDelegate<void(int*, int)> delegate(&SetValueStatic);

    ASSERT_TRUE(delegate);

    delegate(&value, 123);

    EXPECT_EQ(value, 123);
}

TEST(FastDelegateTest, AssignStaticFunction)
{
    FastDelegate<int(int)> delegate;

    delegate.bind(&Increment);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(41), 42);
}

TEST(FastDelegateTest, RebindStaticFunction)
{
    FastDelegate<int(int)> delegate;

    delegate.bind(&Increment);

    EXPECT_EQ(delegate(1), 2);

    delegate.bind([](int value) -> int {
        return value + 10;
    });

    EXPECT_EQ(delegate(1), 11);
}

// =============================================================================
// Non-const member functions
// =============================================================================

TEST(FastDelegateTest, BindsAndInvokesMemberFunction)
{
    TestObject object;
    object.value = 10;

    FastDelegate<int(int, int)> delegate(&object, &TestObject::Add);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(2, 3), 15);
}

TEST(FastDelegateTest, MemberFunctionCanModifyObject)
{
    TestObject object;

    FastDelegate<void(int)> delegate(&object, &TestObject::SetValue);

    ASSERT_TRUE(delegate);

    delegate(123);

    EXPECT_EQ(object.value, 123);
}

TEST(FastDelegateTest, RebindMemberFunction)
{
    TestObject object;
    object.value = 10;

    FastDelegate<int(int, int)> delegate(&object, &TestObject::Add);

    EXPECT_EQ(delegate(1, 2), 13);

    delegate.bind(&object, &TestObject::Add);

    EXPECT_EQ(delegate(3, 4), 17);
}

// =============================================================================
// Const member functions
// =============================================================================

TEST(FastDelegateTest, BindsAndInvokesConstMemberFunction)
{
    const TestObject object{.value = 10};

    FastDelegate<int(int, int)> delegate(
        &object,
        &TestObject::AddConst
    );

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(2, 3), 15);
}

TEST(FastDelegateTest, ConstMemberFunctionCanBeUsedForPredicate)
{
    const TestObject object{.value = 42};

    FastDelegate<bool(int)> delegate(
        &object,
        &TestObject::IsValue
    );

    ASSERT_TRUE(delegate);

    EXPECT_TRUE(delegate(42));
    EXPECT_FALSE(delegate(41));
}

// =============================================================================
// Arguments / return types
// =============================================================================

TEST(FastDelegateTest, SupportsReferences)
{
    TestObject object;
    std::string output;

    FastDelegate<void(const char*, std::string&)> delegate(
        &object,
        &TestObject::Append
    );

    delegate("hello", output);
    delegate(" world", output);

    EXPECT_EQ(output, "hello world");
}

TEST(FastDelegateTest, SupportsPointers)
{
    TestObject object;

    FastDelegate<void(int)> delegate(&object, &TestObject::SetValue);

    delegate(99);

    EXPECT_EQ(object.value, 99);
}

TEST(FastDelegateTest, SupportsVoidReturnType)
{
    TestObject object;

    FastDelegate<void(int)> delegate(&object, &TestObject::SetValue);

    delegate(123);

    EXPECT_EQ(object.value, 123);
}

// =============================================================================
// Copy construction / assignment
// =============================================================================

TEST(FastDelegateTest, CopyConstructorCopiesDelegate)
{
    TestObject object;
    object.value = 10;

    FastDelegate<int(int, int)> original(
        &object,
        &TestObject::Add
    );

    FastDelegate<int(int, int)> copy(original);

    ASSERT_TRUE(original);
    ASSERT_TRUE(copy);

    EXPECT_EQ(copy(1, 2), 13);
    EXPECT_EQ(copy, original);
}

TEST(FastDelegateTest, CopyAssignmentCopiesDelegate)
{
    TestObject object;
    object.value = 10;

    FastDelegate<int(int, int)> original(
        &object,
        &TestObject::Add
    );

    FastDelegate<int(int, int)> copy;

    ASSERT_TRUE(copy.empty());

    copy = original;

    ASSERT_TRUE(copy);
    EXPECT_EQ(copy(1, 2), 13);
    EXPECT_EQ(copy, original);
}

TEST(FastDelegateTest, CopyOfStaticDelegateRemainsCallable)
{
    FastDelegate<int(int)> original(&Increment);
    FastDelegate<int(int)> copy(original);

    EXPECT_EQ(original(10), 11);
    EXPECT_EQ(copy(10), 11);
    EXPECT_EQ(original, copy);
}

TEST(FastDelegateTest, CopyCanBeClearedIndependently)
{
    FastDelegate<int(int)> original(&Increment);
    FastDelegate<int(int)> copy(original);

    copy.clear();

    EXPECT_TRUE(copy.empty());
    EXPECT_FALSE(original.empty());
    EXPECT_EQ(original(10), 11);
}

// =============================================================================
// Equality
// =============================================================================

TEST(FastDelegateTest, EmptyDelegatesAreEqual)
{
    FastDelegate<void()> a;
    FastDelegate<void()> b;

    EXPECT_EQ(a, b);
    EXPECT_FALSE(a != b);
}

TEST(FastDelegateTest, SameMemberFunctionAndObjectAreEqual)
{
    TestObject object;

    FastDelegate<int(int, int)> a(&object, &TestObject::Add);
    FastDelegate<int(int, int)> b(&object, &TestObject::Add);

    EXPECT_EQ(a, b);
    EXPECT_FALSE(a != b);
}

TEST(FastDelegateTest, DifferentObjectsAreNotEqual)
{
    TestObject object1;
    TestObject object2;

    FastDelegate<int(int, int)> a(&object1, &TestObject::Add);
    FastDelegate<int(int, int)> b(&object2, &TestObject::Add);

    EXPECT_NE(a, b);
}

TEST(FastDelegateTest, DifferentMemberFunctionsAreNotEqual)
{
    TestObject object;

    FastDelegate<int(int, int)> a(&object, &TestObject::Add);

    // Different signature, therefore use another object to test a
    // different member function with the same signature.
    class Other {
    public:
        int Add(int, int) {
            return 123;
        }
    };

    Other other;

    FastDelegate<int(int, int)> b(&other, &Other::Add);

    EXPECT_NE(a, b);
}

TEST(FastDelegateTest, SameStaticFunctionAreEqual)
{
    FastDelegate<int(int)> a(&Increment);
    FastDelegate<int(int)> b(&Increment);

    EXPECT_EQ(a, b);
    EXPECT_FALSE(a != b);
}

TEST(FastDelegateTest, StaticFunctionAndEmptyDelegateAreDifferent)
{
    FastDelegate<int(int)> empty;
    FastDelegate<int(int)> function(&Increment);

    EXPECT_NE(empty, function);
}

// =============================================================================
// Comparison / ordering
// =============================================================================

TEST(FastDelegateTest, OrderingIsConsistentWithEquality)
{
    TestObject object;

    FastDelegate<int(int, int)> a(&object, &TestObject::Add);
    FastDelegate<int(int, int)> b(&object, &TestObject::Add);

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(FastDelegateTest, OrderingIsStrict)
{
    TestObject object1;
    TestObject object2;

    FastDelegate<int(int, int)> a(&object1, &TestObject::Add);
    FastDelegate<int(int, int)> b(&object2, &TestObject::Add);

    ASSERT_NE(a, b);

    // Strict weak ordering:
    // if a != b, exactly one direction must normally be true.
    EXPECT_NE(a < b, b < a);
}

TEST(FastDelegateTest, DelegatesCanBeStoredInSet)
{
    TestObject object1;
    TestObject object2;

    FastDelegate<int(int, int)> a(&object1, &TestObject::Add);
    FastDelegate<int(int, int)> b(&object2, &TestObject::Add);

    std::set<FastDelegate<int(int, int)>> delegates;

    delegates.insert(a);
    delegates.insert(b);
    delegates.insert(a);

    EXPECT_EQ(delegates.size(), 2U);
}

// =============================================================================
// MakeDelegate
// =============================================================================

TEST(FastDelegateTest, MakeDelegateForStaticFunction)
{
    auto delegate = MakeDelegate(&AddStatic);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(10, 20), 30);
}

TEST(FastDelegateTest, MakeDelegateForMemberFunction)
{
    TestObject object;
    object.value = 10;

    auto delegate = MakeDelegate(&object, &TestObject::Add);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(1, 2), 13);
}

TEST(FastDelegateTest, MakeDelegateForConstMemberFunction)
{
    const TestObject object{.value = 10};

    auto delegate = MakeDelegate(&object, &TestObject::AddConst);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(1, 2), 13);
}

// =============================================================================
// Derived / base member-function relationships
// =============================================================================

#if 0
TEST(FastDelegateTest, DerivedObjectCanBindBaseMemberFunction)
{
    DerivedTestObject object;
    object.value = 10;

    FastDelegate<int()> delegate(
        &object,
        &BaseTestObject::GetBaseValue
    );

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(), 10);
}
#endif

TEST(FastDelegateTest, DerivedMemberFunctionCanBeBoundToDerivedObject)
{
    DerivedTestObject object;

    FastDelegate<int(int, int)> delegate(
        &object,
        &DerivedTestObject::Multiply
    );

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(6, 7), 42);
}

TEST(FastDelegateTest, DerivedMemberFunctionWorksThroughMakeDelegate)
{
    DerivedTestObject object;

    auto delegate = MakeDelegate(
        &object,
        &DerivedTestObject::Multiply
    );

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(6, 7), 42);
}

// =============================================================================
// DelegateMemento
// =============================================================================

TEST(FastDelegateTest, MementoCanRoundTripMemberDelegate)
{
    TestObject object;
    object.value = 10;

    FastDelegate<int(int, int)> original(
        &object,
        &TestObject::Add
    );

    DelegateMemento memento = original.GetMemento();

    FastDelegate<int(int, int)> restored;
    restored.SetMemento(memento);

    ASSERT_TRUE(restored);
    EXPECT_EQ(restored(1, 2), 13);
    EXPECT_EQ(restored, original);
}

TEST(FastDelegateTest, MementoCanRoundTripStaticDelegate)
{
    FastDelegate<int(int)> original(&Increment);

    DelegateMemento memento = original.GetMemento();

    FastDelegate<int(int)> restored;
    restored.SetMemento(memento);

    ASSERT_TRUE(restored);
    EXPECT_EQ(restored(41), 42);
    EXPECT_EQ(restored, original);
}

TEST(FastDelegateTest, EmptyMementoProducesEmptyDelegate)
{
    FastDelegate<int(int)> original;

    DelegateMemento memento = original.GetMemento();

    FastDelegate<int(int)> restored;
    restored.SetMemento(memento);

    EXPECT_TRUE(restored.empty());
}

TEST(FastDelegateTest, MementoCopyPreservesEquality)
{
    TestObject object;

    FastDelegate<int(int, int)> original(
        &object,
        &TestObject::Add
    );

    DelegateMemento first = original.GetMemento();
    DelegateMemento second = first;

    EXPECT_TRUE(first.IsEqual(second));
    EXPECT_EQ(first.Hash(), second.Hash());
}

// =============================================================================
// Rebinding
// =============================================================================

TEST(FastDelegateTest, RebindFromMemberFunctionToStaticFunction)
{
    TestObject object;
    object.value = 10;

    FastDelegate<int(int, int)> delegate(
        &object,
        &TestObject::Add
    );

    EXPECT_EQ(delegate(1, 2), 13);

    delegate.bind(&AddStatic);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(1, 2), 3);
}

TEST(FastDelegateTest, RebindFromStaticFunctionToMemberFunction)
{
    TestObject object;
    object.value = 10;

    FastDelegate<int(int, int)> delegate(&AddStatic);

    EXPECT_EQ(delegate(1, 2), 3);

    delegate.bind(&object, &TestObject::Add);

    ASSERT_TRUE(delegate);
    EXPECT_EQ(delegate(1, 2), 13);
}

// =============================================================================
// Multiple delegates / practical usage
// =============================================================================

TEST(FastDelegateTest, DelegatesCanBeStoredInVector)
{
    TestObject object1;
    TestObject object2;

    object1.value = 10;
    object2.value = 20;

    std::vector<FastDelegate<int(int, int)>> delegates;

    delegates.emplace_back(&object1, &TestObject::Add);
    delegates.emplace_back(&object2, &TestObject::Add);
    delegates.emplace_back(&AddStatic);

    ASSERT_EQ(delegates.size(), 3U);

    EXPECT_EQ(delegates[0](1, 2), 13);
    EXPECT_EQ(delegates[1](1, 2), 23);
    EXPECT_EQ(delegates[2](1, 2), 3);
}

TEST(FastDelegateTest, DelegatesRemainValidAfterContainerReallocation)
{
    TestObject object;
    object.value = 10;

    std::vector<FastDelegate<int(int, int)>> delegates;

    delegates.reserve(1);
    delegates.emplace_back(&object, &TestObject::Add);

    auto& first = delegates.front();

    delegates.emplace_back(&object, &TestObject::Add);
    delegates.emplace_back(&object, &TestObject::Add);
    delegates.emplace_back(&object, &TestObject::Add);

    EXPECT_EQ(first(1, 2), 13);
}

// =============================================================================
// Different signatures
// =============================================================================

TEST(FastDelegateTest, SupportsSingleArgument)
{
    FastDelegate<int(int)> delegate(&Increment);

    EXPECT_EQ(delegate(41), 42);
}

TEST(FastDelegateTest, SupportsMultipleArguments)
{
    FastDelegate<int(int, int)> delegate(&AddStatic);

    EXPECT_EQ(delegate(20, 22), 42);
}

TEST(FastDelegateTest, SupportsNoArguments)
{
    FastDelegate<int()> delegate(&ReturnFortyTwo);

    EXPECT_EQ(delegate(), 42);
}

// =============================================================================
// Static-function comparison with null
// =============================================================================

TEST(FastDelegateTest, StaticFunctionEqualityWithFunctionPointer)
{
    FastDelegate<int(int)> delegate(&Increment);

    EXPECT_TRUE(delegate == &Increment);
    EXPECT_FALSE(delegate != &Increment);
}

TEST(FastDelegateTest, EmptyDelegateComparesUnequalToStaticFunction)
{
    FastDelegate<int(int)> delegate;

    EXPECT_FALSE(delegate == &Increment);
    EXPECT_TRUE(delegate != &Increment);
}

TEST(FastDelegateTest, EmptyDelegateComparesEqualToNullFunctionPointer)
{
    FastDelegate<int(int)> delegate;

    using Function = int (*)(int);
    Function null_function = nullptr;

    EXPECT_TRUE(delegate == null_function);
    EXPECT_FALSE(delegate != null_function);
}
