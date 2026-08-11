#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "psystem.h"
#include "particle_effect.h"

#include <gtest/gtest.h>

namespace
{
	using PAPI::ParticleEffect;
	using PAPI::pVector;
	using PAPI::Particle;

	struct ParticleSnapshot
	{
		pVector pos;
		pVector posB;
		pVector size;
		pVector vel;

		float rotX;
		float colorA;
		float colorR;
		float colorG;
		float colorB;

		float age;
		u16 frame;
		u16 flags;
	};

	ParticleSnapshot snapshot(const Particle& p)
	{
		return {
			p.pos,
			p.posB,
			p.size,
			p.vel,
			p.rot.x,
			p.colorA,
			p.colorR,
			p.colorG,
			p.colorB,
			p.age,
			p.frame,
			p.flags.flags
		};
	}

	void expect_particle_eq(
		const ParticleSnapshot& expected,
		const Particle& actual)
	{
		EXPECT_EQ(actual.pos, expected.pos);
		EXPECT_EQ(actual.posB, expected.posB);
		EXPECT_EQ(actual.size, expected.size);
		EXPECT_EQ(actual.vel, expected.vel);

		EXPECT_FLOAT_EQ(actual.rot.x, expected.rotX);

		EXPECT_FLOAT_EQ(actual.colorA, expected.colorA);
		EXPECT_FLOAT_EQ(actual.colorR, expected.colorR);
		EXPECT_FLOAT_EQ(actual.colorG, expected.colorG);
		EXPECT_FLOAT_EQ(actual.colorB, expected.colorB);

		EXPECT_FLOAT_EQ(actual.age, expected.age);
		EXPECT_EQ(actual.frame, expected.frame);
		EXPECT_EQ(actual.flags, expected.flags);
	}
}

TEST(ParticleEffect, ConstructsEmptyEffect)
{
	PAPI::ParticleEffect effect(16);

	EXPECT_EQ(effect.p_count, 0u);
	EXPECT_EQ(effect.max_particles, 16u);
	EXPECT_EQ(effect.particles_allocated, 16u);

	ASSERT_NE(effect.particles, nullptr);

	EXPECT_EQ(effect.owner, nullptr);
	EXPECT_EQ(effect.param, 0u);
	EXPECT_EQ(effect.b_cb, nullptr);
	EXPECT_EQ(effect.d_cb, nullptr);
}

TEST(ParticleEffect, AddIncrementsParticleCount)
{
	PAPI::ParticleEffect effect(4);

	const pVector pos{};
	const pVector posB{};
	const pVector size{};
	const pVector rot{};
	const pVector vel{};

	EXPECT_TRUE(effect.Add(
		pos,
		posB,
		size,
		rot,
		vel,
		0xffffffff));

	EXPECT_EQ(effect.p_count, 1u);
}

TEST(ParticleEffect, AddStoresParticleData)
{
	PAPI::ParticleEffect effect(1);

	const pVector pos(1.f, 2.f, 3.f);
	const pVector posB(4.f, 5.f, 6.f);
	const pVector size(7.f, 8.f, 9.f);
	const pVector rot(10.f, 11.f, 12.f);
	const pVector vel(13.f, 14.f, 15.f);

	ASSERT_TRUE(effect.Add(
		pos,
		posB,
		size,
		rot,
		vel,
		0x11223344,
		42.5f,
		123,
		0x4567));

	ASSERT_EQ(effect.p_count, 1u);

	const Particle& p = effect.particles[0];

	EXPECT_EQ(p.pos, pos);
	EXPECT_EQ(p.posI, pos);

	EXPECT_EQ(p.posB, posB);

	EXPECT_EQ(p.size, size);
	EXPECT_EQ(p.sizeI, size);

	// This is deliberately only x: the current implementation only
	// initializes rot.x / rotI.x.
	EXPECT_FLOAT_EQ(p.rot.x, rot.x);
	EXPECT_FLOAT_EQ(p.rotI.x, rot.x);

	EXPECT_EQ(p.vel, vel);
	EXPECT_EQ(p.velI, vel);

	EXPECT_FLOAT_EQ(p.age, 42.5f);
	EXPECT_EQ(p.frame, 123);
	EXPECT_EQ(p.flags, 0x4567);
}

TEST(ParticleEffect, AddConvertsARGBColorToNormalizedComponents)
{
	PAPI::ParticleEffect effect(1);

	const pVector zero{};

	ASSERT_TRUE(effect.Add(
		zero,
		zero,
		zero,
		zero,
		zero,
		0x80402010));

	const Particle& p = effect.particles[0];

	EXPECT_FLOAT_EQ(p.colorA, 128.f / 255.f);
	EXPECT_FLOAT_EQ(p.colorR, 64.f / 255.f);
	EXPECT_FLOAT_EQ(p.colorG, 32.f / 255.f);
	EXPECT_FLOAT_EQ(p.colorB, 16.f / 255.f);
}

TEST(ParticleEffect, AddRejectsParticlesBeyondCapacity)
{
	PAPI::ParticleEffect effect(2);

	const pVector zero{};

	EXPECT_TRUE(effect.Add(
		zero, zero, zero, zero, zero, 0xffffffff));

	EXPECT_TRUE(effect.Add(
		zero, zero, zero, zero, zero, 0xffffffff));

	EXPECT_FALSE(effect.Add(
		zero, zero, zero, zero, zero, 0xffffffff));

	EXPECT_EQ(effect.p_count, 2u);
}

TEST(ParticleEffect, AddDoesNotIncrementCountWhenFull)
{
	PAPI::ParticleEffect effect(1);

	const pVector zero{};

	ASSERT_TRUE(effect.Add(
		zero, zero, zero, zero, zero, 0xffffffff));

	const ParticleSnapshot first = snapshot(effect.particles[0]);

	EXPECT_FALSE(effect.Add(
		zero, zero, zero, zero, zero, 0x12345678));

	EXPECT_EQ(effect.p_count, 1u);

	expect_particle_eq(first, effect.particles[0]);
}

TEST(ParticleEffect, RemoveDecrementsParticleCount)
{
	PAPI::ParticleEffect effect(4);

	const pVector zero{};

	ASSERT_TRUE(effect.Add(
		zero, zero, zero, zero, zero, 0xffffffff));

	ASSERT_TRUE(effect.Add(
		zero, zero, zero, zero, zero, 0xffffffff));

	EXPECT_EQ(effect.p_count, 2u);

	effect.Remove(0);

	EXPECT_EQ(effect.p_count, 1u);
}

TEST(ParticleEffect, RemoveMovesLastParticleIntoRemovedSlot)
{
	PAPI::ParticleEffect effect(4);

	const pVector zero{};

	const pVector firstPos(1.f, 2.f, 3.f);
	const pVector secondPos(4.f, 5.f, 6.f);

	ASSERT_TRUE(effect.Add(
		firstPos,
		zero,
		zero,
		zero,
		zero,
		0x11223344));

	ASSERT_TRUE(effect.Add(
		secondPos,
		zero,
		zero,
		zero,
		zero,
		0x55667788));

	ASSERT_EQ(effect.p_count, 2u);

	const ParticleSnapshot second = snapshot(effect.particles[1]);

	effect.Remove(0);

	ASSERT_EQ(effect.p_count, 1u);

	// Current implementation uses:
	//
	//     particles[i] = particles[--p_count];
	//
	// Therefore removing index 0 replaces it with the old last particle.
	expect_particle_eq(second, effect.particles[0]);
}

TEST(ParticleEffect, RemoveLastParticleDoesNotMoveAnything)
{
	PAPI::ParticleEffect effect(4);

	const pVector zero{};

	const pVector firstPos(1.f, 2.f, 3.f);
	const pVector secondPos(4.f, 5.f, 6.f);

	ASSERT_TRUE(effect.Add(
		firstPos,
		zero,
		zero,
		zero,
		zero,
		0x11223344));

	ASSERT_TRUE(effect.Add(
		secondPos,
		zero,
		zero,
		zero,
		zero,
		0x55667788));

	effect.Remove(1);

	ASSERT_EQ(effect.p_count, 1u);
	EXPECT_EQ(effect.particles[0].pos, firstPos);
}

TEST(ParticleEffect, RemoveEmptyEffectDoesNothing)
{
	PAPI::ParticleEffect effect(4);

	EXPECT_NO_FATAL_FAILURE(effect.Remove(0));
	EXPECT_EQ(effect.p_count, 0u);
}

TEST(ParticleEffect, ResizeGrowingPreservesParticles)
{
	PAPI::ParticleEffect effect(2);

	const pVector zero{};

	const pVector firstPos(1.f, 2.f, 3.f);
	const pVector secondPos(4.f, 5.f, 6.f);

	ASSERT_TRUE(effect.Add(
		firstPos,
		zero,
		zero,
		zero,
		zero,
		0x11223344));

	ASSERT_TRUE(effect.Add(
		secondPos,
		zero,
		zero,
		zero,
		zero,
		0x55667788));

	const ParticleSnapshot first = snapshot(effect.particles[0]);
	const ParticleSnapshot second = snapshot(effect.particles[1]);

	const int result = effect.Resize(8);

	EXPECT_EQ(result, 8);
	EXPECT_EQ(effect.max_particles, 8u);
	EXPECT_EQ(effect.particles_allocated, 8u);
	EXPECT_EQ(effect.p_count, 2u);

	expect_particle_eq(first, effect.particles[0]);
	expect_particle_eq(second, effect.particles[1]);

	EXPECT_TRUE(effect.Add(
		zero,
		zero,
		zero,
		zero,
		zero,
		0xffffffff));

	EXPECT_EQ(effect.p_count, 3u);
}

TEST(ParticleEffect, ResizeShrinkingChangesMaximum)
{
	PAPI::ParticleEffect effect(8);

	EXPECT_EQ(effect.Resize(4), 4);

	EXPECT_EQ(effect.max_particles, 4u);

	// Current implementation does not shrink the allocation.
	EXPECT_EQ(effect.particles_allocated, 8u);
}

TEST(ParticleEffect, ResizeShrinkingBelowParticleCountTruncatesParticleCount)
{
	PAPI::ParticleEffect effect(8);

	const pVector zero{};

	for (int i = 0; i < 6; ++i)
	{
		ASSERT_TRUE(effect.Add(
			zero,
			zero,
			zero,
			zero,
			zero,
			0xffffffff));
	}

	ASSERT_EQ(effect.p_count, 6u);

	EXPECT_EQ(effect.Resize(3), 3);

	EXPECT_EQ(effect.max_particles, 3u);
	EXPECT_EQ(effect.p_count, 3u);

	// Allocation is retained.
	EXPECT_EQ(effect.particles_allocated, 8u);
}

TEST(ParticleEffect, ResizeToCurrentAllocationDoesNotReallocate)
{
	PAPI::ParticleEffect effect(8);

	Particle* original = effect.particles;

	EXPECT_EQ(effect.Resize(4), 4);

	EXPECT_EQ(effect.particles, original);
	EXPECT_EQ(effect.particles_allocated, 8u);
	EXPECT_EQ(effect.max_particles, 4u);
}

TEST(ParticleEffect, ResizeGrowingReallocates)
{
	PAPI::ParticleEffect effect(4);

	Particle* original = effect.particles;

	EXPECT_EQ(effect.Resize(8), 8);

	EXPECT_NE(effect.particles, original);
	EXPECT_EQ(effect.particles_allocated, 8u);
	EXPECT_EQ(effect.max_particles, 8u);
}

TEST(ParticleEffect, ResizeToZero)
{
	PAPI::ParticleEffect effect(4);

	const pVector zero{};

	ASSERT_TRUE(effect.Add(
		zero,
		zero,
		zero,
		zero,
		zero,
		0xffffffff));

	EXPECT_EQ(effect.Resize(0), 0);

	EXPECT_EQ(effect.max_particles, 0u);
	EXPECT_EQ(effect.p_count, 0u);
	EXPECT_EQ(effect.particles_allocated, 4u);

	EXPECT_FALSE(effect.Add(
		zero,
		zero,
		zero,
		zero,
		zero,
		0xffffffff));
}
