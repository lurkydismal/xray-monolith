#include "stdafx.h"

#include "string_concatenations.h"

#include <gtest/gtest.h>

namespace
{
TEST(StringConcatenations, StrconcatTwoStrings)
{
    char buffer[32] = {};

    char* result = strconcat(sizeof(buffer), buffer, "Hello", " World");

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "Hello World");
}

TEST(StringConcatenations, StrconcatThreeStrings)
{
    char buffer[32] = {};

    char* result = strconcat(sizeof(buffer), buffer, "Hello", " ", "World");

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "Hello World");
}

TEST(StringConcatenations, StrconcatFourStrings)
{
    char buffer[32] = {};

    char* result = strconcat(
        sizeof(buffer),
        buffer,
        "one",
        "two",
        "three",
        "four"
    );

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "onetwothreefour");
}

TEST(StringConcatenations, StrconcatFiveStrings)
{
    char buffer[32] = {};

    char* result = strconcat(
        sizeof(buffer),
        buffer,
        "one",
        "two",
        "three",
        "four",
        "five"
    );

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "onetwothreefourfive");
}

TEST(StringConcatenations, StrconcatSixStrings)
{
    char buffer[32] = {};

    char* result = strconcat(
        sizeof(buffer),
        buffer,
        "one",
        "two",
        "three",
        "four",
        "five",
        "six"
    );

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "onetwothreefourfivesix");
}

TEST(StringConcatenations, StrconcatEmptyStrings)
{
    char buffer[32] = {};

    char* result = strconcat(
        sizeof(buffer),
        buffer,
        "",
        "",
        "hello",
        "",
        "world",
        ""
    );

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "helloworld");
}

TEST(StringConcatenations, StrconcatSingleNonEmptyString)
{
    char buffer[32] = {};

    char* result = strconcat(sizeof(buffer), buffer, "", "hello");

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "hello");
}

TEST(StringConcatenations, StrconcatExactFit)
{
    // 5 characters + terminating NUL.
    char buffer[6] = {};

    char* result = strconcat(sizeof(buffer), buffer, "he", "llo");

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "hello");
}

TEST(StringConcatenations, StrconcatLeavesTerminator)
{
    char buffer[32];

    // Deliberately poison the buffer so that we don't accidentally
    // pass this test because it happened to contain zeroes.
    std::fill(std::begin(buffer), std::end(buffer), 'X');

    strconcat(sizeof(buffer), buffer, "abc", "def");

    EXPECT_EQ(buffer[6], '\0');
    EXPECT_EQ(buffer[7], 'X');
    EXPECT_STREQ(buffer, "abcdef");
}


TEST(StringConcatSingle, CopiesCompleteString)
{
    char buffer[16] = {};
    char* cursor = buffer;
    char* end = buffer + sizeof(buffer);

    EXPECT_TRUE(_strconcatSingle(cursor, end, "hello"));

    EXPECT_EQ(cursor, buffer + 5);
    EXPECT_STREQ(buffer, "hello");
}

TEST(StringConcatSingle, CopiesMultipleStringsSequentially)
{
    char buffer[16] = {};
    char* cursor = buffer;
    char* end = buffer + sizeof(buffer);

    EXPECT_TRUE(_strconcatSingle(cursor, end, "hello"));
    EXPECT_TRUE(_strconcatSingle(cursor, end, " "));
    EXPECT_TRUE(_strconcatSingle(cursor, end, "world"));

    *cursor = '\0';

    EXPECT_STREQ(buffer, "hello world");
    EXPECT_EQ(cursor, buffer + 11);
}

TEST(StringConcatSingle, ExactFitLeavesRoomForTerminator)
{
    // Five characters, six bytes including NUL.
    char buffer[6] = {};
    char* cursor = buffer;
    char* end = buffer + sizeof(buffer);

    EXPECT_TRUE(_strconcatSingle(cursor, end, "hello"));

    EXPECT_EQ(cursor, buffer + 5);

    *cursor = '\0';

    EXPECT_STREQ(buffer, "hello");
}

TEST(StringConcatSingle, ReportsTruncation)
{
    char buffer[6] = {};
    char* cursor = buffer;
    char* end = buffer + sizeof(buffer);

    EXPECT_FALSE(_strconcatSingle(cursor, end, "hello!"));

    // The implementation fills the buffer up to end - 1.
    EXPECT_EQ(cursor, end - 1);

    *cursor = '\0';

    EXPECT_STREQ(buffer, "hello");
}

TEST(StringConcatSingle, EmptyStringSucceeds)
{
    char buffer[16] = {};
    char* cursor = buffer;
    char* end = buffer + sizeof(buffer);

    EXPECT_TRUE(_strconcatSingle(cursor, end, ""));

    EXPECT_EQ(cursor, buffer);
}

TEST(StringConcatSingle, NullStringSucceedsWithoutWriting)
{
    char buffer[16] = {};
    char* cursor = buffer;
    char* end = buffer + sizeof(buffer);

    EXPECT_TRUE(_strconcatSingle(cursor, end, nullptr));

    EXPECT_EQ(cursor, buffer);
}


TEST(XrStrconcat, ConcatenatesCStrings)
{
    char buffer[32];

    char* result = xr_strconcat(buffer, "hello", " ", "world");

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "hello world");
}

TEST(XrStrconcat, ConcatenatesTwoStrings)
{
    char buffer[32];

    char* result = xr_strconcat(buffer, "foo", "bar");

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "foobar");
}

TEST(XrStrconcat, ConcatenatesSixStrings)
{
    char buffer[32];

    char* result = xr_strconcat(
        buffer,
        "one",
        "two",
        "three",
        "four",
        "five",
        "six"
    );

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "onetwothreefourfivesix");
}

TEST(XrStrconcat, ExactFitBuffer)
{
    char buffer[6];

    char* result = xr_strconcat(buffer, "he", "llo");

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "hello");
    EXPECT_EQ(buffer[5], '\0');
}

TEST(XrStrconcat, EmptyStrings)
{
    char buffer[16];

    char* result = xr_strconcat(
        buffer,
        "",
        "hello",
        "",
        " ",
        "world",
        ""
    );

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "hello world");
}

TEST(XrStrconcat, WorksWithXrString)
{
    xr_string first = "hello";
    xr_string second = " ";
    xr_string third = "world";

    char buffer[32];

    char* result = xr_strconcat(buffer, first.c_str(), second.c_str(), third.c_str());

    EXPECT_EQ(result, buffer);
    EXPECT_STREQ(buffer, "hello world");
}


TEST(StringTupples, SizeIncludesNullTerminator)
{
    using xray::core::detail::string_tupples;

    string_tupples strings("hello", "world");

    EXPECT_EQ(strings.size(), 11u);
}

TEST(StringTupples, SizeForEmptyStrings)
{
    using xray::core::detail::string_tupples;

    string_tupples strings("", "");

    EXPECT_EQ(strings.size(), 1u);
}

TEST(StringTupples, SizeForMultipleStrings)
{
    using xray::core::detail::string_tupples;

    string_tupples strings(
        "one",
        "two",
        "three",
        "four",
        "five",
        "six"
    );

    // 3 + 3 + 5 + 4 + 4 + 3 + NUL
    EXPECT_EQ(strings.size(), 23u);
}

TEST(StringTupples, ConcatenatesStrings)
{
    using xray::core::detail::string_tupples;

    string_tupples strings("hello", " ", "world");

    char buffer[12] = {};

    strings.concat(buffer);

    EXPECT_STREQ(buffer, "hello world");
}

TEST(StringTupples, ConcatenatesEmptyStrings)
{
    using xray::core::detail::string_tupples;

    string_tupples strings("", "hello", "", "world", "");

    char buffer[11] = {};

    strings.concat(buffer);

    EXPECT_STREQ(buffer, "helloworld");
}

TEST(StringTupples, ConcatenatesXrStrings)
{
    using xray::core::detail::string_tupples;

    xr_string first = "hello";
    xr_string second = " ";
    xr_string third = "world";

    string_tupples strings(first, second, third);

    char buffer[12] = {};

    strings.concat(buffer);

    EXPECT_STREQ(buffer, "hello world");
}
} // namespace
