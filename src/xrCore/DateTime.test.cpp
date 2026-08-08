#include "stdafx.h"

#include "DateTime.hpp"

#include <gtest/gtest.h>

#include <ctime>
#include <string>

namespace
{
    std::tm LocalTime(time_t time)
    {
        return *std::localtime(&time);
    }

    void ExpectTwoDigitString(const xr_string& value, int expected)
    {
        ASSERT_GE(expected, 0);
        ASSERT_LE(expected, 99);

        ASSERT_EQ(value.size(), 2u);
        EXPECT_EQ(value[0], static_cast<char>('0' + expected / 10));
        EXPECT_EQ(value[1], static_cast<char>('0' + expected % 10));
    }
}

TEST(Time, NumericValuesAreValid)
{
    const Time time;

    EXPECT_GE(time.GetSeconds(), 0);
    EXPECT_LE(time.GetSeconds(), 59);

    EXPECT_GE(time.GetMinutes(), 0);
    EXPECT_LE(time.GetMinutes(), 59);

    EXPECT_GE(time.GetHours(), 0);
    EXPECT_LE(time.GetHours(), 23);

    EXPECT_GE(time.GetDay(), 1);
    EXPECT_LE(time.GetDay(), 31);

    EXPECT_GE(time.GetMonth(), 1);
    EXPECT_LE(time.GetMonth(), 12);

    EXPECT_GE(time.GetYear(), 1900);
}

TEST(Time, NumericValuesMatchCurrentLocalTime)
{
    const time_t before = std::time(nullptr);
    const Time time;
    const time_t after = std::time(nullptr);

    ASSERT_LE(before, after);

    // Time can only have been constructed during this interval.
    const std::tm beforeTm = LocalTime(before);
    const std::tm afterTm = LocalTime(after);

    EXPECT_GE(time.GetSeconds(), beforeTm.tm_sec);
    EXPECT_LE(time.GetSeconds(), afterTm.tm_sec);

    // For fields which cannot safely be compared across a minute/hour/day
    // boundary, verify that the complete date/time is one of the possible
    // values represented by the interval.
    std::tm expected = LocalTime(before);

    bool matches = false;

    for (time_t t = before; t <= after; ++t)
    {
        expected = LocalTime(t);

        if (time.GetSeconds() == expected.tm_sec &&
            time.GetMinutes() == expected.tm_min &&
            time.GetHours() == expected.tm_hour &&
            time.GetDay() == expected.tm_mday &&
            time.GetMonth() == expected.tm_mon + 1 &&
            time.GetYear() == expected.tm_year + 1900)
        {
            matches = true;
            break;
        }
    }

    EXPECT_TRUE(matches);
}

TEST(Time, SecondsStringIsZeroPadded)
{
    const Time time;

    const int seconds = time.GetSeconds();
    const xr_string value = time.GetSecondsString();

    ExpectTwoDigitString(value, seconds);
}

TEST(Time, MinutesStringIsZeroPadded)
{
    const Time time;

    const int minutes = time.GetMinutes();
    const xr_string value = time.GetMinutesString();

    ExpectTwoDigitString(value, minutes);
}

TEST(Time, HoursStringIsZeroPadded)
{
    const Time time;

    const int hours = time.GetHours();
    const xr_string value = time.GetHoursString();

    ExpectTwoDigitString(value, hours);
}

TEST(Time, DayStringIsZeroPadded)
{
    const Time time;

    const int day = time.GetDay();
    const xr_string value = time.GetDayString();

    ExpectTwoDigitString(value, day);
}

TEST(Time, MonthStringIsZeroPadded)
{
    const Time time;

    const int month = time.GetMonth();
    const xr_string value = time.GetMonthString();

    ExpectTwoDigitString(value, month);
}

TEST(Time, YearStringIsNotZeroPadded)
{
    const Time time;

    const int year = time.GetYear();
    const xr_string value = time.GetYearString();

    EXPECT_EQ(value, xr_string::ToString(year));
}

TEST(Time, StringGettersCorrespondToNumericGetters)
{
    const Time time;

    EXPECT_EQ(
        time.GetSecondsString(),
        (time.GetSeconds() < 10 ? "0" : "") +
            xr_string::ToString(time.GetSeconds()));

    EXPECT_EQ(
        time.GetMinutesString(),
        (time.GetMinutes() < 10 ? "0" : "") +
            xr_string::ToString(time.GetMinutes()));

    EXPECT_EQ(
        time.GetHoursString(),
        (time.GetHours() < 10 ? "0" : "") +
            xr_string::ToString(time.GetHours()));

    EXPECT_EQ(
        time.GetDayString(),
        (time.GetDay() < 10 ? "0" : "") +
            xr_string::ToString(time.GetDay()));

    EXPECT_EQ(
        time.GetMonthString(),
        (time.GetMonth() < 10 ? "0" : "") +
            xr_string::ToString(time.GetMonth()));

    EXPECT_EQ(
        time.GetYearString(),
        xr_string::ToString(time.GetYear()));
}
