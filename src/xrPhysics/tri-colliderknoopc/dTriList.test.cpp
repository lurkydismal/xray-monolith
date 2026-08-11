#include "../ode_include.h"
#include "dTriList.h"
#include <stdlib.h>
#include "../xrCore/_types.h"
#include "../xrCore/xrCore.h"
#include "../xrCDB/xrCDB.h"
#include "dTriCylinder.h"
#if 0
#include "dxTriList.h"
#include "dcTriListCollider.h"
#endif

#include <gtest/gtest.h>

dColliderFn* dTriListColliderFn(int num);
int dCollideBTL(dxGeom* TriList, dxGeom* Box, int Flags, dContactGeom* Contact, int Stride) throw();
int dCollideSTL(dxGeom* TriList, dxGeom* Sphere, int Flags, dContactGeom* Contact, int Stride) throw();
int dCollideCTL(dxGeom* TriList, dxGeom* Cyl, int Flags, dContactGeom* Contact, int Stride) throw();
int dAABBTestTL(dxGeom* TriList, dxGeom* Object, dReal AABB[6]) throw();

namespace
{

int TestTriangleCallback(dGeomID, dGeomID, int)
{
    return 42;
}

void TestArrayCallback(dGeomID, dGeomID, const int*, int)
{
}

class TriListTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        space = dHashSpaceCreate(nullptr);
        ASSERT_NE(space, nullptr);
    }

    void TearDown() override
    {
        if (space)
            dSpaceDestroy(space);
    }

    dSpaceID space = nullptr;
};

TEST_F(TriListTest, Create)
{
    dGeomID geom = dCreateTriList(
        space,
        nullptr,
        nullptr
    );

    ASSERT_NE(geom, nullptr);
    EXPECT_EQ(dGeomGetClass(geom), dTriListClass);

    dGeomDestroy(geom);
}

TEST_F(TriListTest, CreateWithCallbacks)
{
    dGeomID geom = dCreateTriList(
        space,
        &TestTriangleCallback,
        &TestArrayCallback
    );

    ASSERT_NE(geom, nullptr);

    EXPECT_EQ(
        dGeomTriListGetCallback(geom),
        &TestTriangleCallback
    );

    EXPECT_EQ(
        dGeomTriListGetArrayCallback(geom),
        &TestArrayCallback
    );

    dGeomDestroy(geom);
}

TEST_F(TriListTest, CallbackCanBeChanged)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    EXPECT_EQ(dGeomTriListGetCallback(geom), nullptr);

    dGeomTriListSetCallback(geom, &TestTriangleCallback);

    EXPECT_EQ(
        dGeomTriListGetCallback(geom),
        &TestTriangleCallback
    );

    dGeomTriListSetCallback(geom, nullptr);

    EXPECT_EQ(dGeomTriListGetCallback(geom), nullptr);

    dGeomDestroy(geom);
}

TEST_F(TriListTest, ArrayCallbackCanBeChanged)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    EXPECT_EQ(dGeomTriListGetArrayCallback(geom), nullptr);

    dGeomTriListSetArrayCallback(geom, &TestArrayCallback);

    EXPECT_EQ(
        dGeomTriListGetArrayCallback(geom),
        &TestArrayCallback
    );

    dGeomTriListSetArrayCallback(geom, nullptr);

    EXPECT_EQ(dGeomTriListGetArrayCallback(geom), nullptr);

    dGeomDestroy(geom);
}

TEST_F(TriListTest, IsAddedToSpace)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    EXPECT_EQ(dGeomGetSpace(geom), space);

    dGeomDestroy(geom);
}

TEST_F(TriListTest, CanBeRemovedFromSpace)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    EXPECT_EQ(dGeomGetSpace(geom), space);

    dSpaceRemove(space, geom);

    EXPECT_EQ(dGeomGetSpace(geom), nullptr);

    dGeomDestroy(geom);
}

TEST_F(TriListTest, CanBeCreatedWithoutSpace)
{
    dGeomID geom = dCreateTriList(
        nullptr,
        nullptr,
        nullptr
    );

    ASSERT_NE(geom, nullptr);
    EXPECT_EQ(dGeomGetSpace(geom), nullptr);

    dGeomDestroy(geom);
}

TEST_F(TriListTest, CallbackPointersAreStoredExactly)
{
    dGeomID geom = dCreateTriList(
        space,
        &TestTriangleCallback,
        &TestArrayCallback
    );

    ASSERT_NE(geom, nullptr);

    EXPECT_EQ(
        dGeomTriListGetCallback(geom),
        &TestTriangleCallback
    );

    EXPECT_EQ(
        dGeomTriListGetArrayCallback(geom),
        &TestArrayCallback
    );

    dGeomTriListSetCallback(geom, nullptr);
    dGeomTriListSetArrayCallback(geom, nullptr);

    EXPECT_EQ(dGeomTriListGetCallback(geom), nullptr);
    EXPECT_EQ(dGeomTriListGetArrayCallback(geom), nullptr);

    dGeomDestroy(geom);
}

#if 0
TEST_F(TriListTest, BuildAndGetTriangle)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    const dcVector3 vertices[] =
    {
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
    };

    const int indices[] =
    {
        0, 1, 2
    };

    dGeomTriListBuild(
        geom,
        vertices,
        3,
        indices,
        3
    );

    dVector3 v0;
    dVector3 v1;
    dVector3 v2;

    dGeomTriListGetTriangle(
        geom,
        0,
        &v0,
        &v1,
        &v2
    );

    EXPECT_FLOAT_EQ(v0[0], 0.0f);
    EXPECT_FLOAT_EQ(v0[1], 0.0f);
    EXPECT_FLOAT_EQ(v0[2], 0.0f);

    EXPECT_FLOAT_EQ(v1[0], 1.0f);
    EXPECT_FLOAT_EQ(v1[1], 0.0f);
    EXPECT_FLOAT_EQ(v1[2], 0.0f);

    EXPECT_FLOAT_EQ(v2[0], 0.0f);
    EXPECT_FLOAT_EQ(v2[1], 1.0f);
    EXPECT_FLOAT_EQ(v2[2], 0.0f);

    dGeomDestroy(geom);
}
#endif

#if 0
TEST_F(TriListTest, GetTriangleUsesIndices)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    const dcVector3 vertices[] =
    {
        { 10.0f, 11.0f, 12.0f },
        { 20.0f, 21.0f, 22.0f },
        { 30.0f, 31.0f, 32.0f },
        { 40.0f, 41.0f, 42.0f },
    };

    const int indices[] =
    {
        3, 1, 2
    };

    dGeomTriListBuild(
        geom,
        vertices,
        4,
        indices,
        3
    );

    dVector3 v0;
    dVector3 v1;
    dVector3 v2;

    dGeomTriListGetTriangle(
        geom,
        0,
        &v0,
        &v1,
        &v2
    );

    EXPECT_FLOAT_EQ(v0[0], 40.0f);
    EXPECT_FLOAT_EQ(v0[1], 41.0f);
    EXPECT_FLOAT_EQ(v0[2], 42.0f);

    EXPECT_FLOAT_EQ(v1[0], 20.0f);
    EXPECT_FLOAT_EQ(v1[1], 21.0f);
    EXPECT_FLOAT_EQ(v1[2], 22.0f);

    EXPECT_FLOAT_EQ(v2[0], 30.0f);
    EXPECT_FLOAT_EQ(v2[1], 31.0f);
    EXPECT_FLOAT_EQ(v2[2], 32.0f);

    dGeomDestroy(geom);
}
#endif

#if 0
TEST_F(TriListTest, GetMultipleTriangles)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    const dcVector3 vertices[] =
    {
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },

        { 10.0f, 10.0f, 10.0f },
        { 20.0f, 20.0f, 20.0f },
        { 30.0f, 30.0f, 30.0f },
    };

    const int indices[] =
    {
        0, 1, 2,
        3, 4, 5,
    };

    dGeomTriListBuild(
        geom,
        vertices,
        6,
        indices,
        6
    );

    dVector3 v0;
    dVector3 v1;
    dVector3 v2;

    dGeomTriListGetTriangle(
        geom,
        1,
        &v0,
        &v1,
        &v2
    );

    EXPECT_FLOAT_EQ(v0[0], 10.0f);
    EXPECT_FLOAT_EQ(v0[1], 10.0f);
    EXPECT_FLOAT_EQ(v0[2], 10.0f);

    EXPECT_FLOAT_EQ(v1[0], 20.0f);
    EXPECT_FLOAT_EQ(v1[1], 20.0f);
    EXPECT_FLOAT_EQ(v1[2], 20.0f);

    EXPECT_FLOAT_EQ(v2[0], 30.0f);
    EXPECT_FLOAT_EQ(v2[1], 30.0f);
    EXPECT_FLOAT_EQ(v2[2], 30.0f);

    dGeomDestroy(geom);
}
#endif

TEST_F(TriListTest, ColliderFunctionForBox)
{
    ASSERT_NE(
        dTriListColliderFn(dBoxClass),
        nullptr
    );
}

TEST_F(TriListTest, ColliderFunctionForSphere)
{
    ASSERT_NE(
        dTriListColliderFn(dSphereClass),
        nullptr
    );
}

TEST_F(TriListTest, ColliderFunctionForCylinder)
{
    ASSERT_NE(
        dTriListColliderFn(dCylinderClassUser),
        nullptr
    );
}

TEST_F(TriListTest, ColliderFunctionForUnsupportedClassIsNull)
{
    constexpr int unsupportedClass = 0x7fffffff;

    EXPECT_EQ(
        dTriListColliderFn(unsupportedClass),
        nullptr
    );
}

TEST_F(TriListTest, ColliderFunctionMapping)
{
    EXPECT_EQ(
        dTriListColliderFn(dBoxClass),
        reinterpret_cast<dColliderFn*>(&dCollideBTL)
    );

    EXPECT_EQ(
        dTriListColliderFn(dSphereClass),
        reinterpret_cast<dColliderFn*>(&dCollideSTL)
    );

    EXPECT_EQ(
        dTriListColliderFn(dCylinderClassUser),
        reinterpret_cast<dColliderFn*>(&dCollideCTL)
    );
}

TEST_F(TriListTest, AABBTestAlwaysSucceeds)
{
    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    dReal aabb[6] =
    {
        100.0,
        101.0,
        200.0,
        201.0,
        300.0,
        301.0,
    };

    EXPECT_EQ(
        dAABBTestTL(
            static_cast<dxGeom*>(geom),
            nullptr,
            aabb
        ),
        1
    );

    dGeomDestroy(geom);
}

}
