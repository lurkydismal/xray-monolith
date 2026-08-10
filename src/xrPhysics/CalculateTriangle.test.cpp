#include "stdafx.h"

#include "CalculateTriangle.h"

#include <gtest/gtest.h>

namespace
{
	constexpr float g_EPS = 1e-5f;

	struct TriangleFixture
	{
		// Right triangle in the XY plane:
		//
		//        v2 (0, 1, 0)
		//        |\
		//        | \
		//        |  \
		//        |   \
		//        +---- v1 (1, 0, 0)
		//       v0 (0, 0, 0)
		//
		// Winding v0 -> v1 -> v2 gives +Z normal.
		Fvector vertices[3];

		CDB::TRI tri{};
		Triangle triangle{};

		TriangleFixture()
		{
			vertices[0].set(0.f, 0.f, 0.f);
			vertices[1].set(1.f, 0.f, 0.f);
			vertices[2].set(0.f, 1.f, 0.f);

			tri.verts[0] = 0;
			tri.verts[1] = 1;
			tri.verts[2] = 2;
		}
	};

	void expect_fvector_near(
		const Fvector& actual,
		float x,
		float y,
		float z,
		float epsilon = g_EPS)
	{
		EXPECT_NEAR(actual.x, x, epsilon);
		EXPECT_NEAR(actual.y, y, epsilon);
		EXPECT_NEAR(actual.z, z, epsilon);
	}

	void expect_vector3_near(
		const float* actual,
		float x,
		float y,
		float z,
		float epsilon = g_EPS)
	{
		EXPECT_NEAR(actual[0], x, epsilon);
		EXPECT_NEAR(actual[1], y, epsilon);
		EXPECT_NEAR(actual[2], z, epsilon);
	}
}


// -----------------------------------------------------------------------------
// GetNormal
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, GetNormalProducesExpectedNormal)
{
	TriangleFixture f;

	Fvector normal;
	GetNormal(&f.tri, normal, f.vertices);

	expect_fvector_near(normal, 0.f, 0.f, 1.f);
}

TEST(CalculateTriangle, GetNormalFollowsTriangleWinding)
{
	TriangleFixture f;

	// Reverse the winding.
	f.tri.verts[0] = 0;
	f.tri.verts[1] = 2;
	f.tri.verts[2] = 1;

	Fvector normal;
	GetNormal(&f.tri, normal, f.vertices);

	expect_fvector_near(normal, 0.f, 0.f, -1.f);
}


// -----------------------------------------------------------------------------
// CalculateInitTriangle
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, CalculateInitTriangleBuildsSides)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	EXPECT_EQ(f.triangle.T, &f.tri);

	// side0 = v1 - v0
	expect_vector3_near(f.triangle.side0, 1.f, 0.f, 0.f);

	// side1 = v2 - v1
	expect_vector3_near(f.triangle.side1, -1.f, 1.f, 0.f);
}

TEST(CalculateTriangle, CalculateInitTriangleProducesNormalizedNormal)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	expect_vector3_near(f.triangle.norm, 0.f, 0.f, 1.f);

	EXPECT_NEAR(
		dDOT(f.triangle.norm, f.triangle.norm),
		1.f,
		g_EPS);
}

TEST(CalculateTriangle, CalculateInitTriangleCalculatesPlaneOffset)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	// Plane is z = 0, normal is +Z:
	//
	// dot(v0, normal) = 0
	EXPECT_NEAR(f.triangle.pos, 0.f, g_EPS);
}


// -----------------------------------------------------------------------------
// CalculateTriangle
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, CalculateTriangleCalculatesPositiveDistance)
{
	TriangleFixture f;

	const float position[] = {
		0.25f,
		0.25f,
		2.f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	EXPECT_NEAR(f.triangle.dist, 2.f, g_EPS);
}

TEST(CalculateTriangle, CalculateTriangleCalculatesNegativeDistance)
{
	TriangleFixture f;

	const float position[] = {
		0.25f,
		0.25f,
		-2.f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	EXPECT_NEAR(f.triangle.dist, -2.f, g_EPS);
}

TEST(CalculateTriangle, CalculateTriangleCalculatesZeroDistanceOnPlane)
{
	TriangleFixture f;

	const float position[] = {
		0.25f,
		0.25f,
		0.f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	EXPECT_NEAR(f.triangle.dist, 0.f, g_EPS);
}


// -----------------------------------------------------------------------------
// TriContainPoint
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, TriContainPointReturnsTrueForInteriorPoint)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	const float position[] = {
		0.25f,
		0.25f,
		0.f
	};

	u16 code = 999;

	EXPECT_TRUE(
		TriContainPoint(
			&f.triangle,
			position,
			code,
			f.vertices));

	EXPECT_EQ(code, 0);
}

TEST(CalculateTriangle, TriContainPointReturnsTrueForPointOnEdge)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	const float position[] = {
		0.5f,
		0.f,
		0.f
	};

	u16 code = 999;

	EXPECT_TRUE(
		TriContainPoint(
			&f.triangle,
			position,
			code,
			f.vertices));

	EXPECT_EQ(code, 0);
}

TEST(CalculateTriangle, TriContainPointReturnsTrueForVertex)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	const float position[] = {
		0.f,
		0.f,
		0.f
	};

	u16 code = 999;

	EXPECT_TRUE(
		TriContainPoint(
			&f.triangle,
			position,
			code,
			f.vertices));

	EXPECT_EQ(code, 0);
}

TEST(CalculateTriangle, TriContainPointReturnsFalseOutsideAcrossFirstEdge)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	// Outside across edge v0 -> v1.
	const float position[] = {
		0.5f,
		-0.25f,
		0.f
	};

	u16 code = 0;

	EXPECT_FALSE(
		TriContainPoint(
			&f.triangle,
			position,
			code,
			f.vertices));

	EXPECT_EQ(code, 1);
}

TEST(CalculateTriangle, TriContainPointReturnsFalseOutsideAcrossSecondEdge)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	// Outside across edge v1 -> v2.
	const float position[] = {
		0.75f,
		0.75f,
		0.f
	};

	u16 code = 0;

	EXPECT_FALSE(
		TriContainPoint(
			&f.triangle,
			position,
			code,
			f.vertices));

	EXPECT_EQ(code, 2);
}

TEST(CalculateTriangle, TriContainPointReturnsFalseOutsideAcrossThirdEdge)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	// Outside across edge v2 -> v0.
	const float position[] = {
		-0.25f,
		0.25f,
		0.f
	};

	u16 code = 0;

	EXPECT_FALSE(
		TriContainPoint(
			&f.triangle,
			position,
			code,
			f.vertices));

	EXPECT_EQ(code, 3);
}


// -----------------------------------------------------------------------------
// DistToFragmenton
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, DistToFragmentonProjectsOntoSegment)
{
	const dReal point[] = {
		0.5f,
		1.f,
		0.f
	};

	const dReal pt1[] = {
		0.f,
		0.f,
		0.f
	};

	const dReal pt2[] = {
		1.f,
		0.f,
		0.f
	};

	dReal closest[3];
	dReal direction[3];
	u16 code = 999;

	const float distance = DistToFragmenton(
		point,
		pt1,
		pt2,
		closest,
		direction,
		code);

	EXPECT_NEAR(distance, 1.f, g_EPS);
	EXPECT_EQ(code, 0);

	expect_vector3_near(closest, 0.5f, 0.f, 0.f);
	expect_vector3_near(direction, 0.f, -1.f, 0.f);
}

TEST(CalculateTriangle, DistToFragmentonClampsToFirstEndpoint)
{
	const dReal point[] = {
		-1.f,
		0.f,
		0.f
	};

	const dReal pt1[] = {
		0.f,
		0.f,
		0.f
	};

	const dReal pt2[] = {
		1.f,
		0.f,
		0.f
	};

	dReal closest[3];
	dReal direction[3];
	u16 code = 999;

	const float distance = DistToFragmenton(
		point,
		pt1,
		pt2,
		closest,
		direction,
		code);

	EXPECT_NEAR(distance, 1.f, g_EPS);
	EXPECT_EQ(code, 1);

	expect_vector3_near(closest, 0.f, 0.f, 0.f);
	expect_vector3_near(direction, 1.f, 0.f, 0.f);
}

TEST(CalculateTriangle, DistToFragmentonClampsToSecondEndpoint)
{
	const dReal point[] = {
		2.f,
		0.f,
		0.f
	};

	const dReal pt1[] = {
		0.f,
		0.f,
		0.f
	};

	const dReal pt2[] = {
		1.f,
		0.f,
		0.f
	};

	dReal closest[3];
	dReal direction[3];
	u16 code = 999;

	const float distance = DistToFragmenton(
		point,
		pt1,
		pt2,
		closest,
		direction,
		code);

	EXPECT_NEAR(distance, 1.f, g_EPS);
	EXPECT_EQ(code, 2);

	expect_vector3_near(closest, 1.f, 0.f, 0.f);
	expect_vector3_near(direction, -1.f, 0.f, 0.f);
}


// -----------------------------------------------------------------------------
// DistToTri - point on/in triangle
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, DistToTriReturnsPlaneForPointInsideTriangle)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	const float position[] = {
		0.25f,
		0.25f,
		0.f
	};

	float direction[3];
	float closest[3];
	ETriDist classification = tdBehind;

	const float distance = DistToTri(
		&f.triangle,
		position,
		direction,
		closest,
		classification,
		f.vertices);

	EXPECT_NEAR(distance, 0.f, g_EPS);
	EXPECT_EQ(classification, tdPlane);

	// Projection onto the triangle plane is the point itself.
	expect_vector3_near(closest, 0.25f, 0.25f, 0.f);

	// Direction is the inverse triangle normal.
	expect_vector3_near(direction, 0.f, 0.f, -1.f);
}

TEST(CalculateTriangle, DistToTriReturnsPlaneForPointAboveTriangle)
{
	TriangleFixture f;

	const float position[] = {
		0.25f,
		0.25f,
		2.f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	float direction[3];
	float closest[3];
	ETriDist classification = tdBehind;

	const float distance = DistToTri(
		&f.triangle,
		position,
		direction,
		closest,
		classification,
		f.vertices);

	EXPECT_NEAR(distance, 2.f, g_EPS);
	EXPECT_EQ(classification, tdPlane);

	expect_vector3_near(closest, 0.25f, 0.25f, 0.f);
	expect_vector3_near(direction, 0.f, 0.f, -1.f);
}


// -----------------------------------------------------------------------------
// DistToTri - point outside triangle but on its plane
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, DistToTriReturnsSideForPointOutsideAcrossEdge)
{
	TriangleFixture f;

	const float position[] = {
		0.5f,
		-1.f,
		0.f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	float direction[3];
	float closest[3];
	ETriDist classification = tdBehind;

	const float distance = DistToTri(
		&f.triangle,
		position,
		direction,
		closest,
		classification,
		f.vertices);

	EXPECT_NEAR(distance, 1.f, g_EPS);
	EXPECT_EQ(classification, tdSide);

	expect_vector3_near(closest, 0.5f, 0.f, 0.f);
	expect_vector3_near(direction, 0.f, 1.f, 0.f);
}

TEST(CalculateTriangle, DistToTriReturnsSideForPointOutsideAcrossHypotenuse)
{
	TriangleFixture f;

	const float position[] = {
		0.75f,
		0.75f,
		0.f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	float direction[3];
	float closest[3];
	ETriDist classification = tdBehind;

	const float distance = DistToTri(
		&f.triangle,
		position,
		direction,
		closest,
		classification,
		f.vertices);

	// Closest point on x + y = 1.
	const float expected = (0.75f + 0.75f - 1.f) / 2.f;

	EXPECT_NEAR(distance, std::sqrt(0.125f), g_EPS);
	EXPECT_EQ(classification, tdSide);

	EXPECT_NEAR(closest[0], 0.5f, g_EPS);
	EXPECT_NEAR(closest[1], 0.5f, g_EPS);
	EXPECT_NEAR(closest[2], 0.f, g_EPS);

	EXPECT_NEAR(direction[0], -0.70710678f, g_EPS);
	EXPECT_NEAR(direction[1], -0.70710678f, g_EPS);
	EXPECT_NEAR(direction[2], 0.f, g_EPS);
}


// -----------------------------------------------------------------------------
// DistToTri - point behind the triangle plane
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, DistToTriReturnsBehindForPointBehindPlane)
{
	TriangleFixture f;

	const float position[] = {
		0.25f,
		0.25f,
		-1.f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	float direction[3] = {};
	float closest[3] = {};
	ETriDist classification = tdPlane;

	const float distance = DistToTri(
		&f.triangle,
		position,
		direction,
		closest,
		classification,
		f.vertices);

	EXPECT_EQ(distance, -1.f);
	EXPECT_EQ(classification, tdBehind);
}


// -----------------------------------------------------------------------------
// Vertex distance
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, DistToTriFindsDistanceToVertex)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	// Outside near v0.
	const float position[] = {
		-1.f,
		-1.f,
		0.f
	};

	float direction[3] = {};
	float closest[3] = {};

	ETriDist classification = tdBehind;

	const float distance = DistToTri(
		&f.triangle,
		position,
		direction,
		closest,
		classification,
		f.vertices);

	EXPECT_NEAR(distance, std::sqrt(2.f), g_EPS);

	expect_vector3_near(closest, 0.f, 0.f, 0.f);

	EXPECT_NEAR(direction[0], 0.70710678f, g_EPS);
	EXPECT_NEAR(direction[1], 0.70710678f, g_EPS);
	EXPECT_NEAR(direction[2], 0.f, g_EPS);

	// Intended semantic classification.
	EXPECT_EQ(classification, tdVert);
}


// -----------------------------------------------------------------------------
// Stability / invariants
// -----------------------------------------------------------------------------

TEST(CalculateTriangle, NormalIsUnitLength)
{
	TriangleFixture f;

	CalculateInitTriangle(&f.tri, f.triangle, f.vertices);

	const float lengthSquared =
		dDOT(f.triangle.norm, f.triangle.norm);

	EXPECT_NEAR(lengthSquared, 1.f, g_EPS);
}

TEST(CalculateTriangle, PlaneDistanceMatchesDotProduct)
{
	TriangleFixture f;

	const float position[] = {
		0.2f,
		0.3f,
		4.5f
	};

	CalculateTriangle(
		&f.tri,
		position,
		f.triangle,
		f.vertices);

	const float expected =
		dDOT(position, f.triangle.norm) - f.triangle.pos;

	EXPECT_NEAR(f.triangle.dist, expected, g_EPS);
}
