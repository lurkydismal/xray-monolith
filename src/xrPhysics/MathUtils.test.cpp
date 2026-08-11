#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "xrPhysics.h"
#include "MathUtils.h"

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

namespace
{
	constexpr float g_EPS = 1e-5f;

	void ExpectVectorNear(
		const Fvector& actual,
		float x,
		float y,
		float z,
		float eps = g_EPS)
	{
		EXPECT_NEAR(actual.x, x, eps);
		EXPECT_NEAR(actual.y, y, eps);
		EXPECT_NEAR(actual.z, z, eps);
	}

	void ExpectFloatArray3(
		const float* actual,
		float x,
		float y,
		float z,
		float eps = g_EPS)
	{
		EXPECT_NEAR(actual[0], x, eps);
		EXPECT_NEAR(actual[1], y, eps);
		EXPECT_NEAR(actual[2], z, eps);
	}

	void ExpectFloatArray4(
		const float* actual,
		float x,
		float y,
		float z,
		float w,
		float eps = g_EPS)
	{
		EXPECT_NEAR(actual[0], x, eps);
		EXPECT_NEAR(actual[1], y, eps);
		EXPECT_NEAR(actual[2], z, eps);
		EXPECT_NEAR(actual[3], w, eps);
	}
}


// ============================================================================
// cast_fp / cast_fv
// ============================================================================

TEST(MathUtils, CastFpReturnsUnderlyingVectorStorage)
{
	Fvector v;
	v.set(1.f, 2.f, 3.f);

	float* fp = cast_fp(v);

	ASSERT_NE(fp, nullptr);

	EXPECT_EQ(fp[0], 1.f);
	EXPECT_EQ(fp[1], 2.f);
	EXPECT_EQ(fp[2], 3.f);
}

TEST(MathUtils, CastFpConstReturnsUnderlyingVectorStorage)
{
	const Fvector v = Fvector().set(1.f, 2.f, 3.f);

	const float* fp = cast_fp(v);

	ASSERT_NE(fp, nullptr);

	EXPECT_EQ(fp[0], 1.f);
	EXPECT_EQ(fp[1], 2.f);
	EXPECT_EQ(fp[2], 3.f);
}

TEST(MathUtils, CastFvReturnsOriginalVector)
{
	Fvector v;
	v.set(1.f, 2.f, 3.f);

	float* fp = cast_fp(v);

	Fvector& result = cast_fv(fp);

	EXPECT_EQ(&result, &v);
	EXPECT_EQ(result.x, 1.f);
	EXPECT_EQ(result.y, 2.f);
	EXPECT_EQ(result.z, 3.f);
}

TEST(MathUtils, CastFvConstReturnsOriginalVector)
{
	const Fvector v = Fvector().set(1.f, 2.f, 3.f);

	const float* fp = cast_fp(v);

	const Fvector& result = cast_fv(fp);

	EXPECT_EQ(&result, &v);
	EXPECT_EQ(result.x, 1.f);
	EXPECT_EQ(result.y, 2.f);
	EXPECT_EQ(result.z, 3.f);
}


// ============================================================================
// dXZMag
// ============================================================================

TEST(MathUtils, DXZMagUsesOnlyXZComponents)
{
	const float v[] = {3.f, 100.f, 4.f};

	EXPECT_FLOAT_EQ(dXZMag(v), 5.f);
}

TEST(MathUtils, DXZMagVectorUsesOnlyXZComponents)
{
	const Fvector v = Fvector().set(3.f, 100.f, 4.f);

	EXPECT_FLOAT_EQ(dXZMag(v), 5.f);
}

TEST(MathUtils, DXZMagZero)
{
	const Fvector v = Fvector().set(0.f, 123.f, 0.f);

	EXPECT_FLOAT_EQ(dXZMag(v), 0.f);
}


// ============================================================================
// dXZDot
// ============================================================================

TEST(MathUtils, DXZDotUsesOnlyXZComponents)
{
	const float a[] = {1.f, 100.f, 2.f};
	const float b[] = {3.f, 200.f, 4.f};

	EXPECT_FLOAT_EQ(dXZDot(a, b), 11.f);
}

TEST(MathUtils, DXZDotVectorUsesOnlyXZComponents)
{
	const Fvector a = Fvector().set(1.f, 100.f, 2.f);
	const Fvector b = Fvector().set(3.f, 200.f, 4.f);

	EXPECT_FLOAT_EQ(dXZDot(a, b), 11.f);
}

TEST(MathUtils, DXZDotCanBeNegative)
{
	const Fvector a = Fvector().set(1.f, 100.f, 0.f);
	const Fvector b = Fvector().set(-1.f, 200.f, 0.f);

	EXPECT_FLOAT_EQ(dXZDot(a, b), -1.f);
}


// ============================================================================
// dXZDotNormalized
// ============================================================================

TEST(MathUtils, DXZDotNormalizedParallel)
{
	const Fvector a = Fvector().set(2.f, 100.f, 0.f);
	const Fvector b = Fvector().set(5.f, -200.f, 0.f);

	EXPECT_NEAR(dXZDotNormalized(a, b), 1.f, g_EPS);
}

TEST(MathUtils, DXZDotNormalizedOpposite)
{
	const Fvector a = Fvector().set(2.f, 100.f, 0.f);
	const Fvector b = Fvector().set(-5.f, -200.f, 0.f);

	EXPECT_NEAR(dXZDotNormalized(a, b), -1.f, g_EPS);
}

TEST(MathUtils, DXZDotNormalizedPerpendicular)
{
	const Fvector a = Fvector().set(1.f, 100.f, 0.f);
	const Fvector b = Fvector().set(0.f, -200.f, 1.f);

	EXPECT_NEAR(dXZDotNormalized(a, b), 0.f, g_EPS);
}

TEST(MathUtils, DXZDotNormalizedPointerOverloadMatchesVectorOverload)
{
	const Fvector a = Fvector().set(2.f, 10.f, 3.f);
	const Fvector b = Fvector().set(-4.f, 20.f, 5.f);

	EXPECT_FLOAT_EQ(
		dXZDotNormalized(a, b),
		dXZDotNormalized(cast_fp(a), cast_fp(b)));
}


// ============================================================================
// dVectorSet
// ============================================================================

TEST(MathUtils, DVectorSetCopiesThreeComponents)
{
	const float source[] = {1.f, 2.f, 3.f};
	float destination[] = {10.f, 20.f, 30.f};

	dVectorSet(destination, source);

	ExpectFloatArray3(destination, 1.f, 2.f, 3.f);
}

TEST(MathUtils, DVectorSetZero)
{
	float v[] = {1.f, 2.f, 3.f};

	dVectorSetZero(v);

	ExpectFloatArray3(v, 0.f, 0.f, 0.f);
}

TEST(MathUtils, DVectorSetInvert)
{
	const float source[] = {1.f, -2.f, 3.f};
	float destination[] = {0.f, 0.f, 0.f};

	dVectorSetInvert(destination, source);

	ExpectFloatArray3(destination, -1.f, 2.f, -3.f);
}


// ============================================================================
// dVector4Set
// ============================================================================

TEST(MathUtils, DVector4SetCopiesFourComponents)
{
	const float source[] = {1.f, 2.f, 3.f, 4.f};
	float destination[] = {10.f, 20.f, 30.f, 40.f};

	dVector4Set(destination, source);

	ExpectFloatArray4(destination, 1.f, 2.f, 3.f, 4.f);
}

TEST(MathUtils, DVector4SetZero)
{
	float v[] = {1.f, 2.f, 3.f, 4.f};

	dVector4SetZero(v);

	ExpectFloatArray4(v, 0.f, 0.f, 0.f, 0.f);
}

TEST(MathUtils, DQuaternionSetCopiesFourComponents)
{
	const float source[] = {1.f, 2.f, 3.f, 4.f};
	float destination[] = {0.f, 0.f, 0.f, 0.f};

	dQuaternionSet(destination, source);

	ExpectFloatArray4(destination, 1.f, 2.f, 3.f, 4.f);
}


// ============================================================================
// dVectorAdd
// ============================================================================

TEST(MathUtils, DVectorAddInPlace)
{
	float v[] = {1.f, 2.f, 3.f};
	const float a[] = {4.f, 5.f, 6.f};

	dVectorAdd(v, a);

	ExpectFloatArray3(v, 5.f, 7.f, 9.f);
}

TEST(MathUtils, DVectorAddFromTwoVectors)
{
	const float a[] = {1.f, 2.f, 3.f};
	const float b[] = {4.f, 5.f, 6.f};
	float result[] = {0.f, 0.f, 0.f};

	dVectorAdd(result, a, b);

	ExpectFloatArray3(result, 5.f, 7.f, 9.f);
}

TEST(MathUtils, DVectorAddMul)
{
	float v[] = {1.f, 2.f, 3.f};
	const float a[] = {4.f, 5.f, 6.f};

	dVectorAddMul(v, a, 2.f);

	ExpectFloatArray3(v, 9.f, 12.f, 15.f);
}

TEST(MathUtils, DVectorAddMulWithZero)
{
	float v[] = {1.f, 2.f, 3.f};
	const float a[] = {4.f, 5.f, 6.f};

	dVectorAddMul(v, a, 0.f);

	ExpectFloatArray3(v, 1.f, 2.f, 3.f);
}


// ============================================================================
// dVectorSub
// ============================================================================

TEST(MathUtils, DVectorSubInPlace)
{
	float v[] = {10.f, 20.f, 30.f};
	const float a[] = {1.f, 2.f, 3.f};

	dVectorSub(v, a);

	ExpectFloatArray3(v, 9.f, 18.f, 27.f);
}

TEST(MathUtils, DVectorSubFromTwoVectors)
{
	const float a[] = {10.f, 20.f, 30.f};
	const float b[] = {1.f, 2.f, 3.f};
	float result[] = {0.f, 0.f, 0.f};

	dVectorSub(result, a, b);

	ExpectFloatArray3(result, 9.f, 18.f, 27.f);
}

TEST(MathUtils, DVectorInvert)
{
	float v[] = {1.f, -2.f, 3.f};

	dVectorInvert(v);

	ExpectFloatArray3(v, -1.f, 2.f, -3.f);
}


// ============================================================================
// dVectorMul
// ============================================================================

TEST(MathUtils, DVectorMulInPlace)
{
	float v[] = {1.f, 2.f, 3.f};

	dVectorMul(v, 2.f);

	ExpectFloatArray3(v, 2.f, 4.f, 6.f);
}

TEST(MathUtils, DVectorMulIntoResult)
{
	const float v[] = {1.f, 2.f, 3.f};
	float result[] = {0.f, 0.f, 0.f};

	dVectorMul(result, v, 2.f);

	ExpectFloatArray3(result, 2.f, 4.f, 6.f);
}

TEST(MathUtils, DVectorMulByZero)
{
	float v[] = {1.f, 2.f, 3.f};

	dVectorMul(v, 0.f);

	ExpectFloatArray3(v, 0.f, 0.f, 0.f);
}


// ============================================================================
// dVectorInterpolate
// ============================================================================

TEST(MathUtils, DVectorInterpolate)
{
	float from[] = {0.f, 0.f, 0.f};
	float to[] = {10.f, 20.f, 30.f};

	dVectorInterpolate(from, to, 0.25f);

	ExpectFloatArray3(from, 2.5f, 5.f, 7.5f);
	ExpectFloatArray3(to, 2.5f, 5.f, 7.5f);
}

TEST(MathUtils, DVectorInterpolateZero)
{
	float from[] = {1.f, 2.f, 3.f};
	float to[] = {10.f, 20.f, 30.f};

	dVectorInterpolate(from, to, 0.f);

	ExpectFloatArray3(from, 1.f, 2.f, 3.f);
	ExpectFloatArray3(to, 0.f, 0.f, 0.f);
}

TEST(MathUtils, DVectorInterpolateOne)
{
	float from[] = {1.f, 2.f, 3.f};
	float to[] = {10.f, 20.f, 30.f};

	dVectorInterpolate(from, to, 1.f);

	ExpectFloatArray3(from, 10.f, 20.f, 30.f);
	ExpectFloatArray3(to, 10.f, 20.f, 30.f);
}


// ============================================================================
// deviation
// ============================================================================

TEST(MathUtils, DVectorDeviation)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {5.f, 7.f, 11.f};
	float deviation[] = {0.f, 0.f, 0.f};

	dVectorDeviation(from, to, deviation);

	ExpectFloatArray3(deviation, 4.f, 5.f, 8.f);
}

TEST(MathUtils, DVectorDeviationAdd)
{
	const float from[] = {1.f, 2.f, 3.f};
	const float to[] = {5.f, 7.f, 11.f};
	float deviation[] = {10.f, 20.f, 30.f};

	dVectorDeviationAdd(from, to, deviation);

	// Note: this function intentionally uses:
	//
	//     vector_dev += vector3_from - vector3_to
	//
	// rather than the direction used by dVectorDeviation().
	ExpectFloatArray3(deviation, 6.f, 15.f, 22.f);
}


// ============================================================================
// matrix deviation
// ============================================================================

TEST(MathUtils, DMatrixSmallDeviationUsesExpectedElements)
{
	float from[16] = {};
	float to[16] = {};

	from[10] = 10.f;
	from[2] = 20.f;
	from[4] = 30.f;

	to[10] = 1.f;
	to[2] = 2.f;
	to[4] = 3.f;

	float result[] = {0.f, 0.f, 0.f};

	dMatrixSmallDeviation(from, to, result);

	ExpectFloatArray3(result, 9.f, 18.f, 27.f);
}

TEST(MathUtils, DMatrixSmallDeviationAdd)
{
	float from[16] = {};
	float to[16] = {};

	from[10] = 10.f;
	from[2] = 20.f;
	from[4] = 30.f;

	to[10] = 1.f;
	to[2] = 2.f;
	to[4] = 3.f;

	float result[] = {100.f, 200.f, 300.f};

	dMatrixSmallDeviationAdd(from, to, result);

	ExpectFloatArray3(result, 109.f, 218.f, 327.f);
}


// ============================================================================
// to_mag_and_dir
// ============================================================================

TEST(MathUtils, ToMagAndDirReturnsMagnitude)
{
	const Fvector input = Fvector().set(3.f, 4.f, 0.f);
	Fvector direction;

	const float magnitude = to_mag_and_dir(input, direction);

	EXPECT_FLOAT_EQ(magnitude, 5.f);
}

TEST(MathUtils, ToMagAndDirNormalizesDirection)
{
	const Fvector input = Fvector().set(3.f, 4.f, 0.f);
	Fvector direction;

	to_mag_and_dir(input, direction);

	ExpectVectorNear(direction, 0.6f, 0.8f, 0.f);
}

TEST(MathUtils, ToMagAndDirHandlesZeroVector)
{
	const Fvector input = Fvector().set(0.f, 0.f, 0.f);
	Fvector direction = Fvector().set(1.f, 2.f, 3.f);

	const float magnitude = to_mag_and_dir(input, direction);

	EXPECT_FLOAT_EQ(magnitude, 0.f);
	ExpectVectorNear(direction, 0.f, 0.f, 0.f);
}

TEST(MathUtils, ToMagAndDirInPlace)
{
	Fvector v = Fvector().set(3.f, 4.f, 0.f);

	const float magnitude = to_mag_and_dir(v);

	EXPECT_FLOAT_EQ(magnitude, 5.f);
	ExpectVectorNear(v, 0.6f, 0.8f, 0.f);
}

TEST(MathUtils, ToVectorMultipliesDirectionByMagnitude)
{
	const Fvector direction = Fvector().set(1.f, 2.f, 3.f);
	Fvector result;

	to_vector(result, 4.f, direction);

	ExpectVectorNear(result, 4.f, 8.f, 12.f);
}


// ============================================================================
// prg_pos_on_axis
// ============================================================================

TEST(MathUtils, PrgPosOnAxisProjectsPointOntoAxis)
{
	const Fvector axisPoint = Fvector().set(1.f, 2.f, 3.f);
	const Fvector axisDirection = Fvector().set(1.f, 0.f, 0.f);

	Fvector point = Fvector().set(4.f, 10.f, -5.f);

	prg_pos_on_axis(axisPoint, axisDirection, point);

	ExpectVectorNear(point, 4.f, 2.f, 3.f);
}

TEST(MathUtils, PrgPosOnAxisWorksWithNonUnitDirection)
{
	const Fvector axisPoint = Fvector().set(1.f, 2.f, 3.f);
	const Fvector axisDirection = Fvector().set(2.f, 0.f, 0.f);

	Fvector point = Fvector().set(5.f, 10.f, -5.f);

	prg_pos_on_axis(axisPoint, axisDirection, point);

	ExpectVectorNear(point, 5.f, 2.f, 3.f);
}


// ============================================================================
// prg_pos_on_plane
// ============================================================================

TEST(MathUtils, PrgPosOnPlaneProjectsPointOntoPlane)
{
	const Fvector normal = Fvector().set(0.f, 1.f, 0.f);
	const Fvector position = Fvector().set(1.f, 5.f, 3.f);

	Fvector result;

	const float projection = prg_pos_on_plane(
		normal,
		2.f,
		position,
		result);

	EXPECT_FLOAT_EQ(projection, -3.f);
	ExpectVectorNear(result, 1.f, 2.f, 3.f);
}

TEST(MathUtils, PrgPosOnPlanePointAlreadyOnPlane)
{
	const Fvector normal = Fvector().set(0.f, 1.f, 0.f);
	const Fvector position = Fvector().set(1.f, 2.f, 3.f);

	Fvector result;

	const float projection = prg_pos_on_plane(
		normal,
		2.f,
		position,
		result);

	EXPECT_FLOAT_EQ(projection, 0.f);
	ExpectVectorNear(result, 1.f, 2.f, 3.f);
}


// ============================================================================
// prg_on_normal
// ============================================================================

TEST(MathUtils, PrgOnNormalRemovesNormalComponent)
{
	const Fvector normal = Fvector().set(0.f, 1.f, 0.f);
	const Fvector direction = Fvector().set(1.f, 5.f, 3.f);

	Fvector result;

	prg_on_normal(normal, direction, result);

	ExpectVectorNear(result, 1.f, 0.f, 3.f);
}

TEST(MathUtils, PrgOnNormalParallelDirectionBecomesZero)
{
	const Fvector normal = Fvector().set(0.f, 1.f, 0.f);
	const Fvector direction = Fvector().set(0.f, 5.f, 0.f);

	Fvector result;

	prg_on_normal(normal, direction, result);

	ExpectVectorNear(result, 0.f, 0.f, 0.f);
}


// ============================================================================
// restrict_vector_in_dir
// ============================================================================

TEST(MathUtils, RestrictVectorInDirRemovesPositiveProjection)
{
	Fvector v = Fvector().set(1.f, 5.f, 3.f);
	const Fvector dir = Fvector().set(0.f, 1.f, 0.f);

	restrict_vector_in_dir(v, dir);

	ExpectVectorNear(v, 1.f, 0.f, 3.f);
}

TEST(MathUtils, RestrictVectorInDirLeavesNegativeProjection)
{
	Fvector v = Fvector().set(1.f, -5.f, 3.f);
	const Fvector dir = Fvector().set(0.f, 1.f, 0.f);

	restrict_vector_in_dir(v, dir);

	ExpectVectorNear(v, 1.f, -5.f, 3.f);
}

TEST(MathUtils, RestrictVectorInDirLeavesPerpendicularVector)
{
	Fvector v = Fvector().set(1.f, 0.f, 3.f);
	const Fvector dir = Fvector().set(0.f, 1.f, 0.f);

	restrict_vector_in_dir(v, dir);

	ExpectVectorNear(v, 1.f, 0.f, 3.f);
}


// ============================================================================
// check_obb_sise
// ============================================================================

TEST(MathUtils, CheckObbSizeReturnsFalseForZeroHalfSize)
{
	Fobb obb{};

	obb.m_halfsize.set(0.f, 0.f, 0.f);

	EXPECT_FALSE(check_obb_sise(obb));
}

TEST(MathUtils, CheckObbSizeReturnsTrueForNonZeroHalfSize)
{
	Fobb obb{};

	obb.m_halfsize.set(1.f, 0.f, 0.f);

	EXPECT_TRUE(check_obb_sise(obb));
}

TEST(MathUtils, CheckObbSizeAcceptsAnyNonZeroAxis)
{
	Fobb obb{};

	obb.m_halfsize.set(0.f, 2.f, 0.f);
	EXPECT_TRUE(check_obb_sise(obb));

	obb.m_halfsize.set(0.f, 0.f, 3.f);
	EXPECT_TRUE(check_obb_sise(obb));
}


// ============================================================================
// fsignum
// ============================================================================

TEST(MathUtils, FSignumReturnsNegativeOneForNegativeValue)
{
	EXPECT_FLOAT_EQ(fsignum(-1.f), -1.f);
}

TEST(MathUtils, FSignumReturnsPositiveOneForPositiveValue)
{
	EXPECT_FLOAT_EQ(fsignum(1.f), 1.f);
}

TEST(MathUtils, FSignumReturnsPositiveOneForZero)
{
	EXPECT_FLOAT_EQ(fsignum(0.f), 1.f);
}

TEST(MathUtils, FSignumReturnsPositiveOneForNegativeZero)
{
	EXPECT_FLOAT_EQ(fsignum(-0.f), 1.f);
}


// ============================================================================
// save_max / save_min
// ============================================================================

TEST(MathUtils, SaveMaxReplacesSmallerValue)
{
	float value = 10.f;

	save_max(value, 20.f);

	EXPECT_FLOAT_EQ(value, 20.f);
}

TEST(MathUtils, SaveMaxKeepsLargerValue)
{
	float value = 20.f;

	save_max(value, 10.f);

	EXPECT_FLOAT_EQ(value, 20.f);
}

TEST(MathUtils, SaveMinReplacesLargerValue)
{
	float value = 20.f;

	save_min(value, 10.f);

	EXPECT_FLOAT_EQ(value, 10.f);
}

TEST(MathUtils, SaveMinKeepsSmallerValue)
{
	float value = 10.f;

	save_min(value, 20.f);

	EXPECT_FLOAT_EQ(value, 10.f);
}


// ============================================================================
// limit_above / limit_below
// ============================================================================

TEST(MathUtils, LimitAboveClampsValue)
{
	float value = 20.f;

	limit_above(value, 10.f);

	EXPECT_FLOAT_EQ(value, 10.f);
}

TEST(MathUtils, LimitAboveKeepsValueBelowLimit)
{
	float value = 5.f;

	limit_above(value, 10.f);

	EXPECT_FLOAT_EQ(value, 5.f);
}

TEST(MathUtils, LimitBelowClampsValue)
{
	float value = 5.f;

	limit_below(value, 10.f);

	EXPECT_FLOAT_EQ(value, 10.f);
}

TEST(MathUtils, LimitBelowKeepsValueAboveLimit)
{
	float value = 20.f;

	limit_below(value, 10.f);

	EXPECT_FLOAT_EQ(value, 20.f);
}


// ============================================================================
// TransferenceToThrowVel
// ============================================================================

TEST(MathUtils, TransferenceToThrowVel)
{
	Fvector velocity = Fvector().set(10.f, 20.f, 30.f);

	TransferenceToThrowVel(velocity, 2.f, 10.f);

	// horizontal velocity = transference / time
	// vertical velocity = transference / time + time * gravity / 2
	ExpectVectorNear(velocity, 5.f, 30.f, 15.f);
}

TEST(MathUtils, TransferenceToThrowVelZeroGravity)
{
	Fvector velocity = Fvector().set(10.f, 20.f, 30.f);

	TransferenceToThrowVel(velocity, 2.f, 0.f);

	ExpectVectorNear(velocity, 5.f, 10.f, 15.f);
}


// ============================================================================
// ThrowMinVelTime
// ============================================================================

TEST(MathUtils, ThrowMinVelTime)
{
	const Fvector transference = Fvector().set(3.f, 4.f, 0.f);

	const float result = ThrowMinVelTime(transference, 10.f);

	EXPECT_NEAR(result, std::sqrt(2.f * 5.f / 10.f), g_EPS);
}

TEST(MathUtils, ThrowMinVelTimeUsesFullVectorMagnitude)
{
	const Fvector transference = Fvector().set(3.f, 4.f, 12.f);

	const float magnitude = transference.magnitude();

	const float result = ThrowMinVelTime(transference, 10.f);

	EXPECT_NEAR(
		result,
		std::sqrt(2.f * magnitude / 10.f),
		g_EPS);
}


// ============================================================================
// TransferenceAndThrowVelToTgA
// ============================================================================

TEST(MathUtils, TransferenceAndThrowVelToTgAHasNoSolution)
{
	const Fvector transference = Fvector().set(100.f, 100.f, 0.f);

	Fvector2 tgA;
	float s = 0.f;

	const u8 result = TransferenceAndThrowVelToTgA(
		transference,
		1.f,
		10.f,
		tgA,
		s);

	EXPECT_EQ(result, 0);
}

TEST(MathUtils, TransferenceAndThrowVelToTgAReturnsTwoSolutions)
{
	const Fvector transference = Fvector().set(10.f, 0.f, 0.f);

	Fvector2 tgA;
	float s = 0.f;

	const u8 result = TransferenceAndThrowVelToTgA(
		transference,
		20.f,
		10.f,
		tgA,
		s);

	EXPECT_EQ(result, 2);
	EXPECT_NEAR(s, 10.f, g_EPS);

	EXPECT_LT(tgA.x, tgA.y);
}

TEST(MathUtils, TransferenceAndThrowVelToTgAOverloadMatches)
{
	const Fvector transference = Fvector().set(10.f, 0.f, 0.f);

	Fvector2 first;
	Fvector2 second;

	const u8 result1 = TransferenceAndThrowVelToTgA(
		transference,
		20.f,
		10.f,
		first);

	const u8 result2 = TransferenceAndThrowVelToTgA(
		transference,
		20.f,
		10.f,
		second);

	EXPECT_EQ(result1, result2);
	EXPECT_FLOAT_EQ(first.x, second.x);
	EXPECT_FLOAT_EQ(first.y, second.y);
}


// ============================================================================
// TransferenceAndThrowVelToThrowDir
// ============================================================================

TEST(MathUtils, TransferenceAndThrowVelToThrowDirHasNoSolution)
{
	const Fvector transference = Fvector().set(100.f, 100.f, 0.f);

	Fvector directions[2];

	EXPECT_EQ(
		TransferenceAndThrowVelToThrowDir(
			transference,
			1.f,
			10.f,
			directions),
		0);
}

TEST(MathUtils, TransferenceAndThrowVelToThrowDirReturnsNormalizedDirections)
{
	const Fvector transference = Fvector().set(10.f, 0.f, 0.f);

	Fvector directions[2];

	const u8 result = TransferenceAndThrowVelToThrowDir(
		transference,
		20.f,
		10.f,
		directions);

	ASSERT_EQ(result, 2);

	EXPECT_NEAR(directions[0].magnitude(), 1.f, g_EPS);
	EXPECT_NEAR(directions[1].magnitude(), 1.f, g_EPS);

	// Both solutions point toward the target horizontally.
	EXPECT_GT(directions[0].x, 0.f);
	EXPECT_GT(directions[1].x, 0.f);

	// The two solutions have different elevation.
	EXPECT_LT(directions[0].y, directions[1].y);
}


// ============================================================================
// twoq_2w
// ============================================================================

TEST(MathUtils, TwoQ2WIdenticalQuaternionsProduceZeroAngularVelocity)
{
	Fquaternion q1;
	Fquaternion q2;

	q1.set(0.f, 0.f, 0.f, 1.f);
	q2.set(0.f, 0.f, 0.f, 1.f);

	Fvector w;

	twoq_2w(q1, q2, 1.f, w);

	ExpectVectorNear(w, 0.f, 0.f, 0.f);
}

TEST(MathUtils, TwoQ2WProducesAngularVelocityForRotation)
{
	const float halfAngle = 0.5f * 0.5f;

	Fquaternion q1;
	Fquaternion q2;

	// q1 = identity.
	q1.set(0.f, 0.f, 0.f, 1.f);

	// 1 radian rotation around Y.
	const float halfRotation = 0.5f;
	q2.set(
		0.f,
		std::sin(halfRotation),
		0.f,
		std::cos(halfRotation));

	Fvector w;

	twoq_2w(q1, q2, 1.f, w);

	EXPECT_NEAR(w.x, 0.f, 1e-4f);
	EXPECT_NEAR(w.y, -1.f, 1e-4f);
	EXPECT_NEAR(w.z, 0.f, 1e-4f);

	(void)halfAngle;
}


// ============================================================================
// SInertVal
// ============================================================================

TEST(MathUtils, SInertValUsesInertion)
{
	SInertVal value(0.25f);

	value.val = 0.f;
	value.new_val(100.f);

	EXPECT_FLOAT_EQ(value.val, 75.f);
}

TEST(MathUtils, SInertValCanBeUpdatedRepeatedly)
{
	SInertVal value(0.5f);

	value.val = 0.f;

	value.new_val(100.f);
	EXPECT_FLOAT_EQ(value.val, 50.f);

	value.new_val(100.f);
	EXPECT_FLOAT_EQ(value.val, 75.f);

	value.new_val(100.f);
	EXPECT_FLOAT_EQ(value.val, 87.5f);
}


// ============================================================================
// DET
// ============================================================================

TEST(MathUtils, DetIdentityMatrix)
{
	Fmatrix matrix;
	matrix.identity();

	EXPECT_NEAR(DET(matrix), 1.f, g_EPS);
}

TEST(MathUtils, DetDiagonalMatrix)
{
	Fmatrix matrix;
	matrix.identity();

	matrix._11 = 2.f;
	matrix._22 = 3.f;
	matrix._33 = 4.f;

	EXPECT_NEAR(DET(matrix), 24.f, g_EPS);
}

TEST(MathUtils, DetNegativeScale)
{
	Fmatrix matrix;
	matrix.identity();

	matrix._11 = -2.f;
	matrix._22 = 3.f;
	matrix._33 = 4.f;

	EXPECT_NEAR(DET(matrix), -24.f, g_EPS);
}

TEST(MathUtils, DetZeroMatrix)
{
	Fmatrix matrix{};

	EXPECT_FLOAT_EQ(DET(matrix), 0.f);
}


// ============================================================================
// valid_pos
// ============================================================================

TEST(MathUtils, ValidPosInsideBox)
{
	Fbox box;

	box.set(
		Fvector().set(-1.f, -1.f, -1.f),
		Fvector().set(1.f, 1.f, 1.f));

	const Fvector position = Fvector().set(0.f, 0.f, 0.f);

	EXPECT_TRUE(valid_pos(position, box));
}

TEST(MathUtils, ValidPosOutsideOrdinaryBoxButWithinExpandedBox)
{
	Fbox box;

	box.set(
		Fvector().set(-1.f, -1.f, -1.f),
		Fvector().set(1.f, 1.f, 1.f));

	const Fvector position = Fvector().set(100.f, 0.f, 0.f);

	// valid_pos expands the box by 100000.
	EXPECT_TRUE(valid_pos(position, box));
}

TEST(MathUtils, ValidPosFarOutsideExpandedBox)
{
	Fbox box;

	box.set(
		Fvector().set(-1.f, -1.f, -1.f),
		Fvector().set(1.f, 1.f, 1.f));

	const Fvector position = Fvector().set(200000.f, 0.f, 0.f);

	EXPECT_FALSE(valid_pos(position, box));
}


// ============================================================================
// phInfinity
// ============================================================================

TEST(MathUtils, PhInfinityIsPositiveInfinity)
{
	EXPECT_TRUE(std::isinf(phInfinity));
	EXPECT_GT(phInfinity, 0.f);
}


// ============================================================================
// Three-value selection macros
//
// These tests deliberately test the observable selection order. The macros
// execute arbitrary statements rather than returning a value.
// ============================================================================

TEST(MathUtils, MaxOfSelectsMaximum)
{
	int selected = 0;

	const float x = 1.f;
	const float y = 3.f;
	const float z = 2.f;

	MAX_OF(
		x, selected = 1,
		y, selected = 2,
		z, selected = 3);

	EXPECT_EQ(selected, 2);
}

TEST(MathUtils, MaxOfSelectsZWhenZIsMaximum)
{
	int selected = 0;

	const float x = 1.f;
	const float y = 2.f;
	const float z = 3.f;

	MAX_OF(
		x, selected = 1,
		y, selected = 2,
		z, selected = 3);

	EXPECT_EQ(selected, 3);
}

TEST(MathUtils, MaxOfSelectsXWhenXIsMaximum)
{
	int selected = 0;

	const float x = 3.f;
	const float y = 2.f;
	const float z = 1.f;

	MAX_OF(
		x, selected = 1,
		y, selected = 2,
		z, selected = 3);

	EXPECT_EQ(selected, 1);
}

TEST(MathUtils, MinOfSelectsMinimum)
{
	int selected = 0;

	const float x = 1.f;
	const float y = 3.f;
	const float z = 2.f;

	MIN_OF(
		x, selected = 1,
		y, selected = 2,
		z, selected = 3);

	EXPECT_EQ(selected, 1);
}

TEST(MathUtils, MinOfSelectsZWhenZIsMinimum)
{
	int selected = 0;

	const float x = 3.f;
	const float y = 2.f;
	const float z = 1.f;

	MIN_OF(
		x, selected = 1,
		y, selected = 2,
		z, selected = 3);

	EXPECT_EQ(selected, 3);
}

TEST(MathUtils, MinOfSelectsYWhenYIsMinimum)
{
	int selected = 0;

	const float x = 3.f;
	const float y = 1.f;
	const float z = 2.f;

	MIN_OF(
		x, selected = 1,
		y, selected = 2,
		z, selected = 3);

	EXPECT_EQ(selected, 2);
}
