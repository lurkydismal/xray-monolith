#include "crc32.hpp"

#include <gtest/gtest.h>

#include <cstring>
#include <string>

namespace
{
    // Standard CRC-32/ISO-HDLC check values (same algorithm this table/poly
    // implements: reflected in/out, init 0xFFFFFFFF, final XOR 0xFFFFFFFF).
    constexpr u32 kCrcEmpty      = 0x00000000u;
    constexpr u32 kCrcCheckAscii = 0xCBF43926u; // "123456789"
    constexpr u32 kCrcFox        = 0x414FA339u; // "The quick brown fox jumps over the lazy dog"

    using EngineFn = u32 (*)(const void*, u32, u32) noexcept;

    // Wraps a raw accumulator engine with the standard init/final-XOR so it
    // can be compared directly against known CRC-32 test vectors.
    u32 full_crc(EngineFn engine, const void* data, u32 len)
    {
        return engine(data, len, 0xffffffffu) ^ 0xffffffffu;
    }

    // Mirrors the public crc32(data, len, starting_crc) chaining contract,
    // but pinned to one specific engine so each path is tested in isolation.
    u32 chained_crc(EngineFn engine, const void* part1, u32 len1,
                                      const void* part2, u32 len2)
    {
        u32 first = full_crc(engine, part1, len1);
        return engine(part2, len2, ~first) ^ 0xffffffffu;
    }
}

class Crc32EngineTest : public ::testing::TestWithParam<EngineFn>
{
};

// ---- Happy path: known standard CRC-32 test vectors ----

TEST_P(Crc32EngineTest, EmptyInputIsZero)
{
    EXPECT_EQ(full_crc(GetParam(), "", 0), kCrcEmpty);
}

TEST_P(Crc32EngineTest, StandardCheckVectorAscii123456789)
{
    const char* data = "123456789";
    EXPECT_EQ(full_crc(GetParam(), data, 9), kCrcCheckAscii);
}

TEST_P(Crc32EngineTest, StandardCheckVectorFoxSentence)
{
    const char* data = "The quick brown fox jumps over the lazy dog";
    EXPECT_EQ(full_crc(GetParam(), data, static_cast<u32>(std::strlen(data))), kCrcFox);
}

// ---- Edge cases: lengths around the 8/4/2/1-byte chunking boundaries ----
// (Only crc32_sse42 branches on these, but running both engines here
//  guarantees they agree at every remainder combination.)

TEST_P(Crc32EngineTest, AllLengthsZeroThroughSeventeenAgreeWithTableReference)
{
    // Independently-computed reference: same table-driven algorithm,
    // hand-inlined here so this test doesn't depend on the engine under test.
    static const u8 pattern[24] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17
    };

    for (u32 len = 0; len <= 17; ++len)
    {
        u32 actual = full_crc(GetParam(), pattern, len);
        u32 expected = full_crc(&crc32_internal::crc32_table_based, pattern, len);
        EXPECT_EQ(actual, expected) << "mismatch at len=" << len;
    }
}

TEST_P(Crc32EngineTest, SingleByteInputs)
{
    for (int b = 0; b <= 0xFF; b += 37) // sample across the byte range
    {
        u8 byte = static_cast<u8>(b);
        u32 actual = full_crc(GetParam(), &byte, 1);
        u32 expected = full_crc(&crc32_internal::crc32_table_based, &byte, 1);
        EXPECT_EQ(actual, expected) << "mismatch at byte=" << b;
    }
}

// ---- Chaining / incremental hashing ----

TEST_P(Crc32EngineTest, ChainingMatchesWholeBufferAtEverySplitPoint)
{
    const std::string whole = "The quick brown fox jumps over the lazy dog";
    const u32 wholeLen = static_cast<u32>(whole.size());
    const u32 wholeCrc = full_crc(GetParam(), whole.data(), wholeLen);

    for (u32 split = 0; split <= wholeLen; ++split)
    {
        u32 chained = chained_crc(GetParam(), whole.data(), split,
                                   whole.data() + split, wholeLen - split);
        EXPECT_EQ(chained, wholeCrc) << "mismatch splitting at " << split;
    }
}

INSTANTIATE_TEST_SUITE_P(
    BothEngines,
    Crc32EngineTest,
    ::testing::Values(&crc32_internal::crc32_sse42, &crc32_internal::crc32_table_based),
    [](const ::testing::TestParamInfo<EngineFn>& info) {
        return info.param == &crc32_internal::crc32_sse42 ? "SSE42" : "TableBased";
    });

// ---- Public API dispatch sanity (exercises whichever path CPU::ID picks) ----

TEST(Crc32PublicApi, EmptyInputIsZero)
{
    EXPECT_EQ(crc32("", 0), kCrcEmpty);
}

TEST(Crc32PublicApi, StandardCheckVector)
{
    EXPECT_EQ(crc32("123456789", 9), kCrcCheckAscii);
}

TEST(Crc32PublicApi, ThreeArgOverloadChainsToSameResultAsOneShot)
{
    const std::string whole = "123456789";
    u32 oneShot = crc32(whole.data(), static_cast<u32>(whole.size()));

    u32 partial = crc32(whole.data(), 4);                 // "1234"
    u32 chained = crc32(whole.data() + 4, static_cast<u32>(whole.size()) - 4, partial); // "56789"

    EXPECT_EQ(chained, oneShot);
}

// ---- path_crc32 ----

TEST(PathCrc32, EmptyPathIsZero)
{
    EXPECT_EQ(path_crc32("", 0), kCrcEmpty);
}

TEST(PathCrc32, PathWithNoSlashesMatchesPlainCrc32)
{
    const char* path = "abcxyz";
    EXPECT_EQ(path_crc32(path, 6), crc32(path, 6));
}

TEST(PathCrc32, ForwardSlashesAreStripped)
{
    const char* path = "a/b/c";
    EXPECT_EQ(path_crc32(path, 5), crc32("abc", 3));
}

TEST(PathCrc32, BackslashesAreStripped)
{
    const char* path = "a\\b\\c";
    EXPECT_EQ(path_crc32(path, 5), crc32("abc", 3));
}

TEST(PathCrc32, MixedLeadingTrailingAndEmbeddedSlashes)
{
    const char* path = "/a\\b/c\\";
    EXPECT_EQ(path_crc32(path, static_cast<u32>(std::strlen(path))), crc32("abc", 3));
}

TEST(PathCrc32, PathOfOnlySlashesIsZero)
{
    const char* path = "///\\\\/";
    EXPECT_EQ(path_crc32(path, static_cast<u32>(std::strlen(path))), kCrcEmpty);
}
