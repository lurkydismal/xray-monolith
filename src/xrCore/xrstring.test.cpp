#include "stdafx.h"

#include "xrstring.h"

#include <gtest/gtest.h>

#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

namespace
{
    static void ExpectStrings(
        const xr_vector<xr_string>& actual,
        std::initializer_list<const char*> expected)
    {
        ASSERT_EQ(actual.size(), expected.size());

        size_t i = 0;
        for (const char* value : expected)
        {
            EXPECT_EQ(actual[i], value);
            ++i;
        }
    }

#if 0
    static void ExpectStrings(
        const SStringVec& actual,
        std::initializer_list<const char*> expected)
    {
        ASSERT_EQ(actual.size(), expected.size());

        size_t i = 0;
        for (const char* value : expected)
        {
            EXPECT_EQ(actual[i], value);
            ++i;
        }
    }
#endif
}


// -------------------------------------------------------------------------
// Construction / assignment
// -------------------------------------------------------------------------

TEST(XrString, DefaultConstruction)
{
    xr_string value;

    EXPECT_TRUE(value.empty());
    EXPECT_EQ(value.size(), 0u);
    EXPECT_STREQ(value.c_str(), "");
}

TEST(XrString, ConstructFromCString)
{
    xr_string value("hello");

    EXPECT_EQ(value, "hello");
    EXPECT_EQ(value.size(), 5u);
}

TEST(XrString, ConstructFromCStringWithSize)
{
    const char source[] = "hello world";

    xr_string value(source, 5);

    EXPECT_EQ(value, "hello");
    EXPECT_EQ(value.size(), 5u);
}

TEST(XrString, ConstructFromSuperString)
{
    xr_string::Super source("hello");

    xr_string value(std::move(source));

    EXPECT_EQ(value, "hello");
}

TEST(XrString, AssignCString)
{
    xr_string value("before");

    value = "after";

    EXPECT_EQ(value, "after");
}

TEST(XrString, AssignSuperString)
{
    xr_string value("before");
    xr_string::Super source("after");

    value = source;

    EXPECT_EQ(value, "after");
}

TEST(XrString, CopyConstruction)
{
    xr_string original("hello");

    xr_string copy(original);

    EXPECT_EQ(copy, original);
    EXPECT_EQ(copy, "hello");
}

TEST(XrString, MoveConstruction)
{
    xr_string original("hello");

    xr_string moved(std::move(original));

    EXPECT_EQ(moved, "hello");
}

TEST(XrString, CopyAssignment)
{
    xr_string original("hello");
    xr_string copy;

    copy = original;

    EXPECT_EQ(copy, "hello");
}

TEST(XrString, MoveAssignment)
{
    xr_string original("hello");
    xr_string moved;

    moved = std::move(original);

    EXPECT_EQ(moved, "hello");
}


// -------------------------------------------------------------------------
// Split(char)
// -------------------------------------------------------------------------

TEST(XrString, SplitEmpty)
{
    xr_string value;

    auto result = value.Split(',');

    EXPECT_TRUE(result.empty());
}

TEST(XrString, SplitWithoutDelimiter)
{
    xr_string value("hello");

    auto result = value.Split(',');

    ExpectStrings(result, {"hello"});
}

TEST(XrString, SplitNormal)
{
    xr_string value("one,two,three");

    auto result = value.Split(',');

    ExpectStrings(result, {"one", "two", "three"});
}

TEST(XrString, SplitLeadingDelimiter)
{
    xr_string value(",one,two");

    auto result = value.Split(',');

    ExpectStrings(result, {"", "one", "two"});
}

TEST(XrString, SplitConsecutiveDelimiters)
{
    xr_string value("one,,three");

    auto result = value.Split(',');

    ExpectStrings(result, {"one", "", "three"});
}

TEST(XrString, SplitTrailingDelimiter)
{
    xr_string value("one,two,");

    auto result = value.Split(',');

    // Current implementation does NOT emit a trailing empty token.
    ExpectStrings(result, {"one", "two"});
}

TEST(XrString, SplitOnlyDelimiter)
{
    xr_string value(",");

    auto result = value.Split(',');

    // Current implementation emits one empty element.
    ExpectStrings(result, {""});
}

TEST(XrString, SplitMultipleConsecutiveDelimiters)
{
    xr_string value(",,,x");

    auto result = value.Split(',');

    ExpectStrings(result, {"", "", "", "x"});
}


// -------------------------------------------------------------------------
// Split(u32, ...)
// -------------------------------------------------------------------------

TEST(XrString, SplitMultipleDelimiters)
{
    xr_string value("one,two;three");

    // IMPORTANT:
    // The implementation uses va_arg(args, char), despite default
    // argument promotion making char arguments int.
    //
    // This call matches the existing implementation on the current
    // supported ABI/compiler setup.
    auto result = value.Split(2, ',', ';');

    ExpectStrings(result, {"one", "two", "three"});
}

TEST(XrString, SplitMultipleDelimitersWithEmptyTokens)
{
    xr_string value("one,,two;three");

    auto result = value.Split(2, ',', ';');

    ExpectStrings(result, {"one", "", "two", "three"});
}


// -------------------------------------------------------------------------
// StartWith
// -------------------------------------------------------------------------

TEST(XrString, StartWithString)
{
    xr_string value("hello world");

    EXPECT_TRUE(value.StartWith(xr_string("hello")));
    EXPECT_TRUE(value.StartWith(xr_string("hello world")));

    EXPECT_FALSE(value.StartWith(xr_string("world")));
    EXPECT_FALSE(value.StartWith(xr_string("hello world!")));
}

TEST(XrString, StartWithCString)
{
    xr_string value("hello world");

    EXPECT_TRUE(value.StartWith("hello"));
    EXPECT_TRUE(value.StartWith("hello world"));

    EXPECT_FALSE(value.StartWith("world"));
    EXPECT_FALSE(value.StartWith("hello world!"));
}

TEST(XrString, StartWithExplicitSize)
{
    xr_string value("hello world");

    EXPECT_TRUE(value.StartWith("hello", 5));
    EXPECT_TRUE(value.StartWith("hello world", 11));

    EXPECT_FALSE(value.StartWith("hello world!", 12));
    EXPECT_FALSE(value.StartWith("world", 5));
}

TEST(XrString, StartWithEmptyPrefix)
{
    xr_string value("hello");

    EXPECT_TRUE(value.StartWith(""));
    EXPECT_TRUE(value.StartWith("", 0));
}

TEST(XrString, StartWithPrefixLongerThanString)
{
    xr_string value("hello");

    EXPECT_FALSE(value.StartWith("hello!", 6));
}


// -------------------------------------------------------------------------
// Contains
// -------------------------------------------------------------------------

TEST(XrString, Contains)
{
    xr_string value("hello world");

    EXPECT_TRUE(value.Contains("hello"));
    EXPECT_TRUE(value.Contains("world"));
    EXPECT_TRUE(value.Contains("lo wo"));

    EXPECT_FALSE(value.Contains("xyz"));
}

TEST(XrString, ContainsEmptyString)
{
    xr_string value("hello");

    // std::string::find("") == 0.
    EXPECT_TRUE(value.Contains(""));
}

TEST(XrString, ContainsEmptyValue)
{
    xr_string value;

    EXPECT_TRUE(value.Contains(""));
}


// -------------------------------------------------------------------------
// RemoveWhitespaces
// -------------------------------------------------------------------------

TEST(XrString, RemoveWhitespaces)
{
    xr_string value("hello world");

    EXPECT_EQ(value.RemoveWhitespaces(), "helloworld");
}

TEST(XrString, RemoveWhitespacesOnlyRemovesSpaces)
{
    xr_string value("hello\tworld\n");

    // Function is called RemoveWhitespaces, but the implementation only
    // removes literal ' ' characters.
    EXPECT_EQ(value.RemoveWhitespaces(), "hello\tworld\n");
}

TEST(XrString, RemoveWhitespacesEmpty)
{
    xr_string value;

    EXPECT_TRUE(value.RemoveWhitespaces().empty());
}

TEST(XrString, RemoveWhitespacesAllSpaces)
{
    xr_string value("   ");

    EXPECT_TRUE(value.RemoveWhitespaces().empty());
}


// -------------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------------

TEST(XrString, ToStringInt)
{
    EXPECT_EQ(xr_string::ToString(0), "0");
    EXPECT_EQ(xr_string::ToString(42), "42");
    EXPECT_EQ(xr_string::ToString(-42), "-42");
}

TEST(XrString, ToStringUnsignedInt)
{
    EXPECT_EQ(xr_string::ToString(0u), "0");
    EXPECT_EQ(xr_string::ToString(42u), "42");
    EXPECT_EQ(
        xr_string::ToString(std::numeric_limits<unsigned int>::max()),
        std::to_string(std::numeric_limits<unsigned int>::max()).c_str());
}

TEST(XrString, ToStringFloat)
{
    EXPECT_EQ(xr_string::ToString(0.0f), "0.000000");
    EXPECT_EQ(xr_string::ToString(1.5f), "1.500000");
    EXPECT_EQ(xr_string::ToString(-1.5f), "-1.500000");
}

TEST(XrString, ToStringDouble)
{
    EXPECT_EQ(xr_string::ToString(0.0), "0.000000");
    EXPECT_EQ(xr_string::ToString(1.5), "1.500000");
    EXPECT_EQ(xr_string::ToString(-1.5), "-1.500000");
}


// -------------------------------------------------------------------------
// Join
// -------------------------------------------------------------------------

TEST(XrString, JoinEmpty)
{
    SStringVec values;

    EXPECT_EQ(
        xr_string::Join(values.begin(), values.end()),
        "");
}

TEST(XrString, JoinWithoutDelimiter)
{
    SStringVec values;
    values.push_back( "one" );
    values.push_back( "two" );
    values.push_back( "three" );

    EXPECT_EQ(
        xr_string::Join(values.begin(), values.end()),
        "onetwothree");
}

TEST(XrString, JoinWithDelimiter)
{
    SStringVec values;
    values.push_back( "one" );
    values.push_back( "two" );
    values.push_back( "three" );

    EXPECT_EQ(
        xr_string::Join(values.begin(), values.end(), ','),
        "one,two,three");
}

TEST(XrString, JoinSingleElement)
{
    SStringVec values;
    values.push_back( "hello" );

    EXPECT_EQ(
        xr_string::Join(values.begin(), values.end(), ','),
        "hello");
}

TEST(XrString, JoinEmptyElements)
{
    SStringVec values;
    values.push_back( "" );
    values.push_back( "two" );
    values.push_back( "" );

    EXPECT_EQ(
        xr_string::Join(values.begin(), values.end(), ','),
        ",two,");
}


// -------------------------------------------------------------------------
// SplitStringMulti
// -------------------------------------------------------------------------

TEST(XrString, SplitStringMultiSingleSeparator)
{
    xr_string value("one,two,three");

    auto result = value.SplitStringMulti(",");

    ExpectStrings(result, {"one", "two", "three"});
}

TEST(XrString, SplitStringMultiMultipleSeparators)
{
    xr_string value("one,two;three:four");

    auto result = value.SplitStringMulti(",;:");

    ExpectStrings(result, {"one", "two", "three", "four"});
}

TEST(XrString, SplitStringMultiDoesNotEmitEmptyTokens)
{
    xr_string value("one,,two;;;three");

    auto result = value.SplitStringMulti(",;");

    ExpectStrings(result, {"one", "two", "three"});
}

TEST(XrString, SplitStringMultiIncludeSeparators)
{
    xr_string value("one,two;three");

    auto result = value.SplitStringMulti(",;", true);

    ExpectStrings(result, {
        "one", ",",
        "two", ";",
        "three"
    });
}

TEST(XrString, SplitStringMultiTrim)
{
    xr_string value("  one , two  ,  three  ");

    auto result = value.SplitStringMulti(",", false, true);

    ExpectStrings(result, {
        "one",
        "two",
        "three"
    });
}

TEST(XrString, SplitStringMultiEmpty)
{
    xr_string value;

    auto result = value.SplitStringMulti(",");

    EXPECT_TRUE(result.empty());
}

TEST(XrString, SplitStringMultiNewlineHandling)
{
    xr_string value("one,two\nthree,four");

    auto result = value.SplitStringMulti(",");

    ExpectStrings(result, {
        "one",
        "two",
        "three",
        "four"
    });
}


// -------------------------------------------------------------------------
// SplitStringLimit
// -------------------------------------------------------------------------

TEST(XrString, SplitStringLimitWithoutLimit)
{
    xr_string value("one,two,three");

    auto result = value.SplitStringLimit(",");

    ExpectStrings(result, {
        "one",
        "two",
        "three"
    });
}

TEST(XrString, SplitStringLimit)
{
    xr_string value("one,two,three,four");

    auto result = value.SplitStringLimit(",", 2);

    ExpectStrings(result, {
        "one",
        "two",
        "three,four"
    });
}

TEST(XrString, SplitStringLimitOne)
{
    xr_string value("one,two,three");

    auto result = value.SplitStringLimit(",", 1);

    ExpectStrings(result, {
        "one",
        "two,three"
    });
}

TEST(XrString, SplitStringLimitZero)
{
    xr_string value("one,two,three");

    auto result = value.SplitStringLimit(",", 0);

    ExpectStrings(result, {
        "one",
        "two",
        "three"
    });
}

TEST(XrString, SplitStringLimitNegative)
{
    xr_string value("one,two,three");

    auto result = value.SplitStringLimit(",", -1);

    // Current implementation treats negative limit as unlimited.
    ExpectStrings(result, {
        "one",
        "two",
        "three"
    });
}

TEST(XrString, SplitStringLimitTrim)
{
    xr_string value("  one , two , three  ");

    auto result = value.SplitStringLimit(",", 0, true);

    ExpectStrings(result, {
        "one",
        "two",
        "three"
    });
}

TEST(XrString, SplitStringLimitMultipleSeparators)
{
    xr_string value("one,two;three:four");

    auto result = value.SplitStringLimit(",;:", 2);

    ExpectStrings(result, {
        "one",
        "two",
        "three:four"
    });
}


// -------------------------------------------------------------------------
// Trim
// -------------------------------------------------------------------------

TEST(XrString, Trim)
{
    EXPECT_EQ(xr_string("  hello  ").Trim(), "hello");
    EXPECT_EQ(xr_string("\thello\t").Trim(), "hello");
    EXPECT_EQ(xr_string("\nhello\n").Trim(), "hello");
}

TEST(XrString, TrimDoesNotModifyOriginal)
{
    xr_string value("  hello  ");

    auto result = value.Trim();

    EXPECT_EQ(result, "hello");
    EXPECT_EQ(value, "  hello  ");
}

TEST(XrString, TrimCustomCharacters)
{
    xr_string value("xxxhelloxxx");

    EXPECT_EQ(value.Trim("x"), "hello");
}

TEST(XrString, TrimEmpty)
{
    xr_string value;

    EXPECT_TRUE(value.Trim().empty());
}

TEST(XrString, TrimAllTrimCharacters)
{
    xr_string value("   ");

    EXPECT_TRUE(value.Trim().empty());
}

TEST(XrString, TrimInPlace)
{
    xr_string value("  hello  ");

    value.TrimInPlace();

    EXPECT_EQ(value, "hello");
}

TEST(XrString, TrimInPlaceCustomCharacters)
{
    xr_string value("xxxhelloxxx");

    value.TrimInPlace("x");

    EXPECT_EQ(value, "hello");
}

TEST(XrString, TrimInPlaceEmpty)
{
    xr_string value;

    value.TrimInPlace();

    EXPECT_TRUE(value.empty());
}

TEST(XrString, TrimInPlaceAllTrimCharacters)
{
    xr_string value("   ");

    value.TrimInPlace();

    EXPECT_TRUE(value.empty());
}


// -------------------------------------------------------------------------
// ToLowerCase
// -------------------------------------------------------------------------

TEST(XrString, ToLowerCase)
{
    EXPECT_EQ(
        xr_string("Hello WORLD").ToLowerCase(),
        "hello world");
}

TEST(XrString, ToLowerCaseDoesNotModifyOriginal)
{
    xr_string value("Hello WORLD");

    auto result = value.ToLowerCase();

    EXPECT_EQ(result, "hello world");
    EXPECT_EQ(value, "Hello WORLD");
}

TEST(XrString, ToLowerCaseAlreadyLower)
{
    EXPECT_EQ(
        xr_string("hello world").ToLowerCase(),
        "hello world");
}

TEST(XrString, ToLowerCaseEmpty)
{
    EXPECT_TRUE(xr_string().ToLowerCase().empty());
}

TEST(XrString, ToLowerCaseNumbersAndPunctuation)
{
    EXPECT_EQ(
        xr_string("ABC123!@#").ToLowerCase(),
        "abc123!@#");
}


// -------------------------------------------------------------------------
// ReplaceAll
// -------------------------------------------------------------------------

TEST(XrString, ReplaceAll)
{
    EXPECT_EQ(
        xr_string("one two one").ReplaceAll("one", "three"),
        "three two three");
}

TEST(XrString, ReplaceAllNoMatch)
{
    EXPECT_EQ(
        xr_string("hello").ReplaceAll("xyz", "abc"),
        "hello");
}

TEST(XrString, ReplaceAllEmptyFrom)
{
    EXPECT_EQ(
        xr_string("hello").ReplaceAll("", "x"),
        "hello");
}

TEST(XrString, ReplaceAllEmptyTo)
{
    EXPECT_EQ(
        xr_string("hello world").ReplaceAll(" ", ""),
        "helloworld");
}

TEST(XrString, ReplaceAllMultipleOccurrences)
{
    EXPECT_EQ(
        xr_string("aaaa").ReplaceAll("aa", "b"),
        "bb");
}

TEST(XrString, ReplaceAllToContainsFrom)
{
    EXPECT_EQ(
        xr_string("x").ReplaceAll("x", "yx"),
        "yx");
}

TEST(XrString, ReplaceAllDoesNotModifyOriginal)
{
    xr_string value("hello world");

    auto result = value.ReplaceAll("world", "there");

    EXPECT_EQ(result, "hello there");
    EXPECT_EQ(value, "hello world");
}


// -------------------------------------------------------------------------
// IsUTF8
// -------------------------------------------------------------------------

TEST(XrString, IsUTF8Null)
{
    EXPECT_TRUE(IsUTF8(nullptr));
}

TEST(XrString, IsUTF8Empty)
{
    EXPECT_TRUE(IsUTF8(""));
}

TEST(XrString, IsUTF8Ascii)
{
    EXPECT_TRUE(IsUTF8("hello world"));
}

TEST(XrString, IsUTF8TwoByte)
{
    // U+00E9: é
    const char value[] = "\xC3\xA9";

    EXPECT_TRUE(IsUTF8(value));
}

TEST(XrString, IsUTF8ThreeByte)
{
    // U+20AC: €
    const char value[] = "\xE2\x82\xAC";

    EXPECT_TRUE(IsUTF8(value));
}

TEST(XrString, IsUTF8FourByte)
{
    // U+1F600: 😀
    const char value[] = "\xF0\x9F\x98\x80";

    EXPECT_TRUE(IsUTF8(value));
}

TEST(XrString, IsUTF8InvalidLeadingByte)
{
    const char value[] = "\xFF";

    EXPECT_FALSE(IsUTF8(value));
}

TEST(XrString, IsUTF8InvalidContinuationByte)
{
    const char value[] = "\xC3\x28";

    EXPECT_FALSE(IsUTF8(value));
}

TEST(XrString, IsUTF8InvalidThreeByteSequence)
{
    const char value[] = "\xE2\x28\xA1";

    EXPECT_FALSE(IsUTF8(value));
}

TEST(XrString, IsUTF8InvalidFourByteSequence)
{
    const char value[] = "\xF0\x28\x8C\xBC";

    EXPECT_FALSE(IsUTF8(value));
}

TEST(XrString, IsUTF8MixedAsciiAndUnicode)
{
    const char value[] = "hello \xE2\x82\xAC world";

    EXPECT_TRUE(IsUTF8(value));
}


// -------------------------------------------------------------------------
// shared_str
//
// These tests intentionally control g_pStringContainer because shared_str
// silently becomes empty when the global container is null.
// -------------------------------------------------------------------------

class SharedStrTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        oldContainer = g_pStringContainer;
        g_pStringContainer = str_container::create();
    }

    void TearDown() override
    {
        g_pStringContainer = oldContainer;
    }

    intrusive_ptr<str_container> oldContainer;
};

TEST_F(SharedStrTest, DefaultConstruction)
{
    shared_str value;

    EXPECT_TRUE(value.empty());
    EXPECT_EQ(value.size(), 0u);
    EXPECT_EQ(value.c_str(), nullptr);
    EXPECT_TRUE(!value);
}

TEST_F(SharedStrTest, ConstructionFromCString)
{
    shared_str value("hello");

    EXPECT_FALSE(value.empty());
    EXPECT_FALSE(!value);
    EXPECT_EQ(value.size(), 5u);
    ASSERT_NE(value.c_str(), nullptr);
    EXPECT_STREQ(value.c_str(), "hello");
    EXPECT_STREQ(*value, "hello");
}

TEST_F(SharedStrTest, AssignmentFromCString)
{
    shared_str value;

    value = "hello";

    EXPECT_EQ(value.size(), 5u);
    EXPECT_STREQ(value.c_str(), "hello");
}

TEST_F(SharedStrTest, CopyConstruction)
{
    shared_str original("hello");

    shared_str copy(original);

    EXPECT_EQ(copy.size(), 5u);
    EXPECT_STREQ(copy.c_str(), "hello");
    EXPECT_TRUE(copy.equal(original));
    EXPECT_EQ(copy._get(), original._get());
}

TEST_F(SharedStrTest, CopyAssignment)
{
    shared_str original("hello");
    shared_str copy;

    copy = original;

    EXPECT_TRUE(copy.equal(original));
    EXPECT_EQ(copy._get(), original._get());
}

TEST_F(SharedStrTest, EqualStringsAreInterned)
{
    shared_str a("hello");
    shared_str b("hello");

    EXPECT_TRUE(a.equal(b));
    EXPECT_EQ(a._get(), b._get());
    EXPECT_EQ(a, b);
}

TEST_F(SharedStrTest, DifferentStringsAreNotEqual)
{
    shared_str a("hello");
    shared_str b("world");

    EXPECT_FALSE(a.equal(b));
    EXPECT_NE(a._get(), b._get());
    EXPECT_NE(a, b);
}

TEST_F(SharedStrTest, DifferentPointersCanRepresentSameText)
{
    char first[] = "hello";
    char second[] = "hello";

    shared_str a(first);
    shared_str b(second);

    EXPECT_TRUE(a.equal(b));
    EXPECT_EQ(a._get(), b._get());
}

TEST_F(SharedStrTest, IndexOperator)
{
    shared_str value("hello");

    EXPECT_EQ(value[0], 'h');
    EXPECT_EQ(value[1], 'e');
    EXPECT_EQ(value[4], 'o');
}

TEST_F(SharedStrTest, Swap)
{
    shared_str a("hello");
    shared_str b("world");

    auto* aPtr = a._get();
    auto* bPtr = b._get();

    a.swap(b);

    EXPECT_EQ(a._get(), bPtr);
    EXPECT_EQ(b._get(), aPtr);

    EXPECT_STREQ(a.c_str(), "world");
    EXPECT_STREQ(b.c_str(), "hello");
}

TEST_F(SharedStrTest, FreeFunctionSwap)
{
    shared_str a("hello");
    shared_str b("world");

    swap(a, b);

    EXPECT_STREQ(a.c_str(), "world");
    EXPECT_STREQ(b.c_str(), "hello");
}

TEST_F(SharedStrTest, Size)
{
    shared_str value("hello");

    EXPECT_EQ(value.size(), 5u);
    EXPECT_EQ(xr_strlen(value), 5u);
}

TEST_F(SharedStrTest, EmptyStringIsNotEmpty)
{
    shared_str value("");

    EXPECT_FALSE(value.empty());
    EXPECT_EQ(value.size(), 0u);
    EXPECT_FALSE(!value);
    ASSERT_NE(value.c_str(), nullptr);
    EXPECT_STREQ(value.c_str(), "");
}

TEST_F(SharedStrTest, NullAssignment)
{
    shared_str value("hello");

    value = static_cast<const char*>(nullptr);

    EXPECT_TRUE(value.empty());
    EXPECT_EQ(value.size(), 0u);
    EXPECT_EQ(value.c_str(), nullptr);
    EXPECT_TRUE(!value);
}

TEST_F(SharedStrTest, AssignmentReplacesValue)
{
    shared_str value("hello");

    value = "world";

    EXPECT_STREQ(value.c_str(), "world");
    EXPECT_EQ(value.size(), 5u);
}

TEST_F(SharedStrTest, AssignmentSameStringUsesSameInternedValue)
{
    shared_str value("hello");

    const str_value* original = value._get();

    value = "hello";

    EXPECT_EQ(value._get(), original);
}

TEST_F(SharedStrTest, GlobalContainerNullMakesStringEmpty)
{
    g_pStringContainer = nullptr;

    shared_str value("hello");

    EXPECT_TRUE(value.empty());
    EXPECT_EQ(value.c_str(), nullptr);
    EXPECT_TRUE(!value);
}

TEST_F(SharedStrTest, HashEqualForInternedStrings)
{
    shared_str a("hello");
    shared_str b("hello");

    EXPECT_EQ(
        std::hash<shared_str>{}(a),
        std::hash<shared_str>{}(b));
}

TEST_F(SharedStrTest, HashDiffersForDifferentInternedPointers)
{
    shared_str a("hello");
    shared_str b("world");

    EXPECT_NE(
        std::hash<shared_str>{}(a),
        std::hash<shared_str>{}(b));
}

TEST_F(SharedStrTest, XrStrcmp)
{
    shared_str hello("hello");
    shared_str hello2("hello");
    shared_str world("world");

    EXPECT_EQ(xr_strcmp(hello, hello2), 0);
    EXPECT_EQ(xr_strcmp(hello, "hello"), 0);
    EXPECT_EQ(xr_strcmp("hello", hello), 0);

    EXPECT_LT(xr_strcmp(hello, world), 0);
    EXPECT_GT(xr_strcmp(world, hello), 0);
}


// -------------------------------------------------------------------------
// str_container
// -------------------------------------------------------------------------

TEST(StrContainer, Create)
{
    auto container = str_container::create();

    ASSERT_NE(container, nullptr);
}

TEST(StrContainer, DockNullReturnsNull)
{
    auto container = str_container::create();

    auto value = container->dock(nullptr);

    EXPECT_EQ(value.get(), nullptr);
}

TEST(StrContainer, DockCreatesString)
{
    auto container = str_container::create();

    auto value = container->dock("hello");

    ASSERT_NE(value.get(), nullptr);
    ASSERT_NE(value->value, nullptr);

    EXPECT_STREQ(value->value, "hello");
    EXPECT_EQ(value->length, 5u);
}

TEST(StrContainer, DockSameStringReturnsSameValue)
{
    auto container = str_container::create();

    auto first = container->dock("hello");
    auto second = container->dock("hello");

    ASSERT_NE(first.get(), nullptr);
    ASSERT_NE(second.get(), nullptr);

    EXPECT_EQ(first.get(), second.get());
}

TEST(StrContainer, DockSameStringFromDifferentBuffers)
{
    auto container = str_container::create();

    char first[] = "hello";
    char second[] = "hello";

    auto a = container->dock(first);
    auto b = container->dock(second);

    EXPECT_EQ(a.get(), b.get());
}

TEST(StrContainer, DockDifferentStrings)
{
    auto container = str_container::create();

    auto first = container->dock("hello");
    auto second = container->dock("world");

    ASSERT_NE(first.get(), nullptr);
    ASSERT_NE(second.get(), nullptr);

    EXPECT_NE(first.get(), second.get());
    EXPECT_STREQ(first->value, "hello");
    EXPECT_STREQ(second->value, "world");
}

TEST(StrContainer, DockEmptyString)
{
    auto container = str_container::create();

    auto value = container->dock("");

    ASSERT_NE(value.get(), nullptr);

    EXPECT_EQ(value->length, 0u);
    EXPECT_STREQ(value->value, "");
}

TEST(StrContainer, DockPreservesLength)
{
    auto container = str_container::create();

    const char value[] = "hello";

    auto result = container->dock(value);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->length, 5u);
}

TEST(StrContainer, DockLongString)
{
    auto container = str_container::create();

    std::string source(1024 * 1024, 'x');

    auto value = container->dock(source.c_str());

    ASSERT_NE(value.get(), nullptr);
    EXPECT_EQ(value->length, source.size());
    EXPECT_EQ(
        std::string(value->value, value->length),
        source);
}

TEST(StrContainer, StatEconomyCountsStrings)
{
    auto container = str_container::create();

    container->dock("one");
    container->dock("two");
    container->dock("three");

    // Duplicate must not increase unique/count.
    container->dock("one");

    u32 count = 0;
    u32 unique = 0;

    container->stat_economy(count, unique);

    EXPECT_EQ(count, 3u);
    EXPECT_EQ(unique, 3u);
}

TEST(StrContainer, StatEconomyCountsDuplicateOnlyOnce)
{
    auto container = str_container::create();

    for (int i = 0; i < 100; ++i)
        container->dock("same");

    u32 count = 0;
    u32 unique = 0;

    container->stat_economy(count, unique);

    EXPECT_EQ(count, 1u);
    EXPECT_EQ(unique, 1u);
}

TEST(StrContainer, CleanRemovesStrings)
{
    auto container = str_container::create();

    auto first = container->dock("hello");

    ASSERT_NE(first.get(), nullptr);

    container->clean();

    auto second = container->dock("hello");

    ASSERT_NE(second.get(), nullptr);

    // The old str_value is no longer in the container.
    EXPECT_NE(first.get(), second.get());
}


// -------------------------------------------------------------------------
// str_value
// -------------------------------------------------------------------------

TEST(StrValue, DefaultConstruction)
{
    str_value value;

    EXPECT_EQ(value.value, nullptr);
    EXPECT_EQ(value.hash, 0u);
    EXPECT_EQ(value.length, 0u);
}

TEST(StrValue, Construction)
{
    char text[] = "hello";

    str_value value(text);

    EXPECT_EQ(value.value, text);
    EXPECT_EQ(value.length, 5u);
    EXPECT_NE(value.hash, 0u);
}

TEST(StrValue, ComparisonUsesPointerForEquality)
{
    char first[] = "hello";
    char second[] = "hello";

    str_value a(first);
    str_value b(second);

    // This is important characterization of the current implementation:
    // operator== requires both hash AND pointer identity.
    EXPECT_FALSE(a == b);
}

TEST(StrValue, ComparisonSamePointer)
{
    char text[] = "hello";

    str_value a(text);
    str_value b(text);

    EXPECT_TRUE(a == b);
}

TEST(StrValue, OrderingUsesPointer)
{
    char first[] = "a";
    char second[] = "b";

    str_value a(first);
    str_value b(second);

    // Don't assert lexical ordering: implementation compares addresses.
    EXPECT_TRUE((a < b) || (b < a) || (a.value == b.value));
}


// -------------------------------------------------------------------------
// xr_strlwr
// -------------------------------------------------------------------------

TEST(XrStrlwr, LowercasesString)
{
    xr_string value("Hello WORLD");

    xr_strlwr(value);

    EXPECT_EQ(value, "hello world");
}

TEST(XrStrlwr, AlreadyLowercase)
{
    xr_string value("hello world");

    xr_strlwr(value);

    EXPECT_EQ(value, "hello world");
}

TEST(XrStrlwr, Empty)
{
    xr_string value;

    xr_strlwr(value);

    EXPECT_TRUE(value.empty());
}

TEST_F(SharedStrTest, LowercasesSharedString)
{
    shared_str value("Hello WORLD");

    xr_strlwr(value);

    EXPECT_STREQ(value.c_str(), "hello world");
}

TEST_F(SharedStrTest, LowercaseSharedStringPreservesInterningSemantics)
{
    shared_str value("HELLO");

    xr_strlwr(value);

    shared_str expected("hello");

    EXPECT_TRUE(value.equal(expected));
}


// -------------------------------------------------------------------------
// std::hash
// -------------------------------------------------------------------------

TEST(XrString, StdHashCanBeUsedInUnorderedSet)
{
    std::unordered_set<xr_string> values;

    values.emplace("one");
    values.emplace("two");
    values.emplace("one");

    EXPECT_EQ(values.size(), 2u);
    EXPECT_NE(values.find("one"), values.end());
    EXPECT_NE(values.find("two"), values.end());
}

TEST_F(SharedStrTest, SharedStrCanBeUsedInUnorderedSet)
{
    std::unordered_set<shared_str> values;

    values.emplace("one");
    values.emplace("two");
    values.emplace("one");

    EXPECT_EQ(values.size(), 2u);
}


// -------------------------------------------------------------------------
// UTF-8 -> CP1251
// -------------------------------------------------------------------------

#ifdef _WIN32

TEST(XrStringEncoding, UTF8ToCP1251Ascii)
{
    xr_string value("hello");

    EXPECT_EQ(UTF8_to_CP1251(value), "hello");
}

TEST(XrStringEncoding, UTF8ToCP1251Cyrillic)
{
    // "Привет" in UTF-8.
    xr_string value(
        "\xD0\x9F"
        "\xD1\x80"
        "\xD0\xB8"
        "\xD0\xB2"
        "\xD0\xB5"
        "\xD1\x82");

    xr_string result = UTF8_to_CP1251(value);

    // CP1251: Привет
    const char expected[] =
        "\xCF\xF0\xE8\xE2\xE5\xF2";

    EXPECT_EQ(result, expected);
}

TEST(XrStringEncoding, InvalidUTF8IsReturnedUnchanged)
{
    const char invalid[] = "\xFF\xFE";

    xr_string value(invalid);

    EXPECT_EQ(UTF8_to_CP1251(value), value);
}

TEST(XrStringEncoding, EmptyStringIsReturnedUnchanged)
{
    xr_string value;

    EXPECT_EQ(UTF8_to_CP1251(value), value);
}

#endif
