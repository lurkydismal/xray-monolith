#include "stdafx.h"

#include "clsid.h"

#include <gtest/gtest.h>

#include <cstring>
#include <limits>
#include <string>

// -----------------------------------------------------------------------------
// MK_CLSID
// -----------------------------------------------------------------------------

TEST(CLSIDTest, MKCLSIDPacksEightBytesInOrder)
{
    const CLASS_ID id = MK_CLSID(
        'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H');

    constexpr CLASS_ID expected =
        (CLASS_ID('A') << 56) |
        (CLASS_ID('B') << 48) |
        (CLASS_ID('C') << 40) |
        (CLASS_ID('D') << 32) |
        (CLASS_ID('E') << 24) |
        (CLASS_ID('F') << 16) |
        (CLASS_ID('G') << 8) |
        CLASS_ID('H');

    EXPECT_EQ(id, expected);
}

TEST(CLSIDTest, MKCLSIDPreservesAllEightBytes)
{
    const CLASS_ID id = MK_CLSID(
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xab, 0xcd, 0xef);

    EXPECT_EQ(id, 0x0123456789abcdefULL);
}

TEST(CLSIDTest, MKCLSIDHandlesZeroBytes)
{
    EXPECT_EQ(
        MK_CLSID(0, 0, 0, 0, 0, 0, 0, 0),
        CLASS_ID(0));
}

TEST(CLSIDTest, MKCLSIDHandlesMaximumByteValues)
{
    EXPECT_EQ(
        MK_CLSID(
            0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff),
        std::numeric_limits<CLASS_ID>::max());
}

TEST(CLSIDTest, MKCLSIDDoesNotSwapByteOrder)
{
    const CLASS_ID normal = MK_CLSID(
        'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H');

    const CLASS_ID inverse = MK_CLSID(
        'H', 'G', 'F', 'E',
        'D', 'C', 'B', 'A');

    EXPECT_NE(normal, inverse);
}

// -----------------------------------------------------------------------------
// MK_CLSID_INV
// -----------------------------------------------------------------------------

TEST(CLSIDTest, MKCLSIDINVReversesArguments)
{
    const CLASS_ID normal = MK_CLSID(
        'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H');

    const CLASS_ID inverse = MK_CLSID_INV(
        'H', 'G', 'F', 'E',
        'D', 'C', 'B', 'A');

    EXPECT_EQ(inverse, normal);
}

TEST(CLSIDTest, MKCLSIDINVIsEquivalentToReversedMKCLSID)
{
    const CLASS_ID inv = MK_CLSID_INV(
        1, 2, 3, 4,
        5, 6, 7, 8);

    const CLASS_ID expected = MK_CLSID(
        8, 7, 6, 5,
        4, 3, 2, 1);

    EXPECT_EQ(inv, expected);
}

TEST(CLSIDTest, MKCLSIDINVWithIdenticalBytesEqualsMKCLSID)
{
    const CLASS_ID a = MK_CLSID_INV(
        'X', 'X', 'X', 'X',
        'X', 'X', 'X', 'X');

    const CLASS_ID b = MK_CLSID(
        'X', 'X', 'X', 'X',
        'X', 'X', 'X', 'X');

    EXPECT_EQ(a, b);
}

// -----------------------------------------------------------------------------
// CLSID2TEXT
// -----------------------------------------------------------------------------

TEST(CLSIDTest, CLSID2TEXTConvertsEightCharacters)
{
    char text[9] = {};

    const CLASS_ID id = MK_CLSID(
        'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H');

    CLSID2TEXT(id, text);

    EXPECT_STREQ(text, "ABCDEFGH");
}

TEST(CLSIDTest, CLSID2TEXTProducesExactlyEightCharacters)
{
    char text[9];

    std::memset(text, 'X', sizeof(text));

    const CLASS_ID id = MK_CLSID(
        'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H');

    CLSID2TEXT(id, text);

    EXPECT_EQ(text[8], '\0');

    for (int i = 0; i < 8; ++i)
        EXPECT_NE(text[i], '\0');
}

TEST(CLSIDTest, CLSID2TEXTConvertsZero)
{
    char text[9];

    const CLASS_ID id = 0;

    CLSID2TEXT(id, text);

    EXPECT_EQ(text[8], '\0');

    for (int i = 0; i < 8; ++i)
        EXPECT_EQ(text[i], '\0');
}

TEST(CLSIDTest, CLSID2TEXTPreservesByteValues)
{
    char text[9] = {};

    const CLASS_ID id = MK_CLSID(
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xab, 0xcd, 0xef);

    CLSID2TEXT(id, text);

    EXPECT_EQ(static_cast<unsigned char>(text[0]), 0x01);
    EXPECT_EQ(static_cast<unsigned char>(text[1]), 0x23);
    EXPECT_EQ(static_cast<unsigned char>(text[2]), 0x45);
    EXPECT_EQ(static_cast<unsigned char>(text[3]), 0x67);
    EXPECT_EQ(static_cast<unsigned char>(text[4]), 0x89);
    EXPECT_EQ(static_cast<unsigned char>(text[5]), 0xab);
    EXPECT_EQ(static_cast<unsigned char>(text[6]), 0xcd);
    EXPECT_EQ(static_cast<unsigned char>(text[7]), 0xef);
    EXPECT_EQ(text[8], '\0');
}

TEST(CLSIDTest, CLSID2TEXTDoesNotModifyBytesAfterOutput)
{
    char text[12];

    std::memset(text, 'X', sizeof(text));

    const CLASS_ID id = MK_CLSID(
        'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H');

    CLSID2TEXT(id, text);

    EXPECT_STREQ(text, "ABCDEFGH");

    EXPECT_EQ(text[9], 'X');
    EXPECT_EQ(text[10], 'X');
    EXPECT_EQ(text[11], 'X');
}

// -----------------------------------------------------------------------------
// TEXT2CLSID
// -----------------------------------------------------------------------------

TEST(CLSIDTest, TEXT2CLSIDConvertsEightCharacters)
{
    const CLASS_ID id = TEXT2CLSID("ABCDEFGH");

    EXPECT_EQ(
        id,
        MK_CLSID(
            'A', 'B', 'C', 'D',
            'E', 'F', 'G', 'H'));
}

TEST(CLSIDTest, TEXT2CLSIDPadsShortTextWithSpaces)
{
    const CLASS_ID id = TEXT2CLSID("ABC");

    EXPECT_EQ(
        id,
        MK_CLSID(
            'A', 'B', 'C', ' ',
            ' ', ' ', ' ', ' '));
}

TEST(CLSIDTest, TEXT2CLSIDPadsOneCharacter)
{
    const CLASS_ID id = TEXT2CLSID("A");

    EXPECT_EQ(
        id,
        MK_CLSID(
            'A', ' ', ' ', ' ',
            ' ', ' ', ' ', ' '));
}

TEST(CLSIDTest, TEXT2CLSIDEmptyStringProducesEightSpaces)
{
    const CLASS_ID id = TEXT2CLSID("");

    EXPECT_EQ(
        id,
        MK_CLSID(
            ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' '));
}

TEST(CLSIDTest, TEXT2CLSIDPreservesExistingSpaces)
{
    const CLASS_ID id = TEXT2CLSID("A B");

    EXPECT_EQ(
        id,
        MK_CLSID(
            'A', ' ', 'B', ' ',
            ' ', ' ', ' ', ' '));
}

TEST(CLSIDTest, TEXT2CLSIDUsesOnlyFirstEightCharacters)
{
    const CLASS_ID id = TEXT2CLSID("ABCDEFGH");

    EXPECT_EQ(
        id,
        0x4142434445464748ULL);
}

// -----------------------------------------------------------------------------
// Round trips
// -----------------------------------------------------------------------------

TEST(CLSIDTest, TextToClassIdToTextRoundTrip)
{
    constexpr const char* input = "ABCDEFGH";

    const CLASS_ID id = TEXT2CLSID(input);

    char output[9] = {};
    CLSID2TEXT(id, output);

    EXPECT_STREQ(output, input);
}

TEST(CLSIDTest, ShortTextRoundTripIncludesSpacePadding)
{
    const CLASS_ID id = TEXT2CLSID("ABC");

    char output[9] = {};
    CLSID2TEXT(id, output);

    EXPECT_EQ(output[0], 'A');
    EXPECT_EQ(output[1], 'B');
    EXPECT_EQ(output[2], 'C');

    for (int i = 3; i < 8; ++i)
        EXPECT_EQ(output[i], ' ');

    EXPECT_EQ(output[8], '\0');
}

TEST(CLSIDTest, ClassIdToTextToClassIdRoundTrip)
{
    const CLASS_ID original = MK_CLSID(
        '1', '2', '3', '4',
        '5', '6', '7', '8');

    char text[9] = {};
    CLSID2TEXT(original, text);

    const CLASS_ID result = TEXT2CLSID(text);

    EXPECT_EQ(result, original);
}

TEST(CLSIDTest, AllByteValuesRoundTrip)
{
    const CLASS_ID original = MK_CLSID(
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xab, 0xcd, 0xef);

    char text[9] = {};
    CLSID2TEXT(original, text);

    const CLASS_ID result = TEXT2CLSID(text);

    EXPECT_EQ(result, original);
}

// -----------------------------------------------------------------------------
// ABI / type properties
// -----------------------------------------------------------------------------

TEST(CLSIDTest, CLASSIDIsEightBytes)
{
    EXPECT_EQ(sizeof(CLASS_ID), sizeof(u64));
}

TEST(CLSIDTest, CLASSIDIsUnsigned)
{
    EXPECT_TRUE(std::is_unsigned_v<CLASS_ID>);
}
