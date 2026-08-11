#include "../xrCore/xrCore.h"
#include "../xrCDB/xrCDB.h"
#include "../ode_include.h"
#include "../xrPhysics.h"
#include "dTriColliderMath.h"

#include <gtest/gtest.h>

namespace
{
constexpr dReal g_EPS = static_cast<dReal>(1e-5);

void ExpectVec3Near(const dReal* actual, const dReal* expected, dReal eps = g_EPS)
{
	EXPECT_NEAR(actual[0], expected[0], eps);
	EXPECT_NEAR(actual[1], expected[1], eps);
	EXPECT_NEAR(actual[2], expected[2], eps);
}

void ExpectUnitVector(const dReal* v, dReal eps = g_EPS)
{
	const dReal length = dSqrt(dDOT(v, v));
	EXPECT_NEAR(length, static_cast<dReal>(1), eps);
}
} // namespace

// ============================================================================
// TriContainPoint
// ============================================================================

class TriContainPointTest : public ::testing::Test
{
protected:
	// Counter-clockwise triangle in the XY plane.
	const dReal v0[3] = {0, 0, 0};
	const dReal v1[3] = {1, 0, 0};
	const dReal v2[3] = {0, 1, 0};
};

TEST_F(TriContainPointTest, InteriorPointIsContained)
{
	const dReal pos[] = {0.25, 0.25, 0};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, AnotherInteriorPointIsContained)
{
	const dReal pos[] = {0.1, 0.7, 0};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointOutsideAcrossFirstEdgeIsNotContained)
{
	const dReal pos[] = {-0.1, 0.2, 0};

	EXPECT_FALSE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointOutsideAcrossSecondEdgeIsNotContained)
{
	const dReal pos[] = {0.6, 0.6, 0};

	EXPECT_FALSE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointOutsideAcrossThirdEdgeIsNotContained)
{
	const dReal pos[] = {0.2, -0.1, 0};

	EXPECT_FALSE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, FirstVertexIsContained)
{
	EXPECT_TRUE(TriContainPoint(v0, v1, v2, v0));
}

TEST_F(TriContainPointTest, SecondVertexIsContained)
{
	EXPECT_TRUE(TriContainPoint(v0, v1, v2, v1));
}

TEST_F(TriContainPointTest, ThirdVertexIsContained)
{
	EXPECT_TRUE(TriContainPoint(v0, v1, v2, v2));
}

TEST_F(TriContainPointTest, PointOnFirstEdgeIsContained)
{
	const dReal pos[] = {0.5, 0, 0};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointOnSecondEdgeIsContained)
{
	const dReal pos[] = {0.5, 0.5, 0};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointOnThirdEdgeIsContained)
{
	const dReal pos[] = {0, 0.5, 0};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointAboveTrianglePlaneIsContained)
{
	const dReal pos[] = {0.25, 0.25, 10};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointBelowTrianglePlaneIsContained)
{
	const dReal pos[] = {0.25, 0.25, -10};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}

TEST_F(TriContainPointTest, PointFarOutsideInZIsStillContained)
{
	// TriContainPoint checks the triangle's projected side planes.
	// It does NOT check whether the point lies in the triangle's plane.
	const dReal pos[] = {0.25, 0.25, 1000};

	EXPECT_TRUE(TriContainPoint(v0, v1, v2, pos));
}


// ============================================================================
// TriContainPoint overload with explicit side axes
// ============================================================================

TEST_F(TriContainPointTest, ExplicitSideAxesProduceSameResult)
{
	const dReal side0[] = {
		v1[0] - v0[0],
		v1[1] - v0[1],
		v1[2] - v0[2]
	};

	const dReal side1[] = {
		v2[0] - v1[0],
		v2[1] - v1[1],
		v2[2] - v1[2]
	};

	const dReal side2[] = {
		v0[0] - v2[0],
		v0[1] - v2[1],
		v0[2] - v2[2]
	};

	const dReal triAx[] = {0, 0, 1};

	const dReal inside[] = {0.25, 0.25, 100};
	const dReal outside[] = {0.75, 0.75, 100};

	EXPECT_TRUE(TriContainPoint(
		v0, v1, v2,
		side0, side1, side2,
		triAx,
		inside));

	EXPECT_FALSE(TriContainPoint(
		v0, v1, v2,
		side0, side1, side2,
		triAx,
		outside));
}


// ============================================================================
// TriContainPoint overload with two explicit side axes
// ============================================================================

TEST_F(TriContainPointTest, TwoExplicitSideAxesProduceExpectedResult)
{
	const dReal side0[] = {
		v1[0] - v0[0],
		v1[1] - v0[1],
		v1[2] - v0[2]
	};

	const dReal side1[] = {
		v2[0] - v1[0],
		v2[1] - v1[1],
		v2[2] - v1[2]
	};

	const dReal triAx[] = {0, 0, 1};

	const dReal inside[] = {0.2, 0.3, 50};
	const dReal outside[] = {0.8, 0.8, -50};

	EXPECT_TRUE(TriContainPoint(
		v0, v1, v2,
		triAx,
		side0, side1,
		inside));

	EXPECT_FALSE(TriContainPoint(
		v0, v1, v2,
		triAx,
		side0, side1,
		outside));
}


// ============================================================================
// TriPlaneContainPoint
// ============================================================================

class TriPlaneContainPointTest : public ::testing::Test
{
protected:
	const dReal v0[3] = {0, 0, 0};
	const dReal v1[3] = {1, 0, 0};
	const dReal v2[3] = {0, 1, 0};
};

TEST_F(TriPlaneContainPointTest, PointInPositiveHalfSpaceReturnsTrue)
{
	const dReal pos[] = {0, 0, 1};

	EXPECT_TRUE(TriPlaneContainPoint(v0, v1, v2, pos));
}

TEST_F(TriPlaneContainPointTest, PointInNegativeHalfSpaceReturnsFalse)
{
	const dReal pos[] = {0, 0, -1};

	EXPECT_FALSE(TriPlaneContainPoint(v0, v1, v2, pos));
}

TEST_F(TriPlaneContainPointTest, PointOnPlaneReturnsFalse)
{
	const dReal pos[] = {0.5, 0.5, 0};

	// Current implementation uses:
	//
	//     difference > 0.f
	//
	// rather than >=.
	EXPECT_FALSE(TriPlaneContainPoint(v0, v1, v2, pos));
}

TEST_F(TriPlaneContainPointTest, PointExactlyAtVertexReturnsFalse)
{
	EXPECT_FALSE(TriPlaneContainPoint(v0, v1, v2, v0));
}

TEST_F(TriPlaneContainPointTest, ExplicitNormalPositiveSideReturnsTrue)
{
	const dReal triAx[] = {0, 0, 1};
	const dReal pos[] = {100, -100, 1};

	EXPECT_TRUE(TriPlaneContainPoint(triAx, v0, pos));
}

TEST_F(TriPlaneContainPointTest, ExplicitNormalNegativeSideReturnsFalse)
{
	const dReal triAx[] = {0, 0, 1};
	const dReal pos[] = {100, -100, -1};

	EXPECT_FALSE(TriPlaneContainPoint(triAx, v0, pos));
}

TEST_F(TriPlaneContainPointTest, ExplicitNormalOnPlaneReturnsFalse)
{
	const dReal triAx[] = {0, 0, 1};
	const dReal pos[] = {100, -100, 0};

	EXPECT_FALSE(TriPlaneContainPoint(triAx, v0, pos));
}


// ============================================================================
// PlanePoint
// ============================================================================

TEST(PlanePointTest, FindsIntersectionBetweenTwoPoints)
{
	Triangle tri{};
	tri.dist = -1.f;

	const dReal from[] = {0, 0, 1};
	const dReal to[] = {0, 0, -1};

	dReal point[3] = {};

	PlanePoint(
		tri,
		from,
		to,
		1.f,
		point);

	const dReal expected[] = {0, 0, 0};

	ExpectVec3Near(point, expected);
}

TEST(PlanePointTest, FindsIntersectionOnDiagonalSegment)
{
	Triangle tri{};
	tri.dist = -1.f;

	const dReal from[] = {1, 1, 1};
	const dReal to[] = {-1, -1, -1};

	dReal point[3] = {};

	PlanePoint(
		tri,
		from,
		to,
		1.f,
		point);

	const dReal expected[] = {0, 0, 0};

	ExpectVec3Near(point, expected);
}

TEST(PlanePointTest, PreservesIntersectionCoordinates)
{
	Triangle tri{};
	tri.dist = -2.f;

	const dReal from[] = {2, 4, 6};
	const dReal to[] = {0, 0, 0};

	dReal point[3] = {};

	PlanePoint(
		tri,
		from,
		to,
		2.f,
		point);

	const dReal expected[] = {1, 2, 3};

	ExpectVec3Near(point, expected);
}


// ============================================================================
// InitTriangle / CalculateTri
// ============================================================================
//
// These tests intentionally use the Point/Fvector overloads only if the
// project's Point/Fvector definitions are available through dTriColliderMath.h.
// ============================================================================

TEST(InitTriangleTest, CalculatesSideVectorsAndNormal)
{
	// This requires a CDB::TRI and Point representation from the X-Ray headers.
	// Keep the test here if those types are default-constructible in your tree.

	CDB::TRI tri{};
	Triangle triangle{};

	Point vertices[3] = {
		Point((dReal[3]){0, 0, 0}),
		Point((dReal[3]){1, 0, 0}),
		Point((dReal[3]){0, 1, 0})
	};

	InitTriangle(&tri, triangle, vertices);

	const dReal expectedSide0[] = {1, 0, 0};
	const dReal expectedSide1[] = {-1, 1, 0};
	const dReal expectedNormal[] = {0, 0, 1};

	ExpectVec3Near(triangle.side0, expectedSide0);
	ExpectVec3Near(triangle.side1, expectedSide1);
	ExpectVec3Near(triangle.norm, expectedNormal);

	EXPECT_NEAR(triangle.pos, 0, g_EPS);
	EXPECT_EQ(triangle.T, &tri);
	ExpectUnitVector(triangle.norm);
}
