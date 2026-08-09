#include "stdafx.h"

#include "_type_traits.h"

#include <gtest/gtest.h>

namespace
{
    struct EmptyStruct
    {
    };

    class EmptyClass
    {
    };

    struct NonPolymorphicBase
    {
        void Function() {}
    };

    struct NonPolymorphicDerived : NonPolymorphicBase
    {
    };

    struct PolymorphicBase
    {
        virtual ~PolymorphicBase() = default;
    };

    struct PolymorphicDerived : PolymorphicBase
    {
    };

    struct PolymorphicWithVirtualFunction
    {
        virtual void Function() {}
    };

    union TestUnion
    {
        int integer;
        float floating;
    };

    enum TestEnum
    {
        TestEnumValue
    };

    enum class TestEnumClass
    {
        Value
    };
}

// -----------------------------------------------------------------------------
// is_class
// -----------------------------------------------------------------------------

TEST(TypeTraitsTest, IsClassRecognizesClass)
{
    EXPECT_TRUE((is_class<EmptyClass>::result));
}

TEST(TypeTraitsTest, IsClassRecognizesStruct)
{
    EXPECT_TRUE((is_class<EmptyStruct>::result));
}

TEST(TypeTraitsTest, IsClassRecognizesDerivedClass)
{
    EXPECT_TRUE((is_class<NonPolymorphicDerived>::result));
}

TEST(TypeTraitsTest, IsClassRejectsVoid)
{
    EXPECT_FALSE((is_class<void>::result));
}

TEST(TypeTraitsTest, IsClassRejectsIntegralTypes)
{
    EXPECT_FALSE((is_class<bool>::result));
    EXPECT_FALSE((is_class<char>::result));
    EXPECT_FALSE((is_class<signed char>::result));
    EXPECT_FALSE((is_class<unsigned char>::result));
    EXPECT_FALSE((is_class<short>::result));
    EXPECT_FALSE((is_class<unsigned short>::result));
    EXPECT_FALSE((is_class<int>::result));
    EXPECT_FALSE((is_class<unsigned int>::result));
    EXPECT_FALSE((is_class<long>::result));
    EXPECT_FALSE((is_class<unsigned long>::result));
    EXPECT_FALSE((is_class<long long>::result));
    EXPECT_FALSE((is_class<unsigned long long>::result));
}

TEST(TypeTraitsTest, IsClassRejectsFloatingPointTypes)
{
    EXPECT_FALSE((is_class<float>::result));
    EXPECT_FALSE((is_class<double>::result));
    EXPECT_FALSE((is_class<long double>::result));
}

TEST(TypeTraitsTest, IsClassRejectsPointers)
{
    EXPECT_FALSE((is_class<void*>::result));
    EXPECT_FALSE((is_class<int*>::result));
    EXPECT_FALSE((is_class<EmptyClass*>::result));
    EXPECT_FALSE((is_class<PolymorphicBase*>::result));
}

TEST(TypeTraitsTest, IsClassRejectsReferences)
{
    EXPECT_FALSE((is_class<int&>::result));
    EXPECT_FALSE((is_class<EmptyClass&>::result));
    EXPECT_FALSE((is_class<const EmptyClass&>::result));
}

TEST(TypeTraitsTest, IsClassRejectsArrays)
{
    EXPECT_FALSE((is_class<int[4]>::result));
    EXPECT_FALSE((is_class<EmptyClass[4]>::result));
}

TEST(TypeTraitsTest, IsClassRejectsEnums)
{
    EXPECT_FALSE((is_class<TestEnum>::result));
    EXPECT_FALSE((is_class<TestEnumClass>::result));
}

TEST(TypeTraitsTest, IsClassRejectsUnion)
{
    EXPECT_FALSE((is_class<TestUnion>::result));
}

// -----------------------------------------------------------------------------
// is_pm_class
// -----------------------------------------------------------------------------

TEST(TypeTraitsTest, IsPmClassRecognizesNonPolymorphicClass)
{
    EXPECT_FALSE((is_pm_class<EmptyClass>::result));
}

TEST(TypeTraitsTest, IsPmClassRecognizesNonPolymorphicStruct)
{
    EXPECT_FALSE((is_pm_class<NonPolymorphicBase>::result));
}

TEST(TypeTraitsTest, IsPmClassRecognizesPolymorphicBase)
{
    EXPECT_TRUE((is_pm_class<PolymorphicBase>::result));
}

TEST(TypeTraitsTest, IsPmClassRecognizesClassWithVirtualFunction)
{
    EXPECT_TRUE((is_pm_class<PolymorphicWithVirtualFunction>::result));
}

TEST(TypeTraitsTest, IsPmClassRecognizesPolymorphicDerivedClass)
{
    EXPECT_TRUE((is_pm_class<PolymorphicDerived>::result));
}

TEST(TypeTraitsTest, IsPmClassRecognizesNonPolymorphicDerivedClass)
{
    EXPECT_FALSE((is_pm_class<NonPolymorphicDerived>::result));
}

// -----------------------------------------------------------------------------
// is_polymorphic
// -----------------------------------------------------------------------------

TEST(TypeTraitsTest, IsPolymorphicRecognizesPolymorphicClass)
{
    EXPECT_TRUE((is_polymorphic<PolymorphicBase>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRecognizesVirtualFunction)
{
    EXPECT_TRUE((is_polymorphic<PolymorphicWithVirtualFunction>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRecognizesPolymorphicDerivedClass)
{
    EXPECT_TRUE((is_polymorphic<PolymorphicDerived>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsNonPolymorphicClass)
{
    EXPECT_FALSE((is_polymorphic<EmptyClass>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsNonPolymorphicDerivedClass)
{
    EXPECT_FALSE((is_polymorphic<NonPolymorphicDerived>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsVoid)
{
    EXPECT_FALSE((is_polymorphic<void>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsFundamentalTypes)
{
    EXPECT_FALSE((is_polymorphic<bool>::result));
    EXPECT_FALSE((is_polymorphic<char>::result));
    EXPECT_FALSE((is_polymorphic<int>::result));
    EXPECT_FALSE((is_polymorphic<unsigned int>::result));
    EXPECT_FALSE((is_polymorphic<float>::result));
    EXPECT_FALSE((is_polymorphic<double>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsPointers)
{
    EXPECT_FALSE((is_polymorphic<int*>::result));
    EXPECT_FALSE((is_polymorphic<EmptyClass*>::result));
    EXPECT_FALSE((is_polymorphic<PolymorphicBase*>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsReferences)
{
    EXPECT_FALSE((is_polymorphic<int&>::result));
    EXPECT_FALSE((is_polymorphic<EmptyClass&>::result));
    EXPECT_FALSE((is_polymorphic<PolymorphicBase&>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsEnums)
{
    EXPECT_FALSE((is_polymorphic<TestEnum>::result));
    EXPECT_FALSE((is_polymorphic<TestEnumClass>::result));
}

TEST(TypeTraitsTest, IsPolymorphicRejectsUnion)
{
    EXPECT_FALSE((is_polymorphic<TestUnion>::result));
}

// -----------------------------------------------------------------------------
// is_pm_classify
// -----------------------------------------------------------------------------

TEST(TypeTraitsTest, IsPmClassifyTrueUsesPolymorphismTrait)
{
    EXPECT_FALSE(
        (is_pm_classify<true>::template _detail<EmptyClass>::result));

    EXPECT_TRUE(
        (is_pm_classify<true>::template _detail<PolymorphicBase>::result));
}

TEST(TypeTraitsTest, IsPmClassifyFalseAlwaysReturnsFalse)
{
    EXPECT_FALSE(
        (is_pm_classify<false>::template _detail<EmptyClass>::result));

    EXPECT_FALSE(
        (is_pm_classify<false>::template _detail<PolymorphicBase>::result));

    EXPECT_FALSE(
        (is_pm_classify<false>::template _detail<int>::result));
}
