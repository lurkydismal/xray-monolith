#include "stdafx.h"

#include "xr_ini.h"

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// These are defined in xr_ini.cpp but aren't declared by xr_ini.h.
XRCORE_API BOOL _parse(LPSTR dest, LPCSTR src);
XRCORE_API void _decorate(LPSTR dest, LPCSTR src);

namespace
{
    // -------------------------------------------------------------------------
    // CInifile::IsBOOL
    // -------------------------------------------------------------------------

    TEST(XrIni, IsBOOLAcceptsOn)
    {
        EXPECT_TRUE(CInifile::IsBOOL("on"));
    }

    TEST(XrIni, IsBOOLAcceptsYes)
    {
        EXPECT_TRUE(CInifile::IsBOOL("yes"));
    }

    TEST(XrIni, IsBOOLAcceptsTrue)
    {
        EXPECT_TRUE(CInifile::IsBOOL("true"));
    }

    TEST(XrIni, IsBOOLAcceptsOne)
    {
        EXPECT_TRUE(CInifile::IsBOOL("1"));
    }

    TEST(XrIni, IsBOOLRejectsOff)
    {
        EXPECT_FALSE(CInifile::IsBOOL("off"));
    }

    TEST(XrIni, IsBOOLRejectsNo)
    {
        EXPECT_FALSE(CInifile::IsBOOL("no"));
    }

    TEST(XrIni, IsBOOLRejectsFalse)
    {
        EXPECT_FALSE(CInifile::IsBOOL("false"));
    }

    TEST(XrIni, IsBOOLRejectsZero)
    {
        EXPECT_FALSE(CInifile::IsBOOL("0"));
    }

    TEST(XrIni, IsBOOLIsCaseSensitive)
    {
        EXPECT_FALSE(CInifile::IsBOOL("ON"));
        EXPECT_FALSE(CInifile::IsBOOL("Yes"));
        EXPECT_FALSE(CInifile::IsBOOL("TRUE"));
    }

    // -------------------------------------------------------------------------
    // _parse
    // -------------------------------------------------------------------------

    TEST(XrIni, ParseRemovesWhitespaceOutsideQuotes)
    {
        char output[256];

        EXPECT_FALSE(_parse(output, "  hello   world  "));

        EXPECT_STREQ(output, "helloworld");
    }

    TEST(XrIni, ParsePreservesWhitespaceInsideQuotes)
    {
        char output[256];

        EXPECT_FALSE(_parse(output, R"(hello "hello   world" test)"));

        EXPECT_STREQ(output, R"(hello"hello   world"test)");
    }

    TEST(XrIni, ParsePreservesSingleSpacesInsideQuotes)
    {
        char output[256];

        EXPECT_FALSE(_parse(output, R"("hello world")"));

        EXPECT_STREQ(output, R"("hello world")");
    }

    TEST(XrIni, ParseReturnsTrueForUnterminatedString)
    {
        char output[256];

        EXPECT_TRUE(_parse(output, R"(hello "world)"));

        EXPECT_STREQ(output, R"(hello"world)");
    }

    TEST(XrIni, ParseReturnsFalseForBalancedQuotes)
    {
        char output[256];

        EXPECT_FALSE(_parse(output, R"(hello "world")"));

        EXPECT_STREQ(output, R"(hello"world)");
    }

    TEST(XrIni, ParseHandlesNullSource)
    {
        char output[256];

        std::strcpy(output, "garbage");

        EXPECT_FALSE(_parse(output, nullptr));

        EXPECT_STREQ(output, "");
    }

    TEST(XrIni, ParseHandlesEmptySource)
    {
        char output[256];

        EXPECT_FALSE(_parse(output, ""));

        EXPECT_STREQ(output, "");
    }

    TEST(XrIni, ParsePreservesNonWhitespaceCharacters)
    {
        char output[256];

        EXPECT_FALSE(_parse(output, "a=b,c:d"));

        EXPECT_STREQ(output, "a=b,c:d");
    }

    // -------------------------------------------------------------------------
    // _decorate
    // -------------------------------------------------------------------------

    TEST(XrIni, DecorateAddsSpaceAfterComma)
    {
        char output[256];

        _decorate(output, "one,two,three");

        EXPECT_STREQ(output, "one, two, three");
    }

    TEST(XrIni, DecoratePreservesCommaInsideQuotes)
    {
        char output[256];

        _decorate(output, R"(one,"two,three",four)");

        EXPECT_STREQ(output, R"(one, "two,three", four)");
    }

    TEST(XrIni, DecorateDoesNotAddSpaceAfterQuotedComma)
    {
        char output[256];

        _decorate(output, R"("one,two")");

        EXPECT_STREQ(output, R"("one,two")");
    }

    TEST(XrIni, DecoratePreservesOtherCharacters)
    {
        char output[256];

        _decorate(output, "a=b,c:d");

        EXPECT_STREQ(output, "a=b, c:d");
    }

    TEST(XrIni, DecorateHandlesNullSource)
    {
        char output[256];

        std::strcpy(output, "garbage");

        _decorate(output, nullptr);

        EXPECT_STREQ(output, "");
    }

    TEST(XrIni, DecorateHandlesEmptySource)
    {
        char output[256];

        _decorate(output, "");

        EXPECT_STREQ(output, "");
    }

    // -------------------------------------------------------------------------
    // CInifile::Item
    // -------------------------------------------------------------------------

    TEST(XrIniItem, DefaultConstructionInitializesFields)
    {
        CInifile::Item item;

        EXPECT_TRUE(item.first.empty());
        EXPECT_TRUE(item.second.empty());
        EXPECT_TRUE(item.filename.empty());
        EXPECT_EQ(item.depth, 0);
        EXPECT_EQ(item.insertionIndex, 0u);
    }

    TEST(XrIniItem, LessComparesKey)
    {
        CInifile::Item a;
        CInifile::Item b;

        a.first = "alpha";
        b.first = "beta";

        EXPECT_TRUE(a < b);
        EXPECT_FALSE(b < a);
    }

    TEST(XrIniItem, LessDoesNotDependOnValue)
    {
        CInifile::Item a;
        CInifile::Item b;

        a.first = "key";
        b.first = "key";

        a.second = "aaa";
        b.second = "zzz";

        EXPECT_FALSE(a < b);
        EXPECT_FALSE(b < a);
    }

    TEST(XrIniItem, LessUsesLexicographicalKeyOrder)
    {
        CInifile::Item a;
        CInifile::Item b;
        CInifile::Item c;

        a.first = "a";
        b.first = "b";
        c.first = "c";

        EXPECT_TRUE(a < b);
        EXPECT_TRUE(b < c);
        EXPECT_TRUE(a < c);
    }

    TEST(XrIniItem, LessIsIndependentOfDepth)
    {
        CInifile::Item a;
        CInifile::Item b;

        a.first = "key";
        b.first = "key";

        a.depth = 0;
        b.depth = 100;

        EXPECT_FALSE(a < b);
        EXPECT_FALSE(b < a);
    }

    TEST(XrIniItem, LessIsIndependentOfInsertionIndex)
    {
        CInifile::Item a;
        CInifile::Item b;

        a.first = "key";
        b.first = "key";

        a.insertionIndex = 0;
        b.insertionIndex = 100;

        EXPECT_FALSE(a < b);
        EXPECT_FALSE(b < a);
    }

    // -------------------------------------------------------------------------
    // CInifile::item_comparator
    // -------------------------------------------------------------------------

    TEST(XrIniItemComparator, ComparesItems)
    {
        CInifile::Item a;
        CInifile::Item b;

        a.first = "alpha";
        b.first = "beta";

        CInifile::item_comparator compare;

        EXPECT_TRUE(compare(a, b));
        EXPECT_FALSE(compare(b, a));
    }

    TEST(XrIniItemComparator, ComparesItemWithCString)
    {
        CInifile::Item item;
        item.first = "middle";

        CInifile::item_comparator compare;

        EXPECT_TRUE(compare(item, "zzz"));
        EXPECT_FALSE(compare(item, "aaa"));

        EXPECT_TRUE(compare("aaa", item));
        EXPECT_FALSE(compare("zzz", item));
    }

    TEST(XrIniItemComparator, ComparesItemWithSharedString)
    {
        CInifile::Item item;
        item.first = "middle";

        shared_str lower("aaa");
        shared_str equal("middle");
        shared_str upper("zzz");

        CInifile::item_comparator compare;

        EXPECT_TRUE(compare(item, upper));
        EXPECT_FALSE(compare(item, lower));

        EXPECT_TRUE(compare(lower, item));
        EXPECT_FALSE(compare(upper, item));

        EXPECT_FALSE(compare(item, equal));
        EXPECT_FALSE(compare(equal, item));
    }

    TEST(XrIniItemComparator, EqualKeysCompareEquivalent)
    {
        CInifile::Item a;
        CInifile::Item b;

        a.first = "same";
        b.first = "same";

        CInifile::item_comparator compare;

        EXPECT_FALSE(compare(a, b));
        EXPECT_FALSE(compare(b, a));
    }

    // -------------------------------------------------------------------------
    // CInifile::Sect::line_exist
    // -------------------------------------------------------------------------

    TEST(XrIniSect, LineExistFindsExistingLine)
    {
        CInifile::Sect section;

        CInifile::Item first;
        first.first = "alpha";
        first.second = "one";

        CInifile::Item second;
        second.first = "beta";
        second.second = "two";

        section.Data.push_back(first);
        section.Data.push_back(second);

        LPCSTR value = nullptr;

        EXPECT_TRUE(section.line_exist("alpha", &value));
        ASSERT_NE(value, nullptr);
        EXPECT_STREQ(value, "one");
    }

    TEST(XrIniSect, LineExistReturnsFalseForMissingLine)
    {
        CInifile::Sect section;

        CInifile::Item item;
        item.first = "alpha";
        item.second = "one";

        section.Data.push_back(item);

        EXPECT_FALSE(section.line_exist("missing"));
    }

    TEST(XrIniSect, LineExistDoesNotWriteValueForMissingLine)
    {
        CInifile::Sect section;

        CInifile::Item item;
        item.first = "alpha";
        item.second = "one";

        section.Data.push_back(item);

        LPCSTR value = "unchanged";

        EXPECT_FALSE(section.line_exist("missing", &value));
        EXPECT_STREQ(value, "unchanged");
    }

    TEST(XrIniSect, LineExistAllowsNullValuePointer)
    {
        CInifile::Sect section;

        CInifile::Item item;
        item.first = "alpha";
        item.second = "one";

        section.Data.push_back(item);

        EXPECT_TRUE(section.line_exist("alpha", nullptr));
    }

    TEST(XrIniSect, LineExistWorksWithSortedData)
    {
        CInifile::Sect section;

        for (const char* name : {"alpha", "beta", "gamma", "omega"})
        {
            CInifile::Item item;
            item.first = name;
            item.second = name;
            section.Data.push_back(item);
        }

        LPCSTR value = nullptr;

        EXPECT_TRUE(section.line_exist("alpha", &value));
        ASSERT_NE(value, nullptr);
        EXPECT_STREQ(value, "alpha");

        EXPECT_TRUE(section.line_exist("beta", &value));
        ASSERT_NE(value, nullptr);
        EXPECT_STREQ(value, "beta");

        EXPECT_TRUE(section.line_exist("gamma", &value));
        ASSERT_NE(value, nullptr);
        EXPECT_STREQ(value, "gamma");

        EXPECT_TRUE(section.line_exist("omega", &value));
        ASSERT_NE(value, nullptr);
        EXPECT_STREQ(value, "omega");
    }

    TEST(XrIniSect, LineExistUsesExactKeyMatch)
    {
        CInifile::Sect section;

        CInifile::Item item;
        item.first = "foobar";
        item.second = "value";

        section.Data.push_back(item);

        EXPECT_FALSE(section.line_exist("foo"));
        EXPECT_FALSE(section.line_exist("bar"));
        EXPECT_FALSE(section.line_exist("foobar_extra"));
        EXPECT_TRUE(section.line_exist("foobar"));
    }

    // -------------------------------------------------------------------------
    // CInifile construction with missing / null files
    // -------------------------------------------------------------------------

    TEST(XrIni, NullFilenameCreatesEmptyIni)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        EXPECT_EQ(ini.section_count(), 0u);
        EXPECT_TRUE(ini.sections().empty());
    }

    TEST(XrIni, MissingFileCreatesEmptyIni)
    {
        CInifile ini(
            "this_file_should_not_exist_xray_gtest_123456789.ini",
            TRUE,
            TRUE,
            FALSE);

        EXPECT_EQ(ini.section_count(), 0u);
        EXPECT_TRUE(ini.sections().empty());
    }

    // -------------------------------------------------------------------------
    // Manually populated CInifile
    //
    // These test the public query API without depending on the filesystem.
    // -------------------------------------------------------------------------

    TEST(XrIni, SectionsCanBePopulatedThroughPublicContainer)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        CInifile::Sect section;
        section.Name = "test";

        CInifile::Item item;
        item.first = "value";
        item.second = "hello";

        section.Data.push_back(item);

        ini.sections().push_back(section);

        EXPECT_EQ(ini.section_count(), 1u);
        EXPECT_TRUE(ini.section_exist("test"));
    }

    TEST(XrIni, SectionExistReturnsFalseForMissingSection)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        CInifile::Sect section;
        section.Name = "test";
        ini.sections().push_back(section);

        EXPECT_TRUE(ini.section_exist("test"));
        EXPECT_FALSE(ini.section_exist("missing"));
    }

    TEST(XrIni, SectionExistIsCaseSensitive)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        CInifile::Sect section;
        section.Name = "Test";
        ini.sections().push_back(section);

        EXPECT_TRUE(ini.section_exist("Test"));
        EXPECT_FALSE(ini.section_exist("test"));
    }

    TEST(XrIni, SectionCountReturnsNumberOfSections)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        CInifile::Sect first;
        first.Name = "first";

        CInifile::Sect second;
        second.Name = "second";

        ini.sections().push_back(first);
        ini.sections().push_back(second);

        EXPECT_EQ(ini.section_count(), 2u);
    }

    TEST(XrIni, LineCountReturnsNumberOfItems)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        CInifile::Sect section;
        section.Name = "test";

        CInifile::Item first;
        first.first = "first";
        first.second = "one";

        CInifile::Item second;
        second.first = "second";
        second.second = "two";

        section.Data.push_back(first);
        section.Data.push_back(second);

        ini.sections().push_back(section);

        EXPECT_EQ(ini.line_count("test"), 2u);
    }

    TEST(XrIni, LineExistFindsLineInSection)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        CInifile::Sect section;
        section.Name = "test";

        CInifile::Item item;
        item.first = "key";
        item.second = "value";

        section.Data.push_back(item);
        ini.sections().push_back(section);

        EXPECT_TRUE(ini.line_exist("test", "key"));
        EXPECT_FALSE(ini.line_exist("test", "missing"));
    }

    TEST(XrIni, RStringReturnsStoredValue)
    {
        CInifile ini(static_cast<LPCSTR>(nullptr));

        CInifile::Sect section;
        section.Name = "test";

        CInifile::Item item;
        item.first = "key";
        item.second = "value";

        section.Data.push_back(item);
        ini.sections().push_back(section);

        EXPECT_STREQ(ini.r_string("test", "key"), "value");
    }

    // -------------------------------------------------------------------------
    // Cache
    // -------------------------------------------------------------------------

    TEST(XrIniCache, InvalidateCacheWithoutPathClearsCache)
    {
        CInifile::InvalidateCache();

        u64 filesCached = 0;
        u64 totalBytes = 0;
        u64 sectionCount = 0;

        CInifile::GetCacheStats(
            filesCached,
            totalBytes,
            sectionCount);

        EXPECT_EQ(filesCached, 0u);
        EXPECT_EQ(totalBytes, 0u);
        EXPECT_EQ(sectionCount, 0u);
    }

    TEST(XrIniCache, InvalidateCacheWithEmptyPathDoesNothing)
    {
        CInifile::InvalidateCache();

        u64 filesCached = 0;
        u64 totalBytes = 0;
        u64 sectionCount = 0;

        CInifile::GetCacheStats(
            filesCached,
            totalBytes,
            sectionCount);

        CInifile::InvalidateCache("");

        u64 filesCachedAfter = 0;
        u64 totalBytesAfter = 0;
        u64 sectionCountAfter = 0;

        CInifile::GetCacheStats(
            filesCachedAfter,
            totalBytesAfter,
            sectionCountAfter);

        EXPECT_EQ(filesCachedAfter, filesCached);
        EXPECT_EQ(totalBytesAfter, totalBytes);
        EXPECT_EQ(sectionCountAfter, sectionCount);
    }
}

// ============================================================================
// _parse
// ============================================================================

TEST(XrIniParse, NullSourceProducesEmptyString)
{
    char result[32] = "garbage";

    EXPECT_FALSE(_parse(result, nullptr));
    EXPECT_STREQ(result, "");
}

TEST(XrIniParse, EmptySourceProducesEmptyString)
{
    char result[32] = "garbage";

    EXPECT_FALSE(_parse(result, ""));

    EXPECT_STREQ(result, "");
}

TEST(XrIniParse, RemovesWhitespaceOutsideQuotes)
{
    char result[128];

    EXPECT_FALSE(_parse(result, "  foo   bar\t baz  "));

    EXPECT_STREQ(result, "foobarbaz");
}

TEST(XrIniParse, PreservesWhitespaceInsideQuotes)
{
    char result[128];

    EXPECT_FALSE(_parse(result, R"(  foo  "bar   baz"   qux  )"));

    EXPECT_STREQ(result, R"(foo"bar   baz"qux)");
}

TEST(XrIniParse, TogglesStringStateAtEveryQuote)
{
    char result[128];

    EXPECT_FALSE(_parse(result, R"("hello world" outside)"));

    EXPECT_STREQ(result, R"("hello world"outside)");
}

TEST(XrIniParse, ReportsUnterminatedQuotedString)
{
    char result[128];

    EXPECT_TRUE(_parse(result, R"(foo "unterminated string)"));

    EXPECT_STREQ(result, R"(foo"unterminated string)");
}

TEST(XrIniParse, HandlesOnlyWhitespace)
{
    char result[32];

    EXPECT_FALSE(_parse(result, " \t\r\n  "));

    EXPECT_STREQ(result, "");
}

// ============================================================================
// _decorate
// ============================================================================

TEST(XrIniDecorate, NullSourceProducesEmptyString)
{
    char result[32] = "garbage";

    _decorate(result, nullptr);

    EXPECT_STREQ(result, "");
}

TEST(XrIniDecorate, EmptySourceProducesEmptyString)
{
    char result[32] = "garbage";

    _decorate(result, "");

    EXPECT_STREQ(result, "");
}

TEST(XrIniDecorate, AddsWhitespaceAfterCommas)
{
    char result[128];

    _decorate(result, "one,two,three");

    EXPECT_STREQ(result, "one, two, three");
}

TEST(XrIniDecorate, PreservesCommaInsideQuotes)
{
    char result[128];

    _decorate(result, R"(one,"two,three",four)");

    EXPECT_STREQ(result, R"(one, "two,three", four)");
}

TEST(XrIniDecorate, HandlesMultipleCommas)
{
    char result[128];

    _decorate(result, "a,,b");

    EXPECT_STREQ(result, "a, , b");
}

TEST(XrIniDecorate, DoesNotAddWhitespaceToOtherCharacters)
{
    char result[128];

    _decorate(result, "hello world\t123");

    EXPECT_STREQ(result, "hello world\t123");
}

// ============================================================================
// CInifile::IsBOOL
// ============================================================================

TEST(XrIniIsBool, RecognizesTrueValues)
{
    EXPECT_TRUE(CInifile::IsBOOL("on"));
    EXPECT_TRUE(CInifile::IsBOOL("yes"));
    EXPECT_TRUE(CInifile::IsBOOL("true"));
    EXPECT_TRUE(CInifile::IsBOOL("1"));
}

TEST(XrIniIsBool, RecognizesFalseValues)
{
    EXPECT_FALSE(CInifile::IsBOOL("off"));
    EXPECT_FALSE(CInifile::IsBOOL("no"));
    EXPECT_FALSE(CInifile::IsBOOL("false"));
    EXPECT_FALSE(CInifile::IsBOOL("0"));
}

TEST(XrIniIsBool, IsCaseSensitive)
{
    EXPECT_FALSE(CInifile::IsBOOL("ON"));
    EXPECT_FALSE(CInifile::IsBOOL("Yes"));
    EXPECT_FALSE(CInifile::IsBOOL("TRUE"));
}

TEST(XrIniIsBool, DoesNotAcceptWhitespace)
{
    EXPECT_FALSE(CInifile::IsBOOL(" on"));
    EXPECT_FALSE(CInifile::IsBOOL("on "));
    EXPECT_FALSE(CInifile::IsBOOL(" true "));
}

TEST(XrIniIsBool, NullIsFalse)
{
    EXPECT_FALSE(CInifile::IsBOOL(nullptr));
}

// ============================================================================
// CInifile::Item
// ============================================================================

TEST(XrIniItem, DefaultConstruction)
{
    CInifile::Item item;

    EXPECT_STREQ(*item.first, "");
    EXPECT_STREQ(*item.second, "");
    EXPECT_STREQ(*item.filename, "");
    EXPECT_EQ(item.depth, 0);
    EXPECT_EQ(item.insertionIndex, 0u);
}

TEST(XrIniItem, OrdersByKey)
{
    CInifile::Item a;
    CInifile::Item b;

    a.first = "alpha";
    b.first = "beta";

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(XrIniItem, EqualKeysAreNotLess)
{
    CInifile::Item a;
    CInifile::Item b;

    a.first = "same";
    b.first = "same";

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(XrIniItem, OrderingDependsOnlyOnKey)
{
    CInifile::Item a;
    CInifile::Item b;

    a.first = "same";
    a.second = "first";
    a.depth = 0;
    a.insertionIndex = 1;

    b.first = "same";
    b.second = "second";
    b.depth = 100;
    b.insertionIndex = 999;

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

// ============================================================================
// CInifile::item_comparator
// ============================================================================

TEST(XrIniItemComparator, OrdersItemsByKey)
{
    CInifile::Item a;
    CInifile::Item b;

    a.first = "alpha";
    b.first = "beta";

    CInifile::item_comparator cmp;

    EXPECT_TRUE(cmp(a, b));
    EXPECT_FALSE(cmp(b, a));
}

TEST(XrIniItemComparator, ComparesItemWithCString2)
{
    CInifile::Item item;
    item.first = "beta";

    CInifile::item_comparator cmp;

    EXPECT_TRUE(cmp(item, "gamma"));
    EXPECT_FALSE(cmp(item, "alpha"));
    EXPECT_FALSE(cmp(item, "beta"));

    EXPECT_TRUE(cmp("alpha", item));
    EXPECT_FALSE(cmp("gamma", item));
    EXPECT_FALSE(cmp("beta", item));
}

TEST(XrIniItemComparator, ComparesItemWithSharedString2)
{
    CInifile::Item item;
    item.first = "beta";

    shared_str alpha = "alpha";
    shared_str beta = "beta";
    shared_str gamma = "gamma";

    CInifile::item_comparator cmp;

    EXPECT_TRUE(cmp(item, gamma));
    EXPECT_FALSE(cmp(item, alpha));
    EXPECT_FALSE(cmp(item, beta));

    EXPECT_TRUE(cmp(alpha, item));
    EXPECT_FALSE(cmp(gamma, item));
    EXPECT_FALSE(cmp(beta, item));
}

TEST(XrIniItemComparator, EquivalentKeysAreEquivalent)
{
    CInifile::Item item;
    item.first = "section";

    CInifile::item_comparator cmp;

    EXPECT_FALSE(cmp(item, "section"));
    EXPECT_FALSE(cmp("section", item));
}

TEST(XrIniItemComparator, IsTransparent)
{
    static_assert(std::is_same_v<
        CInifile::item_comparator::is_transparent,
        void>);
}

// ============================================================================
// CInifile::Sect::line_exist
// ============================================================================

TEST(XrIniSection, LineExistFindsExistingLine)
{
    CInifile::Sect section;

    CInifile::Item first;
    first.first = "alpha";
    first.second = "value-alpha";

    CInifile::Item second;
    second.first = "beta";
    second.second = "value-beta";

    CInifile::Item third;
    third.first = "gamma";
    third.second = "value-gamma";

    section.Data.push_back(first);
    section.Data.push_back(second);
    section.Data.push_back(third);

    LPCSTR value = nullptr;

    EXPECT_TRUE(section.line_exist("beta", &value));
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "value-beta");
}

TEST(XrIniSection, LineExistReturnsFalseForMissingLine)
{
    CInifile::Sect section;

    CInifile::Item item;
    item.first = "alpha";
    item.second = "value";

    section.Data.push_back(item);

    EXPECT_FALSE(section.line_exist("missing"));
}

TEST(XrIniSection, LineExistDoesNotWriteValueWhenMissing)
{
    CInifile::Sect section;

    CInifile::Item item;
    item.first = "alpha";
    item.second = "value";

    section.Data.push_back(item);

    LPCSTR value = "unchanged";

    EXPECT_FALSE(section.line_exist("missing", &value));
    EXPECT_STREQ(value, "unchanged");
}

TEST(XrIniSection, LineExistAllowsNullOutput)
{
    CInifile::Sect section;

    CInifile::Item item;
    item.first = "alpha";
    item.second = "value";

    section.Data.push_back(item);

    EXPECT_TRUE(section.line_exist("alpha", nullptr));
}

TEST(XrIniSection, LineExistWorksWithSortedData)
{
    CInifile::Sect section;

    CInifile::Item z;
    z.first = "z";
    z.second = "z-value";

    CInifile::Item a;
    a.first = "a";
    a.second = "a-value";

    CInifile::Item m;
    m.first = "m";
    m.second = "m-value";

    // line_exist() uses lower_bound(), so Data must be sorted.
    section.Data.push_back(a);
    section.Data.push_back(m);
    section.Data.push_back(z);

    LPCSTR value = nullptr;

    EXPECT_TRUE(section.line_exist("a", &value));
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "a-value");

    EXPECT_TRUE(section.line_exist("m", &value));
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "m-value");

    EXPECT_TRUE(section.line_exist("z", &value));
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "z-value");
}

TEST(XrIniSection, LineExistRejectsMissingKeyBetweenExistingKeys)
{
    CInifile::Sect section;

    CInifile::Item a;
    a.first = "a";

    CInifile::Item c;
    c.first = "c";

    section.Data.push_back(a);
    section.Data.push_back(c);

    EXPECT_FALSE(section.line_exist("b"));
}

// ============================================================================
// CInifile construction
// ============================================================================

TEST(XrIni, CreateWithNullFilenameCreatesEmptyIni)
{
    CInifile* ini = CInifile::Create(nullptr);

    ASSERT_NE(ini, nullptr);

    EXPECT_STREQ(ini->fname(), "");
    EXPECT_EQ(ini->section_count(), 0u);
    EXPECT_TRUE(ini->sections().empty());

    CInifile::Destroy(ini);
}

TEST(XrIni, CreateWithEmptyFilenameCreatesEmptyIni)
{
    CInifile* ini = CInifile::Create("");

    ASSERT_NE(ini, nullptr);

    EXPECT_STREQ(ini->fname(), "");
    EXPECT_EQ(ini->section_count(), 0u);

    CInifile::Destroy(ini);
}

TEST(XrIni, NullFilenameDoesNotLoadData)
{
    CInifile ini(static_cast<LPCSTR>(nullptr));

    EXPECT_STREQ(ini.fname(), "");
    EXPECT_EQ(ini.section_count(), 0u);
}

TEST(XrIni, EmptyFilenameDoesNotLoadData)
{
    CInifile ini("");

    EXPECT_STREQ(ini.fname(), "");
    EXPECT_EQ(ini.section_count(), 0u);
}

// ============================================================================
// CInifile empty queries
// ============================================================================

TEST(XrIniEmpty, SectionQueriesReturnFalse)
{
    CInifile ini(static_cast<LPCSTR>(nullptr));

    EXPECT_FALSE(ini.section_exist("missing"));
    EXPECT_FALSE(ini.section_exist(shared_str("missing")));
}

TEST(XrIniEmpty, LineQueriesReturnFalse)
{
    CInifile ini(static_cast<LPCSTR>(nullptr));

    EXPECT_FALSE(ini.line_exist("missing", "key"));
    EXPECT_FALSE(ini.line_exist(shared_str("missing"), shared_str("key")));
}

TEST(XrIniEmpty, CountsAreZero)
{
    CInifile ini(static_cast<LPCSTR>(nullptr));

    EXPECT_EQ(ini.section_count(), 0u);
    EXPECT_EQ(ini.line_count("missing"), 0u);
    EXPECT_EQ(ini.line_count(shared_str("missing")), 0u);
}

TEST(XrIniEmpty, SectionsAreEmpty)
{
    CInifile ini(static_cast<LPCSTR>(nullptr));

    EXPECT_TRUE(ini.sections().empty());
}

// ============================================================================
// LTX parsing helpers
// ============================================================================

TEST(XrIniLtx, SectionNamesAreCaseInsensitive)
{
    CInifile ini("test_ltx_case.ltx");

    ASSERT_TRUE(ini.section_exist("test_section"));
    EXPECT_TRUE(ini.section_exist("TEST_SECTION"));
    EXPECT_TRUE(ini.section_exist("TeSt_SeCtIoN"));
}

TEST(XrIniLtx, KeysAreCaseSensitive)
{
    CInifile ini("test_ltx_case.ltx");

    ASSERT_TRUE(ini.section_exist("test_section"));

    EXPECT_TRUE(ini.line_exist("test_section", "key"));
    EXPECT_FALSE(ini.line_exist("test_section", "KEY"));
}

TEST(XrIniLtx, CommentsAreIgnored)
{
    CInifile ini("test_ltx_comments.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_TRUE(ini.line_exist("test", "value"));
    EXPECT_STREQ(ini.r_string("test", "value"), "hello");

    EXPECT_FALSE(ini.line_exist("test", "comment"));
}

TEST(XrIniLtx, DoubleSlashCommentsAreIgnored)
{
    CInifile ini("test_ltx_comments.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_TRUE(ini.line_exist("test", "slash_comment_value"));
    EXPECT_STREQ(
        ini.r_string("test", "slash_comment_value"),
        "value");
}

TEST(XrIniLtx, CommentInsideQuotedValueIsPreserved)
{
    CInifile ini("test_ltx_comments.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_TRUE(ini.line_exist("test", "quoted"));

    EXPECT_STREQ(
        ini.r_string("test", "quoted"),
        R"("value // not a comment; still quoted")");
}

TEST(XrIniLtx, WhitespaceAroundKeyAndValueIsIgnored)
{
    CInifile ini("test_ltx_whitespace.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_TRUE(ini.line_exist("test", "key"));
    EXPECT_STREQ(ini.r_string("test", "key"), "value");
}

TEST(XrIniLtx, EmptyValueIsAllowed)
{
    CInifile ini("test_ltx_empty_value.ltx");

    ASSERT_TRUE(ini.section_exist("test"));
    EXPECT_TRUE(ini.line_exist("test", "empty"));

    EXPECT_STREQ(ini.r_string("test", "empty"), "");
}

TEST(XrIniLtx, SectionCountMatchesLoadedSections)
{
    CInifile ini("test_ltx_sections.ltx");

    EXPECT_EQ(ini.section_count(), 3u);

    EXPECT_TRUE(ini.section_exist("first"));
    EXPECT_TRUE(ini.section_exist("second"));
    EXPECT_TRUE(ini.section_exist("third"));
}

TEST(XrIniLtx, LineCountMatchesLoadedLines)
{
    CInifile ini("test_ltx_lines.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_EQ(ini.line_count("test"), 3u);
}

TEST(XrIniLtx, MissingSectionReturnsFalse)
{
    CInifile ini("test_ltx_sections.ltx");

    EXPECT_FALSE(ini.section_exist("does_not_exist"));
}

TEST(XrIniLtx, MissingLineReturnsFalse)
{
    CInifile ini("test_ltx_lines.ltx");

    EXPECT_FALSE(ini.line_exist("test", "does_not_exist"));
}

// ============================================================================
// DLTX sections
// ============================================================================

TEST(XrIniDltx, OverrideSectionReplacesBaseValue)
{
    CInifile ini("test_ltx_override.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "value"),
        "override");
}

TEST(XrIniDltx, NonOverriddenBaseValuesRemain)
{
    CInifile ini("test_ltx_override.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "unchanged"),
        "base");
}

TEST(XrIniDltx, OverrideSectionCanAddNewValue)
{
    CInifile ini("test_ltx_override.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_TRUE(ini.line_exist("test", "added"));
    EXPECT_STREQ(
        ini.r_string("test", "added"),
        "override-value");
}

TEST(XrIniDltx, SafeOverrideDoesNotCreateMissingSectionUnlessMarked)
{
    CInifile ini("test_ltx_safe_override.ltx");

    EXPECT_FALSE(ini.section_exist("missing"));
}

TEST(XrIniDltx, SafeOverrideCanCreateMissingSection)
{
    CInifile ini("test_ltx_safe_override_create.ltx");

    ASSERT_TRUE(ini.section_exist("created"));

    EXPECT_TRUE(ini.line_exist("created", "value"));
    EXPECT_STREQ(
        ini.r_string("created", "value"),
        "created-value");
}

TEST(XrIniDltx, OverrideSectionNameIsNormalizedToLowercase)
{
    CInifile ini("test_ltx_override_case.ltx");

    EXPECT_TRUE(ini.section_exist("test"));
    EXPECT_TRUE(ini.section_exist("TEST"));
    EXPECT_TRUE(ini.section_exist("TeSt"));
}

TEST(XrIniDltx, MultipleOverrideSectionsAreMerged)
{
    CInifile ini("test_ltx_multiple_overrides.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(ini.r_string("test", "first"), "first");
    EXPECT_STREQ(ini.r_string("test", "second"), "second");
    EXPECT_STREQ(ini.r_string("test", "third"), "third");
}

TEST(XrIniDltx, LastOverrideAtSameDepthWins)
{
    CInifile ini("test_ltx_multiple_overrides_same_depth.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "value"),
        "last");
}

// ============================================================================
// DLTX line deletion
// ============================================================================

TEST(XrIniDltx, DeleteLineRemovesLine)
{
    CInifile ini("test_ltx_delete_line.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_FALSE(ini.line_exist("test", "deleted"));
}

TEST(XrIniDltx, DeleteLineDoesNotAffectOtherLines)
{
    CInifile ini("test_ltx_delete_line.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_TRUE(ini.line_exist("test", "kept"));
    EXPECT_STREQ(
        ini.r_string("test", "kept"),
        "value");
}

// ============================================================================
// Section inheritance
// ============================================================================

TEST(XrIniInheritance, InheritedValueIsAvailable)
{
    CInifile ini("test_ltx_inheritance.ltx");

    ASSERT_TRUE(ini.section_exist("child"));

    EXPECT_TRUE(ini.line_exist("child", "parent_value"));
    EXPECT_STREQ(
        ini.r_string("child", "parent_value"),
        "from-parent");
}

TEST(XrIniInheritance, ChildValueOverridesInheritedValue)
{
    CInifile ini("test_ltx_inheritance_override.ltx");

    ASSERT_TRUE(ini.section_exist("child"));

    EXPECT_STREQ(
        ini.r_string("child", "value"),
        "from-child");
}

TEST(XrIniInheritance, ChildRetainsUnrelatedParentValues)
{
    CInifile ini("test_ltx_inheritance_override.ltx");

    ASSERT_TRUE(ini.section_exist("child"));

    EXPECT_STREQ(
        ini.r_string("child", "parent_only"),
        "from-parent");
}

TEST(XrIniInheritance, MultipleParentsAreMerged)
{
    CInifile ini("test_ltx_multiple_inheritance.ltx");

    ASSERT_TRUE(ini.section_exist("child"));

    EXPECT_STREQ(ini.r_string("child", "first"), "first-parent");
    EXPECT_STREQ(ini.r_string("child", "second"), "second-parent");
}

TEST(XrIniInheritance, LaterParentCanOverrideEarlierParent)
{
    CInifile ini("test_ltx_multiple_inheritance_override.ltx");

    ASSERT_TRUE(ini.section_exist("child"));

    EXPECT_STREQ(
        ini.r_string("child", "shared"),
        "second-parent");
}

TEST(XrIniInheritance, ParentCanBeRemoved)
{
    CInifile ini("test_ltx_parent_removal.ltx");

    ASSERT_TRUE(ini.section_exist("child"));

    EXPECT_FALSE(
        ini.line_exist("child", "removed_parent_value"));

    EXPECT_TRUE(
        ini.line_exist("child", "kept_parent_value"));
}

// ============================================================================
// Multiline values
// ============================================================================

TEST(XrIniLtx, QuotedWhitespaceIsPreserved)
{
    CInifile ini("test_ltx_quoted.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "value"),
        R"("hello   world")");
}

TEST(XrIniLtx, MultilineQuotedValueIsLoaded)
{
    CInifile ini("test_ltx_multiline.ltx");

    ASSERT_TRUE(ini.section_exist("test"));
    ASSERT_TRUE(ini.line_exist("test", "value"));

    const LPCSTR value = ini.r_string("test", "value");

    ASSERT_NE(value, nullptr);
    EXPECT_NE(strstr(value, "first line"), nullptr);
    EXPECT_NE(strstr(value, "second line"), nullptr);
}

TEST(XrIniLtx, EmptyLinesInsideMultilineQuotedValueArePreserved)
{
    CInifile ini("test_ltx_multiline_empty_line.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    const LPCSTR value = ini.r_string("test", "value");

    ASSERT_NE(value, nullptr);
    EXPECT_NE(strstr(value, "first line"), nullptr);
    EXPECT_NE(strstr(value, "second line"), nullptr);
}

// ============================================================================
// Includes
// ============================================================================

TEST(XrIniInclude, IncludedSectionIsLoaded)
{
    CInifile ini("test_ltx_include.ltx");

    EXPECT_TRUE(ini.section_exist("included"));
}

TEST(XrIniInclude, IncludedValuesAreLoaded)
{
    CInifile ini("test_ltx_include.ltx");

    ASSERT_TRUE(ini.section_exist("included"));

    EXPECT_STREQ(
        ini.r_string("included", "value"),
        "from-include");
}

TEST(XrIniInclude, NestedIncludeIsLoaded)
{
    CInifile ini("test_ltx_nested_include.ltx");

    ASSERT_TRUE(ini.section_exist("nested"));

    EXPECT_STREQ(
        ini.r_string("nested", "value"),
        "from-nested-include");
}

TEST(XrIniInclude, IncludedFileCanOverrideBaseData)
{
    CInifile ini("test_ltx_include_override.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "value"),
        "from-include");
}

// ============================================================================
// DLTX depth / insertion ordering
// ============================================================================

TEST(XrIniDltxOrdering, LowerDepthWins)
{
    CInifile ini("test_ltx_depth_order.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "value"),
        "lower-depth");
}

TEST(XrIniDltxOrdering, HigherInsertionIndexWinsAtSameDepth)
{
    CInifile ini("test_ltx_insertion_order.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "value"),
        "last-inserted");
}

TEST(XrIniDltxOrdering, OverrideCanWinAgainstBaseAtDifferentDepth)
{
    CInifile ini("test_ltx_override_depth.ltx");

    ASSERT_TRUE(ini.section_exist("test"));

    EXPECT_STREQ(
        ini.r_string("test", "value"),
        "override");
}

// ============================================================================
// CInifile cache
// ============================================================================

TEST(XrIniCache, InvalidateAllClearsCache)
{
    CInifile::InvalidateCache();

    u64 files_cached = 0;
    u64 total_bytes = 0;
    u64 section_count = 0;

    CInifile::GetCacheStats(
        files_cached,
        total_bytes,
        section_count);

    EXPECT_EQ(files_cached, 0u);
    EXPECT_EQ(total_bytes, 0u);
    EXPECT_EQ(section_count, 0u);
}

TEST(XrIniCache, InvalidatingMissingPathIsHarmless)
{
    CInifile::InvalidateCache(
        "this_file_definitely_does_not_exist.ltx");

    SUCCEED();
}

TEST(CInifile, IsBOOL)
{
    EXPECT_TRUE(CInifile::IsBOOL("on"));
    EXPECT_TRUE(CInifile::IsBOOL("yes"));
    EXPECT_TRUE(CInifile::IsBOOL("true"));
    EXPECT_TRUE(CInifile::IsBOOL("1"));

    EXPECT_FALSE(CInifile::IsBOOL("off"));
    EXPECT_FALSE(CInifile::IsBOOL("no"));
    EXPECT_FALSE(CInifile::IsBOOL("false"));
    EXPECT_FALSE(CInifile::IsBOOL("0"));

    // The implementation is case-sensitive.
    EXPECT_FALSE(CInifile::IsBOOL("TRUE"));
    EXPECT_FALSE(CInifile::IsBOOL("YES"));
}

TEST(CInifile, ItemOrdering)
{
    CInifile::Item a;
    CInifile::Item b;

    a.first = "alpha";
    b.first = "beta";

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(a < a);
}

TEST(CInifile, ItemComparatorSupportsTransparentLookup)
{
    CInifile::Sect section;
    CInifile::Item item;
    item.first = "key";
    item.second = "value";

    section.Data.push_back(item);

    const auto it = std::lower_bound(
        section.Data.begin(),
        section.Data.end(),
        "key",
        CInifile::item_comparator{}
    );

    ASSERT_NE(it, section.Data.end());
    EXPECT_STREQ(*it->first, "key");
    EXPECT_STREQ(*it->second, "value");
}

TEST(CInifile, SectLineExist)
{
    CInifile::Sect section;

    CInifile::Item first;
    first.first = "alpha";
    first.second = "one";

    CInifile::Item second;
    second.first = "beta";
    second.second = "two";

    section.Data.push_back(first);
    section.Data.push_back(second);
#if 0
    section.Data = {first, second};
#endif

    LPCSTR value = nullptr;

    EXPECT_TRUE(section.line_exist("alpha", &value));
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "one");

    EXPECT_TRUE(section.line_exist("beta", &value));
    EXPECT_STREQ(value, "two");

    EXPECT_FALSE(section.line_exist("missing", &value));
}

TEST(CInifile, SectLineExistWithoutValue)
{
    CInifile::Sect section;

    CInifile::Item item;
    item.first = "key";
    item.second = "value";
    section.Data.push_back(item);

    EXPECT_TRUE(section.line_exist("key"));
    EXPECT_FALSE(section.line_exist("missing"));
}

TEST(InifileParsing, ParseRemovesWhitespaceOutsideQuotes)
{
    char dest[256];

    EXPECT_FALSE(_parse(dest, "  hello   world  "));
    EXPECT_STREQ(dest, "helloworld");
}

TEST(InifileParsing, ParsePreservesWhitespaceInsideQuotes)
{
    char dest[256];

    EXPECT_FALSE(_parse(dest, R"(hello "foo   bar" baz)"));
    EXPECT_STREQ(dest, R"(hello"foo   bar"baz)");
}

TEST(InifileParsing, ParseDetectsUnclosedQuote)
{
    char dest[256];

    EXPECT_TRUE(_parse(dest, R"(hello "foo bar)"));
    EXPECT_STREQ(dest, R"(hello"foo bar)");
}

TEST(InifileParsing, ParseEmptyInput)
{
    char dest[256] = "garbage";

    EXPECT_FALSE(_parse(dest, ""));
    EXPECT_STREQ(dest, "");
}

TEST(InifileParsing, ParseNullInput)
{
    char dest[256] = "garbage";

    EXPECT_FALSE(_parse(dest, nullptr));
    EXPECT_STREQ(dest, "");
}

TEST(InifileParsing, DecorateCommaSeparatedValues)
{
    char dest[256];

    _decorate(dest, "one,two,three");

    EXPECT_STREQ(dest, "one, two, three");
}

TEST(InifileParsing, DecoratePreservesCommasInsideQuotes)
{
    char dest[256];

    _decorate(dest, R"(one,"two,three",four)");

    EXPECT_STREQ(dest, R"(one, "two,three", four)");
}

TEST(InifileParsing, DecorateEmptyInput)
{
    char dest[256] = "garbage";

    _decorate(dest, "");

    EXPECT_STREQ(dest, "");
}

TEST(InifileParsing, DecorateNullInput)
{
    char dest[256] = "garbage";

    _decorate(dest, nullptr);

    EXPECT_STREQ(dest, "");
}

#if 0
TEST(CInifile, LoadsSectionsAndValues)
{
    const auto path = WriteTestFile(
        "xr_ini_basic.ltx",
        R"(
[section]
key = value
number = 42
flag = true
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_TRUE(ini.section_exist("section"));
    EXPECT_FALSE(ini.section_exist("missing"));

    EXPECT_TRUE(ini.line_exist("section", "key"));
    EXPECT_STREQ(ini.r_string("section", "key"), "value");
    EXPECT_EQ(ini.r_s32("section", "number"), 42);
    EXPECT_TRUE(ini.r_bool("section", "flag"));

    EXPECT_EQ(ini.section_count(), 1u);
    EXPECT_EQ(ini.line_count("section"), 3u);

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, SectionNamesAndKeysAreCaseInsensitive)
{
    const auto path = WriteTestFile(
        "xr_ini_case.ltx",
        R"(
[MySection]
MyKey = value
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_TRUE(ini.section_exist("MySection"));
    EXPECT_TRUE(ini.section_exist("mysection"));

    EXPECT_TRUE(ini.line_exist("MySection", "MyKey"));
    EXPECT_TRUE(ini.line_exist("mysection", "mykey"));

    EXPECT_STREQ(ini.r_string("MYSECTION", "MYKEY"), "value");

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, CommentsAreIgnored)
{
    const auto path = WriteTestFile(
        "xr_ini_comments.ltx",
        R"(
[section]
key = value ; this is a comment
other = value // another comment
; whole line comment
// another whole line comment
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_STREQ(ini.r_string("section", "key"), "value");
    EXPECT_STREQ(ini.r_string("section", "other"), "value");

    EXPECT_EQ(ini.line_count("section"), 2u);

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, CommentMarkersInsideQuotesArePreserved)
{
    const auto path = WriteTestFile(
        "xr_ini_quoted_comment.ltx",
        R"(
[section]
url = "https://example.com/a;b//c"
text = "hello ; world // still text"
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_STREQ(
        ini.r_string_wb("section", "url").c_str(),
        "https://example.com/a;b//c"
    );

    EXPECT_STREQ(
        ini.r_string_wb("section", "text").c_str(),
        "hello ; world // still text"
    );

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, TypedValuesRoundTrip)
{
    const auto path = WriteTestFile(
        "xr_ini_typed.ltx",
        R"(
[values]
u8 = 255
u16 = 65535
u32 = 4294967295
s8 = -128
s16 = -32768
s32 = -123456
s64 = -1234567890123
u64 = 1234567890123
float = 3.5
bool = true
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_EQ(ini.r_u8("values", "u8"), 255);
    EXPECT_EQ(ini.r_u16("values", "u16"), 65535);
    EXPECT_EQ(ini.r_u32("values", "u32"), 4294967295u);

    EXPECT_EQ(ini.r_s8("values", "s8"), -128);
    EXPECT_EQ(ini.r_s16("values", "s16"), -32768);
    EXPECT_EQ(ini.r_s32("values", "s32"), -123456);
    EXPECT_EQ(ini.r_s64("values", "s64"), -1234567890123LL);
    EXPECT_EQ(ini.r_u64("values", "u64"), 1234567890123ULL);

    EXPECT_FLOAT_EQ(ini.r_float("values", "float"), 3.5f);
    EXPECT_TRUE(ini.r_bool("values", "bool"));

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, LastDuplicateKeyWins)
{
    const auto path = WriteTestFile(
        "xr_ini_duplicate.ltx",
        R"(
[section]
key = first
key = second
key = third
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_EQ(ini.line_count("section"), 1u);
    EXPECT_STREQ(ini.r_string("section", "key"), "third");

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, IncludedFileHasLowerPriorityThanRoot)
{
    const auto include_path = WriteTestFile(
        "xr_ini_include.ltx",
        R"(
[section]
key = included
)"
    );

    const auto root_path = WriteTestFile(
        "xr_ini_include_root.ltx",
        R"(
#include "xr_ini_include.ltx"

[section]
key = root
)"
    );

    CInifile::InvalidateCache(include_path.c_str());
    CInifile::InvalidateCache(root_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_STREQ(ini.r_string("section", "key"), "root");

    CInifile::InvalidateCache(include_path.c_str());
    CInifile::InvalidateCache(root_path.c_str());
}

TEST(CInifile, DLTXOverrideReplacesBaseValue)
{
    const auto root_path = WriteTestFile(
        "xr_ini_override_root.ltx",
        R"(
[section]
unchanged = base
overridden = base
)"
    );

    const auto mod_path = WriteTestFile(
        "mod_xr_ini_override_root_test.ltx",
        R"(
![section]
overridden = mod
)"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_STREQ(ini.r_string("section", "unchanged"), "base");
    EXPECT_STREQ(ini.r_string("section", "overridden"), "mod");

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());
}

TEST(CInifile, DLTXOverrideCanAddValue)
{
    const auto root_path = WriteTestFile(
        "xr_ini_override_add_root.ltx",
        R"(
[section]
existing = value
)"
    );

    const auto mod_path = WriteTestFile(
        "mod_xr_ini_override_add_root_test.ltx",
        R"(
![section]
added = value
)"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_TRUE(ini.line_exist("section", "existing"));
    EXPECT_TRUE(ini.line_exist("section", "added"));
    EXPECT_STREQ(ini.r_string("section", "added"), "value");

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());
}

TEST(CInifile, DLTXCanDeleteSection)
{
    const auto path = WriteTestFile(
        "xr_ini_delete_section.ltx",
        R"(
[keep]
value = yes

[remove]
value = no

!![remove]
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_TRUE(ini.section_exist("keep"));
    EXPECT_FALSE(ini.section_exist("remove"));

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, DLTXListInsert)
{
    const auto root_path = WriteTestFile(
        "xr_ini_list_insert_root.ltx",
        R"(
[section]
items = one,two
)"
    );

    const auto mod_path = WriteTestFile(
        "mod_xr_ini_list_insert_root_test.ltx",
        R"(
![section]
>items = three,four
)"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_STREQ(
        ini.r_string("section", "items"),
        "one,two,three,four"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());
}

TEST(CInifile, DLTXListRemove)
{
    const auto root_path = WriteTestFile(
        "xr_ini_list_remove_root.ltx",
        R"(
[section]
items = one,two,three,four
)"
    );

    const auto mod_path = WriteTestFile(
        "mod_xr_ini_list_remove_root_test.ltx",
        R"(
![section]
<items = two,four
)"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_STREQ(
        ini.r_string("section", "items"),
        "one,three"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());
}

TEST(CInifile, DLTXListInsertAndRemoveAreAppliedInOrder)
{
    const auto root_path = WriteTestFile(
        "xr_ini_list_order_root.ltx",
        R"(
[section]
items = one,two
)"
    );

    const auto mod_path = WriteTestFile(
        "mod_xr_ini_list_order_root_test.ltx",
        R"(
![section]
>items = three
<items = one
>items = four
)"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_STREQ(
        ini.r_string("section", "items"),
        "two,three,four"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());
}

TEST(CInifile, SectionInheritance)
{
    const auto path = WriteTestFile(
        "xr_ini_inheritance.ltx",
        R"(
[parent]
inherited = parent
overridden = parent

[child]:parent
own = child
overridden = child
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_STREQ(ini.r_string("child", "inherited"), "parent");
    EXPECT_STREQ(ini.r_string("child", "overridden"), "child");
    EXPECT_STREQ(ini.r_string("child", "own"), "child");

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, MultipleInheritance)
{
    const auto path = WriteTestFile(
        "xr_ini_multiple_inheritance.ltx",
        R"(
[first]
first = yes
shared = first

[second]
second = yes
shared = second

[child]:first,second
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    EXPECT_TRUE(ini.line_exist("child", "first"));
    EXPECT_TRUE(ini.line_exist("child", "second"));

    // Later parent wins when both define the same key.
    EXPECT_STREQ(ini.r_string("child", "shared"), "second");

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, DLTXCanOverrideInheritedValue)
{
    const auto root_path = WriteTestFile(
        "xr_ini_inherited_override_root.ltx",
        R"(
[parent]
value = parent

[child]:parent
)"
    );

    const auto mod_path = WriteTestFile(
        "mod_xr_ini_inherited_override_root_test.ltx",
        R"(
![parent]
value = modified
)"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_STREQ(ini.r_string("parent", "value"), "modified");
    EXPECT_STREQ(ini.r_string("child", "value"), "modified");

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());
}

TEST(CInifile, SafeOverrideCreatesMissingSection)
{
    const auto root_path = WriteTestFile(
        "xr_ini_safe_override_root.ltx",
        R"(
[existing]
value = base
)"
    );

    const auto mod_path = WriteTestFile(
        "mod_xr_ini_safe_override_root_test.ltx",
        R"(
@[new_section]
value = created
)"
    );

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());

    CInifile ini(root_path.c_str(), TRUE);

    EXPECT_TRUE(ini.section_exist("new_section"));
    EXPECT_STREQ(ini.r_string("new_section", "value"), "created");

    CInifile::InvalidateCache(root_path.c_str());
    CInifile::InvalidateCache(mod_path.c_str());
}

TEST(CInifile, CacheReturnsPreviouslyLoadedData)
{
    const auto path = WriteTestFile(
        "xr_ini_cache.ltx",
        R"(
[section]
value = original
)"
    );

    CInifile::InvalidateCache(path.c_str());

    u64 files_cached = 0;
    u64 total_bytes = 0;
    u64 section_count = 0;

    CInifile::InvalidateCache(path.c_str());

    CInifile first(path.c_str(), TRUE);

    CInifile::GetCacheStats(
        files_cached,
        total_bytes,
        section_count
    );

    EXPECT_EQ(files_cached, 1u);
    EXPECT_EQ(section_count, 1u);
    EXPECT_GT(total_bytes, 0u);

    CInifile second(path.c_str(), TRUE);

    EXPECT_STREQ(second.r_string("section", "value"), "original");

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, CacheCanBeInvalidated)
{
    const auto path = WriteTestFile(
        "xr_ini_cache_invalidate.ltx",
        R"(
[section]
value = original
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile first(path.c_str(), TRUE);
    EXPECT_STREQ(first.r_string("section", "value"), "original");

    u64 files_cached = 0;
    u64 total_bytes = 0;
    u64 section_count = 0;

    CInifile::GetCacheStats(
        files_cached,
        total_bytes,
        section_count
    );

    EXPECT_EQ(files_cached, 1u);

    CInifile::InvalidateCache(path.c_str());

    CInifile::GetCacheStats(
        files_cached,
        total_bytes,
        section_count
    );

    EXPECT_EQ(files_cached, 0u);

    CInifile::InvalidateCache(path.c_str());
}

TEST(CInifile, CacheStatsCountSections)
{
    const auto path = WriteTestFile(
        "xr_ini_cache_stats.ltx",
        R"(
[first]
a = one
b = two

[second]
c = three
)"
    );

    CInifile::InvalidateCache(path.c_str());

    CInifile ini(path.c_str(), TRUE);

    u64 files_cached = 0;
    u64 total_bytes = 0;
    u64 section_count = 0;

    CInifile::GetCacheStats(
        files_cached,
        total_bytes,
        section_count
    );

    EXPECT_EQ(files_cached, 1u);
    EXPECT_EQ(section_count, 2u);
    EXPECT_GT(total_bytes, 0u);

    CInifile::InvalidateCache(path.c_str());
}
#endif

// TODO: Finish
