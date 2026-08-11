#include "../xrCore/xrCore.h"
#include "../ode_include.h"
#include "../xrCore/_stl_extensions.h"
#include "../xrCDB/xrCDB.h"
#include "dTriCylinder.h"

#include <gtest/gtest.h>

class DcTriListColliderTest : public ::testing::Test
{
protected:
    static void ExpectVec3Near(
        const dReal* actual,
        const dReal* expected,
        dReal epsilon = REAL(1e-5))
    {
        EXPECT_NEAR(actual[0], expected[0], epsilon);
        EXPECT_NEAR(actual[1], expected[1], epsilon);
        EXPECT_NEAR(actual[2], expected[2], epsilon);
    }
};


#if 0
TEST_F(DcTriListColliderTest, CircleLineIntersection_HitsCircle)
{
    dcTriListCollider* collider = nullptr;

    const dVector3 circleNormal = {0.f, 0.f, 1.f};
    const dVector3 circleCenter = {0.f, 0.f, 0.f};

    // Line: (-2, 0, 0) + t * (1, 0, 0)
    const dVector3 lineVector = {1.f, 0.f, 0.f};
    const dVector3 linePoint = {-2.f, 0.f, 0.f};

    dVector3 point;

    const bool result = collider->circleLineIntersection(
        circleNormal,
        circleCenter,
        1.f,
        lineVector,
        linePoint,
        1.f,
        point);

    ASSERT_TRUE(result);

    // Both intersections are (-1, 0, 0) and (1, 0, 0).
    // sign = +1 selects the one closest to the positive normal side.
    ExpectVec3Near(point, {1.f, 0.f, 0.f});
}
#endif


#if 0
TEST_F(DcTriListColliderTest, CircleLineIntersection_SelectsOppositeIntersection)
{
    dcTriListCollider* collider = nullptr;

    const dVector3 circleNormal = {0.f, 0.f, 1.f};
    const dVector3 circleCenter = {0.f, 0.f, 0.f};

    const dVector3 lineVector = {1.f, 0.f, 0.f};
    const dVector3 linePoint = {-2.f, 0.f, 0.f};

    dVector3 point;

    const bool result = collider->circleLineIntersection(
        circleNormal,
        circleCenter,
        1.f,
        lineVector,
        linePoint,
        -1.f,
        point);

    ASSERT_TRUE(result);

    ExpectVec3Near(point, {-1.f, 0.f, 0.f});
}
#endif


#if 0
TEST_F(DcTriListColliderTest, CircleLineIntersection_MissesCircle)
{
    dcTriListCollider* collider = nullptr;

    const dVector3 circleNormal = {0.f, 0.f, 1.f};
    const dVector3 circleCenter = {0.f, 0.f, 0.f};

    // Parallel line at y = 2, radius = 1.
    const dVector3 lineVector = {1.f, 0.f, 0.f};
    const dVector3 linePoint = {-2.f, 2.f, 0.f};

    dVector3 point;

    const bool result = collider->circleLineIntersection(
        circleNormal,
        circleCenter,
        1.f,
        lineVector,
        linePoint,
        1.f,
        point);

    EXPECT_FALSE(result);
}
#endif


#if 0
TEST_F(DcTriListColliderTest, CircleLineIntersection_Tangent)
{
    dcTriListCollider* collider = nullptr;

    const dVector3 circleNormal = {0.f, 0.f, 1.f};
    const dVector3 circleCenter = {0.f, 0.f, 0.f};

    // Tangent at (0, 1, 0).
    const dVector3 lineVector = {1.f, 0.f, 0.f};
    const dVector3 linePoint = {-2.f, 1.f, 0.f};

    dVector3 point;

    const bool result = collider->circleLineIntersection(
        circleNormal,
        circleCenter,
        1.f,
        lineVector,
        linePoint,
        1.f,
        point);

    ASSERT_TRUE(result);
    ExpectVec3Near(point, {0.f, 1.f, 0.f});
}
#endif


#if 0
TEST_F(DcTriListColliderTest, CylinderCrossesLine_IntersectionInsideCylinder)
{
    dcTriListCollider* collider = nullptr;

    // Cylinder:
    // center = origin
    // axis  = +Z
    // half-length = 2
    const dVector3 cylinderPosition = {0.f, 0.f, 0.f};
    const dVector3 cylinderAxis = {0.f, 0.f, 1.f};

    // Triangle edge lies along X and crosses the cylinder axis.
    const dVector3 v0 = {-2.f, 0.f, 0.f};
    const dVector3 v1 = {2.f, 0.f, 0.f};
    const dVector3 line = {1.f, 0.f, 0.f};

    dVector3 position;

    const bool result = collider->cylinderCrossesLine(
        cylinderPosition,
        cylinderAxis,
        2.f,
        v0,
        v1,
        line,
        position);

    ASSERT_TRUE(result);
    ExpectVec3Near(position, {0.f, 0.f, 0.f});
}
#endif


#if 0
TEST_F(DcTriListColliderTest, CylinderCrossesLine_OutsideCylinderHeight)
{
    dcTriListCollider* collider = nullptr;

    const dVector3 cylinderPosition = {0.f, 0.f, 0.f};
    const dVector3 cylinderAxis = {0.f, 0.f, 1.f};

    const dVector3 v0 = {-2.f, 0.f, 3.f};
    const dVector3 v1 = {2.f, 0.f, 3.f};
    const dVector3 line = {1.f, 0.f, 0.f};

    dVector3 position;

    const bool result = collider->cylinderCrossesLine(
        cylinderPosition,
        cylinderAxis,
        2.f,
        v0,
        v1,
        line,
        position);

    EXPECT_FALSE(result);
}
#endif


#if 0
TEST_F(DcTriListColliderTest, CylinderCrossesLine_IntersectionOutsideSegment)
{
    dcTriListCollider* collider = nullptr;

    const dVector3 cylinderPosition = {0.f, 0.f, 0.f};
    const dVector3 cylinderAxis = {0.f, 0.f, 1.f};

    // Segment only covers x = [-2, -1].
    // The infinite line intersects the cylinder at x = 0,
    // but that point isn't part of the segment.
    const dVector3 v0 = {-2.f, 0.f, 0.f};
    const dVector3 v1 = {-1.f, 0.f, 0.f};
    const dVector3 line = {1.f, 0.f, 0.f};

    dVector3 position;

    const bool result = collider->cylinderCrossesLine(
        cylinderPosition,
        cylinderAxis,
        2.f,
        v0,
        v1,
        line,
        position);

    EXPECT_FALSE(result);
}
#endif


#if 0
TEST_F(DcTriListColliderTest, CylinderCrossesLine_ParallelLines)
{
    dcTriListCollider* collider = nullptr;

    const dVector3 cylinderPosition = {0.f, 0.f, 0.f};
    const dVector3 cylinderAxis = {0.f, 0.f, 1.f};

    // l is parallel to the cylinder axis.
    const dVector3 v0 = {0.f, 0.f, -1.f};
    const dVector3 v1 = {0.f, 0.f, 1.f};
    const dVector3 line = {0.f, 0.f, 1.f};

    dVector3 position;

    const bool result = collider->cylinderCrossesLine(
        cylinderPosition,
        cylinderAxis,
        2.f,
        v0,
        v1,
        line,
        position);

    EXPECT_FALSE(result);
}
#endif
