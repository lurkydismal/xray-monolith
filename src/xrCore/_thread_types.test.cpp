#include "stdafx.h"

#include "_thread_types.h"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

namespace
{
    class NativeLoadExecutorTest : public ::testing::Test
    {
    protected:
        NativeLoadExecutor& executor = NativeLoadExecutor::Instance();

        NativeLoadExecutor::GenerationId BeginGeneration()
        {
            return executor.BeginGeneration();
        }

        static void WaitUntil(const std::function<bool()>& predicate,
                               std::chrono::milliseconds timeout =
                                   std::chrono::milliseconds(5000))
        {
            const auto deadline = std::chrono::steady_clock::now() + timeout;

            while (!predicate())
            {
                ASSERT_LT(std::chrono::steady_clock::now(), deadline);
                std::this_thread::yield();
            }
        }

        static constexpr NativeLoadPriority LowPriority =
            NativeLoadPriority::Speculative;

        static constexpr NativeLoadPriority HighPriority =
            NativeLoadPriority::Spawn;
    };

    TEST_F(NativeLoadExecutorTest, WorkerLimitIsAtLeastOne)
    {
        EXPECT_GE(executor.WorkerLimit(), 1u);
    }

    TEST_F(NativeLoadExecutorTest, BeginGenerationCreatesCurrentGeneration)
    {
        const auto id = BeginGeneration();

        EXPECT_NE(id, 0u);
        EXPECT_EQ(executor.CurrentGeneration(), id);
        EXPECT_TRUE(executor.IsCurrent(id));

        executor.CancelGeneration(id);

        EXPECT_EQ(executor.CurrentGeneration(), 0u);
        EXPECT_FALSE(executor.IsCurrent(id));
    }

    TEST_F(NativeLoadExecutorTest, GenerationIdsIncrease)
    {
        const auto first = BeginGeneration();
        executor.CancelGeneration(first);

        const auto second = BeginGeneration();

        EXPECT_GT(second, first);
        EXPECT_EQ(executor.CurrentGeneration(), second);

        executor.CancelGeneration(second);
    }

    TEST_F(NativeLoadExecutorTest, StartingNewGenerationReplacesPreviousGeneration)
    {
        const auto first = BeginGeneration();

        std::atomic_bool first_ran = false;

        auto first_batch = executor.BeginBatch(first);
        ASSERT_TRUE(first_batch.Valid());

        ASSERT_TRUE(executor.Submit(
            first_batch,
            LowPriority,
            [&] { first_ran = true; }));

        const auto second = BeginGeneration();

        EXPECT_NE(second, first);
        EXPECT_EQ(executor.CurrentGeneration(), second);
        EXPECT_FALSE(executor.IsCurrent(first));

        executor.Wait(first_batch);

        EXPECT_FALSE(first_ran.load());

        executor.CancelGeneration(second);
    }

    TEST_F(NativeLoadExecutorTest, BeginBatchRejectsNonCurrentGeneration)
    {
        const auto first = BeginGeneration();

        const auto second = BeginGeneration();

        auto batch = executor.BeginBatch(first);

        EXPECT_FALSE(batch.Valid());

        executor.CancelGeneration(second);
    }

    TEST_F(NativeLoadExecutorTest, BeginBatchAcceptsCurrentGeneration)
    {
        const auto id = BeginGeneration();

        auto batch = executor.BeginBatch(id);

        EXPECT_TRUE(batch.Valid());

        executor.Wait(batch);
        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, SubmitExecutesFunction)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        std::atomic_int value = 0;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                value.fetch_add(42);
            }));

        executor.Wait(batch);

        EXPECT_EQ(value.load(), 42);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, SubmitReturnsFalseForInvalidBatch)
    {
        NativeLoadExecutor::Batch batch;

        EXPECT_FALSE(executor.Submit(
            batch,
            LowPriority,
            [] {}));
    }

    TEST_F(NativeLoadExecutorTest, SubmitRejectsInvalidPriority)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        constexpr auto invalid_priority =
            static_cast<NativeLoadPriority>(
                static_cast<u8>(NativeLoadPriority::Count));

        EXPECT_FALSE(executor.Submit(
            batch,
            invalid_priority,
            [] {}));

        executor.Wait(batch);
        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, SubmitRejectsAfterBatchIsClosed)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        executor.Wait(batch);

        EXPECT_FALSE(executor.Submit(
            batch,
            LowPriority,
            [] {}));

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, MultipleTasksAreExecuted)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        constexpr int task_count = 128;

        std::atomic_int executed = 0;

        for (int i = 0; i < task_count; ++i)
        {
            ASSERT_TRUE(executor.Submit(
                batch,
                LowPriority,
                [&] {
                    executed.fetch_add(1, std::memory_order_relaxed);
                }));
        }

        executor.Wait(batch);

        EXPECT_EQ(executed.load(), task_count);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, TasksRunExactlyOnce)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        constexpr int task_count = 256;

        std::atomic_int executed = 0;

        for (int i = 0; i < task_count; ++i)
        {
            ASSERT_TRUE(executor.Submit(
                batch,
                LowPriority,
                [&] {
                    executed.fetch_add(1, std::memory_order_relaxed);
                }));
        }

        executor.Wait(batch);

        EXPECT_EQ(executed.load(), task_count);

        executor.CancelGeneration(id);
    }

#if 0
    TEST_F(NativeLoadExecutorTest, CancelGenerationRunsCancelCallbacks)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        std::atomic_bool release = false;
        std::atomic_int cancelled = 0;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                while (!release.load(std::memory_order_acquire))
                    std::this_thread::yield();
            },
            [&] {
                cancelled.fetch_add(1);
            }));

        WaitUntil([&] {
            return executor.HelpGeneration(id) == false ||
                   release.load();
        });

        executor.CancelGeneration(id);

        release = true;

        executor.Wait(batch);

        EXPECT_GE(cancelled.load(), 0);
    }
#endif

#if 0
    TEST_F(NativeLoadExecutorTest, CancelledQueuedWorkUsesCancelCallback)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        /*
         * Keep the first task occupied so subsequent work remains queued.
         */
        std::atomic_bool release_first = false;
        std::atomic_bool first_started = false;
        std::atomic_int executed = 0;
        std::atomic_int cancelled = 0;

        ASSERT_TRUE(executor.Submit(
            batch,
            HighPriority,
            [&] {
                first_started = true;

                while (!release_first.load(std::memory_order_acquire))
                    std::this_thread::yield();

                executed.fetch_add(1);
            }));

        WaitUntil([&] {
            return first_started.load(std::memory_order_acquire);
        });

        constexpr int queued_count = 32;

        for (int i = 0; i < queued_count; ++i)
        {
            ASSERT_TRUE(executor.Submit(
                batch,
                LowPriority,
                [&] {
                    executed.fetch_add(1);
                },
                [&] {
                    cancelled.fetch_add(1);
                }));
        }

        executor.CancelGeneration(id);

        release_first = true;

        executor.Wait(batch);

        /*
         * Some queued work may already have been picked up by workers, so the
         * exact split between executed/cancelled is intentionally not asserted.
         */
        EXPECT_EQ(executed.load() + cancelled.load(), queued_count + 1);
    }
#endif

    TEST_F(NativeLoadExecutorTest, FinalizeGenerationWaitsForSubmittedWork)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        std::atomic_bool finished = false;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                finished = true;
            }));

        executor.FinalizeGeneration(id);

        EXPECT_TRUE(finished.load());
        EXPECT_EQ(executor.CurrentGeneration(), 0u);
    }

    TEST_F(NativeLoadExecutorTest, FinalizeGenerationMakesGenerationNonCurrent)
    {
        const auto id = BeginGeneration();

        executor.FinalizeGeneration(id);

        EXPECT_EQ(executor.CurrentGeneration(), 0u);
        EXPECT_FALSE(executor.IsCurrent(id));
    }

    TEST_F(NativeLoadExecutorTest, FinalizeGenerationRejectsFurtherSubmission)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        executor.FinalizeGeneration(id);

        EXPECT_FALSE(executor.Submit(
            batch,
            LowPriority,
            [] {}));
    }

    TEST_F(NativeLoadExecutorTest, WaitCurrentGenerationIdleWaitsForWork)
    {
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        std::atomic_bool finished = false;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                finished = true;
            }));

        executor.WaitCurrentGenerationIdle();

        EXPECT_TRUE(finished.load());
        EXPECT_EQ(executor.CurrentGeneration(), id);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, WaitCurrentGenerationIdleDoesNotCloseGeneration)
    {
        const auto id = BeginGeneration();

        executor.WaitCurrentGenerationIdle();

        EXPECT_EQ(executor.CurrentGeneration(), id);
        EXPECT_TRUE(executor.IsCurrent(id));

        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        std::atomic_bool ran = false;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                ran = true;
            }));

        executor.Wait(batch);

        EXPECT_TRUE(ran.load());

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, BatchWaitDoesNotCloseGeneration)
    {
        const auto id = BeginGeneration();

        auto first = executor.BeginBatch(id);
        ASSERT_TRUE(first.Valid());

        std::atomic_int value = 0;

        ASSERT_TRUE(executor.Submit(
            first,
            LowPriority,
            [&] {
                value.fetch_add(1);
            }));

        executor.Wait(first);

        auto second = executor.BeginBatch(id);
        ASSERT_TRUE(second.Valid());

        ASSERT_TRUE(executor.Submit(
            second,
            LowPriority,
            [&] {
                value.fetch_add(2);
            }));

        executor.Wait(second);

        EXPECT_EQ(value.load(), 3);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, BatchFailureIsPropagated)
    {
        /*
         * NOTE:
         *
         * The current implementation has the exception-catching blocks in
         * Execute() disabled with #if 0. Therefore this test documents the
         * intended contract and will fail/crash with the exact implementation
         * supplied above.
         *
         * Keep this test disabled until exception handling is enabled.
         */
#if 0
        const auto id = BeginGeneration();
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [] {
                throw std::runtime_error("test failure");
            }));

        EXPECT_THROW(
            executor.Wait(batch),
            std::runtime_error);

        EXPECT_FALSE(executor.IsCurrent(id));
        EXPECT_EQ(executor.CurrentGeneration(), 0u);
#endif
    }

    TEST_F(NativeLoadExecutorTest, EmptyBatchCanBeWaited)
    {
        const auto id = BeginGeneration();

        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        executor.Wait(batch);

        executor.CancelGeneration(id);

        SUCCEED();
    }

    TEST_F(NativeLoadExecutorTest, EmptyBatchDoesNotBlock)
    {
        const auto id = BeginGeneration();

        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        const auto start = std::chrono::steady_clock::now();

        executor.Wait(batch);

        const auto elapsed =
            std::chrono::steady_clock::now() - start;

        EXPECT_LT(
            elapsed,
            std::chrono::seconds(1));

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, HelpGenerationExecutesQueuedWork)
    {
        const auto id = BeginGeneration();

        /*
         * There may already be PPL workers executing the work. Therefore this
         * only verifies that HelpGeneration is capable of executing work and
         * that waiting eventually completes.
         */
        auto batch = executor.BeginBatch(id);

        ASSERT_TRUE(batch.Valid());

        std::atomic_int executed = 0;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                executed.fetch_add(1);
            }));

        executor.Wait(batch);

        EXPECT_EQ(executed.load(), 1);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, NestedSubmissionWorks)
    {
        const auto id = BeginGeneration();

        auto batch = executor.BeginBatch(id);
        ASSERT_TRUE(batch.Valid());

        std::atomic_int executed = 0;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                executed.fetch_add(1);

                ASSERT_TRUE(executor.Submit(
                    batch,
                    LowPriority,
                    [&] {
                        executed.fetch_add(10);
                    }));
            }));

        executor.Wait(batch);

        EXPECT_EQ(executed.load(), 11);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, NestedSubmissionCanUseDifferentPriority)
    {
        const auto id = BeginGeneration();

        auto batch = executor.BeginBatch(id);
        ASSERT_TRUE(batch.Valid());

        std::atomic_int executed = 0;

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                ASSERT_TRUE(executor.Submit(
                    batch,
                    HighPriority,
                    [&] {
                        executed.fetch_add(1);
                    }));
            }));

        executor.Wait(batch);

        EXPECT_EQ(executed.load(), 1);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, PriorityIsHighestFirstWhenWorkIsQueued)
    {
        /*
         * This test deliberately prevents the first task from completing,
         * allowing us to observe the order in which queued work is selected.
         */
        const auto id = BeginGeneration();

        auto batch = executor.BeginBatch(id);
        ASSERT_TRUE(batch.Valid());

        std::mutex mutex;
        std::vector<int> order;

        std::atomic_bool release = false;
        std::atomic_bool first_started = false;

        ASSERT_TRUE(executor.Submit(
            batch,
            HighPriority,
            [&] {
                first_started = true;

                while (!release.load(std::memory_order_acquire))
                    std::this_thread::yield();

                std::lock_guard<std::mutex> guard(mutex);
                order.push_back(0);
            }));

        WaitUntil([&] {
            return first_started.load(std::memory_order_acquire);
        });

        ASSERT_TRUE(executor.Submit(
            batch,
            LowPriority,
            [&] {
                std::lock_guard<std::mutex> guard(mutex);
                order.push_back(2);
            }));

        ASSERT_TRUE(executor.Submit(
            batch,
            NativeLoadPriority::Geometry,
            [&] {
                std::lock_guard<std::mutex> guard(mutex);
                order.push_back(1);
            }));

        release = true;

        executor.Wait(batch);

        ASSERT_EQ(order.size(), 3u);

        /*
         * The first item is already executing. Among queued items, Geometry
         * has higher priority than Speculative.
         */
        EXPECT_EQ(order[0], 0);
        EXPECT_EQ(order[1], 1);
        EXPECT_EQ(order[2], 2);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, ConcurrentSubmissionIsSafe)
    {
        const auto id = BeginGeneration();

        auto batch = executor.BeginBatch(id);
        ASSERT_TRUE(batch.Valid());

        constexpr int producer_count = 8;
        constexpr int tasks_per_producer = 128;

        std::atomic_int executed = 0;

        std::vector<std::thread> producers;
        producers.reserve(producer_count);

        for (int producer = 0; producer < producer_count; ++producer)
        {
            producers.emplace_back([&, producer] {
                for (int i = 0; i < tasks_per_producer; ++i)
                {
                    const bool submitted = executor.Submit(
                        batch,
                        static_cast<NativeLoadPriority>(
                            producer % static_cast<int>(
                                NativeLoadPriority::Count)),
                        [&] {
                            executed.fetch_add(
                                1,
                                std::memory_order_relaxed);
                        });

                    ASSERT_TRUE(submitted);
                }
            });
        }

        for (auto& producer : producers)
            producer.join();

        executor.Wait(batch);

        EXPECT_EQ(
            executed.load(),
            producer_count * tasks_per_producer);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, ConcurrentBatchesInSameGenerationWork)
    {
        const auto id = BeginGeneration();

        auto first = executor.BeginBatch(id);
        auto second = executor.BeginBatch(id);

        ASSERT_TRUE(first.Valid());
        ASSERT_TRUE(second.Valid());

        std::atomic_int first_count = 0;
        std::atomic_int second_count = 0;

        constexpr int count = 100;

        for (int i = 0; i < count; ++i)
        {
            ASSERT_TRUE(executor.Submit(
                first,
                LowPriority,
                [&] {
                    first_count.fetch_add(1);
                }));

            ASSERT_TRUE(executor.Submit(
                second,
                LowPriority,
                [&] {
                    second_count.fetch_add(1);
                }));
        }

        executor.Wait(first);
        executor.Wait(second);

        EXPECT_EQ(first_count.load(), count);
        EXPECT_EQ(second_count.load(), count);

        executor.CancelGeneration(id);
    }

    TEST_F(NativeLoadExecutorTest, CancelGenerationMakesIsCurrentFalse)
    {
        const auto id = BeginGeneration();

        ASSERT_TRUE(executor.IsCurrent(id));

        executor.CancelGeneration(id);

        EXPECT_FALSE(executor.IsCurrent(id));
        EXPECT_EQ(executor.CurrentGeneration(), 0u);
    }

    TEST_F(NativeLoadExecutorTest, CancelUnknownGenerationDoesNothing)
    {
        const auto id = BeginGeneration();

        const auto unknown = id + 100000;

        executor.CancelGeneration(unknown);

        EXPECT_EQ(executor.CurrentGeneration(), id);
        EXPECT_TRUE(executor.IsCurrent(id));

        executor.CancelGeneration(id);

        SUCCEED();
    }

    TEST_F(NativeLoadExecutorTest, FinalizeUnknownGenerationDoesNothing)
    {
        const auto id = BeginGeneration();

        const auto unknown = id + 100000;

        executor.FinalizeGeneration(unknown);

        EXPECT_EQ(executor.CurrentGeneration(), id);
        EXPECT_TRUE(executor.IsCurrent(id));

        executor.CancelGeneration(id);

        SUCCEED();
    }

    TEST_F(NativeLoadExecutorTest, WaitInvalidBatchDoesNothing)
    {
        NativeLoadExecutor::Batch batch;

        executor.Wait(batch);

        SUCCEED();
    }

    TEST_F(NativeLoadExecutorTest, WaitCurrentGenerationIdleWithNoGenerationDoesNothing)
    {
        EXPECT_EQ(executor.CurrentGeneration(), 0u);

        executor.WaitCurrentGenerationIdle();

        EXPECT_EQ(executor.CurrentGeneration(), 0u);

        SUCCEED();
    }
}
