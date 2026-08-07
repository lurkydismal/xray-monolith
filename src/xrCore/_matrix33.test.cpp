#include "stdafx.h"

#include "_matrix33.h"

#include <gtest/gtest.h>

namespace
{
    using Mat = Fmatrix33;
    using Vec = Fvector3;

    void ExpectMatrixEq(
        const Mat& m,
        float m11, float m12, float m13,
        float m21, float m22, float m23,
        float m31, float m32, float m33)
    {
        EXPECT_FLOAT_EQ(m._11, m11);
        EXPECT_FLOAT_EQ(m._12, m12);
        EXPECT_FLOAT_EQ(m._13, m13);

        EXPECT_FLOAT_EQ(m._21, m21);
        EXPECT_FLOAT_EQ(m._22, m22);
        EXPECT_FLOAT_EQ(m._23, m23);

        EXPECT_FLOAT_EQ(m._31, m31);
        EXPECT_FLOAT_EQ(m._32, m32);
        EXPECT_FLOAT_EQ(m._33, m33);
    }

    Mat MakeMatrix()
    {
        Mat m;

        m._11 = 1; m._12 = 2; m._13 = 3;
        m._21 = 4; m._22 = 5; m._23 = 6;
        m._31 = 7; m._32 = 8; m._33 = 9;

        return m;
    }
}

// identity
TEST(Matrix33, Identity)
{
    Mat m;

    auto& r = m.identity();

    EXPECT_EQ(&r, &m);

    ExpectMatrixEq(
        m,
        1,0,0,
        0,1,0,
        0,0,1);
}

// set
TEST(Matrix33, SetCopiesMatrix)
{
    Mat a = MakeMatrix();
    Mat b;

    auto& r = b.set(a);

    EXPECT_EQ(&r, &b);

    ExpectMatrixEq(
        b,
        1,2,3,
        4,5,6,
        7,8,9);
}

// transpose
TEST(Matrix33, TransposeSource)
{
    Mat src = MakeMatrix();
    Mat dst;

    dst.transpose(src);

    ExpectMatrixEq(
        dst,
        1,4,7,
        2,5,8,
        3,6,9);
}

TEST(Matrix33, SelfTranspose)
{
    Mat m = MakeMatrix();

    m.transpose();

    ExpectMatrixEq(
        m,
        1,4,7,
        2,5,8,
        3,6,9);
}

// MxM
TEST(Matrix33, MatrixMultiply)
{
    Mat A;
    Mat B;
    Mat C;

    A._11=1; A._12=2; A._13=3;
    A._21=4; A._22=5; A._23=6;
    A._31=7; A._32=8; A._33=9;

    B._11=9; B._12=8; B._13=7;
    B._21=6; B._22=5; B._23=4;
    B._31=3; B._32=2; B._33=1;

    C.MxM(A,B);

    ExpectMatrixEq(
        C,
        30,24,18,
        84,69,54,
        138,114,90);
}

// MTxM
TEST(Matrix33, TransposedMultiply)
{
    Mat A = MakeMatrix();

    Mat B;
    B.identity();

    Mat C;

    C.MTxM(A,B);

    ExpectMatrixEq(
        C,
        1,4,7,
        2,5,8,
        3,6,9);
}

// MxMT
TEST(Matrix33, MultiplyByTranspose)
{
    Mat A = MakeMatrix();

    Mat I;
    I.identity();

    Mat C;

    C.MxMT(A,I);

    ExpectMatrixEq(
        C,
        1,2,3,
        4,5,6,
        7,8,9);
}

// McolcMcol
TEST(Matrix33, CopyColumn)
{
    Mat src = MakeMatrix();
    Mat dst;

    dst.identity();

    dst.McolcMcol(1, src, 2);

    EXPECT_FLOAT_EQ(dst._12, 3);
    EXPECT_FLOAT_EQ(dst._22, 6);
    EXPECT_FLOAT_EQ(dst._32, 9);
}

// MskewV
TEST(Matrix33, SkewMatrix)
{
    Mat m;
    Vec v;

    v.set(1,2,3);

    m.MskewV(v);

    ExpectMatrixEq(
        m,
         0,-3, 2,
         3, 0,-1,
        -2, 1, 0);
}

// MxV
TEST(Matrix33, MultiplyVector)
{
    Mat m;
    m.identity();

    Vec in;
    in.set(4,5,6);

    Vec out;

    m.MxV(out,in);

    EXPECT_FLOAT_EQ(out.x,4);
    EXPECT_FLOAT_EQ(out.y,5);
    EXPECT_FLOAT_EQ(out.z,6);
}

// MTxV
TEST(Matrix33, MultiplyTransposeVector)
{
    Mat m = MakeMatrix();

    Vec in;
    in.set(1,2,3);

    Vec out;

    m.MTxV(out,in);

    EXPECT_FLOAT_EQ(out.x,30);
    EXPECT_FLOAT_EQ(out.y,36);
    EXPECT_FLOAT_EQ(out.z,42);
}

// MxVpV
TEST(Matrix33, MultiplyVectorPlusVector)
{
    Mat m;
    m.identity();

    Vec in;
    in.set(1,2,3);

    Vec add;
    add.set(10,20,30);

    Vec out;

    m.MxVpV(out,in,add);

    EXPECT_FLOAT_EQ(out.x,11);
    EXPECT_FLOAT_EQ(out.y,22);
    EXPECT_FLOAT_EQ(out.z,33);
}

// sMxVpV
TEST(Matrix33, ScaledMultiplyVectorPlusVector)
{
    Mat m;
    m.identity();

    Vec in;
    in.set(1,2,3);

    Vec add;
    add.set(10,20,30);

    Vec out;

    m.sMxVpV(out,2.0f,in,add);

    EXPECT_FLOAT_EQ(out.x,12);
    EXPECT_FLOAT_EQ(out.y,24);
    EXPECT_FLOAT_EQ(out.z,36);
}
