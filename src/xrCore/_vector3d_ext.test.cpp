#include "stdafx.h"

#include "_vector3d_ext.h"

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

namespace
{
    constexpr float EPS = 1e-5f;

    void ExpectVectorNear(const Fvector& actual, const Fvector& expected)
    {
        EXPECT_NEAR(actual.x, expected.x, EPS);
        EXPECT_NEAR(actual.y, expected.y, EPS);
        EXPECT_NEAR(actual.z, expected.z, EPS);
    }

    Fvector MakeVector(float x, float y, float z)
    {
        return cr_fvector3(x, y, z);
    }
}

// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, CreateUniformVector)
{
    const Fvector v = cr_fvector3(3.5f);

    EXPECT_FLOAT_EQ(v.x, 3.5f);
    EXPECT_FLOAT_EQ(v.y, 3.5f);
    EXPECT_FLOAT_EQ(v.z, 3.5f);
}

TEST(Vector3DExtTest, CreateVectorFromComponents)
{
    const Fvector v = cr_fvector3(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vector3DExtTest, CreateVectorWithZero)
{
    const Fvector v = cr_fvector3(0.0f);

    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vector3DExtTest, CreateVectorWithNegativeValues)
{
    const Fvector v = cr_fvector3(-1.0f, -2.0f, -3.0f);

    EXPECT_FLOAT_EQ(v.x, -1.0f);
    EXPECT_FLOAT_EQ(v.y, -2.0f);
    EXPECT_FLOAT_EQ(v.z, -3.0f);
}

// -----------------------------------------------------------------------------
// Vector arithmetic
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, Addition)
{
    const Fvector a = MakeVector(1.0f, 2.0f, 3.0f);
    const Fvector b = MakeVector(4.0f, 5.0f, 6.0f);

    ExpectVectorNear(a + b, MakeVector(5.0f, 7.0f, 9.0f));
}

TEST(Vector3DExtTest, AdditionWithNegativeValues)
{
    const Fvector a = MakeVector(5.0f, -2.0f, 10.0f);
    const Fvector b = MakeVector(-3.0f, 4.0f, -7.0f);

    ExpectVectorNear(a + b, MakeVector(2.0f, 2.0f, 3.0f));
}

TEST(Vector3DExtTest, Subtraction)
{
    const Fvector a = MakeVector(5.0f, 7.0f, 9.0f);
    const Fvector b = MakeVector(1.0f, 2.0f, 3.0f);

    ExpectVectorNear(a - b, MakeVector(4.0f, 5.0f, 6.0f));
}

TEST(Vector3DExtTest, UnaryMinus)
{
    const Fvector v = MakeVector(1.0f, -2.0f, 3.0f);

    ExpectVectorNear(-v, MakeVector(-1.0f, 2.0f, -3.0f));
}

TEST(Vector3DExtTest, ScalarMultiplication)
{
    const Fvector v = MakeVector(1.0f, 2.0f, 3.0f);

    ExpectVectorNear(v * 2.0f, MakeVector(2.0f, 4.0f, 6.0f));
}

TEST(Vector3DExtTest, ScalarMultiplicationIsCommutative)
{
    const Fvector v = MakeVector(1.0f, 2.0f, 3.0f);

    ExpectVectorNear(v * 2.5f, MakeVector(2.5f, 5.0f, 7.5f));
    ExpectVectorNear(2.5f * v, MakeVector(2.5f, 5.0f, 7.5f));
}

TEST(Vector3DExtTest, ScalarMultiplicationByZero)
{
    const Fvector v = MakeVector(1.0f, -2.0f, 3.0f);

    ExpectVectorNear(v * 0.0f, MakeVector(0.0f, 0.0f, 0.0f));
}

TEST(Vector3DExtTest, ScalarMultiplicationByNegativeValue)
{
    const Fvector v = MakeVector(1.0f, -2.0f, 3.0f);

    ExpectVectorNear(v * -2.0f, MakeVector(-2.0f, 4.0f, -6.0f));
}

TEST(Vector3DExtTest, Division)
{
    const Fvector v = MakeVector(2.0f, 4.0f, 6.0f);

    ExpectVectorNear(v / 2.0f, MakeVector(1.0f, 2.0f, 3.0f));
}

TEST(Vector3DExtTest, DivisionByNegativeValue)
{
    const Fvector v = MakeVector(2.0f, -4.0f, 6.0f);

    ExpectVectorNear(v / -2.0f, MakeVector(-1.0f, 2.0f, -3.0f));
}

// -----------------------------------------------------------------------------
// Component-wise helpers
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, Min)
{
    const Fvector a = MakeVector(1.0f, 5.0f, -3.0f);
    const Fvector b = MakeVector(2.0f, 3.0f, -4.0f);

    ExpectVectorNear(
        _min(a, b),
        MakeVector(1.0f, 3.0f, -4.0f));
}

TEST(Vector3DExtTest, Max)
{
    const Fvector a = MakeVector(1.0f, 5.0f, -3.0f);
    const Fvector b = MakeVector(2.0f, 3.0f, -4.0f);

    ExpectVectorNear(
        _max(a, b),
        MakeVector(2.0f, 5.0f, -3.0f));
}

TEST(Vector3DExtTest, Abs)
{
    const Fvector v = MakeVector(-1.0f, 2.0f, -3.0f);

    ExpectVectorNear(
        _abs(v),
        MakeVector(1.0f, 2.0f, 3.0f));
}

TEST(Vector3DExtTest, AbsOfZero)
{
    const Fvector v = MakeVector(0.0f, 0.0f, 0.0f);

    ExpectVectorNear(
        _abs(v),
        MakeVector(0.0f, 0.0f, 0.0f));
}

// -----------------------------------------------------------------------------
// Magnitude / normalization
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, Magnitude)
{
    const Fvector v = MakeVector(3.0f, 4.0f, 0.0f);

    EXPECT_NEAR(magnitude(v), 5.0f, ::EPS);
}

TEST(Vector3DExtTest, SquareMagnitude)
{
    const Fvector v = MakeVector(1.0f, 2.0f, 3.0f);

    EXPECT_NEAR(sqaure_magnitude(v), 14.0f, ::EPS);
}

TEST(Vector3DExtTest, MagnitudeOfZero)
{
    const Fvector v = MakeVector(0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(magnitude(v), 0.0f);
    EXPECT_FLOAT_EQ(sqaure_magnitude(v), 0.0f);
}

TEST(Vector3DExtTest, Normalize)
{
    const Fvector v = MakeVector(3.0f, 4.0f, 0.0f);

    const Fvector normalized = normalize(v);

    ExpectVectorNear(
        normalized,
        MakeVector(0.6f, 0.8f, 0.0f));

    EXPECT_NEAR(magnitude(normalized), 1.0f, ::EPS);
}

TEST(Vector3DExtTest, NormalizeDoesNotModifyOriginal)
{
    const Fvector v = MakeVector(3.0f, 4.0f, 0.0f);

    const Fvector normalized = normalize(v);

    ExpectVectorNear(v, MakeVector(3.0f, 4.0f, 0.0f));
    ExpectVectorNear(normalized, MakeVector(0.6f, 0.8f, 0.0f));
}

// -----------------------------------------------------------------------------
// Dot product
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, DotProduct)
{
    const Fvector a = MakeVector(1.0f, 2.0f, 3.0f);
    const Fvector b = MakeVector(4.0f, 5.0f, 6.0f);

    EXPECT_NEAR(dotproduct(a, b), 32.0f, ::EPS);
}

TEST(Vector3DExtTest, DotProductIsCommutative)
{
    const Fvector a = MakeVector(1.0f, -2.0f, 3.0f);
    const Fvector b = MakeVector(4.0f, 5.0f, -6.0f);

    EXPECT_FLOAT_EQ(dotproduct(a, b), dotproduct(b, a));
}

TEST(Vector3DExtTest, DotProductOfOrthogonalVectorsIsZero)
{
    const Fvector x = MakeVector(1.0f, 0.0f, 0.0f);
    const Fvector y = MakeVector(0.0f, 1.0f, 0.0f);

    EXPECT_FLOAT_EQ(dotproduct(x, y), 0.0f);
}

TEST(Vector3DExtTest, DotProductWithItselfEqualsSquareMagnitude)
{
    const Fvector v = MakeVector(2.0f, 3.0f, 4.0f);

    EXPECT_NEAR(
        dotproduct(v, v),
        sqaure_magnitude(v),
        ::EPS);
}

// -----------------------------------------------------------------------------
// Cross product
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, CrossProduct)
{
    const Fvector x = MakeVector(1.0f, 0.0f, 0.0f);
    const Fvector y = MakeVector(0.0f, 1.0f, 0.0f);

    ExpectVectorNear(
        crossproduct(x, y),
        MakeVector(0.0f, 0.0f, 1.0f));
}

TEST(Vector3DExtTest, CrossProductReversingOperandsReversesResult)
{
    const Fvector x = MakeVector(1.0f, 0.0f, 0.0f);
    const Fvector y = MakeVector(0.0f, 1.0f, 0.0f);

    ExpectVectorNear(
        crossproduct(y, x),
        MakeVector(0.0f, 0.0f, -1.0f));
}

TEST(Vector3DExtTest, CrossProductOfParallelVectorsIsZero)
{
    const Fvector a = MakeVector(1.0f, 2.0f, 3.0f);
    const Fvector b = MakeVector(2.0f, 4.0f, 6.0f);

    ExpectVectorNear(
        crossproduct(a, b),
        MakeVector(0.0f, 0.0f, 0.0f));
}

TEST(Vector3DExtTest, CrossProductIsPerpendicularToBothInputs)
{
    const Fvector a = MakeVector(1.0f, 2.0f, 3.0f);
    const Fvector b = MakeVector(4.0f, 5.0f, 6.0f);

    const Fvector cross = crossproduct(a, b);

    EXPECT_NEAR(dotproduct(cross, a), 0.0f, ::EPS);
    EXPECT_NEAR(dotproduct(cross, b), 0.0f, ::EPS);
}

// -----------------------------------------------------------------------------
// HP / heading-pitch conversion
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, CreateVectorHP)
{
    const Fvector v = cr_vectorHP(0.0f, 0.0f);

    ExpectVectorNear(
        v,
        MakeVector(0.0f, 0.0f, 1.0f));
}

TEST(Vector3DExtTest, CreateVectorHPWithNinetyDegreePitch)
{
    const Fvector v = cr_vectorHP(0.0f, PI_DIV_2);

    ExpectVectorNear(
        v,
        MakeVector(0.0f, 1.0f, 0.0f));
}

TEST(Vector3DExtTest, CreateVectorHPWithNegativeNinetyDegreePitch)
{
    const Fvector v = cr_vectorHP(0.0f, -PI_DIV_2);

    ExpectVectorNear(
        v,
        MakeVector(0.0f, -1.0f, 0.0f));
}

TEST(Vector3DExtTest, CreateVectorHPWithNinetyDegreeHeading)
{
    const Fvector v = cr_vectorHP(PI_DIV_2, 0.0f);

    ExpectVectorNear(
        v,
        MakeVector(-1.0f, 0.0f, 0.0f));
}

TEST(Vector3DExtTest, CreateVectorHPProducesUnitVector)
{
    const Fvector v = cr_vectorHP(0.73f, -0.42f);

    EXPECT_NEAR(magnitude(v), 1.0f, ::EPS);
}

TEST(Vector3DExtTest, CreateFvector3HPUsesFvectorSetHP)
{
    const Fvector expected = cr_vectorHP(0.73f, -0.42f);
    const Fvector actual = cr_fvector3_hp(0.73f, -0.42f);

    ExpectVectorNear(actual, expected);
}

// -----------------------------------------------------------------------------
// Angle between vectors
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, AngleBetweenIdenticalVectorsIsZero)
{
    const Fvector v = MakeVector(1.0f, 2.0f, 3.0f);

    EXPECT_NEAR(
        angle_between_vectors(v, v),
        0.0f,
        ::EPS);
}

TEST(Vector3DExtTest, AngleBetweenOppositeVectorsIsPi)
{
    const Fvector a = MakeVector(1.0f, 0.0f, 0.0f);
    const Fvector b = MakeVector(-1.0f, 0.0f, 0.0f);

    EXPECT_NEAR(
        angle_between_vectors(a, b),
        PI,
        ::EPS);
}

TEST(Vector3DExtTest, AngleBetweenOrthogonalVectorsIsHalfPi)
{
    const Fvector x = MakeVector(1.0f, 0.0f, 0.0f);
    const Fvector y = MakeVector(0.0f, 1.0f, 0.0f);

    EXPECT_NEAR(
        angle_between_vectors(x, y),
        PI_DIV_2,
        ::EPS);
}

TEST(Vector3DExtTest, AngleBetweenVectorsIsSymmetric)
{
    const Fvector a = MakeVector(1.0f, 2.0f, 3.0f);
    const Fvector b = MakeVector(-2.0f, 4.0f, 1.0f);

    EXPECT_NEAR(
        angle_between_vectors(a, b),
        angle_between_vectors(b, a),
        ::EPS);
}

TEST(Vector3DExtTest, AngleBetweenZeroVectorAndVectorIsZero)
{
    const Fvector zero = MakeVector(0.0f, 0.0f, 0.0f);
    const Fvector v = MakeVector(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(
        angle_between_vectors(zero, v),
        0.0f);

    EXPECT_FLOAT_EQ(
        angle_between_vectors(v, zero),
        0.0f);
}

TEST(Vector3DExtTest, AngleBetweenTwoZeroVectorsIsZero)
{
    const Fvector zero = MakeVector(0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(
        angle_between_vectors(zero, zero),
        0.0f);
}

// -----------------------------------------------------------------------------
// rotate_point
// -----------------------------------------------------------------------------

TEST(Vector3DExtTest, RotatePointByZero)
{
    const Fvector point = MakeVector(1.0f, 2.0f, 3.0f);

    const Fvector result = rotate_point(point, 0.0f);

    /*
     * rotate_point intentionally discards Y.
     */
    ExpectVectorNear(
        result,
        MakeVector(1.0f, 0.0f, 3.0f));
}

TEST(Vector3DExtTest, RotatePointByNinetyDegrees)
{
    const Fvector point = MakeVector(1.0f, 100.0f, 0.0f);

    const Fvector result =
        rotate_point(point, PI_DIV_2);

    ExpectVectorNear(
        result,
        MakeVector(0.0f, 0.0f, 1.0f));
}

TEST(Vector3DExtTest, RotatePointByNegativeNinetyDegrees)
{
    const Fvector point = MakeVector(1.0f, 100.0f, 0.0f);

    const Fvector result =
        rotate_point(point, -PI_DIV_2);

    ExpectVectorNear(
        result,
        MakeVector(0.0f, 0.0f, -1.0f));
}

TEST(Vector3DExtTest, RotatePointByPi)
{
    const Fvector point = MakeVector(1.0f, 100.0f, 2.0f);

    const Fvector result =
        rotate_point(point, PI);

    ExpectVectorNear(
        result,
        MakeVector(-1.0f, 0.0f, -2.0f));
}

TEST(Vector3DExtTest, RotatePointPreservesXZDistanceFromOrigin)
{
    const Fvector point = MakeVector(3.0f, 100.0f, 4.0f);

    const Fvector result =
        rotate_point(point, 0.73f);

    const float original_distance =
        std::sqrt(point.x * point.x + point.z * point.z);

    const float rotated_distance =
        std::sqrt(result.x * result.x + result.z * result.z);

    EXPECT_NEAR(
        rotated_distance,
        original_distance,
        ::EPS);
}

TEST(Vector3DExtTest, RotatePointAlwaysProducesZeroY)
{
    const Fvector point = MakeVector(3.0f, 123.0f, 4.0f);

    const Fvector result =
        rotate_point(point, 0.37f);

    EXPECT_FLOAT_EQ(result.y, 0.0f);
}

TEST(Vector3DExtTest, RotatePointDoesNotModifyInput)
{
    const Fvector point = MakeVector(1.0f, 2.0f, 3.0f);

    const Fvector result =
        rotate_point(point, PI_DIV_2);

    (void)result;

    ExpectVectorNear(
        point,
        MakeVector(1.0f, 2.0f, 3.0f));
}
