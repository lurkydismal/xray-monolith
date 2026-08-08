#include "stdafx.h"

#include "ScopeLock.hpp"

#include <gtest/gtest.h>

TEST(ScopeLock, LocksOnConstruction)
{
    Lock lock;

    EXPECT_FALSE(lock.IsLocked());

    {
        ScopeLock scopeLock(&lock);

        EXPECT_TRUE(lock.IsLocked());
    }
}

TEST(ScopeLock, UnlocksOnDestruction)
{
    Lock lock;

    {
        ScopeLock scopeLock(&lock);
        ASSERT_TRUE(lock.IsLocked());
    }

    EXPECT_FALSE(lock.IsLocked());
}

TEST(ScopeLock, UnlocksWhenLeavingScope)
{
    Lock lock;

    {
        ScopeLock scopeLock(&lock);
        EXPECT_TRUE(lock.IsLocked());

        {
            // A separate scope does not affect the first ScopeLock.
            EXPECT_TRUE(lock.IsLocked());
        }

        EXPECT_TRUE(lock.IsLocked());
    }

    EXPECT_FALSE(lock.IsLocked());
}

TEST(ScopeLock, AllowsLockToBeUsedAgainAfterDestruction)
{
    Lock lock;

    {
        ScopeLock scopeLock(&lock);
        EXPECT_TRUE(lock.IsLocked());
    }

    EXPECT_FALSE(lock.IsLocked());

    {
        ScopeLock scopeLock(&lock);
        EXPECT_TRUE(lock.IsLocked());
    }

    EXPECT_FALSE(lock.IsLocked());
}

TEST(ScopeLock, LockCanBeUsedAfterScopeLock)
{
    Lock lock;

    {
        ScopeLock scopeLock(&lock);
        EXPECT_TRUE(lock.IsLocked());
    }

    EXPECT_FALSE(lock.IsLocked());

    EXPECT_TRUE(lock.TryEnter());
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();

    EXPECT_FALSE(lock.IsLocked());
}

TEST(ScopeLock, ScopeLockWithAlreadyLockedLock)
{
    Lock lock;

    ASSERT_TRUE(lock.TryEnter());
    ASSERT_TRUE(lock.IsLocked());

    {
        ScopeLock scopeLock(&lock);

        EXPECT_TRUE(lock.IsLocked());
    }

    // ScopeLock performs exactly one Leave(), so the original lock
    // remains held.
    EXPECT_TRUE(lock.IsLocked());

    lock.Leave();

    EXPECT_FALSE(lock.IsLocked());
}

TEST(ScopeLock, MultipleScopeLocksTrackLockCounter)
{
    Lock lock;

    {
        ScopeLock first(&lock);
        EXPECT_TRUE(lock.IsLocked());

        {
            ScopeLock second(&lock);
            EXPECT_TRUE(lock.IsLocked());
        }

        // The outer ScopeLock still owns one level of the recursive lock.
        EXPECT_TRUE(lock.IsLocked());
    }

    EXPECT_FALSE(lock.IsLocked());
}

