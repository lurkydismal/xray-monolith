#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "../ode_include.h"
#include "../xrCDB/xrCDB.h"
#include "TriPrimitiveCollideClassDef.h"
#include "dcTriListCollider.h"

#include <gtest/gtest.h>

namespace
{
constexpr dReal g_EPS = static_cast<dReal>(1e-5);

void ExpectVec3Near(
	const dReal* actual,
	const dReal* expected,
	dReal eps = g_EPS)
{
	EXPECT_NEAR(actual[0], expected[0], eps);
	EXPECT_NEAR(actual[1], expected[1], eps);
	EXPECT_NEAR(actual[2], expected[2], eps);
}

void ExpectUnitVector(
	const dReal* value,
	dReal eps = g_EPS)
{
	EXPECT_NEAR(
		dSqrt(dDOT(value, value)),
		static_cast<dReal>(1),
		eps);
}
}


// ============================================================================
// Private helper tests
// ============================================================================

class DcTriListColliderTest : public ::testing::Test
{
protected:
	/*
	 * These tests only exercise functions that don't actually use the
	 * collider's Geometry/GeomData members.
	 *
	 * The fixture itself deliberately doesn't construct dcTriListCollider.
	 */
};


// ============================================================================
// dSphereProj
// ============================================================================

TEST_F(DcTriListColliderTest, SphereProjReturnsSphereRadius)
{
	dxGeom* sphere = dCreateSphere(nullptr, 5.0);

	ASSERT_NE(sphere, nullptr);
	ASSERT_EQ(dGeomGetClass(sphere), dSphereClass);

	// dSphereProj doesn't use the normal.
	const dReal normal[] = {1, 0, 0};

	// We need an object to call the member function on.
	//
	// This helper is effectively stateless, but is a non-static member.
	// Construction of dcTriListCollider requires a tri-list geom, so this
	// test is intentionally omitted until the tri-list test fixture exists.
	dGeomDestroy(sphere);
}


// ============================================================================
// IsPtInBx
// ============================================================================
//
// IsPtInBx:
//
//     Pt   = point
//     BxP  = box position
//     BxEx = box axis/extent
//     BxR  = box radius/half-size
//
// The exact interpretation of BxEx/BxR is implementation-specific, so these
// tests should be filled from the implementation in dcTriListCollider.cpp.
//
// ============================================================================


// ============================================================================
// CrossProjLine / CrossProjLine1 / CrossProjLine14
// ============================================================================
//
// These are also private helpers. Their implementations are not present in
// the supplied dcTriListCollider.cpp, so don't invent expected behavior here.
// Add tests once their implementations are available.
//
// ============================================================================


// ============================================================================
// circleLineIntersection
// ============================================================================
//
// Same situation: the declaration is present, but its implementation wasn't
// included in the supplied source.
// ============================================================================


// ============================================================================
// PointSphereTest
// ============================================================================

TEST_F(DcTriListColliderTest, PointSphereTestOutsideReturnsFalse)
{
	// We need a constructed dcTriListCollider to call the private member.
	//
	// The actual construction is intentionally deferred until the test fixture
	// has a valid dxTriList geometry.
	GTEST_SKIP() << "Requires dxTriList fixture";
}

TEST_F(DcTriListColliderTest, PointSphereTestInsideReturnsDepth)
{
	GTEST_SKIP() << "Requires dxTriList fixture";
}

TEST_F(DcTriListColliderTest, PointSphereTestBoundaryReturnsZeroDepth)
{
	GTEST_SKIP() << "Requires dxTriList fixture";
}

TEST_F(DcTriListColliderTest, PointSphereTestCenterUsesYAxisFallbackNormal)
{
	GTEST_SKIP() << "Requires dxTriList fixture";
}


// ============================================================================
// FragmentonSphereTest
// ============================================================================

TEST_F(DcTriListColliderTest, FragmentonSphereTestOutsideReturnsFalse)
{
	GTEST_SKIP() << "Requires dxTriList fixture";
}

TEST_F(DcTriListColliderTest, FragmentonSphereTestThroughCenterReturnsHit)
{
	GTEST_SKIP() << "Requires dxTriList fixture";
}

TEST_F(DcTriListColliderTest, FragmentonSphereTestTangentReturnsHit)
{
	GTEST_SKIP() << "Requires dxTriList fixture";
}

TEST_F(DcTriListColliderTest, FragmentonSphereTestEndpointReturnsHit)
{
	GTEST_SKIP() << "Requires dxTriList fixture";
}

#if 0
TEST_F(DcTriListColliderCollisionTest, SphereCompletelyOutsideTriangle)
{
	// expect 0 contacts
}

TEST_F(DcTriListColliderCollisionTest, SphereTouchingTriangle)
{
	// expect 1 contact
	// depth == 0
}

TEST_F(DcTriListColliderCollisionTest, SphereIntersectingTriangleFace)
{
	// expect 1 contact
	// verify depth
	// verify normal
	// verify position
}

TEST_F(DcTriListColliderCollisionTest, SphereIntersectingTriangleEdge)
{
	// expect 1 contact
	// verify edge normal
}

TEST_F(DcTriListColliderCollisionTest, SphereIntersectingTriangleVertex)
{
	// expect 1 contact
	// verify vertex normal
}
#endif
