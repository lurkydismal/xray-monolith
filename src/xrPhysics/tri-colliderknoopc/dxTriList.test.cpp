#include "../xrCore/xrCore.h"
#include "../ode_include.h"
#include "_std_extensions.h"
#include "dxTriList.h"

#include <gtest/gtest.h>

namespace
{
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
        dSpaceDestroy(space);
        space = nullptr;
    }

    dSpaceID space = nullptr;
};

void ExpectVectorEqual(
    const dVector3 actual,
    const dcVector3& expected)
{
    EXPECT_FLOAT_EQ(actual[0], expected.x);
    EXPECT_FLOAT_EQ(actual[1], expected.y);
    EXPECT_FLOAT_EQ(actual[2], expected.z);
}

#if 0
TEST_F(TriListTest, GetTriangleReturnsBuiltTriangle)
{
    const dcVector3 vertices[] =
    {
        dcVector3(1.0f, 2.0f, 3.0f),
        dcVector3(4.0f, 5.0f, 6.0f),
        dcVector3(7.0f, 8.0f, 9.0f),
    };

    const int indices[] =
    {
        0, 1, 2,
    };

    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

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

    ExpectVectorEqual(v0, vertices[0]);
    ExpectVectorEqual(v1, vertices[1]);
    ExpectVectorEqual(v2, vertices[2]);

    dGeomDestroy(geom);
}
#endif

#if 0
TEST_F(TriListTest, GetTriangleUsesIndices)
{
    const dcVector3 vertices[] =
    {
        dcVector3(10.0f, 11.0f, 12.0f),
        dcVector3(20.0f, 21.0f, 22.0f),
        dcVector3(30.0f, 31.0f, 32.0f),
        dcVector3(40.0f, 41.0f, 42.0f),
        dcVector3(50.0f, 51.0f, 52.0f),
        dcVector3(60.0f, 61.0f, 62.0f),
    };

    // Deliberately non-sequential.
    const int indices[] =
    {
        4, 1, 5,
    };

    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    dGeomTriListBuild(
        geom,
        vertices,
        6,
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

    ExpectVectorEqual(v0, vertices[4]);
    ExpectVectorEqual(v1, vertices[1]);
    ExpectVectorEqual(v2, vertices[5]);

    dGeomDestroy(geom);
}
#endif

#if 0
TEST_F(TriListTest, GetTriangleUsesTriangleIndex)
{
    const dcVector3 vertices[] =
    {
        dcVector3(1.0f,  1.0f,  1.0f),
        dcVector3(2.0f,  2.0f,  2.0f),
        dcVector3(3.0f,  3.0f,  3.0f),

        dcVector3(10.0f, 10.0f, 10.0f),
        dcVector3(20.0f, 20.0f, 20.0f),
        dcVector3(30.0f, 30.0f, 30.0f),
    };

    const int indices[] =
    {
        0, 1, 2,
        3, 4, 5,
    };

    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

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

    ExpectVectorEqual(v0, vertices[3]);
    ExpectVectorEqual(v1, vertices[4]);
    ExpectVectorEqual(v2, vertices[5]);

    dGeomDestroy(geom);
}
#endif

#if 0
TEST_F(TriListTest, GetTrianglePreservesVertexOrder)
{
    const dcVector3 vertices[] =
    {
        dcVector3(1.0f, 0.0f, 0.0f),
        dcVector3(0.0f, 1.0f, 0.0f),
        dcVector3(0.0f, 0.0f, 1.0f),
    };

    const int indices[] =
    {
        2, 0, 1,
    };

    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

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

    ExpectVectorEqual(v0, vertices[2]);
    ExpectVectorEqual(v1, vertices[0]);
    ExpectVectorEqual(v2, vertices[1]);

    dGeomDestroy(geom);
}
#endif

#if 0
TEST_F(TriListTest, GetTrianglePreservesFloatingPointCoordinates)
{
    const dcVector3 vertices[] =
    {
        dcVector3(-123.456f, 0.0001f, 9999.25f),
        dcVector3(1.0f / 3.0f, -42.75f, 0.125f),
        dcVector3(-0.5f, 123.75f, -987.625f),
    };

    const int indices[] =
    {
        0, 1, 2,
    };

    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

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

    ExpectVectorEqual(v0, vertices[0]);
    ExpectVectorEqual(v1, vertices[1]);
    ExpectVectorEqual(v2, vertices[2]);

    dGeomDestroy(geom);
}
#endif

#if 0
TEST_F(TriListTest, GetTriangleWorksForArbitrarilyIndexedMesh)
{
    const dcVector3 vertices[] =
    {
        dcVector3(100.0f, 100.0f, 100.0f),
        dcVector3(200.0f, 200.0f, 200.0f),
        dcVector3(300.0f, 300.0f, 300.0f),
        dcVector3(400.0f, 400.0f, 400.0f),
        dcVector3(500.0f, 500.0f, 500.0f),
        dcVector3(600.0f, 600.0f, 600.0f),
        dcVector3(700.0f, 700.0f, 700.0f),
    };

    const int indices[] =
    {
        6, 2, 4,
        1, 5, 0,
    };

    dGeomID geom = dCreateTriList(space, nullptr, nullptr);
    ASSERT_NE(geom, nullptr);

    dGeomTriListBuild(
        geom,
        vertices,
        7,
        indices,
        6
    );

    {
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

        ExpectVectorEqual(v0, vertices[6]);
        ExpectVectorEqual(v1, vertices[2]);
        ExpectVectorEqual(v2, vertices[4]);
    }

    {
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

        ExpectVectorEqual(v0, vertices[1]);
        ExpectVectorEqual(v1, vertices[5]);
        ExpectVectorEqual(v2, vertices[0]);
    }

    dGeomDestroy(geom);
}
#endif

TEST(DcVector3Test, StoresCoordinates)
{
    const dcVector3 v(1.0, 2.0, 3.0);

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(DcVector3Test, IndexAccess)
{
    const dcVector3 v(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
}

TEST(DcVector3Test, Addition)
{
    const dcVector3 a(1.0f, 2.0f, 3.0f);
    const dcVector3 b(4.0f, 5.0f, 6.0f);

    const dcVector3 result = a + b;

    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST(DcVector3Test, Subtraction)
{
    const dcVector3 a(5.0f, 7.0f, 9.0f);
    const dcVector3 b(1.0f, 2.0f, 3.0f);

    const dcVector3 result = a - b;

    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 5.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(DcVector3Test, Multiplication)
{
    const dcVector3 v(1.0f, 2.0f, 3.0f);

    const dcVector3 result = v * 2.0f;

    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(DcVector3Test, DotProduct)
{
    const dcVector3 a(1.0f, 2.0f, 3.0f);
    const dcVector3 b(4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(a.DotProduct(b), 32.0f);
}

TEST(DcVector3Test, CrossProduct)
{
    const dcVector3 a(1.0f, 0.0f, 0.0f);
    const dcVector3 b(0.0f, 1.0f, 0.0f);

    const dcVector3 result = a.CrossProduct(b);

    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 1.0f);
}

} // namespace
