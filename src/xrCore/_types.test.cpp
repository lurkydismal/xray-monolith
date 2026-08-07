#include "stdafx.h"

#include "_types.h"

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

TEST(types, integer_sizes)
{
	EXPECT_EQ(sizeof(s8), 1);
	EXPECT_EQ(sizeof(u8), 1);

	EXPECT_EQ(sizeof(s16), 2);
	EXPECT_EQ(sizeof(u16), 2);

	EXPECT_EQ(sizeof(s32), 4);
	EXPECT_EQ(sizeof(u32), 4);

	EXPECT_EQ(sizeof(s64), 8);
	EXPECT_EQ(sizeof(u64), 8);
}

TEST(types, floating_sizes)
{
	EXPECT_EQ(sizeof(f32), sizeof(float));
	EXPECT_EQ(sizeof(f64), sizeof(double));
}

TEST(types, signedness)
{
	EXPECT_TRUE(std::is_signed_v<s8>);
	EXPECT_TRUE(std::is_signed_v<s16>);
	EXPECT_TRUE(std::is_signed_v<s32>);
	EXPECT_TRUE(std::is_signed_v<s64>);

	EXPECT_FALSE(std::is_signed_v<u8>);
	EXPECT_FALSE(std::is_signed_v<u16>);
	EXPECT_FALSE(std::is_signed_v<u32>);
	EXPECT_FALSE(std::is_signed_v<u64>);
}

TEST(types, pointer_string_types)
{
	EXPECT_TRUE((std::is_same_v<pstr, char*>));
	EXPECT_TRUE((std::is_same_v<pcstr, const char*>));
}

TEST(types, empty_struct)
{
	EXPECT_EQ(sizeof(xr_empty), 1);
}

TEST(types, bool_definitions)
{
	EXPECT_EQ(TRUE, true);
	EXPECT_EQ(FALSE, false);
}

TEST(types, integer_limits)
{
	EXPECT_EQ(int_max, std::numeric_limits<int>::max());
	EXPECT_EQ(int_min, -std::numeric_limits<int>::max());
	EXPECT_EQ(int_zero, std::numeric_limits<int>::min());
}

TEST(types, float_limits)
{
	EXPECT_EQ(flt_max, std::numeric_limits<float>::max());
	EXPECT_EQ(flt_min, -std::numeric_limits<float>::max());

	EXPECT_EQ(dbl_max, std::numeric_limits<double>::max());
	EXPECT_EQ(dbl_min, -std::numeric_limits<double>::max());
}

TEST(types, epsilon_values)
{
	EXPECT_EQ(flt_eps, std::numeric_limits<float>::epsilon());
	EXPECT_EQ(dbl_eps, std::numeric_limits<double>::epsilon());
}

TEST(types, string_sizes)
{
	EXPECT_EQ(sizeof(string16), 16);
	EXPECT_EQ(sizeof(string32), 32);
	EXPECT_EQ(sizeof(string64), 64);
	EXPECT_EQ(sizeof(string128), 128);
	EXPECT_EQ(sizeof(string256), 256);
	EXPECT_EQ(sizeof(string512), 512);
	EXPECT_EQ(sizeof(string1024), 1024);
	EXPECT_EQ(sizeof(string2048), 2048);
	EXPECT_EQ(sizeof(string4096), 4096);
}

TEST(types, string_path_size)
{
	EXPECT_EQ(sizeof(string_path), 2 * _MAX_PATH);
}
