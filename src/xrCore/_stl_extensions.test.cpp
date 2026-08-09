#include "stdafx.h"

#include "_stl_extensions.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>
#include <type_traits>
#include <vector>

namespace
{

// -----------------------------------------------------------------------------
// xalloc
// -----------------------------------------------------------------------------

TEST(Xalloc, Traits)
{
    using alloc = xalloc<int>;

    static_assert(std::is_same_v<alloc::value_type, int>);
    static_assert(std::is_same_v<alloc::pointer, int*>);
    static_assert(std::is_same_v<alloc::const_pointer, const int*>);
    static_assert(std::is_same_v<alloc::reference, int&>);
    static_assert(std::is_same_v<alloc::const_reference, const int&>);
    static_assert(std::is_same_v<alloc::size_type, size_t>);
    static_assert(std::is_same_v<alloc::difference_type, ptrdiff_t>);

    static_assert(std::is_same_v<
        typename alloc::template rebind<float>::other,
        xalloc<float>>);

    static_assert(alloc::propagate_on_container_move_assignment::value);
    static_assert(alloc::is_always_equal::value);
}

TEST(Xalloc, AllocateConstructDestroy)
{
    xalloc<int> alloc;

    int* p = alloc.allocate(1);
    ASSERT_NE(p, nullptr);

    alloc.construct(p, 42);
    EXPECT_EQ(*p, 42);

    alloc.destroy(p);
    alloc.deallocate(p, 1);
}

TEST(Xalloc, Equality)
{
    xalloc<int> int_alloc;
    xalloc<float> float_alloc;

    EXPECT_TRUE(int_alloc == int_alloc);
    EXPECT_TRUE(int_alloc == float_alloc);
    EXPECT_FALSE(int_alloc != int_alloc);
    EXPECT_FALSE(int_alloc != float_alloc);
}

TEST(Xalloc, MaxSize)
{
    xalloc<int> alloc;

    EXPECT_GT(alloc.max_size(), 0u);
    EXPECT_EQ(alloc.max_size(), static_cast<size_t>(-1) / sizeof(int));
}


// -----------------------------------------------------------------------------
// xr_array
// -----------------------------------------------------------------------------

TEST(XrArray, IsStdArrayAlias)
{
    static_assert(std::is_same_v<
        xr_array<int, 4>,
        std::array<int, 4>>);

    xr_array<int, 4> a{1, 2, 3, 4};

    EXPECT_EQ(a.size(), 4u);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[3], 4);
}


// -----------------------------------------------------------------------------
// xr_vector
// -----------------------------------------------------------------------------

TEST(XrVector, DefaultConstruction)
{
    xr_vector<int> v;

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
}

TEST(XrVector, CountConstruction)
{
    xr_vector<int> v(5);

    ASSERT_EQ(v.size(), 5u);

    for (int value : v)
        EXPECT_EQ(value, 0);
}

TEST(XrVector, CountValueConstruction)
{
    xr_vector<int> v(5, 42);

    ASSERT_EQ(v.size(), 5u);

    for (int value : v)
        EXPECT_EQ(value, 42);
}

TEST(XrVector, SizeUsesU32)
{
    static_assert(std::is_same_v<
        decltype(std::declval<const xr_vector<int>&>().size()),
        u32>);
}

TEST(XrVector, Indexing)
{
    xr_vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);

    v[1] = 99;

    EXPECT_EQ(v[1], 99);
}

TEST(XrVector, Iteration)
{
    xr_vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::vector<int> result(v.begin(), v.end());

    EXPECT_EQ(result, (std::vector<int>{1, 2, 3}));
}

TEST(XrVector, ClearNotFree)
{
    xr_vector<int> v;

    v.reserve(128);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    ASSERT_GE(v.capacity(), 128u);

    v.clear_not_free();

    EXPECT_TRUE(v.empty());
    EXPECT_GE(v.capacity(), 128u);
}

TEST(XrVector, ClearAndFree)
{
    xr_vector<int> v;

    v.reserve(128);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    ASSERT_GE(v.capacity(), 128u);

    v.clear_and_free();

    EXPECT_TRUE(v.empty());

    // Current implementation uses shrink_to_fit(). The standard does not
    // guarantee a reduction, but with the current implementation this is
    // the intended observable behavior.
    EXPECT_LE(v.capacity(), 128u);
}

TEST(XrVector, ClearUsesClearNotFree)
{
    xr_vector<int> v;

    v.reserve(128);
    v.push_back(1);
    v.push_back(2);

    ASSERT_GE(v.capacity(), 128u);

    v.clear();

    EXPECT_TRUE(v.empty());
    EXPECT_GE(v.capacity(), 128u);
}

TEST(XrVector, ClearAndReserveKeepsLargeCapacity)
{
    xr_vector<int> v;

    v.reserve(128);

    for (int i = 0; i != 10; ++i)
        v.push_back(i);

    const auto old_capacity = v.capacity();

    v.clear_and_reserve();

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.capacity(), old_capacity);
}

TEST(XrVector, ClearAndReserveShrinksAndRestoresOldSize)
{
    xr_vector<int> v;

    v.reserve(1000);

    for (int i = 0; i != 10; ++i)
        v.push_back(i);

    ASSERT_EQ(v.size(), 10u);
    ASSERT_GT(v.capacity(), v.size() + v.size() / 4);

    v.clear_and_reserve();

    EXPECT_TRUE(v.empty());

    // Current implementation:
    //   old = size()
    //   clear_and_free()
    //   reserve(old)
    EXPECT_GE(v.capacity(), 10u);
}

TEST(XrVector, EraseFastLastElement)
{
    xr_vector<int> v{};

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    auto it = v.erase_fast(v.begin() + 2);

    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(it, v.end());
}

TEST(XrVector, EraseFastMiddleElement)
{
    xr_vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    auto it = v.erase_fast(v.begin() + 1);

    EXPECT_EQ(v.size(), 3u);

    // erase_fast does not preserve ordering.
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 40);
    EXPECT_EQ(v[2], 30);

    EXPECT_EQ(it, v.begin() + 1);
}

TEST(XrVector, EraseFastConstIterator)
{
    xr_vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    const auto& cv = v;

    auto it = v.erase_fast(cv.begin() + 1);

    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(it, v.begin() + 1);
}

TEST(XrVector, EraseFastTriviallyMoveAssignable)
{
    struct Item
    {
        int value;

        Item() = default;
        explicit Item(int v) : value(v) {}
    };

    static_assert(std::is_trivially_move_assignable_v<Item>);

    xr_vector<Item> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);

    v.erase_fast(v.begin());

    ASSERT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0].value, 3);
    EXPECT_EQ(v[1].value, 2);
}

#if 0
TEST(XrVector, EraseFastSwappable)
{
    struct Item
    {
        int value;

        Item() = default;
        explicit Item(int v) : value(v) {}

        Item(const Item&) = default;
        Item& operator=(const Item&) = default;

        Item(Item&&) = default;
        Item& operator=(Item&&) = delete;

        friend void swap(Item& a, Item& b) noexcept
        {
            std::swap(a.value, b.value);
        }
    };

    static_assert(!std::is_trivially_move_assignable_v<Item>);
    static_assert(std::is_swappable_v<Item>);

    xr_vector<Item> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);

    v.erase_fast(v.begin());

    ASSERT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0].value, 3);
    EXPECT_EQ(v[1].value, 2);
}
#endif


// -----------------------------------------------------------------------------
// xr_vector<bool>
// -----------------------------------------------------------------------------

TEST(XrVectorBool, BasicOperations)
{
    xr_vector<bool> v;

    EXPECT_TRUE(v.empty());

    v.push_back(false);
    v.push_back(true);
    v.push_back(false);

    ASSERT_EQ(v.size(), 3u);

    EXPECT_FALSE(v[0]);
    EXPECT_TRUE(v[1]);
    EXPECT_FALSE(v[2]);
}

TEST(XrVectorBool, Clear)
{
    xr_vector<bool> v;

    v.push_back(true);
    v.push_back(false);
    v.push_back(true);

    v.clear();

    EXPECT_TRUE(v.empty());
}


// -----------------------------------------------------------------------------
// xr_deque
// -----------------------------------------------------------------------------

TEST(XrDeque, BasicOperations)
{
    xr_deque<int> d;

    EXPECT_TRUE(d.empty());

    d.push_back(2);
    d.push_front(1);
    d.push_back(3);

    ASSERT_EQ(d.size(), 3u);

    EXPECT_EQ(d.front(), 1);
    EXPECT_EQ(d.back(), 3);
}


// -----------------------------------------------------------------------------
// xr_fixedqueue
// -----------------------------------------------------------------------------

TEST(XrFixedQueue, PushKeepsMaximumLength)
{
    xr_fixedqueue<int, 3> q;

    q.push(1);
    q.push(2);
    q.push(3);

    ASSERT_EQ(q.size(), 3u);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);

    q.push(4);

    ASSERT_EQ(q.size(), 3u);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 4);
}

TEST(XrFixedQueue, EmplaceKeepsMaximumLength)
{
    xr_fixedqueue<std::string, 2> q;

    q.emplace("first");
    q.emplace("second");
    q.emplace("third");

    ASSERT_EQ(q.size(), 2u);

    EXPECT_EQ(q.front(), "second");
    EXPECT_EQ(q.back(), "third");
}

TEST(XrFixedQueue, DoesNotPopBeforeMaximum)
{
    xr_fixedqueue<int, 3> q;

    q.push(1);
    q.push(2);

    EXPECT_EQ(q.size(), 2u);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 2);
}


// -----------------------------------------------------------------------------
// xr_stack
// -----------------------------------------------------------------------------

TEST(XrStack, Lifo)
{
    xr_stack<int> stack;

    EXPECT_TRUE(stack.empty());

    stack.push(10);
    stack.push(20);
    stack.push(30);

    ASSERT_EQ(stack.size(), 3u);
    EXPECT_EQ(stack.top(), 30);

    stack.pop();
    EXPECT_EQ(stack.top(), 20);

    stack.pop();
    EXPECT_EQ(stack.top(), 10);

    stack.pop();

    EXPECT_TRUE(stack.empty());
}

TEST(XrStack, Comparison)
{
    xr_stack<int> a;
    xr_stack<int> b;

    a.push(1);
    a.push(2);

    b.push(1);
    b.push(2);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    b.push(3);

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b >= a);
}


// -----------------------------------------------------------------------------
// xr_ordered_map
// -----------------------------------------------------------------------------

TEST(XrOrderedMap, Empty)
{
    xr_ordered_map<int, std::string> map;

    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0u);
    EXPECT_EQ(map.begin(), map.end());
}

TEST(XrOrderedMap, InsertPreservesInsertionOrder)
{
    xr_ordered_map<int, std::string> map;

    map.insert({3, "three"});
    map.insert({1, "one"});
    map.insert({2, "two"});

    ASSERT_EQ(map.size(), 3u);

    auto it = map.begin();

    ASSERT_NE(it, map.end());
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, "three");

    ++it;
    ASSERT_NE(it, map.end());
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, "one");

    ++it;
    ASSERT_NE(it, map.end());
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");

    ++it;
    EXPECT_EQ(it, map.end());
}

TEST(XrOrderedMap, DuplicateInsertDoesNotChangeOrder)
{
    xr_ordered_map<int, std::string> map;

    auto first = map.insert({1, "one"});
    auto duplicate = map.insert({1, "replacement"});

    EXPECT_TRUE(first.second);
    EXPECT_FALSE(duplicate.second);
    EXPECT_EQ(map.size(), 1u);

    EXPECT_EQ(map.begin()->first, 1);
    EXPECT_EQ(map.begin()->second, "one");
}

TEST(XrOrderedMap, DuplicateInsertReturnsExistingIterator)
{
    xr_ordered_map<int, int> map;

    auto first = map.insert({42, 100});
    auto second = map.insert({42, 200});

    EXPECT_EQ(first.first, second.first);
    EXPECT_EQ(second.first->second, 100);
}

TEST(XrOrderedMap, Find)
{
    xr_ordered_map<int, std::string> map;

    map.insert({10, "ten"});
    map.insert({20, "twenty"});

    auto it = map.find(20);

    ASSERT_NE(it, map.end());
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "twenty");

    EXPECT_EQ(map.find(99), map.end());
}

TEST(XrOrderedMap, Count)
{
    xr_ordered_map<int, int> map;

    map.insert({1, 10});

    EXPECT_EQ(map.count(1), 1u);
    EXPECT_EQ(map.count(2), 0u);
}

TEST(XrOrderedMap, At)
{
    xr_ordered_map<int, std::string> map;

    map.insert({1, "one"});

    EXPECT_EQ(map.at(1), "one");

    map.at(1) = "changed";

    EXPECT_EQ(map.at(1), "changed");
}

TEST(XrOrderedMap, OperatorBracketInsertsDefaultValue)
{
    xr_ordered_map<int, int> map;

    int& value = map[42];

    EXPECT_EQ(value, 0);
    EXPECT_EQ(map.size(), 1u);
    EXPECT_EQ(map.begin()->first, 42);
}

TEST(XrOrderedMap, OperatorBracketExistingKeyDoesNotReorder)
{
    xr_ordered_map<int, int> map;

    map[10] = 100;
    map[20] = 200;

    map[10] = 999;

    ASSERT_EQ(map.size(), 2u);

    auto it = map.begin();

    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, 999);

    ++it;
    EXPECT_EQ(it->first, 20);
}

TEST(XrOrderedMap, EraseByKey)
{
    xr_ordered_map<int, std::string> map;

    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    EXPECT_EQ(map.erase(2), 1u);
    EXPECT_EQ(map.erase(2), 0u);

    ASSERT_EQ(map.size(), 2u);

    auto it = map.begin();
    EXPECT_EQ(it->first, 1);

    ++it;
    EXPECT_EQ(it->first, 3);
}

TEST(XrOrderedMap, EraseByIteratorReturnsNext)
{
    xr_ordered_map<int, int> map;

    map.insert({1, 10});
    map.insert({2, 20});
    map.insert({3, 30});

    auto it = map.begin();
    ++it;

    auto next = map.erase(it);

    ASSERT_NE(next, map.end());
    EXPECT_EQ(next->first, 3);

    ASSERT_EQ(map.size(), 2u);
    EXPECT_EQ(map.begin()->first, 1);
}

TEST(XrOrderedMap, EraseLastReturnsEnd)
{
    xr_ordered_map<int, int> map;

    map.insert({1, 10});
    map.insert({2, 20});

    auto it = map.end();
    --it;

    EXPECT_EQ(map.erase(it), map.end());
    EXPECT_EQ(map.size(), 1u);
}

TEST(XrOrderedMap, EraseEndIsNoop)
{
    xr_ordered_map<int, int> map;

    map.insert({1, 10});

    EXPECT_EQ(map.erase(map.end()), map.end());
    EXPECT_EQ(map.size(), 1u);
}

TEST(XrOrderedMap, Clear)
{
    xr_ordered_map<int, int> map;

    map.insert({1, 10});
    map.insert({2, 20});

    map.clear();

    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0u);
    EXPECT_EQ(map.find(1), map.end());

    map.insert({3, 30});

    EXPECT_EQ(map.size(), 1u);
    EXPECT_EQ(map.at(3), 30);
}

TEST(XrOrderedMap, CopyConstructionPreservesOrder)
{
    xr_ordered_map<int, int> original;

    original.insert({3, 30});
    original.insert({1, 10});
    original.insert({2, 20});

    xr_ordered_map<int, int> copy(original);

    ASSERT_EQ(copy.size(), 3u);

    auto it = copy.begin();

    EXPECT_EQ(it->first, 3);
    ++it;
    EXPECT_EQ(it->first, 1);
    ++it;
    EXPECT_EQ(it->first, 2);
}

TEST(XrOrderedMap, CopyAssignmentPreservesOrder)
{
    xr_ordered_map<int, int> source;

    source.insert({3, 30});
    source.insert({1, 10});
    source.insert({2, 20});

    xr_ordered_map<int, int> destination;
    destination.insert({99, 99});

    destination = source;

    ASSERT_EQ(destination.size(), 3u);

    auto it = destination.begin();

    EXPECT_EQ(it->first, 3);
    ++it;
    EXPECT_EQ(it->first, 1);
    ++it;
    EXPECT_EQ(it->first, 2);
}

TEST(XrOrderedMap, MoveConstruction)
{
    xr_ordered_map<int, int> source;

    source.insert({3, 30});
    source.insert({1, 10});
    source.insert({2, 20});

    xr_ordered_map<int, int> destination(std::move(source));

    ASSERT_EQ(destination.size(), 3u);

    auto it = destination.begin();

    EXPECT_EQ(it->first, 3);
    ++it;
    EXPECT_EQ(it->first, 1);
    ++it;
    EXPECT_EQ(it->first, 2);
}

TEST(XrOrderedMap, MoveAssignment)
{
    xr_ordered_map<int, int> source;

    source.insert({1, 10});
    source.insert({2, 20});

    xr_ordered_map<int, int> destination;
    destination.insert({99, 99});

    destination = std::move(source);

    ASSERT_EQ(destination.size(), 2u);
    EXPECT_EQ(destination.at(1), 10);
    EXPECT_EQ(destination.at(2), 20);
}

TEST(XrOrderedMap, InitializerList)
{
    xr_ordered_map<int, int> map{
        {3, 30},
        {1, 10},
        {2, 20},
    };

    ASSERT_EQ(map.size(), 3u);

    auto it = map.begin();

    EXPECT_EQ(it->first, 3);
    ++it;
    EXPECT_EQ(it->first, 1);
    ++it;
    EXPECT_EQ(it->first, 2);
}

TEST(XrOrderedMap, ReverseIteration)
{
    xr_ordered_map<int, int> map;

    map.insert({1, 10});
    map.insert({2, 20});
    map.insert({3, 30});

    auto it = map.rbegin();

    ASSERT_NE(it, map.rend());
    EXPECT_EQ(it->first, 3);

    ++it;
    EXPECT_EQ(it->first, 2);

    ++it;
    EXPECT_EQ(it->first, 1);

    ++it;
    EXPECT_EQ(it, map.rend());
}

TEST(XrOrderedMap, Swap)
{
    xr_ordered_map<int, int> a;
    xr_ordered_map<int, int> b;

    a.insert({1, 10});
    a.insert({2, 20});

    b.insert({3, 30});

    a.swap(b);

    ASSERT_EQ(a.size(), 1u);
    EXPECT_EQ(a.begin()->first, 3);

    ASSERT_EQ(b.size(), 2u);
    EXPECT_EQ(b.begin()->first, 1);

    auto it = b.begin();
    ++it;
    EXPECT_EQ(it->first, 2);
}

TEST(XrOrderedMap, MutableMappedValueDoesNotBreakLookup)
{
    xr_ordered_map<int, std::string> map;

    map.insert({10, "old"});

    map.at(10) = "new";

    EXPECT_EQ(map.find(10)->second, "new");
    EXPECT_EQ(map.at(10), "new");
}


// -----------------------------------------------------------------------------
// xr_sparse_map
// -----------------------------------------------------------------------------

TEST(XrSparseMap, Empty)
{
    xr_sparse_map<u32, int, 16> map;

    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0u);

    EXPECT_EQ(map.find(0), map.end());
    EXPECT_EQ(map.find(15), map.end());

    EXPECT_FALSE(map.contains(0));
    EXPECT_EQ(map.count(0), 0u);
}

TEST(XrSparseMap, Emplace)
{
    xr_sparse_map<u32, std::string, 16> map;

    auto [it, inserted] = map.emplace(5, "five");

    ASSERT_TRUE(inserted);
    ASSERT_NE(it, map.end());

    EXPECT_EQ(it->first, 5u);
    EXPECT_EQ(it->second, "five");

    EXPECT_EQ(map.size(), 1u);
    EXPECT_TRUE(map.contains(5));
    EXPECT_EQ(map.count(5), 1u);
}

TEST(XrSparseMap, DuplicateEmplaceDoesNotModifyValue)
{
    xr_sparse_map<u32, std::string, 16> map;

    auto first = map.emplace(5, "five");
    auto second = map.emplace(5, "replacement");

    EXPECT_TRUE(first.second);
    EXPECT_FALSE(second.second);

    EXPECT_EQ(map.size(), 1u);
    EXPECT_EQ(map.at(5), "five");
    EXPECT_EQ(first.first, second.first);
}

TEST(XrSparseMap, Find)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(3, 30);
    map.emplace(7, 70);

    auto it = map.find(7);

    ASSERT_NE(it, map.end());
    EXPECT_EQ(it->first, 7u);
    EXPECT_EQ(it->second, 70);

    EXPECT_EQ(map.find(4), map.end());
}

TEST(XrSparseMap, OperatorBracket)
{
    xr_sparse_map<u32, int, 16> map;

    EXPECT_EQ(map[5], 0);

    map[5] = 42;

    EXPECT_EQ(map[5], 42);
    EXPECT_EQ(map.size(), 1u);

    map[5] = 99;

    EXPECT_EQ(map[5], 99);
    EXPECT_EQ(map.size(), 1u);
}

TEST(XrSparseMap, Insert)
{
    xr_sparse_map<u32, int, 16> map;

    auto result = map.insert({7, 70});

    EXPECT_TRUE(result.second);
    EXPECT_EQ(result.first->first, 7u);
    EXPECT_EQ(result.first->second, 70);

    EXPECT_EQ(map.at(7), 70);
}

TEST(XrSparseMap, EraseByKey)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(1, 10);
    map.emplace(2, 20);
    map.emplace(3, 30);

    EXPECT_EQ(map.erase(2), 1u);
    EXPECT_EQ(map.erase(2), 0u);

    EXPECT_FALSE(map.contains(2));
    EXPECT_EQ(map.size(), 2u);

    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(3));
}

TEST(XrSparseMap, EraseByKeyUpdatesMovedElementIndex)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(10, 100);
    map.emplace(20, 200);
    map.emplace(30, 300);

    // Remove the middle element.  30 is moved into its slot.
    EXPECT_EQ(map.erase(20), 1u);

    ASSERT_EQ(map.size(), 2u);

    EXPECT_EQ(map.at(10), 100);
    EXPECT_EQ(map.at(30), 300);

    auto it = map.find(30);

    ASSERT_NE(it, map.end());
    EXPECT_EQ(it->first, 30u);
    EXPECT_EQ(it->second, 300);
}

TEST(XrSparseMap, EraseFirstUpdatesMovedElementIndex)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(10, 100);
    map.emplace(20, 200);
    map.emplace(30, 300);

    map.erase(10);

    ASSERT_EQ(map.size(), 2u);

    EXPECT_FALSE(map.contains(10));
    EXPECT_EQ(map.at(20), 200);
    EXPECT_EQ(map.at(30), 300);

    EXPECT_EQ(map.find(20)->second, 200);
    EXPECT_EQ(map.find(30)->second, 300);
}

TEST(XrSparseMap, EraseLast)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(1, 10);
    map.emplace(2, 20);

    map.erase(2);

    ASSERT_EQ(map.size(), 1u);
    EXPECT_TRUE(map.contains(1));
    EXPECT_FALSE(map.contains(2));
}

TEST(XrSparseMap, EraseByIteratorReturnsSameSlot)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(10, 100);
    map.emplace(20, 200);
    map.emplace(30, 300);

    auto it = map.find(20);
    ASSERT_NE(it, map.end());

    auto returned = map.erase(it);

    ASSERT_NE(returned, map.end());

    // 30 was moved into the erased slot.
    EXPECT_EQ(returned->first, 30u);
    EXPECT_EQ(returned->second, 300);
}

TEST(XrSparseMap, EraseLastByIteratorReturnsEnd)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(10, 100);
    map.emplace(20, 200);

    auto it = map.find(20);

    EXPECT_EQ(map.erase(it), map.end());
    EXPECT_EQ(map.size(), 1u);
}

TEST(XrSparseMap, EraseEndIsNoop)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(10, 100);

    EXPECT_EQ(map.erase(map.end()), map.end());
    EXPECT_EQ(map.size(), 1u);
    EXPECT_TRUE(map.contains(10));
}

TEST(XrSparseMap, KeyZeroIsAlwaysFirst)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(10, 100);
    map.emplace(20, 200);

    ASSERT_EQ(map.begin()->first, 10u);

    map.emplace(0, 0);

    ASSERT_EQ(map.size(), 3u);

    auto it = map.begin();

    EXPECT_EQ(it->first, 0u);
    EXPECT_EQ(it->second, 0);

    ++it;
    EXPECT_EQ(it->first, 20u);

    ++it;
    EXPECT_EQ(it->first, 10u);
}

TEST(XrSparseMap, KeyZeroInsertedIntoEmptyMap)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(0, 123);

    ASSERT_EQ(map.size(), 1u);
    EXPECT_EQ(map.begin()->first, 0u);
    EXPECT_EQ(map.begin()->second, 123);
}

TEST(XrSparseMap, KeyZeroInsertedTwice)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(0, 123);

    auto result = map.emplace(0, 456);

    EXPECT_FALSE(result.second);
    EXPECT_EQ(map.size(), 1u);
    EXPECT_EQ(map.at(0), 123);
}

TEST(XrSparseMap, Sort)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(30, 300);
    map.emplace(10, 100);
    map.emplace(20, 200);
    map.emplace(5, 50);

    map.sort();

    ASSERT_EQ(map.size(), 4u);

    auto it = map.begin();

    EXPECT_EQ(it->first, 5u);
    ++it;
    EXPECT_EQ(it->first, 10u);
    ++it;
    EXPECT_EQ(it->first, 20u);
    ++it;
    EXPECT_EQ(it->first, 30u);
}

TEST(XrSparseMap, SortRebuildsSparseIndices)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(30, 300);
    map.emplace(10, 100);
    map.emplace(20, 200);

    ASSERT_EQ(map.size(), 3u);

    EXPECT_EQ(map.begin()[0].first, 30u);
    EXPECT_EQ(map.begin()[0].second, 300);
    EXPECT_EQ(map.begin()[1].first, 10u);
    EXPECT_EQ(map.begin()[1].second, 100);
    EXPECT_EQ(map.begin()[2].first, 20u);
    EXPECT_EQ(map.begin()[2].second, 200);

    map.sort();

    ASSERT_EQ(map.size(), 3u);

    EXPECT_EQ(map.begin()[0].first, 10u);
    EXPECT_EQ(map.begin()[0].second, 100);
    EXPECT_EQ(map.begin()[1].first, 20u);
    EXPECT_EQ(map.begin()[1].second, 200);
    EXPECT_EQ(map.begin()[2].first, 30u);
    EXPECT_EQ(map.begin()[2].second, 300);

    auto it10 = map.find(10);
    auto it20 = map.find(20);
    auto it30 = map.find(30);

    ASSERT_NE(it10, map.end());
    ASSERT_NE(it20, map.end());
    ASSERT_NE(it30, map.end());

    EXPECT_EQ(it10->second, 100);
    EXPECT_EQ(it20->second, 200);
    EXPECT_EQ(it30->second, 300);
}

TEST(XrSparseMap, Clear)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(1, 10);
    map.emplace(5, 50);
    map.emplace(10, 100);

    map.clear();

    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0u);

    EXPECT_FALSE(map.contains(1));
    EXPECT_FALSE(map.contains(5));
    EXPECT_FALSE(map.contains(10));

    map.emplace(5, 500);

    EXPECT_EQ(map.at(5), 500);
    EXPECT_EQ(map.size(), 1u);
}

TEST(XrSparseMap, Swap)
{
    xr_sparse_map<u32, int, 16> a;
    xr_sparse_map<u32, int, 16> b;

    a.emplace(1, 10);
    a.emplace(2, 20);

    b.emplace(7, 70);

    a.swap(b);

    ASSERT_EQ(a.size(), 1u);
    EXPECT_EQ(a.at(7), 70);

    ASSERT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(1), 10);
    EXPECT_EQ(b.at(2), 20);
}

TEST(XrSparseMap, IterationIsDense)
{
    xr_sparse_map<u32, int, 16> map;

    map.emplace(100, 1);
    map.emplace(2, 2);
    map.emplace(50, 3);

    std::vector<std::pair<u32, int>> result;

    for (const auto& item : map)
        result.emplace_back(item.first, item.second);

    EXPECT_EQ(
        result,
        (std::vector<std::pair<u32, int>>{
            {100, 1},
            {2, 2},
            {50, 3},
        }));
}

TEST(XrSparseMap, RepeatedEraseAndInsertMaintainsIndices)
{
    xr_sparse_map<u32, int, 32> map;

    for (u32 i = 0; i != 10; ++i)
        map.emplace(i, static_cast<int>(i * 10));

    map.erase(3);
    map.erase(7);
    map.erase(0);

    map.emplace(15, 150);
    map.emplace(20, 200);

    for (u32 i : {1u, 2u, 4u, 5u, 6u, 8u, 9u, 15u, 20u})
    {
        ASSERT_TRUE(map.contains(i)) << "Missing key " << i;
        EXPECT_EQ(map.at(i), static_cast<int>(i * 10));
    }

    EXPECT_EQ(map.at(15), 150);
    EXPECT_EQ(map.at(20), 200);
}


// -----------------------------------------------------------------------------
// xr_set / xr_multiset / xr_map / xr_multimap
// -----------------------------------------------------------------------------

TEST(XrSet, BasicOperations)
{
    xr_set<int> set;

    set.insert(3);
    set.insert(1);
    set.insert(2);
    set.insert(2);

    EXPECT_EQ(set.size(), 3u);

    EXPECT_TRUE(set.contains(1));
    EXPECT_TRUE(set.contains(2));
    EXPECT_TRUE(set.contains(3));
    EXPECT_FALSE(set.contains(4));
}

TEST(XrMultiset, BasicOperations)
{
    xr_multiset<int> set;

    set.insert(1);
    set.insert(1);
    set.insert(2);

    EXPECT_EQ(set.size(), 3u);
    EXPECT_EQ(set.count(1), 2u);
}

TEST(XrMap, BasicOperations)
{
    xr_map<int, std::string> map;

    map[3] = "three";
    map[1] = "one";
    map[2] = "two";

    ASSERT_EQ(map.size(), 3u);

    EXPECT_EQ(map.at(1), "one");
    EXPECT_EQ(map.at(2), "two");
    EXPECT_EQ(map.at(3), "three");

    EXPECT_EQ(map.begin()->first, 1);
}

TEST(XrMultimap, BasicOperations)
{
    xr_multimap<int, std::string> map;

    map.emplace(1, "one");
    map.emplace(1, "another");
    map.emplace(2, "two");

    EXPECT_EQ(map.size(), 3u);
    EXPECT_EQ(map.count(1), 2u);
}


// -----------------------------------------------------------------------------
// robin-hood aliases
// -----------------------------------------------------------------------------

TEST(XrUnorderedMap, BasicOperations)
{
    xr_unordered_map<int, std::string> map;

    map.emplace(1, "one");
    map.emplace(2, "two");

    ASSERT_EQ(map.size(), 2u);

    EXPECT_EQ(map.at(1), "one");
    EXPECT_EQ(map.at(2), "two");
}

TEST(XrUnorderedMap, DuplicateKey)
{
    xr_unordered_map<int, int> map;

    auto first = map.emplace(1, 10);
    auto second = map.emplace(1, 20);

    EXPECT_TRUE(first.second);
    EXPECT_FALSE(second.second);

    EXPECT_EQ(map.size(), 1u);
    EXPECT_EQ(map.at(1), 10);
}

TEST(XrUnorderedSet, BasicOperations)
{
    xr_unordered_set<int> set;

    set.insert(1);
    set.insert(2);
    set.insert(2);

    EXPECT_EQ(set.size(), 2u);
    EXPECT_TRUE(set.contains(1));
    EXPECT_TRUE(set.contains(2));
    EXPECT_FALSE(set.contains(3));
}

TEST(XrUnorderedFlatMap, BasicOperations)
{
    xr_unordered_flat_map<int, std::string> map;

    map.emplace(10, "ten");
    map.emplace(20, "twenty");

    EXPECT_EQ(map.at(10), "ten");
    EXPECT_EQ(map.at(20), "twenty");
}

TEST(XrUnorderedFlatSet, BasicOperations)
{
    xr_unordered_flat_set<int> set;

    set.insert(10);
    set.insert(20);

    EXPECT_EQ(set.size(), 2u);
    EXPECT_TRUE(set.contains(10));
    EXPECT_TRUE(set.contains(20));
}


// -----------------------------------------------------------------------------
// xr_hash / xr_pair
// -----------------------------------------------------------------------------

TEST(XrHash, CanHashInteger)
{
    xr_hash<int> hash;

    EXPECT_EQ(hash(123), std::hash<int>{}(123));
}

TEST(XrPair, IsUsable)
{
    xr_pair<int, std::string> pair{42, "answer"};

    EXPECT_EQ(pair.first, 42);
    EXPECT_EQ(pair.second, "answer");
}


// -----------------------------------------------------------------------------
// mk_pair
// -----------------------------------------------------------------------------

TEST(MkPair, CreatesPair)
{
    auto pair = mk_pair(42, std::string("answer"));

    EXPECT_EQ(pair.first, 42);
    EXPECT_EQ(pair.second, "answer");

    static_assert(std::is_same_v<
        decltype(pair),
        std::pair<int, std::string>>);
}


// -----------------------------------------------------------------------------
// string predicates
// -----------------------------------------------------------------------------

TEST(PredStr, LexicographicalComparison)
{
    pred_str pred;

    EXPECT_TRUE(pred("abc", "abd"));
    EXPECT_FALSE(pred("abd", "abc"));
    EXPECT_FALSE(pred("abc", "abc"));
}

TEST(PredStr, WorksWithXrSet)
{
    xr_set<const char*, pred_str> set;

    set.insert("banana");
    set.insert("apple");
    set.insert("cherry");

    ASSERT_EQ(set.size(), 3u);

    auto it = set.begin();

    EXPECT_STREQ(*it, "apple");
    ++it;
    EXPECT_STREQ(*it, "banana");
    ++it;
    EXPECT_STREQ(*it, "cherry");
}

TEST(PredStri, CaseInsensitiveComparison)
{
    pred_stri pred;

    EXPECT_FALSE(pred("ABC", "abc"));
    EXPECT_FALSE(pred("abc", "ABC"));

    EXPECT_TRUE(pred("abc", "BCD"));
    EXPECT_FALSE(pred("BCD", "abc"));
}


// -----------------------------------------------------------------------------
// DEF_* / DEFINE_* aliases
// -----------------------------------------------------------------------------

TEST(StlExtensions, AuxiliaryAliases)
{
    boolVec bools;
    BOOLVec bools2;
    FrectVec frects;
    IrectVec irects;
    PlaneVec planes;
    Fvector2Vec vectors2;
    FvectorVec vectors;
    FcolorVec colors;

    bools.push_back(true);
    bools2.push_back(TRUE);
    frects.emplace_back();
    irects.emplace_back();
    planes.emplace_back();
    vectors2.emplace_back();
    vectors.emplace_back();
    colors.emplace_back();

    EXPECT_EQ(bools.size(), 1u);
    EXPECT_EQ(bools2.size(), 1u);
    EXPECT_EQ(frects.size(), 1u);
    EXPECT_EQ(irects.size(), 1u);
    EXPECT_EQ(planes.size(), 1u);
    EXPECT_EQ(vectors2.size(), 1u);
    EXPECT_EQ(vectors.size(), 1u);
    EXPECT_EQ(colors.size(), 1u);
}

TEST(StlExtensions, IteratorAliases)
{
    IntVec values;

    values.push_back(10);
    values.push_back(20);

    IntIt it = values.begin();

    ASSERT_NE(it, values.end());
    EXPECT_EQ(*it, 10);

    ++it;

    EXPECT_EQ(*it, 20);
}

}
