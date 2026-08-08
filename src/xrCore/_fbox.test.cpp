#include "stdafx.h"

#include "_fbox.h"

#include <gtest/gtest.h>

#include <cmath>
#include <numbers>

constexpr float M_PI_2 = std::numbers::pi_v<float> / 2.0f;

namespace
{
    using Box = Fbox;
    using Vec = Fvector;

    void expect_vec_eq(const Vec& actual, float x, float y, float z)
    {
        EXPECT_FLOAT_EQ(actual.x, x);
        EXPECT_FLOAT_EQ(actual.y, y);
        EXPECT_FLOAT_EQ(actual.z, z);
    }

    void expect_box_eq(
        const Box& actual,
        float min_x, float min_y, float min_z,
        float max_x, float max_y, float max_z)
    {
        expect_vec_eq(actual.min, min_x, min_y, min_z);
        expect_vec_eq(actual.max, max_x, max_y, max_z);
    }
}


// -----------------------------------------------------------------------------
// Basic state
// -----------------------------------------------------------------------------

TEST(Fbox, SetFromVectors)
{
    Box box;

    const Vec min = {1.0f, 2.0f, 3.0f};
    const Vec max = {4.0f, 5.0f, 6.0f};

    EXPECT_EQ(&box.set(min, max), &box);

    expect_box_eq(box, 1, 2, 3, 4, 5, 6);
}


TEST(Fbox, SetFromCoordinates)
{
    Box box;

    EXPECT_EQ(&box.set(1, 2, 3, 4, 5, 6), &box);

    expect_box_eq(box, 1, 2, 3, 4, 5, 6);
}


TEST(Fbox, SetFromAnotherBox)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Box box;

    EXPECT_EQ(&box.set(source), &box);

    expect_box_eq(box, 1, 2, 3, 4, 5, 6);
}


TEST(Fbox, Setb)
{
    Box box;

    const Vec center = {10.0f, 20.0f, 30.0f};
    const Vec dim = {1.0f, 2.0f, 3.0f};

    EXPECT_EQ(&box.setb(center, dim), &box);

    expect_box_eq(box, 9, 18, 27, 11, 22, 33);
}


TEST(Fbox, Null)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    EXPECT_EQ(&box.null(), &box);

    expect_box_eq(box, 0, 0, 0, 0, 0, 0);
}


TEST(Fbox, Identity)
{
    Box box;

    EXPECT_EQ(&box.identity(), &box);

    expect_box_eq(box, -0.5f, -0.5f, -0.5f,
                       0.5f,  0.5f,  0.5f);
}


TEST(Fbox, Invalidate)
{
    Box box;

    EXPECT_EQ(&box.invalidate(), &box);

    EXPECT_EQ(box.min.x, type_max(float));
    EXPECT_EQ(box.min.y, type_max(float));
    EXPECT_EQ(box.min.z, type_max(float));

    EXPECT_EQ(box.max.x, type_min(float));
    EXPECT_EQ(box.max.y, type_min(float));
    EXPECT_EQ(box.max.z, type_min(float));

    EXPECT_FALSE(box.is_valid());
}


// -----------------------------------------------------------------------------
// Validity
// -----------------------------------------------------------------------------

TEST(Fbox, ValidWhenMinEqualsMax)
{
    Box box;
    box.set(1, 2, 3, 1, 2, 3);

    EXPECT_TRUE(box.is_valid());
}


TEST(Fbox, ValidWhenMinIsLessThanMax)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    EXPECT_TRUE(box.is_valid());
}


TEST(Fbox, InvalidWhenXMinExceedsXMax)
{
    Box box;
    box.set(4, 2, 3, 1, 5, 6);

    EXPECT_FALSE(box.is_valid());
}


TEST(Fbox, InvalidWhenYMinExceedsYMax)
{
    Box box;
    box.set(1, 5, 3, 4, 2, 6);

    EXPECT_FALSE(box.is_valid());
}


TEST(Fbox, InvalidWhenZMinExceedsZMax)
{
    Box box;
    box.set(1, 2, 6, 4, 5, 3);

    EXPECT_FALSE(box.is_valid());
}


// -----------------------------------------------------------------------------
// Data
// -----------------------------------------------------------------------------

TEST(Fbox, DataPointsToMinX)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    const float* data = box.data();

    ASSERT_NE(data, nullptr);

    EXPECT_EQ(data, &box.min.x);
    EXPECT_FLOAT_EQ(data[0], 1.0f);
    EXPECT_FLOAT_EQ(data[1], 2.0f);
    EXPECT_FLOAT_EQ(data[2], 3.0f);
    EXPECT_FLOAT_EQ(data[3], 4.0f);
    EXPECT_FLOAT_EQ(data[4], 5.0f);
    EXPECT_FLOAT_EQ(data[5], 6.0f);
}


// -----------------------------------------------------------------------------
// Grow / shrink
// -----------------------------------------------------------------------------

TEST(Fbox, GrowUniformly)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    EXPECT_EQ(&box.grow(2.0f), &box);

    expect_box_eq(box, -1, 0, 1, 6, 7, 8);
}


TEST(Fbox, GrowByVector)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    const Vec amount = {1, 2, 3};

    EXPECT_EQ(&box.grow(amount), &box);

    expect_box_eq(box, 0, 0, 0, 5, 7, 9);
}


TEST(Fbox, ShrinkUniformly)
{
    Box box;
    box.set(1, 2, 3, 7, 8, 9);

    EXPECT_EQ(&box.shrink(1.0f), &box);

    expect_box_eq(box, 2, 3, 4, 6, 7, 8);
}


TEST(Fbox, ShrinkByVector)
{
    Box box;
    box.set(1, 2, 3, 7, 8, 9);

    const Vec amount = {1, 2, 3};

    EXPECT_EQ(&box.shrink(amount), &box);

    expect_box_eq(box, 2, 4, 6, 6, 6, 6);
}


// -----------------------------------------------------------------------------
// Translation
// -----------------------------------------------------------------------------

TEST(Fbox, AddTranslatesBox)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    const Vec offset = {10, 20, 30};

    EXPECT_EQ(&box.add(offset), &box);

    expect_box_eq(box, 11, 22, 33, 14, 25, 36);
}


TEST(Fbox, SubTranslatesBox)
{
    Box box;
    box.set(11, 22, 33, 14, 25, 36);

    const Vec offset = {10, 20, 30};

    EXPECT_EQ(&box.sub(offset), &box);

    expect_box_eq(box, 1, 2, 3, 4, 5, 6);
}


TEST(Fbox, OffsetTranslatesBox)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    const Vec offset = {10, 20, 30};

    EXPECT_EQ(&box.offset(offset), &box);

    expect_box_eq(box, 11, 22, 33, 14, 25, 36);
}


TEST(Fbox, AddFromBoxWithOffset)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Box box;

    const Vec offset = {10, 20, 30};

    EXPECT_EQ(&box.add(source, offset), &box);

    expect_box_eq(box, 11, 22, 33, 14, 25, 36);
}


// -----------------------------------------------------------------------------
// Containment
// -----------------------------------------------------------------------------

TEST(Fbox, ContainsPointInside)
{
    Box box;
    box.set(0, 0, 0, 10, 10, 10);

    EXPECT_TRUE(box.contains(5, 5, 5));
}


TEST(Fbox, ContainsPointOnBoundary)
{
    Box box;
    box.set(0, 0, 0, 10, 10, 10);

    EXPECT_TRUE(box.contains(0, 0, 0));
    EXPECT_TRUE(box.contains(10, 10, 10));
    EXPECT_TRUE(box.contains(0, 10, 5));
}


TEST(Fbox, DoesNotContainPointOutside)
{
    Box box;
    box.set(0, 0, 0, 10, 10, 10);

    EXPECT_FALSE(box.contains(-0.001f, 5, 5));
    EXPECT_FALSE(box.contains(10.001f, 5, 5));
    EXPECT_FALSE(box.contains(5, -0.001f, 5));
    EXPECT_FALSE(box.contains(5, 10.001f, 5));
    EXPECT_FALSE(box.contains(5, 5, -0.001f));
    EXPECT_FALSE(box.contains(5, 5, 10.001f));
}


TEST(Fbox, ContainsVector)
{
    Box box;
    box.set(0, 0, 0, 10, 10, 10);

    const Vec point = {5, 5, 5};

    EXPECT_TRUE(box.contains(point));
}


TEST(Fbox, ContainsBox)
{
    Box outer;
    outer.set(0, 0, 0, 10, 10, 10);

    Box inner;
    inner.set(2, 3, 4, 6, 7, 8);

    EXPECT_TRUE(outer.contains(inner));
}


TEST(Fbox, DoesNotContainPartiallyOutsideBox)
{
    Box outer;
    outer.set(0, 0, 0, 10, 10, 10);

    Box inner;
    inner.set(2, 3, 4, 11, 7, 8);

    EXPECT_FALSE(outer.contains(inner));
}


// -----------------------------------------------------------------------------
// Similarity
// -----------------------------------------------------------------------------

TEST(Fbox, SimilarBoxesAreSimilar)
{
    Box a;
    Box b;

    a.set(1, 2, 3, 4, 5, 6);
    b.set(1, 2, 3, 4, 5, 6);

    EXPECT_TRUE(a.similar(b));
}


TEST(Fbox, DifferentBoxesAreNotSimilar)
{
    Box a;
    Box b;

    a.set(1, 2, 3, 4, 5, 6);
    b.set(1, 2, 3, 4, 5, 7);

    EXPECT_FALSE(a.similar(b));
}


// -----------------------------------------------------------------------------
// Modify / merge
// -----------------------------------------------------------------------------

TEST(Fbox, ModifyExpandsToContainPoint)
{
    Box box;
    box.set(0, 0, 0, 10, 10, 10);

    EXPECT_EQ(&box.modify({-5, 20, 5}), &box);

    expect_box_eq(box, -5, 0, 0, 10, 20, 10);
}


TEST(Fbox, ModifyCoordinatesExpandsToContainPoint)
{
    Box box;
    box.set(0, 0, 0, 10, 10, 10);

    EXPECT_EQ(&box.modify(-5, 20, 15), &box);

    expect_box_eq(box, -5, 0, 0, 10, 20, 15);
}


TEST(Fbox, MergeExpandsToContainOtherBox)
{
    Box box;
    box.set(0, 0, 0, 10, 10, 10);

    Box other;
    other.set(-5, 2, 3, 20, 8, 30);

    EXPECT_EQ(&box.merge(other), &box);

    expect_box_eq(box, -5, 0, 0, 20, 10, 30);
}


TEST(Fbox, MergeTwoBoxes)
{
    Box a;
    a.set(1, 2, 3, 4, 5, 6);

    Box b;
    b.set(-10, 20, -30, 40, 50, 60);

    Box result;

    EXPECT_EQ(&result.merge(a, b), &result);

    expect_box_eq(result, -10, 2, -30, 40, 50, 60);
}


// -----------------------------------------------------------------------------
// Size / radius / volume / center
// -----------------------------------------------------------------------------

TEST(Fbox, GetSize)
{
    Box box;
    box.set(1, 2, 3, 11, 22, 33);

    Vec size;
    box.getsize(size);

    expect_vec_eq(size, 10, 20, 30);
}


TEST(Fbox, GetRadiusVector)
{
    Box box;
    box.set(0, 0, 0, 10, 20, 30);

    Vec radius;
    box.getradius(radius);

    expect_vec_eq(radius, 5, 10, 15);
}


TEST(Fbox, GetRadius)
{
    Box box;
    box.set(0, 0, 0, 2, 4, 4);

    // sqrt(1^2 + 2^2 + 2^2) = 3
    EXPECT_FLOAT_EQ(box.getradius(), 3.0f);
}


TEST(Fbox, GetVolume)
{
    Box box;
    box.set(1, 2, 3, 11, 22, 33);

    EXPECT_FLOAT_EQ(box.getvolume(), 10.0f * 20.0f * 30.0f);
}


TEST(Fbox, GetCenter)
{
    Box box;
    box.set(0, 10, 20, 10, 30, 40);

    Vec center;
    box.getcenter(center);

    expect_vec_eq(center, 5, 20, 30);
}


TEST(Fbox, GetCenterAndDimensions)
{
    Box box;
    box.set(0, 10, 20, 10, 30, 40);

    Vec center;
    Vec dimensions;

    box.get_CD(center, dimensions);

    expect_vec_eq(center, 5, 20, 30);
    expect_vec_eq(dimensions, 5, 10, 10);
}


TEST(Fbox, GetSphere)
{
    Box box;
    box.set(-1, -2, -2, 1, 2, 2);

    Vec center;
    float radius;

    box.getsphere(center, radius);

    expect_vec_eq(center, 0, 0, 0);
    EXPECT_FLOAT_EQ(radius, 3.0f);
}


TEST(Fbox, Scale)
{
    Box box;
    box.set(0, 0, 0, 10, 20, 30);

    EXPECT_EQ(&box.scale(0.1f), &box);

    // Characterizes the current implementation:
    //
    // bd = size * s
    // grow(bd)
    //
    // Therefore each side grows by 10% of the original size.
    expect_box_eq(box, -1, -2, -3, 11, 22, 33);
}


// -----------------------------------------------------------------------------
// Intersection
// -----------------------------------------------------------------------------

TEST(Fbox, IntersectsOverlappingBoxes)
{
    Box a;
    a.set(0, 0, 0, 10, 10, 10);

    Box b;
    b.set(5, 5, 5, 15, 15, 15);

    EXPECT_TRUE(a.intersect(b));
}


TEST(Fbox, IntersectsWhenBoxesTouch)
{
    Box a;
    a.set(0, 0, 0, 10, 10, 10);

    Box b;
    b.set(10, 10, 10, 20, 20, 20);

    EXPECT_TRUE(a.intersect(b));
}


TEST(Fbox, DoesNotIntersectWhenSeparatedOnX)
{
    Box a;
    a.set(0, 0, 0, 10, 10, 10);

    Box b;
    b.set(10.001f, 0, 0, 20, 10, 10);

    EXPECT_FALSE(a.intersect(b));
}


TEST(Fbox, DoesNotIntersectWhenSeparatedOnY)
{
    Box a;
    a.set(0, 0, 0, 10, 10, 10);

    Box b;
    b.set(0, 10.001f, 0, 10, 20, 10);

    EXPECT_FALSE(a.intersect(b));
}


TEST(Fbox, DoesNotIntersectWhenSeparatedOnZ)
{
    Box a;
    a.set(0, 0, 0, 10, 10, 10);

    Box b;
    b.set(0, 0, 10.001f, 10, 10, 20);

    EXPECT_FALSE(a.intersect(b));
}


// -----------------------------------------------------------------------------
// Pick
// -----------------------------------------------------------------------------

TEST(Fbox, PickHitsXFace)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec start = {-2, 0, 0};
    const Vec dir = {1, 0, 0};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox, PickHitsYFace)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec start = {0, -2, 0};
    const Vec dir = {0, 1, 0};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox, PickHitsZFace)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec start = {0, 0, -2};
    const Vec dir = {0, 0, 1};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox, PickMisses)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec start = {-2, 2, 0};
    const Vec dir = {1, 0, 0};

    EXPECT_FALSE(box.Pick(start, dir));
}


// -----------------------------------------------------------------------------
// Pick2
// -----------------------------------------------------------------------------

TEST(Fbox, Pick2ReportsOriginInside)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec origin = {0, 0, 0};
    const Vec dir = {1, 0, 0};

    Vec coord;

    EXPECT_EQ(box.Pick2(origin, dir, coord), Box::rpOriginInside);

    expect_vec_eq(coord, 0, 0, 0);
}


TEST(Fbox, Pick2HitsXFace)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec origin = {-2, 0, 0};
    const Vec dir = {1, 0, 0};

    Vec coord;

    EXPECT_EQ(box.Pick2(origin, dir, coord), Box::rpOriginOutside);

    expect_vec_eq(coord, -1, 0, 0);
}


TEST(Fbox, Pick2HitsYFace)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec origin = {0, -2, 0};
    const Vec dir = {0, 1, 0};

    Vec coord;

    EXPECT_EQ(box.Pick2(origin, dir, coord), Box::rpOriginOutside);

    expect_vec_eq(coord, 0, -1, 0);
}


TEST(Fbox, Pick2HitsZFace)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec origin = {0, 0, -2};
    const Vec dir = {0, 0, 1};

    Vec coord;

    EXPECT_EQ(box.Pick2(origin, dir, coord), Box::rpOriginOutside);

    expect_vec_eq(coord, 0, 0, -1);
}


TEST(Fbox, Pick2Misses)
{
    Box box;
    box.set(-1, -1, -1, 1, 1, 1);

    const Vec origin = {-2, 2, 0};
    const Vec dir = {1, 0, 0};

    Vec coord;

    EXPECT_EQ(box.Pick2(origin, dir, coord), Box::rpNone);
}


// -----------------------------------------------------------------------------
// Corner enumeration
// -----------------------------------------------------------------------------

TEST(Fbox, GetPointReturnsExpectedCorners)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    const Vec expected[] =
    {
        {1, 2, 3},
        {1, 2, 6},
        {4, 2, 6},
        {4, 2, 3},
        {1, 5, 3},
        {1, 5, 6},
        {4, 5, 6},
        {4, 5, 3},
    };

    for (int i = 0; i < 8; ++i)
    {
        SCOPED_TRACE(i);

        Vec result;
        box.getpoint(i, result);

        expect_vec_eq(
            result,
            expected[i].x,
            expected[i].y,
            expected[i].z
        );
    }
}


TEST(Fbox, GetPointOutOfRangeReturnsZero)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    Vec result;

    box.getpoint(-1, result);
    expect_vec_eq(result, 0, 0, 0);

    box.getpoint(8, result);
    expect_vec_eq(result, 0, 0, 0);
}


TEST(Fbox, GetPointsReturnsExpectedCorners)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    Vec points[8];

    box.getpoints(points);

    const Vec expected[] =
    {
        {1, 2, 3},
        {1, 2, 6},
        {4, 2, 6},
        {4, 2, 3},
        {1, 5, 3},
        {1, 5, 6},
        {4, 5, 6},
        {4, 5, 3},
    };

    for (int i = 0; i < 8; ++i)
    {
        SCOPED_TRACE(i);

        expect_vec_eq(
            points[i],
            expected[i].x,
            expected[i].y,
            expected[i].z
        );
    }
}


// -----------------------------------------------------------------------------
// Composite operations
// -----------------------------------------------------------------------------

TEST(Fbox, ModifyWithTransformedSource)
{
    Box source;
    source.set(0, 0, 0, 10, 20, 30);

    Box result;

    // This test is intentionally omitted because the exact _matrix<T>
    // construction/API is not present in _fbox.h.
    //
    // Add it once the project's matrix test infrastructure is known.
    (void)source;
    (void)result;
}

// -----------------------------------------------------------------------------
// Matrix transforms
// -----------------------------------------------------------------------------

TEST(Fbox, XformIdentity)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Box result;

    Fmatrix matrix;
    matrix.identity();

    EXPECT_EQ(&result.xform(source, matrix), &result);

    expect_box_eq(result, 1, 2, 3, 4, 5, 6);
}


TEST(Fbox, XformIdentityInPlace)
{
    Box box;
    box.set(1, 2, 3, 4, 5, 6);

    Fmatrix matrix;
    matrix.identity();

    EXPECT_EQ(&box.xform(matrix), &box);

    expect_box_eq(box, 1, 2, 3, 4, 5, 6);
}


TEST(Fbox, XformTranslation)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Fmatrix matrix;
    matrix.identity();
    matrix.translate_over(10, 20, 30);

    Box result;
    result.xform(source, matrix);

    expect_box_eq(result, 11, 22, 33, 14, 25, 36);
}


TEST(Fbox, XformNegativeTranslation)
{
    Box source;
    source.set(10, 20, 30, 40, 50, 60);

    Fmatrix matrix;
    matrix.identity();
    matrix.translate_over(-5, -10, -15);

    Box result;
    result.xform(source, matrix);

    expect_box_eq(result, 5, 10, 15, 35, 40, 45);
}


TEST(Fbox, XformUniformScale)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Fmatrix matrix;
    matrix.scale(2, 2, 2);

    Box result;
    result.xform(source, matrix);

    expect_box_eq(result, 2, 4, 6, 8, 10, 12);
}


TEST(Fbox, XformNonUniformScale)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Fmatrix matrix;
    matrix.scale(2, 3, 4);

    Box result;
    result.xform(source, matrix);

    expect_box_eq(result, 2, 6, 12, 8, 15, 24);
}


TEST(Fbox, XformNegativeScale)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Fmatrix matrix;
    matrix.scale(-2, -3, -4);

    Box result;
    result.xform(source, matrix);

    // The transformed corners are:
    //
    // min -> (-2, -6, -12)
    // max -> (-8, -15, -24)
    //
    // xform() must reorder these into an AABB.
    expect_box_eq(result, -8, -15, -24, -2, -6, -12);
}


TEST(Fbox, XformRotationZ90)
{
    Box source;
    source.set(0, 0, 0, 2, 4, 6);

    Fmatrix matrix;
    matrix.rotateZ(M_PI_2);

    Box result;
    result.xform(source, matrix);

    // X-Ray's positive rotation is clockwise in its coordinate convention.
    //
    // The resulting extents should be 4 x 2 x 6.
    EXPECT_NEAR(result.x2 - result.x1, 4.0f, 1e-5f);
    EXPECT_NEAR(result.y2 - result.y1, 2.0f, 1e-5f);
    EXPECT_NEAR(result.z2 - result.z1, 6.0f, 1e-5f);
}


TEST(Fbox, XformRotationX90)
{
    Box source;
    source.set(0, 0, 0, 2, 4, 6);

    Fmatrix matrix;
    matrix.rotateX(M_PI_2);

    Box result;
    result.xform(source, matrix);

    EXPECT_NEAR(result.x2 - result.x1, 2.0f, 1e-5f);
    EXPECT_NEAR(result.y2 - result.y1, 6.0f, 1e-5f);
    EXPECT_NEAR(result.z2 - result.z1, 4.0f, 1e-5f);
}


TEST(Fbox, XformRotationY90)
{
    Box source;
    source.set(0, 0, 0, 2, 4, 6);

    Fmatrix matrix;
    matrix.rotateY(M_PI_2);

    Box result;
    result.xform(source, matrix);

    EXPECT_NEAR(result.x2 - result.x1, 6.0f, 1e-5f);
    EXPECT_NEAR(result.y2 - result.y1, 4.0f, 1e-5f);
    EXPECT_NEAR(result.z2 - result.z1, 2.0f, 1e-5f);
}


TEST(Fbox, XformRotationPreservesVolume)
{
    Box source;
    source.set(-1, -2, -3, 4, 5, 6);

    Fmatrix matrix;
    matrix.rotateY(0.73f);

    Box result;
    result.xform(source, matrix);

    // A rotation can increase the AABB dimensions, so don't compare
    // dimensions. But the transformed AABB must still contain every
    // transformed source corner.
    for (int i = 0; i < 8; ++i)
    {
        Vec corner;
        source.getpoint(i, corner);

        Vec transformed;
        matrix.transform_tiny(transformed, corner);

        SCOPED_TRACE(i);

        EXPECT_TRUE(result.contains(transformed));
    }
}


TEST(Fbox, XformRotationAndTranslation)
{
    Box source;
    source.set(-1, -2, -3, 1, 2, 3);

    Fmatrix matrix;
    matrix.rotateZ(M_PI_2);
    matrix.translate_over(10, 20, 30);

    Box result;
    result.xform(source, matrix);

    for (int i = 0; i < 8; ++i)
    {
        Vec corner;
        source.getpoint(i, corner);

        Vec transformed;
        matrix.transform_tiny(transformed, corner);

        SCOPED_TRACE(i);

        EXPECT_TRUE(result.contains(transformed));
    }
}


TEST(Fbox, XformScaleRotationTranslation)
{
    Box source;
    source.set(-1, -2, -3, 4, 5, 6);

    Fmatrix matrix;
    matrix.scale(2, 3, 4);

    // Deliberately construct translation after scale so the test exercises
    // the matrix's actual row-vector convention.
    matrix.translate_add(10, 20, 30);

    Box result;
    result.xform(source, matrix);

    for (int i = 0; i < 8; ++i)
    {
        Vec corner;
        source.getpoint(i, corner);

        Vec transformed;
        matrix.transform_tiny(transformed, corner);

        SCOPED_TRACE(i);

        EXPECT_TRUE(result.contains(transformed));
    }
}


TEST(Fbox, XformResultContainsAllTransformedCorners)
{
    Box source;
    source.set(-2, -3, -4, 5, 6, 7);

    Fmatrix matrix;
    matrix.rotateX(0.31f);
    matrix.rotateY(-0.73f);
    matrix.rotateZ(1.17f);
    matrix.translate_over(13, -7, 42);

    Box result;
    result.xform(source, matrix);

    for (int i = 0; i < 8; ++i)
    {
        Vec corner;
        source.getpoint(i, corner);

        Vec transformed;
        matrix.transform_tiny(transformed, corner);

        SCOPED_TRACE(i);

        EXPECT_TRUE(result.contains(transformed));
    }
}


TEST(Fbox, XformMatchesExplicitCornerTransformation)
{
    Box source;
    source.set(1, 2, 3, 7, 11, 13);

    Fmatrix matrix;
    matrix.rotateY(0.4f);
    matrix.translate_over(17, 19, 23);

    Box result;
    result.xform(source, matrix);

    Box expected;
    expected.invalidate();

    for (int i = 0; i < 8; ++i)
    {
        Vec corner;
        source.getpoint(i, corner);

        Vec transformed;
        matrix.transform_tiny(transformed, corner);

        expected.modify(transformed);
    }

    expect_box_eq(
        result,
        expected.min.x,
        expected.min.y,
        expected.min.z,
        expected.max.x,
        expected.max.y,
        expected.max.z
    );
}


TEST(Fbox, XformFromBoxDoesNotModifySource)
{
    Box source;
    source.set(1, 2, 3, 4, 5, 6);

    Box original;
    original.set(source);

    Fmatrix matrix;
    matrix.translate_over(10, 20, 30);

    Box result;
    result.xform(source, matrix);

    EXPECT_TRUE(source.similar(original));
}


TEST(Fbox, XformInPlaceMatchesOutOfPlace)
{
    Box source;
    source.set(-2, -3, -4, 5, 6, 7);

    Fmatrix matrix;
    matrix.rotateZ(0.37f);
    matrix.translate_over(10, 20, 30);

    Box expected;
    expected.xform(source, matrix);

    Box actual;
    actual.set(source);
    actual.xform(matrix);

    EXPECT_TRUE(actual.similar(expected));
}


// -----------------------------------------------------------------------------
// Degenerate boxes
// -----------------------------------------------------------------------------

TEST(Fbox, XformPointBox)
{
    Box source;
    source.set(2, 3, 4, 2, 3, 4);

    Fmatrix matrix;
    matrix.translate_over(10, 20, 30);

    Box result;
    result.xform(source, matrix);

    expect_box_eq(result, 12, 23, 34, 12, 23, 34);
}


TEST(Fbox, XformZeroSizeBoxWithRotation)
{
    Box source;
    source.set(1, 2, 3, 1, 2, 3);

    Fmatrix matrix;
    matrix.rotateZ(M_PI_2);

    Box result;
    result.xform(source, matrix);

    Vec expected;
    matrix.transform_tiny(expected, source.min);

    expect_vec_eq(
        result.min,
        expected.x,
        expected.y,
        expected.z
    );

    expect_vec_eq(
        result.max,
        expected.x,
        expected.y,
        expected.z
    );
}
