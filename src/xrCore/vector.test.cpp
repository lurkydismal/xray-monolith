#include "stdafx.h"

#include "vector.h"

#include <gtest/gtest.h>

namespace
{
    constexpr float kEps = 1e-5f;

    void expect_vec_eq(const Fvector& actual, float x, float y, float z)
    {
        EXPECT_FLOAT_EQ(actual.x, x);
        EXPECT_FLOAT_EQ(actual.y, y);
        EXPECT_FLOAT_EQ(actual.z, z);
    }

    void expect_vec_near(
        const Fvector& actual,
        float x,
        float y,
        float z,
        float eps = kEps)
    {
        EXPECT_NEAR(actual.x, x, eps);
        EXPECT_NEAR(actual.y, y, eps);
        EXPECT_NEAR(actual.z, z, eps);
    }
}


// =============================================================================
// Floating-point comparison helpers
// =============================================================================

TEST(VectorHelpers, Fsimilar)
{
    EXPECT_TRUE(fsimilar(1.0f, 1.0f));
    EXPECT_TRUE(fsimilar(1.0f, 1.0f + EPS / 2.0f));

    EXPECT_FALSE(fsimilar(1.0f, 1.0f + EPS));
    EXPECT_FALSE(fsimilar(1.0f, 1.1f));
}


TEST(VectorHelpers, FsimilarWithCustomTolerance)
{
    EXPECT_TRUE(fsimilar(1.0f, 1.05f, 0.1f));
    EXPECT_FALSE(fsimilar(1.0f, 1.05f, 0.01f));
}


TEST(VectorHelpers, Dsimilar)
{
    EXPECT_TRUE(dsimilar(1.0, 1.0));
    EXPECT_TRUE(dsimilar(1.0, 1.0 + EPS / 2.0));

    EXPECT_FALSE(dsimilar(1.0, 1.0 + EPS));
    EXPECT_FALSE(dsimilar(1.0, 1.1));
}


TEST(VectorHelpers, FisZero)
{
    EXPECT_TRUE(fis_zero(0.0f));
    EXPECT_TRUE(fis_zero(EPS_S / 2.0f));
    EXPECT_TRUE(fis_zero(-EPS_S / 2.0f));

    EXPECT_FALSE(fis_zero(EPS_S));
    EXPECT_FALSE(fis_zero(1.0f));
}


TEST(VectorHelpers, DisZero)
{
    EXPECT_TRUE(dis_zero(0.0));
    EXPECT_TRUE(dis_zero(EPS_S / 2.0));
    EXPECT_TRUE(dis_zero(-EPS_S / 2.0));

    EXPECT_FALSE(dis_zero(EPS_S));
    EXPECT_FALSE(dis_zero(1.0));
}


TEST(VectorHelpers, FisZeroCustomTolerance)
{
    EXPECT_TRUE(fis_zero(0.05f, 0.1f));
    EXPECT_FALSE(fis_zero(0.05f, 0.01f));
}


TEST(VectorHelpers, DisZeroCustomTolerance)
{
    EXPECT_TRUE(dis_zero(0.05, 0.1));
    EXPECT_FALSE(dis_zero(0.05, 0.01));
}


// =============================================================================
// Angle conversion
// =============================================================================

TEST(VectorHelpers, Deg2Rad)
{
    EXPECT_NEAR(deg2rad(0.0f), 0.0f, kEps);
    EXPECT_NEAR(deg2rad(90.0f), PI_DIV_2, kEps);
    EXPECT_NEAR(deg2rad(180.0f), PI, kEps);
    EXPECT_NEAR(deg2rad(270.0f), PI_MUL_3 / 2.0f, kEps);
    EXPECT_NEAR(deg2rad(360.0f), PI_MUL_2, kEps);
}


TEST(VectorHelpers, Deg2RadDouble)
{
    EXPECT_NEAR(deg2rad(90.0), static_cast<double>(PI_DIV_2), kEps);
    EXPECT_NEAR(deg2rad(180.0), static_cast<double>(PI), kEps);
}


TEST(VectorHelpers, Rad2Deg)
{
    EXPECT_NEAR(rad2deg(0.0f), 0.0f, kEps);
    EXPECT_NEAR(rad2deg(PI_DIV_2), 90.0f, kEps);
    EXPECT_NEAR(rad2deg(PI), 180.0f, kEps);
    EXPECT_NEAR(rad2deg(PI_MUL_2), 360.0f, kEps);
}


TEST(VectorHelpers, Rad2DegDouble)
{
    EXPECT_NEAR(rad2deg(static_cast<double>(PI_DIV_2)), 90.0, kEps);
    EXPECT_NEAR(rad2deg(static_cast<double>(PI)), 180.0, kEps);
}


// =============================================================================
// Clamping
// =============================================================================

TEST(VectorHelpers, ClampLeavesValueInsideRange)
{
    float value = 5.0f;

    clamp(value, 0.0f, 10.0f);

    EXPECT_FLOAT_EQ(value, 5.0f);
}


TEST(VectorHelpers, ClampClampsLow)
{
    float value = -5.0f;

    clamp(value, 0.0f, 10.0f);

    EXPECT_FLOAT_EQ(value, 0.0f);
}


TEST(VectorHelpers, ClampClampsHigh)
{
    float value = 15.0f;

    clamp(value, 0.0f, 10.0f);

    EXPECT_FLOAT_EQ(value, 10.0f);
}


TEST(VectorHelpers, ClampKeepsBoundaryValues)
{
    float low = 0.0f;
    float high = 10.0f;

    clamp(low, 0.0f, 10.0f);
    clamp(high, 0.0f, 10.0f);

    EXPECT_FLOAT_EQ(low, 0.0f);
    EXPECT_FLOAT_EQ(high, 10.0f);
}


TEST(VectorHelpers, ClamprReturnsValueInsideRange)
{
    EXPECT_FLOAT_EQ(clampr(5.0f, 0.0f, 10.0f), 5.0f);
}


TEST(VectorHelpers, ClamprReturnsLow)
{
    EXPECT_FLOAT_EQ(clampr(-5.0f, 0.0f, 10.0f), 0.0f);
}


TEST(VectorHelpers, ClamprReturnsHigh)
{
    EXPECT_FLOAT_EQ(clampr(15.0f, 0.0f, 10.0f), 10.0f);
}


TEST(VectorHelpers, ClamprKeepsBoundaryValues)
{
    EXPECT_FLOAT_EQ(clampr(0.0f, 0.0f, 10.0f), 0.0f);
    EXPECT_FLOAT_EQ(clampr(10.0f, 0.0f, 10.0f), 10.0f);
}


// =============================================================================
// Snap
// =============================================================================

TEST(VectorHelpers, SnapToRoundsToNearestStep)
{
    EXPECT_FLOAT_EQ(snapto(0.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(snapto(0.49f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(snapto(0.5f, 1.0f), 1.0f);
    EXPECT_FLOAT_EQ(snapto(0.51f, 1.0f), 1.0f);
}


TEST(VectorHelpers, SnapToWorksWithNonUnitStep)
{
    EXPECT_FLOAT_EQ(snapto(1.0f, 2.0f), 2.0f);
    EXPECT_FLOAT_EQ(snapto(2.9f, 2.0f), 2.0f);
    EXPECT_FLOAT_EQ(snapto(3.0f, 2.0f), 4.0f);
    EXPECT_FLOAT_EQ(snapto(3.9f, 2.0f), 4.0f);
}


TEST(VectorHelpers, SnapToHandlesNegativeValues)
{
    EXPECT_FLOAT_EQ(snapto(-0.49f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(snapto(-0.5f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(snapto(-0.51f, 1.0f), -1.0f);
}


TEST(VectorHelpers, SnapToNonPositiveStepReturnsOriginal)
{
    EXPECT_FLOAT_EQ(snapto(3.7f, 0.0f), 3.7f);
    EXPECT_FLOAT_EQ(snapto(3.7f, -1.0f), 3.7f);
}


// =============================================================================
// Linear interpolation
// =============================================================================

TEST(VectorHelpers, LerpAtZero)
{
    EXPECT_FLOAT_EQ(_lerp(10.0f, 20.0f, 0.0f), 10.0f);
}


TEST(VectorHelpers, LerpAtOne)
{
    EXPECT_FLOAT_EQ(_lerp(10.0f, 20.0f, 1.0f), 20.0f);
}


TEST(VectorHelpers, LerpAtHalf)
{
    EXPECT_FLOAT_EQ(_lerp(10.0f, 20.0f, 0.5f), 15.0f);
}


TEST(VectorHelpers, LerpCanExtrapolate)
{
    EXPECT_FLOAT_EQ(_lerp(10.0f, 20.0f, -1.0f), 0.0f);
    EXPECT_FLOAT_EQ(_lerp(10.0f, 20.0f, 2.0f), 30.0f);
}


TEST(VectorHelpers, LerpcClampsFactor)
{
    EXPECT_FLOAT_EQ(_lerpc(10.0f, 20.0f, -1.0f), 10.0f);
    EXPECT_FLOAT_EQ(_lerpc(10.0f, 20.0f, 2.0f), 20.0f);
}


TEST(VectorHelpers, LerpcMatchesLerpInsideRange)
{
    EXPECT_FLOAT_EQ(_lerpc(10.0f, 20.0f, 0.25f), 12.5f);
}


// =============================================================================
// Inertion
// =============================================================================

TEST(VectorHelpers, InertionAtZeroFriction)
{
    EXPECT_FLOAT_EQ(_inertion(10.0f, 20.0f, 0.0f), 20.0f);
}


TEST(VectorHelpers, InertionAtFullFriction)
{
    EXPECT_FLOAT_EQ(_inertion(10.0f, 20.0f, 1.0f), 10.0f);
}


TEST(VectorHelpers, InertionAtHalfFriction)
{
    EXPECT_FLOAT_EQ(_inertion(10.0f, 20.0f, 0.5f), 15.0f);
}


// =============================================================================
// Angle normalization
// =============================================================================

TEST(VectorHelpers, AngleNormalizeAlways)
{
    EXPECT_NEAR(angle_normalize_always(0.0f), 0.0f, kEps);
    EXPECT_NEAR(angle_normalize_always(PI), PI, kEps);
    EXPECT_NEAR(angle_normalize_always(PI_MUL_2), 0.0f, kEps);
    EXPECT_NEAR(angle_normalize_always(PI_MUL_2 + PI_DIV_2), PI_DIV_2, kEps);
}


TEST(VectorHelpers, AngleNormalizeAlwaysNegative)
{
    EXPECT_NEAR(
        angle_normalize_always(-PI_DIV_2),
        PI_MUL_2 - PI_DIV_2,
        kEps
    );

    EXPECT_NEAR(
        angle_normalize_always(-PI_MUL_2),
        0.0f,
        kEps
    );
}


TEST(VectorHelpers, AngleNormalizeKeepsAlreadyNormalizedAngle)
{
    EXPECT_FLOAT_EQ(angle_normalize(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(angle_normalize(PI), PI);
    EXPECT_FLOAT_EQ(angle_normalize(PI_MUL_2), PI_MUL_2);
}


TEST(VectorHelpers, AngleNormalizeWrapsOutsideRange)
{
    EXPECT_NEAR(
        angle_normalize(PI_MUL_2 + PI_DIV_2),
        PI_DIV_2,
        kEps
    );

    EXPECT_NEAR(
        angle_normalize(-PI_DIV_2),
        PI_MUL_2 - PI_DIV_2,
        kEps
    );
}


TEST(VectorHelpers, AngleNormalizeSigned)
{
    EXPECT_NEAR(angle_normalize_signed(0.0f), 0.0f, kEps);
    EXPECT_NEAR(angle_normalize_signed(PI), PI, kEps);
    EXPECT_NEAR(angle_normalize_signed(-PI), -PI, kEps);

    EXPECT_NEAR(
        angle_normalize_signed(PI_MUL_2 + PI_DIV_2),
        PI_DIV_2,
        kEps
    );

    EXPECT_NEAR(
        angle_normalize_signed(-PI_DIV_2),
        -PI_DIV_2,
        kEps
    );
}


// =============================================================================
// Angle differences
// =============================================================================

TEST(VectorHelpers, AngleDifferenceSigned)
{
    EXPECT_NEAR(angle_difference_signed(0.0f, 0.0f), 0.0f, kEps);
    EXPECT_NEAR(angle_difference_signed(PI_DIV_2, 0.0f), PI_DIV_2, kEps);
    EXPECT_NEAR(angle_difference_signed(0.0f, PI_DIV_2), -PI_DIV_2, kEps);
}


TEST(VectorHelpers, AngleDifferenceSignedUsesShortestPath)
{
    EXPECT_NEAR(
        angle_difference_signed(PI_MUL_2 - 0.1f, 0.1f),
        -0.2f,
        kEps
    );

    EXPECT_NEAR(
        angle_difference_signed(0.1f, PI_MUL_2 - 0.1f),
        0.2f,
        kEps
    );
}


TEST(VectorHelpers, AngleDifference)
{
    EXPECT_NEAR(
        angle_difference(PI_MUL_2 - 0.1f, 0.1f),
        0.2f,
        kEps
    );

    EXPECT_NEAR(
        angle_difference(0.1f, PI_MUL_2 - 0.1f),
        0.2f,
        kEps
    );
}


// =============================================================================
// Ordering / between
// =============================================================================

TEST(VectorHelpers, AreOrderedAscending)
{
    EXPECT_TRUE(are_ordered(1.0f, 2.0f, 3.0f));
}


TEST(VectorHelpers, AreOrderedDescending)
{
    EXPECT_TRUE(are_ordered(3.0f, 2.0f, 1.0f));
}


TEST(VectorHelpers, AreOrderedWhenMiddleEqualsEndpoint)
{
    EXPECT_TRUE(are_ordered(1.0f, 1.0f, 3.0f));
    EXPECT_TRUE(are_ordered(1.0f, 3.0f, 3.0f));
}


TEST(VectorHelpers, AreOrderedRejectsOutsideValue)
{
    EXPECT_FALSE(are_ordered(1.0f, 4.0f, 3.0f));
    EXPECT_FALSE(are_ordered(3.0f, 0.0f, 1.0f));
}


TEST(VectorHelpers, IsBetween)
{
    EXPECT_TRUE(is_between(2.0f, 1.0f, 3.0f));
    EXPECT_TRUE(is_between(2.0f, 3.0f, 1.0f));

    EXPECT_FALSE(is_between(4.0f, 1.0f, 3.0f));
}


// =============================================================================
// angle_lerp
// =============================================================================

TEST(VectorHelpers, AngleLerpReachesTarget)
{
    float current = 0.0f;

    EXPECT_TRUE(angle_lerp(current, PI, 10.0f, 1.0f));
    EXPECT_NEAR(current, PI, kEps);
}


TEST(VectorHelpers, AngleLerpDoesNotOvershoot)
{
    float current = 0.0f;

    EXPECT_FALSE(angle_lerp(current, 1.0f, 0.5f, 1.0f));
    EXPECT_NEAR(current, 0.5f, kEps);
}


TEST(VectorHelpers, AngleLerpUsesShortestAngularPath)
{
    float current = 0.0f;

    EXPECT_FALSE(
        angle_lerp(
            current,
            PI_MUL_2 - 0.2f,
            1.0f,
            0.1f
        )
    );

    EXPECT_NEAR(current, PI_MUL_2 - 0.1f, kEps);
}


TEST(VectorHelpers, AngleLerpAlreadyAtTarget)
{
    float current = 1.0f;

    EXPECT_TRUE(angle_lerp(current, 1.0f, 10.0f, 1.0f));

    EXPECT_NEAR(current, 1.0f, kEps);
}


TEST(VectorHelpers, AngleLerpScalar)
{
    EXPECT_NEAR(
        angle_lerp(0.0f, PI, 0.5f),
        PI / 2.0f,
        kEps
    );
}


TEST(VectorHelpers, AngleLerpScalarUsesShortestPath)
{
    EXPECT_NEAR(
        angle_lerp(0.0f, PI_MUL_2 - 0.2f, 0.5f),
        -0.1f,
        kEps
    );
}


// =============================================================================
// angle_inertion
// =============================================================================

TEST(VectorHelpers, AngleInertionMovesTowardTarget)
{
    const float result =
        angle_inertion(0.0f, PI_DIV_2, 1.0f, PI, 0.5f);

    EXPECT_GT(result, 0.0f);
    EXPECT_LT(result, PI_DIV_2);
}


TEST(VectorHelpers, AngleInertionDoesNotMovePastTarget)
{
    const float result =
        angle_inertion(0.0f, PI_DIV_2, 100.0f, PI, 1.0f);

    EXPECT_NEAR(result, PI_DIV_2, kEps);
}


TEST(VectorHelpers, AngleInertionRespectsClamp)
{
    const float result =
        angle_inertion(0.0f, PI, 100.0f, 0.1f, 1.0f);

    EXPECT_NEAR(result, 0.1f, kEps);
}


// =============================================================================
// angle_inertion_var
// =============================================================================

TEST(VectorHelpers, AngleInertionVarMovesTowardTarget)
{
    const float result =
        angle_inertion_var(
            0.0f,
            PI_DIV_2,
            1.0f,
            10.0f,
            PI,
            0.1f
        );

    EXPECT_GT(result, 0.0f);
    EXPECT_LT(result, PI_DIV_2);
}


TEST(VectorHelpers, AngleInertionVarRespectsClamp)
{
    const float result =
        angle_inertion_var(
            0.0f,
            PI,
            1.0f,
            100.0f,
            0.1f,
            1.0f
        );

    EXPECT_NEAR(result, 0.1f, kEps);
}


// =============================================================================
// EulerYawPitchRollInertion
// =============================================================================

TEST(VectorHelpers, EulerInertionReturnsCurrentWhenAlreadyAtTarget)
{
    const Fvector current = {1.0f, 2.0f, 3.0f};
    const Fvector target = current;

    const Fvector result =
        EulerYawPitchRollInertion(current, target, 10.0f, 1.0f);

    expect_vec_near(result, current.x, current.y, current.z);
}


TEST(VectorHelpers, EulerInertionMovesTowardTarget)
{
    const Fvector current = {0.0f, 0.0f, 0.0f};
    const Fvector target = {1.0f, 2.0f, 3.0f};

    const Fvector result =
        EulerYawPitchRollInertion(current, target, 1.0f, 0.1f);

    EXPECT_GT(result.x, 0.0f);
    EXPECT_GT(result.y, 0.0f);
    EXPECT_GT(result.z, 0.0f);
}


TEST(VectorHelpers, EulerInertionDoesNotMoveMoreThanMaximumDistance)
{
    const Fvector current = {0.0f, 0.0f, 0.0f};
    const Fvector target = {1.0f, 1.0f, 1.0f};

    const float speed = 1.0f;
    const float dt = 0.25f;

    const Fvector result =
        EulerYawPitchRollInertion(current, target, speed, dt);

    Fvector delta;
    delta.sub(result, current);

    EXPECT_NEAR(delta.magnitude(), speed * dt, kEps);
}


TEST(VectorHelpers, EulerInertionUsesShortestAnglePath)
{
    const Fvector current =
    {
        PI_MUL_2 - 0.1f,
        0.0f,
        0.0f
    };

    const Fvector target =
    {
        0.1f,
        0.0f,
        0.0f
    };

    const Fvector result =
        EulerYawPitchRollInertion(
            current,
            target,
            1.0f,
            0.05f
        );

    // The shortest path is forward by +0.2 radians rather than almost
    // a complete revolution in the opposite direction.
    EXPECT_GT(result.x, current.x);
    EXPECT_LT(result.x, 0.1f);
}
