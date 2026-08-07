#include "stdafx.h"

#include "_color.h"

#include <gtest/gtest.h>

#include <cmath>

class ColorTest : public ::testing::Test
{
protected:
    static constexpr float EPS = 1e-5f;

    void expectColorNear(const Fcolor& a, const Fcolor& b, float eps = EPS)
    {
        EXPECT_NEAR(a.r, b.r, eps);
        EXPECT_NEAR(a.g, b.g, eps);
        EXPECT_NEAR(a.b, b.b, eps);
        EXPECT_NEAR(a.a, b.a, eps);
    }
};


// ------------------------------------------------------------
// Packed color helpers
// ------------------------------------------------------------

TEST(ColorPackedTest, ArgbPacking)
{
    EXPECT_EQ(color_argb(0x12, 0x34, 0x56, 0x78),
              0x12345678u);

    EXPECT_EQ(color_rgba(0x34, 0x56, 0x78, 0x12),
              0x12345678u);
}


TEST(ColorPackedTest, ComponentExtraction)
{
    u32 c = 0x12345678;

    EXPECT_EQ(color_get_A(c), 0x12);
    EXPECT_EQ(color_get_R(c), 0x34);
    EXPECT_EQ(color_get_G(c), 0x56);
    EXPECT_EQ(color_get_B(c), 0x78);
}


TEST(ColorPackedTest, ComponentSubstitution)
{
    u32 c = 0x12345678;

    EXPECT_EQ(subst_alpha(c, 0xaa),
              0xaa345678u);

    EXPECT_EQ(subst_red(c, 0xaa),
              0x12aa5678u);

    EXPECT_EQ(subst_green(c, 0xaa),
              0x1234aa78u);

    EXPECT_EQ(subst_blue(c, 0xaa),
              0x123456aau);
}


TEST(ColorPackedTest, Xrgb)
{
    EXPECT_EQ(color_xrgb(1, 2, 3),
              0xff010203u);
}


TEST(ColorPackedTest, BgrRgbConversion)
{
    EXPECT_EQ(bgr2rgb(0x00112233),
              0x00332211);

    EXPECT_EQ(rgb2bgr(0x00112233),
              0x00332211);
}


// ------------------------------------------------------------
// Float conversion
// ------------------------------------------------------------

TEST(ColorFloatTest, FloatToPacked)
{
    EXPECT_EQ(
        color_rgba_f(1.f, 0.f, 0.f, 1.f),
        0xffff0000u
    );

    EXPECT_EQ(
        color_rgba_f(0.f, 1.f, 0.f, 1.f),
        0xff00ff00u
    );

    EXPECT_EQ(
        color_rgba_f(0.f, 0.f, 1.f, 1.f),
        0xff0000ffu
    );
}


TEST(ColorFloatTest, FloatClamping)
{
    EXPECT_EQ(
        color_rgba_f(-1.f, 2.f, 0.5f, 3.f),
        color_argb(255, 255, 127, 0)
    );
}


// ------------------------------------------------------------
// _color set/get
// ------------------------------------------------------------

TEST_F(ColorTest, SetFromPackedColor)
{
    Fcolor c;

    c.set(0x80402010);

    EXPECT_NEAR(c.a, 128.f / 255.f, EPS);
    EXPECT_NEAR(c.r, 64.f / 255.f, EPS);
    EXPECT_NEAR(c.g, 32.f / 255.f, EPS);
    EXPECT_NEAR(c.b, 16.f / 255.f, EPS);
}


TEST_F(ColorTest, GetRoundTrip)
{
    Fcolor c;
    c.set(0x80402010);

    EXPECT_EQ(c.get(), 0x80402010u);
}


TEST_F(ColorTest, CopySet)
{
    Fcolor a;
    a.set(.1f, .2f, .3f, .4f);

    Fcolor b;
    b.set(a);

    expectColorNear(a, b);
}


// ------------------------------------------------------------
// Windows format
// ------------------------------------------------------------

TEST_F(ColorTest, WindowsRoundTrip)
{
    Fcolor c;
    c.set(.1f, .2f, .3f, .4f);

    u32 packed = c.get_windows();

    Fcolor result;
    result.set_windows(packed);

    EXPECT_NEAR(result.a, .4f, 1.f / 255.f);
    EXPECT_NEAR(result.r, .1f, 1.f / 255.f);
    EXPECT_NEAR(result.g, .2f, 1.f / 255.f);
    EXPECT_NEAR(result.b, .3f, 1.f / 255.f);
}


// ------------------------------------------------------------
// Arithmetic
// ------------------------------------------------------------

TEST_F(ColorTest, Modulate)
{
    Fcolor a;
    a.set(0.5f, 0.25f, 1.f, 0.5f);

    Fcolor b;
    b.set(0.2f, 0.4f, 0.5f, 0.5f);

    a.modulate(b);

    EXPECT_FLOAT_EQ(a.r, .1f);
    EXPECT_FLOAT_EQ(a.g, .1f);
    EXPECT_FLOAT_EQ(a.b, .5f);
    EXPECT_FLOAT_EQ(a.a, .25f);
}


TEST_F(ColorTest, AddRgb)
{
    Fcolor c;
    c.set(.1f, .2f, .3f, .4f);

    c.add_rgb(.5f);

    EXPECT_FLOAT_EQ(c.r, .6f);
    EXPECT_FLOAT_EQ(c.g, .7f);
    EXPECT_FLOAT_EQ(c.b, .8f);
    EXPECT_FLOAT_EQ(c.a, .4f);
}


TEST_F(ColorTest, MultiplyRgba)
{
    Fcolor c;
    c.set(.5f, .5f, .5f, .5f);

    c.mul_rgba(2.f);

    EXPECT_FLOAT_EQ(c.r, 1.f);
    EXPECT_FLOAT_EQ(c.g, 1.f);
    EXPECT_FLOAT_EQ(c.b, 1.f);
    EXPECT_FLOAT_EQ(c.a, 1.f);
}


// ------------------------------------------------------------
// Adjustments
// ------------------------------------------------------------

TEST_F(ColorTest, Negative)
{
    Fcolor c;
    c.set(.1f, .2f, .3f, .4f);

    c.negative();

    EXPECT_FLOAT_EQ(c.r, .9f);
    EXPECT_FLOAT_EQ(c.g, .8f);
    EXPECT_FLOAT_EQ(c.b, .7f);
    EXPECT_FLOAT_EQ(c.a, .6f);
}


TEST_F(ColorTest, Contrast)
{
    Fcolor c;
    c.set(.25f, .5f, .75f, 1.f);

    c.adjust_contrast(2.f);

    EXPECT_FLOAT_EQ(c.r, 0.f);
    EXPECT_FLOAT_EQ(c.g, .5f);
    EXPECT_FLOAT_EQ(c.b, 1.f);
}


TEST_F(ColorTest, SaturationZeroProducesGray)
{
    Fcolor c;
    c.set(.2f, .4f, .8f, 1.f);

    c.adjust_saturation(0.f);

    EXPECT_NEAR(c.r, c.g, EPS);
    EXPECT_NEAR(c.g, c.b, EPS);
}


// ------------------------------------------------------------
// Vector operations
// ------------------------------------------------------------

TEST_F(ColorTest, Magnitude)
{
    Fcolor c;
    c.set(3.f, 4.f, 0.f, 1.f);

    EXPECT_FLOAT_EQ(c.magnitude_rgb(), 5.f);
}


TEST_F(ColorTest, Normalize)
{
    Fcolor c;
    c.set(3.f, 0.f, 0.f, 1.f);

    c.normalize_rgb();

    EXPECT_FLOAT_EQ(c.r, 1.f);
    EXPECT_FLOAT_EQ(c.g, 0.f);
    EXPECT_FLOAT_EQ(c.b, 0.f);
}


TEST_F(ColorTest, Intensity)
{
    Fcolor c;
    c.set(1.f, 0.f, 0.f, 1.f);

    EXPECT_FLOAT_EQ(c.intensity(), 1.f / 3.f);
}


// ------------------------------------------------------------
// Lerp
// ------------------------------------------------------------

TEST_F(ColorTest, LinearInterpolation)
{
    Fcolor a;
    a.set(0.f, 0.f, 0.f, 0.f);

    Fcolor b;
    b.set(1.f, 1.f, 1.f, 1.f);

    Fcolor out;
    out.lerp(a, b, .5f);

    EXPECT_FLOAT_EQ(out.r, .5f);
    EXPECT_FLOAT_EQ(out.g, .5f);
    EXPECT_FLOAT_EQ(out.b, .5f);
    EXPECT_FLOAT_EQ(out.a, .5f);
}


TEST_F(ColorTest, Similar)
{
    Fcolor a;
    a.set(.5f, .5f, .5f, .5f);

    Fcolor b;
    b.set(.500001f, .500001f, .500001f, .500001f);

    EXPECT_TRUE(a.similar_rgba(b));
    EXPECT_TRUE(a.similar_rgb(b));
}
