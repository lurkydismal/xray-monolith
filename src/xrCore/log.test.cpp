#include "stdafx.h"

#include "log.h"

#include <gtest/gtest.h>

namespace
{

class LogTest : public ::testing::Test
{
protected:
    static inline xr_vector<xr_string> messages;

    static void callback(const char* message)
    {
        messages.emplace_back(message);
    }

    static void clear_messages()
    {
        messages.clear();
    }

    void SetUp() override
    {
        clear_messages();

        xrLogger::InitLog();
        xrLogger::SetImmediateMode(true);
        xrLogger::AddLogCallback(&callback);
    }

    void TearDown() override
    {
        xrLogger::RemoveLogCallback(&callback);
        clear_messages();
    }
};

} // namespace

// =============================================================================
// FormatString
// =============================================================================

TEST(LogFormatString, FormatsString)
{
    EXPECT_EQ(
        FormatString("hello %s", "world"),
        "hello world"
    );
}

TEST(LogFormatString, FormatsInteger)
{
    EXPECT_EQ(
        FormatString("%d %d", 42, -17),
        "42 -17"
    );
}

TEST(LogFormatString, FormatsUnsignedInteger)
{
    EXPECT_EQ(
        FormatString("%u", 42u),
        "42"
    );
}

TEST(LogFormatString, FormatsFloat)
{
    EXPECT_EQ(
        FormatString("%f", 1.5f),
        "1.500000"
    );
}

TEST(LogFormatString, FormatsMultipleArguments)
{
    EXPECT_EQ(
        FormatString(
            "%s %d %.2f",
            "value",
            42,
            3.14159
        ),
        "value 42 3.14"
    );
}

TEST(LogFormatString, EmptyFormat)
{
    EXPECT_EQ(
        FormatString(""),
        ""
    );
}

TEST(LogFormatString, LiteralPercent)
{
    EXPECT_EQ(
        FormatString("100%% complete"),
        "100% complete"
    );
}

// =============================================================================
// Msg
// =============================================================================

TEST_F(LogTest, MsgFormatsMessage)
{
    Msg("hello %s", "world");

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "hello world");
}

TEST_F(LogTest, MsgFormatsMultipleArguments)
{
    Msg(
        "name=%s value=%d float=%f",
        "test",
        42,
        1.25f
    );

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(
        messages[0],
        "name=test value=42 float=1.250000"
    );
}

TEST_F(LogTest, MsgNullFormatDoesNothing)
{
    Msg(nullptr);

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Log(const char*)
// =============================================================================

TEST_F(LogTest, LogString)
{
    Log("hello");

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "hello");
}

TEST_F(LogTest, LogNullStringDoesNothing)
{
    Log(nullptr);

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Log(const char*, const char*)
// =============================================================================

TEST_F(LogTest, LogStringString)
{
    Log("hello", "world");

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "hello world");
}

TEST_F(LogTest, LogStringStringWithNullValue)
{
    Log("hello", static_cast<const char*>(nullptr));

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "hello");
}

TEST_F(LogTest, LogStringStringWithNullMessage)
{
    Log(nullptr, "world");

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Log(const char*, u32)
// =============================================================================

TEST_F(LogTest, LogStringU32)
{
    Log("value", static_cast<u32>(42));

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value 42");
}

TEST_F(LogTest, LogStringU32Zero)
{
    Log("value", static_cast<u32>(0));

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value 0");
}

TEST_F(LogTest, LogStringU32Maximum)
{
    Log("value", static_cast<u32>(~u32(0)));

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value 4294967295");
}

TEST_F(LogTest, LogStringU32NullMessage)
{
    Log(nullptr, static_cast<u32>(42));

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Log(const char*, int)
// =============================================================================

TEST_F(LogTest, LogStringInt)
{
    Log("value", 42);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value 42");
}

TEST_F(LogTest, LogStringNegativeInt)
{
    Log("value", -42);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value -42");
}

TEST_F(LogTest, LogStringIntZero)
{
    Log("value", 0);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value 0");
}

TEST_F(LogTest, LogStringIntNullMessage)
{
    Log(nullptr, 42);

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Log(const char*, float)
// =============================================================================

TEST_F(LogTest, LogStringFloat)
{
    Log("value", 1.5f);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value 1.500000");
}

TEST_F(LogTest, LogStringNegativeFloat)
{
    Log("value", -1.5f);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value -1.500000");
}

TEST_F(LogTest, LogStringZeroFloat)
{
    Log("value", 0.0f);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "value 0.000000");
}

TEST_F(LogTest, LogStringFloatNullMessage)
{
    Log(nullptr, 1.5f);

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Log(const char*, Fvector)
// =============================================================================

TEST_F(LogTest, LogVector)
{
    Fvector value;
    value.set(1.0f, 2.0f, 3.0f);

    Log("position", value);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(
        messages[0],
        "position (1.000000,2.000000,3.000000)"
    );
}

TEST_F(LogTest, LogVectorNegativeValues)
{
    Fvector value;
    value.set(-1.5f, -2.5f, -3.5f);

    Log("position", value);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(
        messages[0],
        "position (-1.500000,-2.500000,-3.500000)"
    );
}

TEST_F(LogTest, LogVectorNullMessage)
{
    Fvector value;
    value.set(1.0f, 2.0f, 3.0f);

    Log(nullptr, value);

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Log(const char*, Fmatrix)
// =============================================================================

TEST_F(LogTest, LogMatrix)
{
    Fmatrix value;

    value.i.set(1.0f, 2.0f, 3.0f);
    value._14_ = 4.0f;

    value.j.set(5.0f, 6.0f, 7.0f);
    value._24_ = 8.0f;

    value.k.set(9.0f, 10.0f, 11.0f);
    value._34_ = 12.0f;

    value.c.set(13.0f, 14.0f, 15.0f);
    value._44_ = 16.0f;

    Log("matrix", value);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(
        messages[0],
        "matrix:\n"
        "1.000000,2.000000,3.000000,4.000000\n"
        "5.000000,6.000000,7.000000,8.000000\n"
        "9.000000,10.000000,11.000000,12.000000\n"
        "13.000000,14.000000,15.000000,16.000000\n"
    );
}

TEST_F(LogTest, LogMatrixNegativeValues)
{
    Fmatrix value;

    value.i.set(-1.0f, -2.0f, -3.0f);
    value._14_ = -4.0f;

    value.j.set(-5.0f, -6.0f, -7.0f);
    value._24_ = -8.0f;

    value.k.set(-9.0f, -10.0f, -11.0f);
    value._34_ = -12.0f;

    value.c.set(-13.0f, -14.0f, -15.0f);
    value._44_ = -16.0f;

    Log("matrix", value);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(
        messages[0],
        "matrix:\n"
        "-1.000000,-2.000000,-3.000000,-4.000000\n"
        "-5.000000,-6.000000,-7.000000,-8.000000\n"
        "-9.000000,-10.000000,-11.000000,-12.000000\n"
        "-13.000000,-14.000000,-15.000000,-16.000000\n"
    );
}

TEST_F(LogTest, LogMatrixNullMessage)
{
    Fmatrix value;

    value.i.set(1.0f, 2.0f, 3.0f);
    value._14_ = 4.0f;
    value.j.set(5.0f, 6.0f, 7.0f);
    value._24_ = 8.0f;
    value.k.set(9.0f, 10.0f, 11.0f);
    value._34_ = 12.0f;
    value.c.set(13.0f, 14.0f, 15.0f);
    value._44_ = 16.0f;

    Log(nullptr, value);

    EXPECT_TRUE(messages.empty());
}

// =============================================================================
// Callback management
// =============================================================================

TEST_F(LogTest, CallbackReceivesSimpleMessage)
{
    Log("hello");

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages.front(), "hello");
}

TEST_F(LogTest, RemovedCallbackDoesNotReceiveMessages)
{
    xrLogger::RemoveLogCallback(&callback);

    Log("hello");

    EXPECT_TRUE(messages.empty());
}

TEST_F(LogTest, CallbackCanBeAddedAgain)
{
    xrLogger::RemoveLogCallback(&callback);
    xrLogger::AddLogCallback(&callback);

    Log("hello");

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages.front(), "hello");
}

TEST_F(LogTest, NullCallbackIsIgnored)
{
    xrLogger::AddLogCallback(nullptr);

    Log("hello");

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages.front(), "hello");
}

// =============================================================================
// SimpleMessage explicit size
// =============================================================================

TEST_F(LogTest, SimpleMessageUsesExplicitSize)
{
    xrLogger logger;

    logger.SetImmediateMode(true);
    xrLogger::AddLogCallback(&callback);

    logger.SimpleMessage("abcdef", 3);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "abc");

    xrLogger::RemoveLogCallback(&callback);
}

TEST_F(LogTest, SimpleMessageZeroSizeUsesStringLength)
{
    xrLogger logger;

    logger.SetImmediateMode(true);
    xrLogger::AddLogCallback(&callback);

    logger.SimpleMessage("abcdef", 0);

    ASSERT_EQ(messages.size(), 1u);
    EXPECT_EQ(messages[0], "abcdef");

    xrLogger::RemoveLogCallback(&callback);
}

TEST_F(LogTest, SimpleMessageMinusOneDoesNothing)
{
    xrLogger logger;

    logger.SetImmediateMode(true);
    xrLogger::AddLogCallback(&callback);

    logger.SimpleMessage("abcdef", u32(-1));

    EXPECT_TRUE(messages.empty());

    xrLogger::RemoveLogCallback(&callback);
}

TEST_F(LogTest, SimpleMessageNullDoesNothing)
{
    xrLogger logger;

    logger.SetImmediateMode(true);
    xrLogger::AddLogCallback(&callback);

    logger.SimpleMessage(nullptr);

    EXPECT_TRUE(messages.empty());

    xrLogger::RemoveLogCallback(&callback);
}

// =============================================================================
// SimpleMessage newline handling
// =============================================================================

TEST_F(LogTest, SimpleMessageCallbackReceivesEachLineSeparately)
{
    xrLogger logger;

    logger.SetImmediateMode(true);
    xrLogger::AddLogCallback(&callback);

    logger.SimpleMessage("first\nsecond\nthird");

    ASSERT_EQ(messages.size(), 3u);
    EXPECT_EQ(messages[0], "first");
    EXPECT_EQ(messages[1], "second");
    EXPECT_EQ(messages[2], "third");

    xrLogger::RemoveLogCallback(&callback);
}
