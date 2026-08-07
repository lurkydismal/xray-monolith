#include "stdafx.h"

#include "_matrix.h"

#include <gtest/gtest.h>


class MatrixTest : public ::testing::Test
{
protected:

    static constexpr float EPS = 1e-5f;

    void ExpectNear(float a, float b)
    {
        EXPECT_NEAR(a, b, EPS);
    }

    void ExpectVec(const Fvector& a, const Fvector& b)
    {
        EXPECT_NEAR(a.x, b.x, EPS);
        EXPECT_NEAR(a.y, b.y, EPS);
        EXPECT_NEAR(a.z, b.z, EPS);
    }

    void ExpectMatrixIdentity(const Fmatrix& m)
    {
        EXPECT_NEAR(m._11,1,EPS);
        EXPECT_NEAR(m._22,1,EPS);
        EXPECT_NEAR(m._33,1,EPS);
        EXPECT_NEAR(m._44,1,EPS);

        EXPECT_NEAR(m._12,0,EPS);
        EXPECT_NEAR(m._13,0,EPS);
        EXPECT_NEAR(m._14,0,EPS);

        EXPECT_NEAR(m._21,0,EPS);
        EXPECT_NEAR(m._23,0,EPS);
        EXPECT_NEAR(m._24,0,EPS);

        EXPECT_NEAR(m._31,0,EPS);
        EXPECT_NEAR(m._32,0,EPS);
        EXPECT_NEAR(m._34,0,EPS);

        EXPECT_NEAR(m._41,0,EPS);
        EXPECT_NEAR(m._42,0,EPS);
        EXPECT_NEAR(m._43,0,EPS);
    }
};


// ------------------------------------------------------------
// Initialization
// ------------------------------------------------------------

TEST_F(MatrixTest, Identity)
{
    Fmatrix m;

    m.identity();

    EXPECT_TRUE(m.has_identity());
}


TEST_F(MatrixTest, ZeroMatrixIsNotInitialized)
{
    Fmatrix m{};

    EXPECT_TRUE(m.has_inited());
    EXPECT_FALSE(m.has_identity());
}


// ------------------------------------------------------------
// Translation
// ------------------------------------------------------------

TEST_F(MatrixTest, TranslationMatrix)
{
    Fmatrix m;

    m.translate(10.f,20.f,30.f);

    EXPECT_FLOAT_EQ(m._41,10.f);
    EXPECT_FLOAT_EQ(m._42,20.f);
    EXPECT_FLOAT_EQ(m._43,30.f);

    EXPECT_TRUE(m.has_identity() == false);
}


TEST_F(MatrixTest, TranslateOver)
{
    Fmatrix m;

    m.identity();
    m.translate_over(5.f,6.f,7.f);

    EXPECT_FLOAT_EQ(m._41,5.f);
    EXPECT_FLOAT_EQ(m._42,6.f);
    EXPECT_FLOAT_EQ(m._43,7.f);
}


TEST_F(MatrixTest, TranslateAdd)
{
    Fmatrix m;

    m.translate(1,2,3);

    m.translate_add(4,5,6);

    EXPECT_FLOAT_EQ(m._41,5);
    EXPECT_FLOAT_EQ(m._42,7);
    EXPECT_FLOAT_EQ(m._43,9);
}


// ------------------------------------------------------------
// Scale
// ------------------------------------------------------------

TEST_F(MatrixTest, Scale)
{
    Fmatrix m;

    m.scale(2,3,4);

    EXPECT_FLOAT_EQ(m._11,2);
    EXPECT_FLOAT_EQ(m._22,3);
    EXPECT_FLOAT_EQ(m._33,4);

    EXPECT_FLOAT_EQ(m._44,1);
}


// ------------------------------------------------------------
// Transform
// ------------------------------------------------------------

TEST_F(MatrixTest, TransformTranslation)
{
    Fmatrix m;

    m.translate(10,20,30);

    Fvector src{1,2,3};
    Fvector dst;

    m.transform_tiny(dst,src);

    ExpectVec(
        dst,
        Fvector{11,22,33}
    );
}


TEST_F(MatrixTest, TransformDirectionDoesNotTranslate)
{
    Fmatrix m;

    m.translate(10,20,30);

    Fvector src{1,2,3};
    Fvector dst;

    m.transform_dir(dst,src);

    ExpectVec(
        dst,
        Fvector{1,2,3}
    );
}


// ------------------------------------------------------------
// Rotations
// ------------------------------------------------------------

TEST_F(MatrixTest, RotateX)
{
    Fmatrix m;

    m.rotateX(PI_DIV_2);

    Fvector src{0,1,0};
    Fvector dst;

    m.transform_dir(dst,src);

    ExpectVec(
        dst,
        Fvector{0,0,1}
    );
}


TEST_F(MatrixTest, RotateY)
{
    Fmatrix m;

    m.rotateY(PI_DIV_2);

    Fvector src{0,0,1};
    Fvector dst;

    m.transform_dir(dst,src);

    ExpectVec(
        dst,
        Fvector{1,0,0}
    );
}


TEST_F(MatrixTest, RotateZ)
{
    Fmatrix m;

    m.rotateZ(PI_DIV_2);

    Fvector src{1,0,0};
    Fvector dst;

    m.transform_dir(dst,src);

    ExpectVec(
        dst,
        Fvector{0,1,0}
    );
}


// ------------------------------------------------------------
// Matrix multiplication
// ------------------------------------------------------------

TEST_F(MatrixTest, MultiplyIdentity)
{
    Fmatrix a;
    Fmatrix b;
    Fmatrix result;

    a.identity();
    b.identity();

    result.mul(a,b);

    EXPECT_TRUE(result.has_identity());
}


TEST_F(MatrixTest, MultiplyTranslation)
{
    Fmatrix a;
    Fmatrix b;
    Fmatrix result;

    a.translate(10,0,0);
    b.translate(0,20,0);

    result.mul(a,b);

    Fvector src{0,0,0};
    Fvector dst;

    result.transform_tiny(dst,src);

    ExpectVec(
        dst,
        Fvector{10,20,0}
    );
}


// ------------------------------------------------------------
// Inversion
// ------------------------------------------------------------

TEST_F(MatrixTest, InvertTranslation)
{
    Fmatrix m;

    m.translate(10,20,30);

    Fmatrix inv;

    inv.invert(m);

    Fvector src{10,20,30};
    Fvector dst;

    inv.transform_tiny(dst,src);

    ExpectVec(
        dst,
        Fvector{0,0,0}
    );
}


TEST_F(MatrixTest, InvertProducesIdentityWhenMultiplied)
{
    Fmatrix m;

    m.translate(10,20,30);

    Fmatrix inv;

    inv.invert(m);

    Fmatrix result;

    result.mul(m,inv);

    ExpectMatrixIdentity(result);
}


// ------------------------------------------------------------
// Transpose
// ------------------------------------------------------------

TEST_F(MatrixTest, Transpose)
{
    Fmatrix a;

    a.identity();

    a._12 = 5;
    a._31 = 7;

    Fmatrix t;

    t.transpose(a);

    EXPECT_FLOAT_EQ(t._21,5);
    EXPECT_FLOAT_EQ(t._13,7);
}


// ------------------------------------------------------------
// Mirror
// ------------------------------------------------------------

TEST_F(MatrixTest, MirrorX)
{
    Fmatrix m;

    m.mirrorX();

    Fvector src{1,2,3};
    Fvector dst;

    m.transform_tiny(dst,src);

    ExpectVec(
        dst,
        Fvector{-1,2,3}
    );
}


TEST_F(MatrixTest, MirrorY)
{
    Fmatrix m;

    m.mirrorY();

    Fvector src{1,2,3};
    Fvector dst;

    m.transform_tiny(dst,src);

    ExpectVec(
        dst,
        Fvector{1,-2,3}
    );
}


TEST_F(MatrixTest, MirrorZ)
{
    Fmatrix m;

    m.mirrorZ();

    Fvector src{1,2,3};
    Fvector dst;

    m.transform_tiny(dst,src);

    ExpectVec(
        dst,
        Fvector{1,2,-3}
    );
}


// ------------------------------------------------------------
// Projection
// ------------------------------------------------------------

TEST_F(MatrixTest, ProjectionMatrix)
{
    Fmatrix m;

    m.build_projection_HAT(
        1.f,
        1.f,
        1.f,
        100.f
    );

    EXPECT_NEAR(
        m._34,
        1.f,
        EPS
    );

    EXPECT_NEAR(
        m._44,
        0.f,
        EPS
    );
}


// ------------------------------------------------------------
// Camera
// ------------------------------------------------------------

TEST_F(MatrixTest, CameraLookingForward)
{
    Fmatrix m;

    m.build_camera(
        Fvector{0,0,0},
        Fvector{0,0,1},
        Fvector{0,1,0}
    );

    Fvector dst;

    m.transform_dir(
        dst,
        Fvector{0,0,1}
    );

    EXPECT_NEAR(dst.z,1,EPS);
}


// ------------------------------------------------------------
// Axis mapping
// ------------------------------------------------------------

TEST_F(MatrixTest, MapXYZ)
{
    Fmatrix m;

    m.mapXYZ();

    EXPECT_TRUE(m.has_identity());
}


TEST_F(MatrixTest, MapZXY)
{
    Fmatrix m;

    m.mapZXY();

    Fvector src{1,2,3};
    Fvector dst;

    m.transform_tiny(dst,src);

    ExpectVec(
        dst,
        Fvector{2,3,1}
    );
}
