#include "stdafx.h"

#include "xrDebug.h"

#include <gtest/gtest.h>

#include <windows.h>

namespace
{

TEST(XrDebug, CrashHandlerInitiallyNull)
{
    xrDebug debug{};

    EXPECT_EQ(debug.get_crashhandler(), nullptr);
}

TEST(XrDebug, SetAndGetCrashHandler)
{
    xrDebug debug{};

    auto handler = +[]() {};

    debug.set_crashhandler(handler);

    EXPECT_EQ(debug.get_crashhandler(), handler);
}

TEST(XrDebug, CrashHandlerCanBeReset)
{
    xrDebug debug{};

    auto handler = +[]() {};

    debug.set_crashhandler(handler);
    ASSERT_EQ(debug.get_crashhandler(), handler);

    debug.set_crashhandler(nullptr);

    EXPECT_EQ(debug.get_crashhandler(), nullptr);
}

TEST(XrDebug, OnDialogInitiallyNull)
{
    xrDebug debug{};

    EXPECT_EQ(debug.get_on_dialog(), nullptr);
}

TEST(XrDebug, SetAndGetOnDialog)
{
    xrDebug debug{};

    auto callback = +[](bool) {};

    debug.set_on_dialog(callback);

    EXPECT_EQ(debug.get_on_dialog(), callback);
}

TEST(XrDebug, OnDialogCanBeReset)
{
    xrDebug debug{};

    auto callback = +[](bool) {};

    debug.set_on_dialog(callback);
    ASSERT_EQ(debug.get_on_dialog(), callback);

    debug.set_on_dialog(nullptr);

    EXPECT_EQ(debug.get_on_dialog(), nullptr);
}


TEST(XrDebug, GatherInfoContainsExpression)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "x != nullptr",
        "assertion failed",
        nullptr,
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "Expression    : x != nullptr"), nullptr);
}

TEST(XrDebug, GatherInfoContainsFunction)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "x != nullptr",
        "assertion failed",
        nullptr,
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "Function      : TestFunction"), nullptr);
}

TEST(XrDebug, GatherInfoContainsFile)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "x != nullptr",
        "assertion failed",
        nullptr,
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "File          : test.cpp"), nullptr);
}

TEST(XrDebug, GatherInfoContainsLine)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "x != nullptr",
        "assertion failed",
        nullptr,
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "Line          : 42"), nullptr);
}

TEST(XrDebug, GatherInfoContainsDescription)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "x != nullptr",
        "assertion failed",
        nullptr,
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "Description   : assertion failed"), nullptr);
}

TEST(XrDebug, GatherInfoContainsSingleArgument)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "x != nullptr",
        "assertion failed",
        "actual value: 123",
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(
        std::strstr(buffer, "Arguments     : actual value: 123"),
        nullptr
    );
}

TEST(XrDebug, GatherInfoContainsTwoArguments)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "x != nullptr",
        "assertion failed",
        "actual value: 123",
        "expected value: 456",
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(
        std::strstr(buffer, "Argument 0    : actual value: 123"),
        nullptr
    );

    EXPECT_NE(
        std::strstr(buffer, "Argument 1    : expected value: 456"),
        nullptr
    );
}

TEST(XrDebug, GatherInfoNullExpressionUsesPlaceholder)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        nullptr,
        "assertion failed",
        nullptr,
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(
        std::strstr(buffer, "Expression    : <no expression>"),
        nullptr
    );
}

TEST(XrDebug, GatherInfoExtendedDescription)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "some expression",
        "first line\nsecond line",
        nullptr,
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "first line\nsecond line"), nullptr);

    // In extended-description mode there should not be the normal
    // "Description   :" prefix.
    EXPECT_EQ(
        std::strstr(buffer, "Description   : first line"),
        nullptr
    );
}

TEST(XrDebug, GatherInfoExtendedDescriptionWithOneArgument)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "some expression",
        "first line\nsecond line",
        "argument",
        nullptr,
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "first line\nsecond line"), nullptr);
    EXPECT_NE(std::strstr(buffer, "argument"), nullptr);
}

TEST(XrDebug, GatherInfoExtendedDescriptionWithTwoArguments)
{
    xrDebug debug{};

    char buffer[4096] = {};

    debug.gather_info(
        "some expression",
        "first line\nsecond line",
        "argument 0",
        "argument 1",
        "test.cpp",
        42,
        "TestFunction",
        buffer
    );

    EXPECT_NE(std::strstr(buffer, "first line\nsecond line"), nullptr);
    EXPECT_NE(std::strstr(buffer, "argument 0"), nullptr);
    EXPECT_NE(std::strstr(buffer, "argument 1"), nullptr);
}


TEST(XrDebug, GatherInfoArrayOverloadProducesSameResult)
{
    xrDebug debug{};

    char buffer1[4096] = {};
    char buffer2[4096] = {};

    debug.gather_info(
        "expression",
        "description",
        "argument",
        nullptr,
        "test.cpp",
        123,
        "TestFunction",
        buffer1
    );

    debug.gather_info(
        "expression",
        "description",
        "argument",
        nullptr,
        "test.cpp",
        123,
        "TestFunction",
        buffer2,
        sizeof(buffer2)
    );

    EXPECT_STREQ(buffer1, buffer2);
}


TEST(XrDebug, Error2StringForKnownWindowsError)
{
    xrDebug debug{};

    const char* result = debug.error2string(ERROR_FILE_NOT_FOUND);

    ASSERT_NE(result, nullptr);
    EXPECT_NE(result[0], '\0');
}

TEST(XrDebug, Error2StringForSuccessCode)
{
    xrDebug debug{};

    const char* result = debug.error2string(ERROR_SUCCESS);

    ASSERT_NE(result, nullptr);
    EXPECT_NE(result[0], '\0');
}


TEST(MakeString, FormatsString)
{
    std::string result = make_string(
        "hello %s %d",
        "world",
        42
    );

    EXPECT_EQ(result, "hello world 42");
}

TEST(MakeString, FormatsMultipleArguments)
{
    std::string result = make_string(
        "%s=%d, %s=%d",
        "foo",
        123,
        "bar",
        456
    );

    EXPECT_EQ(result, "foo=123, bar=456");
}

TEST(MakeString, FormatsEmptyString)
{
    std::string result = make_string("%s", "");

    EXPECT_TRUE(result.empty());
}

TEST(MakeString, FormatsPercentLiteral)
{
    std::string result = make_string("100%% complete");

    EXPECT_EQ(result, "100% complete");
}

} // namespace
