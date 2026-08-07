#include "stdafx.h"

#include "_vector2.h"

#include <gtest/gtest.h>

#include <cmath>


#if 0
static constexpr float EPS = 1e-5f;
#endif

void expectVec(const Fvector2& v, float x, float y)
{
    EXPECT_NEAR(v.x, x, EPS);
    EXPECT_NEAR(v.y, y, EPS);
}


// ------------------------------------------------------------
// Construction / set
// ------------------------------------------------------------

TEST(Vector2SetTest, SetFloat)
{
    Fvector2 v;
    v.set(1.5f, 2.5f);

    EXPECT_FLOAT_EQ(v.x, 1.5f);
    EXPECT_FLOAT_EQ(v.y, 2.5f);
}


TEST(Vector2SetTest, SetInteger)
{
    Fvector2 v;
    v.set(10, 20);

    EXPECT_FLOAT_EQ(v.x, 10.f);
    EXPECT_FLOAT_EQ(v.y, 20.f);
}


TEST(Vector2SetTest, CopySet)
{
    Fvector2 a;
    a.set(3.f, 4.f);

    Fvector2 b;
    b.set(a);

    EXPECT_EQ(b.x, 3.f);
    EXPECT_EQ(b.y, 4.f);
}


// ------------------------------------------------------------
// Component operations
// ------------------------------------------------------------

TEST(Vector2Test, Abs)
{
    Fvector2 v;
    v.abs(Fvector2{-2.f, 3.f});

    expectVec(v, 2.f, 3.f);
}


TEST(Vector2Test, Min)
{
    Fvector2 v;
    v.set(5.f, 1.f);

    v.min(3.f, 4.f);

    expectVec(v, 3.f, 1.f);
}


TEST(Vector2Test, Max)
{
    Fvector2 v;
    v.set(5.f, 1.f);

    v.max(3.f, 4.f);

    expectVec(v, 5.f, 4.f);
}


// ------------------------------------------------------------
// Arithmetic
// ------------------------------------------------------------

TEST(Vector2ArithmeticTest, AddScalar)
{
    Fvector2 v;
    v.set(1.f, 2.f);

    v.add(5.f);

    expectVec(v, 6.f, 7.f);
}


TEST(Vector2ArithmeticTest, AddVector)
{
    Fvector2 v;
    v.set(1.f, 2.f);

    v.add(Fvector2{3.f, 4.f});

    expectVec(v, 4.f, 6.f);
}


TEST(Vector2ArithmeticTest, AddTwoVectors)
{
    Fvector2 v;
    v.add(
        Fvector2{1.f, 2.f},
        Fvector2{3.f, 4.f}
    );

    expectVec(v, 4.f, 6.f);
}


TEST(Vector2ArithmeticTest, Subtract)
{
    Fvector2 v;
    v.sub(
        Fvector2{5.f, 7.f},
        Fvector2{2.f, 3.f}
    );

    expectVec(v, 3.f, 4.f);
}


TEST(Vector2ArithmeticTest, MultiplyScalar)
{
    Fvector2 v;
    v.set(2.f, 3.f);

    v.mul(4.f);

    expectVec(v, 8.f, 12.f);
}


TEST(Vector2ArithmeticTest, MultiplyVector)
{
    Fvector2 v;
    v.set(2.f, 3.f);

    v.mul(Fvector2{4.f, 5.f});

    expectVec(v, 8.f, 15.f);
}


TEST(Vector2ArithmeticTest, DivideScalar)
{
    Fvector2 v;
    v.set(8.f, 12.f);

    v.div(4.f);

    expectVec(v, 2.f, 3.f);
}


// ------------------------------------------------------------
// Geometry
// ------------------------------------------------------------

TEST(Vector2GeometryTest, SquareMagnitude)
{
    Fvector2 v;
    v.set(3.f, 4.f);

    EXPECT_FLOAT_EQ(v.square_magnitude(), 25.f);
}


TEST(Vector2GeometryTest, Magnitude)
{
    Fvector2 v;
    v.set(3.f, 4.f);

    EXPECT_FLOAT_EQ(v.magnitude(), 5.f);
}


TEST(Vector2GeometryTest, Distance)
{
    Fvector2 a;
    a.set(0.f, 0.f);

    Fvector2 b;
    b.set(3.f, 4.f);

    EXPECT_FLOAT_EQ(a.distance_to(b), 5.f);
}


TEST(Vector2GeometryTest, Dot)
{
    Fvector2 a;
    a.set(1.f, 2.f);

    Fvector2 b;
    b.set(3.f, 4.f);

    EXPECT_FLOAT_EQ(a.dot(b), 11.f);
}


TEST(Vector2GeometryTest, CrossProduct)
{
    Fvector2 a;
    a.set(1.f, 2.f);

    Fvector2 b;
    b.set(3.f, 4.f);

    EXPECT_FLOAT_EQ(a.crossproduct(b), -2.f);
}


// ------------------------------------------------------------
// Normalize
// ------------------------------------------------------------

TEST(Vector2NormalizeTest, Normalize)
{
    Fvector2 v;
    v.set(3.f, 4.f);

    v.normalize();

    EXPECT_NEAR(v.x, .6f, EPS);
    EXPECT_NEAR(v.y, .8f, EPS);
}


TEST(Vector2NormalizeTest, NormalizeSafeZero)
{
    Fvector2 v;
    v.set(0.f, 0.f);

    v.normalize_safe();

    expectVec(v, 0.f, 0.f);
}


TEST(Vector2NormalizeTest, NormalizeOtherVector)
{
    Fvector2 result;

    result.normalize(
        Fvector2{0.f, 5.f}
    );

    expectVec(result, 0.f, 1.f);
}


// ------------------------------------------------------------
// Rotations / perpendicular vectors
// ------------------------------------------------------------

TEST(Vector2GeometryTest, Rot90)
{
    Fvector2 v;
    v.set(1.f, 2.f);

    v.rot90();

    expectVec(v, 2.f, -1.f);
}


TEST(Vector2GeometryTest, CrossVector)
{
    Fvector2 v;
    v.cross(Fvector2{3.f, 4.f});

    expectVec(v, 4.f, -3.f);
}


TEST(Vector2GeometryTest, CrossReturnsOrthogonal)
{
    Fvector2 v;
    v.set(2.f, 3.f);

    Fvector2 c = v.Cross();

    expectVec(c, 3.f, -2.f);

    EXPECT_FLOAT_EQ(v.dot(c), 0.f);
}


// ------------------------------------------------------------
// MAD
// ------------------------------------------------------------

TEST(Vector2Test, Mad)
{
    Fvector2 v;

    v.mad(
        Fvector2{1.f, 2.f},
        Fvector2{3.f, 4.f},
        2.f
    );

    expectVec(v, 7.f, 10.f);
}


// ------------------------------------------------------------
// Average
// ------------------------------------------------------------

TEST(Vector2AverageTest, Arithmetic)
{
    Fvector2 v;

    Fvector2 a{2.f, 4.f};
    Fvector2 b{6.f, 8.f};

    v.averageA(a, b);

    expectVec(v, 4.f, 6.f);
}


TEST(Vector2AverageTest, Geometric)
{
    Fvector2 v;

    Fvector2 a{4.f, 9.f};
    Fvector2 b{9.f, 16.f};

    v.averageG(a, b);

    expectVec(v, 6.f, 12.f);
}


// ------------------------------------------------------------
// Similar
// ------------------------------------------------------------

TEST(Vector2Test, Similar)
{
    Fvector2 a;
    a.set(1.f, 2.f);

    Fvector2 b;
    b.set(1.000001f, 2.000001f);

    EXPECT_TRUE(a.similar(b));
}


TEST(Vector2Test, NotSimilar)
{
    Fvector2 a;
    a.set(1.f, 2.f);

    Fvector2 b;
    b.set(1.1f, 2.f);

    EXPECT_FALSE(a.similar(b));
}


// ------------------------------------------------------------
// Index operator
// ------------------------------------------------------------

TEST(Vector2Test, IndexAccess)
{
    Fvector2 v;
    v.set(10.f, 20.f);

    EXPECT_FLOAT_EQ(v[0], 10.f);
    EXPECT_FLOAT_EQ(v[1], 20.f);
}


// ------------------------------------------------------------
// Heading angle
// ------------------------------------------------------------

TEST(Vector2Test, HeadingPositiveY)
{
    Fvector2 v;
    v.set(0.f, 1.f);

    EXPECT_NEAR(v.getH(), 0.f, EPS);
}


TEST(Vector2Test, HeadingPositiveX)
{
    Fvector2 v;
    v.set(1.f, 0.f);

    EXPECT_NEAR(v.getH(), -PI_DIV_2, EPS);
}


// ------------------------------------------------------------
// Validity
// ------------------------------------------------------------

TEST(Vector2Test, Valid)
{
    Fvector2 v;
    v.set(1.f, 2.f);

    EXPECT_TRUE(_valid(v));
}
