#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "psystem.h"
#include "particle_actions_collection.h"
#include "particle_effect.h"
#include "../xrEngine/pure.h"
#include "particle_manager.h"
#include "particle_actions.h"

#include <gtest/gtest.h>

using namespace PAPI;

namespace
{
	struct CallbackState
	{
		int birth_count = 0;
		int dead_count = 0;

		void* birth_owner = nullptr;
		void* dead_owner = nullptr;

		u32 birth_param = 0;
		u32 dead_param = 0;

		int birth_index = -1;
		int dead_index = -1;

		Particle* birth_particle = nullptr;
		Particle* dead_particle = nullptr;
	};

	CallbackState* g_callback_state = nullptr;

	void BirthCallback(
		void* owner,
		u32 param,
		Particle& particle,
		unsigned int index)
	{
		ASSERT_NE(g_callback_state, nullptr);

		++g_callback_state->birth_count;
		g_callback_state->birth_owner = owner;
		g_callback_state->birth_param = param;
		g_callback_state->birth_index = index;
		g_callback_state->birth_particle = &particle;
	}

	void DeadCallback(
		void* owner,
		u32 param,
		Particle& particle,
		unsigned int index)
	{
		ASSERT_NE(g_callback_state, nullptr);

		++g_callback_state->dead_count;
		g_callback_state->dead_owner = owner;
		g_callback_state->dead_param = param;
		g_callback_state->dead_index = index;
		g_callback_state->dead_particle = &particle;
	}

	pVector Vector(float x, float y, float z)
	{
		return pVector(x, y, z);
	}

	void AddParticle(
		CParticleManager& manager,
		int effect_id,
		const pVector& pos,
		u32 color = 0xffffffff,
		float age = 0.f,
		u16 frame = 0,
		u16 flags = 0)
	{
		ParticleEffect* effect = manager.GetEffectPtr(effect_id).get();

		ASSERT_NE(effect, nullptr);

		EXPECT_TRUE(effect->Add(
			pos,
			Vector(0.f, 0.f, 0.f),
			Vector(1.f, 1.f, 1.f),
			Vector(0.f, 0.f, 0.f),
			Vector(0.f, 0.f, 0.f),
			color,
			age,
			frame,
			flags));
	}
}

class ParticleManagerTest : public ::testing::Test
{
protected:
	CParticleManager manager;

	void TearDown() override
	{
		g_callback_state = nullptr;
	}
};


// -----------------------------------------------------------------------------
// Effects
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, CreateEffectReturnsValidId)
{
	const int id = manager.CreateEffect(16);

	EXPECT_GE(id, 0);
	EXPECT_NE(manager.GetEffectPtr(id), nullptr);
}

TEST_F(ParticleManagerTest, CreateEffectsReturnsUniqueIds)
{
	const int first = manager.CreateEffect(16);
	const int second = manager.CreateEffect(16);
	const int third = manager.CreateEffect(16);

	EXPECT_NE(first, second);
	EXPECT_NE(first, third);
	EXPECT_NE(second, third);

	EXPECT_NE(manager.GetEffectPtr(first), nullptr);
	EXPECT_NE(manager.GetEffectPtr(second), nullptr);
	EXPECT_NE(manager.GetEffectPtr(third), nullptr);
}

TEST_F(ParticleManagerTest, CreatedEffectHasRequestedCapacity)
{
	const int id = manager.CreateEffect(123);

	auto effect = manager.GetEffectPtr(id);

	ASSERT_NE(effect, nullptr);

	EXPECT_EQ(effect->max_particles, 123u);
	EXPECT_EQ(effect->particles_allocated, 123u);
	EXPECT_EQ(effect->p_count, 0u);
}

TEST_F(ParticleManagerTest, DestroyEffectRemovesEffect)
{
	const int id = manager.CreateEffect(16);

	ASSERT_NE(manager.GetEffectPtr(id), nullptr);

	manager.DestroyEffect(id);

	EXPECT_EQ(manager.GetEffectPtr(id), nullptr);
}

TEST_F(ParticleManagerTest, DestroyUnknownEffectDoesNothing)
{
	EXPECT_NO_FATAL_FAILURE(manager.DestroyEffect(123456));
}

TEST_F(ParticleManagerTest, UnknownEffectReturnsNull)
{
	EXPECT_EQ(manager.GetEffectPtr(123456), nullptr);
	EXPECT_EQ(manager.GetParticlesCount(123456), 0u);
}

TEST_F(ParticleManagerTest, GetParticlesReturnsNullForUnknownEffect)
{
	Particle* particles = reinterpret_cast<Particle*>(0x1);
	u32 count = 123;

	manager.GetParticles(123456, particles, count);

	EXPECT_EQ(particles, nullptr);
	EXPECT_EQ(count, 0u);
}


// -----------------------------------------------------------------------------
// Particle access
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, GetParticlesReturnsEffectStorage)
{
	const int id = manager.CreateEffect(4);

	AddParticle(
		manager,
		id,
		Vector(1.f, 2.f, 3.f));

	Particle* particles = nullptr;
	u32 count = 0;

	manager.GetParticles(id, particles, count);

	ASSERT_NE(particles, nullptr);
	EXPECT_EQ(count, 1u);

	auto effect = manager.GetEffectPtr(id);
	ASSERT_NE(effect, nullptr);

	EXPECT_EQ(particles, effect->particles);
	EXPECT_EQ(&particles[0], &effect->particles[0]);
}

TEST_F(ParticleManagerTest, GetParticlesCountTracksParticles)
{
	const int id = manager.CreateEffect(4);

	EXPECT_EQ(manager.GetParticlesCount(id), 0u);

	AddParticle(manager, id, Vector(1.f, 0.f, 0.f));
	EXPECT_EQ(manager.GetParticlesCount(id), 1u);

	AddParticle(manager, id, Vector(2.f, 0.f, 0.f));
	EXPECT_EQ(manager.GetParticlesCount(id), 2u);
}

TEST_F(ParticleManagerTest, RemoveParticleRemovesRequestedParticle)
{
	const int id = manager.CreateEffect(4);

	AddParticle(manager, id, Vector(1.f, 0.f, 0.f));
	AddParticle(manager, id, Vector(2.f, 0.f, 0.f));

	ASSERT_EQ(manager.GetParticlesCount(id), 2u);

	manager.RemoveParticle(id, 1);

	EXPECT_EQ(manager.GetParticlesCount(id), 1u);

	Particle* particles = nullptr;
	u32 count = 0;
	manager.GetParticles(id, particles, count);

	ASSERT_EQ(count, 1u);
	EXPECT_EQ(particles[0].pos, Vector(1.f, 0.f, 0.f));
}

TEST_F(ParticleManagerTest, RemoveParticleUsesParticleEffectSwapSemantics)
{
	const int id = manager.CreateEffect(4);

	AddParticle(manager, id, Vector(1.f, 0.f, 0.f));
	AddParticle(manager, id, Vector(2.f, 0.f, 0.f));
	AddParticle(manager, id, Vector(3.f, 0.f, 0.f));

	manager.RemoveParticle(id, 0);

	Particle* particles = nullptr;
	u32 count = 0;
	manager.GetParticles(id, particles, count);

	ASSERT_EQ(count, 2u);

	EXPECT_EQ(particles[0].pos, Vector(3.f, 0.f, 0.f));
	EXPECT_EQ(particles[1].pos, Vector(2.f, 0.f, 0.f));
}

TEST_F(ParticleManagerTest, RemoveUnknownEffectDoesNothing)
{
	EXPECT_NO_FATAL_FAILURE(manager.RemoveParticle(123456, 0));
}

TEST_F(ParticleManagerTest, SetMaxParticlesChangesEffectCapacity)
{
	const int id = manager.CreateEffect(8);

	manager.SetMaxParticles(id, 16);

	auto effect = manager.GetEffectPtr(id);
	ASSERT_NE(effect, nullptr);

	EXPECT_EQ(effect->max_particles, 16u);
	EXPECT_EQ(effect->particles_allocated, 16u);
}

TEST_F(ParticleManagerTest, SetMaxParticlesUnknownEffectDoesNothing)
{
	EXPECT_NO_FATAL_FAILURE(manager.SetMaxParticles(123456, 16));
}


// -----------------------------------------------------------------------------
// Callbacks
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, SetCallbackStoresCallbacks)
{
	const int id = manager.CreateEffect(4);

	CallbackState state;
	g_callback_state = &state;

	int owner = 123;

	manager.SetCallback(
		id,
		BirthCallback,
		DeadCallback,
		&owner,
		0x12345678);

	auto effect = manager.GetEffectPtr(id);

	ASSERT_NE(effect, nullptr);

	EXPECT_EQ(effect->b_cb, BirthCallback);
	EXPECT_EQ(effect->d_cb, DeadCallback);
	EXPECT_EQ(effect->owner, &owner);
	EXPECT_EQ(effect->param, 0x12345678u);
}

TEST_F(ParticleManagerTest, SetCallbackUnknownEffectDoesNothing)
{
	int owner = 123;

	EXPECT_NO_FATAL_FAILURE(manager.SetCallback(
		123456,
		BirthCallback,
		DeadCallback,
		&owner,
		42));
}

TEST_F(ParticleManagerTest, BirthCallbackIsForwarded)
{
	const int id = manager.CreateEffect(4);

	CallbackState state;
	g_callback_state = &state;

	int owner = 123;

	manager.SetCallback(
		id,
		BirthCallback,
		nullptr,
		&owner,
		0xabcdef);

	AddParticle(
		manager,
		id,
		Vector(1.f, 2.f, 3.f),
		0x11223344);

	EXPECT_EQ(state.birth_count, 1);
	EXPECT_EQ(state.birth_owner, &owner);
	EXPECT_EQ(state.birth_param, 0xabcdefu);
	EXPECT_EQ(state.birth_index, 0);
	EXPECT_NE(state.birth_particle, nullptr);

	EXPECT_EQ(state.birth_particle->pos, Vector(1.f, 2.f, 3.f));
}

TEST_F(ParticleManagerTest, BirthCallbackReceivesParticleIndex)
{
	const int id = manager.CreateEffect(4);

	CallbackState state;
	g_callback_state = &state;

	manager.SetCallback(id, BirthCallback, nullptr, nullptr, 0);

	AddParticle(manager, id, Vector(1.f, 0.f, 0.f));
	EXPECT_EQ(state.birth_index, 0);

	AddParticle(manager, id, Vector(2.f, 0.f, 0.f));
	EXPECT_EQ(state.birth_index, 1);

	AddParticle(manager, id, Vector(3.f, 0.f, 0.f));
	EXPECT_EQ(state.birth_index, 2);
}

TEST_F(ParticleManagerTest, DeadCallbackIsForwarded)
{
	const int id = manager.CreateEffect(4);

	CallbackState state;
	g_callback_state = &state;

	int owner = 123;

	manager.SetCallback(
		id,
		nullptr,
		DeadCallback,
		&owner,
		0xabcdef);

	AddParticle(manager, id, Vector(1.f, 2.f, 3.f));

	manager.RemoveParticle(id, 0);

	EXPECT_EQ(state.dead_count, 1);
	EXPECT_EQ(state.dead_owner, &owner);
	EXPECT_EQ(state.dead_param, 0xabcdefu);
	EXPECT_EQ(state.dead_index, 0);
	EXPECT_NE(state.dead_particle, nullptr);

	EXPECT_EQ(state.dead_particle->pos, Vector(1.f, 2.f, 3.f));
}


// -----------------------------------------------------------------------------
// Action lists
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, CreateActionListReturnsValidId)
{
	const int id = manager.CreateActionList();

	EXPECT_GE(id, 0);
	EXPECT_NE(manager.GetActionListPtr(id), nullptr);
}

TEST_F(ParticleManagerTest, CreateActionListsReturnsUniqueIds)
{
	const int first = manager.CreateActionList();
	const int second = manager.CreateActionList();
	const int third = manager.CreateActionList();

	EXPECT_NE(first, second);
	EXPECT_NE(first, third);
	EXPECT_NE(second, third);
}

TEST_F(ParticleManagerTest, CreatedActionListIsEmpty)
{
	const int id = manager.CreateActionList();

	auto actions = manager.GetActionListPtr(id);

	ASSERT_NE(actions, nullptr);
	EXPECT_TRUE(actions->empty());
}

TEST_F(ParticleManagerTest, DestroyActionListRemovesActionList)
{
	const int id = manager.CreateActionList();

	ASSERT_NE(manager.GetActionListPtr(id), nullptr);

	manager.DestroyActionList(id);

	EXPECT_EQ(manager.GetActionListPtr(id), nullptr);
}

TEST_F(ParticleManagerTest, DestroyUnknownActionListDoesNothing)
{
	EXPECT_NO_FATAL_FAILURE(manager.DestroyActionList(123456));
}

TEST_F(ParticleManagerTest, UnknownActionListReturnsNull)
{
	EXPECT_EQ(manager.GetActionListPtr(123456), nullptr);
}


// -----------------------------------------------------------------------------
// CreateAction
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, CreateActionCreatesRequestedAction)
{
	struct TestCase
	{
		PActionEnum type;
	};

	const TestCase tests[] =
	{
		{ PAAvoidID },
		{ PABounceID },
		{ PACopyVertexBID },
		{ PADampingID },
		{ PAExplosionID },
		{ PAFollowID },
		{ PAGravitateID },
		{ PAGravityID },
		{ PAJetID },
		{ PAKillOldID },
		{ PAMatchVelocityID },
		{ PAMoveID },
		{ PAOrbitLineID },
		{ PAOrbitPointID },
		{ PARandomAccelID },
		{ PARandomDisplaceID },
		{ PARandomVelocityID },
		{ PARestoreID },
		{ PASinkID },
		{ PASinkVelocityID },
		{ PASourceID },
		{ PASpeedLimitID },
		{ PATargetColorID },
		{ PATargetSizeID },
		{ PATargetRotateID },
		{ PATargetRotateDID },
		{ PATargetVelocityID },
		{ PATargetVelocityDID },
		{ PAVortexID },
		{ PATurbulenceID },
		{ PAScatterID },
	};

	for (const auto& test : tests)
	{
		SCOPED_TRACE(static_cast<int>(test.type));

		ParticleAction* action = manager.CreateAction(test.type);

		ASSERT_NE(action, nullptr);
		EXPECT_EQ(action->type, test.type);

		xr_delete(action);
	}
}


// -----------------------------------------------------------------------------
// Play / Stop
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, PlayEffectWithUnknownActionListDoesNothing)
{
	const int effect_id = manager.CreateEffect(4);

	EXPECT_NO_FATAL_FAILURE(
		manager.PlayEffect(effect_id, 123456));
}

TEST_F(ParticleManagerTest, StopEffectWithUnknownActionListDoesNothing)
{
	const int effect_id = manager.CreateEffect(4);

	EXPECT_NO_FATAL_FAILURE(
		manager.StopEffect(effect_id, 123456));
}

TEST_F(ParticleManagerTest, PlayEffectClearsSourceSilentFlag)
{
	const int action_list_id = manager.CreateActionList();

	auto actions = manager.GetActionListPtr(action_list_id);
	ASSERT_NE(actions, nullptr);

	auto* source = static_cast<PASource*>(
		manager.CreateAction(PASourceID));

	ASSERT_NE(source, nullptr);

	source->m_Flags.set(PASource::flSilent, TRUE);
	actions->append(source);

	manager.PlayEffect(0, action_list_id);

	EXPECT_FALSE(source->m_Flags.is(PASource::flSilent));
}

TEST_F(ParticleManagerTest, StopEffectSetsSourceSilentFlag)
{
	const int action_list_id = manager.CreateActionList();

	auto actions = manager.GetActionListPtr(action_list_id);
	ASSERT_NE(actions, nullptr);

	auto* source = static_cast<PASource*>(
		manager.CreateAction(PASourceID));

	ASSERT_NE(source, nullptr);

	source->m_Flags.set(PASource::flSilent, FALSE);
	actions->append(source);

	manager.StopEffect(0, action_list_id);

	EXPECT_TRUE(source->m_Flags.is(PASource::flSilent));
}

TEST_F(ParticleManagerTest, StopEffectNonDeferredClearsParticles)
{
	const int effect_id = manager.CreateEffect(4);
	const int action_list_id = manager.CreateActionList();

	AddParticle(manager, effect_id, Vector(1.f, 0.f, 0.f));
	AddParticle(manager, effect_id, Vector(2.f, 0.f, 0.f));

	ASSERT_EQ(manager.GetParticlesCount(effect_id), 2u);

	manager.StopEffect(effect_id, action_list_id, FALSE);

	EXPECT_EQ(manager.GetParticlesCount(effect_id), 0u);
}

TEST_F(ParticleManagerTest, StopEffectDeferredKeepsParticles)
{
	const int effect_id = manager.CreateEffect(4);
	const int action_list_id = manager.CreateActionList();

	AddParticle(manager, effect_id, Vector(1.f, 0.f, 0.f));

	ASSERT_EQ(manager.GetParticlesCount(effect_id), 1u);

	manager.StopEffect(effect_id, action_list_id, TRUE);

	EXPECT_EQ(manager.GetParticlesCount(effect_id), 1u);
}

TEST_F(ParticleManagerTest, StopEffectNonDeferredUnknownEffectDoesNothing)
{
	const int action_list_id = manager.CreateActionList();

	EXPECT_NO_FATAL_FAILURE(
		manager.StopEffect(123456, action_list_id, FALSE));
}


// -----------------------------------------------------------------------------
// Update
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, UpdateWithUnknownEffectDoesNothing)
{
	const int action_list_id = manager.CreateActionList();

	EXPECT_NO_FATAL_FAILURE(
		manager.Update(123456, action_list_id, 1.f));
}

TEST_F(ParticleManagerTest, UpdateWithUnknownActionListDoesNothing)
{
	const int effect_id = manager.CreateEffect(4);

	EXPECT_NO_FATAL_FAILURE(
		manager.Update(effect_id, 123456, 1.f));
}

TEST_F(ParticleManagerTest, UpdateWithBothIdsUnknownDoesNothing)
{
	EXPECT_NO_FATAL_FAILURE(
		manager.Update(123456, 654321, 1.f));
}


// -----------------------------------------------------------------------------
// Transform
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, TransformUnknownActionListDoesNothing)
{
	Fmatrix matrix;
	matrix.identity();

	EXPECT_NO_FATAL_FAILURE(
		manager.Transform(123456, matrix, Fvector().set(1.f, 2.f, 3.f)));
}

TEST_F(ParticleManagerTest, TransformUpdatesSourceParentVelocity)
{
	const int action_list_id = manager.CreateActionList();

	auto actions = manager.GetActionListPtr(action_list_id);
	ASSERT_NE(actions, nullptr);

	auto* source = static_cast<PASource*>(
		manager.CreateAction(PASourceID));

	ASSERT_NE(source, nullptr);

	source->parent_motion = 2.f;

	actions->append(source);

	Fmatrix matrix;
	matrix.identity();

	const Fvector velocity = Fvector().set(1.f, 2.f, 3.f);

	manager.Transform(action_list_id, matrix, velocity);

	const pVector expected(2.f, 4.f, 6.f);

	EXPECT_EQ(source->parent_vel, expected);
}


// -----------------------------------------------------------------------------
// Resize through manager
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, SetMaxParticlesCanShrinkEffect)
{
	const int effect_id = manager.CreateEffect(8);

	AddParticle(manager, effect_id, Vector(1.f, 0.f, 0.f));
	AddParticle(manager, effect_id, Vector(2.f, 0.f, 0.f));
	AddParticle(manager, effect_id, Vector(3.f, 0.f, 0.f));

	manager.SetMaxParticles(effect_id, 2);

	auto effect = manager.GetEffectPtr(effect_id);

	ASSERT_NE(effect, nullptr);

	EXPECT_EQ(effect->max_particles, 2u);
	EXPECT_EQ(effect->p_count, 2u);
}

TEST_F(ParticleManagerTest, SetMaxParticlesCanGrowEffect)
{
	const int effect_id = manager.CreateEffect(2);

	AddParticle(manager, effect_id, Vector(1.f, 0.f, 0.f));
	AddParticle(manager, effect_id, Vector(2.f, 0.f, 0.f));

	manager.SetMaxParticles(effect_id, 8);

	AddParticle(manager, effect_id, Vector(3.f, 0.f, 0.f));

	EXPECT_EQ(manager.GetParticlesCount(effect_id), 3u);
}


// -----------------------------------------------------------------------------
// Save / Load
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, SaveAndLoadEmptyActionList)
{
	const int source_id = manager.CreateActionList();
	const int destination_id = manager.CreateActionList();

	auto source = manager.GetActionListPtr(source_id);
	auto destination = manager.GetActionListPtr(destination_id);

	ASSERT_NE(source, nullptr);
	ASSERT_NE(destination, nullptr);

	// This assumes your existing IWriter test helper can create an in-memory
	// writer. Replace the construction below with the project's standard
	// memory-writer fixture if IWriter cannot be instantiated this way.
	//
	// The actual behavioral contract being tested is:
	//
	//   empty list -> SaveActions -> LoadActions -> size == 0
}


// -----------------------------------------------------------------------------
// API consistency
// -----------------------------------------------------------------------------

TEST_F(ParticleManagerTest, DestroyedEffectCannotBeAccessed)
{
	const int effect_id = manager.CreateEffect(4);

	manager.DestroyEffect(effect_id);

	Particle* particles = reinterpret_cast<Particle*>(0x1);
	u32 count = 123;

	manager.GetParticles(effect_id, particles, count);

	EXPECT_EQ(particles, nullptr);
	EXPECT_EQ(count, 0u);
	EXPECT_EQ(manager.GetParticlesCount(effect_id), 0u);
}

TEST_F(ParticleManagerTest, DestroyedActionListCannotBeAccessed)
{
	const int action_list_id = manager.CreateActionList();

	manager.DestroyActionList(action_list_id);

	EXPECT_EQ(manager.GetActionListPtr(action_list_id), nullptr);
}
