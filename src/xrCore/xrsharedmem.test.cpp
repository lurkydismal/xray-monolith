#include "stdafx.h"

#include "xrsharedmem.h"

#include <gtest/gtest.h>

#include <array>
#include <cstring>
#include <type_traits>

namespace
{

class SharedMemoryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // ref_smem::create() uses this global.
        g_pSharedMemoryContainer = &container;
    }

    void TearDown() override
    {
        // Remove all entries whose references have reached zero.
        container.clean();

        g_pSharedMemoryContainer = nullptr;
    }

    smem_container container;
};


// -----------------------------------------------------------------------------
// smem_sort
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, SmemSortOrdersByCrc)
{
    smem_value a{};
    smem_value b{};

    a.dwCRC = 10;
    a.dwLength = 1;

    b.dwCRC = 20;
    b.dwLength = 1;

    EXPECT_TRUE(smem_sort(&a, &b));
    EXPECT_FALSE(smem_sort(&b, &a));
}

TEST_F(SharedMemoryTest, SmemSortOrdersByLengthWhenCrcMatches)
{
    const u8 value_a[] = {'a'};
    const u8 value_b[] = {'a', 'b'};

    struct TestValue
    {
        smem_value header;
        u8 data[2];
    };

    TestValue a{};
    TestValue b{};

    a.header.dwCRC = 100;
    a.header.dwLength = 1;
    std::memcpy(a.header.value, value_a, sizeof(value_a));

    b.header.dwCRC = 100;
    b.header.dwLength = 2;
    std::memcpy(b.header.value, value_b, sizeof(value_b));

    EXPECT_TRUE(smem_sort(&a.header, &b.header));
    EXPECT_FALSE(smem_sort(&b.header, &a.header));
}

TEST_F(SharedMemoryTest, SmemSortUsesValueWhenCrcAndLengthMatch)
{
    struct TestValue
    {
        smem_value header;
        u8 data[3];
    };

    TestValue a{};
    TestValue b{};

    a.header.dwCRC = 100;
    a.header.dwLength = 3;
    a.data[0] = 'a';
    a.data[1] = 'b';
    a.data[2] = 'c';

    b.header.dwCRC = 100;
    b.header.dwLength = 3;
    b.data[0] = 'a';
    b.data[1] = 'd';
    b.data[2] = 'c';

    EXPECT_TRUE(smem_sort(&a.header, &b.header));
    EXPECT_FALSE(smem_sort(&b.header, &a.header));
}

TEST_F(SharedMemoryTest, SmemSortReturnsFalseForEqualValues)
{
    struct TestValue
    {
        smem_value header;
        u8 data[3];
    };

    TestValue a{};
    TestValue b{};

    a.header.dwCRC = 100;
    a.header.dwLength = 3;
    std::memcpy(a.data, "abc", 3);

    b.header.dwCRC = 100;
    b.header.dwLength = 3;
    std::memcpy(b.data, "abc", 3);

    EXPECT_FALSE(smem_sort(&a.header, &b.header));
    EXPECT_FALSE(smem_sort(&b.header, &a.header));
}


// -----------------------------------------------------------------------------
// smem_search
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, SmemSearchOrdersByCrc)
{
    smem_value a{};
    smem_value b{};

    a.dwCRC = 10;
    a.dwLength = 100;

    b.dwCRC = 20;
    b.dwLength = 1;

    EXPECT_TRUE(smem_search(&a, &b));
    EXPECT_FALSE(smem_search(&b, &a));
}

TEST_F(SharedMemoryTest, SmemSearchOrdersByLengthWhenCrcMatches)
{
    smem_value a{};
    smem_value b{};

    a.dwCRC = 100;
    a.dwLength = 10;

    b.dwCRC = 100;
    b.dwLength = 20;

    EXPECT_TRUE(smem_search(&a, &b));
    EXPECT_FALSE(smem_search(&b, &a));
}

TEST_F(SharedMemoryTest, SmemSearchIgnoresValue)
{
    struct TestValue
    {
        smem_value header;
        u8 data[3];
    };

    TestValue a{};
    TestValue b{};

    a.header.dwCRC = 100;
    a.header.dwLength = 3;
    std::memcpy(a.data, "abc", 3);

    b.header.dwCRC = 100;
    b.header.dwLength = 3;
    std::memcpy(b.data, "xyz", 3);

    // Same CRC and length means neither is less according to smem_search.
    EXPECT_FALSE(smem_search(&a.header, &b.header));
    EXPECT_FALSE(smem_search(&b.header, &a.header));
}


// -----------------------------------------------------------------------------
// smem_equal
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, SmemEqualReturnsTrueForIdenticalValue)
{
    struct TestValue
    {
        smem_value header;
        u8 data[5];
    };

    TestValue value{};

    value.header.dwCRC = 1234;
    value.header.dwLength = 5;
    std::memcpy(value.data, "hello", 5);

    EXPECT_TRUE(
        smem_equal(
            &value.header,
            1234,
            5,
            value.data
        )
    );
}

TEST_F(SharedMemoryTest, SmemEqualRejectsDifferentCrc)
{
    struct TestValue
    {
        smem_value header;
        u8 data[5];
    };

    TestValue value{};

    value.header.dwCRC = 1234;
    value.header.dwLength = 5;
    std::memcpy(value.data, "hello", 5);

    EXPECT_FALSE(
        smem_equal(
            &value.header,
            5678,
            5,
            value.data
        )
    );
}

TEST_F(SharedMemoryTest, SmemEqualRejectsDifferentLength)
{
    struct TestValue
    {
        smem_value header;
        u8 data[5];
    };

    TestValue value{};

    value.header.dwCRC = 1234;
    value.header.dwLength = 5;
    std::memcpy(value.data, "hello", 5);

    EXPECT_FALSE(
        smem_equal(
            &value.header,
            1234,
            4,
            value.data
        )
    );
}

TEST_F(SharedMemoryTest, SmemEqualRejectsDifferentValue)
{
    struct TestValue
    {
        smem_value header;
        u8 data[5];
    };

    TestValue value{};

    value.header.dwCRC = 1234;
    value.header.dwLength = 5;
    std::memcpy(value.data, "hello", 5);

    const u8 different[] = {'h', 'e', 'l', 'p', 'o'};

    EXPECT_FALSE(
        smem_equal(
            &value.header,
            1234,
            5,
            const_cast<u8*>(different)
        )
    );
}


// -----------------------------------------------------------------------------
// smem_container::dock
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, DockCreatesEntry)
{
    const char value[] = "hello";

    smem_value* result =
        container.dock(1234, sizeof(value), const_cast<char*>(value));

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->dwCRC, 1234u);
    EXPECT_EQ(result->dwLength, sizeof(value));
    EXPECT_EQ(result->dwReference.load(std::memory_order_relaxed), 0u);
    EXPECT_EQ(
        std::memcmp(result->value, value, sizeof(value)),
        0
    );
}

TEST_F(SharedMemoryTest, DockDeduplicatesIdenticalValues)
{
    const char value[] = "hello";

    smem_value* first =
        container.dock(1234, sizeof(value), const_cast<char*>(value));

    smem_value* second =
        container.dock(1234, sizeof(value), const_cast<char*>(value));

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    EXPECT_EQ(first, second);
}

TEST_F(SharedMemoryTest, DockDoesNotDeduplicateDifferentCrc)
{
    const char value[] = "hello";

    smem_value* first =
        container.dock(1234, sizeof(value), const_cast<char*>(value));

    smem_value* second =
        container.dock(5678, sizeof(value), const_cast<char*>(value));

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    EXPECT_NE(first, second);
}

TEST_F(SharedMemoryTest, DockDoesNotDeduplicateDifferentLength)
{
    const char value[] = "hello";

    smem_value* first =
        container.dock(
            1234,
            sizeof(value),
            const_cast<char*>(value)
        );

    smem_value* second =
        container.dock(
            1234,
            sizeof(value) - 1,
            const_cast<char*>(value)
        );

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    EXPECT_NE(first, second);
}

TEST_F(SharedMemoryTest, DockDoesNotDeduplicateDifferentValue)
{
    const char first_value[] = "hello";
    const char second_value[] = "world";

    smem_value* first =
        container.dock(
            1234,
            sizeof(first_value),
            const_cast<char*>(first_value)
        );

    smem_value* second =
        container.dock(
            1234,
            sizeof(second_value),
            const_cast<char*>(second_value)
        );

    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    EXPECT_NE(first, second);
}

TEST_F(SharedMemoryTest, DockCopiesInput)
{
    char value[] = "hello";

    smem_value* result =
        container.dock(
            1234,
            sizeof(value),
            value
        );

    ASSERT_NE(result, nullptr);

    value[0] = 'X';

    EXPECT_EQ(
        std::memcmp(result->value, "hello", sizeof(value)),
        0
    );
}


// -----------------------------------------------------------------------------
// ref_smem construction
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, DefaultRefSmemIsEmpty)
{
    ref_smem<char> value;

    EXPECT_TRUE(!value);
    EXPECT_EQ(value._get(), nullptr);
    EXPECT_EQ(value.size(), 0u);
    EXPECT_EQ(value.ref_count(), 0u);
}

TEST_F(SharedMemoryTest, CreateStoresValue)
{
    const char value[] = "hello";

    ref_smem<char> shared;
    shared.create(1234, sizeof(value), const_cast<char*>(value));

    ASSERT_FALSE(!shared);
    ASSERT_NE(shared._get(), nullptr);

    EXPECT_EQ(shared._get()->dwCRC, 1234u);
    EXPECT_EQ(shared._get()->dwLength, sizeof(value));
    EXPECT_EQ(shared.size(), sizeof(value));
    EXPECT_EQ(shared.ref_count(), 1u);

    EXPECT_EQ(
        std::memcmp(*shared, value, sizeof(value)),
        0
    );
}

TEST_F(SharedMemoryTest, CreateCopiesValue)
{
    char value[] = "hello";

    ref_smem<char> shared;
    shared.create(1234, sizeof(value), value);

    ASSERT_FALSE(!shared);

    value[0] = 'X';

    EXPECT_STREQ(
        static_cast<const char*>(*shared),
        "hello"
    );
}


// -----------------------------------------------------------------------------
// ref_smem reference counting
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, CopyConstructionIncrementsReferenceCount)
{
    const char value[] = "hello";

    ref_smem<char> first;
    first.create(1234, sizeof(value), const_cast<char*>(value));

    ASSERT_EQ(first.ref_count(), 1u);

    {
        ref_smem<char> second(first);

        EXPECT_EQ(first.ref_count(), 2u);
        EXPECT_EQ(second.ref_count(), 2u);
        EXPECT_EQ(first, second);
    }

    EXPECT_EQ(first.ref_count(), 1u);
}

TEST_F(SharedMemoryTest, AssignmentIncrementsReferenceCount)
{
    const char value[] = "hello";

    ref_smem<char> first;
    first.create(1234, sizeof(value), const_cast<char*>(value));

    ref_smem<char> second;

    second = first;

    EXPECT_EQ(first.ref_count(), 2u);
    EXPECT_EQ(second.ref_count(), 2u);
    EXPECT_EQ(first, second);
}

TEST_F(SharedMemoryTest, AssignmentReleasesPreviousValue)
{
    const char first_value[] = "first";
    const char second_value[] = "second";

    ref_smem<char> first;
    first.create(
        1,
        sizeof(first_value),
        const_cast<char*>(first_value)
    );

    ref_smem<char> second;
    second.create(
        2,
        sizeof(second_value),
        const_cast<char*>(second_value)
    );

    ASSERT_EQ(first.ref_count(), 1u);
    ASSERT_EQ(second.ref_count(), 1u);

    second = first;

    EXPECT_EQ(first.ref_count(), 2u);
    EXPECT_EQ(second.ref_count(), 2u);
    EXPECT_EQ(first, second);
}

TEST_F(SharedMemoryTest, MultipleCopiesShareSameStorage)
{
    const char value[] = "shared";

    ref_smem<char> first;
    first.create(
        1234,
        sizeof(value),
        const_cast<char*>(value)
    );

    ref_smem<char> second(first);
    ref_smem<char> third(second);

    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
    EXPECT_EQ(first, third);

    EXPECT_EQ(first.ref_count(), 3u);
    EXPECT_EQ(second.ref_count(), 3u);
    EXPECT_EQ(third.ref_count(), 3u);
}

TEST_F(SharedMemoryTest, DifferentValuesAreNotEqual)
{
    const char first_value[] = "first";
    const char second_value[] = "second";

    ref_smem<char> first;
    ref_smem<char> second;

    first.create(
        1,
        sizeof(first_value),
        const_cast<char*>(first_value)
    );

    second.create(
        2,
        sizeof(second_value),
        const_cast<char*>(second_value)
    );

    EXPECT_NE(first, second);
    EXPECT_NE(first._get(), second._get());
}

TEST_F(SharedMemoryTest, EmptyRefSmemValuesCompareEqual)
{
    ref_smem<char> first;
    ref_smem<char> second;

    EXPECT_EQ(first, second);
    EXPECT_FALSE(first != second);
}

TEST_F(SharedMemoryTest, EmptyAndNonEmptyValuesCompareDifferent)
{
    const char value[] = "hello";

    ref_smem<char> empty;
    ref_smem<char> non_empty;

    non_empty.create(
        1234,
        sizeof(value),
        const_cast<char*>(value)
    );

    EXPECT_NE(empty, non_empty);
    EXPECT_NE(non_empty, empty);
}


// -----------------------------------------------------------------------------
// ref_smem access
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, DereferenceReturnsStoredData)
{
    const char value[] = "hello";

    ref_smem<char> shared;
    shared.create(
        1234,
        sizeof(value),
        const_cast<char*>(value)
    );

    ASSERT_FALSE(!shared);

    EXPECT_EQ(
        std::memcmp(*shared, value, sizeof(value)),
        0
    );
}

TEST_F(SharedMemoryTest, SubscriptProvidesMutableAccess)
{
    char value[] = {'a', 'b', 'c', 'd'};

    ref_smem<char> shared;
    shared.create(
        1234,
        sizeof(value),
        value
    );

    ASSERT_EQ(shared.size(), 4u);

    EXPECT_EQ(shared[0], 'a');
    EXPECT_EQ(shared[1], 'b');
    EXPECT_EQ(shared[2], 'c');
    EXPECT_EQ(shared[3], 'd');

    shared[1] = 'X';

    EXPECT_EQ(shared[1], 'X');
}

TEST_F(SharedMemoryTest, ConstSubscriptProvidesReadAccess)
{
    char value[] = {'a', 'b', 'c'};

    ref_smem<char> shared;
    shared.create(
        1234,
        sizeof(value),
        value
    );

    const ref_smem<char>& const_shared = shared;

    EXPECT_EQ(const_shared[0], 'a');
    EXPECT_EQ(const_shared[1], 'b');
    EXPECT_EQ(const_shared[2], 'c');
}

TEST_F(SharedMemoryTest, SizeReturnsElementCountForTypedData)
{
    std::array<u32, 4> value = {10, 20, 30, 40};

    ref_smem<u32> shared;
    shared.create(
        1234,
        static_cast<u32>(value.size()),
        value.data()
    );

    EXPECT_EQ(shared.size(), value.size());
}

TEST_F(SharedMemoryTest, TypedAccessPreservesValues)
{
    std::array<u32, 4> value = {10, 20, 30, 40};

    ref_smem<u32> shared;
    shared.create(
        1234,
        static_cast<u32>(value.size()),
        value.data()
    );

    EXPECT_EQ(shared[0], 10u);
    EXPECT_EQ(shared[1], 20u);
    EXPECT_EQ(shared[2], 30u);
    EXPECT_EQ(shared[3], 40u);
}


// -----------------------------------------------------------------------------
// swap
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, SwapExchangesValues)
{
    const char first_value[] = "first";
    const char second_value[] = "second";

    ref_smem<char> first;
    ref_smem<char> second;

    first.create(
        1,
        sizeof(first_value),
        const_cast<char*>(first_value)
    );

    second.create(
        2,
        sizeof(second_value),
        const_cast<char*>(second_value)
    );

    const smem_value* first_ptr = first._get();
    const smem_value* second_ptr = second._get();

    first.swap(second);

    EXPECT_EQ(first._get(), second_ptr);
    EXPECT_EQ(second._get(), first_ptr);

    EXPECT_EQ(first.ref_count(), 1u);
    EXPECT_EQ(second.ref_count(), 1u);

    EXPECT_STREQ(
        static_cast<const char*>(*first),
        "second"
    );

    EXPECT_STREQ(
        static_cast<const char*>(*second),
        "first"
    );
}

TEST_F(SharedMemoryTest, StdSwapExchangesValues)
{
    const char first_value[] = "first";
    const char second_value[] = "second";

    ref_smem<char> first;
    ref_smem<char> second;

    first.create(
        1,
        sizeof(first_value),
        const_cast<char*>(first_value)
    );

    second.create(
        2,
        sizeof(second_value),
        const_cast<char*>(second_value)
    );

    const smem_value* first_ptr = first._get();
    const smem_value* second_ptr = second._get();

    swap(first, second);

    EXPECT_EQ(first._get(), second_ptr);
    EXPECT_EQ(second._get(), first_ptr);
}


// -----------------------------------------------------------------------------
// Container cleanup / reference ownership
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, CleanKeepsReferencedEntry)
{
    const char value[] = "hello";

    ref_smem<char> shared;
    shared.create(
        1234,
        sizeof(value),
        const_cast<char*>(value)
    );

    const smem_value* original = shared._get();

    container.clean();

    EXPECT_EQ(shared._get(), original);
    EXPECT_EQ(shared.ref_count(), 1u);

    EXPECT_STREQ(
        static_cast<const char*>(*shared),
        "hello"
    );
}

TEST_F(SharedMemoryTest, ReleasedEntryCanBeCleaned)
{
    const char value[] = "hello";

    smem_value* entry =
        container.dock(
            1234,
            sizeof(value),
            const_cast<char*>(value)
        );

    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->dwReference.load(std::memory_order_relaxed), 0u);

    // Entry is unreferenced and should be removed by clean().
    container.clean();

    // Docking the same value creates a new entry after cleanup.
    smem_value* new_entry =
        container.dock(
            1234,
            sizeof(value),
            const_cast<char*>(value)
        );

    ASSERT_NE(new_entry, nullptr);
    EXPECT_NE(new_entry, entry);
}

TEST_F(SharedMemoryTest, ReferencedEntryIsDeduplicatedAfterClean)
{
    const char value[] = "hello";

    ref_smem<char> first;
    first.create(
        1234,
        sizeof(value),
        const_cast<char*>(value)
    );

    const smem_value* original = first._get();

    container.clean();

    ref_smem<char> second;
    second.create(
        1234,
        sizeof(value),
        const_cast<char*>(value)
    );

    EXPECT_EQ(second._get(), original);
    EXPECT_EQ(first, second);
    EXPECT_EQ(first.ref_count(), 2u);
}


// -----------------------------------------------------------------------------
// Ordering operators
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, LessOperatorComparesUnderlyingPointer)
{
    const char value[] = "hello";

    ref_smem<char> first;
    ref_smem<char> second;

    first.create(
        1,
        sizeof(value),
        const_cast<char*>(value)
    );

    second.create(
        2,
        sizeof(value),
        const_cast<char*>(value)
    );

    const auto* first_ptr = first._get();
    const auto* second_ptr = second._get();

    EXPECT_EQ(first < second, first_ptr < second_ptr);
}

TEST_F(SharedMemoryTest, GreaterOperatorComparesUnderlyingPointer)
{
    const char value[] = "hello";

    ref_smem<char> first;
    ref_smem<char> second;

    first.create(
        1,
        sizeof(value),
        const_cast<char*>(value)
    );

    second.create(
        2,
        sizeof(value),
        const_cast<char*>(value)
    );

    const auto* first_ptr = first._get();
    const auto* second_ptr = second._get();

    EXPECT_EQ(first > second, first_ptr > second_ptr);
}


// -----------------------------------------------------------------------------
// stat_economy
// -----------------------------------------------------------------------------

TEST_F(SharedMemoryTest, StatEconomyCanBeCalledOnEmptyContainer)
{
    {
        container.stat_economy();
    };

    SUCCEED();
}

TEST_F(SharedMemoryTest, StatEconomyCanBeCalledWithEntry)
{
    const char value[] = "hello";

    ref_smem<char> shared;
    shared.create(
        1234,
        sizeof(value),
        const_cast<char*>(value)
    );

    {
        container.stat_economy();
    };

    SUCCEED();
}

} // namespace
