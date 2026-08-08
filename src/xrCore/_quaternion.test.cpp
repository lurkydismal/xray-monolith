#include "stdafx.h"

#include "_quaternion.h"

#include <gtest/gtest.h>

#include "_matrix.h"

#include <cmath>

static constexpr float g_EPS = 1e-5f;

static void expect_quat_near(const Fquaternion& a, const Fquaternion& b, float eps = g_EPS)
{
	EXPECT_NEAR(a.x, b.x, eps);
	EXPECT_NEAR(a.y, b.y, eps);
	EXPECT_NEAR(a.z, b.z, eps);
	EXPECT_NEAR(a.w, b.w, eps);
}

static void expect_vec_near(const Fvector& a, const Fvector& b, float eps = g_EPS)
{
	EXPECT_NEAR(a.x, b.x, eps);
	EXPECT_NEAR(a.y, b.y, eps);
	EXPECT_NEAR(a.z, b.z, eps);
}


TEST(Quaternion, Identity)
{
	Fquaternion q;

	q.identity();

	EXPECT_FLOAT_EQ(q.w, 1.0f);
	EXPECT_FLOAT_EQ(q.x, 0.0f);
	EXPECT_FLOAT_EQ(q.y, 0.0f);
	EXPECT_FLOAT_EQ(q.z, 0.0f);

	EXPECT_TRUE(q.isValid());
	EXPECT_TRUE(q.isUnit());
}


TEST(Quaternion, Set)
{
	Fquaternion q;

	q.set(1, 2, 3, 4);

	EXPECT_FLOAT_EQ(q.w, 1);
	EXPECT_FLOAT_EQ(q.x, 2);
	EXPECT_FLOAT_EQ(q.y, 3);
	EXPECT_FLOAT_EQ(q.z, 4);
}


TEST(Quaternion, Normalize)
{
	Fquaternion q;

	q.set(10, 0, 0, 0);
	q.normalize();

	EXPECT_NEAR(q.w, 1.0f, g_EPS);
	EXPECT_NEAR(q.x, 0.0f, g_EPS);
	EXPECT_NEAR(q.y, 0.0f, g_EPS);
	EXPECT_NEAR(q.z, 0.0f, g_EPS);

	EXPECT_TRUE(q.isUnit());
}


TEST(Quaternion, Magnitude)
{
	Fquaternion q;

	q.set(1, 2, 3, 4);

	EXPECT_FLOAT_EQ(
		q.magnitude(),
		30.0f
	);
}


TEST(Quaternion, Inverse)
{
	Fquaternion q;
	Fquaternion inv;
	Fquaternion result;

	q.rotation(
		Fvector().set(0, 1, 0),
		PI_DIV_2
	);

	inv.inverse(q);

	result.mul(q, inv);

	EXPECT_NEAR(result.w, 1.0f, g_EPS);
	EXPECT_NEAR(result.x, 0.0f, g_EPS);
	EXPECT_NEAR(result.y, 0.0f, g_EPS);
	EXPECT_NEAR(result.z, 0.0f, g_EPS);
}


TEST(Quaternion, Multiplication)
{
	Fquaternion q1;
	Fquaternion q2;
	Fquaternion result;

	q1.rotation(
		Fvector().set(1, 0, 0),
		PI_DIV_2
	);

	q2.rotation(
		Fvector().set(0, 1, 0),
		PI_DIV_2
	);

	result.mul(q1, q2);

	EXPECT_TRUE(result.isValid());

	EXPECT_NEAR(result.magnitude(), 1.0f, g_EPS);
}


TEST(Quaternion, AxisAngle)
{
	Fquaternion q;

	Fvector axis;
	float angle;

	q.rotation(
		Fvector().set(0, 0, 1),
		PI_DIV_2
	);

	ASSERT_TRUE(q.get_axis_angle(axis, angle));

	expect_vec_near(
		axis,
		Fvector().set(0, 0, 1)
	);

	EXPECT_NEAR(
		angle,
		PI_DIV_2,
		g_EPS
	);
}


TEST(Quaternion, RotationYawPitchRollProducesUnit)
{
	Fquaternion q;

	q.rotationYawPitchRoll(
		0.1f,
		0.2f,
		0.3f
	);

	EXPECT_TRUE(q.isValid());
	EXPECT_NEAR(
		q.magnitude(),
		1.0f,
		g_EPS
	);
}


TEST(Quaternion, SlerpEndpoints)
{
	Fquaternion a;
	Fquaternion b;
	Fquaternion out;

	a.identity();

	b.rotation(
		Fvector().set(0, 1, 0),
		PI_DIV_2
	);

	out.slerp(a, b, 0.0f);

	expect_quat_near(out, a);


	out.slerp(a, b, 1.0f);

	EXPECT_TRUE(
		out.cmp(b)
	);
}


TEST(Quaternion, SlerpMiddleIsUnit)
{
	Fquaternion a;
	Fquaternion b;
	Fquaternion out;

	a.identity();

	b.rotation(
		Fvector().set(0, 0, 1),
		PI
	);

	out.slerp(a, b, 0.5f);

	EXPECT_NEAR(
		out.magnitude(),
		1.0f,
		g_EPS
	);
}


TEST(Quaternion, LnExpRoundTrip)
{
	Fquaternion q;
	Fquaternion ln;
	Fquaternion exp;

	q.rotation(
		Fvector().set(0, 1, 0),
		0.7f
	);

	ln.ln(q);
	exp.exp(ln);

	EXPECT_TRUE(
		exp.cmp(q, 1e-4f)
	);
}


TEST(Quaternion, QuaternionRotationMatchesMatrix)
{
	Fquaternion q;

	Fvector axis;
	axis.set(0, 1, 0);

	float angle = PI_DIV_2;

	q.rotation(axis, angle);


	Fmatrix m;
	m.rotation(axis, angle);


	Fvector v;
	v.set(1, 0, 0);


	// Quaternion rotate:
	Fquaternion p;
	Fquaternion qi;
	Fquaternion tmp;
	Fquaternion result;

	p.set(0, v.x, v.y, v.z);

	qi.inverse(q);

	tmp.mul(q, p);
	result.mul(tmp, qi);


	Fvector qv;
	qv.set(
		result.x,
		result.y,
		result.z
	);


	// Matrix rotate:
	Fvector mv;
	m.transform_dir(mv, v);


	expect_vec_near(qv, mv);
}


TEST(Quaternion, OppositeSignsAreSameRotation)
{
	Fquaternion a;
	Fquaternion b;

	a.rotation(
		Fvector().set(1, 0, 0),
		0.5f
	);

	b.set(
		-a.w,
		-a.x,
		-a.y,
		-a.z
	);


	EXPECT_TRUE(
		a.cmp(b)
	);
}
