#include "stdafx.h"

#include "_math.h"
#include "_math.hpp"

#include <gtest/gtest.h>

#include <atomic>
#include <thread>
#include <chrono>


#if 0
TEST(math_cpu, initialize_cpu)
{
	_initialize_cpu();

	EXPECT_TRUE(_math_internal::g_initialize_cpu_called);

	EXPECT_GT(CPU::qpc_freq, 0);
	EXPECT_GT(CPU::clk_per_second, 0);

	EXPECT_GT(CPU::clk_to_seconds, 0.0f);
	EXPECT_GT(CPU::clk_to_milisec, 0.0f);
	EXPECT_GT(CPU::clk_to_microsec, 0.0f);
}
#endif


#if 0
TEST(math_cpu, qpc_is_monotonic)
{
	_initialize_cpu();

	u64 a = CPU::QPC();

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	u64 b = CPU::QPC();

	EXPECT_GT(b, a);
}
#endif


#if 0
TEST(math_cpu, qpc_counter_increments)
{
	_initialize_cpu();

	u32 before = CPU::qpc_counter;

	CPU::QPC();
	CPU::QPC();
	CPU::QPC();

	EXPECT_EQ(CPU::qpc_counter, before + 3);
}
#endif


#if 0
TEST(math_cpu, clock_conversion)
{
	_initialize_cpu();

	EXPECT_NEAR(
		CPU::clk_to_seconds * float(CPU::clk_per_second),
		1.0f,
		0.01f
	);

	EXPECT_NEAR(
		CPU::clk_to_milisec * float(CPU::clk_per_milisec),
		1.0f,
		0.01f
	);
}
#endif


TEST(math_fpu, mode_switches_do_not_crash)
{
	FPU::m24();
	FPU::m24r();

	FPU::m53();
	FPU::m53r();

	FPU::m64();
	FPU::m64r();

    SUCCEED();
}


TEST(math_thread, thread_spawn_executes)
{
	static std::atomic<bool> called(false);

	auto fn = [](void*)
	{
		called = true;
	};

	thread_spawn(
		fn,
		"test_thread",
		0,
		nullptr
	);

	for (int i = 0; i < 100 && !called; ++i)
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	EXPECT_TRUE(called);
}


#if 0
TEST(math_globals, identity_matrix_initialized)
{
	_initialize_cpu();

	Fvector v(1.f, 2.f, 3.f);
	Fvector result;

	Fidentity.transform(result, v);

	EXPECT_FLOAT_EQ(result.x, v.x);
	EXPECT_FLOAT_EQ(result.y, v.y);
	EXPECT_FLOAT_EQ(result.z, v.z);
}
#endif


TEST(math_spline, spline2_endpoints)
{
	Fvector points[4];

	points[0].set(0, 0, 0);
	points[1].set(1, 1, 1);
	points[2].set(2, 2, 2);
	points[3].set(3, 3, 3);

	Fvector result;

    _math_internal::spline2(0.f, points, &result);

	EXPECT_TRUE(_valid(result));

	_math_internal::spline2(1.f, points, &result);

	EXPECT_TRUE(_valid(result));
}


TEST(math_spline, spline3_produces_valid_values)
{
	Fvector points[4];

	points[0].set(0, 0, 0);
	points[1].set(1, 1, 1);
	points[2].set(2, 2, 2);
	points[3].set(3, 3, 3);

	Fvector result;

	for (float t = 0.f; t <= 1.f; t += 0.1f)
	{
		_math_internal::spline3(t, points, &result);

		EXPECT_TRUE(_valid(result));
	}
}


#if 0
TEST(math_cpu, cpu_detect_populates_id)
{
	_initialize_cpu();

	EXPECT_NE(
		strlen(CPU::ID.model_name),
		0
	);

	EXPECT_NE(
		strlen(CPU::ID.v_name),
		0
	);

	EXPECT_GT(
		CPU::ID.n_cores,
		0
	);

	EXPECT_GT(
		CPU::ID.n_threads,
		0
	);
}
#endif
