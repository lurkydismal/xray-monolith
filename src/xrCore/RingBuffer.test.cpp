#include "stdafx.h"

#include "RingBuffer.h"

#include <gtest/gtest.h>

TEST(RingBuffer, DefaultConstruction)
{
    RingBuffer<int, 4> buffer;

    EXPECT_EQ(buffer.GetSize(), 4u);
    EXPECT_EQ(buffer.GetHead(), 0u);
    EXPECT_EQ(buffer.GetTail(), 3u);
    EXPECT_EQ(buffer.Position, 0u);

    for (unsigned i = 0; i < buffer.GetSize(); ++i)
        EXPECT_EQ(buffer.Get(i), 0);
}

TEST(RingBuffer, WriteStoresValues)
{
    RingBuffer<int, 4> buffer;

    buffer.Write(10);
    buffer.Write(20);
    buffer.Write(30);

    EXPECT_EQ(buffer.Get(0), 10);
    EXPECT_EQ(buffer.Get(1), 20);
    EXPECT_EQ(buffer.Get(2), 30);
    EXPECT_EQ(buffer.Get(3), 0);

    EXPECT_EQ(buffer.Position, 3u);
    EXPECT_EQ(buffer.GetHead(), 0u);
}

TEST(RingBuffer, WriteWrapsAround)
{
    RingBuffer<int, 4> buffer;

    buffer.Write(10);
    buffer.Write(20);
    buffer.Write(30);
    buffer.Write(40);
    buffer.Write(50);

    EXPECT_EQ(buffer.Get(0), 50);
    EXPECT_EQ(buffer.Get(1), 20);
    EXPECT_EQ(buffer.Get(2), 30);
    EXPECT_EQ(buffer.Get(3), 40);

    EXPECT_EQ(buffer.Position, 5u);
}

TEST(RingBuffer, PositionIsMonotonicallyIncremented)
{
    RingBuffer<int, 4> buffer;

    EXPECT_EQ(buffer.Position, 0u);

    buffer.Write(1);
    EXPECT_EQ(buffer.Position, 1u);

    buffer.Write(2);
    EXPECT_EQ(buffer.Position, 2u);

    buffer.Write(3);
    EXPECT_EQ(buffer.Position, 3u);

    buffer.Write(4);
    EXPECT_EQ(buffer.Position, 4u);

    // Position itself is not wrapped.
    buffer.Write(5);
    EXPECT_EQ(buffer.Position, 5u);
}

TEST(RingBuffer, GetHeadAndTail)
{
    RingBuffer<int, 5> buffer;

    EXPECT_EQ(buffer.GetHead(), 0u);
    EXPECT_EQ(buffer.GetTail(), 4u);

    buffer.MoveHead(1);

    EXPECT_EQ(buffer.GetHead(), 1u);
    EXPECT_EQ(buffer.GetTail(), 0u);

    buffer.MoveHead(1);

    EXPECT_EQ(buffer.GetHead(), 2u);
    EXPECT_EQ(buffer.GetTail(), 1u);

    buffer.MoveHead(2);

    EXPECT_EQ(buffer.GetHead(), 4u);
    EXPECT_EQ(buffer.GetTail(), 3u);

    buffer.MoveHead(1);

    EXPECT_EQ(buffer.GetHead(), 0u);
    EXPECT_EQ(buffer.GetTail(), 4u);
}

TEST(RingBuffer, MoveHeadWraps)
{
    RingBuffer<int, 4> buffer;

    buffer.MoveHead(4);

    EXPECT_EQ(buffer.GetHead(), 0u);
    EXPECT_EQ(buffer.GetTail(), 3u);

    buffer.MoveHead(5);

    EXPECT_EQ(buffer.GetHead(), 1u);
    EXPECT_EQ(buffer.GetTail(), 0u);

    buffer.MoveHead(10);

    EXPECT_EQ(buffer.GetHead(), 3u);
    EXPECT_EQ(buffer.GetTail(), 2u);
}

TEST(RingBuffer, GetAndGetLooped)
{
    RingBuffer<int, 4> buffer;

    buffer.Write(10);
    buffer.Write(20);
    buffer.Write(30);
    buffer.Write(40);

    EXPECT_EQ(buffer.Get(0), 10);
    EXPECT_EQ(buffer.Get(1), 20);
    EXPECT_EQ(buffer.Get(2), 30);
    EXPECT_EQ(buffer.Get(3), 40);

    EXPECT_EQ(buffer.GetLooped(0), 10);
    EXPECT_EQ(buffer.GetLooped(1), 20);
    EXPECT_EQ(buffer.GetLooped(2), 30);
    EXPECT_EQ(buffer.GetLooped(3), 40);
    EXPECT_EQ(buffer.GetLooped(4), 10);
    EXPECT_EQ(buffer.GetLooped(5), 20);
    EXPECT_EQ(buffer.GetLooped(8), 10);
}

TEST(RingBuffer, GetReturnsMutableReference)
{
    RingBuffer<int, 4> buffer;

    buffer.Write(10);

    buffer.Get(0) = 42;

    EXPECT_EQ(buffer.Get(0), 42);
}

TEST(RingBuffer, PushMovesHeadBackward)
{
    RingBuffer<int, 4> buffer;

    int value = 42;
    buffer.Push(value);

    EXPECT_EQ(buffer.GetHead(), 3u);
    EXPECT_EQ(buffer.GetTail(), 2u);
    EXPECT_EQ(buffer.Get(3), 42);
}

TEST(RingBuffer, PushWrapsHead)
{
    RingBuffer<int, 4> buffer;

    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    int e = 50;

    buffer.Push(a);
    EXPECT_EQ(buffer.GetHead(), 3u);

    buffer.Push(b);
    EXPECT_EQ(buffer.GetHead(), 2u);

    buffer.Push(c);
    EXPECT_EQ(buffer.GetHead(), 1u);

    buffer.Push(d);
    EXPECT_EQ(buffer.GetHead(), 0u);

    buffer.Push(e);
    EXPECT_EQ(buffer.GetHead(), 3u);

    EXPECT_EQ(buffer.Get(3), 50);
    EXPECT_EQ(buffer.Get(2), 20);
    EXPECT_EQ(buffer.Get(1), 30);
    EXPECT_EQ(buffer.Get(0), 40);
}

TEST(RingBuffer, PushRvalue)
{
    RingBuffer<int, 4> buffer;

    buffer.Push(123);

    EXPECT_EQ(buffer.GetHead(), 3u);
    EXPECT_EQ(buffer.Get(3), 123);
}

TEST(RingBuffer, WriteAndPushUseIndependentPositions)
{
    RingBuffer<int, 4> buffer;

    buffer.Write(10);
    buffer.Write(20);

    EXPECT_EQ(buffer.Position, 2u);
    EXPECT_EQ(buffer.GetHead(), 0u);

    int value = 30;
    buffer.Push(value);

    EXPECT_EQ(buffer.Position, 2u);
    EXPECT_EQ(buffer.GetHead(), 3u);

    EXPECT_EQ(buffer.Get(0), 10);
    EXPECT_EQ(buffer.Get(1), 20);
    EXPECT_EQ(buffer.Get(3), 30);
}

TEST(RingBuffer, WriteFromHeadNoMoveCopiesContiguousData)
{
    RingBuffer<int, 5> buffer;

    int values[] = {10, 20, 30};

    EXPECT_TRUE(buffer.WriteFromHeadNoMove(values, 3));

    EXPECT_EQ(buffer.GetHead(), 0u);
    EXPECT_EQ(buffer.Get(0), 10);
    EXPECT_EQ(buffer.Get(1), 20);
    EXPECT_EQ(buffer.Get(2), 30);
    EXPECT_EQ(buffer.Get(3), 0);
    EXPECT_EQ(buffer.Get(4), 0);
}

TEST(RingBuffer, WriteFromHeadNoMoveCopiesAcrossBoundary)
{
    RingBuffer<int, 5> buffer;

    buffer.MoveHead(3);

    int values[] = {10, 20, 30, 40};

    EXPECT_TRUE(buffer.WriteFromHeadNoMove(values, 4));

    EXPECT_EQ(buffer.GetHead(), 3u);

    EXPECT_EQ(buffer.Get(3), 10);
    EXPECT_EQ(buffer.Get(4), 20);
    EXPECT_EQ(buffer.Get(0), 30);
    EXPECT_EQ(buffer.Get(1), 40);
}

TEST(RingBuffer, WriteFromHeadNoMoveDoesNotMoveHead)
{
    RingBuffer<int, 5> buffer;

    buffer.MoveHead(2);

    int values[] = {10, 20};

    EXPECT_TRUE(buffer.WriteFromHeadNoMove(values, 2));

    EXPECT_EQ(buffer.GetHead(), 2u);
    EXPECT_EQ(buffer.Get(2), 10);
    EXPECT_EQ(buffer.Get(3), 20);
}

TEST(RingBuffer, WriteFromHeadNoMoveRejectsBufferSize)
{
    RingBuffer<int, 5> buffer;

    int values[] = {1, 2, 3, 4, 5};

    EXPECT_FALSE(buffer.WriteFromHeadNoMove(values, 5));

    // Nothing should have been written.
    for (unsigned i = 0; i < buffer.GetSize(); ++i)
        EXPECT_EQ(buffer.Get(i), 0);
}

TEST(RingBuffer, WriteFromHeadNoMoveAllowsEmptyWrite)
{
    RingBuffer<int, 5> buffer;

    buffer.Write(123);

    int values[] = {1};

    EXPECT_TRUE(buffer.WriteFromHeadNoMove(values, 0));

    EXPECT_EQ(buffer.GetHead(), 0u);
    EXPECT_EQ(buffer.Get(0), 123);
}

TEST(RingBuffer, ForEachElementFromHeadIteratesUntilTail)
{
    RingBuffer<int, 5> buffer;

    int a = 10;
    int b = 20;
    int c = 30;

    buffer.Push(a);
    buffer.Push(b);
    buffer.Push(c);

    std::vector<int> result;

    auto collect = [&result](const int& value)
    {
        result.push_back(value);
    };

    buffer.ForEachElementFromHead(collect);

    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 30);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 10);
}

TEST(RingBuffer, ForEachElementFromHeadHandlesWraparound)
{
    RingBuffer<int, 5> buffer;

    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;

    buffer.Push(a); // head = 4
    buffer.Push(b); // head = 3
    buffer.Push(c); // head = 2
    buffer.Push(d); // head = 1

    std::vector<int> result;

    auto collect = [&result](const int& value)
    {
        result.push_back(value);
    };

    buffer.ForEachElementFromHead(collect);

    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], 40);
    EXPECT_EQ(result[1], 30);
    EXPECT_EQ(result[2], 20);
    EXPECT_EQ(result[3], 10);
}

TEST(RingBuffer, ForEachElementFromHeadOnEmptyBuffer)
{
    RingBuffer<int, 5> buffer;

    std::vector<int> result;

    auto collect = [&result](const int& value)
    {
        result.push_back(value);
    };

    buffer.ForEachElementFromHead(collect);

    EXPECT_TRUE(result.empty());
}

TEST(RingBuffer, NonFundamentalTypeIsDefaultConstructed)
{
    struct Value
    {
        int value = 123;

        Value() = default;
        Value(int v) : value(v) {}
    };

    RingBuffer<Value, 3> buffer;

    EXPECT_EQ(buffer.Get(0).value, 123);
    EXPECT_EQ(buffer.Get(1).value, 123);
    EXPECT_EQ(buffer.Get(2).value, 123);
}

TEST(RingBuffer, NonFundamentalTypeCanBeWritten)
{
    struct Value
    {
        int value = 0;

        Value() = default;
        Value(int v) : value(v) {}
    };

    RingBuffer<Value, 3> buffer;

    buffer.Write(Value{42});

    EXPECT_EQ(buffer.Get(0).value, 42);
}
