#include "../xrCore/xrCore.h"
#include "../xrPhysics.h"
#include "../xrCDB/xrCDB.h"
#include "dTriBox.h"

#include <gtest/gtest.h>

namespace
{
constexpr dReal Eps = 1e-5f;

struct BoxFixture
{
	dWorldID world = nullptr;
	dSpaceID space = nullptr;
	dxGeom* box = nullptr;

	BoxFixture()
	{
		world = dWorldCreate();
		space = dHashSpaceCreate(nullptr);

		box = static_cast<dxGeom*>(
			dCreateBox(space, 2.0, 4.0, 6.0)
		);
	}

	~BoxFixture()
	{
		if (space)
			dSpaceDestroy(space);

		if (world)
			dWorldDestroy(world);
	}

	BoxFixture(const BoxFixture&) = delete;
	BoxFixture& operator=(const BoxFixture&) = delete;
};

void ExpectVec3Near(
	const dReal* actual,
	dReal x,
	dReal y,
	dReal z,
	dReal eps = Eps)
{
	EXPECT_NEAR(actual[0], x, eps);
	EXPECT_NEAR(actual[1], y, eps);
	EXPECT_NEAR(actual[2], z, eps);
}

void ExpectUnitVector(const dReal* v, dReal eps = Eps)
{
	const dReal length =
		std::sqrt(
			v[0] * v[0] +
			v[1] * v[1] +
			v[2] * v[2]);

	EXPECT_NEAR(length, 1.0f, eps);
}

CDB::TRI MakeTriangle(
	const dVector3& v0,
	const dVector3& v1,
	const dVector3& v2)
{
	CDB::TRI tri{};

	// Adapt this if your CDB::TRI representation differs.
	tri.side0[0] = v1[0] - v0[0];
	tri.side0[1] = v1[1] - v0[1];
	tri.side0[2] = v1[2] - v0[2];

	tri.side1[0] = v2[0] - v1[0];
	tri.side1[1] = v2[1] - v1[1];
	tri.side1[2] = v2[2] - v1[2];

	return tri;
}

TEST(NormalizeIfPossible, NormalizesNonZeroVector)
{
	dVector3 v = {3.0f, 4.0f, 0.0f};

	ASSERT_TRUE(normalize_if_possible(v));

	EXPECT_NEAR(v[0], 0.6f, Eps);
	EXPECT_NEAR(v[1], 0.8f, Eps);
	EXPECT_NEAR(v[2], 0.0f, Eps);
	EXPECT_NEAR(dDOT(v, v), 1.0f, Eps);
}

TEST(NormalizeIfPossible, HandlesNegativeComponents)
{
	dVector3 v = {-2.0f, 3.0f, -6.0f};

	ASSERT_TRUE(normalize_if_possible(v));

	EXPECT_NEAR(dDOT(v, v), 1.0f, Eps);
}

TEST(NormalizeIfPossible, RejectsZeroVector)
{
	dVector3 v = {0.0f, 0.0f, 0.0f};

	EXPECT_FALSE(normalize_if_possible(v));

	ExpectVec3Near(v, 0.0f, 0.0f, 0.0f);
}

TEST(NormalizeIfPossible, RejectsVerySmallVector)
{
	dVector3 v = {EPS_S * 0.1f, 0.0f, 0.0f};

	EXPECT_FALSE(normalize_if_possible(v));
}

TEST(IsPtInBx, PointAtCenterIsInside)
{
	const dVector3 point = {0.0f, 0.0f, 0.0f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	EXPECT_TRUE(
		dcTriListCollider::IsPtInBx(
			point,
			boxPos,
			boxExtents,
			identity));
}

TEST(IsPtInBx, PointInsideIsAccepted)
{
	const dVector3 point = {0.5f, 1.0f, 2.0f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	EXPECT_TRUE(
		dcTriListCollider::IsPtInBx(
			point,
			boxPos,
			boxExtents,
			identity));
}

TEST(IsPtInBx, PointOutsideXIsRejected)
{
	const dVector3 point = {1.01f, 0.0f, 0.0f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	EXPECT_FALSE(
		dcTriListCollider::IsPtInBx(
			point,
			boxPos,
			boxExtents,
			identity));
}

TEST(IsPtInBx, PointOutsideYIsRejected)
{
	const dVector3 point = {0.0f, 2.01f, 0.0f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0
	};

	EXPECT_FALSE(
		dcTriListCollider::IsPtInBx(
			point,
			boxPos,
			boxExtents,
			identity));
}

TEST(IsPtInBx, PointOutsideZIsRejected)
{
	const dVector3 point = {0.0f, 0.0f, 3.01f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	EXPECT_FALSE(
		dcTriListCollider::IsPtInBx(
			point,
			boxPos,
			boxExtents,
			identity));
}

TEST(IsPtInBx, BoundaryIsOutside)
{
	const dVector3 point = {1.0f, 0.0f, 0.0f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	EXPECT_FALSE(
		dcTriListCollider::IsPtInBx(
			point,
			boxPos,
			boxExtents,
			identity));
}

TEST(PointBoxTest, PointInsideReturnsPositiveDepth)
{
	const dVector3 point = {0.0f, 0.0f, 0.0f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	dVector3 normal{};

	const dReal depth =
		PointBoxTest(
			point,
			boxPos,
			boxExtents,
			identity,
			normal);

	EXPECT_GT(depth, 0.0f);
	EXPECT_NEAR(depth, 1.0f, Eps);
}

TEST(PointBoxTest, PointOutsideReturnsNegative)
{
	const dVector3 point = {2.0f, 0.0f, 0.0f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	dVector3 normal{};

	EXPECT_LT(
		PointBoxTest(
			point,
			boxPos,
			boxExtents,
			identity,
			normal),
		0.0f);
}

TEST(PointBoxTest, ChoosesSmallestPenetrationAxis)
{
	const dVector3 point = {0.5f, 1.5f, 0.5f};
	const dVector3 boxPos = {0.0f, 0.0f, 0.0f};
	const dVector3 boxExtents = {2.0f, 4.0f, 6.0f};

	const dMatrix3 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};

	dVector3 normal{};

	const dReal depth =
		PointBoxTest(
			point,
			boxPos,
			boxExtents,
			identity,
			normal);

	EXPECT_NEAR(depth, 0.5f, Eps);

	ExpectVec3Near(normal, -0.5f, 0.0f, 0.0f);
}

TEST(CrossProjLine, FindsClosestPoint)
{
	const dVector3 pt1 = {0.0f, 0.0f, 0.0f};
	const dVector3 vc1 = {1.0f, 0.0f, 0.0f};

	const dVector3 pt2 = {0.0f, 1.0f, 0.0f};
	const dVector3 vc2 = {0.0f, 1.0f, 0.0f};

	dVector3 proj{};

	dcTriListCollider::CrossProjLine(
		pt1,
		vc1,
		pt2,
		vc2,
		proj);

	EXPECT_NEAR(proj[0], 0.0f, Eps);
	EXPECT_NEAR(proj[1], 0.0f, Eps);
	EXPECT_NEAR(proj[2], 0.0f, Eps);
}

TEST(CrossProjLine, ParallelLinesReturnInfinity)
{
	const dVector3 pt1 = {0.0f, 0.0f, 0.0f};
	const dVector3 vc1 = {1.0f, 0.0f, 0.0f};

	const dVector3 pt2 = {0.0f, 1.0f, 0.0f};
	const dVector3 vc2 = {1.0f, 0.0f, 0.0f};

	dVector3 proj{};

	dcTriListCollider::CrossProjLine(
		pt1,
		vc1,
		pt2,
		vc2,
		proj);

	EXPECT_EQ(proj[0], dInfinity);
}

TEST(CrossProjLine14, FindsIntersectionInsideBothConstraints)
{
	const dVector3 pt1 = {0.0f, 0.0f, 0.0f};
	const dVector3 vc1 = {1.0f, 0.0f, 0.0f};

	const dVector3 pt2 = {0.5f, -1.0f, 0.0f};
	const dVector3 vc2 = {0.0f, 1.0f, 0.0f};

	dVector3 proj{};

	ASSERT_TRUE(
		dcTriListCollider::CrossProjLine14(
			pt1,
			vc1,
			pt2,
			vc2,
			1.0f,
			proj));

	ExpectVec3Near(proj, 0.5f, 0.0f, 0.0f);
}

TEST(CrossProjLine14, RejectsIntersectionPastFirstSegment)
{
	const dVector3 pt1 = {0.0f, 0.0f, 0.0f};
	const dVector3 vc1 = {1.0f, 0.0f, 0.0f};

	const dVector3 pt2 = {2.0f, -1.0f, 0.0f};
	const dVector3 vc2 = {0.0f, 1.0f, 0.0f};

	dVector3 proj{};

	EXPECT_FALSE(
		dcTriListCollider::CrossProjLine14(
			pt1,
			vc1,
			pt2,
			vc2,
			1.0f,
			proj));
}

TEST(CrossProjLine14, RejectsIntersectionOutsideSecondExtent)
{
	const dVector3 pt1 = {0.0f, 0.0f, 0.0f};
	const dVector3 vc1 = {1.0f, 0.0f, 0.0f};

	const dVector3 pt2 = {0.5f, -2.0f, 0.0f};
	const dVector3 vc2 = {0.0f, 1.0f, 0.0f};

	dVector3 proj{};

	EXPECT_FALSE(
		dcTriListCollider::CrossProjLine14(
			pt1,
			vc1,
			pt2,
			vc2,
			1.0f,
			proj));
}

TEST(CrossProjLine14, ParallelLinesAreRejected)
{
	const dVector3 pt1 = {0.0f, 0.0f, 0.0f};
	const dVector3 vc1 = {1.0f, 0.0f, 0.0f};

	const dVector3 pt2 = {0.0f, 1.0f, 0.0f};
	const dVector3 vc2 = {1.0f, 0.0f, 0.0f};

	dVector3 proj{};

	EXPECT_FALSE(
		dcTriListCollider::CrossProjLine14(
			pt1,
			vc1,
			pt2,
			vc2,
			1.0f,
			proj));
}

TEST(DBoxProj, IdentityRotationUsesHalfExtents)
{
	BoxFixture fixture;

	dGeomBoxSetLengths(fixture.box, 2.0, 4.0, 6.0);
	dGeomSetPosition(fixture.box, 0.0, 0.0, 0.0);

	const dVector3 normal = {1.0f, 0.0f, 0.0f};

	const dReal projection =
		dcTriListCollider::dBoxProj(
			fixture.box,
			normal);

	EXPECT_NEAR(projection, 1.0f, Eps);
}

TEST(DBoxProj, DiagonalNormal)
{
	BoxFixture fixture;

	const dVector3 normal = {
		1.0f / std::sqrt(3.0f),
		1.0f / std::sqrt(3.0f),
		1.0f / std::sqrt(3.0f)
	};

	const dReal projection =
		dcTriListCollider::dBoxProj(
			fixture.box,
			normal);

	const dReal expected =
		(1.0f + 2.0f + 3.0f) / std::sqrt(3.0f);

	EXPECT_NEAR(projection, expected, Eps);
}

TEST(DBoxProj, RotationChangesProjection)
{
	BoxFixture fixture;

	const dReal angle = dM_PI / 2.0f;

	dMatrix3 rotation{};
	dRFromAxisAndAngle(
		rotation,
		0.0f,
		0.0f,
		1.0f,
		angle);

	dGeomSetRotation(fixture.box, rotation);

	const dVector3 normal = {1.0f, 0.0f, 0.0f};

	const dReal projection =
		dcTriListCollider::dBoxProj(
			fixture.box,
			normal);

	// After a 90-degree Z rotation, world X corresponds to
	// the original local Y axis.
	EXPECT_NEAR(projection, 2.0f, Eps);
}

class TriBoxTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		world = dWorldCreate();
		space = dHashSpaceCreate(nullptr);

		box = dCreateBox(
			space,
			2.0,
			2.0,
			2.0);

		dGeomSetPosition(box, 0.0, 0.0, 0.0);
	}

	void TearDown() override
	{
		dSpaceDestroy(space);
		dWorldDestroy(world);
	}

	dWorldID world{};
	dSpaceID space{};
	dxGeom* box{};
};

TEST_F(TriBoxTest, SeparatedTriangleDoesNotCollide)
{
	// Triangle completely outside the box.

	const dVector3 v0 = {5.0f, 0.0f, 0.0f};
	const dVector3 v1 = {5.0f, 1.0f, 0.0f};
	const dVector3 v2 = {5.0f, 0.0f, 1.0f};

	// Build your actual Triangle here.

	dContactGeom contacts[3]{};

	const int result =
		dcTriListCollider::dTriBox(
			v0,
			v1,
			v2,
			&triangle,
			nullptr,
			box,
			NUMC_MASK,
			contacts,
			sizeof(dContactGeom));

	EXPECT_EQ(result, 0);
}

#if 0
TEST(TriBoxRegression, GoldenCases)
{
	for (const auto& test : GoldenCases)
	{
		const auto actual = RunTriBox(test.input);

		EXPECT_EQ(actual.count, test.expected.count);

		for (int i = 0; i < actual.count; ++i)
		{
			EXPECT_NEAR(
				actual.contacts[i].depth,
				test.expected.contacts[i].depth,
				1e-5);

			EXPECT_NEAR(
				actual.contacts[i].normal.x,
				test.expected.contacts[i].normal.x,
				1e-5);

			EXPECT_NEAR(
				actual.contacts[i].normal.y,
				test.expected.contacts[i].normal.y,
				1e-5);

			EXPECT_NEAR(
				actual.contacts[i].normal.z,
				test.expected.contacts[i].normal.z,
				1e-5);

			EXPECT_NEAR(
				actual.contacts[i].position.x,
				test.expected.contacts[i].position.x,
				1e-5);

			EXPECT_NEAR(
				actual.contacts[i].position.y,
				test.expected[i].position.y,
				1e-5);

			EXPECT_NEAR(
				actual.contacts[i].position.z,
				test.expected[i].position.z,
				1e-5);
		}
	}
}
#endif

} // namespace
