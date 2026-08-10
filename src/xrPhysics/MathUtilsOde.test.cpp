#include "stdafx.h"

#include "MathUtilsOde.h"

#include <gtest/gtest.h>

namespace
{
	constexpr float EPS = 1e-5f;

	void expect_vector_near(
		const float* actual,
		float x,
		float y,
		float z,
		float epsilon = EPS)
	{
		EXPECT_NEAR(actual[0], x, epsilon);
		EXPECT_NEAR(actual[1], y, epsilon);
		EXPECT_NEAR(actual[2], z, epsilon);
	}

	float magnitude(const float* v)
	{
		return std::sqrt(
			v[0] * v[0] +
			v[1] * v[1] +
			v[2] * v[2]);
	}
}


// =============================================================================
// accurate_normalize
// =============================================================================

TEST(MathUtilsOde, AccurateNormalizeNormalizesVector)
{
	float v[] = {3.f, 4.f, 0.f};

	accurate_normalize(v);

	expect_vector_near(v, 0.6f, 0.8f, 0.f);
	EXPECT_NEAR(magnitude(v), 1.f, EPS);
}

TEST(MathUtilsOde, AccurateNormalizeNormalizesThreeDimensionalVector)
{
	float v[] = {2.f, 3.f, 6.f};

	accurate_normalize(v);

	const float expected_length = std::sqrt(49.f);

	EXPECT_NEAR(magnitude(v), 1.f, EPS);
	EXPECT_NEAR(v[0], 2.f / expected_length, EPS);
	EXPECT_NEAR(v[1], 3.f / expected_length, EPS);
	EXPECT_NEAR(v[2], 6.f / expected_length, EPS);
}

TEST(MathUtilsOde, AccurateNormalizePreservesPositiveDirection)
{
	float v[] = {1.f, 2.f, 3.f};

	const float before_length = magnitude(v);

	accurate_normalize(v);

	EXPECT_NEAR(v[0], 1.f / before_length, EPS);
	EXPECT_NEAR(v[1], 2.f / before_length, EPS);
	EXPECT_NEAR(v[2], 3.f / before_length, EPS);
}

TEST(MathUtilsOde, AccurateNormalizePreservesNegativeDirection)
{
	float v[] = {-1.f, -2.f, -3.f};

	const float before_length = magnitude(v);

	accurate_normalize(v);

	EXPECT_NEAR(v[0], -1.f / before_length, EPS);
	EXPECT_NEAR(v[1], -2.f / before_length, EPS);
	EXPECT_NEAR(v[2], -3.f / before_length, EPS);
}

TEST(MathUtilsOde, AccurateNormalizeHandlesZeroVector)
{
	float v[] = {0.f, 0.f, 0.f};

	accurate_normalize(v);

	// The implementation explicitly chooses +X for a zero vector.
	expect_vector_near(v, 1.f, 0.f, 0.f);
}

TEST(MathUtilsOde, AccurateNormalizeHandlesVerySmallVector)
{
	float v[] = {
		1e-10f,
		2e-10f,
		3e-10f
	};

	accurate_normalize(v);

	EXPECT_NEAR(magnitude(v), 1.f, EPS);

	// Direction should be preserved even through the small-vector path.
	EXPECT_GT(v[0], 0.f);
	EXPECT_GT(v[1], 0.f);
	EXPECT_GT(v[2], 0.f);

	EXPECT_NEAR(
		v[1] / v[0],
		2.f,
		EPS);

	EXPECT_NEAR(
		v[2] / v[0],
		3.f,
		EPS);
}

TEST(MathUtilsOde, AccurateNormalizeHandlesNegativeDominantX)
{
	float v[] = {-10.f, 1.f, 2.f};

	accurate_normalize(v);

	EXPECT_NEAR(magnitude(v), 1.f, EPS);
	EXPECT_LT(v[0], 0.f);
	EXPECT_GT(v[1], 0.f);
	EXPECT_GT(v[2], 0.f);
}

TEST(MathUtilsOde, AccurateNormalizeHandlesNegativeDominantY)
{
	float v[] = {1.f, -10.f, 2.f};

	accurate_normalize(v);

	EXPECT_NEAR(magnitude(v), 1.f, EPS);
	EXPECT_GT(v[0], 0.f);
	EXPECT_LT(v[1], 0.f);
	EXPECT_GT(v[2], 0.f);
}

TEST(MathUtilsOde, AccurateNormalizeHandlesNegativeDominantZ)
{
	float v[] = {1.f, 2.f, -10.f};

	accurate_normalize(v);

	EXPECT_NEAR(magnitude(v), 1.f, EPS);
	EXPECT_GT(v[0], 0.f);
	EXPECT_GT(v[1], 0.f);
	EXPECT_LT(v[2], 0.f);
}

TEST(MathUtilsOde, AccurateNormalizeHandlesAxisAlignedVector)
{
	float v[] = {0.f, -5.f, 0.f};

	accurate_normalize(v);

	expect_vector_near(v, 0.f, -1.f, 0.f);
}

TEST(MathUtilsOde, AccurateNormalizeIsIdempotentForUnitVector)
{
	float v[] = {
		0.f,
		0.6f,
		0.8f
	};

	accurate_normalize(v);

	float first[] = {
		v[0],
		v[1],
		v[2]
	};

	accurate_normalize(v);

	expect_vector_near(
		v,
		first[0],
		first[1],
		first[2]);
}


// =============================================================================
// dVectorLimit
// =============================================================================

TEST(MathUtilsOde, VectorLimitLeavesShorterVectorUnchanged)
{
	const float v[] = {1.f, 2.f, 2.f};
	float result[] = {0.f, 0.f, 0.f};

	const bool limited = dVectorLimit(
		v,
		10.f,
		result);

	EXPECT_FALSE(limited);

	expect_vector_near(result, 1.f, 2.f, 2.f);
}

TEST(MathUtilsOde, VectorLimitLeavesVectorAtLimitUnchanged)
{
	const float v[] = {3.f, 4.f, 0.f};
	float result[] = {0.f, 0.f, 0.f};

	const bool limited = dVectorLimit(
		v,
		5.f,
		result);

	EXPECT_FALSE(limited);

	expect_vector_near(result, 3.f, 4.f, 0.f);
}

TEST(MathUtilsOde, VectorLimitScalesVectorDownToLimit)
{
	const float v[] = {3.f, 4.f, 0.f};
	float result[] = {0.f, 0.f, 0.f};

	const bool limited = dVectorLimit(
		v,
		2.5f,
		result);

	EXPECT_TRUE(limited);

	EXPECT_NEAR(magnitude(result), 2.5f, EPS);

	expect_vector_near(
		result,
		1.5f,
		2.f,
		0.f);
}

TEST(MathUtilsOde, VectorLimitPreservesDirection)
{
	const float v[] = {2.f, 3.f, 6.f};
	float result[] = {0.f, 0.f, 0.f};

	const float original_length = magnitude(v);
	const float limit = 2.f;

	const bool limited = dVectorLimit(
		v,
		limit,
		result);

	ASSERT_TRUE(limited);

	EXPECT_NEAR(magnitude(result), limit, EPS);

	const float scale = limit / original_length;

	EXPECT_NEAR(result[0], v[0] * scale, EPS);
	EXPECT_NEAR(result[1], v[1] * scale, EPS);
	EXPECT_NEAR(result[2], v[2] * scale, EPS);
}

TEST(MathUtilsOde, VectorLimitDoesNotModifyInput)
{
	const float v[] = {3.f, 4.f, 0.f};
	float result[] = {0.f, 0.f, 0.f};

	dVectorLimit(v, 2.f, result);

	expect_vector_near(v, 3.f, 4.f, 0.f);
}

TEST(MathUtilsOde, VectorLimitCopiesInputWhenNoLimitIsNeeded)
{
	const float v[] = {-1.f, 2.f, -3.f};
	float result[] = {99.f, 99.f, 99.f};

	const bool limited = dVectorLimit(
		v,
		100.f,
		result);

	EXPECT_FALSE(limited);

	expect_vector_near(result, -1.f, 2.f, -3.f);
}

TEST(MathUtilsOde, VectorLimitHandlesZeroVector)
{
	const float v[] = {0.f, 0.f, 0.f};
	float result[] = {99.f, 99.f, 99.f};

	const bool limited = dVectorLimit(
		v,
		1.f,
		result);

	EXPECT_FALSE(limited);

	expect_vector_near(result, 0.f, 0.f, 0.f);
}

TEST(MathUtilsOde, VectorLimitProducesCorrectResultForNegativeVector)
{
	const float v[] = {-3.f, -4.f, 0.f};
	float result[] = {0.f, 0.f, 0.f};

	const bool limited = dVectorLimit(
		v,
		2.5f,
		result);

	EXPECT_TRUE(limited);

	expect_vector_near(
		result,
		-1.5f,
		-2.f,
		0.f);
}


// =============================================================================
// dVectorInterpolate
// =============================================================================

TEST(MathUtilsOde, VectorInterpolateAtZeroReturnsFrom)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {10.f, 20.f, 30.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		0.f);

	expect_vector_near(result, 1.f, 2.f, 3.f);
}

TEST(MathUtilsOde, VectorInterpolateAtOneReturnsTo)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {10.f, 20.f, 30.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		1.f);

	expect_vector_near(result, 10.f, 20.f, 30.f);
}

TEST(MathUtilsOde, VectorInterpolateAtHalfReturnsMidpoint)
{
	const float from[] = {0.f, 0.f, 0.f};
	const float to[] = {10.f, 20.f, 30.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		0.5f);

	expect_vector_near(result, 5.f, 10.f, 15.f);
}

TEST(MathUtilsOde, VectorInterpolateInterpolatesEachComponent)
{
	const float from[] = {-10.f, 5.f, 20.f};
	const float to[] = {10.f, 15.f, 30.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		0.25f);

	expect_vector_near(
		result,
		-5.f,
		7.5f,
		22.5f);
}

TEST(MathUtilsOde, VectorInterpolateCanExtrapolate)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {5.f, 6.f, 7.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		2.f);

	expect_vector_near(
		result,
		9.f,
		10.f,
		11.f);
}

TEST(MathUtilsOde, VectorInterpolateSupportsNegativeFactor)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {5.f, 6.f, 7.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		-1.f);

	expect_vector_near(
		result,
		-3.f,
		-2.f,
		-1.f);
}

TEST(MathUtilsOde, VectorInterpolateDoesNotModifyFrom)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {10.f, 20.f, 30.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		0.5f);

	expect_vector_near(from, 1.f, 2.f, 3.f);
}

TEST(MathUtilsOde, VectorInterpolateDoesNotModifyTo)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {10.f, 20.f, 30.f};

	float result[] = {0.f, 0.f, 0.f};

	dVectorInterpolate(
		result,
		from,
		to,
		0.5f);

	expect_vector_near(to, 10.f, 20.f, 30.f);
}

TEST(MathUtilsOde, VectorInterpolateSupportsAliasingResultWithFrom)
{
	float from[] = {1.f, 2.f, 3.f};
	const float to[] = {5.f, 6.f, 7.f};

	dVectorInterpolate(
		from,
		from,
		to,
		0.5f);

	expect_vector_near(
		from,
		3.f,
		4.f,
		5.f);
}

TEST(MathUtilsOde, VectorInterpolateSupportsAliasingResultWithTo)
{
	const float from[] = {1.f, 2.f, 3.f};
	float to[] = {5.f, 6.f, 7.f};

	dVectorInterpolate(
		to,
		from,
		to,
		0.5f);

	expect_vector_near(
		to,
		3.f,
		4.f,
		5.f);
}
