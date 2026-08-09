#include "stdafx.h"

#include "xr_resource.h"

#include <gtest/gtest.h>

#include <atomic>
#include <type_traits>


namespace
{

class TestResource : public xr_resource
{
public:
    static inline int constructions = 0;
    static inline int destructions = 0;

    int value = 0;

    TestResource()
    {
        ++constructions;
    }

    explicit TestResource(int v) : value(v)
    {
        ++constructions;
    }

    ~TestResource()
    {
        ++destructions;
    }

    static void ResetCounters()
    {
        constructions = 0;
        destructions = 0;
    }
};


class TestNamedResource : public xr_resource_named
{
public:
    static inline int destructions = 0;

    ~TestNamedResource()
    {
        ++destructions;
    }

    static void ResetCounters()
    {
        destructions = 0;
    }
};


class XrResourceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        TestResource::ResetCounters();
        TestNamedResource::ResetCounters();
    }
};

} // namespace


// -----------------------------------------------------------------------------
// xr_resource
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, DefaultConstruction)
{
    xr_resource resource;

    EXPECT_EQ(resource.dwReference.load(), 0u);
}

TEST_F(XrResourceTest, CopyConstructionResetsReferenceCount)
{
    xr_resource original;

    original.dwReference.store(42);

    xr_resource copy(original);

    EXPECT_EQ(original.dwReference.load(), 42u);
    EXPECT_EQ(copy.dwReference.load(), 0u);
}

TEST_F(XrResourceTest, AssignmentDoesNotChangeReferenceCount)
{
    xr_resource original;
    xr_resource destination;

    original.dwReference.store(42);
    destination.dwReference.store(17);

    destination = original;

    EXPECT_EQ(original.dwReference.load(), 42u);
    EXPECT_EQ(destination.dwReference.load(), 17u);
}


// -----------------------------------------------------------------------------
// xr_resource_flagged
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, FlaggedResourceDefaultValues)
{
    xr_resource_flagged resource;

    EXPECT_EQ(resource.dwReference.load(), 0u);
    EXPECT_EQ(resource.dwFlags, 0u);
}

TEST_F(XrResourceTest, FlaggedResourceFieldsCanBeModified)
{
    xr_resource_flagged resource;

    resource.dwFlags = xr_resource_flagged::RF_REGISTERED;
    resource.skinning = 42;
    resource.hud_disabled = true;

    EXPECT_EQ(resource.dwFlags, xr_resource_flagged::RF_REGISTERED);
    EXPECT_EQ(resource.skinning, 42);
    EXPECT_TRUE(resource.hud_disabled);
}


// -----------------------------------------------------------------------------
// xr_resource_named
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, NamedResourceDefaultName)
{
    xr_resource_named resource;

    EXPECT_TRUE(resource.cName.empty());
}

TEST_F(XrResourceTest, SetName)
{
    xr_resource_named resource;

    const char* result = resource.set_name("test_resource");

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "test_resource");
    EXPECT_STREQ(resource.cName.c_str(), "test_resource");
}

TEST_F(XrResourceTest, SetNameReplacesPreviousName)
{
    xr_resource_named resource;

    EXPECT_STREQ(resource.set_name("first"), "first");
    EXPECT_STREQ(resource.set_name("second"), "second");

    EXPECT_STREQ(resource.cName.c_str(), "second");
}

TEST_F(XrResourceTest, SetEmptyName)
{
    xr_resource_named resource;

    const char* result = resource.set_name("");

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
    EXPECT_TRUE(resource.cName.empty());
}


// -----------------------------------------------------------------------------
// resptr_base
//
// resptr_base is protected through resptr_core below. These tests focus on
// externally observable reference-counting behavior.
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, ResourceStartsWithZeroReferences)
{
    auto* resource = new TestResource;

    EXPECT_EQ(resource->dwReference.load(), 0u);

    delete resource;
}

TEST_F(XrResourceTest, ConstructionWithPointerIncrementsReference)
{
    auto* resource = new TestResource;

    EXPECT_EQ(resource->dwReference.load(), 0u);

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

        EXPECT_EQ(resource->dwReference.load(), 1u);
        EXPECT_EQ(ptr._get(), resource);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, ConstructionWithAddRefFalseDoesNotIncrement)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(
            resource,
            false);

        EXPECT_EQ(resource->dwReference.load(), 0u);

        // ptr does not own a reference, so its destructor must not delete
        // the resource.
    }

    EXPECT_EQ(TestResource::destructions, 0);

    delete resource;

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, CopyConstructionIncrementsReference)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(resource);

        EXPECT_EQ(resource->dwReference.load(), 1u);

        {
            resptr_core<TestResource, resptr_base<TestResource>> second(first);

            EXPECT_EQ(resource->dwReference.load(), 2u);
            EXPECT_EQ(first._get(), resource);
            EXPECT_EQ(second._get(), resource);
        }

        EXPECT_EQ(resource->dwReference.load(), 1u);
        EXPECT_EQ(TestResource::destructions, 0);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, DestructionDecrementsReference)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(resource);

        EXPECT_EQ(resource->dwReference.load(), 1u);

        {
            resptr_core<TestResource, resptr_base<TestResource>> second(first);

            EXPECT_EQ(resource->dwReference.load(), 2u);
        }

        EXPECT_EQ(resource->dwReference.load(), 1u);
        EXPECT_EQ(TestResource::destructions, 0);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, LastReferenceDeletesResource)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

        EXPECT_EQ(resource->dwReference.load(), 1u);
        EXPECT_EQ(TestResource::destructions, 0);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, MultipleReferencesDeleteOnlyOnce)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> a(resource);
        resptr_core<TestResource, resptr_base<TestResource>> b(a);
        resptr_core<TestResource, resptr_base<TestResource>> c(b);

        EXPECT_EQ(resource->dwReference.load(), 3u);
        EXPECT_EQ(TestResource::destructions, 0);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}


// -----------------------------------------------------------------------------
// Default construction
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, DefaultResptrIsNull)
{
    resptr_core<TestResource, resptr_base<TestResource>> ptr;

    EXPECT_EQ(ptr._get(), nullptr);
    EXPECT_TRUE(!ptr);
    EXPECT_TRUE(ptr.operator!());
}

TEST_F(XrResourceTest, DefaultResptrConvertsToFalse)
{
    resptr_core<TestResource, resptr_base<TestResource>> ptr;

    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(XrResourceTest, NonNullResptrConvertsToTrue)
{
    auto* resource = new TestResource;

    resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_FALSE(!ptr);
}


// -----------------------------------------------------------------------------
// Access
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, DereferenceOperator)
{
    auto* resource = new TestResource(123);

    resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

    EXPECT_EQ(&*ptr, resource);
    EXPECT_EQ((*ptr).value, 123);
}

TEST_F(XrResourceTest, ArrowOperator)
{
    auto* resource = new TestResource(123);

    resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

    EXPECT_EQ(ptr->value, 123);
}

TEST_F(XrResourceTest, GetReturnsUnderlyingPointer)
{
    auto* resource = new TestResource;

    resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

    EXPECT_EQ(ptr._get(), resource);
}


// -----------------------------------------------------------------------------
// Assignment
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, AssignmentIncrementsNewReference)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(resource);
        resptr_core<TestResource, resptr_base<TestResource>> second;

        EXPECT_EQ(resource->dwReference.load(), 1u);

        second = first;

        EXPECT_EQ(resource->dwReference.load(), 2u);
        EXPECT_EQ(second._get(), resource);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, AssignmentReleasesOldReference)
{
    auto* firstResource = new TestResource(1);
    auto* secondResource = new TestResource(2);

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(firstResource);

        EXPECT_EQ(firstResource->dwReference.load(), 1u);
        EXPECT_EQ(secondResource->dwReference.load(), 0u);

        ptr._set(secondResource);

        EXPECT_EQ(firstResource->dwReference.load(), 0u);
        EXPECT_EQ(secondResource->dwReference.load(), 1u);

        EXPECT_EQ(TestResource::destructions, 1);
        EXPECT_EQ(ptr._get(), secondResource);
    }

    EXPECT_EQ(TestResource::destructions, 2);
}

TEST_F(XrResourceTest, SelfAssignmentPreservesReference)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

        EXPECT_EQ(resource->dwReference.load(), 1u);

        ptr = ptr;

        EXPECT_EQ(ptr._get(), resource);
        EXPECT_EQ(resource->dwReference.load(), 1u);
        EXPECT_EQ(TestResource::destructions, 0);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, AssignmentFromEmptyPointerClearsPointer)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);
        resptr_core<TestResource, resptr_base<TestResource>> empty;

        ptr = empty;

        EXPECT_EQ(ptr._get(), nullptr);
        EXPECT_FALSE(static_cast<bool>(ptr));
        EXPECT_EQ(TestResource::destructions, 1);
    }
}


// -----------------------------------------------------------------------------
// _set
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, SetNullClearsPointer)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

        ptr._set(static_cast<TestResource*>(nullptr));

        EXPECT_EQ(ptr._get(), nullptr);
        EXPECT_EQ(TestResource::destructions, 1);
    }
}

TEST_F(XrResourceTest, SetSamePointerPreservesSingleReference)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

        EXPECT_EQ(resource->dwReference.load(), 1u);

        ptr._set(resource);

        EXPECT_EQ(ptr._get(), resource);
        EXPECT_EQ(resource->dwReference.load(), 1u);
        EXPECT_EQ(TestResource::destructions, 0);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, SetFromAnotherResptr)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(resource);
        resptr_core<TestResource, resptr_base<TestResource>> second;

        second._set(first);

        EXPECT_EQ(first._get(), resource);
        EXPECT_EQ(second._get(), resource);
        EXPECT_EQ(resource->dwReference.load(), 2u);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}


// -----------------------------------------------------------------------------
// _clear
//
// _clear() is deliberately tested as a raw pointer clear rather than an
// ownership release because that is what the current implementation does.
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, ClearMakesPointerNull)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

        EXPECT_EQ(ptr._get(), resource);
        EXPECT_EQ(resource->dwReference.load(), 1u);

        ptr._clear();

        EXPECT_EQ(ptr._get(), nullptr);
    }

    // Current implementation of _clear() does NOT decrement the reference.
    // The object therefore remains alive and has to be manually deleted here.
    EXPECT_EQ(TestResource::destructions, 0);

    EXPECT_EQ(resource->dwReference.load(), 1u);

    resource->dwReference.store(0);
    delete resource;

    EXPECT_EQ(TestResource::destructions, 1);
}


// -----------------------------------------------------------------------------
// swap
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, SwapExchangesPointers)
{
    auto* firstResource = new TestResource(1);
    auto* secondResource = new TestResource(2);

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(firstResource);
        resptr_core<TestResource, resptr_base<TestResource>> second(secondResource);

        EXPECT_EQ(first._get(), firstResource);
        EXPECT_EQ(second._get(), secondResource);

        first.swap(second);

        EXPECT_EQ(first._get(), secondResource);
        EXPECT_EQ(second._get(), firstResource);

        EXPECT_EQ(first->value, 2);
        EXPECT_EQ(second->value, 1);

        EXPECT_EQ(firstResource->dwReference.load(), 1u);
        EXPECT_EQ(secondResource->dwReference.load(), 1u);
    }

    EXPECT_EQ(TestResource::destructions, 2);
}

TEST_F(XrResourceTest, SwapWithEmptyPointer)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(resource);
        resptr_core<TestResource, resptr_base<TestResource>> second;

        first.swap(second);

        EXPECT_EQ(first._get(), nullptr);
        EXPECT_EQ(second._get(), resource);

        EXPECT_EQ(resource->dwReference.load(), 1u);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, FreeSwapExchangesPointers)
{
    auto* firstResource = new TestResource(1);
    auto* secondResource = new TestResource(2);

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(firstResource);
        resptr_core<TestResource, resptr_base<TestResource>> second(secondResource);

        swap(first, second);

        EXPECT_EQ(first._get(), secondResource);
        EXPECT_EQ(second._get(), firstResource);
    }

    EXPECT_EQ(TestResource::destructions, 2);
}


// -----------------------------------------------------------------------------
// Comparisons
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, EqualPointersCompareEqual)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(resource);
        resptr_core<TestResource, resptr_base<TestResource>> second(first);

        EXPECT_TRUE(first == second);
        EXPECT_FALSE(first != second);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, EmptyPointersCompareEqual)
{
    resptr_core<TestResource, resptr_base<TestResource>> first;
    resptr_core<TestResource, resptr_base<TestResource>> second;

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);
}

TEST_F(XrResourceTest, DifferentPointersCompareNotEqual)
{
    auto* firstResource = new TestResource;
    auto* secondResource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(firstResource);
        resptr_core<TestResource, resptr_base<TestResource>> second(secondResource);

        EXPECT_FALSE(first == second);
        EXPECT_TRUE(first != second);
    }

    EXPECT_EQ(TestResource::destructions, 2);
}

TEST_F(XrResourceTest, PointerComparison)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> ptr(resource);

        EXPECT_TRUE(ptr == resource);
        EXPECT_TRUE(resource == ptr);

        EXPECT_FALSE(ptr != resource);
        EXPECT_FALSE(resource != ptr);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, NullPointerComparison)
{
    resptr_core<TestResource, resptr_base<TestResource>> ptr;

    EXPECT_TRUE(ptr == static_cast<TestResource*>(nullptr));
    EXPECT_TRUE(static_cast<TestResource*>(nullptr) == ptr);

    EXPECT_FALSE(ptr != static_cast<TestResource*>(nullptr));
    EXPECT_FALSE(static_cast<TestResource*>(nullptr) != ptr);
}

TEST_F(XrResourceTest, LessThanIsBasedOnPointerOrdering)
{
    auto* firstResource = new TestResource;
    auto* secondResource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(firstResource);
        resptr_core<TestResource, resptr_base<TestResource>> second(secondResource);

        const bool expectedLess =
            std::less<TestResource*>()(firstResource, secondResource);

        EXPECT_EQ(first < second, expectedLess);
    }

    EXPECT_EQ(TestResource::destructions, 2);
}

TEST_F(XrResourceTest, GreaterThanIsBasedOnPointerOrdering)
{
    auto* firstResource = new TestResource;
    auto* secondResource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> first(firstResource);
        resptr_core<TestResource, resptr_base<TestResource>> second(secondResource);

        const bool expectedGreater =
            std::less<TestResource*>()(secondResource, firstResource);

        EXPECT_EQ(first > second, expectedGreater);
    }

    EXPECT_EQ(TestResource::destructions, 2);
}


// -----------------------------------------------------------------------------
// Reference count invariants
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, ReferenceCountTracksNumberOfOwningPointers)
{
    auto* resource = new TestResource;

    {
        resptr_core<TestResource, resptr_base<TestResource>> a(resource);
        EXPECT_EQ(resource->dwReference.load(), 1u);

        resptr_core<TestResource, resptr_base<TestResource>> b(a);
        EXPECT_EQ(resource->dwReference.load(), 2u);

        resptr_core<TestResource, resptr_base<TestResource>> c(b);
        EXPECT_EQ(resource->dwReference.load(), 3u);

        c = a;
        EXPECT_EQ(resource->dwReference.load(), 3u);

        b = resptr_core<TestResource, resptr_base<TestResource>>();
        EXPECT_EQ(resource->dwReference.load(), 2u);
    }

    EXPECT_EQ(TestResource::destructions, 1);
}

TEST_F(XrResourceTest, ReferenceCountUsesAtomicStorage)
{
    static_assert(
        std::is_same_v<
            decltype(TestResource::dwReference),
            xr_atomic_u32>);

    TestResource resource;

    resource.dwReference.store(123);

    EXPECT_EQ(resource.dwReference.load(), 123u);
}


// -----------------------------------------------------------------------------
// Named resource through resptr_core
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, NamedResourceWorksWithResptr)
{
    auto* resource = new TestNamedResource;

    {
        resptr_core<
            TestNamedResource,
            resptr_base<TestNamedResource>> ptr(resource);

        ASSERT_NE(ptr._get(), nullptr);

        ptr->set_name("example");

        EXPECT_STREQ(ptr->cName.c_str(), "example");
        EXPECT_EQ(resource->dwReference.load(), 1u);
    }

    EXPECT_EQ(TestNamedResource::destructions, 1);
}


// -----------------------------------------------------------------------------
// Resource flags
// -----------------------------------------------------------------------------

TEST_F(XrResourceTest, RegisteredFlagValue)
{
    EXPECT_EQ(xr_resource::RF_REGISTERED, 1);
    EXPECT_EQ(xr_resource_flagged::RF_REGISTERED, 1);
}

TEST_F(XrResourceTest, RegisteredFlagCanBeStored)
{
    xr_resource_flagged resource;

    resource.dwFlags |= xr_resource_flagged::RF_REGISTERED;

    EXPECT_NE(
        resource.dwFlags & xr_resource_flagged::RF_REGISTERED,
        0u);
}
