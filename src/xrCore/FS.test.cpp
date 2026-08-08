#include "stdafx.h"

#include "FS.h"

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

namespace
{
    class MemoryReaderFixture : public ::testing::Test
    {
    protected:
        CMemoryWriter writer;

        IReader reader()
        {
            return IReader(writer.pointer(), static_cast<int>(writer.size()));
        }
    };

    template <typename T>
    void ExpectBytesEqual(const void* actual, const T& expected)
    {
        ASSERT_EQ(sizeof(T), sizeof(expected));
        EXPECT_EQ(
            std::memcmp(actual, &expected, sizeof(T)),
            0);
    }

    void ExpectFloatNear(float actual, float expected)
    {
        EXPECT_NEAR(actual, expected, 1e-5f);
    }

    void ExpectVectorNear(const Fvector& actual, const Fvector& expected)
    {
        ExpectFloatNear(actual.x, expected.x);
        ExpectFloatNear(actual.y, expected.y);
        ExpectFloatNear(actual.z, expected.z);
    }

    void ExpectVector4Near(const Fvector4& actual, const Fvector4& expected)
    {
        ExpectFloatNear(actual.x, expected.x);
        ExpectFloatNear(actual.y, expected.y);
        ExpectFloatNear(actual.z, expected.z);
        ExpectFloatNear(actual.w, expected.w);
    }
}

// ============================================================================
// CMemoryWriter
// ============================================================================

TEST(CMemoryWriter, StartsEmpty)
{
    CMemoryWriter writer;

    EXPECT_EQ(writer.pointer(), nullptr);
    EXPECT_EQ(writer.size(), 0u);
    EXPECT_EQ(writer.tell(), 0u);
}

TEST(CMemoryWriter, WritesBytes)
{
    CMemoryWriter writer;

    const std::array<u8, 4> data = {1, 2, 3, 4};

    writer.w(data.data(), static_cast<u32>(data.size()));

    ASSERT_NE(writer.pointer(), nullptr);
    ASSERT_EQ(writer.size(), data.size());
    EXPECT_EQ(writer.tell(), data.size());

    EXPECT_EQ(
        std::memcmp(writer.pointer(), data.data(), data.size()),
        0);
}

TEST(CMemoryWriter, MultipleWritesAreContiguous)
{
    CMemoryWriter writer;

    const u32 first = 0x11223344;
    const u16 second = 0x5566;
    const u8 third = 0x77;

    writer.w_u32(first);
    writer.w_u16(second);
    writer.w_u8(third);

    ASSERT_EQ(writer.size(), sizeof(first) + sizeof(second) + sizeof(third));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_u32(), first);
    EXPECT_EQ(reader.r_u16(), second);
    EXPECT_EQ(reader.r_u8(), third);
    EXPECT_EQ(reader.tell(), static_cast<int>(writer.size()));
    EXPECT_TRUE(reader.eof());
}

TEST(CMemoryWriter, SeekOverwritesExistingData)
{
    CMemoryWriter writer;

    writer.w_u32(0x11111111);
    writer.w_u32(0x22222222);

    ASSERT_EQ(writer.size(), 8u);

    writer.seek(0);
    writer.w_u32(0xAAAAAAAA);

    EXPECT_EQ(writer.size(), 8u);
    EXPECT_EQ(writer.tell(), 4u);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_u32(), 0xAAAAAAAAu);
    EXPECT_EQ(reader.r_u32(), 0x22222222u);
}

TEST(CMemoryWriter, ClearKeepsAllocatedStorageButResetsLogicalSize)
{
    CMemoryWriter writer;

    writer.w_u32(0x12345678);
    ASSERT_EQ(writer.size(), 4u);

    writer.clear();

    EXPECT_EQ(writer.size(), 0u);
    EXPECT_EQ(writer.tell(), 0u);

    // Existing storage remains allocated.
    EXPECT_NE(writer.pointer(), nullptr);

    writer.w_u32(0xAABBCCDD);

    EXPECT_EQ(writer.size(), 4u);
    EXPECT_EQ(writer.tell(), 4u);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_u32(), 0xAABBCCDDu);
}

TEST(CMemoryWriter, FreeReleasesStorage)
{
    CMemoryWriter writer;

    writer.w_u32(0x12345678);
    ASSERT_NE(writer.pointer(), nullptr);

    writer.free();

    EXPECT_EQ(writer.pointer(), nullptr);
    EXPECT_EQ(writer.size(), 0u);
    EXPECT_EQ(writer.tell(), 0u);
}

// ============================================================================
// Primitive serialization
// ============================================================================

TEST(IWriter, WritesUnsignedIntegers)
{
    CMemoryWriter writer;

    writer.w_u64(0x1122334455667788ull);
    writer.w_u32(0xAABBCCDDu);
    writer.w_u16(0xEEFFu);
    writer.w_u8(0x42u);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_u64(), 0x1122334455667788ull);
    EXPECT_EQ(reader.r_u32(), 0xAABBCCDDu);
    EXPECT_EQ(reader.r_u16(), 0xEEFFu);
    EXPECT_EQ(reader.r_u8(), 0x42u);
}

TEST(IWriter, WritesSignedIntegers)
{
    CMemoryWriter writer;

    writer.w_s64(-1234567890123ll);
    writer.w_s32(-123456789);
    writer.w_s16(-12345);
    writer.w_s8(-123);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_s64(), -1234567890123ll);
    EXPECT_EQ(reader.r_s32(), -123456789);
    EXPECT_EQ(reader.r_s16(), -12345);
    EXPECT_EQ(reader.r_s8(), -123);
}

TEST(IWriter, WritesFloat)
{
    CMemoryWriter writer;

    constexpr float value = 123.456f;
    writer.w_float(value);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_FLOAT_EQ(reader.r_float(), value);
}

TEST(IWriter, WritesVectors)
{
    CMemoryWriter writer;

    const Fvector2 v2 = {1.0f, 2.0f};
    const Fvector3 v3 = {3.0f, 4.0f, 5.0f};
    const Fvector4 v4 = {6.0f, 7.0f, 8.0f, 9.0f};

    writer.w_fvector2(v2);
    writer.w_fvector3(v3);
    writer.w_fvector4(v4);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    Fvector2 actual2;
    Fvector3 actual3;
    Fvector4 actual4;

    reader.r_fvector2(actual2);
    reader.r_fvector3(actual3);
    reader.r_fvector4(actual4);

    ExpectFloatNear(actual2.x, v2.x);
    ExpectFloatNear(actual2.y, v2.y);

    ExpectVectorNear(actual3, v3);
    ExpectVector4Near(actual4, v4);
}

TEST(IWriter, WritesColors)
{
    CMemoryWriter writer;

    const Fcolor color = {0.1f, 0.2f, 0.3f, 0.4f};

    writer.w_fcolor(color);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    Fcolor actual;
    reader.r_fcolor(actual);

    ExpectFloatNear(actual.r, color.r);
    ExpectFloatNear(actual.g, color.g);
    ExpectFloatNear(actual.b, color.b);
    ExpectFloatNear(actual.a, color.a);
}

// ============================================================================
// Strings
// ============================================================================

TEST(IWriter, WStringWritesCRLF)
{
    CMemoryWriter writer;

    writer.w_string("hello");

    ASSERT_EQ(writer.size(), 7u);

    const char expected[] = {'h', 'e', 'l', 'l', 'o', '\r', '\n'};

    EXPECT_EQ(
        std::memcmp(writer.pointer(), expected, sizeof(expected)),
        0);
}

TEST(IWriter, WStringZWritesNullTerminator)
{
    CMemoryWriter writer;

    writer.w_stringZ("hello");

    ASSERT_EQ(writer.size(), 6u);

    const char expected[] = "hello";

    EXPECT_EQ(
        std::memcmp(writer.pointer(), expected, sizeof(expected)),
        0);
}

TEST(IWriter, WStringZXrStringWritesNullTerminator)
{
    CMemoryWriter writer;

    const xr_string value = "hello world";

    writer.w_stringZ(value);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    xr_string result;
    reader.r_stringZ(result);

    EXPECT_EQ(result, value);
    EXPECT_EQ(reader.tell(), static_cast<int>(writer.size()));
}

TEST(IWriter, WStringZSharedStringRoundTrips)
{
    CMemoryWriter writer;

    shared_str value("hello shared string");

    writer.w_stringZ(value);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    shared_str result;
    reader.r_stringZ(result);

    EXPECT_STREQ(*result, *value);
    EXPECT_EQ(reader.tell(), static_cast<int>(writer.size()));
}

TEST(IReader, RStringZReadsNullTerminatedString)
{
    CMemoryWriter writer;

    writer.w_stringZ("hello");

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    char result[32] = {};
    reader.r_stringZ(result, sizeof(result));

    EXPECT_STREQ(result, "hello");
    EXPECT_EQ(reader.tell(), 6);
}

TEST(IReader, RStringReadsCRLFTerminatedString)
{
    CMemoryWriter writer;

    writer.w_string("hello");

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    char result[32] = {};
    reader.r_string(result, sizeof(result));

    EXPECT_STREQ(result, "hello");
    EXPECT_EQ(reader.tell(), 7);
}

TEST(IReader, RStringReadsMultipleTerminatorCharacters)
{
    const char data[] = "hello\r\n\nworld\r\n";

    IReader reader(
        const_cast<char*>(data),
        static_cast<int>(sizeof(data) - 1));

    char first[32] = {};
    char second[32] = {};

    reader.r_string(first, sizeof(first));
    reader.r_string(second, sizeof(second));

    EXPECT_STREQ(first, "hello");
    EXPECT_STREQ(second, "world");
}

// ============================================================================
// Positioning
// ============================================================================

TEST(IReader, StartsAtZero)
{
    const u32 value = 123;

    IReader reader(
        const_cast<u32*>(&value),
        sizeof(value));

    EXPECT_EQ(reader.tell(), 0);
    EXPECT_EQ(reader.elapsed(), static_cast<int>(sizeof(value)));
    EXPECT_EQ(reader.length(), static_cast<int>(sizeof(value)));
}

TEST(IReader, SeekChangesPosition)
{
    const u32 values[] = {
        0x11111111,
        0x22222222,
        0x33333333
    };

    IReader reader(
        const_cast<u32*>(values),
        sizeof(values));

    reader.seek(sizeof(u32));

    EXPECT_EQ(reader.tell(), static_cast<int>(sizeof(u32)));
    EXPECT_EQ(reader.r_u32(), 0x22222222u);
}

TEST(IReader, RewindReturnsToBeginning)
{
    CMemoryWriter writer;

    writer.w_u32(0x11111111);
    writer.w_u32(0x22222222);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_u32(), 0x11111111u);
    EXPECT_EQ(reader.r_u32(), 0x22222222u);

    reader.rewind();

    EXPECT_EQ(reader.tell(), 0);
    EXPECT_EQ(reader.r_u32(), 0x11111111u);
}

TEST(IReader, AdvanceChangesPosition)
{
    const std::array<u8, 8> data = {};

    IReader reader(
        const_cast<u8*>(data.data()),
        static_cast<int>(data.size()));

    reader.advance(3);

    EXPECT_EQ(reader.tell(), 3);
    EXPECT_EQ(reader.elapsed(), 5);
}

// ============================================================================
// Chunks
// ============================================================================

TEST(IWriter, OpenAndCloseChunkProducesExpectedHeader)
{
    CMemoryWriter writer;

    writer.open_chunk(1234);
    writer.w_u32(0xAABBCCDD);
    writer.close_chunk();

    ASSERT_EQ(writer.size(), 12u);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_u32(), 1234u);
    EXPECT_EQ(reader.r_u32(), 4u);
    EXPECT_EQ(reader.r_u32(), 0xAABBCCDDu);
}

TEST(IWriter, ChunkSizeIsZeroWithoutOpenChunk)
{
    CMemoryWriter writer;

    EXPECT_EQ(writer.chunk_size(), 0u);
}

TEST(IWriter, ChunkSizeTracksCurrentChunk)
{
    CMemoryWriter writer;

    writer.open_chunk(1);

    EXPECT_EQ(writer.chunk_size(), 0u);

    writer.w_u32(0x12345678);

    EXPECT_EQ(writer.chunk_size(), 4u);

    writer.w_u16(0x1234);

    EXPECT_EQ(writer.chunk_size(), 6u);

    writer.close_chunk();

    EXPECT_EQ(writer.chunk_size(), 0u);
}

TEST(IWriter, NestedChunksHaveIndependentSizes)
{
    CMemoryWriter writer;

    writer.open_chunk(1);
    writer.w_u32(0xAAAAAAAA);

    writer.open_chunk(2);
    writer.w_u32(0xBBBBBBBB);

    EXPECT_EQ(writer.chunk_size(), 4u);

    writer.close_chunk();

    EXPECT_EQ(writer.chunk_size(), 12u);

    writer.close_chunk();

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.r_u32(), 1u);
    EXPECT_EQ(reader.r_u32(), 16u);
    EXPECT_EQ(reader.r_u32(), 0xAAAAAAAAu);

    EXPECT_EQ(reader.r_u32(), 2u);
    EXPECT_EQ(reader.r_u32(), 4u);
    EXPECT_EQ(reader.r_u32(), 0xBBBBBBBBu);
}

TEST(IWriter, WChunkCanBeReadWithFindChunk)
{
    CMemoryWriter writer;

    const u32 value = 0x12345678;

    writer.w_chunk(100, const_cast<u32*>(&value), sizeof(value));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.find_chunk(100), sizeof(value));

    const u32 result = reader.r_u32();

    EXPECT_EQ(result, value);
}

TEST(IReader, FindChunkReturnsZeroForMissingChunk)
{
    CMemoryWriter writer;

    const u32 value = 0x12345678;

    writer.w_chunk(100, const_cast<u32*>(&value), sizeof(value));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_EQ(reader.find_chunk(999), 0u);
}

TEST(IReader, OpenChunkReturnsReadableReader)
{
    CMemoryWriter writer;

    const u32 values[] = {
        0x11111111,
        0x22222222,
        0x33333333
    };

    writer.w_chunk(
        100,
        const_cast<u32*>(values),
        sizeof(values));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    IReader* chunk = reader.open_chunk(100);

    ASSERT_NE(chunk, nullptr);

    EXPECT_EQ(chunk->r_u32(), values[0]);
    EXPECT_EQ(chunk->r_u32(), values[1]);
    EXPECT_EQ(chunk->r_u32(), values[2]);

    chunk->close();
}

TEST(IReader, OpenChunkReturnsNullForMissingChunk)
{
    CMemoryWriter writer;

    const u32 value = 123;

    writer.w_chunk(
        100,
        const_cast<u32*>(&value),
        sizeof(value));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    IReader* chunk = reader.open_chunk(999);

    EXPECT_EQ(chunk, nullptr);
}

// ============================================================================
// Chunk iteration
// ============================================================================

TEST(IReader, OpenChunkIteratorEnumeratesChunks)
{
    CMemoryWriter writer;

    const u32 value1 = 111;
    const u32 value2 = 222;
    const u32 value3 = 333;

    writer.w_chunk(10, const_cast<u32*>(&value1), sizeof(value1));
    writer.w_chunk(20, const_cast<u32*>(&value2), sizeof(value2));
    writer.w_chunk(30, const_cast<u32*>(&value3), sizeof(value3));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    u32 id = 0;

    IReader* chunk = reader.open_chunk_iterator(id);

    ASSERT_NE(chunk, nullptr);
    EXPECT_EQ(id, 10u);
    EXPECT_EQ(chunk->r_u32(), value1);

    chunk = reader.open_chunk_iterator(id, chunk);

    ASSERT_NE(chunk, nullptr);
    EXPECT_EQ(id, 20u);
    EXPECT_EQ(chunk->r_u32(), value2);

    chunk = reader.open_chunk_iterator(id, chunk);

    ASSERT_NE(chunk, nullptr);
    EXPECT_EQ(id, 30u);
    EXPECT_EQ(chunk->r_u32(), value3);

    chunk = reader.open_chunk_iterator(id, chunk);

    EXPECT_EQ(chunk, nullptr);
}

TEST(IReader, OpenChunkIteratorOnEmptyReaderReturnsNull)
{
    CMemoryWriter writer;

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    u32 id = 0;

    EXPECT_EQ(reader.open_chunk_iterator(id), nullptr);
}

// ============================================================================
// Quantization
// ============================================================================

TEST(IWriter, FloatQ8RoundTripsEndpoints)
{
    CMemoryWriter writer;

    writer.w_float_q8(0.0f, 0.0f, 1.0f);
    writer.w_float_q8(1.0f, 0.0f, 1.0f);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_FLOAT_EQ(reader.r_float_q8(0.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(reader.r_float_q8(0.0f, 1.0f), 1.0f);
}

TEST(IWriter, FloatQ16RoundTripsEndpoints)
{
    CMemoryWriter writer;

    writer.w_float_q16(0.0f, 0.0f, 1.0f);
    writer.w_float_q16(1.0f, 0.0f, 1.0f);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    EXPECT_FLOAT_EQ(reader.r_float_q16(0.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(reader.r_float_q16(0.0f, 1.0f), 1.0f);
}

TEST(IWriter, FloatQ8RoundTripsRepresentativeValues)
{
    constexpr std::array<float, 7> values = {
        0.0f,
        0.1f,
        0.25f,
        0.5f,
        0.75f,
        0.9f,
        1.0f
    };

    CMemoryWriter writer;

    for (const float value : values)
        writer.w_float_q8(value, 0.0f, 1.0f);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    for (const float expected : values)
    {
        const float actual = reader.r_float_q8(0.0f, 1.0f);

        // 8-bit quantization has an expected maximum error of roughly
        // half a quantization step.
        EXPECT_NEAR(actual, expected, 1.0f / 255.0f);
    }
}

TEST(IWriter, FloatQ16RoundTripsRepresentativeValues)
{
    constexpr std::array<float, 7> values = {
        0.0f,
        0.1f,
        0.25f,
        0.5f,
        0.75f,
        0.9f,
        1.0f
    };

    CMemoryWriter writer;

    for (const float value : values)
        writer.w_float_q16(value, 0.0f, 1.0f);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    for (const float expected : values)
    {
        const float actual = reader.r_float_q16(0.0f, 1.0f);

        EXPECT_NEAR(actual, expected, 1.0f / 65535.0f);
    }
}

// ============================================================================
// Direction serialization
// ============================================================================

TEST(IWriter, DirectionRoundTrips)
{
    CMemoryWriter writer;

    Fvector original;
    original.set(1.0f, 0.0f, 0.0f);

    writer.w_dir(original);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    Fvector result;
    reader.r_dir(result);

    ExpectVectorNear(result, original);
}

TEST(IWriter, SdirStoresDirectionAndMagnitude)
{
    CMemoryWriter writer;

    Fvector original;
    original.set(3.0f, 4.0f, 0.0f);

    writer.w_sdir(original);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    Fvector result;
    reader.r_sdir(result);

    EXPECT_NEAR(result.magnitude(), original.magnitude(), 0.01f);

    Fvector normalizedOriginal;
    normalizedOriginal.set(original);
    normalizedOriginal.normalize();

    Fvector normalizedResult;
    normalizedResult.set(result);
    normalizedResult.normalize();

    ExpectVectorNear(normalizedResult, normalizedOriginal);
}

TEST(IWriter, SdirZeroVectorRoundTrips)
{
    CMemoryWriter writer;

    Fvector original;
    original.set(0.0f, 0.0f, 0.0f);

    writer.w_sdir(original);

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    Fvector result;
    reader.r_sdir(result);

    EXPECT_NEAR(result.x, 0.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.0f, 1e-5f);
    EXPECT_NEAR(result.z, 0.0f, 1e-5f);
    EXPECT_NEAR(result.magnitude(), 0.0f, 1e-5f);
}

// ============================================================================
// Compression
// ============================================================================

TEST(IWriter, CompressedChunkRoundTrips)
{
    std::vector<u8> source;

    for (int i = 0; i < 4096; ++i)
    {
        source.push_back(static_cast<u8>(i % 16));
    }

    CMemoryWriter writer;

    writer.w_chunk(
        CFS_CompressMark | 123,
        source.data(),
        static_cast<u32>(source.size()));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    BOOL compressed = FALSE;

    const u32 size = reader.find_chunk(
        CFS_CompressMark | 123,
        &compressed);

    EXPECT_EQ(size, writer.size() - 8);
    EXPECT_TRUE(compressed);

    reader.rewind();

    IReader* chunk = reader.open_chunk(CFS_CompressMark | 123);

    ASSERT_NE(chunk, nullptr);
    ASSERT_EQ(chunk->length(), source.size());

    std::vector<u8> result(source.size());

    chunk->r(result.data(), static_cast<int>(result.size()));

    EXPECT_EQ(result, source);

    chunk->close();
}

// ============================================================================
// Compression marker handling
// ============================================================================

TEST(IReader, FindChunkReportsUncompressedChunk)
{
    CMemoryWriter writer;

    const u32 value = 123;

    writer.w_chunk(
        123,
        const_cast<u32*>(&value),
        sizeof(value));

    IReader reader = IReader(
        writer.pointer(),
        static_cast<int>(writer.size()));

    BOOL compressed = TRUE;

    EXPECT_EQ(
        reader.find_chunk(123, &compressed),
        sizeof(value));

    EXPECT_FALSE(compressed);
}

// ============================================================================
// w_printf
// ============================================================================

TEST(IWriter, WPrintfWritesFormattedText)
{
    CMemoryWriter writer;

    writer.w_printf(
        "value=%d name=%s float=%.2f",
        42,
        "test",
        1.25f);

    const char expected[] = "value=42 name=test float=1.25";

    ASSERT_EQ(writer.size(), sizeof(expected) - 1);

    EXPECT_EQ(
        std::memcmp(writer.pointer(), expected, sizeof(expected) - 1),
        0);
}

// ============================================================================
// Alignment
// ============================================================================

#if 0
TEST(IWriter, AlignMovesPositionToExpectedBoundary)
{
    CMemoryWriter writer;

    writer.w_u8(0x42);

    const u32 aligned = writer.align();

    EXPECT_EQ(writer.tell() % 16, 0u);
    EXPECT_EQ(aligned, writer.tell());
}

TEST(IWriter, AlignDoesNothingWhenAlreadyAligned)
{
    CMemoryWriter writer;

    std::array<u8, 16> data = {};

    writer.w(data.data(), static_cast<u32>(data.size()));

    ASSERT_EQ(writer.tell(), 16u);

    const u32 position = writer.align();

    EXPECT_EQ(position, 16u);
    EXPECT_EQ(writer.tell(), 16u);
}
#endif
