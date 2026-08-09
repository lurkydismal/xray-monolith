#include "stdafx.h"

#include "compression_ppmd_stream.h"

#include <gtest/gtest.h>

#include <array>
#include <cstring>

namespace
{
    using Stream = compression::ppmd::stream;

    TEST(PPMDStreamTest, ConstructorInitializesBuffer)
    {
        std::array<u8, 8> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.buffer(), buffer.data());
    }

    TEST(PPMDStreamTest, ConstructorInitializesPositionToBeginning)
    {
        std::array<u8, 8> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.tell(), 0u);
    }

    TEST(PPMDStreamTest, BufferReturnsOriginalBuffer)
    {
        std::array<u8, 16> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.buffer(), buffer.data());
    }

    TEST(PPMDStreamTest, InitialPositionIsZero)
    {
        std::array<u8, 16> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.tell(), 0u);
    }

    TEST(PPMDStreamTest, PutCharWritesByte)
    {
        std::array<u8, 4> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.put_char(0x42);

        EXPECT_EQ(buffer[0], 0x42);
    }

    TEST(PPMDStreamTest, PutCharAdvancesPosition)
    {
        std::array<u8, 4> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.put_char(0x42);

        EXPECT_EQ(stream.tell(), 1u);
    }

    TEST(PPMDStreamTest, PutCharWritesSequentialBytes)
    {
        std::array<u8, 4> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.put_char(0x10);
        stream.put_char(0x20);
        stream.put_char(0x30);
        stream.put_char(0x40);

        EXPECT_EQ(buffer[0], 0x10);
        EXPECT_EQ(buffer[1], 0x20);
        EXPECT_EQ(buffer[2], 0x30);
        EXPECT_EQ(buffer[3], 0x40);

        EXPECT_EQ(stream.tell(), 4u);
    }

    TEST(PPMDStreamTest, PutCharPreservesAllByteValues)
    {
        std::array<u8, 4> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.put_char(0x00);
        stream.put_char(0x01);
        stream.put_char(0x7f);
        stream.put_char(0xff);

        EXPECT_EQ(buffer[0], 0x00);
        EXPECT_EQ(buffer[1], 0x01);
        EXPECT_EQ(buffer[2], 0x7f);
        EXPECT_EQ(buffer[3], 0xff);
    }

    TEST(PPMDStreamTest, GetCharReadsByte)
    {
        std::array<u8, 4> buffer{
            0x42, 0x43, 0x44, 0x45
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.get_char(), 0x42);
    }

    TEST(PPMDStreamTest, GetCharAdvancesPosition)
    {
        std::array<u8, 4> buffer{
            0x42, 0x43, 0x44, 0x45
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.get_char();

        EXPECT_EQ(stream.tell(), 1u);
    }

    TEST(PPMDStreamTest, GetCharReadsSequentialBytes)
    {
        std::array<u8, 4> buffer{
            0x10, 0x20, 0x30, 0x40
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.get_char(), 0x10);
        EXPECT_EQ(stream.get_char(), 0x20);
        EXPECT_EQ(stream.get_char(), 0x30);
        EXPECT_EQ(stream.get_char(), 0x40);

        EXPECT_EQ(stream.tell(), 4u);
    }

    TEST(PPMDStreamTest, GetCharPreservesUnsignedByteValue)
    {
        std::array<u8, 3> buffer{
            0x00, 0x80, 0xff
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.get_char(), 0x00);
        EXPECT_EQ(stream.get_char(), 0x80);
        EXPECT_EQ(stream.get_char(), 0xff);
    }

    TEST(PPMDStreamTest, GetCharReturnsEOFAtEnd)
    {
        std::array<u8, 2> buffer{
            0x10, 0x20
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.get_char(), 0x10);
        EXPECT_EQ(stream.get_char(), 0x20);
        EXPECT_EQ(stream.get_char(), EOF);
    }

    TEST(PPMDStreamTest, GetCharAtEndDoesNotAdvancePosition)
    {
        std::array<u8, 2> buffer{
            0x10, 0x20
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.get_char();
        stream.get_char();

        ASSERT_EQ(stream.tell(), 2u);

        EXPECT_EQ(stream.get_char(), EOF);
        EXPECT_EQ(stream.tell(), 2u);

        EXPECT_EQ(stream.get_char(), EOF);
        EXPECT_EQ(stream.tell(), 2u);
    }

    TEST(PPMDStreamTest, RewindReturnsToBeginning)
    {
        std::array<u8, 4> buffer{
            0x10, 0x20, 0x30, 0x40
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.get_char();
        stream.get_char();

        ASSERT_EQ(stream.tell(), 2u);

        stream.rewind();

        EXPECT_EQ(stream.tell(), 0u);
        EXPECT_EQ(stream.get_char(), 0x10);
    }

    TEST(PPMDStreamTest, RewindAfterWritingReturnsToBeginning)
    {
        std::array<u8, 4> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.put_char(0x10);
        stream.put_char(0x20);

        ASSERT_EQ(stream.tell(), 2u);

        stream.rewind();

        EXPECT_EQ(stream.tell(), 0u);

        stream.put_char(0x30);

        EXPECT_EQ(buffer[0], 0x30);
        EXPECT_EQ(buffer[1], 0x20);
        EXPECT_EQ(stream.tell(), 1u);
    }

    TEST(PPMDStreamTest, RewindCanBeUsedRepeatedly)
    {
        std::array<u8, 4> buffer{
            0x10, 0x20, 0x30, 0x40
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.get_char(), 0x10);

        stream.rewind();

        EXPECT_EQ(stream.get_char(), 0x10);

        stream.rewind();

        EXPECT_EQ(stream.get_char(), 0x10);

        EXPECT_EQ(stream.tell(), 1u);
    }

    TEST(PPMDStreamTest, BufferContentsAreNotModifiedByReads)
    {
        const std::array<u8, 4> expected{
            0x10, 0x20, 0x30, 0x40
        };

        auto buffer = expected;

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.get_char();
        stream.get_char();
        stream.get_char();

        EXPECT_EQ(buffer, expected);
    }

    TEST(PPMDStreamTest, BufferContentsAreModifiedByWrites)
    {
        std::array<u8, 4> buffer{
            0x00, 0x00, 0x00, 0x00
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.put_char(0xaa);
        stream.put_char(0xbb);

        EXPECT_EQ(buffer[0], 0xaa);
        EXPECT_EQ(buffer[1], 0xbb);
        EXPECT_EQ(buffer[2], 0x00);
        EXPECT_EQ(buffer[3], 0x00);
    }

    TEST(PPMDStreamTest, TellTracksMixedReadsAndWrites)
    {
        std::array<u8, 8> buffer{
            0x01, 0x02, 0x03, 0x04,
            0x05, 0x06, 0x07, 0x08
        };

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.tell(), 0u);

        stream.get_char();
        EXPECT_EQ(stream.tell(), 1u);

        stream.get_char();
        EXPECT_EQ(stream.tell(), 2u);

        stream.put_char(0xaa);
        EXPECT_EQ(stream.tell(), 3u);

        stream.put_char(0xbb);
        EXPECT_EQ(stream.tell(), 4u);

        EXPECT_EQ(buffer[2], 0xaa);
        EXPECT_EQ(buffer[3], 0xbb);
    }

    TEST(PPMDStreamTest, SingleByteBuffer)
    {
        std::array<u8, 1> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        EXPECT_EQ(stream.tell(), 0u);

        stream.put_char(0xab);

        EXPECT_EQ(buffer[0], 0xab);
        EXPECT_EQ(stream.tell(), 1u);

        stream.rewind();

        EXPECT_EQ(stream.get_char(), 0xab);
        EXPECT_EQ(stream.tell(), 1u);
        EXPECT_EQ(stream.get_char(), EOF);
        EXPECT_EQ(stream.tell(), 1u);
    }

    TEST(PPMDStreamTest, ZeroSizedBufferStartsAtZero)
    {
        std::array<u8, 1> buffer{0xab};

        Stream stream(buffer.data(), 0);

        EXPECT_EQ(stream.buffer(), buffer.data());
        EXPECT_EQ(stream.tell(), 0u);
        EXPECT_EQ(stream.get_char(), EOF);
        EXPECT_EQ(stream.tell(), 0u);
    }

    TEST(PPMDStreamTest, ZeroSizedBufferDoesNotReadMemory)
    {
        std::array<u8, 1> buffer{0xab};

        Stream stream(buffer.data(), 0);

        EXPECT_EQ(stream.get_char(), EOF);
        EXPECT_EQ(buffer[0], 0xab);
    }

    TEST(PPMDStreamTest, PutThenRewindThenRead)
    {
        std::array<u8, 8> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        stream.put_char(0x11);
        stream.put_char(0x22);
        stream.put_char(0x33);

        ASSERT_EQ(stream.tell(), 3u);

        stream.rewind();

        EXPECT_EQ(stream.get_char(), 0x11);
        EXPECT_EQ(stream.get_char(), 0x22);
        EXPECT_EQ(stream.get_char(), 0x33);
        EXPECT_EQ(stream.get_char(), EOF);
    }

    TEST(PPMDStreamTest, FullBufferCanBeWrittenAndReadBack)
    {
        std::array<u8, 256> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        for (u32 i = 0; i < buffer.size(); ++i)
            stream.put_char(static_cast<u8>(i));

        EXPECT_EQ(stream.tell(), buffer.size());

        stream.rewind();

        for (u32 i = 0; i < buffer.size(); ++i)
            EXPECT_EQ(stream.get_char(), static_cast<int>(static_cast<u8>(i)));

        EXPECT_EQ(stream.tell(), buffer.size());
        EXPECT_EQ(stream.get_char(), EOF);
    }

    TEST(PPMDStreamTest, BufferReturnsSamePointerAfterRewind)
    {
        std::array<u8, 8> buffer{};

        Stream stream(buffer.data(), static_cast<u32>(buffer.size()));

        const u8* original = stream.buffer();

        stream.put_char(1);
        stream.put_char(2);
        stream.rewind();

        EXPECT_EQ(stream.buffer(), original);
    }
}
