#include "stdafx.h"

#include "_random.h"

#include <gtest/gtest.h>

TEST(Random, DefaultConstructorHasDeterministicSeed)
{
	CRandom a;
	CRandom b;

	EXPECT_EQ(a.randI(), b.randI());
	EXPECT_EQ(a.randI(), b.randI());
	EXPECT_EQ(a.randI(), b.randI());
}

TEST(Random, SeedProducesSameSequence)
{
	CRandom a;
	CRandom b;

	a.seed(12345);
	b.seed(12345);

	for (int i = 0; i < 10; ++i)
	{
		EXPECT_EQ(a.randI(), b.randI());
	}
}

TEST(Random, DifferentSeedsProduceDifferentSequence)
{
	CRandom a(1);
	CRandom b(2);

	bool different = false;

	for (int i = 0; i < 10; ++i)
	{
		if (a.randI() != b.randI())
		{
			different = true;
			break;
		}
	}

	EXPECT_TRUE(different);
}

TEST(Random, RandIRange)
{
	CRandom random(123);

	for (int i = 0; i < 1000; ++i)
	{
		s32 value = random.randI(100);

		EXPECT_GE(value, 0);
		EXPECT_LT(value, 100);
	}
}

TEST(Random, RandIRangeZeroOrNegative)
{
	CRandom random(123);

	EXPECT_EQ(random.randI(0), 0);
	EXPECT_EQ(random.randI(-10), 0);
}

TEST(Random, RandIRangeMinMax)
{
	CRandom random(456);

	for (int i = 0; i < 1000; ++i)
	{
		s32 value = random.randI(-50, 50);

		EXPECT_GE(value, -50);
		EXPECT_LT(value, 50);
	}
}

TEST(Random, RandIsRange)
{
	CRandom random(789);

	for (int i = 0; i < 1000; ++i)
	{
		s32 value = random.randIs(25);

		EXPECT_GE(value, -25);
		EXPECT_LE(value, 24);
	}
}

TEST(Random, RandIsWithOffset)
{
	CRandom random(100);

	for (int i = 0; i < 1000; ++i)
	{
		s32 value = random.randIs(10, 100);

		EXPECT_GE(value, 90);
		EXPECT_LE(value, 109);
	}
}

TEST(Random, RandFFractionRange)
{
	CRandom random(321);

	for (int i = 0; i < 1000; ++i)
	{
		float value = random.randF();

		EXPECT_GE(value, 0.0f);
		EXPECT_LE(value, 1.0f);
	}
}

TEST(Random, RandFMaxRange)
{
	CRandom random(123);

	for (int i = 0; i < 1000; ++i)
	{
		float value = random.randF(50.0f);

		EXPECT_GE(value, 0.0f);
		EXPECT_LE(value, 50.0f);
	}
}

TEST(Random, RandFMinMaxRange)
{
	CRandom random(456);

	for (int i = 0; i < 1000; ++i)
	{
		float value = random.randF(-10.0f, 10.0f);

		EXPECT_GE(value, -10.0f);
		EXPECT_LE(value, 10.0f);
	}
}

TEST(Random, RandFsRange)
{
	CRandom random(789);

	for (int i = 0; i < 1000; ++i)
	{
		float value = random.randFs(5.0f);

		EXPECT_GE(value, -5.0f);
		EXPECT_LE(value, 5.0f);
	}
}

TEST(Random, RandFsWithOffset)
{
	CRandom random(999);

	for (int i = 0; i < 1000; ++i)
	{
		float value = random.randFs(5.0f, 20.0f);

		EXPECT_GE(value, 15.0f);
		EXPECT_LE(value, 25.0f);
	}
}

TEST(Random, MaxValues)
{
	CRandom random;

	EXPECT_EQ(random.maxI(), 32767);
	EXPECT_FLOAT_EQ(random.maxF(), 32767.0f);
}

TEST(Random, GlobalRandomCanBeSeeded)
{
	Random.seed(42);

	s32 first = Random.randI();

	Random.seed(42);

	EXPECT_EQ(first, Random.randI());
}
