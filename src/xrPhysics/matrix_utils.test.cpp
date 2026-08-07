#include "stdafx.h"

#include "matrix_utils.h"

#include <gtest/gtest.h>

#include "_matrix.h"
#include "_quaternion.h"

#if 0
static constexpr float EPS = 1e-5f;
#endif


static void expect_vec_near(
	const Fvector& a,
	const Fvector& b,
	float eps = EPS)
{
	EXPECT_NEAR(a.x, b.x, eps);
	EXPECT_NEAR(a.y, b.y, eps);
	EXPECT_NEAR(a.z, b.z, eps);
}


TEST(MatrixUtils, ClampQuaternionRotationBelowLimit)
{
	Fquaternion q;

	q.rotation(
		Fvector().set(0, 1, 0),
		0.5f
	);

	float result = clamp_rotation(q, 1.0f);

	EXPECT_NEAR(result, 0.5f, EPS);

	Fvector axis;
	float angle;

	ASSERT_TRUE(q.get_axis_angle(axis, angle));

	EXPECT_NEAR(angle, 0.5f, EPS);
}


TEST(MatrixUtils, ClampQuaternionRotationAboveLimit)
{
	Fquaternion q;

	q.rotation(
		Fvector().set(0, 1, 0),
		1.5f
	);

	float result = clamp_rotation(q, 1.0f);

	EXPECT_NEAR(result, 1.5f, EPS);

	Fvector axis;
	float angle;

	ASSERT_TRUE(q.get_axis_angle(axis, angle));

	EXPECT_NEAR(angle, 1.0f, EPS);
	EXPECT_NEAR(q.magnitude(), 1.0f, EPS);
}


TEST(MatrixUtils, ClampMatrixRotationPreservesTranslation)
{
	Fmatrix m;

	m.rotation(
		Fvector().set(0, 0, 1),
		1.5f
	);

	m.c.set(10, 20, 30);

	float result = clamp_rotation(m, 0.5f);

	EXPECT_NEAR(result, 1.5f, EPS);

	expect_vec_near(
		m.c,
		Fvector().set(10, 20, 30)
	);


	Fvector axis;
	float angle;

	get_axis_angle(m, axis, angle);

	EXPECT_NEAR(angle, 0.5f, EPS);
}


TEST(MatrixUtils, GetAxisAngleIdentity)
{
	Fmatrix m;
	m.identity();

	Fvector axis;
	float angle;

	get_axis_angle(m, axis, angle);

	EXPECT_NEAR(angle, 0.0f, EPS);
}


TEST(MatrixUtils, GetAxisAngleRotation)
{
	Fmatrix m;

	m.rotation(
		Fvector().set(1, 0, 0),
		PI_DIV_2
	);

	Fvector axis;
	float angle;

	get_axis_angle(m, axis, angle);

	EXPECT_NEAR(angle, PI_DIV_2, EPS);

	expect_vec_near(
		axis,
		Fvector().set(1, 0, 0)
	);
}


TEST(MatrixUtils, CompareEqualMatrices)
{
	Fmatrix a;
	Fmatrix b;

	a.translate(1, 2, 3);
	b.translate(1, 2, 3);

	EXPECT_TRUE(
		cmp_matrix(
			a,
			b,
			EPS,
			EPS
		)
	);
}


TEST(MatrixUtils, CompareDifferentTranslation)
{
	Fmatrix a;
	Fmatrix b;

	a.translate(0, 0, 0);
	b.translate(10, 0, 0);


	EXPECT_FALSE(
		cmp_matrix(
			a,
			b,
			1.0f,
			EPS
		)
	);
}


TEST(MatrixUtils, CompareDifferentRotation)
{
	Fmatrix a;
	Fmatrix b;

	a.identity();

	b.rotation(
		Fvector().set(0, 1, 0),
		PI_DIV_2
	);


	bool linear;
	bool angular;

	cmp_matrix(
		linear,
		angular,
		a,
		b,
		EPS,
		0.1f
	);

	EXPECT_TRUE(linear);
	EXPECT_FALSE(angular);
}


TEST(MatrixUtils, GetDiffValueTranslation)
{
	Fmatrix a;
	Fmatrix b;

	a.translate(5, 0, 0);
	b.identity();

	float linear;
	float angular;

	get_diff_value(
		a,
		b,
		linear,
		angular
	);


	EXPECT_NEAR(linear, 5.0f, EPS);
	EXPECT_NEAR(angular, 0.0f, EPS);
}


TEST(MatrixUtils, GetDiffValueRotation)
{
	Fmatrix a;
	Fmatrix b;

	a.rotation(
		Fvector().set(0, 1, 0),
		PI_DIV_2
	);

	b.identity();

	float linear;
	float angular;

	get_diff_value(
		a,
		b,
		linear,
		angular
	);

	EXPECT_NEAR(linear, 0.0f, EPS);
	EXPECT_NEAR(angular, PI_DIV_2, EPS);
}


TEST(MatrixUtils, LinearDiff)
{
	Fvector result;

	linear_diff(
		result,
		Fvector().set(10, 20, 30),
		2.0f
	);

	expect_vec_near(
		result,
		Fvector().set(5, 10, 15)
	);
}


TEST(MatrixUtils, LinearDiffBetweenPoints)
{
	Fvector result;

	linear_diff(
		result,
		Fvector().set(10, 0, 0),
		Fvector().set(0, 0, 0),
		2.0f
	);

	expect_vec_near(
		result,
		Fvector().set(5, 0, 0)
	);
}


TEST(MatrixUtils, AngularDiffRotation)
{
	Fmatrix diff;

	diff.rotation(
		Fvector().set(0, 1, 0),
		1.0f
	);

	Fvector angular;

	angular_diff(
		angular,
		diff,
		1.0f
	);


	EXPECT_NEAR(
		angular.y,
		-sinf(1.0f),
		0.01f
	);
}


TEST(MatrixUtils, MatrixDiffTranslation)
{
	Fmatrix a;
	Fmatrix b;

	a.translate(0, 0, 0);
	b.translate(10, 0, 0);

	Fvector linear;
	Fvector angular;

	matrix_diff(
		linear,
		angular,
		a,
		b,
		2.0f
	);


	expect_vec_near(
		linear,
		Fvector().set(5, 0, 0)
	);

	expect_vec_near(
		angular,
		Fvector().set(0, 0, 0)
	);
}


TEST(MatrixUtils, ClampChangeWithinLimits)
{
	Fmatrix start;
	Fmatrix current;

	start.identity();

	current.translate(
		0.5f,
		0,
		0
	);

	bool result = clamp_change(
		current,
		start,
		1.0f,
		1.0f,
		1.0f,
		1.0f
	);

	EXPECT_TRUE(result);

	expect_vec_near(
		current.c,
		Fvector().set(0.5f, 0, 0)
	);
}


TEST(MatrixUtils, ClampChangeExceedsTranslation)
{
	Fmatrix start;
	Fmatrix current;

	start.identity();

	current.translate(
		10,
		0,
		0
	);

	bool result = clamp_change(
		current,
		start,
		1.0f,
		1.0f,
		0.1f,
		1.0f
	);


	EXPECT_FALSE(result);
}
