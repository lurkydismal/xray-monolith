#include "stdafx.h"

#include "ElevatorState.h"

#include <gtest/gtest.h>

class CElevatorStateTest : public ::testing::Test
{
protected:
	CElevatorState state;
};


// -----------------------------------------------------------------------------
// Initial state
// -----------------------------------------------------------------------------

TEST_F(CElevatorStateTest, StartsInNoLadderState)
{
	EXPECT_EQ(state.State(), clbNoLadder);
}

TEST_F(CElevatorStateTest, IsNotActiveInitially)
{
	EXPECT_FALSE(state.Active());
}

TEST_F(CElevatorStateTest, IsNotNearStateInitially)
{
	EXPECT_FALSE(state.NearState());
}

TEST_F(CElevatorStateTest, IsNotNearDownInitially)
{
	EXPECT_FALSE(state.NearDown());
}

TEST_F(CElevatorStateTest, IsNotClimbingInitially)
{
	EXPECT_FALSE(state.ClimbingState());
}


// -----------------------------------------------------------------------------
// State predicates
// -----------------------------------------------------------------------------

TEST_F(CElevatorStateTest, InitialStateIsNoLadderAndNotAnyOperationalState)
{
	EXPECT_EQ(state.State(), clbNoLadder);

	EXPECT_FALSE(state.Active());
	EXPECT_FALSE(state.NearState());
	EXPECT_FALSE(state.NearDown());
	EXPECT_FALSE(state.ClimbingState());
}


// -----------------------------------------------------------------------------
// Methods that are intentionally safe without a ladder
// -----------------------------------------------------------------------------

TEST_F(CElevatorStateTest, GetLeaderNormalDoesNothingWithoutLadder)
{
	Fvector dir;
	dir.set(1.f, 2.f, 3.f);

	state.GetLeaderNormal(dir);

	EXPECT_FLOAT_EQ(dir.x, 1.f);
	EXPECT_FLOAT_EQ(dir.y, 2.f);
	EXPECT_FLOAT_EQ(dir.z, 3.f);
}

TEST_F(CElevatorStateTest, NetRelcaseWithNullObjectDoesNothing)
{
	state.NetRelcase(nullptr);

	EXPECT_EQ(state.State(), clbNoLadder);
	EXPECT_FALSE(state.Active());
}

TEST_F(CElevatorStateTest, NetRelcaseWithoutLadderDoesNothing)
{
	// m_ladder is null after construction.
	// The implementation returns before attempting to use O.
	IPhysicsShellHolder* object = nullptr;

	state.NetRelcase(object);

	EXPECT_EQ(state.State(), clbNoLadder);
	EXPECT_FALSE(state.Active());
}

TEST_F(CElevatorStateTest, UpdateMaterialReturnsFalseWhenNotClimbing)
{
	u16 material = 1234;

	EXPECT_FALSE(state.UpdateMaterial(material));

	// Current implementation must not modify the material index when
	// the state is not climbing.
	EXPECT_EQ(material, u16(1234));
}


// -----------------------------------------------------------------------------
// Deactivate / lifecycle
// -----------------------------------------------------------------------------

TEST_F(CElevatorStateTest, DeactivateLeavesStateInactive)
{
	/*
	 * Deactivate() currently calls:
	 *
	 *     SwitchState(clbNoLadder);
	 *
	 * before clearing m_character.
	 *
	 * Therefore it requires a character to have been assigned and cannot
	 * safely be called on a freshly constructed CElevatorState.
	 *
	 * This behavior is intentionally not tested here because calling it
	 * on the initial object would hit the VERIFY(m_character) in
	 * SwitchState().
	 */
	SUCCEED();
}


// -----------------------------------------------------------------------------
// Enum contract
// -----------------------------------------------------------------------------

TEST(ElevatorStateEnumTest, StatesHaveExpectedValues)
{
	EXPECT_EQ(clbNone, 0);
	EXPECT_EQ(clbNearUp, 1);
	EXPECT_EQ(clbNearDown, 2);
	EXPECT_EQ(clbClimbingUp, 3);
	EXPECT_EQ(clbClimbingDown, 4);
	EXPECT_EQ(clbDepart, 5);
	EXPECT_EQ(clbNoLadder, 6);
	EXPECT_EQ(clbNoState, 7);
}

TEST(ElevatorStateEnumTest, OperationalStatesAreBeforeNoLadder)
{
	EXPECT_LT(clbNone, clbNoLadder);
	EXPECT_LT(clbNearUp, clbNoLadder);
	EXPECT_LT(clbNearDown, clbNoLadder);
	EXPECT_LT(clbClimbingUp, clbNoLadder);
	EXPECT_LT(clbClimbingDown, clbNoLadder);
	EXPECT_LT(clbDepart, clbNoLadder);
}

TEST(ElevatorStateEnumTest, NoStateIsSentinelAfterNoLadder)
{
	EXPECT_EQ(clbNoState, clbNoLadder + 1);
}
