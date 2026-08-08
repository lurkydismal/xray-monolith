#include "stdafx.h"

#include "LocatorAPI_Notifications.h"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <filesystem>
#include <thread>

namespace
{

class TestThread final : public CThread
{
public:
	explicit TestThread(std::atomic<bool>& executed)
		: CThread(0), executed(executed)
	{
	}

	void Execute() override
	{
		executed.store(true, std::memory_order_release);
	}

private:
	std::atomic<bool>& executed;
};

class CThreadTest : public ::testing::Test
{
};

class PathNotificatorTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		InitializeCriticalSection(&criticalSection);
	}

	void TearDown() override
	{
		DeleteCriticalSection(&criticalSection);
	}

	CRITICAL_SECTION criticalSection{};
};

} // namespace

// ============================================================================
// CThread
// ============================================================================

TEST(CThreadTest, ConstructorInitializesThreadAsNotTerminated)
{
	class InspectableThread final : public CThread
	{
	public:
		InspectableThread()
			: CThread(1234)
		{
		}

		void Execute() override
		{
		}

		bool isTerminated() const
		{
			return Terminated != TRUE;
		}

		u32 id() const
		{
			return thID;
		}
	};

	InspectableThread thread;

	EXPECT_EQ(thread.id(), 1234u);
	EXPECT_TRUE(thread.isTerminated());
}

TEST(CThreadTest, TerminateSetsTerminatedFlag)
{
	class InspectableThread final : public CThread
	{
	public:
		InspectableThread()
			: CThread(0)
		{
		}

		void Execute() override
		{
		}

		bool isTerminated() const
		{
			return Terminated == TRUE;
		}
	};

	InspectableThread thread;

	EXPECT_FALSE(thread.isTerminated());

	thread.Terminate();

	EXPECT_TRUE(thread.isTerminated());
}

TEST(CThreadTest, StartInvokesExecute)
{
	std::atomic<bool> executed{false};

	TestThread thread(executed);
	thread.Start();

	// thread_spawn() is asynchronous, so wait for the worker to run.
	const auto deadline = std::chrono::steady_clock::now() +
		std::chrono::seconds(2);

	while (!executed.load(std::memory_order_acquire) &&
	       std::chrono::steady_clock::now() < deadline)
	{
		std::this_thread::yield();
	}

	EXPECT_TRUE(executed.load(std::memory_order_acquire));
}

// ============================================================================
// CFS_PathNotificator
// ============================================================================

TEST(PathNotificatorTest, ConstructorCreatesMutex)
{
	CFS_PathNotificator notificator;

	EXPECT_NE(notificator.FMutex, nullptr);
}

TEST(PathNotificatorTest, ConstructorInitializesNotifyFlagsToZero)
{
	CFS_PathNotificator notificator;

	EXPECT_EQ(notificator.FNotifyOptionFlags, 0u);
}

TEST(PathNotificatorTest, DestructorCanDestroyEmptyNotificator)
{
	{
		CFS_PathNotificator notificator;
		ASSERT_NE(notificator.FMutex, nullptr);
	}

	SUCCEED();
}

TEST(PathNotificatorTest, RegisterPathCanRegisterPath)
{
	CFS_PathNotificator notificator;

	FS_Path path(".", "", nullptr, nullptr, 0);

	notificator.RegisterPath(path);

	SUCCEED();
}

TEST(PathNotificatorTest, RegisterSamePathCanBeCalledMoreThanOnce)
{
	CFS_PathNotificator notificator;

	FS_Path path(".", "", nullptr, nullptr, 0);

	notificator.RegisterPath(path);
	notificator.RegisterPath(path);

	SUCCEED();
}

TEST(PathNotificatorTest, RegisterDifferentPaths)
{
	CFS_PathNotificator notificator;

	FS_Path first(".", "", nullptr, nullptr, 0);
	FS_Path second("..", "", nullptr, nullptr, 0);

	notificator.RegisterPath(first);
	notificator.RegisterPath(second);

	SUCCEED();
}

TEST(PathNotificatorTest, SamePathWithDifferentRecursionIsRegisteredSeparately)
{
	CFS_PathNotificator notificator;

	FS_Path nonRecursive(".", "", nullptr, nullptr, 0);
	FS_Path recursive(".", "", nullptr, nullptr, FS_Path::flRecurse);

	notificator.RegisterPath(nonRecursive);
	notificator.RegisterPath(recursive);

	SUCCEED();
}

TEST(PathNotificatorTest, SamePathAndSameRecursionIsDeduplicated)
{
	CFS_PathNotificator notificator;

	FS_Path first(".", "", nullptr, nullptr, FS_Path::flRecurse);
	FS_Path second(".", "", nullptr, nullptr, FS_Path::flRecurse);

	notificator.RegisterPath(first);
	notificator.RegisterPath(second);

	SUCCEED();
}
