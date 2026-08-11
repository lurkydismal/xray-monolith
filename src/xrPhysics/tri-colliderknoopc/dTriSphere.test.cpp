#include "../xrCore/xrCore.h"
#include "../ode_include.h"
#include "../xrCore/_stl_extensions.h"
#include "../xrPhysics.h"
#include "dTriColliderCommon.h"
#include "dTriColliderMath.h"
#include "dTriSphere.h"
#include "dcTriListCollider.h"

#include <gtest/gtest.h>

#include <random>

namespace
{
constexpr dReal g_EPS = static_cast<dReal>(1e-5);

void ExpectVec3Near(const dReal* actual, const dReal* expected, dReal eps = g_EPS)
{
    EXPECT_NEAR(actual[0], expected[0], eps);
    EXPECT_NEAR(actual[1], expected[1], eps);
    EXPECT_NEAR(actual[2], expected[2], eps);
}

void ExpectUnitVector(const dReal* v, dReal eps = g_EPS)
{
    const dReal length = dSqrt(dDOT(v, v));
    EXPECT_NEAR(length, static_cast<dReal>(1), eps);
}
} // namespace

#if 0
class PointSphereTest : public ::testing::Test
{
protected:
    dcTriListCollider collider;
};
#endif

// -----------------------------------------------------------------------------
// PointSphereTest(center, radius, point, norm) -> depth
// -----------------------------------------------------------------------------

#if 0
TEST_F(PointSphereTest, PointOutsideSphereReturnsNegativeOne)
{
    const dReal center[] = {0, 0, 0};
    const dReal point[] = {2, 0, 0};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, 1.0, point, normal);

    EXPECT_EQ(result, -1.0);

    // Current implementation still writes the unnormalized vector before
    // discovering that the point is outside.
    const dReal expected[] = {-2, 0, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(PointSphereTest, PointOnSphereReturnsZeroDepth)
{
    const dReal center[] = {0, 0, 0};
    const dReal point[] = {1, 0, 0};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, 1.0, point, normal);

    EXPECT_NEAR(result, 0.0, g_EPS);

    const dReal expected[] = {-1, 0, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(PointSphereTest, PointInsideSphereReturnsPenetrationDepth)
{
    const dReal center[] = {0, 0, 0};
    const dReal point[] = {0.25, 0, 0};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, 1.0, point, normal);

    EXPECT_NEAR(result, 0.75, g_EPS);

    const dReal expected[] = {-1, 0, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(PointSphereTest, NormalPointsFromPointTowardSphereCenter)
{
    const dReal center[] = {10, 20, 30};
    const dReal point[] = {9, 20, 30};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, 2.0, point, normal);

    EXPECT_NEAR(result, 1.0, g_EPS);

    const dReal expected[] = {1, 0, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(PointSphereTest, DiagonalNormalIsNormalized)
{
    const dReal center[] = {0, 0, 0};
    const dReal point[] = {1, 1, 1};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, 2.0, point, normal);

    EXPECT_NEAR(result, 2.0 - dSqrt(3.0), g_EPS);

    const dReal invSqrt3 = 1.0 / dSqrt(3.0);
    const dReal expected[] = {
        -invSqrt3,
        -invSqrt3,
        -invSqrt3
    };

    ExpectVec3Near(normal, expected);
    ExpectUnitVector(normal);
}

TEST_F(PointSphereTest, SphereCenterUsesPositiveYAxisAsFallbackNormal)
{
    const dReal center[] = {5, 6, 7};
    const dReal point[] = {5, 6, 7};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, 2.0, point, normal);

    EXPECT_NEAR(result, 2.0, g_EPS);

    const dReal expected[] = {0, 1, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(PointSphereTest, BoundaryIsConsideredCollision)
{
    const dReal center[] = {1, 2, 3};
    const dReal point[] = {1, 2, 5};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, 2.0, point, normal);

    EXPECT_NEAR(result, 0.0, g_EPS);
}

TEST_F(PointSphereTest, NegativeRadiusCurrentlyProducesNoCollision)
{
    const dReal center[] = {0, 0, 0};
    const dReal point[] = {0, 0, 0};
    dReal normal[3] = {};

    const dReal result =
        collider.PointSphereTest(center, -1.0, point, normal);

    EXPECT_EQ(result, -1.0);
}
#endif

#if 0
class SegmentSphereTest : public ::testing::Test
{
protected:
    dcTriListCollider collider;
};
#endif

// -----------------------------------------------------------------------------
// FragmentonSphereTest(center, radius, pt1, pt2, norm, depth) -> bool
// -----------------------------------------------------------------------------

#if 0
TEST_F(SegmentSphereTest, SegmentThroughSphereIntersects)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, 0, 0};
    const dReal pt2[] = {2, 0, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_TRUE(result);
    EXPECT_NEAR(depth, 1.0, g_EPS);

    const dReal expected[] = {1, 0, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(SegmentSphereTest, SegmentTangentToSphereIntersects)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, 1, 0};
    const dReal pt2[] = {2, 1, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_TRUE(result);
    EXPECT_NEAR(depth, 0.0, g_EPS);

    const dReal expected[] = {0, -1, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(SegmentSphereTest, SegmentOutsideSphereDoesNotIntersect)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, 2, 0};
    const dReal pt2[] = {2, 2, 0};

    dReal normal[] = {123, 456, 789};
    dReal depth = 123;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_FALSE(result);

    // Current implementation leaves outputs untouched on failure.
    EXPECT_EQ(normal[0], 123);
    EXPECT_EQ(normal[1], 456);
    EXPECT_EQ(normal[2], 789);
    EXPECT_EQ(depth, 123);
}

TEST_F(SegmentSphereTest, ClosestPointIsInsideSegment)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, 0.5, 0};
    const dReal pt2[] = {2, 0.5, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_TRUE(result);
    EXPECT_NEAR(depth, 0.5, g_EPS);

    const dReal expected[] = {0, -1, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(SegmentSphereTest, IntersectionAtSegmentEndpoint)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {1, 0, 0};
    const dReal pt2[] = {2, 0, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_TRUE(result);
    EXPECT_NEAR(depth, 0.0, g_EPS);

    const dReal expected[] = {-1, 0, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(SegmentSphereTest, SegmentBeforeSphereDoesNotIntersect)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {2, 0, 0};
    const dReal pt2[] = {3, 0, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_FALSE(result);
}

TEST_F(SegmentSphereTest, SegmentAfterSphereDoesNotIntersect)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-3, 0, 0};
    const dReal pt2[] = {-2, 0, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_FALSE(result);
}

TEST_F(SegmentSphereTest, DiagonalSegmentProducesNormalizedNormal)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, -2, 0};
    const dReal pt2[] = {2, 2, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_TRUE(result);
    EXPECT_NEAR(depth, 1.0, g_EPS);

    const dReal expected[] = {0, 1, 0};

    // The closest point is exactly the sphere center, so the implementation
    // deliberately uses its fallback normal.
    ExpectVec3Near(normal, expected);
    EXPECT_TRUE(std::isfinite(depth));
}

TEST_F(SegmentSphereTest, ClosestPointAtSphereCenterUsesFallbackNormal)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, 0, 0};
    const dReal pt2[] = {2, 0, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    ASSERT_TRUE(collider.FragmentonSphereTest(
        center, 1.0,
        pt1, pt2,
        normal, depth));

    const dReal expected[] = {0, 1, 0};
    ExpectVec3Near(normal, expected);
}
#endif

#if 0
TEST_F(SegmentSphereTest, ZeroLengthSegmentIsCurrentUndefinedBehavior)
{
    // This test is intentionally NOT asserting the result.
    //
    // The implementation divides by sq_mag_V here:
    //
    //     t = -dot_L_V / sq_mag_V;
    //
    // when pt1 == pt2.
    //
    // Do not accidentally "fix" this behavior while modernizing without
    // deciding whether zero-length segments are supposed to be supported.
    GTEST_SKIP() << "Current implementation does not define zero-length segments";
}
#endif

#if 0
TEST_F(SegmentSphereTest, DiagonalSegmentThroughCenterUsesFallbackNormal)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, -2, 0};
    const dReal pt2[] = {2, 2, 0};

    dReal normal[3] = {};
    dReal depth = -1;

    const bool result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal, depth);

    EXPECT_TRUE(result);
    EXPECT_NEAR(depth, 1.0, g_EPS);

    const dReal expected[] = {0, 1, 0};
    ExpectVec3Near(normal, expected);
}

class LegacySegmentSphereTest : public ::testing::Test
{
protected:
    dcTriListCollider collider;
};

TEST_F(LegacySegmentSphereTest, SegmentThroughSphereReturnsDepth)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, 0, 0};
    const dReal pt2[] = {2, 0, 0};

    dReal normal[3] = {};

    const dReal result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal);

    EXPECT_NEAR(result, 1.0, g_EPS);

    const dReal expected[] = {0, 1, 0};
    ExpectVec3Near(normal, expected);
}

TEST_F(LegacySegmentSphereTest, SegmentOutsideSphereReturnsNegativeOne)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-2, 2, 0};
    const dReal pt2[] = {2, 2, 0};

    dReal normal[] = {123, 456, 789};

    const dReal result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal);

    EXPECT_EQ(result, -1.0);
}

TEST_F(LegacySegmentSphereTest, SegmentBeforeSphereReturnsNegativeOne)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {2, 0, 0};
    const dReal pt2[] = {3, 0, 0};

    dReal normal[3] = {};

    const dReal result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal);

    EXPECT_EQ(result, -1.0);
}

TEST_F(LegacySegmentSphereTest, SegmentAfterSphereReturnsNegativeOne)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {-3, 0, 0};
    const dReal pt2[] = {-2, 0, 0};

    dReal normal[3] = {};

    const dReal result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal);

    EXPECT_EQ(result, -1.0);
}

TEST_F(LegacySegmentSphereTest, EndpointCanBeInsideSphere)
{
    const dReal center[] = {0, 0, 0};
    const dReal pt1[] = {0.5, 0, 0};
    const dReal pt2[] = {2, 0, 0};

    dReal normal[3] = {};

    const dReal result =
        collider.FragmentonSphereTest(
            center, 1.0,
            pt1, pt2,
            normal);

    EXPECT_NEAR(result, 0.5, g_EPS);

    const dReal expected[] = {-1, 0, 0};
    ExpectVec3Near(normal, expected);
}
#endif

#if 0
TEST_F(PointSphereTest, RandomPointsPreserveBasicInvariants)
{
    std::mt19937 rng(0x12345678);
    std::uniform_real_distribution<dReal> dist(-10.0, 10.0);

    constexpr int iterations = 10000;

    for (int i = 0; i < iterations; ++i)
    {
        const dReal center[] = {
            dist(rng),
            dist(rng),
            dist(rng)
        };

        const dReal point[] = {
            dist(rng),
            dist(rng),
            dist(rng)
        };

        constexpr dReal radius = 3.0;

        dReal normal[3] = {};

        const dReal result =
            collider.PointSphereTest(
                center,
                radius,
                point,
                normal);

        const dReal dx = center[0] - point[0];
        const dReal dy = center[1] - point[1];
        const dReal dz = center[2] - point[2];
        const dReal distance = dSqrt(dx * dx + dy * dy + dz * dz);

        if (distance > radius)
        {
            EXPECT_EQ(result, -1.0);
        }
        else
        {
            EXPECT_NEAR(result, radius - distance, g_EPS);

            if (distance > 0)
                ExpectUnitVector(normal);
            else
            {
                const dReal expected[] = {0, 1, 0};
                ExpectVec3Near(normal, expected);
            }
        }
    }
}
#endif
