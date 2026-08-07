#include "stdafx.h"

#include "_vector3d.h"

#include <gtest/gtest.h>


class Vector3DTest : public ::testing::Test
{
protected:
    using Vec = Fvector;

    static constexpr float EPS = 1e-5f;

    void ExpectVecNear(const Vec& a, const Vec& b)
    {
        EXPECT_NEAR(a.x, b.x, EPS);
        EXPECT_NEAR(a.y, b.y, EPS);
        EXPECT_NEAR(a.z, b.z, EPS);
    }
};


// ------------------------------------------------------------
// Basic access
// ------------------------------------------------------------

TEST_F(Vector3DTest, SetAndIndexAccess)
{
    Fvector v;

    v.set(1.f, 2.f, 3.f);

    EXPECT_FLOAT_EQ(v[0], 1.f);
    EXPECT_FLOAT_EQ(v[1], 2.f);
    EXPECT_FLOAT_EQ(v[2], 3.f);

    v[0] = 10.f;
    v[1] = 20.f;
    v[2] = 30.f;

    EXPECT_FLOAT_EQ(v.x, 10.f);
    EXPECT_FLOAT_EQ(v.y, 20.f);
    EXPECT_FLOAT_EQ(v.z, 30.f);
}


// ------------------------------------------------------------
// Arithmetic
// ------------------------------------------------------------

TEST_F(Vector3DTest, AddVector)
{
    Fvector a;
    a.set(1, 2, 3);

    Fvector b;
    b.set(4, 5, 6);

    a.add(b);

    ExpectVecNear(a, Fvector{5, 7, 9});
}


TEST_F(Vector3DTest, AddScalar)
{
    Fvector v{1,2,3};

    v.add(5);

    ExpectVecNear(v, Fvector{6,7,8});
}


TEST_F(Vector3DTest, Subtract)
{
    Fvector a{10,20,30};
    Fvector b{1,2,3};

    a.sub(b);

    ExpectVecNear(a, Fvector{9,18,27});
}


TEST_F(Vector3DTest, Multiply)
{
    Fvector v{2,3,4};

    v.mul(2);

    ExpectVecNear(v, Fvector{4,6,8});
}


TEST_F(Vector3DTest, Divide)
{
    Fvector v{10,20,30};

    v.div(10);

    ExpectVecNear(v, Fvector{1,2,3});
}


// ------------------------------------------------------------
// Unary operations
// ------------------------------------------------------------

TEST_F(Vector3DTest, Invert)
{
    Fvector v{1,-2,3};

    v.invert();

    ExpectVecNear(v, Fvector{-1,2,-3});
}


TEST_F(Vector3DTest, MinMax)
{
    Fvector a{1,10,-5};
    Fvector b{5,2,0};

    a.min(b);

    ExpectVecNear(a, Fvector{1,2,-5});

    a.set(1,10,-5);
    a.max(b);

    ExpectVecNear(a, Fvector{5,10,0});
}


// ------------------------------------------------------------
// Magnitude
// ------------------------------------------------------------

TEST_F(Vector3DTest, SquareMagnitude)
{
    Fvector v{3,4,12};

    EXPECT_FLOAT_EQ(v.square_magnitude(),169.f);
}


TEST_F(Vector3DTest, Magnitude)
{
    Fvector v{3,4,0};

    EXPECT_FLOAT_EQ(v.magnitude(),5.f);
}


// ------------------------------------------------------------
// Normalize
// ------------------------------------------------------------

TEST_F(Vector3DTest, Normalize)
{
    Fvector v{3,0,4};

    float len = v.normalize_magn();

    EXPECT_NEAR(len,5.f,EPS);

    EXPECT_NEAR(v.magnitude(),1.f,EPS);
    ExpectVecNear(v,Fvector{0.6f,0.f,0.8f});
}


TEST_F(Vector3DTest, NormalizeSafeZeroVector)
{
    Fvector v{0,0,0};

    v.normalize_safe();

    ExpectVecNear(v,Fvector{0,0,0});
}


// ------------------------------------------------------------
// Dot / Cross
// ------------------------------------------------------------

TEST_F(Vector3DTest, DotProduct)
{
    Fvector a{1,2,3};
    Fvector b{4,5,6};

    EXPECT_FLOAT_EQ(
        a.dotproduct(b),
        32.f
    );
}


TEST_F(Vector3DTest, CrossProduct)
{
    Fvector a{1,0,0};
    Fvector b{0,1,0};

    Fvector result;

    result.crossproduct(a,b);

    ExpectVecNear(result,Fvector{0,0,1});
}


// ------------------------------------------------------------
// Distance
// ------------------------------------------------------------

TEST_F(Vector3DTest, Distance)
{
    Fvector a{0,0,0};
    Fvector b{3,4,0};

    EXPECT_FLOAT_EQ(a.distance_to(b),5.f);
}


TEST_F(Vector3DTest, DistanceXZ)
{
    Fvector a{0,10,0};
    Fvector b{3,-5,4};

    EXPECT_FLOAT_EQ(
        a.distance_to_xz(b),
        5.f
    );
}


// ------------------------------------------------------------
// Interpolation
// ------------------------------------------------------------

TEST_F(Vector3DTest, Lerp)
{
    Fvector a;
    Fvector p1{0,0,0};
    Fvector p2{10,20,30};

    a.lerp(p1,p2,0.5f);

    ExpectVecNear(
        a,
        Fvector{5,10,15}
    );
}


TEST_F(Vector3DTest, Average)
{
    Fvector a{10,20,30};

    a.average(Fvector{20,40,60});

    ExpectVecNear(
        a,
        Fvector{15,30,45}
    );
}


// ------------------------------------------------------------
// MAD
// ------------------------------------------------------------

TEST_F(Vector3DTest, Mad)
{
    Fvector v{1,1,1};

    v.mad(
        Fvector{2,3,4},
        10.f
    );

    ExpectVecNear(
        v,
        Fvector{21,31,41}
    );
}


// ------------------------------------------------------------
// Projection / reflection
// ------------------------------------------------------------

TEST_F(Vector3DTest, Project)
{
    Fvector v{2,2,0};
    Fvector axis{1,0,0};

    v.project(axis);

    ExpectVecNear(
        v,
        Fvector{2,0,0}
    );
}


TEST_F(Vector3DTest, Reflect)
{
    Fvector dir{1,-1,0};
    Fvector normal{0,1,0};

    Fvector result;

    result.reflect(dir,normal);

    ExpectVecNear(
        result,
        Fvector{1,1,0}
    );
}


// ------------------------------------------------------------
// Barycentric
// ------------------------------------------------------------

TEST_F(Vector3DTest, FromBarycentric)
{
    Fvector result;

    result.from_bary(
        Fvector{0,0,0},
        Fvector{10,0,0},
        Fvector{0,10,0},
        0.f,
        0.5f,
        0.5f
    );

    ExpectVecNear(
        result,
        Fvector{5,5,0}
    );
}


// ------------------------------------------------------------
// Normals
// ------------------------------------------------------------

TEST_F(Vector3DTest, MakeNormal)
{
    Fvector normal;

    normal.mknormal(
        Fvector{0,0,0},
        Fvector{1,0,0},
        Fvector{0,1,0}
    );

    ExpectVecNear(
        normal,
        Fvector{0,0,1}
    );
}


// ------------------------------------------------------------
// Similar
// ------------------------------------------------------------

TEST_F(Vector3DTest, Similar)
{
    Fvector a{1,2,3};

    Fvector b{
        1.000001f,
        2.000001f,
        3.000001f
    };

    EXPECT_TRUE(a.similar(b));
}


// ------------------------------------------------------------
// Hash
// ------------------------------------------------------------

TEST_F(Vector3DTest, HashChangesWithVector)
{
    Fvector a{1,2,3};
    Fvector b{1,2,4};

    EXPECT_NE(
        GetFvectorHash(a),
        GetFvectorHash(b)
    );
}
