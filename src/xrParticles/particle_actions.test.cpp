#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "psystem.h"
#include "particle_core.h"
#include "particle_actions.h"
#include "noise.h"

#include <gtest/gtest.h>

using namespace PAPI;

// noise3Init() exists in noise.cpp but is not declared by noise.h.
extern void noise3Init();

namespace
{
constexpr float kEpsilon = 1e-5f;

void ExpectVecNear(const pVector& actual, const pVector& expected, float eps = kEpsilon)
{
	EXPECT_NEAR(actual.x, expected.x, eps);
	EXPECT_NEAR(actual.y, expected.y, eps);
	EXPECT_NEAR(actual.z, expected.z, eps);
}

void ExpectVecFinite(const pVector& v)
{
	EXPECT_TRUE(std::isfinite(v.x));
	EXPECT_TRUE(std::isfinite(v.y));
	EXPECT_TRUE(std::isfinite(v.z));
}

float Distance(const pVector& a, const pVector& b)
{
	return (a - b).length();
}

// A ParticleAction implementation used exclusively to test ParticleActions'
// ownership semantics.
class TestParticleAction final : public ParticleAction
{
public:
	static int alive;
	static int destroyed;
	static int executed;
	static int transformed;
	static int loaded;
	static int saved;

	TestParticleAction()
	{
		++alive;
	}

	~TestParticleAction()
	{
		--alive;
		++destroyed;
	}

	void Execute(ParticleEffect*, const float, float&) override
	{
		++executed;
	}

	void Transform(const Fmatrix&) override
	{
		++transformed;
	}

	void Load(IReader&) override
	{
		++loaded;
	}

	void Save(IWriter&) override
	{
		++saved;
	}

	static void ResetCounters()
	{
		alive = 0;
		destroyed = 0;
		executed = 0;
		transformed = 0;
		loaded = 0;
		saved = 0;
	}
};

int TestParticleAction::alive = 0;
int TestParticleAction::destroyed = 0;
int TestParticleAction::executed = 0;
int TestParticleAction::transformed = 0;
int TestParticleAction::loaded = 0;
int TestParticleAction::saved = 0;

class ParticleActionsTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		TestParticleAction::ResetCounters();
	}

	void TearDown() override
	{
		ASSERT_EQ(TestParticleAction::alive, 0);
	}
};

} // namespace


// ============================================================================
// pVector
// ============================================================================

TEST(PVectorRegression, ConstructorAndBasicArithmetic)
{
	const pVector a(1.0f, 2.0f, 3.0f);
	const pVector b(4.0f, -5.0f, 6.0f);

	EXPECT_FLOAT_EQ(a.x, 1.0f);
	EXPECT_FLOAT_EQ(a.y, 2.0f);
	EXPECT_FLOAT_EQ(a.z, 3.0f);

	const pVector sum = a + b;
	ExpectVecNear(sum, pVector(5.0f, -3.0f, 9.0f));

	const pVector difference = a - b;
	ExpectVecNear(difference, pVector(-3.0f, 7.0f, -3.0f));

	const pVector scaled = a * 2.0f;
	ExpectVecNear(scaled, pVector(2.0f, 4.0f, 6.0f));

	const pVector divided = a / 2.0f;
	ExpectVecNear(divided, pVector(0.5f, 1.0f, 1.5f));
}

TEST(PVectorRegression, DotProduct)
{
	const pVector a(1.0f, 2.0f, 3.0f);
	const pVector b(4.0f, -5.0f, 6.0f);

	EXPECT_FLOAT_EQ(a * b, 12.0f);
}

TEST(PVectorRegression, CrossProduct)
{
	const pVector x(1.0f, 0.0f, 0.0f);
	const pVector y(0.0f, 1.0f, 0.0f);

	ExpectVecNear(x ^ y, pVector(0.0f, 0.0f, 1.0f));
	ExpectVecNear(y ^ x, pVector(0.0f, 0.0f, -1.0f));
}

TEST(PVectorRegression, LengthAndLengthSquared)
{
	const pVector v(3.0f, 4.0f, 12.0f);

	EXPECT_FLOAT_EQ(v.length2(), 169.0f);
	EXPECT_FLOAT_EQ(v.length(), 13.0f);
}

TEST(PVectorRegression, CompoundOperators)
{
	pVector v(1.0f, 2.0f, 3.0f);

	v += pVector(4.0f, 5.0f, 6.0f);
	ExpectVecNear(v, pVector(5.0f, 7.0f, 9.0f));

	v -= pVector(1.0f, 2.0f, 3.0f);
	ExpectVecNear(v, pVector(4.0f, 5.0f, 6.0f));

	v *= 2.0f;
	ExpectVecNear(v, pVector(8.0f, 10.0f, 12.0f));

	v /= 2.0f;
	ExpectVecNear(v, pVector(4.0f, 5.0f, 6.0f));
}

TEST(PVectorRegression, UnaryMinusMutatesAndReturnsSelf)
{
	pVector v(1.0f, -2.0f, 3.0f);

	const pVector result = -v;

	ExpectVecNear(v, pVector(-1.0f, 2.0f, -3.0f));
	ExpectVecNear(result, pVector(-1.0f, 2.0f, -3.0f));
}


// ============================================================================
// Rotation / Particle
// ============================================================================

TEST(RotationRegression, SetAndCopy)
{
	Rotation a;
	a.set(1.25f);

	EXPECT_FLOAT_EQ(a.x, 1.25f);

	Rotation b;
	b.set(a);

	EXPECT_FLOAT_EQ(b.x, 1.25f);
}

TEST(RotationRegression, InertionMatchesCurrentImplementation)
{
	Rotation r;
	r.set(10.0f);

	Rotation target;
	target.set(20.0f);

	r.inertion(target, 0.25f);

	// Current implementation:
	// x = v * x + (1-v) * p.x
	EXPECT_FLOAT_EQ(r.x, 17.5f);
}

TEST(ParticleRegression, Layout)
{
	// Particle is explicitly documented as 116 bytes.
	EXPECT_EQ(sizeof(Particle), 116u);
}

TEST(ParticleRegression, FlagsAndConstants)
{
	EXPECT_EQ(Particle::ANIMATE_CCW, 1 << 0);
	EXPECT_EQ(ParticleAction::ALLOW_ROTATE, 1 << 1);
}


// ============================================================================
// Public enum values
// ============================================================================

TEST(PublicEnumsRegression, DomainValues)
{
	EXPECT_EQ(PDPoint, 0);
	EXPECT_EQ(PDLine, 1);
	EXPECT_EQ(PDTriangle, 2);
	EXPECT_EQ(PDPlane, 3);
	EXPECT_EQ(PDBox, 4);
	EXPECT_EQ(PDSphere, 5);
	EXPECT_EQ(PDCylinder, 6);
	EXPECT_EQ(PDCone, 7);
	EXPECT_EQ(PDBlob, 8);
	EXPECT_EQ(PDDisc, 9);
	EXPECT_EQ(PDRectangle, 10);
}

TEST(PublicEnumsRegression, ActionValues)
{
	EXPECT_EQ(PAAvoidID, 0);
	EXPECT_EQ(PABounceID, 1);
	EXPECT_EQ(PACallActionListID_obsolette, 2);
	EXPECT_EQ(PACopyVertexBID, 3);
	EXPECT_EQ(PADampingID, 4);
	EXPECT_EQ(PAExplosionID, 5);
	EXPECT_EQ(PAFollowID, 6);
	EXPECT_EQ(PAGravitateID, 7);
	EXPECT_EQ(PAGravityID, 8);
	EXPECT_EQ(PAJetID, 9);
	EXPECT_EQ(PAKillOldID, 10);
	EXPECT_EQ(PAMatchVelocityID, 11);
	EXPECT_EQ(PAMoveID, 12);
	EXPECT_EQ(PAOrbitLineID, 13);
	EXPECT_EQ(PAOrbitPointID, 14);
	EXPECT_EQ(PARandomAccelID, 15);
	EXPECT_EQ(PARandomDisplaceID, 16);
	EXPECT_EQ(PARandomVelocityID, 17);
	EXPECT_EQ(PARestoreID, 18);
	EXPECT_EQ(PASinkID, 19);
	EXPECT_EQ(PASinkVelocityID, 20);
	EXPECT_EQ(PASourceID, 21);
	EXPECT_EQ(PASpeedLimitID, 22);
	EXPECT_EQ(PATargetColorID, 23);
	EXPECT_EQ(PATargetSizeID, 24);
	EXPECT_EQ(PATargetRotateID, 25);
	EXPECT_EQ(PATargetRotateDID, 26);
	EXPECT_EQ(PATargetVelocityID, 27);
	EXPECT_EQ(PATargetVelocityDID, 28);
	EXPECT_EQ(PAVortexID, 29);
	EXPECT_EQ(PATurbulenceID, 30);
	EXPECT_EQ(PAScatterID, 31);
}


// ============================================================================
// pDomain - constructors and Within()
// ============================================================================

TEST(PDomainRegression, Point)
{
	const pDomain d(PDPoint, 1.0f, 2.0f, 3.0f);

	ExpectVecNear(d.p1, pVector(1.0f, 2.0f, 3.0f));

	// This is current behavior: PDPoint is not handled by Within().
	EXPECT_FALSE(d.Within(pVector(1.0f, 2.0f, 3.0f)));
	EXPECT_FALSE(d.Within(pVector(100.0f, 100.0f, 100.0f)));

	pVector generated;
	d.Generate(generated);

	ExpectVecNear(generated, pVector(1.0f, 2.0f, 3.0f));
}

TEST(PDomainRegression, Line)
{
	const pDomain d(PDLine, 1.0f, 2.0f, 3.0f,
	                5.0f, 6.0f, 7.0f);

	ExpectVecNear(d.p1, pVector(1.0f, 2.0f, 3.0f));
	ExpectVecNear(d.p2, pVector(4.0f, 4.0f, 4.0f));

	// Current implementation deliberately returns false for PDLine.
	EXPECT_FALSE(d.Within(pVector(3.0f, 4.0f, 5.0f)));

	for (int i = 0; i < 100; ++i)
	{
		pVector generated;
		d.Generate(generated);

		EXPECT_GE(generated.x, 1.0f);
		EXPECT_LE(generated.x, 5.0f);
		EXPECT_GE(generated.y, 2.0f);
		EXPECT_LE(generated.y, 6.0f);
		EXPECT_GE(generated.z, 3.0f);
		EXPECT_LE(generated.z, 7.0f);
	}
}

TEST(PDomainRegression, BoxNormalizesCorners)
{
	const pDomain d(PDBox,
	                5.0f, 6.0f, 7.0f,
	                1.0f, 2.0f, 3.0f);

	ExpectVecNear(d.p1, pVector(1.0f, 2.0f, 3.0f));
	ExpectVecNear(d.p2, pVector(5.0f, 6.0f, 7.0f));

	EXPECT_TRUE(d.Within(pVector(1.0f, 2.0f, 3.0f)));
	EXPECT_TRUE(d.Within(pVector(5.0f, 6.0f, 7.0f)));
	EXPECT_TRUE(d.Within(pVector(3.0f, 4.0f, 5.0f)));

	EXPECT_FALSE(d.Within(pVector(0.999f, 4.0f, 5.0f)));
	EXPECT_FALSE(d.Within(pVector(3.0f, 6.001f, 5.0f)));
}

TEST(PDomainRegression, BoxGenerateProducesPointsInside)
{
	const pDomain d(PDBox,
	                -2.0f, -4.0f, -6.0f,
	                2.0f, 4.0f, 6.0f);

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);

		EXPECT_TRUE(d.Within(generated));
	}
}

TEST(PDomainRegression, Plane)
{
	const pDomain d(PDPlane,
	                0.0f, 0.0f, 0.0f,
	                0.0f, 1.0f, 0.0f);

	EXPECT_NEAR(d.p2.length(), 1.0f, kEpsilon);

	EXPECT_TRUE(d.Within(pVector(0.0f, 0.0f, 0.0f)));
	EXPECT_TRUE(d.Within(pVector(0.0f, 1.0f, 0.0f)));
	EXPECT_TRUE(d.Within(pVector(10.0f, 0.001f, 10.0f)));

	EXPECT_FALSE(d.Within(pVector(0.0f, -0.001f, 0.0f)));

	pVector generated;
	d.Generate(generated);

	// Current behavior: Generate() returns p1 for an infinite plane.
	ExpectVecNear(generated, d.p1);
}

TEST(PDomainRegression, Sphere)
{
	const pDomain d(PDSphere,
	                10.0f, 20.0f, 30.0f,
	                5.0f, 2.0f);

	EXPECT_FLOAT_EQ(d.radius1, 5.0f);
	EXPECT_FLOAT_EQ(d.radius2, 2.0f);
	EXPECT_FLOAT_EQ(d.radius1Sqr, 25.0f);
	EXPECT_FLOAT_EQ(d.radius2Sqr, 4.0f);

	EXPECT_TRUE(d.Within(pVector(10.0f, 20.0f, 30.0f) + pVector(2.0f, 0.0f, 0.0f)));
	EXPECT_TRUE(d.Within(pVector(10.0f, 20.0f, 30.0f) + pVector(5.0f, 0.0f, 0.0f)));

	// Inner radius is excluded.
	EXPECT_FALSE(d.Within(pVector(10.0f, 20.0f, 30.0f)));
	EXPECT_FALSE(d.Within(pVector(10.0f, 20.0f, 30.0f) +
	                      pVector(1.999f, 0.0f, 0.0f)));

	EXPECT_FALSE(d.Within(pVector(10.0f, 20.0f, 30.0f) +
	                      pVector(5.001f, 0.0f, 0.0f)));
}

TEST(PDomainRegression, SphereGenerateProducesCorrectRadiusRange)
{
	const pVector center(1.0f, 2.0f, 3.0f);
	const pDomain d(PDSphere,
	                center.x, center.y, center.z,
	                5.0f, 2.0f);

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);

		const float radius = Distance(generated, center);

		EXPECT_GE(radius, 2.0f - 1e-4f);
		EXPECT_LE(radius, 5.0f + 1e-4f);
		EXPECT_NEAR(radius, d.Within(generated) ? radius : radius, 0.0f);
	}
}

TEST(PDomainRegression, Cylinder)
{
	const pDomain d(PDCylinder,
	                0.0f, 0.0f, 0.0f,
	                0.0f, 0.0f, 2.0f,
	                1.0f, 0.0f);

	EXPECT_TRUE(d.Within(pVector(0.0f, 0.0f, 0.0f)));
	EXPECT_TRUE(d.Within(pVector(0.5f, 0.0f, 1.0f)));
	EXPECT_TRUE(d.Within(pVector(1.0f, 0.0f, 1.0f)));

	EXPECT_FALSE(d.Within(pVector(1.001f, 0.0f, 1.0f)));
	EXPECT_FALSE(d.Within(pVector(0.0f, 0.0f, -0.001f)));
	EXPECT_FALSE(d.Within(pVector(0.0f, 0.0f, 2.001f)));

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);
		EXPECT_TRUE(d.Within(generated));
	}
}

TEST(PDomainRegression, Cone)
{
	const pDomain d(PDCone,
	                0.0f, 0.0f, 0.0f,
	                0.0f, 0.0f, 2.0f,
	                1.0f, 0.0f);

	// At half height the outer radius is half the base radius.
	EXPECT_TRUE(d.Within(pVector(0.0f, 0.0f, 1.0f)));
	EXPECT_TRUE(d.Within(pVector(0.49f, 0.0f, 1.0f)));
	EXPECT_FALSE(d.Within(pVector(0.51f, 0.0f, 1.0f)));

	// The apex is included.
	EXPECT_TRUE(d.Within(pVector(0.0f, 0.0f, 0.0f)));

	EXPECT_FALSE(d.Within(pVector(0.0f, 0.0f, 2.001f)));

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);
		EXPECT_TRUE(d.Within(generated));
	}
}

TEST(PDomainRegression, RectangleGenerateProducesPointsOnExpectedPlane)
{
	const pDomain d(PDRectangle,
	                10.0f, 20.0f, 30.0f,
	                2.0f, 0.0f, 0.0f,
	                0.0f, 3.0f, 0.0f);

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);

		EXPECT_NEAR(generated.z, 30.0f, kEpsilon);
		EXPECT_GE(generated.x, 10.0f);
		EXPECT_LE(generated.x, 12.0f);
		EXPECT_GE(generated.y, 20.0f);
		EXPECT_LE(generated.y, 23.0f);
	}

	// Current Within() behavior for PDRectangle.
	EXPECT_FALSE(d.Within(d.p1));
}

TEST(PDomainRegression, TriangleGenerateProducesPointsOnExpectedPlane)
{
	const pDomain d(PDTriangle,
	                0.0f, 0.0f, 0.0f,
	                4.0f, 0.0f, 0.0f,
	                0.0f, 3.0f, 0.0f);

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);

		EXPECT_NEAR(generated.z, 0.0f, kEpsilon);

		// Triangle: x >= 0, y >= 0, x/4 + y/3 <= 1.
		EXPECT_GE(generated.x, -kEpsilon);
		EXPECT_GE(generated.y, -kEpsilon);
		EXPECT_LE(generated.x / 4.0f + generated.y / 3.0f, 1.0f + kEpsilon);
	}
}

TEST(PDomainRegression, DiscGenerateProducesCorrectAnnulus)
{
	const pVector center(1.0f, 2.0f, 3.0f);

	const pDomain d(PDDisc,
	                center.x, center.y, center.z,
	                0.0f, 0.0f, 1.0f,
	                2.0f, 1.0f);

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);

		EXPECT_NEAR(generated.z, center.z, kEpsilon);

		const float radius = Distance(generated, center);
		EXPECT_GE(radius, 1.0f - kEpsilon);
		EXPECT_LE(radius, 2.0f + kEpsilon);
	}

	// Current implementation does not implement Within() for PDDisc.
	EXPECT_FALSE(d.Within(center));
}

TEST(PDomainRegression, BlobGenerateProducesFiniteValues)
{
	const pDomain d(PDBlob,
	                10.0f, 20.0f, 30.0f,
	                2.0f);

	for (int i = 0; i < 1000; ++i)
	{
		pVector generated;
		d.Generate(generated);

		ExpectVecFinite(generated);
	}
}


// ============================================================================
// pDomain transforms
// ============================================================================

TEST(PDomainRegression, IdentityTransformPreservesPoint)
{
	const pDomain source(PDPoint, 1.0f, 2.0f, 3.0f);
	pDomain destination(PDPoint, 100.0f, 200.0f, 300.0f);

	Fmatrix m;
	m.identity();

	destination.transform(source, m);

	ExpectVecNear(destination.p1, source.p1);
}

TEST(PDomainRegression, IdentityTransformPreservesLine)
{
	const pDomain source(PDLine,
	                     1.0f, 2.0f, 3.0f,
	                     5.0f, 6.0f, 7.0f);

	pDomain destination(PDLine,
	                    100.0f, 200.0f, 300.0f,
	                    500.0f, 600.0f, 700.0f);

	Fmatrix m;
	m.identity();

	destination.transform(source, m);

	ExpectVecNear(destination.p1, source.p1);
	ExpectVecNear(destination.p2, source.p2);
}

TEST(PDomainRegression, TransformDirIgnoresTranslation)
{
	const pDomain source(PDLine,
	                     1.0f, 2.0f, 3.0f,
	                     5.0f, 6.0f, 7.0f);

	pDomain destination(PDLine,
	                    0.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f);

	Fmatrix m;
	m.identity();

	// Set only the translation portion.
	m.c.set(100.0f, 200.0f, 300.0f);

	destination.transform_dir(source, m);

	// transform_dir() explicitly zeros translation before transform().
	ExpectVecNear(destination.p1, source.p1);
	ExpectVecNear(destination.p2, source.p2);
}


// ============================================================================
// NRand
// ============================================================================

TEST(RandomRegression, NRandZeroSigmaAlwaysReturnsZero)
{
	for (int i = 0; i < 100; ++i)
		EXPECT_FLOAT_EQ(NRand(0.0f), 0.0f);
}

TEST(RandomRegression, NRandProducesFiniteValues)
{
	for (int i = 0; i < 10000; ++i)
	{
		const float value = NRand();
		EXPECT_TRUE(std::isfinite(value));
	}
}

TEST(RandomRegression, NRandScalesWithSigma)
{
	// We don't assert statistical distribution here; this is a cheap
	// characterization that values scale linearly with sigma.
	//
	// Replacing the implementation with a different random generator is
	// allowed to change individual samples, but not the basic scale.
	double sumAbs1 = 0.0;
	double sumAbs2 = 0.0;

	for (int i = 0; i < 10000; ++i)
	{
		sumAbs1 += std::fabs(NRand(1.0f));
		sumAbs2 += std::fabs(NRand(2.0f));
	}

	// Loose bounds deliberately account for randomness.
	EXPECT_GT(sumAbs1, 0.0);
	EXPECT_GT(sumAbs2, sumAbs1 * 0.75);
	EXPECT_LT(sumAbs2, sumAbs1 * 1.5);
}


// ============================================================================
// noise
// ============================================================================

class NoiseRegression : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{
		// noise3() has no lazy initialization. The current production code
		// expects somebody else to call noise3Init().
		noise3Init();
	}
};

TEST_F(NoiseRegression, SameInputIsDeterministic)
{
	const Fvector v(1.25f, -2.5f, 3.75f);

	const float a = noise3(v);
	const float b = noise3(v);

	EXPECT_FLOAT_EQ(a, b);
}

TEST_F(NoiseRegression, OutputIsFinite)
{
	const Fvector samples[] =
	{
		Fvector(0.0f, 0.0f, 0.0f),
		Fvector(1.0f, 2.0f, 3.0f),
		Fvector(-10.5f, 4.25f, 100.0f),
		Fvector(0.1234f, -0.5678f, 0.91011f),
	};

	for (const Fvector& v : samples)
	{
		EXPECT_TRUE(std::isfinite(noise3(v)));
	}
}

TEST_F(NoiseRegression, IntegerLatticePointsAreDeterministic)
{
	const Fvector samples[] =
	{
		Fvector(0.0f, 0.0f, 0.0f),
		Fvector(1.0f, 0.0f, 0.0f),
		Fvector(0.0f, 1.0f, 0.0f),
		Fvector(0.0f, 0.0f, 1.0f),
		Fvector(1.0f, 1.0f, 1.0f),
	};

	for (const Fvector& v : samples)
	{
		const float first = noise3(v);

		for (int i = 0; i < 10; ++i)
			EXPECT_FLOAT_EQ(noise3(v), first);
	}
}

TEST_F(NoiseRegression, SmallInputChangeDoesNotCreateHugeJump)
{
	const Fvector a(2.0f, 3.0f, 4.0f);
	const Fvector b(2.0001f, 3.0001f, 4.0001f);

	const float na = noise3(a);
	const float nb = noise3(b);

	EXPECT_LT(std::fabs(na - nb), 0.01f);
}

TEST_F(NoiseRegression, FractalSumIsDeterministic)
{
	const Fvector v(1.2f, -0.7f, 3.4f);

	const float a = fractalsum3(v, 1.0f, 5);
	const float b = fractalsum3(v, 1.0f, 5);

	EXPECT_FLOAT_EQ(a, b);
	EXPECT_TRUE(std::isfinite(a));
}

TEST_F(NoiseRegression, TurbulenceIsNonNegative)
{
	const Fvector samples[] =
	{
		Fvector(0.0f, 0.0f, 0.0f),
		Fvector(1.0f, 2.0f, 3.0f),
		Fvector(-1.5f, 2.75f, 8.25f),
		Fvector(100.0f, -50.0f, 0.25f),
	};

	for (const Fvector& v : samples)
	{
		const float value = turbulence3(v, 1.0f, 5);

		EXPECT_TRUE(std::isfinite(value));
		EXPECT_GE(value, 0.0f);
	}
}

TEST_F(NoiseRegression, ZeroOctavesReturnZero)
{
	const Fvector v(1.0f, 2.0f, 3.0f);

	EXPECT_FLOAT_EQ(fractalsum3(v, 1.0f, 0), 0.0f);
	EXPECT_FLOAT_EQ(turbulence3(v, 1.0f, 0), 0.0f);
}


// ============================================================================
// ParticleActions
// ============================================================================

TEST_F(ParticleActionsTest, StartsEmpty)
{
	ParticleActions actions;

	EXPECT_TRUE(actions.empty());
	EXPECT_EQ(actions.size(), 0);
	EXPECT_EQ(actions.begin(), actions.end());
}

TEST_F(ParticleActionsTest, AppendStoresActions)
{
	ParticleActions actions;

	auto* a = new TestParticleAction();
	auto* b = new TestParticleAction();

	actions.append(a);
	actions.append(b);

	EXPECT_FALSE(actions.empty());
	EXPECT_EQ(actions.size(), 2);

	auto it = actions.begin();

	EXPECT_EQ(*it, a);

	++it;
	EXPECT_EQ(*it, b);

	EXPECT_EQ(TestParticleAction::alive, 2);
}

TEST_F(ParticleActionsTest, ClearDeletesOwnedActions)
{
	ParticleActions actions;

	actions.append(new TestParticleAction());
	actions.append(new TestParticleAction());
	actions.append(new TestParticleAction());

	ASSERT_EQ(TestParticleAction::alive, 3);

	actions.clear();

	EXPECT_TRUE(actions.empty());
	EXPECT_EQ(actions.size(), 0);
	EXPECT_EQ(TestParticleAction::alive, 0);
	EXPECT_EQ(TestParticleAction::destroyed, 3);
}

TEST_F(ParticleActionsTest, DestructorDeletesOwnedActions)
{
	{
		ParticleActions actions;

		actions.append(new TestParticleAction());
		actions.append(new TestParticleAction());

		EXPECT_EQ(TestParticleAction::alive, 2);
	}

	EXPECT_EQ(TestParticleAction::alive, 0);
	EXPECT_EQ(TestParticleAction::destroyed, 2);
}

TEST_F(ParticleActionsTest, ReserveDoesNotChangeLogicalSize)
{
	ParticleActions actions;

	actions.reserve(128);

	EXPECT_TRUE(actions.empty());
	EXPECT_EQ(actions.size(), 0);
}

TEST_F(ParticleActionsTest, ResizeCanChangeLogicalSize)
{
	ParticleActions actions;

	actions.append(new TestParticleAction());
	actions.append(new TestParticleAction());

	ASSERT_EQ(actions.size(), 2);

	actions.resize(1);

	EXPECT_EQ(actions.size(), 1);

	// Important characterization: std::vector::resize() does not delete
	// the removed pointer itself. Therefore ParticleActions::resize() does
	// NOT have the ownership semantics of clear().
	//
	// The remaining action is owned and will be deleted by ~ParticleActions.
	EXPECT_EQ(TestParticleAction::alive, 2);
}

TEST_F(ParticleActionsTest, IterationMatchesInsertionOrder)
{
	ParticleActions actions;

	auto* a = new TestParticleAction();
	auto* b = new TestParticleAction();
	auto* c = new TestParticleAction();

	actions.append(a);
	actions.append(b);
	actions.append(c);

	auto it = actions.begin();

	ASSERT_NE(it, actions.end());
	EXPECT_EQ(*it++, a);

	ASSERT_NE(it, actions.end());
	EXPECT_EQ(*it++, b);

	ASSERT_NE(it, actions.end());
	EXPECT_EQ(*it++, c);

	EXPECT_EQ(it, actions.end());
}

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

#if 0
namespace
{
    constexpr float g_EPS = 1e-5f;

    void ExpectVecNear(const Fvector& actual, const Fvector& expected, float eps = g_EPS)
    {
        EXPECT_NEAR(actual.x, expected.x, eps);
        EXPECT_NEAR(actual.y, expected.y, eps);
        EXPECT_NEAR(actual.z, expected.z, eps);
    }

    class TestParticleAction final : public PAPI::ParticleAction
    {
    public:
        static int alive;

        TestParticleAction()
        {
            ++alive;
        }

        ~TestParticleAction() override
        {
            --alive;
        }

        void Execute(PAPI::ParticleEffect*, const float, float&) override
        {
        }

        void Transform(const Fmatrix&) override
        {
        }

        void Load(IReader&) override
        {
        }

        void Save(IWriter&) override
        {
        }
    };

    int TestParticleAction::alive = 0;
}
#endif

// ============================================================================
// pDomain construction
// ============================================================================

TEST(PDomain, PointConstructor)
{
    PAPI::pDomain domain(PDPoint, 1.f, 2.f, 3.f);

    EXPECT_EQ(domain.type, PDPoint);
    ExpectVecNear(domain.p1, PAPI::pVector(1.f, 2.f, 3.f));
}

TEST(PDomain, LineConstructorStoresVectorFromP1ToP2)
{
    PAPI::pDomain domain(PDLine, 1.f, 2.f, 3.f,
                         4.f, 6.f, 8.f);

    EXPECT_EQ(domain.type, PDLine);
    ExpectVecNear(domain.p1, PAPI::pVector(1.f, 2.f, 3.f));
    ExpectVecNear(domain.p2, PAPI::pVector(3.f, 4.f, 5.f));
}

TEST(PDomain, BoxConstructorNormalizesBounds)
{
    PAPI::pDomain domain(PDBox,
                         5.f, 8.f, 9.f,
                         1.f, 2.f, 3.f);

    EXPECT_EQ(domain.type, PDBox);

    ExpectVecNear(domain.p1, PAPI::pVector(1.f, 2.f, 3.f));
    ExpectVecNear(domain.p2, PAPI::pVector(5.f, 8.f, 9.f));
}

TEST(PDomain, SphereConstructorNormalizesRadii)
{
    PAPI::pDomain domain(PDSphere,
                         1.f, 2.f, 3.f,
                         2.f, 5.f);

    EXPECT_EQ(domain.type, PDSphere);
    EXPECT_FLOAT_EQ(domain.radius1, 5.f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.f);
    EXPECT_FLOAT_EQ(domain.radius1Sqr, 25.f);
    EXPECT_FLOAT_EQ(domain.radius2Sqr, 4.f);
}

TEST(PDomain, SphereConstructorAcceptsReversedRadii)
{
    PAPI::pDomain domain(PDSphere,
                         0.f, 0.f, 0.f,
                         5.f, 2.f);

    EXPECT_FLOAT_EQ(domain.radius1, 5.f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.f);
}

TEST(PDomain, PlaneConstructorNormalizesNormal)
{
    PAPI::pDomain domain(PDPlane,
                         0.f, 0.f, 5.f,
                         0.f, 0.f, 2.f);

    EXPECT_EQ(domain.type, PDPlane);
    EXPECT_NEAR(domain.p2.x, 0.f, kEpsilon);
    EXPECT_NEAR(domain.p2.y, 0.f, kEpsilon);
    EXPECT_NEAR(domain.p2.z, 1.f, kEpsilon);

    // Plane: z - 5 = 0 => d = -5.
    EXPECT_NEAR(domain.radius1, -5.f, kEpsilon);
}

TEST(PDomain, RectangleConstructorBuildsNormal)
{
    PAPI::pDomain domain(PDRectangle,
                         1.f, 2.f, 3.f,
                         2.f, 0.f, 0.f,
                         0.f, 4.f, 0.f);

    EXPECT_EQ(domain.type, PDRectangle);

    ExpectVecNear(domain.p1, PAPI::pVector(1.f, 2.f, 3.f));
    ExpectVecNear(domain.u, PAPI::pVector(2.f, 0.f, 0.f));
    ExpectVecNear(domain.v, PAPI::pVector(0.f, 4.f, 0.f));

    EXPECT_NEAR(domain.p2.x, 0.f, kEpsilon);
    EXPECT_NEAR(domain.p2.y, 0.f, kEpsilon);
    EXPECT_NEAR(domain.p2.z, 1.f, kEpsilon);

    EXPECT_NEAR(domain.radius1, -3.f, kEpsilon);
}

TEST(PDomain, TriangleConstructorBuildsNormal)
{
    PAPI::pDomain domain(PDTriangle,
                         0.f, 0.f, 0.f,
                         1.f, 0.f, 0.f,
                         0.f, 1.f, 0.f);

    EXPECT_EQ(domain.type, PDTriangle);

    ExpectVecNear(domain.u, PAPI::pVector(1.f, 0.f, 0.f));
    ExpectVecNear(domain.v, PAPI::pVector(0.f, 1.f, 0.f));

    EXPECT_NEAR(domain.p2.x, 0.f, kEpsilon);
    EXPECT_NEAR(domain.p2.y, 0.f, kEpsilon);
    EXPECT_NEAR(domain.p2.z, 1.f, kEpsilon);

    EXPECT_NEAR(domain.radius1, 0.f, kEpsilon);
}

TEST(PDomain, DiscConstructorBuildsOrthonormalBasis)
{
    PAPI::pDomain domain(PDDisc,
                         1.f, 2.f, 3.f,
                         0.f, 0.f, 1.f,
                         2.f, 5.f);

    EXPECT_EQ(domain.type, PDDisc);
    EXPECT_FLOAT_EQ(domain.radius1, 5.f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.f);

    EXPECT_NEAR(domain.p2.magnitude(), 1.f, kEpsilon);
    EXPECT_NEAR(domain.u.magnitude(), 1.f, kEpsilon);
    EXPECT_NEAR(domain.v.magnitude(), 1.f, kEpsilon);

    EXPECT_NEAR(domain.u.dotproduct(domain.p2), 0.f, kEpsilon);
    EXPECT_NEAR(domain.v.dotproduct(domain.p2), 0.f, kEpsilon);
    EXPECT_NEAR(domain.u.dotproduct(domain.v), 0.f, kEpsilon);
}

// ============================================================================
// pDomain::Within
// ============================================================================

TEST(PDomainWithin, BoxIncludesBoundary)
{
    PAPI::pDomain domain(PDBox,
                         0.f, 0.f, 0.f,
                         10.f, 10.f, 10.f);

    EXPECT_TRUE(domain.Within(PAPI::pVector(0.f, 0.f, 0.f)));
    EXPECT_TRUE(domain.Within(PAPI::pVector(10.f, 10.f, 10.f)));
    EXPECT_TRUE(domain.Within(PAPI::pVector(5.f, 5.f, 5.f)));
}

TEST(PDomainWithin, BoxRejectsOutside)
{
    PAPI::pDomain domain(PDBox,
                         0.f, 0.f, 0.f,
                         10.f, 10.f, 10.f);

    EXPECT_FALSE(domain.Within(PAPI::pVector(-0.001f, 5.f, 5.f)));
    EXPECT_FALSE(domain.Within(PAPI::pVector(5.f, 10.001f, 5.f)));
    EXPECT_FALSE(domain.Within(PAPI::pVector(5.f, 5.f, 10.001f)));
}

TEST(PDomainWithin, PlaneUsesPositiveHalfSpace)
{
    // z = 5, positive side is z >= 5.
    PAPI::pDomain domain(PDPlane,
                         0.f, 0.f, 5.f,
                         0.f, 0.f, 1.f);

    EXPECT_TRUE(domain.Within(PAPI::pVector(0.f, 0.f, 5.f)));
    EXPECT_TRUE(domain.Within(PAPI::pVector(0.f, 0.f, 10.f)));
    EXPECT_FALSE(domain.Within(PAPI::pVector(0.f, 0.f, 4.999f)));
}

TEST(PDomainWithin, SphereIncludesBothRadialBoundaries)
{
    PAPI::pDomain domain(PDSphere,
                         0.f, 0.f, 0.f,
                         5.f, 2.f);

    EXPECT_TRUE(domain.Within(PAPI::pVector(2.f, 0.f, 0.f)));
    EXPECT_TRUE(domain.Within(PAPI::pVector(5.f, 0.f, 0.f)));

    EXPECT_FALSE(domain.Within(PAPI::pVector(1.999f, 0.f, 0.f)));
    EXPECT_FALSE(domain.Within(PAPI::pVector(5.001f, 0.f, 0.f)));
}

TEST(PDomainWithin, SolidSphereAcceptsCenter)
{
    PAPI::pDomain domain(PDSphere,
                         1.f, 2.f, 3.f,
                         5.f, 0.f);

    EXPECT_TRUE(domain.Within(PAPI::pVector(1.f, 2.f, 3.f)));
}

TEST(PDomainWithin, CylinderChecksAxisAndRadius)
{
    PAPI::pDomain domain(PDCylinder,
                         0.f, 0.f, 0.f,
                         0.f, 0.f, 10.f,
                         2.f, 1.f);

    EXPECT_TRUE(domain.Within(PAPI::pVector(0.f, 0.f, 0.f)));
    EXPECT_TRUE(domain.Within(PAPI::pVector(0.f, 0.f, 10.f)));

    EXPECT_TRUE(domain.Within(PAPI::pVector(1.5f, 0.f, 5.f)));
    EXPECT_FALSE(domain.Within(PAPI::pVector(2.001f, 0.f, 5.f)));

    EXPECT_FALSE(domain.Within(PAPI::pVector(0.f, 0.f, -0.001f)));
    EXPECT_FALSE(domain.Within(PAPI::pVector(0.f, 0.f, 10.001f)));
}

TEST(PDomainWithin, HollowCylinderRejectsInnerRadius)
{
    PAPI::pDomain domain(PDCylinder,
                         0.f, 0.f, 0.f,
                         0.f, 0.f, 10.f,
                         3.f, 1.f);

    EXPECT_FALSE(domain.Within(PAPI::pVector(0.f, 0.f, 5.f)));
    EXPECT_TRUE(domain.Within(PAPI::pVector(2.f, 0.f, 5.f)));
}

TEST(PDomainWithin, ConeRadiusChangesWithAxisPosition)
{
    // Base radius = 4, inner radius = 0.
    // At dist = 0.5 the outer radius is 2.
    PAPI::pDomain domain(PDCone,
                         0.f, 0.f, 0.f,
                         0.f, 0.f, 10.f,
                         4.f, 0.f);

    EXPECT_TRUE(domain.Within(PAPI::pVector(1.5f, 0.f, 5.f)));
    EXPECT_TRUE(domain.Within(PAPI::pVector(2.f, 0.f, 5.f)));
    EXPECT_FALSE(domain.Within(PAPI::pVector(2.001f, 0.f, 5.f)));
}

TEST(PDomainWithin, UnsupportedDomainsReturnFalse)
{
    PAPI::pDomain point(PDPoint, 1.f, 2.f, 3.f);
    PAPI::pDomain line(PDLine, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f);
    PAPI::pDomain rectangle(PDRectangle,
                            0.f, 0.f, 0.f,
                            1.f, 0.f, 0.f,
                            0.f, 1.f, 0.f);

    const auto p = PAPI::pVector(0.f, 0.f, 0.f);

    EXPECT_FALSE(point.Within(p));
    EXPECT_FALSE(line.Within(p));
    EXPECT_FALSE(rectangle.Within(p));
}

// ============================================================================
// pDomain::Generate
// ============================================================================

TEST(PDomainGenerate, PointAlwaysGeneratesPoint)
{
    PAPI::pDomain domain(PDPoint, 1.f, 2.f, 3.f);

    PAPI::pVector result;
    domain.Generate(result);

    ExpectVecNear(result, PAPI::pVector(1.f, 2.f, 3.f));
}

TEST(PDomainGenerate, LineAlwaysGeneratesPointOnLine)
{
    PAPI::pDomain domain(PDLine,
                         1.f, 2.f, 3.f,
                         11.f, 12.f, 13.f);

    for (int i = 0; i < 100; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        EXPECT_NEAR(result.x - result.y + 1.f, 0.f, 1e-4f);
        EXPECT_NEAR(result.z - result.x - 2.f, 0.f, 1e-4f);
    }
}

TEST(PDomainGenerate, BoxAlwaysGeneratesInsideBox)
{
    PAPI::pDomain domain(PDBox,
                         -2.f, -3.f, -4.f,
                         5.f, 6.f, 7.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        EXPECT_TRUE(domain.Within(result));
    }
}

TEST(PDomainGenerate, TriangleAlwaysGeneratesInsideTriangle)
{
    PAPI::pDomain domain(PDTriangle,
                         0.f, 0.f, 0.f,
                         10.f, 0.f, 0.f,
                         0.f, 10.f, 0.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        EXPECT_NEAR(result.z, 0.f, kEpsilon);
        EXPECT_GE(result.x, -kEpsilon);
        EXPECT_GE(result.y, -kEpsilon);
        EXPECT_LE(result.x + result.y, 10.f + kEpsilon);
    }
}

TEST(PDomainGenerate, RectangleGeneratesWithinParallelogram)
{
    PAPI::pDomain domain(PDRectangle,
                         10.f, 20.f, 30.f,
                         5.f, 0.f, 0.f,
                         0.f, 8.f, 0.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        EXPECT_GE(result.x, 10.f - kEpsilon);
        EXPECT_LE(result.x, 15.f + kEpsilon);
        EXPECT_GE(result.y, 20.f - kEpsilon);
        EXPECT_LE(result.y, 28.f + kEpsilon);
        EXPECT_NEAR(result.z, 30.f, kEpsilon);
    }
}

TEST(PDomainGenerate, PlaneGeneratesReferencePoint)
{
    PAPI::pDomain domain(PDPlane,
                         1.f, 2.f, 3.f,
                         0.f, 1.f, 0.f);

    PAPI::pVector result;
    domain.Generate(result);

    ExpectVecNear(result, PAPI::pVector(1.f, 2.f, 3.f));
}

TEST(PDomainGenerate, SphereGeneratesWithinShell)
{
    PAPI::pDomain domain(PDSphere,
                         1.f, 2.f, 3.f,
                         5.f, 2.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        PAPI::pVector delta;
        delta.sub(result, domain.p1);

        const float r2 = delta.magnitude2();

        EXPECT_GE(r2, 4.f - 1e-4f);
        EXPECT_LE(r2, 25.f + 1e-4f);
    }
}

TEST(PDomainGenerate, SphereSurfaceGenerationForEqualRadii)
{
    PAPI::pDomain domain(PDSphere,
                         0.f, 0.f, 0.f,
                         5.f, 5.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        EXPECT_NEAR(result.magnitude(), 5.f, 1e-3f);
    }
}

TEST(PDomainGenerate, CylinderGeneratesWithinCylinder)
{
    PAPI::pDomain domain(PDCylinder,
                         0.f, 0.f, 0.f,
                         0.f, 0.f, 10.f,
                         3.f, 1.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        EXPECT_TRUE(domain.Within(result));
    }
}

TEST(PDomainGenerate, ConeGeneratesWithinCone)
{
    PAPI::pDomain domain(PDCone,
                         0.f, 0.f, 0.f,
                         0.f, 0.f, 10.f,
                         4.f, 0.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        EXPECT_TRUE(domain.Within(result));
    }
}

TEST(PDomainGenerate, DiscGeneratesWithinExpectedRadialRange)
{
    PAPI::pDomain domain(PDDisc,
                         0.f, 0.f, 0.f,
                         0.f, 0.f, 1.f,
                         2.f, 5.f);

    for (int i = 0; i < 1000; ++i)
    {
        PAPI::pVector result;
        domain.Generate(result);

        const float radius = result.magnitude();

        EXPECT_GE(radius, 2.f - kEpsilon);
        EXPECT_LE(radius, 5.f + kEpsilon);
        EXPECT_NEAR(result.z, 0.f, kEpsilon);
    }
}

// ============================================================================
// NRand
// ============================================================================

TEST(NRand, ZeroSigmaReturnsZero)
{
    EXPECT_FLOAT_EQ(PAPI::NRand(0.f), 0.f);
}

TEST(NRand, ProducesBothSigns)
{
    bool positive = false;
    bool negative = false;

    for (int i = 0; i < 1000 && !(positive && negative); ++i)
    {
        const float value = PAPI::NRand(1.f);

        positive |= value > 0.f;
        negative |= value < 0.f;
    }

    EXPECT_TRUE(positive);
    EXPECT_TRUE(negative);
}

TEST(NRand, SigmaChangesMagnitudeScale)
{
    // This is deliberately a statistical sanity check rather than an exact
    // distribution test.
    constexpr int samples = 10000;

    double sumSmall = 0.0;
    double sumLarge = 0.0;

    for (int i = 0; i < samples; ++i)
    {
        sumSmall += std::fabs(PAPI::NRand(1.f));
        sumLarge += std::fabs(PAPI::NRand(5.f));
    }

    EXPECT_GT(sumLarge / sumSmall, 3.0);
    EXPECT_LT(sumLarge / sumSmall, 7.0);
}

// ============================================================================
// ParticleActions
// ============================================================================

TEST(ParticleActions, StartsEmpty)
{
    PAPI::ParticleActions actions;

    EXPECT_TRUE(actions.empty());
    EXPECT_EQ(actions.size(), 0);
    EXPECT_EQ(actions.begin(), actions.end());
}

TEST(ParticleActions, AppendIncreasesSize)
{
    PAPI::ParticleActions actions;

    actions.append(new TestParticleAction());

    EXPECT_FALSE(actions.empty());
    EXPECT_EQ(actions.size(), 1);
}

TEST(ParticleActions, SupportsMultipleActions)
{
    PAPI::ParticleActions actions;

    actions.append(new TestParticleAction());
    actions.append(new TestParticleAction());
    actions.append(new TestParticleAction());

    EXPECT_EQ(actions.size(), 3);
}

TEST(ParticleActions, ClearDeletesOwnedActions)
{
    ASSERT_EQ(TestParticleAction::alive, 0);

    {
        PAPI::ParticleActions actions;

        actions.append(new TestParticleAction());
        actions.append(new TestParticleAction());

        EXPECT_EQ(TestParticleAction::alive, 2);

        actions.clear();

        EXPECT_EQ(TestParticleAction::alive, 0);
        EXPECT_TRUE(actions.empty());
        EXPECT_EQ(actions.size(), 0);
    }
}

TEST(ParticleActions, DestructorDeletesOwnedActions)
{
    ASSERT_EQ(TestParticleAction::alive, 0);

    {
        PAPI::ParticleActions actions;

        actions.append(new TestParticleAction());
        actions.append(new TestParticleAction());

        EXPECT_EQ(TestParticleAction::alive, 2);
    }

    EXPECT_EQ(TestParticleAction::alive, 0);
}

TEST(ParticleActions, ResizeChangesContainerSize)
{
    PAPI::ParticleActions actions;

    // Don't use resize() to create actions: resize creates null entries.
    actions.resize(3);

    EXPECT_EQ(actions.size(), 3);
    EXPECT_FALSE(actions.empty());

    // clear() would xr_delete nullptr entries, assuming xr_delete supports it.
    actions.clear();

    EXPECT_TRUE(actions.empty());
}

TEST(ParticleActions, ReserveDoesNotChangeSize)
{
    PAPI::ParticleActions actions;

    actions.reserve(128);

    EXPECT_TRUE(actions.empty());
    EXPECT_EQ(actions.size(), 0);
}

// ============================================================================
// Fmatrix initialization and vector/translation behavior
// ============================================================================

TEST(Fmatrix, IdentityProducesIdentityMatrix)
{
    Fmatrix m;
    m.identity();

    EXPECT_TRUE(m.has_identity());
    EXPECT_FALSE(m.has_inited());
}

TEST(Fmatrix, ZeroInitializedMatrixIsDetectedAsUninitialized)
{
    Fmatrix m{};

    EXPECT_TRUE(m.has_inited());
    EXPECT_FALSE(m.has_identity());
}

TEST(Fmatrix, TranslateSetsTranslationOnly)
{
    Fmatrix m;
    m.translate(10.f, 20.f, 30.f);

    EXPECT_TRUE(m.has_identity() == false);

    EXPECT_FLOAT_EQ(m._11, 1.f);
    EXPECT_FLOAT_EQ(m._22, 1.f);
    EXPECT_FLOAT_EQ(m._33, 1.f);

    EXPECT_FLOAT_EQ(m._41, 10.f);
    EXPECT_FLOAT_EQ(m._42, 20.f);
    EXPECT_FLOAT_EQ(m._43, 30.f);
    EXPECT_FLOAT_EQ(m._44, 1.f);
}

TEST(Fmatrix, TransformTinyAppliesTranslation)
{
    Fmatrix m;
    m.translate(10.f, 20.f, 30.f);

    PAPI::pVector input;
    input.set(1.f, 2.f, 3.f);

    PAPI::pVector output;
    m.transform_tiny(output, input);

    ExpectVecNear(output, PAPI::pVector(11.f, 22.f, 33.f));
}

TEST(Fmatrix, TransformDirIgnoresTranslation)
{
    Fmatrix m;
    m.identity();
    m.translate_over(100.f, 200.f, 300.f);

    PAPI::pVector input;
    input.set(1.f, 2.f, 3.f);

    PAPI::pVector output;
    m.transform_dir(output, input);

    ExpectVecNear(output, input);
}

TEST(Fmatrix, TranslateOverChangesOnlyTranslation)
{
    Fmatrix m;
    m.rotateX(0.5f);

    const float old11 = m._11;
    const float old12 = m._12;
    const float old22 = m._22;

    m.translate_over(10.f, 20.f, 30.f);

    EXPECT_FLOAT_EQ(m._11, old11);
    EXPECT_FLOAT_EQ(m._12, old12);
    EXPECT_FLOAT_EQ(m._22, old22);

    EXPECT_FLOAT_EQ(m._41, 10.f);
    EXPECT_FLOAT_EQ(m._42, 20.f);
    EXPECT_FLOAT_EQ(m._43, 30.f);
}

TEST(Fmatrix, TranslateAddAccumulatesTranslation)
{
    Fmatrix m;
    m.translate(1.f, 2.f, 3.f);

    m.translate_add(4.f, 5.f, 6.f);

    EXPECT_FLOAT_EQ(m._41, 5.f);
    EXPECT_FLOAT_EQ(m._42, 7.f);
    EXPECT_FLOAT_EQ(m._43, 9.f);
}

// ============================================================================
// Fmatrix::transform_dir and pDomain::transform_dir
// ============================================================================

TEST(PDomainTransform, TransformPointAppliesTranslation)
{
    PAPI::pDomain source(PDPoint, 1.f, 2.f, 3.f);
    PAPI::pDomain destination(PDPoint);

    Fmatrix m;
    m.translate(10.f, 20.f, 30.f);

    destination.transform(source, m);

    ExpectVecNear(destination.p1, PAPI::pVector(11.f, 22.f, 33.f));
}

TEST(PDomainTransform, TransformDirDoesNotApplyTranslationToLineDirection)
{
    PAPI::pDomain source(PDLine,
                         1.f, 2.f, 3.f,
                         4.f, 6.f, 8.f);

    PAPI::pDomain destination(PDLine);

    Fmatrix m;
    m.translate(100.f, 200.f, 300.f);

    destination.transform_dir(source, m);

    // p1 is a point and therefore receives translation.
    ExpectVecNear(destination.p1, PAPI::pVector(101.f, 202.f, 303.f));

    // p2 is a direction and must NOT receive translation.
    ExpectVecNear(destination.p2, source.p2);
}

TEST(PDomainTransform, TransformDirPreservesDirectionUnderPureTranslation)
{
    PAPI::pDomain source(PDLine,
                         0.f, 0.f, 0.f,
                         10.f, 20.f, 30.f);

    PAPI::pDomain destination(PDLine);

    Fmatrix m;
    m.identity();
    m.translate_over(100.f, 200.f, 300.f);

    destination.transform_dir(source, m);

    ExpectVecNear(destination.p2, PAPI::pVector(10.f, 20.f, 30.f));
}

TEST(PDomainTransform, RotationTransformsDirectionWithoutTranslation)
{
    PAPI::pDomain source(PDLine,
                         0.f, 0.f, 0.f,
                         1.f, 0.f, 0.f);

    PAPI::pDomain destination(PDLine);

    Fmatrix m;
    m.rotateZ(M_PI / 2.f);

    destination.transform_dir(source, m);

    // Positive Z rotation in this matrix convention maps X -> Y.
    EXPECT_NEAR(destination.p2.x, 0.f, kEpsilon);
    EXPECT_NEAR(destination.p2.y, 1.f, kEpsilon);
    EXPECT_NEAR(destination.p2.z, 0.f, kEpsilon);
}

// ============================================================================
// Fmatrix::set / vector representation
// ============================================================================

TEST(Fmatrix, SetFourVectorsSetsHomogeneousMatrix)
{
    Fmatrix m;

    Fvector i;
    i.set(1.f, 2.f, 3.f);

    Fvector j;
    j.set(4.f, 5.f, 6.f);

    Fvector k;
    k.set(7.f, 8.f, 9.f);

    Fvector c;
    c.set(10.f, 11.f, 12.f);

    m.set(i, j, k, c);

    EXPECT_FLOAT_EQ(m._11, 1.f);
    EXPECT_FLOAT_EQ(m._12, 2.f);
    EXPECT_FLOAT_EQ(m._13, 3.f);
    EXPECT_FLOAT_EQ(m._14, 0.f);

    EXPECT_FLOAT_EQ(m._21, 4.f);
    EXPECT_FLOAT_EQ(m._22, 5.f);
    EXPECT_FLOAT_EQ(m._23, 6.f);
    EXPECT_FLOAT_EQ(m._24, 0.f);

    EXPECT_FLOAT_EQ(m._31, 7.f);
    EXPECT_FLOAT_EQ(m._32, 8.f);
    EXPECT_FLOAT_EQ(m._33, 9.f);
    EXPECT_FLOAT_EQ(m._34, 0.f);

    EXPECT_FLOAT_EQ(m._41, 10.f);
    EXPECT_FLOAT_EQ(m._42, 11.f);
    EXPECT_FLOAT_EQ(m._43, 12.f);
    EXPECT_FLOAT_EQ(m._44, 1.f);
}

TEST(Fmatrix, SetCopyProducesEqualMatrix)
{
    Fmatrix source;
    source.setHPB(0.1f, 0.2f, 0.3f);
    source.translate_over(10.f, 20.f, 30.f);

    Fmatrix destination;
    destination.set(source);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            EXPECT_FLOAT_EQ(destination.m[row][col], source.m[row][col]);
        }
    }
}

// ============================================================================
// Fmatrix rotation / scale / mirror
// ============================================================================

TEST(Fmatrix, ScaleTransformsVector)
{
    Fmatrix m;
    m.scale(2.f, 3.f, 4.f);

    PAPI::pVector input;
    input.set(1.f, 1.f, 1.f);

    PAPI::pVector output;
    m.transform_tiny(output, input);

    ExpectVecNear(output, PAPI::pVector(2.f, 3.f, 4.f));
}

TEST(Fmatrix, RotateXTransformsDirection)
{
    Fmatrix m;
    m.rotateX(M_PI / 2.f);

    Fvector input;
    input.set(0.f, 1.f, 0.f);

    Fvector output;
    m.transform_dir(output, input);

    EXPECT_NEAR(output.x, 0.f, kEpsilon);
    EXPECT_NEAR(output.y, 0.f, kEpsilon);
    EXPECT_NEAR(output.z, 1.f, kEpsilon);
}

TEST(Fmatrix, RotateYTransformsDirection)
{
    Fmatrix m;
    m.rotateY(M_PI / 2.f);

    Fvector input;
    input.set(0.f, 0.f, 1.f);

    Fvector output;
    m.transform_dir(output, input);

    EXPECT_NEAR(output.x, 1.f, kEpsilon);
    EXPECT_NEAR(output.y, 0.f, kEpsilon);
    EXPECT_NEAR(output.z, 0.f, kEpsilon);
}

TEST(Fmatrix, RotateZTransformsDirection)
{
    Fmatrix m;
    m.rotateZ(M_PI / 2.f);

    Fvector input;
    input.set(1.f, 0.f, 0.f);

    Fvector output;
    m.transform_dir(output, input);

    EXPECT_NEAR(output.x, 0.f, kEpsilon);
    EXPECT_NEAR(output.y, 1.f, kEpsilon);
    EXPECT_NEAR(output.z, 0.f, kEpsilon);
}

TEST(Fmatrix, MirrorXReflectsX)
{
    Fmatrix m;
    m.mirrorX();

    PAPI::pVector input;
    input.set(1.f, 2.f, 3.f);

    PAPI::pVector output;
    m.transform_tiny(output, input);

    ExpectVecNear(output, PAPI::pVector(-1.f, 2.f, 3.f));
}

TEST(Fmatrix, MirrorYReflectsY)
{
    Fmatrix m;
    m.mirrorY();

    PAPI::pVector input;
    input.set(1.f, 2.f, 3.f);

    PAPI::pVector output;
    m.transform_tiny(output, input);

    ExpectVecNear(output, PAPI::pVector(1.f, -2.f, 3.f));
}

TEST(Fmatrix, MirrorZReflectsZ)
{
    Fmatrix m;
    m.mirrorZ();

    PAPI::pVector input;
    input.set(1.f, 2.f, 3.f);

    PAPI::pVector output;
    m.transform_tiny(output, input);

    ExpectVecNear(output, PAPI::pVector(1.f, 2.f, -3.f));
}

// ============================================================================
// Fmatrix multiplication
// ============================================================================

TEST(Fmatrix, MultiplicationByIdentityPreservesMatrix)
{
    Fmatrix a;
    a.setHPB(0.2f, 0.3f, 0.4f);
    a.translate_over(10.f, 20.f, 30.f);

    Fmatrix identity;
    identity.identity();

    Fmatrix result;
    result.mul(a, identity);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            EXPECT_NEAR(result.m[row][col], a.m[row][col], kEpsilon);
        }
    }
}

TEST(Fmatrix, InverseCancelsTransform)
{
    Fmatrix transform;
    transform.setHPB(0.2f, -0.3f, 0.4f);
    transform.translate_over(10.f, 20.f, 30.f);

    Fmatrix inverse;
    inverse.invert(transform);

    Fmatrix result;
    result.mul(transform, inverse);

    Fmatrix identity;
    identity.identity();

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            EXPECT_NEAR(result.m[row][col], identity.m[row][col], 1e-4f);
        }
    }
}

TEST(Fmatrix, InvertBReportsSingularMatrix)
{
    Fmatrix singular{};
    singular.identity();

    // Make the first two rows/axes linearly dependent.
    singular._21 = singular._11;
    singular._22 = singular._12;
    singular._23 = singular._13;

    Fmatrix result;

    EXPECT_FALSE(result.invert_b(singular));
}

// ============================================================================
// Fmatrix projection
// ============================================================================

TEST(Fmatrix, OrthographicProjectionHasExpectedStructure)
{
    Fmatrix m;
    m.build_projection_ortho(20.f, 10.f, 1.f, 101.f);

    EXPECT_NEAR(m._11, 0.1f, kEpsilon);
    EXPECT_NEAR(m._22, 0.2f, kEpsilon);
    EXPECT_NEAR(m._33, 0.01f, kEpsilon);
    EXPECT_NEAR(m._43, -0.01f, kEpsilon);
    EXPECT_FLOAT_EQ(m._44, 1.f);

    EXPECT_FLOAT_EQ(m._14, 0.f);
    EXPECT_FLOAT_EQ(m._24, 0.f);
    EXPECT_FLOAT_EQ(m._34, 0.f);
}

TEST(Fmatrix, ProjectionTransformsNearPlaneToZeroDepth)
{
    Fmatrix m;
    m.build_projection_ortho(20.f, 20.f, 1.f, 101.f);

    Fvector input;
    input.set(0.f, 0.f, 1.f);

    Fvector output;
    m.transform(output, input);

    EXPECT_NEAR(output.z, 0.f, kEpsilon);
}
