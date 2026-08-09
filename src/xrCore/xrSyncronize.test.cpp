#include "stdafx.h"

#include "xrSyncronize.h"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace
{

class ThreadGate
{
public:
    void wait()
    {
        std::unique_lock lock(mutex);

        condition.wait(lock, [this] {
            return released;
        });
    }

    void release()
    {
        {
            std::lock_guard lock(mutex);
            released = true;
        }

        condition.notify_all();
    }

private:
    std::mutex mutex;
    std::condition_variable condition;
    bool released = false;
};


// -----------------------------------------------------------------------------
// xrCriticalSection
// -----------------------------------------------------------------------------

TEST(XrCriticalSection, IsValidAfterConstruction)
{
    xrCriticalSection section;

    EXPECT_TRUE(section.IsValid());
}

TEST(XrCriticalSection, EnterAndLeave)
{
    xrCriticalSection section;

    section.Enter();
    section.Leave();

    SUCCEED();
}

TEST(XrCriticalSection, TryEnterSucceedsWhenUnlocked)
{
    xrCriticalSection section;

    EXPECT_NE(section.TryEnter(), FALSE);

    section.Leave();
}

TEST(XrCriticalSection, TryEnterFailsWhenHeldByAnotherThread)
{
    xrCriticalSection section;

    section.Enter();

    std::atomic<BOOL> result{TRUE};

    std::thread worker([&] {
        result.store(section.TryEnter(), std::memory_order_release);
    });

    worker.join();

    EXPECT_EQ(result.load(std::memory_order_acquire), FALSE);

    section.Leave();
}

TEST(XrCriticalSection, TryEnterSucceedsAgainAfterLeave)
{
    xrCriticalSection section;

    section.Enter();
    section.Leave();

    EXPECT_NE(section.TryEnter(), FALSE);

    section.Leave();
}

TEST(XrCriticalSection, IsValidRemainsTrueAfterUse)
{
    xrCriticalSection section;

    section.Enter();
    section.Leave();

    EXPECT_TRUE(section.IsValid());
}


// -----------------------------------------------------------------------------
// xrCriticalSection::raii
// -----------------------------------------------------------------------------

TEST(XrCriticalSectionRaii, AcquiresLockOnConstruction)
{
    xrCriticalSection section;

    xrCriticalSection::raii guard(&section);

    std::atomic<BOOL> result{TRUE};

    std::thread worker([&] {
        result.store(section.TryEnter(), std::memory_order_release);
    });

    worker.join();

    EXPECT_EQ(result.load(std::memory_order_acquire), FALSE);
}

TEST(XrCriticalSectionRaii, ReleasesLockOnDestruction)
{
    xrCriticalSection section;

    {
        xrCriticalSection::raii guard(&section);
    }

    EXPECT_NE(section.TryEnter(), FALSE);

    section.Leave();
}


// -----------------------------------------------------------------------------
// xrCriticalSectionGuard
// -----------------------------------------------------------------------------

TEST(XrCriticalSectionGuard, PointerConstructorAcquiresLock)
{
    xrCriticalSection section;

    {
        xrCriticalSectionGuard guard(&section);

        EXPECT_EQ(section.TryEnter(), FALSE);
    }

    EXPECT_NE(section.TryEnter(), FALSE);
    section.Leave();
}

TEST(XrCriticalSectionGuard, ReferenceConstructorAcquiresLock)
{
    xrCriticalSection section;

    {
        xrCriticalSectionGuard guard(section);

        EXPECT_EQ(section.TryEnter(), FALSE);
    }

    EXPECT_NE(section.TryEnter(), FALSE);
    section.Leave();
}

TEST(XrCriticalSectionGuard, ReleasesLockOnDestruction)
{
    xrCriticalSection section;

    {
        xrCriticalSectionGuard guard(section);
    }

    EXPECT_NE(section.TryEnter(), FALSE);

    section.Leave();
}


// -----------------------------------------------------------------------------
// xrCriticalSectionTryGuard
// -----------------------------------------------------------------------------

TEST(XrCriticalSectionTryGuard, OwnsLockWhenAvailable)
{
    xrCriticalSection section;

    xrCriticalSectionTryGuard guard(section);

    EXPECT_TRUE(guard.owns_lock());
}

TEST(XrCriticalSectionTryGuard, DoesNotOwnLockWhenContended)
{
    xrCriticalSection section;

    section.Enter();

    {
        xrCriticalSectionTryGuard guard(section);

        EXPECT_FALSE(guard.owns_lock());
    }

    // The failed guard must not release somebody else's lock.
    EXPECT_EQ(section.TryEnter(), FALSE);

    section.Leave();
}

TEST(XrCriticalSectionTryGuard, ReleasesOwnedLockOnDestruction)
{
    xrCriticalSection section;

    {
        xrCriticalSectionTryGuard guard(section);

        ASSERT_TRUE(guard.owns_lock());
    }

    EXPECT_NE(section.TryEnter(), FALSE);

    section.Leave();
}

TEST(XrCriticalSectionTryGuard, PointerConstructor)
{
    xrCriticalSection section;

    {
        xrCriticalSectionTryGuard guard(&section);

        ASSERT_TRUE(guard.owns_lock());
    }

    EXPECT_NE(section.TryEnter(), FALSE);

    section.Leave();
}

TEST(XrCriticalSectionTryGuard, FailedGuardDoesNotReleaseLock)
{
    xrCriticalSection section;

    section.Enter();

    {
        xrCriticalSectionTryGuard guard(&section);

        ASSERT_FALSE(guard.owns_lock());
    }

    // Still owned by the original owner.
    EXPECT_EQ(section.TryEnter(), FALSE);

    section.Leave();
}


// -----------------------------------------------------------------------------
// Cross-thread critical-section behavior
// -----------------------------------------------------------------------------

TEST(XrCriticalSection, ExcludesOtherThreads)
{
    xrCriticalSection section;
    ThreadGate gate;

    std::atomic<bool> worker_attempted{false};
    std::atomic<BOOL> worker_result{TRUE};

    section.Enter();

    std::thread worker([&] {
        worker_attempted.store(true, std::memory_order_release);

        // This must fail while the main thread owns the section.
        worker_result.store(section.TryEnter(), std::memory_order_release);

        gate.wait();
    });

    while (!worker_attempted.load(std::memory_order_acquire))
        std::this_thread::yield();

    EXPECT_EQ(worker_result.load(std::memory_order_acquire), FALSE);

    section.Leave();
    gate.release();

    worker.join();
}


// -----------------------------------------------------------------------------
// xrSRWLock
// -----------------------------------------------------------------------------

TEST(XrSRWLock, ExclusiveLockCanBeAcquired)
{
    xrSRWLock lock;

    lock.AcquireExclusive();
    lock.ReleaseExclusive();

    SUCCEED();
}

TEST(XrSRWLock, SharedLockCanBeAcquired)
{
    xrSRWLock lock;

    lock.AcquireShared();
    lock.ReleaseShared();

    SUCCEED();
}

TEST(XrSRWLock, TryAcquireExclusiveSucceedsWhenUnlocked)
{
    xrSRWLock lock;

    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);

    lock.ReleaseExclusive();
}

TEST(XrSRWLock, TryAcquireSharedSucceedsWhenUnlocked)
{
    xrSRWLock lock;

    EXPECT_NE(lock.TryAcquireShared(), FALSE);

    lock.ReleaseShared();
}

TEST(XrSRWLock, TryAcquireExclusiveFailsWhileExclusivelyLocked)
{
    xrSRWLock lock;

    lock.AcquireExclusive();

    EXPECT_EQ(lock.TryAcquireExclusive(), FALSE);

    lock.ReleaseExclusive();
}

TEST(XrSRWLock, TryAcquireSharedFailsWhileExclusivelyLocked)
{
    xrSRWLock lock;

    lock.AcquireExclusive();

    EXPECT_EQ(lock.TryAcquireShared(), FALSE);

    lock.ReleaseExclusive();
}

TEST(XrSRWLock, TryAcquireExclusiveSucceedsAfterRelease)
{
    xrSRWLock lock;

    lock.AcquireExclusive();
    lock.ReleaseExclusive();

    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);

    lock.ReleaseExclusive();
}

TEST(XrSRWLock, TryAcquireSharedSucceedsAfterRelease)
{
    xrSRWLock lock;

    lock.AcquireExclusive();
    lock.ReleaseExclusive();

    EXPECT_NE(lock.TryAcquireShared(), FALSE);

    lock.ReleaseShared();
}

TEST(XrSRWLock, MultipleSharedAcquiresAreAllowed)
{
    xrSRWLock lock;

    ASSERT_NE(lock.TryAcquireShared(), FALSE);
    ASSERT_NE(lock.TryAcquireShared(), FALSE);

    lock.ReleaseShared();
    lock.ReleaseShared();
}

TEST(XrSRWLock, ExclusiveAcquireFailsWhileSharedLockIsHeld)
{
    xrSRWLock lock;

    lock.AcquireShared();

    EXPECT_EQ(lock.TryAcquireExclusive(), FALSE);

    lock.ReleaseShared();
}

TEST(XrSRWLock, SharedAcquireFailsAfterExclusiveAcquire)
{
    xrSRWLock lock;

    lock.AcquireExclusive();

    EXPECT_EQ(lock.TryAcquireShared(), FALSE);

    lock.ReleaseExclusive();
}


// -----------------------------------------------------------------------------
// xrSRWLock cross-thread behavior
// -----------------------------------------------------------------------------

TEST(XrSRWLock, ExclusiveLockExcludesOtherThread)
{
    xrSRWLock lock;

    lock.AcquireExclusive();

    std::atomic<BOOL> result{TRUE};

    std::thread worker([&] {
        result.store(
            lock.TryAcquireExclusive(),
            std::memory_order_release
        );
    });

    worker.join();

    EXPECT_EQ(result.load(std::memory_order_acquire), FALSE);

    lock.ReleaseExclusive();
}

TEST(XrSRWLock, ExclusiveLockExcludesSharedAcquisitionFromOtherThread)
{
    xrSRWLock lock;

    lock.AcquireExclusive();

    std::atomic<BOOL> result{TRUE};

    std::thread worker([&] {
        result.store(
            lock.TryAcquireShared(),
            std::memory_order_release
        );
    });

    worker.join();

    EXPECT_EQ(result.load(std::memory_order_acquire), FALSE);

    lock.ReleaseExclusive();
}

TEST(XrSRWLock, SharedLocksCanBeHeldByMultipleThreads)
{
    xrSRWLock lock;

    lock.AcquireShared();

    std::atomic<BOOL> result{FALSE};

    std::thread worker([&] {
        result.store(
            lock.TryAcquireShared(),
            std::memory_order_release
        );

        if (result.load(std::memory_order_acquire))
            lock.ReleaseShared();
    });

    worker.join();

    EXPECT_NE(result.load(std::memory_order_acquire), FALSE);

    lock.ReleaseShared();
}


// -----------------------------------------------------------------------------
// xrSRWLockGuard
// -----------------------------------------------------------------------------

TEST(XrSRWLockGuard, ReferenceConstructorAcquiresExclusiveLock)
{
    xrSRWLock lock;

    {
        xrSRWLockGuard guard(lock);

        EXPECT_EQ(lock.TryAcquireExclusive(), FALSE);
    }

    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);
    lock.ReleaseExclusive();
}

TEST(XrSRWLockGuard, PointerConstructorAcquiresExclusiveLock)
{
    xrSRWLock lock;

    {
        xrSRWLockGuard guard(&lock);

        EXPECT_EQ(lock.TryAcquireExclusive(), FALSE);
    }

    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);
    lock.ReleaseExclusive();
}

TEST(XrSRWLockGuard, SharedGuardAcquiresSharedLock)
{
    xrSRWLock lock;

    {
        xrSRWLockGuard guard(lock, true);

        // A second shared acquisition should be possible.
        EXPECT_NE(lock.TryAcquireShared(), FALSE);
        lock.ReleaseShared();
    }

    // The guard's shared acquisition has been released.
    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);
    lock.ReleaseExclusive();
}

TEST(XrSRWLockGuard, PointerSharedGuardAcquiresSharedLock)
{
    xrSRWLock lock;

    {
        xrSRWLockGuard guard(&lock, true);

        EXPECT_NE(lock.TryAcquireShared(), FALSE);
        lock.ReleaseShared();
    }

    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);
    lock.ReleaseExclusive();
}

TEST(XrSRWLockGuard, ReleasesExclusiveLockOnDestruction)
{
    xrSRWLock lock;

    {
        xrSRWLockGuard guard(lock);
    }

    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);
    lock.ReleaseExclusive();
}

TEST(XrSRWLockGuard, ReleasesSharedLockOnDestruction)
{
    xrSRWLock lock;

    {
        xrSRWLockGuard guard(lock, true);
    }

    EXPECT_NE(lock.TryAcquireExclusive(), FALSE);
    lock.ReleaseExclusive();
}


// -----------------------------------------------------------------------------
// xrSpinWait
// -----------------------------------------------------------------------------

TEST(XrSpinWait, CanBeConstructedWithDefaultCount)
{
    xrSpinWait wait;

    wait();

    SUCCEED();
}

TEST(XrSpinWait, CanBeConstructedWithCustomCount)
{
    xrSpinWait wait(4);

    for (int i = 0; i < 8; ++i)
        wait();

    SUCCEED();
}

TEST(XrSpinWait, CanBeCalledRepeatedly)
{
    xrSpinWait wait(1);

    for (int i = 0; i < 100; ++i)
        wait();

    SUCCEED();
}

TEST(XrSpinWait, ResetAllowsSpinningAgain)
{
    xrSpinWait wait(1);

    // Enter phase 2.
    wait();
    wait();

    wait.reset();

    // Exercise phase 1 again.
    wait();

    SUCCEED();
}

TEST(XrSpinWait, ZeroSpinCountImmediatelyYields)
{
    xrSpinWait wait(0);

    for (int i = 0; i < 10; ++i)
        wait();

    SUCCEED();
}

} // namespace
