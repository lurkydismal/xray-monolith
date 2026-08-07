#include "stdafx.h"

#include "_bitwise.h"

#include <gtest/gtest.h>

TEST(Bitwise, LowestBitMaskSigned)
{
	EXPECT_EQ(btwLowestBitMask(0), 0);
	EXPECT_EQ(btwLowestBitMask(1), 1);
	EXPECT_EQ(btwLowestBitMask(2), 2);
	EXPECT_EQ(btwLowestBitMask(3), 1);
	EXPECT_EQ(btwLowestBitMask(12), 4);
	EXPECT_EQ(btwLowestBitMask(40), 8);
}

TEST(Bitwise, LowestBitMaskUnsigned)
{
	EXPECT_EQ(btwLowestBitMask(u32(0)), 0u);
	EXPECT_EQ(btwLowestBitMask(u32(1)), 1u);
	EXPECT_EQ(btwLowestBitMask(u32(8)), 8u);
	EXPECT_EQ(btwLowestBitMask(u32(10)), 2u);
	EXPECT_EQ(btwLowestBitMask(u32(0x100)), 0x100u);
}

TEST(Bitwise, IsPow2)
{
	EXPECT_TRUE(btwIsPow2(1));
	EXPECT_TRUE(btwIsPow2(2));
	EXPECT_TRUE(btwIsPow2(4));
	EXPECT_TRUE(btwIsPow2(1024));

	EXPECT_FALSE(btwIsPow2(0));
	EXPECT_FALSE(btwIsPow2(3));
	EXPECT_FALSE(btwIsPow2(6));
	EXPECT_FALSE(btwIsPow2(1023));
}

TEST(Bitwise, Pow2CeilSigned)
{
	EXPECT_EQ(btwPow2_Ceil(1), 1);
	EXPECT_EQ(btwPow2_Ceil(2), 2);
	EXPECT_EQ(btwPow2_Ceil(3), 4);
	EXPECT_EQ(btwPow2_Ceil(5), 8);
	EXPECT_EQ(btwPow2_Ceil(100), 128);
}

TEST(Bitwise, Pow2CeilUnsigned)
{
	EXPECT_EQ(btwPow2_Ceil(u32(1)), 1u);
	EXPECT_EQ(btwPow2_Ceil(u32(7)), 8u);
	EXPECT_EQ(btwPow2_Ceil(u32(64)), 64u);
	EXPECT_EQ(btwPow2_Ceil(u32(65)), 128u);
}

TEST(Bitwise, CountBits8)
{
	EXPECT_EQ(btwCount1(u8(0)), 0);
	EXPECT_EQ(btwCount1(u8(1)), 1);
	EXPECT_EQ(btwCount1(u8(0xff)), 8);
	EXPECT_EQ(btwCount1(u8(0xf0)), 4);
	EXPECT_EQ(btwCount1(u8(0x55)), 4);
}

TEST(Bitwise, CountBits32)
{
	EXPECT_EQ(btwCount1(u32(0)), 0u);
	EXPECT_EQ(btwCount1(u32(1)), 1u);
	EXPECT_EQ(btwCount1(u32(0xffffffff)), 32u);
	EXPECT_EQ(btwCount1(u32(0xf0f0f0f0)), 16u);
	EXPECT_EQ(btwCount1(u32(0xaaaaaaaa)), 16u);
}

TEST(Bitwise, CountBits64)
{
	EXPECT_EQ(btwCount1(u64(0)), 0u);
	EXPECT_EQ(btwCount1(u64(1)), 1u);
	EXPECT_EQ(btwCount1(u64(0xffffffffffffffffULL)), 64u);
	EXPECT_EQ(btwCount1(u64(0xffffffff00000000ULL)), 32u);
}

TEST(Bitwise, SignDetection)
{
	float l_positive = 10.0f;
	float l_negative = -10.0f;
	float l_zero = 0.0f;

	EXPECT_TRUE(positive(l_positive));
	EXPECT_FALSE(negative(l_negative));

	EXPECT_TRUE(positive(l_zero));
	EXPECT_FALSE(negative(l_zero));
}

TEST(Bitwise, SetNegative)
{
	float value = 5.0f;

	set_negative(value);

	EXPECT_LT(value, 0.0f);
	EXPECT_FLOAT_EQ(value, -5.0f);
}

TEST(Bitwise, SetPositive)
{
	float value = -5.0f;

	set_positive(value);

	EXPECT_GE(value, 0.0f);
	EXPECT_FLOAT_EQ(value, 5.0f);
}

TEST(Bitwise, Floor)
{
	EXPECT_EQ(iFloor(0.0f), 0);
	EXPECT_EQ(iFloor(1.0f), 1);
	EXPECT_EQ(iFloor(1.9f), 1);
	EXPECT_EQ(iFloor(-1.0f), -1);
	EXPECT_EQ(iFloor(-1.1f), -2);
	EXPECT_EQ(iFloor(100.75f), 100);
}

TEST(Bitwise, Ceil)
{
	EXPECT_EQ(iCeil(0.0f), 0);
	EXPECT_EQ(iCeil(1.0f), 1);
	EXPECT_EQ(iCeil(1.1f), 2);
	EXPECT_EQ(iCeil(-1.0f), -1);
	EXPECT_EQ(iCeil(-1.1f), -1);
	EXPECT_EQ(iCeil(100.25f), 101);
}

TEST(Bitwise, FloatValidity)
{
	float normal = 1.0f;
	float zero = 0.0f;

	EXPECT_FALSE(fis_denormal(normal));
	EXPECT_TRUE(fis_denormal(zero));

	EXPECT_FALSE(fis_gremlin(normal));
}

TEST(Bitwise, ApproxInverseSqrt)
{
	float v = 4.0f;

	float result = apx_InvSqrt(v);

	EXPECT_NEAR(result, 0.5f, 0.01f);
}

TEST(Bitwise, ApproxAsin)
{
	EXPECT_NEAR(apx_asin(0.0f), 0.0f, 0.001f);
	EXPECT_NEAR(apx_asin(1.0f), PI_DIV_2, 0.01f);
	EXPECT_NEAR(apx_asin(0.5f), asinf(0.5f), 0.01f);
}

TEST(Bitwise, ApproxAcos)
{
	EXPECT_NEAR(apx_acos(1.0f), 0.0f, 0.01f);
	EXPECT_NEAR(apx_acos(0.0f), PI_DIV_2, 0.01f);
	EXPECT_NEAR(apx_acos(0.5f), acosf(0.5f), 0.01f);
}
