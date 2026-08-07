#include "stdafx.h"

#include "_vector4.h"

#include <gtest/gtest.h>

namespace
{
    using Vec = Fvector4;

    void ExpectVecEq(const Vec& v, float x, float y, float z, float w)
    {
        EXPECT_FLOAT_EQ(v.x, x);
        EXPECT_FLOAT_EQ(v.y, y);
        EXPECT_FLOAT_EQ(v.z, z);
        EXPECT_FLOAT_EQ(v.w, w);
    }
}

// Construction / set
TEST(Vector4, SetComponents)
{
    Vec v;
    auto& r = v.set(1.f, 2.f, 3.f, 4.f);

    EXPECT_EQ(&r, &v);
    ExpectVecEq(v, 1, 2, 3, 4);
}

TEST(Vector4, SetDefaultWIsOne)
{
    Vec v;
    v.set(5.f, 6.f, 7.f);

    ExpectVecEq(v, 5, 6, 7, 1);
}

TEST(Vector4, SetFromVector)
{
    Vec a, b;

    a.set(1,2,3,4);
    b.set(a);

    ExpectVecEq(b,1,2,3,4);
}

// []
TEST(Vector4, IndexOperatorReadWrite)
{
    Vec v;
    v.set(1,2,3,4);

    EXPECT_FLOAT_EQ(v[0], 1);
    EXPECT_FLOAT_EQ(v[1], 2);
    EXPECT_FLOAT_EQ(v[2], 3);
    EXPECT_FLOAT_EQ(v[3], 4);

    v[2] = 10;

    EXPECT_FLOAT_EQ(v.z, 10);
}

// Add
TEST(Vector4, AddVector)
{
    Vec a, b;

    a.set(1,2,3,4);
    b.set(10,20,30,40);

    a.add(b);

    ExpectVecEq(a,11,22,33,44);
}

TEST(Vector4, AddScalar)
{
    Vec v;
    v.set(1,2,3,4);

    v.add(5);

    ExpectVecEq(v,6,7,8,9);
}

TEST(Vector4, AddComponentsUsesDefaultWOne)
{
    Vec v;
    v.set(1,2,3,4);

    v.add(10,20,30);

    ExpectVecEq(v,11,22,33,5);
}

TEST(Vector4, AddTwoVectors)
{
    Vec a,b,c;

    a.set(1,2,3,4);
    b.set(5,6,7,8);

    c.add(a,b);

    ExpectVecEq(c,6,8,10,12);
}

TEST(Vector4, AddVectorAndScalar)
{
    Vec a,b;

    a.set(1,2,3,4);

    b.add(a,2);

    ExpectVecEq(b,3,4,5,6);
}

// Subtract
TEST(Vector4, SubVector)
{
    Vec a,b;

    a.set(10,20,30,40);
    b.set(1,2,3,4);

    a.sub(b);

    ExpectVecEq(a,9,18,27,36);
}

TEST(Vector4, SubScalar)
{
    Vec v;
    v.set(5,6,7,8);

    v.sub(2);

    ExpectVecEq(v,3,4,5,6);
}

TEST(Vector4, SubComponentsDefaultWOne)
{
    Vec v;
    v.set(10,20,30,40);

    v.sub(1,2,3);

    ExpectVecEq(v,9,18,27,39);
}

// Multiply
TEST(Vector4, MultiplyScalar)
{
    Vec v;
    v.set(1,2,3,4);

    v.mul(2);

    ExpectVecEq(v,2,4,6,8);
}

TEST(Vector4, MultiplyVector)
{
    Vec a,b;

    a.set(1,2,3,4);
    b.set(5,6,7,8);

    a.mul(b);

    ExpectVecEq(a,5,12,21,32);
}

TEST(Vector4, MultiplyComponentsDefaultWOne)
{
    Vec v;
    v.set(2,3,4,5);

    v.mul(10,20,30);

    ExpectVecEq(v,20,60,120,5);
}

// Divide
TEST(Vector4, DivideScalar)
{
    Vec v;
    v.set(2,4,6,8);

    v.div(2);

    ExpectVecEq(v,1,2,3,4);
}

TEST(Vector4, DivideVector)
{
    Vec a,b;

    a.set(20,30,40,50);
    b.set(2,3,4,5);

    a.div(b);

    ExpectVecEq(a,10,10,10,10);
}

TEST(Vector4, DivideComponentsDefaultWOne)
{
    Vec v;
    v.set(20,30,40,50);

    v.div(2,3,4);

    ExpectVecEq(v,10,10,10,50);
}

// Clamp
// FIX: No UB overload
TEST(Vector4, ClampMinMax)
{
    Vec value;
    Vec min;
    Vec max;

    value.set(-5,5,15,100);
    min.set(0,0,10,20);
    max.set(3,4,12,50);

    value.clamp(min,max);

    ExpectVecEq(value,0,4,12,50);
}

// Magnitude
TEST(Vector4, MagnitudeSquared)
{
    Vec v;
    v.set(1,2,3,4);

    EXPECT_FLOAT_EQ(v.magnitude_sqr(), 30.f);
}

TEST(Vector4, Magnitude)
{
    Vec v;
    v.set(2,0,0,0);

    EXPECT_FLOAT_EQ(v.magnitude(), 2.f);
}

// Normalize
TEST(Vector4, Normalize)
{
    Vec v;
    v.set(2,0,0,0);

    v.normalize();

    ExpectVecEq(v,1,0,0,0);
}

TEST(Vector4, NormalizeAsPlane)
{
    Vec v;
    v.set(3,4,0,10);

    v.normalize_as_plane();

    EXPECT_NEAR(v.x, 0.6f, 1e-6f);
    EXPECT_NEAR(v.y, 0.8f, 1e-6f);
    EXPECT_NEAR(v.z, 0.0f, 1e-6f);
    EXPECT_NEAR(v.w, 2.0f, 1e-6f);
}

// Lerp
TEST(Vector4, Lerp)
{
    Vec a,b,c;

    a.set(0,0,0,0);
    b.set(10,20,30,40);

    c.lerp(a,b,0.25f);

    ExpectVecEq(c,2.5f,5.f,7.5f,10.f);
}

// Similar
TEST(Vector4, Similar)
{
    Vec a,b;

    a.set(1,2,3,4);
    b.set(1.00001f,2.00001f,3.00001f,4.00001f);

    EXPECT_TRUE(a.similar(b,0.001f));
    EXPECT_FALSE(a.similar(b,1e-7f));
}
