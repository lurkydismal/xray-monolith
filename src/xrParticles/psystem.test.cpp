#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "psystem.h"

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

namespace
{

using namespace PAPI;

// -----------------------------------------------------------------------------
// pVector
// -----------------------------------------------------------------------------

TEST(PVectorTest, ConstructorSetsComponents)
{
    const pVector v(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(PVectorTest, Length2ReturnsSquaredLength)
{
    const pVector v(3.0f, 4.0f, 12.0f);

    EXPECT_FLOAT_EQ(v.length2(), 169.0f);
}

TEST(PVectorTest, LengthReturnsLength)
{
    const pVector v(3.0f, 4.0f, 0.0f);

    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(PVectorTest, DotProduct)
{
    const pVector a(1.0f, 2.0f, 3.0f);
    const pVector b(4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(a * b, 32.0f);
}

TEST(PVectorTest, ScalarMultiplication)
{
    const pVector v(1.0f, -2.0f, 3.0f);

    const pVector result = v * 2.5f;

    EXPECT_FLOAT_EQ(result.x, 2.5f);
    EXPECT_FLOAT_EQ(result.y, -5.0f);
    EXPECT_FLOAT_EQ(result.z, 7.5f);

    // Operator* is non-mutating.
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, -2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(PVectorTest, ScalarDivision)
{
    const pVector v(10.0f, -20.0f, 30.0f);

    const pVector result = v / 10.0f;

    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, -2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);

    // Operator/ is non-mutating.
    EXPECT_FLOAT_EQ(v.x, 10.0f);
    EXPECT_FLOAT_EQ(v.y, -20.0f);
    EXPECT_FLOAT_EQ(v.z, 30.0f);
}

TEST(PVectorTest, Addition)
{
    const pVector a(1.0f, 2.0f, 3.0f);
    const pVector b(4.0f, 5.0f, 6.0f);

    const pVector result = a + b;

    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST(PVectorTest, Subtraction)
{
    const pVector a(10.0f, 20.0f, 30.0f);
    const pVector b(4.0f, 5.0f, 6.0f);

    const pVector result = a - b;

    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 15.0f);
    EXPECT_FLOAT_EQ(result.z, 24.0f);
}

TEST(PVectorTest, UnaryMinusMutatesObject)
{
    pVector v(1.0f, -2.0f, 3.0f);

    const pVector& result = -v;

    // Important characterization:
    // operator-() changes the original vector and returns *this.
    EXPECT_FLOAT_EQ(v.x, -1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, -3.0f);

    EXPECT_EQ(&result, &v);
}

TEST(PVectorTest, PlusAssignmentMutatesObject)
{
    pVector v(1.0f, 2.0f, 3.0f);
    const pVector a(4.0f, 5.0f, 6.0f);

    pVector& result = (v += a);

    EXPECT_EQ(&result, &v);
    EXPECT_FLOAT_EQ(v.x, 5.0f);
    EXPECT_FLOAT_EQ(v.y, 7.0f);
    EXPECT_FLOAT_EQ(v.z, 9.0f);
}

TEST(PVectorTest, MinusAssignmentMutatesObject)
{
    pVector v(10.0f, 20.0f, 30.0f);
    const pVector a(4.0f, 5.0f, 6.0f);

    pVector& result = (v -= a);

    EXPECT_EQ(&result, &v);
    EXPECT_FLOAT_EQ(v.x, 6.0f);
    EXPECT_FLOAT_EQ(v.y, 15.0f);
    EXPECT_FLOAT_EQ(v.z, 24.0f);
}

TEST(PVectorTest, MultiplyAssignmentMutatesObject)
{
    pVector v(1.0f, -2.0f, 3.0f);

    pVector& result = (v *= 2.0f);

    EXPECT_EQ(&result, &v);
    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, -4.0f);
    EXPECT_FLOAT_EQ(v.z, 6.0f);
}

TEST(PVectorTest, DivideAssignmentMutatesObject)
{
    pVector v(10.0f, -20.0f, 30.0f);

    pVector& result = (v /= 10.0f);

    EXPECT_EQ(&result, &v);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, -2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(PVectorTest, CrossProduct)
{
    const pVector x(1.0f, 0.0f, 0.0f);
    const pVector y(0.0f, 1.0f, 0.0f);

    const pVector result = x ^ y;

    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 1.0f);
}

TEST(PVectorTest, CrossProductIsAntiCommutative)
{
    const pVector a(1.0f, 2.0f, 3.0f);
    const pVector b(4.0f, 5.0f, 6.0f);

    const pVector ab = a ^ b;
    const pVector ba = b ^ a;

    EXPECT_FLOAT_EQ(ab.x, -ba.x);
    EXPECT_FLOAT_EQ(ab.y, -ba.y);
    EXPECT_FLOAT_EQ(ab.z, -ba.z);
}

TEST(PVectorTest, AssignmentCopiesComponents)
{
    pVector a(1.0f, 2.0f, 3.0f);
    const pVector b(4.0f, 5.0f, 6.0f);

    pVector& result = (a = b);

    EXPECT_EQ(&result, &a);
    EXPECT_FLOAT_EQ(a.x, 4.0f);
    EXPECT_FLOAT_EQ(a.y, 5.0f);
    EXPECT_FLOAT_EQ(a.z, 6.0f);
}


// -----------------------------------------------------------------------------
// Rotation
// -----------------------------------------------------------------------------

TEST(RotationTest, SetFromFloat)
{
    Rotation rotation{};

    rotation.set(42.5f);

    EXPECT_FLOAT_EQ(rotation.x, 42.5f);
}

TEST(RotationTest, SetFromRotation)
{
    Rotation source{};
    source.x = 12.5f;

    Rotation destination{};
    destination.set(source);

    EXPECT_FLOAT_EQ(destination.x, 12.5f);
}

TEST(RotationTest, InertionUsesCurrentAndPreviousValues)
{
    Rotation current{};
    current.x = 10.0f;

    Rotation previous{};
    previous.x = 20.0f;

    current.inertion(previous, 0.25f);

    // Current implementation:
    // x = v * x + (1 - v) * p.x
    //
    // = 0.25 * 10 + 0.75 * 20
    // = 17.5
    EXPECT_FLOAT_EQ(current.x, 17.5f);
}

TEST(RotationTest, InertionWithZeroUsesOtherRotation)
{
    Rotation current{};
    current.x = 10.0f;

    Rotation other{};
    other.x = 20.0f;

    current.inertion(other, 0.0f);

    EXPECT_FLOAT_EQ(current.x, 20.0f);
}

TEST(RotationTest, InertionWithOneKeepsCurrentRotation)
{
    Rotation current{};
    current.x = 10.0f;

    Rotation other{};
    other.x = 20.0f;

    current.inertion(other, 1.0f);

    EXPECT_FLOAT_EQ(current.x, 10.0f);
}


// -----------------------------------------------------------------------------
// Particle layout / ABI
// -----------------------------------------------------------------------------

TEST(ParticleTest, SizeIs116Bytes)
{
    // The source explicitly documents this layout as 116 bytes.
    EXPECT_EQ(sizeof(Particle), 116u);
}

TEST(ParticleTest, RotationsComeFirst)
{
    EXPECT_EQ(offsetof(Particle, rot), 0u);
    EXPECT_EQ(offsetof(Particle, rotI), 4u);
}

TEST(ParticleTest, PositionFieldsHaveExpectedLayout)
{
    EXPECT_EQ(offsetof(Particle, pos), 8u);
    EXPECT_EQ(offsetof(Particle, posI), 20u);
    EXPECT_EQ(offsetof(Particle, posB), 32u);
}

TEST(ParticleTest, VelocityFieldsHaveExpectedLayout)
{
    EXPECT_EQ(offsetof(Particle, vel), 44u);
    EXPECT_EQ(offsetof(Particle, velI), 56u);
}

TEST(ParticleTest, SizeFieldsHaveExpectedLayout)
{
    EXPECT_EQ(offsetof(Particle, size), 68u);
    EXPECT_EQ(offsetof(Particle, sizeI), 80u);
}

TEST(ParticleTest, ColorFieldsHaveExpectedLayout)
{
    EXPECT_EQ(offsetof(Particle, colorR), 92u);
    EXPECT_EQ(offsetof(Particle, colorG), 96u);
    EXPECT_EQ(offsetof(Particle, colorB), 100u);
    EXPECT_EQ(offsetof(Particle, colorA), 104u);
}

TEST(ParticleTest, AgeFrameAndFlagsHaveExpectedLayout)
{
    EXPECT_EQ(offsetof(Particle, age), 108u);
    EXPECT_EQ(offsetof(Particle, frame), 112u);
    EXPECT_EQ(offsetof(Particle, flags), 114u);
}

TEST(ParticleTest, ParticleIsTriviallyCopyable)
{
    EXPECT_TRUE(std::is_trivially_copyable_v<Particle>);
}


// -----------------------------------------------------------------------------
// Constants / enum values
//
// These are particularly valuable when modernizing because enum reordering,
// changing underlying types, or changing constants can silently break
// serialized particle/action data.
// -----------------------------------------------------------------------------

TEST(PSystemConstantsTest, MaxFloatMatchesCurrentImplementation)
{
    EXPECT_FLOAT_EQ(P_MAXFLOAT, 1.0e16f);
}

TEST(PDomainEnumTest, ValuesAreStable)
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

TEST(PActionEnumTest, ValuesAreStable)
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

TEST(PDomainEnumTest, ForceDwordValueIsStable)
{
    EXPECT_EQ(
        static_cast<u32>(domain_enum_force_dword),
        0xffffffffu
    );
}

TEST(PActionEnumTest, ForceDwordValueIsStable)
{
    EXPECT_EQ(
        static_cast<u32>(action_enum_force_dword),
        0xffffffffu
    );
}


// -----------------------------------------------------------------------------
// Particle flags
// -----------------------------------------------------------------------------

TEST(ParticleTest, AnimateCCWFlagHasExpectedValue)
{
    EXPECT_EQ(Particle::ANIMATE_CCW, 1);
}


// -----------------------------------------------------------------------------
// Interface contract
//
// This verifies the API remains polymorphic and the important methods retain
// their expected virtual nature. It does not require the real implementation.
// -----------------------------------------------------------------------------

class FakeParticleManager final : public IParticleManager
{
public:
    int CreateEffect(u32) override
    {
        return 123;
    }

    void DestroyEffect(int) override
    {
    }

    int CreateActionList() override
    {
        return 456;
    }

    void DestroyActionList(int) override
    {
    }

    void PlayEffect(int, int) override
    {
    }

    void StopEffect(int, int, BOOL) override
    {
    }

    void Update(int, int, float) override
    {
    }

    void Transform(int, const Fmatrix&, const Fvector&) override
    {
    }

    void RemoveParticle(int, u32) override
    {
    }

    void SetMaxParticles(int, u32) override
    {
    }

    void SetCallback(
        int,
        OnBirthParticleCB,
        OnDeadParticleCB,
        void*,
        u32) override
    {
    }

    void GetParticles(int, Particle*& particles, u32& cnt) override
    {
        particles = nullptr;
        cnt = 0;
    }

    u32 GetParticlesCount(int) override
    {
        return 0;
    }

    ParticleAction* CreateAction(PActionEnum) override
    {
        return nullptr;
    }

    u32 LoadActions(int, IReader&) override
    {
        return 0;
    }

    void SaveActions(int, IWriter&) override
    {
    }
};

TEST(IParticleManagerTest, CanBeImplementedPolymorphically)
{
    FakeParticleManager manager;

    IParticleManager* interface = &manager;

    EXPECT_EQ(interface->CreateEffect(100), 123);
    EXPECT_EQ(interface->CreateActionList(), 456);
    EXPECT_EQ(interface->GetParticlesCount(0), 0u);
}

TEST(IParticleManagerTest, DestructorIsVirtual)
{
    EXPECT_TRUE(std::has_virtual_destructor_v<IParticleManager>);
}

} // namespace
