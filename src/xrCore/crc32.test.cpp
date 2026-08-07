#include "stdafx.h"

#include "crc32.hpp"

#include <gtest/gtest.h>

#include <array>
#include <cstring>
#include <string>


namespace
{
    TEST(CRC32_PublicAPI, KnownVectors)
    {
        // These values correspond to the SSE4.2 CRC32C path used by modern CPUs.
        // If running without SSE4.2, the expected values will differ because the
        // implementation falls back to IEEE CRC32.
        if (CPU::ID.feature & _CPU_FEATURE_SSE4_2)
        {
            EXPECT_EQ(crc32("", 0), 0x00000000u);
            EXPECT_EQ(crc32("123456789", 9), 0xE3069283u);
            EXPECT_EQ(crc32("hello", 5), 0x9A71BB4Cu);
        }
        else
        {
            EXPECT_EQ(crc32("", 0), 0x00000000u);
            EXPECT_EQ(crc32("123456789", 9), 0xCBF43926u);
            EXPECT_EQ(crc32("hello", 5), 0x3610A686u);
        }
    }


    TEST(CRC32_PublicAPI, EmptyInput)
    {
        EXPECT_EQ(crc32(nullptr, 0), 0u);
        EXPECT_EQ(crc32(nullptr, 0, 0x12345678u), 0x12345678u);
    }


    TEST(CRC32_PublicAPI, SeedChangesResult)
    {
        const char* text = "XRay";

        const u32 a =
            crc32(text, 4, 0);

        const u32 b =
            crc32(text, 4, 0x12345678u);

        EXPECT_NE(a, b);
    }


    TEST(CRC32_Internal, SSE42KnownValues)
    {
        EXPECT_EQ(
            crc32_internal::crc32_sse42(
                "123456789",
                9,
                0xffffffffu),
            0x1CF96D7Cu);
    }


    TEST(CRC32_Internal, TableKnownValues)
    {
        EXPECT_EQ(
            crc32_internal::crc32_table_based(
                "123456789",
                9,
                0xffffffffu)
            ^ 0xffffffffu,
            0xCBF43926u);
    }


    TEST(CRC32_Internal, TablePathIsStable)
    {
        const std::string input =
            "X-Ray Engine regression test";

        const u32 result =
            crc32_internal::crc32_table_based(
                input.data(),
                static_cast<u32>(input.size()),
                0xffffffffu)
            ^ 0xffffffffu;

        EXPECT_EQ(result, 0xDD5BCBC9u);
    }


    TEST(CRC32_Internal, SSE42PathIsStable)
    {
        const std::string input =
            "X-Ray Engine regression test";

        const u32 result =
            crc32_internal::crc32_sse42(
                input.data(),
                static_cast<u32>(input.size()),
                0xffffffffu);

        EXPECT_EQ(result, 0x1F1C2284u);
    }


    TEST(CRC32_Internal, DifferentAlgorithmsAreNotCompared)
    {
        const char* text = "123456789";

        const u32 sse =
            crc32_internal::crc32_sse42(
                text,
                9,
                0xffffffffu);

        const u32 table =
            crc32_internal::crc32_table_based(
                text,
                9,
                0xffffffffu)
            ^ 0xffffffffu;


        // Important:
        // these are different CRC polynomials.
        EXPECT_NE(sse, table);
    }


    TEST(CRC32_Internal, IncrementalMatchesSinglePass)
    {
        constexpr auto a = std::to_array("X-Ray ");
        constexpr auto b = std::to_array("Engine");
        constexpr auto ab = std::to_array("X-Ray Engine");

        const u32 crc =
            crc32_internal::crc32_sse42(
                ab.data(),
                ab.size() - 1,
                0xffffffffu);


        u32 split =
            crc32_internal::crc32_sse42(
                a.data(),
                a.size() - 1,
                0xffffffffu);

        split =
            crc32_internal::crc32_sse42(
                b.data(),
                b.size() - 1,
                split);


        EXPECT_EQ(split, crc);
    }


    TEST(CRC32, BinaryData)
    {
        std::array<u8, 256> data{};

        for (size_t i = 0; i < data.size(); ++i)
            data[i] = static_cast<u8>(i);


        EXPECT_NE(
            crc32(data.data(), static_cast<u32>(data.size())),
            0u);
    }


    TEST(PathCRC32, SeparatorsAreIgnored)
    {
        const char* unix =
            "gamedata/config/system.ltx";

        const char* windows =
            "gamedata\\config\\system.ltx";


        EXPECT_EQ(
            path_crc32(
                unix,
                static_cast<u32>(strlen(unix))),
            path_crc32(
                windows,
                static_cast<u32>(strlen(windows))));
    }


    TEST(PathCRC32, EmptyPath)
    {
        EXPECT_EQ(
            path_crc32("", 0),
            0u);
    }


    TEST(PathCRC32, FilenameCaseMatters)
    {
        const char* a =
            "gamedata/config/system.ltx";

        const char* b =
            "gamedata/config/System.ltx";


        EXPECT_NE(
            path_crc32(a, strlen(a)),
            path_crc32(b, strlen(b)));
    }
}
