#include "stdafx.h"

#include "_plane2.h"

#include <gtest/gtest.h>

namespace
{
    constexpr float EPSILON = 1e-5f;

    void expect_vec_near(
        const Fvector2& actual,
        float x,
        float y,
        float epsilon = EPSILON)
    {
        EXPECT_NEAR(actual.x, x, epsilon);
        EXPECT_NEAR(actual.y, y, epsilon);
    }

    Fplane2 make_plane(
        float nx,
        float ny,
        float d)
    {
        Fplane2 plane;
        plane.n.set(nx, ny);
        plane.d = d;
        return plane;
    }
}


// -----------------------------------------------------------------------------
// Construction / copying
// -----------------------------------------------------------------------------

TEST(Plane2, SetCopiesNormalAndOffset)
{
    Fplane2 source = make_plane(1.0f, 2.0f, 3.0f);
    Fplane2 destination = make_plane(10.0f, 20.0f, 30.0f);

    EXPECT_EQ(&destination.set(source), &destination);

    expect_vec_near(destination.n, 1.0f, 2.0f);
    EXPECT_FLOAT_EQ(destination.d, 3.0f);
}


TEST(Plane2, SimilarReturnsTrueForEqualPlanes)
{
    Fplane2 a = make_plane(1.0f, 2.0f, 3.0f);
    Fplane2 b = make_plane(1.0f, 2.0f, 3.0f);

    EXPECT_TRUE(a.similar(b));
}


TEST(Plane2, SimilarReturnsFalseForDifferentNormal)
{
    Fplane2 a = make_plane(1.0f, 2.0f, 3.0f);
    Fplane2 b = make_plane(1.0f, 2.1f, 3.0f);

    EXPECT_FALSE(a.similar(b));
}


TEST(Plane2, SimilarReturnsFalseForDifferentOffset)
{
    Fplane2 a = make_plane(1.0f, 2.0f, 3.0f);
    Fplane2 b = make_plane(1.0f, 2.0f, 3.1f);

    EXPECT_FALSE(a.similar(b));
}


TEST(Plane2, SimilarUsesSeparateNormalAndOffsetTolerance)
{
    Fplane2 a = make_plane(1.0f, 2.0f, 3.0f);
    Fplane2 b = make_plane(1.0f, 2.0f, 3.001f);

    EXPECT_TRUE(a.similar(b, 0.001f, 0.01f));
    EXPECT_FALSE(a.similar(b, 0.001f, 0.0001f));
}


// -----------------------------------------------------------------------------
// Build
// -----------------------------------------------------------------------------

TEST(Plane2, BuildFromPointAndNormal)
{
    Fplane2 plane;

    Fvector2 point = {0.0f, 5.0f};
    Fvector2 normal = {0.0f, 1.0f};

    EXPECT_EQ(&plane.build(point, normal), &plane);

    expect_vec_near(plane.n, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(plane.d, -5.0f);
}


TEST(Plane2, BuildNormalizesNonUnitNormal)
{
    Fplane2 plane;

    Fvector2 point = {0.0f, 5.0f};
    Fvector2 normal = {0.0f, 10.0f};

    plane.build(point, normal);

    EXPECT_NEAR(plane.n.magnitude(), 1.0f, EPSILON);
    EXPECT_NEAR(plane.classify(point), 0.0f, EPSILON);
}


TEST(Plane2, BuildPointIsOnPlane)
{
    Fplane2 plane;

    Fvector2 point = {3.0f, 7.0f};
    Fvector2 normal = {1.0f, 2.0f};

    plane.build(point, normal);

    EXPECT_NEAR(plane.classify(point), 0.0f, EPSILON);
}


// -----------------------------------------------------------------------------
// Classification
// -----------------------------------------------------------------------------

TEST(Plane2, ClassifyPointOnPlane)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 point = {100.0f, 5.0f};

    EXPECT_NEAR(plane.classify(point), 0.0f, EPSILON);
}


TEST(Plane2, ClassifyPositiveHalfSpace)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 point = {0.0f, 10.0f};

    EXPECT_FLOAT_EQ(plane.classify(point), 5.0f);
}


TEST(Plane2, ClassifyNegativeHalfSpace)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 point = {0.0f, 2.0f};

    EXPECT_FLOAT_EQ(plane.classify(point), -3.0f);
}


// -----------------------------------------------------------------------------
// Projection
// -----------------------------------------------------------------------------

TEST(Plane2, ProjectPointOntoPlane)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 source = {10.0f, 10.0f};
    Fvector2 projected;

    EXPECT_EQ(&plane.project(projected, source), &plane);

    expect_vec_near(projected, 10.0f, 5.0f);
}


TEST(Plane2, ProjectPointBelowPlane)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 source = {10.0f, 2.0f};
    Fvector2 projected;

    plane.project(projected, source);

    expect_vec_near(projected, 10.0f, 5.0f);
}


TEST(Plane2, ProjectPointAlreadyOnPlane)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 source = {10.0f, 5.0f};
    Fvector2 projected;

    plane.project(projected, source);

    expect_vec_near(projected, source.x, source.y);
}


TEST(Plane2, ProjectedPointClassifiesAsOnPlane)
{
    Fplane2 plane = make_plane(1.0f, 2.0f, -10.0f);

    Fvector2 source = {10.0f, 20.0f};
    Fvector2 projected;

    plane.project(projected, source);

    EXPECT_NEAR(
        plane.classify(projected),
        0.0f,
        EPSILON
    );
}


// -----------------------------------------------------------------------------
// Normalization
// -----------------------------------------------------------------------------

TEST(Plane2, NormalizeNormalizesNormalAndOffset)
{
    Fplane2 plane = make_plane(0.0f, 2.0f, -10.0f);

    EXPECT_EQ(&plane.normalize(), &plane);

    expect_vec_near(plane.n, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(plane.d, -5.0f);
}


TEST(Plane2, NormalizeProducesUnitNormal)
{
    Fplane2 plane = make_plane(3.0f, 4.0f, -20.0f);

    plane.normalize();

    EXPECT_NEAR(plane.n.magnitude(), 1.0f, EPSILON);
}


TEST(Plane2, NormalizePreservesPlaneGeometry)
{
    Fplane2 plane = make_plane(3.0f, 4.0f, -20.0f);

    Fvector2 point = {4.0f, 2.0f};

    const float before = plane.classify(point);

    plane.normalize();

    const float after = plane.classify(point);

    EXPECT_NEAR(after, before / 5.0f, EPSILON);
}


// -----------------------------------------------------------------------------
// Distance
// -----------------------------------------------------------------------------

TEST(Plane2, DistanceToPlaneIsZero)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 point = {10.0f, 5.0f};

    EXPECT_FLOAT_EQ(plane.distance(point), 0.0f);
}


TEST(Plane2, DistanceIsAbsoluteClassification)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 above = {0.0f, 8.0f};
    Fvector2 below = {0.0f, 2.0f};

    EXPECT_FLOAT_EQ(plane.distance(above), 3.0f);
    EXPECT_FLOAT_EQ(plane.distance(below), 3.0f);
}


// -----------------------------------------------------------------------------
// Ray intersection - distance
// -----------------------------------------------------------------------------

TEST(Plane2, IntersectRayDist)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, 10.0f};
    Fvector2 direction = {0.0f, -1.0f};

    float distance = -1.0f;

    EXPECT_TRUE(
        plane.intersectRayDist(origin, direction, distance)
    );

    EXPECT_FLOAT_EQ(distance, 10.0f);
}


TEST(Plane2, IntersectRayDistFromNegativeSide)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, -10.0f};
    Fvector2 direction = {0.0f, 1.0f};

    float distance = -1.0f;

    EXPECT_TRUE(
        plane.intersectRayDist(origin, direction, distance)
    );

    EXPECT_FLOAT_EQ(distance, 10.0f);
}


TEST(Plane2, IntersectRayDistStartingOnPlane)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, 0.0f};
    Fvector2 direction = {0.0f, 1.0f};

    float distance = -1.0f;

    EXPECT_TRUE(
        plane.intersectRayDist(origin, direction, distance)
    );

    EXPECT_FLOAT_EQ(distance, 0.0f);
}


TEST(Plane2, IntersectRayDistRejectsBehindOrigin)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, 10.0f};
    Fvector2 direction = {0.0f, 1.0f};

    float distance = 123.0f;

    EXPECT_FALSE(
        plane.intersectRayDist(origin, direction, distance)
    );
}


TEST(Plane2, IntersectRayDistRejectsParallelRay)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, 10.0f};
    Fvector2 direction = {1.0f, 0.0f};

    float distance = 123.0f;

    EXPECT_FALSE(
        plane.intersectRayDist(origin, direction, distance)
    );
}


// -----------------------------------------------------------------------------
// Ray intersection - point
// -----------------------------------------------------------------------------

TEST(Plane2, IntersectRayPoint)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, 10.0f};
    Fvector2 direction = {0.0f, -1.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersectRayPoint(
            origin,
            direction,
            intersection
        )
    );

    expect_vec_near(intersection, 10.0f, 0.0f);
}


TEST(Plane2, IntersectRayPointFromNegativeSide)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, -10.0f};
    Fvector2 direction = {0.0f, 1.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersectRayPoint(
            origin,
            direction,
            intersection
        )
    );

    expect_vec_near(intersection, 10.0f, 0.0f);
}


TEST(Plane2, IntersectRayPointRejectsBehindOrigin)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, 10.0f};
    Fvector2 direction = {0.0f, 1.0f};

    Fvector2 intersection = {99.0f, 99.0f};

    EXPECT_FALSE(
        plane.intersectRayPoint(
            origin,
            direction,
            intersection
        )
    );
}


TEST(Plane2, IntersectRayPointRejectsParallelRay)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 origin = {10.0f, 10.0f};
    Fvector2 direction = {1.0f, 0.0f};

    Fvector2 intersection = {99.0f, 99.0f};

    EXPECT_FALSE(
        plane.intersectRayPoint(
            origin,
            direction,
            intersection
        )
    );
}


// -----------------------------------------------------------------------------
// Segment intersection
// -----------------------------------------------------------------------------

TEST(Plane2, IntersectSegment)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 a = {0.0f, -10.0f};
    Fvector2 b = {0.0f, 10.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersect(a, b, intersection)
    );

    expect_vec_near(intersection, 0.0f, 0.0f);
}


TEST(Plane2, IntersectSegmentWithArbitraryCoordinates)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 a = {1.0f, 0.0f};
    Fvector2 b = {5.0f, 10.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersect(a, b, intersection)
    );

    expect_vec_near(intersection, 3.0f, 5.0f);
}


TEST(Plane2, IntersectSegmentRejectsSegmentEntirelyOnOneSide)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 a = {0.0f, 1.0f};
    Fvector2 b = {0.0f, 10.0f};

    Fvector2 intersection = {99.0f, 99.0f};

    EXPECT_FALSE(
        plane.intersect(a, b, intersection)
    );
}


TEST(Plane2, IntersectSegmentParallel)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -5.0f);

    Fvector2 a = {0.0f, 10.0f};
    Fvector2 b = {10.0f, 10.0f};

    Fvector2 intersection = {99.0f, 99.0f};

    EXPECT_FALSE(
        plane.intersect(a, b, intersection)
    );
}


TEST(Plane2, IntersectSegmentAtFirstEndpoint)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 a = {0.0f, 0.0f};
    Fvector2 b = {0.0f, 10.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersect(a, b, intersection)
    );

    expect_vec_near(intersection, 0.0f, 0.0f);
}


TEST(Plane2, IntersectSegmentAtSecondEndpoint)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, -10.0f);

    Fvector2 a = {0.0f, 0.0f};
    Fvector2 b = {0.0f, 10.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersect(a, b, intersection)
    );

    expect_vec_near(intersection, 0.0f, 10.0f);
}


// -----------------------------------------------------------------------------
// intersect_2
//
// These tests intentionally preserve the CURRENT implementation's behavior.
// -----------------------------------------------------------------------------

TEST(Plane2, Intersect2ReturnsCurrentCrossingBehavior)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 a = {0.0f, -10.0f};
    Fvector2 b = {0.0f, 10.0f};

    Fvector2 intersection;

    EXPECT_FALSE(
        plane.intersect_2(a, b, intersection)
    );
}


TEST(Plane2, Intersect2ReturnsTrueWhenEndpointsHaveSameSign)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 a = {0.0f, 1.0f};
    Fvector2 b = {0.0f, 10.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersect_2(a, b, intersection)
    );
}


TEST(Plane2, Intersect2ReturnsTrueWhenBothEndpointsAreNegative)
{
    Fplane2 plane = make_plane(0.0f, 1.0f, 0.0f);

    Fvector2 a = {0.0f, -10.0f};
    Fvector2 b = {0.0f, -1.0f};

    Fvector2 intersection;

    EXPECT_TRUE(
        plane.intersect_2(a, b, intersection)
    );
}


// -----------------------------------------------------------------------------
// Geometry invariants
// -----------------------------------------------------------------------------

TEST(Plane2, BuildThenProjectPointProducesPointOnPlane)
{
    Fplane2 plane;

    Fvector2 point = {0.0f, 5.0f};
    Fvector2 normal = {0.0f, 1.0f};

    plane.build(point, normal);

    Fvector2 source = {10.0f, 100.0f};
    Fvector2 projected;

    plane.project(projected, source);

    EXPECT_NEAR(
        plane.classify(projected),
        0.0f,
        EPSILON
    );
}


TEST(Plane2, SegmentIntersectionPointLiesOnPlane)
{
    Fplane2 plane = make_plane(1.0f, 2.0f, -10.0f);

    Fvector2 a = {0.0f, 0.0f};
    Fvector2 b = {10.0f, 10.0f};

    Fvector2 intersection;

    ASSERT_TRUE(
        plane.intersect(a, b, intersection)
    );

    EXPECT_NEAR(
        plane.classify(intersection),
        0.0f,
        EPSILON
    );
}
