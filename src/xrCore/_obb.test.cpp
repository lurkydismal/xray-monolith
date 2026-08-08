#include "stdafx.h"

#include "_obb.h"

#include <gtest/gtest.h>

namespace
{
    using OBB = Fobb;
    using Vec = Fvector;
    using Matrix = Fmatrix;

    constexpr float EPSILON = 1e-5f;

    void expect_vec_near(const Vec& actual, const Vec& expected, float eps = EPSILON)
    {
        EXPECT_NEAR(actual.x, expected.x, eps);
        EXPECT_NEAR(actual.y, expected.y, eps);
        EXPECT_NEAR(actual.z, expected.z, eps);
    }

    void expect_vec_near(
        const Vec& actual,
        float x,
        float y,
        float z,
        float eps = EPSILON)
    {
        EXPECT_NEAR(actual.x, x, eps);
        EXPECT_NEAR(actual.y, y, eps);
        EXPECT_NEAR(actual.z, z, eps);
    }

    OBB make_obb(
        const Vec& center,
        const Vec& halfsize)
    {
        OBB box;
        box.identity();
        box.m_translate = center;
        box.m_halfsize = halfsize;
        return box;
    }

    OBB make_obb(
        float cx, float cy, float cz,
        float hx, float hy, float hz)
    {
        return make_obb(
            Vec{cx, cy, cz},
            Vec{hx, hy, hz});
    }

    void expect_matrix_transform_matches(
        const OBB& box,
        const Matrix& matrix)
    {
        Matrix actual;
        box.xform_get(actual);

        // xform_get() is supposed to represent rotation + translation,
        // not the half-size scaling.
        Vec source = {1.0f, 2.0f, 3.0f};

        Vec expected_result;
        Vec actual_result;

        matrix.transform_tiny(expected_result, source);
        actual.transform_tiny(actual_result, source);

        expect_vec_near(actual_result, expected_result);
    }
}


// -----------------------------------------------------------------------------
// Basic state
// -----------------------------------------------------------------------------

TEST(Fobb, Invalidate)
{
    OBB box;

    EXPECT_EQ(&box.invalidate(), &box);

    EXPECT_TRUE(box.m_rotate.i.similar(Fvector{1, 0, 0}));
    EXPECT_TRUE(box.m_rotate.j.similar(Fvector{0, 1, 0}));
    EXPECT_TRUE(box.m_rotate.k.similar(Fvector{0, 0, 1}));

    expect_vec_near(box.m_translate, 0, 0, 0);
    expect_vec_near(box.m_halfsize, 0, 0, 0);
}


TEST(Fobb, Identity)
{
    OBB box;

    EXPECT_EQ(&box.identity(), &box);

    expect_vec_near(box.m_translate, 0, 0, 0);
    expect_vec_near(box.m_halfsize, 0.5f, 0.5f, 0.5f);

    EXPECT_TRUE(box.contains(Vec{0, 0, 0}));
}


TEST(Fobb, IdentityContainsExpectedBounds)
{
    OBB box;
    box.identity();

    EXPECT_TRUE(box.contains(Vec{0.5f, 0, 0}));
    EXPECT_TRUE(box.contains(Vec{-0.5f, 0, 0}));
    EXPECT_TRUE(box.contains(Vec{0, 0.5f, 0}));
    EXPECT_TRUE(box.contains(Vec{0, -0.5f, 0}));
    EXPECT_TRUE(box.contains(Vec{0, 0, 0.5f}));
    EXPECT_TRUE(box.contains(Vec{0, 0, -0.5f}));

    EXPECT_FALSE(box.contains(Vec{0.50001f, 0, 0}));
    EXPECT_FALSE(box.contains(Vec{0, 0.50001f, 0}));
    EXPECT_FALSE(box.contains(Vec{0, 0, 0.50001f}));
}


// -----------------------------------------------------------------------------
// xform_get / xform_set
// -----------------------------------------------------------------------------

TEST(Fobb, XformGetIdentity)
{
    OBB box;
    box.identity();

    Matrix matrix;
    box.xform_get(matrix);

    EXPECT_TRUE(matrix.i.similar(Vec{1, 0, 0}));
    EXPECT_TRUE(matrix.j.similar(Vec{0, 1, 0}));
    EXPECT_TRUE(matrix.k.similar(Vec{0, 0, 1}));
    EXPECT_TRUE(matrix.c.similar(Vec{0, 0, 0}));

    EXPECT_FLOAT_EQ(matrix._14_, 0.0f);
    EXPECT_FLOAT_EQ(matrix._24_, 0.0f);
    EXPECT_FLOAT_EQ(matrix._34_, 0.0f);
    EXPECT_FLOAT_EQ(matrix._44_, 1.0f);
}


TEST(Fobb, XformGetContainsRotationAndTranslation)
{
    OBB box;
    box.identity();

    Matrix source;
    source.identity();

    // 90-degree rotation around Z:
    // i = (0, 1, 0)
    // j = (-1, 0, 0)
    // k = (0, 0, 1)
    source.i.set(0.0f, 1.0f, 0.0f);
    source.j.set(-1.0f, 0.0f, 0.0f);
    source.k.set(0.0f, 0.0f, 1.0f);
    source.c.set(10.0f, 20.0f, 30.0f);

    box.xform_set(source);

    Matrix result;
    box.xform_get(result);

    EXPECT_TRUE(result.i.similar(source.i));
    EXPECT_TRUE(result.j.similar(source.j));
    EXPECT_TRUE(result.k.similar(source.k));
    EXPECT_TRUE(result.c.similar(source.c));

    EXPECT_FLOAT_EQ(result._14_, 0.0f);
    EXPECT_FLOAT_EQ(result._24_, 0.0f);
    EXPECT_FLOAT_EQ(result._34_, 0.0f);
    EXPECT_FLOAT_EQ(result._44_, 1.0f);
}

TEST(Fobb, XformSetCopiesRotation)
{
    OBB box;

    Matrix matrix;
    matrix.identity();

    // 90-degree rotation around Z.
    matrix.i.set(0.0f, 1.0f, 0.0f);
    matrix.j.set(-1.0f, 0.0f, 0.0f);
    matrix.k.set(0.0f, 0.0f, 1.0f);

    box.xform_set(matrix);

    EXPECT_TRUE(box.m_rotate.i.similar(matrix.i));
    EXPECT_TRUE(box.m_rotate.j.similar(matrix.j));
    EXPECT_TRUE(box.m_rotate.k.similar(matrix.k));
}


TEST(Fobb, XformSetCopiesTranslation)
{
    OBB box;

    Matrix matrix;
    matrix.identity();
    matrix.translate_over(11, 22, 33);

    box.xform_set(matrix);

    expect_vec_near(box.m_translate, 11, 22, 33);
}


// -----------------------------------------------------------------------------
// xform_full
// -----------------------------------------------------------------------------

TEST(Fobb, XformFullIdentity)
{
    OBB box;
    box.identity();

    Matrix result;
    box.xform_full(result);

    Vec point = {1, 2, 3};
    Vec transformed;

    result.transform_tiny(transformed, point);

    expect_vec_near(transformed, 0.5f, 1.0f, 1.5f);
}


TEST(Fobb, XformFullContainsHalfSizeScale)
{
    OBB box;
    box.identity();

    box.m_halfsize.set(2, 3, 4);
    box.m_translate.set(10, 20, 30);

    Matrix result;
    box.xform_full(result);

    Vec origin = {0, 0, 0};
    Vec transformed;

    result.transform_tiny(transformed, origin);

    expect_vec_near(transformed, 10, 20, 30);
}


TEST(Fobb, XformFullAppliesHalfSizeScaleAndTranslation)
{
    OBB box;
    box.identity();

    box.m_halfsize.set(2, 3, 4);
    box.m_translate.set(10, 20, 30);

    Matrix result;
    box.xform_full(result);

    Vec point = {1, 1, 1};
    Vec transformed;

    result.transform_tiny(transformed, point);

    expect_vec_near(transformed, 12, 23, 34);
}


// -----------------------------------------------------------------------------
// transform
// -----------------------------------------------------------------------------

TEST(Fobb, TransformIdentity)
{
    OBB source = make_obb(1, 2, 3, 4, 5, 6);

    OBB result;

    Matrix matrix;
    matrix.identity();

    EXPECT_EQ(&result.transform(source, matrix), &result);

    expect_vec_near(result.m_translate, 1, 2, 3);
    expect_vec_near(result.m_halfsize, 4, 5, 6);

    EXPECT_TRUE(result.m_rotate.i.similar(source.m_rotate.i));
    EXPECT_TRUE(result.m_rotate.j.similar(source.m_rotate.j));
    EXPECT_TRUE(result.m_rotate.k.similar(source.m_rotate.k));
}


TEST(Fobb, TransformTranslation)
{
    OBB source = make_obb(1, 2, 3, 4, 5, 6);

    Matrix matrix;
    matrix.identity();
    matrix.translate_over(10, 20, 30);

    OBB result;
    result.transform(source, matrix);

    expect_vec_near(result.m_translate, 11, 22, 33);
    expect_vec_near(result.m_halfsize, 4, 5, 6);
}


TEST(Fobb, TransformRotation)
{
    OBB source = make_obb(0, 0, 0, 1, 2, 3);

    Matrix matrix;
    matrix.identity();
    matrix.rotateY(0.5f);

    OBB result;
    result.transform(source, matrix);

    expect_vec_near(result.m_halfsize, 1, 2, 3);

    EXPECT_TRUE(result.m_rotate.i.similar(matrix.i));
    EXPECT_TRUE(result.m_rotate.j.similar(matrix.j));
    EXPECT_TRUE(result.m_rotate.k.similar(matrix.k));
}


TEST(Fobb, TransformRotationAndTranslation)
{
    OBB source = make_obb(1, 2, 3, 4, 5, 6);

    Matrix matrix;
    matrix.identity();

    // 90-degree rotation around Z.
    matrix.i.set(0.0f, 1.0f, 0.0f);
    matrix.j.set(-1.0f, 0.0f, 0.0f);
    matrix.k.set(0.0f, 0.0f, 1.0f);
    matrix.c.set(10.0f, 20.0f, 30.0f);

    OBB result;
    result.transform(source, matrix);

    Matrix source_matrix;
    source.xform_get(source_matrix);

    Matrix expected;
    expected.mul_43(matrix, source_matrix);

    EXPECT_TRUE(result.m_rotate.i.similar(expected.i));
    EXPECT_TRUE(result.m_rotate.j.similar(expected.j));
    EXPECT_TRUE(result.m_rotate.k.similar(expected.k));

    expect_vec_near(
        result.m_translate,
        expected.c.x,
        expected.c.y,
        expected.c.z);

    expect_vec_near(result.m_halfsize, 4, 5, 6);
}


// -----------------------------------------------------------------------------
// contains
// -----------------------------------------------------------------------------

TEST(Fobb, ContainsCenter)
{
    OBB box = make_obb(10, 20, 30, 2, 3, 4);

    EXPECT_TRUE(box.contains(Vec{10, 20, 30}));
}


TEST(Fobb, ContainsAxisAlignedInteriorPoint)
{
    OBB box = make_obb(10, 20, 30, 2, 3, 4);

    EXPECT_TRUE(box.contains(Vec{11, 21, 32}));
}


TEST(Fobb, ContainsBoundaryPoints)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    EXPECT_TRUE(box.contains(Vec{2, 0, 0}));
    EXPECT_TRUE(box.contains(Vec{-2, 0, 0}));
    EXPECT_TRUE(box.contains(Vec{0, 3, 0}));
    EXPECT_TRUE(box.contains(Vec{0, -3, 0}));
    EXPECT_TRUE(box.contains(Vec{0, 0, 4}));
    EXPECT_TRUE(box.contains(Vec{0, 0, -4}));
}


TEST(Fobb, DoesNotContainOutsidePoint)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    EXPECT_FALSE(box.contains(Vec{2.001f, 0, 0}));
    EXPECT_FALSE(box.contains(Vec{0, 3.001f, 0}));
    EXPECT_FALSE(box.contains(Vec{0, 0, 4.001f}));
}


TEST(Fobb, ContainsRotatedPoint)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.5f);

    box.xform_set(matrix);

    Vec local = {1.5f, 0.5f, 0};
    Vec world;

    matrix.transform_tiny(world, local);

    EXPECT_TRUE(box.contains(world));
}


TEST(Fobb, RotatedBoxRejectsPointOutsideLocalBounds)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.5f);

    box.xform_set(matrix);

    Vec local = {2.001f, 0, 0};
    Vec world;

    matrix.transform_tiny(world, local);

    EXPECT_FALSE(box.contains(world));
}


// -----------------------------------------------------------------------------
// Ray intersection
// -----------------------------------------------------------------------------

TEST(Fobb, IntersectRayHitsFromNegativeX)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec start = {-5, 0, 0};
    Vec dir = {1, 0, 0};

    float dist = 100.0f;

    EXPECT_TRUE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 4.0f);
}


TEST(Fobb, IntersectRayHitsFromPositiveX)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec start = {5, 0, 0};
    Vec dir = {-1, 0, 0};

    float dist = 100.0f;

    EXPECT_TRUE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 4.0f);
}


TEST(Fobb, IntersectRayHitsFromNegativeY)
{
    OBB box = make_obb(0, 0, 0, 1, 2, 1);

    Vec start = {0, -5, 0};
    Vec dir = {0, 1, 0};

    float dist = 100.0f;

    EXPECT_TRUE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 3.0f);
}


TEST(Fobb, IntersectRayHitsFromNegativeZ)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 2);

    Vec start = {0, 0, -5};
    Vec dir = {0, 0, 1};

    float dist = 100.0f;

    EXPECT_TRUE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 3.0f);
}


TEST(Fobb, IntersectRayMisses)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec start = {-5, 2, 0};
    Vec dir = {1, 0, 0};

    float dist = 100.0f;

    EXPECT_FALSE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 100.0f);
}


TEST(Fobb, IntersectRayStartingInside)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec start = {0, 0, 0};
    Vec dir = {1, 0, 0};

    float dist = 100.0f;

    EXPECT_TRUE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 1.0f);
}


TEST(Fobb, IntersectRayStartingInsideUsesExitDistance)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    Vec start = {0, 0, 0};
    Vec dir = {0, 0, 1};

    float dist = 100.0f;

    EXPECT_TRUE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 4.0f);
}


TEST(Fobb, IntersectDoesNotIncreaseExistingDistance)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec start = {-5, 0, 0};
    Vec dir = {1, 0, 0};

    float dist = 2.0f;

    EXPECT_FALSE(box.intersect(start, dir, dist));
    EXPECT_FLOAT_EQ(dist, 2.0f);
}


TEST(Fobb, IntersectRotatedBox)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.78539816339f);

    box.xform_set(matrix);

    Vec start = {-10, 0, 0};
    Vec dir = {1, 0, 0};

    float dist = 100.0f;

    ASSERT_TRUE(box.intersect(start, dir, dist));

    EXPECT_GT(dist, 0.0f);
    EXPECT_LT(dist, 10.0f);
}


// -----------------------------------------------------------------------------
// AABB intersection
// -----------------------------------------------------------------------------

TEST(Fobb, IntersectAABBOverlapping)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec center = {1.5f, 0, 0};
    Vec extents = {1, 1, 1};

    EXPECT_TRUE(box.intersectAABB(center, extents));
}


TEST(Fobb, IntersectAABBSeparated)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec center = {3.0f, 0, 0};
    Vec extents = {1, 1, 1};

    EXPECT_FALSE(box.intersectAABB(center, extents));
}


TEST(Fobb, IntersectAABBTouching)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec center = {2, 0, 0};
    Vec extents = {1, 1, 1};

    EXPECT_TRUE(box.intersectAABB(center, extents));
}


TEST(Fobb, IntersectAABBContained)
{
    OBB box = make_obb(0, 0, 0, 5, 5, 5);

    Vec center = {0, 0, 0};
    Vec extents = {1, 1, 1};

    EXPECT_TRUE(box.intersectAABB(center, extents));
}


TEST(Fobb, IntersectAABBRotated)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.78539816339f);

    box.xform_set(matrix);

    Vec center = {2.0f, 0, 0};
    Vec extents = {0.5f, 0.5f, 0.5f};

    EXPECT_TRUE(box.intersectAABB(center, extents));
}


TEST(Fobb, IntersectAABBRotatedSeparated)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.78539816339f);

    box.xform_set(matrix);

    Vec center = {4.0f, 0, 0};
    Vec extents = {0.25f, 0.25f, 0.25f};

    EXPECT_FALSE(box.intersectAABB(center, extents));
}


TEST(Fobb, IntersectAABBBoxOverload)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Fbox aabb;
    aabb.set(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f);

    EXPECT_TRUE(box.intersectAABB(aabb));
}


TEST(Fobb, IntersectAABBSeparatedBoxOverload)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Fbox aabb;
    aabb.set(5, 5, 5, 6, 6, 6);

    EXPECT_FALSE(box.intersectAABB(aabb));
}


// -----------------------------------------------------------------------------
// Triangle intersection
// -----------------------------------------------------------------------------

TEST(Fobb, IntersectTriWhenTriangleInside)
{
    OBB box = make_obb(0, 0, 0, 2, 2, 2);

    Vec triangle[3] =
    {
        {-1, -1, 0},
        { 1, -1, 0},
        { 0,  1, 0},
    };

    EXPECT_TRUE(box.intersectTri(triangle));
}


TEST(Fobb, IntersectTriWhenTriangleCrossesBox)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {-2, 0, 0},
        { 2, 0, 0},
        { 0, 2, 0},
    };

    EXPECT_TRUE(box.intersectTri(triangle));
}


TEST(Fobb, IntersectTriWhenTriangleOutside)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {5, 5, 5},
        {6, 5, 5},
        {5, 6, 5},
    };

    EXPECT_FALSE(box.intersectTri(triangle));
}


TEST(Fobb, IntersectTriTouchingBox)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {1, -0.5f, 0},
        {1,  0.5f, 0},
        {1,  0,      0.5f},
    };

    EXPECT_TRUE(box.intersectTri(triangle));
}


TEST(Fobb, IntersectTriSeparatedAlongX)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {2, 0, 0},
        {3, 0, 0},
        {2, 1, 0},
    };

    EXPECT_FALSE(box.intersectTri(triangle));
}


TEST(Fobb, IntersectTriSeparatedAlongZ)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {0, 0, 2},
        {1, 0, 3},
        {0, 1, 2},
    };

    EXPECT_FALSE(box.intersectTri(triangle));
}


TEST(Fobb, IntersectTriClass2)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {-2, 0, 0},
        { 2, 0, 0},
        { 0, 2, 0},
    };

    EXPECT_TRUE(box.intersectTri(triangle, false));
}


TEST(Fobb, IntersectTriRotatedOBB)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.78539816339f);

    box.xform_set(matrix);

    Vec triangle[3] =
    {
        {0, 0, 0},
        {2, 0, 0},
        {0, 2, 0},
    };

    EXPECT_TRUE(box.intersectTri(triangle));
}


// -----------------------------------------------------------------------------
// ClampPointOBB
// -----------------------------------------------------------------------------

TEST(Fobb, ClampPointInsideLeavesPointUnchanged)
{
    OBB box = make_obb(10, 20, 30, 2, 3, 4);

    Vec point = {11, 21, 32};
    Vec original = point;

    box.ClampPointOBB(point);

    expect_vec_near(point, original);
}


TEST(Fobb, ClampPointOutsideOneAxis)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    Vec point = {5, 1, 2};

    box.ClampPointOBB(point);

    expect_vec_near(point, 2, 1, 2);
}


TEST(Fobb, ClampPointOutsideNegativeOneAxis)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    Vec point = {-5, 1, 2};

    box.ClampPointOBB(point);

    expect_vec_near(point, -2, 1, 2);
}


TEST(Fobb, ClampPointOutsideTwoAxes)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    Vec point = {5, 6, 1};

    box.ClampPointOBB(point);

    EXPECT_LE(point.x, 2.0f);
    EXPECT_GE(point.x, -2.0f);

    EXPECT_LE(point.y, 3.0f);
    EXPECT_GE(point.y, -3.0f);

    EXPECT_LE(point.z, 4.0f);
    EXPECT_GE(point.z, -4.0f);
}


TEST(Fobb, ClampPointOutsideThreeAxes)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    Vec point = {5, 6, 7};

    box.ClampPointOBB(point);

    expect_vec_near(point, 2, 3, 4);
}


TEST(Fobb, ClampPointOutsideNegativeThreeAxes)
{
    OBB box = make_obb(0, 0, 0, 2, 3, 4);

    Vec point = {-5, -6, -7};

    box.ClampPointOBB(point);

    expect_vec_near(point, -2, -3, -4);
}


TEST(Fobb, ClampPointTranslatedOBB)
{
    OBB box = make_obb(10, 20, 30, 2, 3, 4);

    Vec point = {20, 21, 32};

    box.ClampPointOBB(point);

    expect_vec_near(point, 12, 21, 32);
}


TEST(Fobb, ClampPointRotatedOBB)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.78539816339f);

    box.xform_set(matrix);

    Vec local = {3, 0, 0};
    Vec point;

    matrix.transform_tiny(point, local);

    box.ClampPointOBB(point);

    Vec expected_local = {2, 0, 0};
    Vec expected_world;

    matrix.transform_tiny(expected_world, expected_local);

    expect_vec_near(point, expected_world);
}


// -----------------------------------------------------------------------------
// FindContactsClipping
// -----------------------------------------------------------------------------

namespace
{
    struct ContactCollector
    {
        std::vector<Vec> points;

        static void callback(const Vec& point, void* user_data)
        {
            auto* collector = static_cast<ContactCollector*>(user_data);
            collector->points.push_back(point);
        }
    };
}


TEST(Fobb, FindContactsClippingTriangleInside)
{
    OBB box = make_obb(0, 0, 0, 2, 2, 2);

    Vec triangle[3] =
    {
        {-1, -1, 0},
        { 1, -1, 0},
        { 0,  1, 0},
    };

    ContactCollector contacts;

    box.FindContactsClipping(
        triangle,
        &ContactCollector::callback,
        &contacts);

    ASSERT_EQ(contacts.points.size(), 3u);

    expect_vec_near(contacts.points[0], -1, -1, 0);
    expect_vec_near(contacts.points[1],  1, -1, 0);
    expect_vec_near(contacts.points[2],  0,  1, 0);
}


TEST(Fobb, FindContactsClippingTriangleOutside)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {5, 5, 5},
        {6, 5, 5},
        {5, 6, 5},
    };

    ContactCollector contacts;

    box.FindContactsClipping(
        triangle,
        &ContactCollector::callback,
        &contacts);

    EXPECT_TRUE(contacts.points.empty());
}


TEST(Fobb, FindContactsClippingTriangleCrossingOneFace)
{
    OBB box = make_obb(0, 0, 0, 1, 1, 1);

    Vec triangle[3] =
    {
        {0, 0, 0},
        {2, 0, 0},
        {0, 0.5f, 0},
    };

    ContactCollector contacts;

    box.FindContactsClipping(
        triangle,
        &ContactCollector::callback,
        &contacts);

    ASSERT_GE(contacts.points.size(), 3u);

    for (const Vec& point : contacts.points)
        EXPECT_TRUE(box.contains(point));
}


TEST(Fobb, FindContactsClippingTranslatedOBB)
{
    OBB box = make_obb(10, 20, 30, 2, 2, 2);

    Vec triangle[3] =
    {
        {9, 19, 30},
        {11, 19, 30},
        {10, 21, 30},
    };

    ContactCollector contacts;

    box.FindContactsClipping(
        triangle,
        &ContactCollector::callback,
        &contacts);

    ASSERT_EQ(contacts.points.size(), 3u);

    for (const Vec& point : contacts.points)
        EXPECT_TRUE(box.contains(point));
}


TEST(Fobb, FindContactsClippingRotatedOBB)
{
    OBB box = make_obb(0, 0, 0, 2, 1, 1);

    Matrix matrix;
    matrix.identity();
    matrix.rotateZ(0.5f);

    box.xform_set(matrix);

    Vec triangle[3] =
    {
        {0, 0, 0},
        {2, 0, 0},
        {0, 2, 0},
    };

    ContactCollector contacts;

    box.FindContactsClipping(
        triangle,
        &ContactCollector::callback,
        &contacts);

    ASSERT_GE(contacts.points.size(), 3u);

    for (const Vec& point : contacts.points)
        EXPECT_TRUE(box.contains(point));
}


// -----------------------------------------------------------------------------
// _valid
// -----------------------------------------------------------------------------

TEST(Fobb, ValidIdentity)
{
    OBB box;
    box.identity();

    EXPECT_TRUE(_valid(box));
}


TEST(Fobb, ValidTranslatedBox)
{
    OBB box = make_obb(10, 20, 30, 1, 2, 3);

    EXPECT_TRUE(_valid(box));
}
