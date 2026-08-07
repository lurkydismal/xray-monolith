#include "stdafx.h"

#include "_std_extensions.h"

#include <gtest/gtest.h>

TEST(StdExtensions, TokenLookupName)
{
	xr_token tokens[] =
	{
		{"zero", 0},
		{"one", 1},
		{"two", 2},
		{nullptr, -1}
	};

	EXPECT_STREQ(get_token_name(tokens, 0), "zero");
	EXPECT_STREQ(get_token_name(tokens, 2), "two");
	EXPECT_STREQ(get_token_name(tokens, 99), "");
}

TEST(StdExtensions, TokenLookupId)
{
	xr_token tokens[] =
	{
		{"zero", 0},
		{"One", 1},
		{"two", 2},
		{nullptr, -1}
	};

	EXPECT_EQ(get_token_id(tokens, "zero"), 0);
	EXPECT_EQ(get_token_id(tokens, "one"), 1);
	EXPECT_EQ(get_token_id(tokens, "ONE"), 1);
	EXPECT_EQ(get_token_id(tokens, "missing"), -1);
}

TEST(StdExtensions, Min)
{
	EXPECT_EQ(_min(1, 2), 1);
	EXPECT_EQ(_min(2, 1), 1);

	EXPECT_FLOAT_EQ(_min(1.5f, 2.5f), 1.5f);
}

TEST(StdExtensions, Max)
{
	EXPECT_EQ(_max(1, 2), 2);
	EXPECT_EQ(_max(2, 1), 2);

	EXPECT_FLOAT_EQ(_max(1.5f, 2.5f), 2.5f);
}

TEST(StdExtensions, Square)
{
	EXPECT_EQ(_sqr(3), 9);
	EXPECT_EQ(_sqr(-4), 16);

	EXPECT_FLOAT_EQ(_sqr(2.5f), 6.25f);
}

TEST(StdExtensions, Abs)
{
	EXPECT_EQ(_abs(-10), 10);
	EXPECT_EQ(_abs(10), 10);

	EXPECT_FLOAT_EQ(_abs(-3.5f), 3.5f);
	EXPECT_DOUBLE_EQ(_abs(-7.25), 7.25);
}

TEST(StdExtensions, SimilarFloat)
{
	EXPECT_TRUE(_fsimilar(1.0f, 1.0f));
	EXPECT_TRUE(_fsimilar(1.0f, 1.0f + EPS / 2));

	EXPECT_FALSE(_fsimilar(1.0f, 1.1f));
}

TEST(StdExtensions, PowfOptimizations)
{
	EXPECT_FLOAT_EQ(_powf(3.0f, 2.0f), 9.0f);
	EXPECT_FLOAT_EQ(_powf(9.0f, 0.5f), 3.0f);
	EXPECT_FLOAT_EQ(_powf(5.0f, 1.0f), 5.0f);
	EXPECT_FLOAT_EQ(_powf(5.0f, 0.0f), 1.0f);

	EXPECT_NEAR(_powf(2.0f, 3.0f), 8.0f, 0.001f);
}

TEST(StdExtensions, ValidFloat)
{
	EXPECT_TRUE(_valid(0.0f));
	EXPECT_TRUE(_valid(1.0f));
	EXPECT_TRUE(_valid(-1.0f));

	EXPECT_FALSE(_valid(INFINITY));
	EXPECT_FALSE(_valid(-INFINITY));
	EXPECT_FALSE(_valid(NAN));
}

TEST(StdExtensions, ValidDouble)
{
	EXPECT_TRUE(_valid(0.0));
	EXPECT_TRUE(_valid(123.456));

	EXPECT_FALSE(_valid(INFINITY));
	EXPECT_FALSE(_valid(-INFINITY));
	EXPECT_FALSE(_valid(NAN));
}

TEST(StdExtensions, StringLength)
{
	EXPECT_EQ(xr_strlen(""), 0u);
	EXPECT_EQ(xr_strlen("hello"), 5u);
}

TEST(StdExtensions, StringExtension)
{
	char a[] = "file.txt";
	char b[] = "archive.tar.gz";
	char c[] = "no_extension";

	EXPECT_STREQ(strext(a), ".txt");
	EXPECT_STREQ(strext(b), ".gz");
	EXPECT_EQ(strext(c), nullptr);
}

TEST(StdExtensions, StringCompare)
{
	EXPECT_EQ(xr_strcmp("abc", "abc"), 0);
	EXPECT_LT(xr_strcmp("abc", "abd"), 0);
	EXPECT_GT(xr_strcmp("abd", "abc"), 0);
}

TEST(StdExtensions, StringLowercase)
{
	char value[] = "HeLLo WoRLD";

	xr_strlwr(value);

	EXPECT_STREQ(value, "hello world");
}

TEST(StdExtensions, StringCopy)
{
	char buffer[32];

	xr_strcpy(buffer, sizeof(buffer), "hello");

	EXPECT_STREQ(buffer, "hello");
}

TEST(StdExtensions, StringConcat)
{
	char buffer[32] = "hello ";

	xr_strcat(buffer, sizeof(buffer), "world");

	EXPECT_STREQ(buffer, "hello world");
}

TEST(StdExtensions, S8Abs)
{
	s8 value = -10;

	EXPECT_EQ(_abs(value), 10);
}

TEST(StdExtensions, S16Abs)
{
	s16 value = -200;

	EXPECT_EQ(_abs(value), 200);
}

TEST(StdExtensions, S32Abs)
{
	s32 value = -5000;

	EXPECT_EQ(_abs(value), 5000);
}

TEST(StdExtensions, S64Abs)
{
	s64 value = -900000;

	EXPECT_EQ(_abs(value), 900000);
}

TEST(StdExtensions, IntegerMinMax)
{
	EXPECT_EQ(_min<s32>(10, 20), 10);
	EXPECT_EQ(_max<s32>(10, 20), 20);

	EXPECT_EQ(_min<s16>(-5, 5), -5);
	EXPECT_EQ(_max<s16>(-5, 5), 5);
}
