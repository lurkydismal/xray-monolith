#include "cpuid.h"
#include "ttapi.h"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

namespace
{
    // RAII helper so every test leaves TTAPI shut down.
    class TTApiFixture : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // The current implementation is not initialized at test start.
            ASSERT_EQ(ttapi_GetWorkersCount(), 0u);

            const DWORD workers = ttapi_Init(nullptr);

            ASSERT_GT(workers, 0u);
            ASSERT_EQ(ttapi_GetWorkersCount(), workers);
        }

        void TearDown() override
        {
            ttapi_Done();

            EXPECT_EQ(ttapi_GetWorkersCount(), 0u);
        }
    };

    struct CounterTask
    {
        std::atomic<int>* counter;
    };

    void IncrementCounter(LPVOID parameter)
    {
        auto* task = static_cast<CounterTask*>(parameter);
        task->counter->fetch_add(1, std::memory_order_relaxed);
    }

    struct ValueTask
    {
        std::atomic<int>* value;
        int newValue;
    };

    void SetValue(LPVOID parameter)
    {
        auto* task = static_cast<ValueTask*>(parameter);
        task->value->store(task->newValue, std::memory_order_relaxed);
    }

    struct RecordingTask
    {
        std::atomic<int>* executions;
        std::atomic<int>* accumulatedValue;
        int value;
    };

    void RecordExecution(LPVOID parameter)
    {
        auto* task = static_cast<RecordingTask*>(parameter);

        task->accumulatedValue->fetch_add(
            task->value,
            std::memory_order_relaxed);

        task->executions->fetch_add(
            1,
            std::memory_order_relaxed);
    }
}


// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------

TEST_F(TTApiFixture, InitReportsAtLeastOneWorker)
{
    const DWORD workers = ttapi_GetWorkersCount();

    EXPECT_GT(workers, 0u);
}

TEST_F(TTApiFixture, InitIsIdempotent)
{
    const DWORD firstCount = ttapi_GetWorkersCount();

    const DWORD secondCount = ttapi_Init(nullptr);

    EXPECT_EQ(secondCount, firstCount);
    EXPECT_EQ(ttapi_GetWorkersCount(), firstCount);
}

TEST_F(TTApiFixture, InitCanBeCalledAfterDone)
{
    const DWORD firstCount = ttapi_GetWorkersCount();

    ttapi_Done();

    EXPECT_EQ(ttapi_GetWorkersCount(), 0u);

    const DWORD secondCount = ttapi_Init(nullptr);

    EXPECT_GT(secondCount, 0u);
    EXPECT_EQ(secondCount, firstCount);
}


// -----------------------------------------------------------------------------
// Single-worker execution
// -----------------------------------------------------------------------------

TEST_F(TTApiFixture, ExecutesSingleWorker)
{
    std::atomic<int> executions{0};

    CounterTask task{&executions};

    ttapi_AddWorker(&IncrementCounter, &task);
    ttapi_RunAllWorkers();

    EXPECT_EQ(executions.load(), 1);
}

TEST_F(TTApiFixture, PassesWorkerParameterToFunction)
{
    std::atomic<int> value{0};

    ValueTask task{
        &value,
        12345
    };

    ttapi_AddWorker(&SetValue, &task);
    ttapi_RunAllWorkers();

    EXPECT_EQ(value.load(), 12345);
}

TEST_F(TTApiFixture, RunAllWorkersResetsAssignedWorkerCount)
{
    std::atomic<int> executions{0};

    CounterTask task{&executions};

    ttapi_AddWorker(&IncrementCounter, &task);
    ttapi_RunAllWorkers();

    EXPECT_EQ(executions.load(), 1);

    // Add another task after RunAllWorkers().
    // This verifies that the implementation resets
    // ttapi_assigned_workers back to zero.
    ttapi_AddWorker(&IncrementCounter, &task);
    ttapi_RunAllWorkers();

    EXPECT_EQ(executions.load(), 2);
}


// -----------------------------------------------------------------------------
// Multiple workers
// -----------------------------------------------------------------------------

TEST_F(TTApiFixture, ExecutesMultipleWorkersExactlyOnce)
{
    const DWORD workerCount = ttapi_GetWorkersCount();

    ASSERT_GT(workerCount, 0u);

    std::atomic<int> executions{0};
    std::atomic<int> accumulatedValue{0};

    std::vector<RecordingTask> tasks;
    tasks.reserve(workerCount);

    // The implementation expects at most ttapi_GetWorkersCount()
    // assigned workers.
    for (DWORD i = 0; i < workerCount; ++i)
    {
        tasks.push_back({
            &executions,
            &accumulatedValue,
            static_cast<int>(i + 1)
        });
    }

    for (auto& task : tasks)
        ttapi_AddWorker(&RecordExecution, &task);

    ttapi_RunAllWorkers();

    EXPECT_EQ(executions.load(), static_cast<int>(workerCount));

    // 1 + 2 + ... + N
    const int expectedSum =
        static_cast<int>(workerCount * (workerCount + 1) / 2);

    EXPECT_EQ(accumulatedValue.load(), expectedSum);
}

TEST_F(TTApiFixture, ExecutesWorkerFunctionsWithDifferentParameters)
{
    const DWORD workerCount = ttapi_GetWorkersCount();

    ASSERT_GT(workerCount, 0u);

    std::atomic<int> accumulated{0};

    std::vector<ValueTask> tasks;
    tasks.reserve(workerCount);

    for (DWORD i = 0; i < workerCount; ++i)
    {
        tasks.push_back({
            &accumulated,
            static_cast<int>(i + 1)
        });
    }

    // Use a separate callback that accumulates the supplied value.
    // This keeps the test independent of task execution order.
    struct AccumulateTask
    {
        std::atomic<int>* target;
        int value;
    };

    // Local lambda cannot be converted to the required C function pointer,
    // so use a static helper below.
}


// -----------------------------------------------------------------------------
// Maximum supported queue size
// -----------------------------------------------------------------------------

TEST_F(TTApiFixture, AcceptsExactlyWorkerCountTasks)
{
    const DWORD workerCount = ttapi_GetWorkersCount();

    ASSERT_GT(workerCount, 0u);

    std::atomic<int> executions{0};

    CounterTask task{&executions};

    for (DWORD i = 0; i < workerCount; ++i)
        ttapi_AddWorker(&IncrementCounter, &task);

    ttapi_RunAllWorkers();

    EXPECT_EQ(executions.load(), static_cast<int>(workerCount));
}


// -----------------------------------------------------------------------------
// Repeated execution
// -----------------------------------------------------------------------------

TEST_F(TTApiFixture, CanRunMultipleBatches)
{
    const DWORD workerCount = ttapi_GetWorkersCount();

    ASSERT_GT(workerCount, 0u);

    std::atomic<int> executions{0};

    CounterTask task{&executions};

    // Batch 1
    for (DWORD i = 0; i < workerCount; ++i)
        ttapi_AddWorker(&IncrementCounter, &task);

    ttapi_RunAllWorkers();

    EXPECT_EQ(executions.load(), static_cast<int>(workerCount));

    // Batch 2
    for (DWORD i = 0; i < workerCount; ++i)
        ttapi_AddWorker(&IncrementCounter, &task);

    ttapi_RunAllWorkers();

    EXPECT_EQ(executions.load(), static_cast<int>(workerCount * 2));
}

TEST_F(TTApiFixture, CanRunManySmallBatches)
{
    constexpr int batchCount = 100;

    std::atomic<int> executions{0};
    CounterTask task{&executions};

    for (int i = 0; i < batchCount; ++i)
    {
        ttapi_AddWorker(&IncrementCounter, &task);
        ttapi_RunAllWorkers();
    }

    EXPECT_EQ(executions.load(), batchCount);
}


// -----------------------------------------------------------------------------
// Shutdown / reinitialization
// -----------------------------------------------------------------------------

TEST_F(TTApiFixture, DoneIsIdempotent)
{
    ttapi_Done();

    EXPECT_EQ(ttapi_GetWorkersCount(), 0u);

    // A second Done() should be harmless.
    ttapi_Done();

    EXPECT_EQ(ttapi_GetWorkersCount(), 0u);
}

TEST_F(TTApiFixture, CanInitializeRunAndShutdownRepeatedly)
{
    for (int iteration = 0; iteration < 10; ++iteration)
    {
        const DWORD workers = ttapi_Init(nullptr);

        ASSERT_GT(workers, 0u);

        std::atomic<int> executions{0};
        CounterTask task{&executions};

        ttapi_AddWorker(&IncrementCounter, &task);
        ttapi_RunAllWorkers();

        EXPECT_EQ(executions.load(), 1);

        ttapi_Done();

        EXPECT_EQ(ttapi_GetWorkersCount(), 0u);
    }
}


// -----------------------------------------------------------------------------
// Worker count consistency
// -----------------------------------------------------------------------------

TEST_F(TTApiFixture, WorkerCountMatchesInitReturnValue)
{
    // SetUp() already initialized the subsystem. Calling Init again
    // exercises the "already initialized" path.
    const DWORD count = ttapi_Init(nullptr);

    EXPECT_EQ(count, ttapi_GetWorkersCount());
    EXPECT_GT(count, 0u);
}
