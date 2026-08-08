#include "stdafx.h"

#include "TimeUtils.h"

#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <regex>
#include <string>

namespace
{
    int parse_digits(const xr_string& str, std::size_t pos, std::size_t count)
    {
        int value = 0;

        for (std::size_t i = 0; i < count; ++i)
        {
            const char c = str[pos + i];
            EXPECT_GE(c, '0');
            EXPECT_LE(c, '9');

            value = value * 10 + (c - '0');
        }

        return value;
    }

    using namespace std::chrono;

    TEST(TimeUtils, ChronoToTimeT_ConvertsSystemClockTimePoint)
    {
        const auto now = system_clock::now();

        const auto tp1 = now;
        const auto tp2 = now - hours(1);
        const auto tp3 = now + hours(1);

        const xr_time_t t1 = xr_chrono_to_time_t(tp1);
        const xr_time_t t2 = xr_chrono_to_time_t(tp2);
        const xr_time_t t3 = xr_chrono_to_time_t(tp3);

        EXPECT_NEAR(
            static_cast<double>(t1),
            static_cast<double>(system_clock::to_time_t(tp1)),
            1.0);

        EXPECT_NEAR(
            static_cast<double>(t2),
            static_cast<double>(system_clock::to_time_t(tp2)),
            1.0);

        EXPECT_NEAR(
            static_cast<double>(t3),
            static_cast<double>(system_clock::to_time_t(tp3)),
            1.0);

        EXPECT_LT(t2, t1);
        EXPECT_LT(t1, t3);
    }

    TEST(TimeUtils, CurrentTimeStamp_HasDefaultFormat)
    {
        const xr_string timestamp = getCurrentTimeStamp();

        // HH:MM:SS.mmm
        static const std::regex pattern(R"(^\d{2}:\d{2}:\d{2}\.\d{3}$)");

        EXPECT_TRUE(std::regex_match(timestamp, pattern))
            << "timestamp: " << timestamp;
    }

    TEST(TimeUtils, CurrentTimeStamp_HasValidTimeComponents)
    {
        const xr_string timestamp = getCurrentTimeStamp();

        ASSERT_EQ(timestamp.size(), 12u);
        ASSERT_EQ(timestamp[2], ':');
        ASSERT_EQ(timestamp[5], ':');
        ASSERT_EQ(timestamp[8], '.');

        const int hours =
            parse_digits(timestamp, 0, 2);

        const int minutes =
            parse_digits(timestamp, 3, 2);

        const int seconds =
            parse_digits(timestamp,6, 2);

        const int milliseconds =
            parse_digits(timestamp,9, 3);

        EXPECT_GE(hours, 0);
        EXPECT_LE(hours, 23);

        EXPECT_GE(minutes, 0);
        EXPECT_LE(minutes, 59);

        EXPECT_GE(seconds, 0);
        EXPECT_LE(seconds, 59);

        EXPECT_GE(milliseconds, 0);
        EXPECT_LE(milliseconds, 999);
    }

    TEST(TimeUtils, CurrentTimeStamp_UsesCustomFormat)
    {
        const xr_string timestamp =
            getCurrentTimeStamp("%Y-%m-%d");

        // YYYY-MM-DD.mmm
        static const std::regex pattern(
            R"(^\d{4}-\d{2}-\d{2}\.\d{3}$)");

        EXPECT_TRUE(std::regex_match(timestamp, pattern))
            << "timestamp: " << timestamp;
    }

    TEST(TimeUtils, CurrentTimeStamp_MillisecondsAreThreeDigits)
    {
        const xr_string timestamp = getCurrentTimeStamp();

        ASSERT_EQ(timestamp.size(), 12u);

        for (std::size_t i = 9; i < 12; ++i)
        {
            EXPECT_GE(timestamp[i], '0');
            EXPECT_LE(timestamp[i], '9');
        }
    }

    TEST(TimeUtils, TimeInHMSMMM_MatchesCurrentTimeStampDefault)
    {
        const xr_string timestamp = timeInHMSMMM();

        static const std::regex pattern(R"(^\d{2}:\d{2}:\d{2}\.\d{3}$)");

        EXPECT_TRUE(std::regex_match(timestamp, pattern))
            << "timestamp: " << timestamp;
    }

    TEST(TimeUtils, TimeInDMYHMSMMM_HasExpectedFormat)
    {
        const xr_string timestamp = timeInDMYHMSMMM();

        // DD.MM.YYYY HH:MM:SS.mmm
        static const std::regex pattern(
            R"(^\d{2}\.\d{2}\.\d{4} \d{2}:\d{2}:\d{2}\.\d{3}$)");

        EXPECT_TRUE(std::regex_match(timestamp, pattern))
            << "timestamp: " << timestamp;
    }

    TEST(TimeUtils, TimeInDMYHMSMMM_ContainsValidDateAndTime)
    {
        const xr_string timestamp = timeInDMYHMSMMM();

        ASSERT_EQ(timestamp.size(), 23u);

        const int day =
            parse_digits(timestamp,0, 2);

        const int month =
            parse_digits(timestamp,3, 2);

        const int year =
            parse_digits(timestamp,6, 4);

        const int hours =
            parse_digits(timestamp,11, 2);

        const int minutes =
            parse_digits(timestamp,14, 2);

        const int seconds =
            parse_digits(timestamp,17, 2);

        const int milliseconds =
            parse_digits(timestamp,20, 3);

        EXPECT_GE(day, 1);
        EXPECT_LE(day, 31);

        EXPECT_GE(month, 1);
        EXPECT_LE(month, 12);

        EXPECT_GE(year, 1970);

        EXPECT_GE(hours, 0);
        EXPECT_LE(hours, 23);

        EXPECT_GE(minutes, 0);
        EXPECT_LE(minutes, 59);

        EXPECT_GE(seconds, 0);
        EXPECT_LE(seconds, 59);

        EXPECT_GE(milliseconds, 0);
        EXPECT_LE(milliseconds, 999);
    }

    TEST(TimeUtils, CurrentTimeStamp_IsCloseToSystemClock)
    {
        const auto before = system_clock::now();

        const xr_string timestamp = getCurrentTimeStamp();

        const auto after = system_clock::now();

        ASSERT_EQ(timestamp.size(), 12u);

        const int hours =
            parse_digits(timestamp,0, 2);

        const int minutes =
            parse_digits(timestamp,3, 2);

        const int seconds =
            parse_digits(timestamp,6, 2);

        const int milliseconds =
            parse_digits(timestamp,9, 3);

        // Convert the returned local broken-down time back to a
        // time_t using today's date. This verifies that the timestamp
        // is actually representing "now", rather than merely matching
        // the expected syntax.
        const xr_time_t now_time =
            system_clock::to_time_t(after);

        const std::tm* local = std::localtime(&now_time);
        ASSERT_NE(local, nullptr);

        EXPECT_EQ(hours, local->tm_hour);
        EXPECT_EQ(minutes, local->tm_min);
        EXPECT_EQ(seconds, local->tm_sec);

        EXPECT_GE(milliseconds, 0);
        EXPECT_LE(milliseconds, 999);

        // The test intentionally does not compare milliseconds exactly:
        // getCurrentTimeStamp() executes between before and after.
        (void)before;
    }
}
