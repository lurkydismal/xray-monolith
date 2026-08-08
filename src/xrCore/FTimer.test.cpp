#include "stdafx.h"

#include "FTimer.h"

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

// TODO: Fix

#if 0
namespace
{

class TimerTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		// Do not allow state from another test to leak into this one.
		g_pauseMngr().Pause(false);
		g_bEnableStatGather = FALSE;
	}

	void TearDown() override
	{
		g_pauseMngr().Pause(false);
		g_bEnableStatGather = FALSE;
	}

	static void SleepMs(unsigned ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
};

TEST_F(TimerTest, BaseTimerStartsAtZero)
{
	CTimerBase timer;

	EXPECT_EQ(timer.GetElapsed_ticks(), 0u);
	EXPECT_EQ(timer.GetElapsed_ms(), 0u);
	EXPECT_FLOAT_EQ(timer.GetElapsed_sec(), 0.0f);
}

TEST_F(TimerTest, BaseTimerStartProducesElapsedTime)
{
	CTimerBase timer;

	timer.Start();
	SleepMs(5);

	EXPECT_GT(timer.GetElapsed_ticks(), 0u);
	EXPECT_GE(timer.GetElapsed_ms(), 1u);
	EXPECT_GT(timer.GetElapsed_sec(), 0.0f);
}

TEST_F(TimerTest, BaseTimerStartRestartsTimer)
{
	CTimerBase timer;

	timer.Start();
	SleepMs(5);

	const u64 first = timer.GetElapsed_ticks();
	ASSERT_GT(first, 0u);

	timer.Start();

	const u64 immediately_after_restart = timer.GetElapsed_ticks();

	// Start() should move the beginning of the measurement to "now".
	EXPECT_LT(immediately_after_restart, first);

	SleepMs(5);

	const u64 second = timer.GetElapsed_ticks();

	EXPECT_GT(second, immediately_after_restart);
}

TEST_F(TimerTest, TimerStartsWithTimeFactorOne)
{
	CTimer timer;

	EXPECT_FLOAT_EQ(timer.time_factor(), 1.0f);

	timer.Start();
	SleepMs(5);

	EXPECT_GT(timer.GetElapsed_ticks(), 0u);
}

TEST_F(TimerTest, TimerTimeFactorZeroFreezesElapsedTime)
{
	CTimer timer;

	timer.Start();
	SleepMs(5);

	const u64 before = timer.GetElapsed_ticks();
	ASSERT_GT(before, 0u);

	timer.time_factor(0.0f);

	const u64 immediately_after_change = timer.GetElapsed_ticks();

	// Changing the factor must preserve the time accumulated before
	// the change.
	EXPECT_NEAR(
		static_cast<double>(immediately_after_change),
		static_cast<double>(before),
		static_cast<double>(CPU::qpc_freq) * 0.002);

	SleepMs(5);

	const u64 after = timer.GetElapsed_ticks();

	// With factor == 0, real time should no longer advance the timer.
	EXPECT_NEAR(
		static_cast<double>(after),
		static_cast<double>(immediately_after_change),
		static_cast<double>(CPU::qpc_freq) * 0.002);
}

TEST_F(TimerTest, TimerTimeFactorScalesElapsedTime)
{
	CTimer timer;

	timer.Start();
	SleepMs(10);

	const u64 before = timer.GetElapsed_ticks();
	ASSERT_GT(before, 0u);

	timer.time_factor(2.0f);

	const u64 at_factor_change = timer.GetElapsed_ticks();

	SleepMs(10);

	const u64 after = timer.GetElapsed_ticks();

	const u64 real_delta = after - at_factor_change;

	// At factor 2, roughly 10 ms of real time should produce roughly
	// 20 ms worth of timer ticks.
	const double expected =
		static_cast<double>(CPU::qpc_freq) * 0.010 * 2.0;

	EXPECT_NEAR(
		static_cast<double>(real_delta),
		expected,
		static_cast<double>(CPU::qpc_freq) * 0.006);
}

TEST_F(TimerTest, TimerChangingFactorPreservesAccumulatedTime)
{
	CTimer timer;

	timer.Start();
	SleepMs(10);

	const u64 before = timer.GetElapsed_ticks();
	ASSERT_GT(before, 0u);

	timer.time_factor(2.0f);

	const u64 after = timer.GetElapsed_ticks();

	// The time accumulated under the old factor must not be lost or
	// recalculated using the new factor.
	EXPECT_NEAR(
		static_cast<double>(after),
		static_cast<double>(before),
		static_cast<double>(CPU::qpc_freq) * 0.003);
}

TEST_F(TimerTest, TimerMillisecondAndSecondConversionsAgree)
{
	CTimer timer;

	timer.Start();
	SleepMs(10);

	const u64 ticks = timer.GetElapsed_ticks();
	const u32 ms = timer.GetElapsed_ms();
	const float ms_f = timer.GetElapsed_ms_f();
	const float sec = timer.GetElapsed_sec();

	ASSERT_GT(ticks, 0u);

	EXPECT_NEAR(
		static_cast<double>(ms),
		static_cast<double>(ticks) * 1000.0 / CPU::qpc_freq,
		1.0);

	EXPECT_NEAR(
		static_cast<double>(ms_f),
		static_cast<double>(ticks) * 1000.0 / CPU::qpc_freq,
		0.01);

	EXPECT_NEAR(
		static_cast<double>(sec),
		static_cast<double>(ticks) / CPU::qpc_freq,
		0.001);
}

TEST_F(TimerTest, PausedTimerReportsPausedState)
{
	CTimer_paused timer;

	EXPECT_FALSE(timer.Paused());

	timer.Pause(true);
	EXPECT_TRUE(timer.Paused());

	timer.Pause(false);
	EXPECT_FALSE(timer.Paused());
}

TEST_F(TimerTest, PausedTimerStopsWhilePaused)
{
	CTimer_paused timer;

	timer.Start();
	SleepMs(10);

	timer.Pause(true);

	const u64 paused = timer.GetElapsed_ticks();

	SleepMs(20);

	const u64 still_paused = timer.GetElapsed_ticks();

	// While paused, GetElapsed_ticks() must return qwPausedTime rather
	// than continuing to use QPC.
	EXPECT_EQ(still_paused, paused);
}

TEST_F(TimerTest, PausedTimerContinuesAfterUnpause)
{
	CTimer_paused timer;

	timer.Start();
	SleepMs(10);

	timer.Pause(true);
	const u64 paused = timer.GetElapsed_ticks();

	SleepMs(20);

	timer.Pause(false);
	SleepMs(10);

	const u64 after = timer.GetElapsed_ticks();

	EXPECT_GT(after, paused);

	// The 20 ms spent paused must not contribute to elapsed time.
	//
	// We only require that the timer did not advance by approximately
	// the entire wall-clock interval.
	const u64 wall_clock_interval =
		static_cast<u64>(CPU::qpc_freq) * 0.030;

	EXPECT_LT(after - paused, wall_clock_interval);
}

TEST_F(TimerTest, PausingAlreadyPausedTimerDoesNothing)
{
	CTimer_paused timer;

	timer.Start();
	SleepMs(5);

	timer.Pause(true);
	const u64 first = timer.GetElapsed_ticks();

	SleepMs(5);

	timer.Pause(true);
	const u64 second = timer.GetElapsed_ticks();

	EXPECT_EQ(second, first);
	EXPECT_TRUE(timer.Paused());
}

TEST_F(TimerTest, UnpausingAlreadyRunningTimerDoesNothing)
{
	CTimer_paused timer;

	timer.Start();
	SleepMs(5);

	const u64 before = timer.GetElapsed_ticks();

	timer.Pause(false);

	SleepMs(5);

	const u64 after = timer.GetElapsed_ticks();

	EXPECT_GT(after, before);
	EXPECT_FALSE(timer.Paused());
}

TEST_F(TimerTest, PauseManagerPausesRegisteredTimers)
{
	CTimer_paused first;
	CTimer_paused second;

	first.Start();
	second.Start();

	SleepMs(5);

	g_pauseMngr().Pause(true);

	ASSERT_TRUE(g_pauseMngr().Paused());
	EXPECT_TRUE(first.Paused());
	EXPECT_TRUE(second.Paused());

	const u64 first_paused = first.GetElapsed_ticks();
	const u64 second_paused = second.GetElapsed_ticks();

	SleepMs(10);

	EXPECT_EQ(first.GetElapsed_ticks(), first_paused);
	EXPECT_EQ(second.GetElapsed_ticks(), second_paused);

	g_pauseMngr().Pause(false);

	EXPECT_FALSE(g_pauseMngr().Paused());
	EXPECT_FALSE(first.Paused());
	EXPECT_FALSE(second.Paused());
}

TEST_F(TimerTest, PauseManagerDoesNothingWhenStateDoesNotChange)
{
	CTimer_paused timer;

	timer.Start();
	SleepMs(5);

	g_pauseMngr().Pause(true);
	const u64 paused = timer.GetElapsed_ticks();

	g_pauseMngr().Pause(true);

	EXPECT_EQ(timer.GetElapsed_ticks(), paused);
	EXPECT_TRUE(timer.Paused());

	g_pauseMngr().Pause(false);
	g_pauseMngr().Pause(false);

	EXPECT_FALSE(timer.Paused());
	EXPECT_FALSE(g_pauseMngr().Paused());
}

TEST_F(TimerTest, PauseManagerOnlyPausesRegisteredTimers)
{
	CTimer_paused registered;
	CTimerBase unregistered;

	registered.Start();
	unregistered.Start();

	SleepMs(5);

	g_pauseMngr().Pause(true);

	EXPECT_TRUE(registered.Paused());

	// CTimerBase has no pause support and therefore continues normally.
	const u64 before = unregistered.GetElapsed_ticks();

	SleepMs(5);

	const u64 after = unregistered.GetElapsed_ticks();

	EXPECT_GT(after, before);

	g_pauseMngr().Pause(false);
}

TEST_F(TimerTest, TimerUnregistersFromPauseManagerOnDestruction)
{
	{
		CTimer_paused timer;
		timer.Start();
	}

	// If UnRegister() fails, Pause() will dereference the destroyed timer.
	// This test primarily checks that the current registration lifetime is
	// safe.
	EXPECT_NO_FATAL_FAILURE(g_pauseMngr().Pause(true));
	EXPECT_NO_FATAL_FAILURE(g_pauseMngr().Pause(false));
}

TEST_F(TimerTest, NewlyRegisteredTimerDoesNotInheritManagerPauseState)
{
	g_pauseMngr().Pause(true);

	CTimer_paused timer;

	// This documents the current implementation:
	// Register() only adds the timer to the manager. It does not call
	// Pause(m_paused) on a newly registered timer.
	EXPECT_FALSE(timer.Paused());

	g_pauseMngr().Pause(false);
}

TEST_F(TimerTest, StatTimerStartsWithZeroState)
{
	CStatTimer timer;

	EXPECT_EQ(timer.accum, 0u);
	EXPECT_FLOAT_EQ(timer.result, 0.0f);
	EXPECT_EQ(timer.count, 0u);
	EXPECT_EQ(timer.GetElapsed_ticks(), 0u);
}

TEST_F(TimerTest, StatTimerBeginAndEndAreDisabledByDefault)
{
	CStatTimer timer;

	timer.FrameStart();

	timer.Begin();
	SleepMs(5);
	timer.End();

	EXPECT_EQ(timer.count, 0u);
	EXPECT_EQ(timer.accum, 0u);
}

TEST_F(TimerTest, StatTimerAccumulatesWhenEnabled)
{
	g_bEnableStatGather = TRUE;

	CStatTimer timer;

	timer.FrameStart();

	timer.Begin();
	SleepMs(5);
	timer.End();

	EXPECT_EQ(timer.count, 1u);
	EXPECT_GT(timer.accum, 0u);
	EXPECT_EQ(timer.GetElapsed_ticks(), timer.accum);
}

TEST_F(TimerTest, StatTimerCanAccumulateMultipleMeasurements)
{
	g_bEnableStatGather = TRUE;

	CStatTimer timer;

	timer.FrameStart();

	timer.Begin();
	SleepMs(5);
	timer.End();

	const u64 first = timer.accum;

	timer.Begin();
	SleepMs(5);
	timer.End();

	EXPECT_EQ(timer.count, 2u);
	EXPECT_GT(timer.accum, first);
}

TEST_F(TimerTest, StatTimerFrameStartResetsAccumulationAndCount)
{
	g_bEnableStatGather = TRUE;

	CStatTimer timer;

	timer.Begin();
	SleepMs(5);
	timer.End();

	ASSERT_EQ(timer.count, 1u);
	ASSERT_GT(timer.accum, 0u);

	timer.FrameStart();

	EXPECT_EQ(timer.count, 0u);
	EXPECT_EQ(timer.accum, 0u);
}

TEST_F(TimerTest, StatTimerFrameEndUpdatesMaximum)
{
	CStatTimer timer;

	timer.accum = CPU::qpc_freq;
	timer.FrameEnd();

	// One second expressed as milliseconds.
	EXPECT_FLOAT_EQ(timer.result, 1000.0f);
}

TEST_F(TimerTest, StatTimerFrameEndSmoothsValuesBelowMaximum)
{
	CStatTimer timer;

	timer.result = 1000.0f;
	timer.accum = 0;

	timer.FrameEnd();

	// Current implementation:
	// result = 0.99 * old_result + 0.01 * current_time
	//         = 0.99 * 1000 + 0.01 * 0
	//         = 990.
	EXPECT_FLOAT_EQ(timer.result, 990.0f);
}

TEST_F(TimerTest, StatTimerFrameEndReplacesResultWhenCurrentValueIsHigher)
{
	CStatTimer timer;

	timer.result = 100.0f;
	timer.accum = CPU::qpc_freq / 2;

	timer.FrameEnd();

	EXPECT_FLOAT_EQ(timer.result, 500.0f);
}

TEST_F(TimerTest, StatTimerElapsedConversionsAreBasedOnAccumulation)
{
	CStatTimer timer;

	timer.accum = CPU::qpc_freq;

	EXPECT_EQ(timer.GetElapsed_ticks(), CPU::qpc_freq);
	EXPECT_EQ(timer.GetElapsed_ms(), 1000u);
	EXPECT_FLOAT_EQ(timer.GetElapsed_sec(), 1.0f);
}

} // namespace
#endif
