#include "stdafx.h"

#include "_plane.h"

#include <gtest/gtest.h>

#include <numbers>

constexpr float M_PI_2 = std::numbers::pi_v<float> / 2.0f;

namespace
{
    constexpr float EPSILON = 1e-5f;

    void expect_vec_near(
        const Fvector& actual,
        float x,
        float y,
        float z,
        float epsilon = EPSILON)
    {
        EXPECT_NEAR(actual.x, x, epsilon);
        EXPECT_NEAR(actual.y, y, epsilon);
        EXPECT_NEAR(actual.z, z, epsilon);
    }

    Fplane make_plane(
        float nx,
        float ny,
        float nz,
        float d)
    {
        Fplane plane;
        plane.n.set(nx, ny, nz);
        plane.d = d;
        return plane;
    }
}


// -----------------------------------------------------------------------------
// Construction / copying
// -----------------------------------------------------------------------------

TEST(Plane, SetCopiesNormalAndOffset)
{
    Fplane source = make_plane(1.0f, 2.0f, 3.0f, 4.0f);
    Fplane destination = make_plane(10.0f, 20.0f, 30.0f, 40.0f);

    EXPECT_EQ(&destination.set(source), &destination);

    expect_vec_near(destination.n, 1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(destination.d, 4.0f);
}


TEST(Plane, SimilarReturnsTrueForEqualPlanes)
{
    Fplane a = make_plane(1.0f, 2.0f, 3.0f, 4.0f);
    Fplane b = make_plane(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_TRUE(a.similar(b));
}


TEST(Plane, SimilarReturnsFalseForDifferentNormal)
{
    Fplane a = make_plane(1.0f, 2.0f, 3.0f, 4.0f);
    Fplane b = make_plane(1.0f, 2.0f, 3.1f, 4.0f);

    EXPECT_FALSE(a.similar(b));
}


TEST(Plane, SimilarReturnsFalseForDifferentOffset)
{
    Fplane a = make_plane(1.0f, 2.0f, 3.0f, 4.0f);
    Fplane b = make_plane(1.0f, 2.0f, 3.0f, 4.1f);

    EXPECT_FALSE(a.similar(b));
}


TEST(Plane, SimilarUsesSeparateNormalAndOffsetTolerance)
{
    Fplane a = make_plane(1.0f, 2.0f, 3.0f, 4.0f);
    Fplane b = make_plane(1.0f, 2.0f, 3.0f, 4.0f + 0.001f);

    EXPECT_TRUE(a.similar(b, 0.001f, 0.01f));
    EXPECT_FALSE(a.similar(b, 0.001f, 0.0001f));
}


// -----------------------------------------------------------------------------
// Build from three points
// -----------------------------------------------------------------------------

TEST(Plane, BuildFromThreePoints)
{
    Fplane plane;

    Fvector a = {0.0f, 0.0f, 0.0f};
    Fvector b = {1.0f, 0.0f, 0.0f};
    Fvector c = {0.0f, 1.0f, 0.0f};

    EXPECT_EQ(&plane.build(a, b, c), &plane);

    expect_vec_near(plane.n, 0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(plane.d, 0.0f);
}


TEST(Plane, BuildFromThreePointsProducesUnitNormal)
{
    Fplane plane;

    Fvector a = {1.0f, 2.0f, 3.0f};
    Fvector b = {4.0f, 2.0f, 3.0f};
    Fvector c = {1.0f, 7.0f, 3.0f};

    plane.build(a, b, c);

    EXPECT_NEAR(plane.n.magnitude(), 1.0f, EPSILON);
}


TEST(Plane, BuildFromThreePointsClassifiesInputPointsAsOnPlane)
{
    Fplane plane;

    Fvector a = {1.0f, 2.0f, 3.0f};
    Fvector b = {4.0f, 2.0f, 3.0f};
    Fvector c = {1.0f, 7.0f, 3.0f};

    plane.build(a, b, c);

    EXPECT_NEAR(plane.classify(a), 0.0f, EPSILON);
    EXPECT_NEAR(plane.classify(b), 0.0f, EPSILON);
    EXPECT_NEAR(plane.classify(c), 0.0f, EPSILON);
}


TEST(Plane, BuildPreciseFromThreePoints)
{
    Fplane plane;

    Fvector a = {1.0f, 2.0f, 3.0f};
    Fvector b = {4.0f, 2.0f, 3.0f};
    Fvector c = {1.0f, 7.0f, 3.0f};

    EXPECT_EQ(&plane.build_precise(a, b, c), &plane);

    expect_vec_near(plane.n, 0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(plane.d, -3.0f);
}


// -----------------------------------------------------------------------------
// Build from point + normal
// -----------------------------------------------------------------------------

TEST(Plane, BuildFromPointAndNormal)
{
    Fplane plane;

    Fvector point = {0.0f, 0.0f, 5.0f};
    Fvector normal = {0.0f, 0.0f, 1.0f};

    EXPECT_EQ(&plane.build(point, normal), &plane);

    expect_vec_near(plane.n, 0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(plane.d, -5.0f);
}


TEST(Plane, BuildFromPointAndNonUnitNormalNormalizesNormal)
{
    Fplane plane;

    Fvector point = {0.0f, 0.0f, 5.0f};
    Fvector normal = {0.0f, 0.0f, 10.0f};

    plane.build(point, normal);

    EXPECT_NEAR(plane.n.magnitude(), 1.0f, EPSILON);
    EXPECT_NEAR(plane.classify(point), 0.0f, EPSILON);
}


TEST(Plane, BuildUnitNormalPreservesUnitNormal)
{
    Fplane plane;

    Fvector point = {1.0f, 2.0f, 3.0f};
    Fvector normal = {0.0f, 0.0f, 1.0f};

    EXPECT_EQ(&plane.build_unit_normal(point, normal), &plane);

    expect_vec_near(plane.n, 0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(plane.d, -3.0f);
}


// -----------------------------------------------------------------------------
// Classification
// -----------------------------------------------------------------------------

TEST(Plane, ClassifyPointOnPlane)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector point = {100.0f, -200.0f, 5.0f};

    EXPECT_NEAR(plane.classify(point), 0.0f, EPSILON);
}


TEST(Plane, ClassifyPointInPositiveHalfSpace)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector point = {0.0f, 0.0f, 10.0f};

    EXPECT_FLOAT_EQ(plane.classify(point), 5.0f);
}


TEST(Plane, ClassifyPointInNegativeHalfSpace)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector point = {0.0f, 0.0f, 2.0f};

    EXPECT_FLOAT_EQ(plane.classify(point), -3.0f);
}


// -----------------------------------------------------------------------------
// Distance
// -----------------------------------------------------------------------------

TEST(Plane, DistanceToPlaneIsZero)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector point = {10.0f, 20.0f, 5.0f};

    EXPECT_FLOAT_EQ(plane.distance(point), 0.0f);
}


TEST(Plane, DistanceIsAbsoluteClassification)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector above = {0.0f, 0.0f, 8.0f};
    Fvector below = {0.0f, 0.0f, 2.0f};

    EXPECT_FLOAT_EQ(plane.distance(above), 3.0f);
    EXPECT_FLOAT_EQ(plane.distance(below), 3.0f);
}


// -----------------------------------------------------------------------------
// Projection
// -----------------------------------------------------------------------------

TEST(Plane, ProjectPointOntoPlane)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector source = {1.0f, 2.0f, 10.0f};
    Fvector projected;

    EXPECT_EQ(&plane.project(projected, source), &plane);

    expect_vec_near(projected, 1.0f, 2.0f, 5.0f);
}


TEST(Plane, ProjectPointBelowPlane)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector source = {1.0f, 2.0f, 2.0f};
    Fvector projected;

    plane.project(projected, source);

    expect_vec_near(projected, 1.0f, 2.0f, 5.0f);
}


TEST(Plane, ProjectPointAlreadyOnPlane)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector source = {1.0f, 2.0f, 5.0f};
    Fvector projected;

    plane.project(projected, source);

    expect_vec_near(projected, source.x, source.y, source.z);
}


// -----------------------------------------------------------------------------
// Normalization
// -----------------------------------------------------------------------------

TEST(Plane, NormalizeNormalizesNormalAndOffset)
{
    Fplane plane = make_plane(0.0f, 0.0f, 2.0f, -10.0f);

    EXPECT_EQ(&plane.normalize(), &plane);

    expect_vec_near(plane.n, 0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(plane.d, -5.0f);
}


TEST(Plane, NormalizePreservesPlaneGeometry)
{
    Fplane plane = make_plane(1.0f, 2.0f, 3.0f, -12.0f);

    Fvector point = {1.0f, 2.0f, 3.0f};

    const float before = plane.classify(point);

    plane.normalize();

    const float after = plane.classify(point);

    EXPECT_NEAR(after, before / std::sqrt(14.0f), EPSILON);
    EXPECT_NEAR(plane.n.magnitude(), 1.0f, EPSILON);
}


// -----------------------------------------------------------------------------
// Ray intersection - distance
// -----------------------------------------------------------------------------

TEST(Plane, IntersectRayDistFromPositiveSide)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {0.0f, 0.0f, 10.0f};
    Fvector direction = {0.0f, 0.0f, -1.0f};

    float distance = -1.0f;

    EXPECT_TRUE(plane.intersectRayDist(origin, direction, distance));
    EXPECT_FLOAT_EQ(distance, 10.0f);
}


TEST(Plane, IntersectRayDistFromNegativeSide)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {0.0f, 0.0f, -10.0f};
    Fvector direction = {0.0f, 0.0f, 1.0f};

    float distance = -1.0f;

    EXPECT_TRUE(plane.intersectRayDist(origin, direction, distance));
    EXPECT_FLOAT_EQ(distance, 10.0f);
}


TEST(Plane, IntersectRayDistStartingOnPlane)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {1.0f, 2.0f, 0.0f};
    Fvector direction = {0.0f, 0.0f, 1.0f};

    float distance = -1.0f;

    EXPECT_TRUE(plane.intersectRayDist(origin, direction, distance));
    EXPECT_FLOAT_EQ(distance, 0.0f);
}


TEST(Plane, IntersectRayDistRejectsIntersectionBehindOrigin)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {0.0f, 0.0f, 10.0f};
    Fvector direction = {0.0f, 0.0f, 1.0f};

    float distance = 123.0f;

    EXPECT_FALSE(plane.intersectRayDist(origin, direction, distance));
}


TEST(Plane, IntersectRayDistRejectsParallelRay)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {0.0f, 0.0f, 10.0f};
    Fvector direction = {1.0f, 0.0f, 0.0f};

    float distance = 123.0f;

    EXPECT_FALSE(plane.intersectRayDist(origin, direction, distance));
}


// -----------------------------------------------------------------------------
// Ray intersection - point
// -----------------------------------------------------------------------------

TEST(Plane, IntersectRayPoint)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {1.0f, 2.0f, 10.0f};
    Fvector direction = {0.0f, 0.0f, -1.0f};

    Fvector intersection;

    EXPECT_TRUE(
        plane.intersectRayPoint(origin, direction, intersection)
    );

    expect_vec_near(intersection, 1.0f, 2.0f, 0.0f);
}


TEST(Plane, IntersectRayPointRejectsBehindOrigin)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {1.0f, 2.0f, 10.0f};
    Fvector direction = {0.0f, 0.0f, 1.0f};

    Fvector intersection = {99.0f, 99.0f, 99.0f};

    EXPECT_FALSE(
        plane.intersectRayPoint(origin, direction, intersection)
    );
}


TEST(Plane, IntersectRayPointRejectsParallelRay)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector origin = {1.0f, 2.0f, 10.0f};
    Fvector direction = {1.0f, 0.0f, 0.0f};

    Fvector intersection = {99.0f, 99.0f, 99.0f};

    EXPECT_FALSE(
        plane.intersectRayPoint(origin, direction, intersection)
    );
}


// -----------------------------------------------------------------------------
// Segment intersection
// -----------------------------------------------------------------------------

TEST(Plane, IntersectSegment)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector a = {0.0f, 0.0f, -10.0f};
    Fvector b = {0.0f, 0.0f, 10.0f};

    Fvector intersection;

    EXPECT_TRUE(plane.intersect(a, b, intersection));

    expect_vec_near(intersection, 0.0f, 0.0f, 0.0f);
}


TEST(Plane, IntersectSegmentWithArbitraryCoordinates)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector a = {1.0f, 2.0f, 0.0f};
    Fvector b = {5.0f, 8.0f, 10.0f};

    Fvector intersection;

    EXPECT_TRUE(plane.intersect(a, b, intersection));

    expect_vec_near(intersection, 3.0f, 5.0f, 5.0f);
}


TEST(Plane, IntersectSegmentRejectsSegmentEntirelyOnOneSide)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector a = {0.0f, 0.0f, 1.0f};
    Fvector b = {0.0f, 0.0f, 10.0f};

    Fvector intersection = {99.0f, 99.0f, 99.0f};

    EXPECT_FALSE(plane.intersect(a, b, intersection));
}


TEST(Plane, IntersectSegmentParallel)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector a = {0.0f, 0.0f, 5.0f};
    Fvector b = {10.0f, 0.0f, 5.0f};

    Fvector intersection = {99.0f, 99.0f, 99.0f};

    EXPECT_FALSE(plane.intersect(a, b, intersection));
}


TEST(Plane, IntersectSegmentEndpoint)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector a = {0.0f, 0.0f, 0.0f};
    Fvector b = {0.0f, 0.0f, 10.0f};

    Fvector intersection;

    EXPECT_TRUE(plane.intersect(a, b, intersection));

    expect_vec_near(intersection, 0.0f, 0.0f, 0.0f);
}


// -----------------------------------------------------------------------------
// intersect_2
//
// This deliberately tests the CURRENT implementation's behavior.
// Do not replace these expectations with the mathematically conventional
// segment-intersection behavior without first deciding that the implementation
// itself should change.
// -----------------------------------------------------------------------------

TEST(Plane, Intersect2ReturnsIntersectionForCurrentImplementation)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, 0.0f);

    Fvector a = {0.0f, 0.0f, -10.0f};
    Fvector b = {0.0f, 0.0f, 10.0f};

    Fvector intersection;

    EXPECT_TRUE(plane.intersect_2(a, b, intersection));
}


TEST(Plane, Intersect2UsesEndpointClassifications)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector a = {0.0f, 0.0f, 0.0f};
    Fvector b = {0.0f, 0.0f, 10.0f};

    Fvector intersection;

    EXPECT_TRUE(plane.intersect_2(a, b, intersection));
}


TEST(Plane, Intersect2CurrentParallelBehavior)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fvector a = {0.0f, 0.0f, 1.0f};
    Fvector b = {10.0f, 0.0f, 1.0f};

    Fvector intersection;

    // Regression test for the current implementation rather than a claim
    // that this is the desired mathematical behavior.
    EXPECT_TRUE(plane.intersect_2(a, b, intersection));
}


// -----------------------------------------------------------------------------
// Transform
// -----------------------------------------------------------------------------

TEST(Plane, TransformTranslation)
{
    Fplane plane = make_plane(0.0f, 0.0f, 1.0f, -5.0f);

    Fmatrix matrix;
    matrix.identity();
    matrix.translate_over(0.0f, 0.0f, 10.0f);

    EXPECT_EQ(&plane.transform(matrix), &plane);

    expect_vec_near(plane.n, 0.0f, 0.0f, 1.0f);

    // The implementation applies:
    //
    // d -= M.c.dot(n)
    //
    // with the current matrix representation.
    EXPECT_FLOAT_EQ(plane.d, -15.0f);
}


TEST(Plane, TransformRotation)
{
    Fplane plane = make_plane(1.0f, 0.0f, 0.0f, -5.0f);

    Fmatrix matrix;
    matrix.identity();
    matrix.rotateZ(M_PI_2);

    plane.transform(matrix);

    Fvector expected = {1.0f, 0.0f, 0.0f};
    matrix.transform_dir(expected);

    expect_vec_near(
        plane.n,
        expected.x,
        expected.y,
        expected.z,
        1e-4f
    );
}


TEST(Plane, TransformDoesNotChangeNormalMagnitude)
{
    Fplane plane = make_plane(
        1.0f / std::sqrt(14.0f),
        2.0f / std::sqrt(14.0f),
        3.0f / std::sqrt(14.0f),
        -5.0f
    );

    const float originalMagnitude = plane.n.magnitude();

    Fmatrix matrix;
    matrix.identity();
    matrix.rotateX(0.3f);
    matrix.rotateY(-0.7f);
    matrix.rotateZ(1.1f);

    plane.transform(matrix);

    EXPECT_NEAR(
        plane.n.magnitude(),
        originalMagnitude,
        1e-4f
    );
}


// -----------------------------------------------------------------------------
// Plane geometry invariants
// -----------------------------------------------------------------------------

TEST(Plane, BuildThenProjectReturnsOriginalPoint)
{
    Fplane plane;

    Fvector a = {1.0f, 2.0f, 3.0f};
    Fvector b = {4.0f, 2.0f, 3.0f};
    Fvector c = {1.0f, 7.0f, 3.0f};

    plane.build(a, b, c);

    Fvector projected;
    plane.project(projected, b);

    expect_vec_near(
        projected,
        b.x,
        b.y,
        b.z
    );
}


TEST(Plane, ProjectedPointClassifiesAsOnPlane)
{
    Fplane plane = make_plane(1.0f, 2.0f, 3.0f, -14.0f);

    Fvector source = {10.0f, 20.0f, 30.0f};
    Fvector projected;

    plane.project(projected, source);

    EXPECT_NEAR(
        plane.classify(projected),
        0.0f,
        EPSILON
    );
}


TEST(Plane, IntersectionPointClassifiesAsOnPlane)
{
    Fplane plane = make_plane(1.0f, 2.0f, 3.0f, -14.0f);

    Fvector a = {0.0f, 0.0f, 0.0f};
    Fvector b = {10.0f, 20.0f, 30.0f};

    Fvector intersection;

    ASSERT_TRUE(plane.intersect(a, b, intersection));

    EXPECT_NEAR(
        plane.classify(intersection),
        0.0f,
        EPSILON
    );
}
