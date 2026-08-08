#include "stdafx.h"

#include "Lock.hpp"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

TEST(LockTest, StartsUnlocked)
{
    Lock lock;

    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, EnterLocks)
{
    Lock lock;

    lock.Enter();

    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();

    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, TryEnterLocksWhenUnlocked)
{
    Lock lock;

    EXPECT_TRUE(lock.TryEnter());
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();

    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, TryEnterSucceedsWhenAlreadyOwnedBySameThread)
{
    Lock lock;

    lock.Enter();

    EXPECT_TRUE(lock.IsLocked());
    EXPECT_TRUE(lock.TryEnter());
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();
    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, RecursiveEnterRequiresMatchingLeaves)
{
    Lock lock;

    lock.Enter();
    EXPECT_TRUE(lock.IsLocked());

    lock.Enter();
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();
    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, TryEnterCanBeUsedRecursively)
{
    Lock lock;

    EXPECT_TRUE(lock.TryEnter());
    EXPECT_TRUE(lock.TryEnter());

    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();
    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, TryEnterFailsWhenOwnedByAnotherThread)
{
    Lock lock;

    lock.Enter();

    std::atomic_bool started{false};
    std::atomic_bool finished{false};
    std::atomic_bool result{true};

    std::thread thread([&]
    {
        started.store(true, std::memory_order_release);

        result.store(lock.TryEnter(), std::memory_order_release);

        finished.store(true, std::memory_order_release);
    });

    while (!started.load(std::memory_order_acquire))
        std::this_thread::yield();

    thread.join();

    EXPECT_TRUE(finished.load(std::memory_order_acquire));
    EXPECT_FALSE(result.load(std::memory_order_acquire));
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();

    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, EnterBlocksUntilLockIsReleased)
{
    Lock lock;
    lock.Enter();

    std::atomic_bool started{false};
    std::atomic_bool entered{false};

    std::thread thread([&]
    {
        started.store(true, std::memory_order_release);

        lock.Enter();

        entered.store(true, std::memory_order_release);

        lock.Leave();
    });

    while (!started.load(std::memory_order_acquire))
        std::this_thread::yield();

    // The other thread must still be blocked by our lock.
    std::this_thread::sleep_for(10ms);

    EXPECT_FALSE(entered.load(std::memory_order_acquire));

    lock.Leave();

    thread.join();

    EXPECT_TRUE(entered.load(std::memory_order_acquire));
    EXPECT_FALSE(lock.IsLocked());
}

TEST(LockTest, DifferentLocksDoNotInterfere)
{
    Lock first;
    Lock second;

    first.Enter();

    EXPECT_FALSE(second.IsLocked());
    EXPECT_TRUE(second.TryEnter());
    EXPECT_TRUE(second.IsLocked());

    second.Leave();
    first.Leave();

    EXPECT_FALSE(first.IsLocked());
    EXPECT_FALSE(second.IsLocked());
}

TEST(LockTest, CanBeDestroyedWhenUnlocked)
{
    {
        Lock lock;
        EXPECT_FALSE(lock.IsLocked());
    }

    SUCCEED();
}

TEST(LockTest, CanBeDestroyedAfterUse)
{
    {
        Lock lock;

        lock.Enter();
        lock.Leave();

        EXPECT_FALSE(lock.IsLocked());
    }

    SUCCEED();
}
