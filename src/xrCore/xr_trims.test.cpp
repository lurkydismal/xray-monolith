#include "stdafx.h"

#include "xr_trims.h"

#include <gtest/gtest.h>

namespace
{
TEST(XrTrims, TrimLeft)
{
    char s[] = "  \t\nhello  ";
    EXPECT_STREQ(_TrimLeft(s), "hello  ");
}

TEST(XrTrims, TrimRight)
{
    char s[] = "  hello \t\n";
    EXPECT_STREQ(_TrimRight(s), "  hello");
}

TEST(XrTrims, Trim)
{
    char s[] = " \t hello world \n ";
    EXPECT_STREQ(_Trim(s), "hello world");
}

#if 0
TEST(XrTrims, TrimEmpty)
{
    char s[] = "";
    EXPECT_STREQ(_Trim(s), "");

    char spaces[] = " \t\r\n";
    EXPECT_STREQ(_Trim(spaces), "");
}
#endif

TEST(XrTrims, TrimString)
{
    xr_string s = " \t hello world \n ";
    EXPECT_EQ(&_Trim(s), &s);
    EXPECT_EQ(s, "hello world");
}

TEST(XrTrims, TrimLeftString)
{
    xr_string s = " \t hello  ";
    EXPECT_EQ(&_TrimLeft(s), &s);
    EXPECT_EQ(s, "hello  ");
}

TEST(XrTrims, TrimRightString)
{
    xr_string s = "  hello \t ";
    EXPECT_EQ(&_TrimRight(s), &s);
    EXPECT_EQ(s, "  hello");
}

TEST(XrTrims, SetPos)
{
    EXPECT_STREQ(_SetPos("one,two,three", 0), "one,two,three");
    EXPECT_STREQ(_SetPos("one,two,three", 1), "two,three");
    EXPECT_STREQ(_SetPos("one,two,three", 2), "three");
}

TEST(XrTrims, SetPosPastEnd)
{
    EXPECT_STREQ(_SetPos("one,two", 3), "");
}

TEST(XrTrims, SetPosCustomSeparator)
{
    EXPECT_STREQ(_SetPos("one;two;three", 1, ';'), "two;three");
    EXPECT_STREQ(_SetPos("one;two;three", 2, ';'), "three");
}

TEST(XrTrims, GetItemCount)
{
    EXPECT_EQ(_GetItemCount("one,two,three"), 3);
    EXPECT_EQ(_GetItemCount("one"), 1);
    EXPECT_EQ(_GetItemCount(""), 0);
}

TEST(XrTrims, GetItemCountCustomSeparator)
{
    EXPECT_EQ(_GetItemCount("one;two;three", ';'), 3);
}

TEST(XrTrims, GetItemCountTrailingSeparator)
{
    // Current implementation does not count the empty item after the
    // trailing separator.
    EXPECT_EQ(_GetItemCount("one,two,"), 2);
}

TEST(XrTrims, GetItemCountConsecutiveSeparators)
{
    // Preserve the current special handling of consecutive separators.
    EXPECT_EQ(_GetItemCount("one,,two"), 2);
}

TEST(XrTrims, GetItemCountNull)
{
    EXPECT_EQ(_GetItemCount(nullptr), 0);
}

TEST(XrTrims, CopyVal)
{
    char dst[64];

    EXPECT_STREQ(_CopyVal("hello,world", dst, sizeof(dst)), "hello");
    EXPECT_STREQ(_CopyVal("hello", dst, sizeof(dst)), "hello");
}

TEST(XrTrims, CopyValCustomSeparator)
{
    char dst[64];

    EXPECT_STREQ(_CopyVal("hello;world", dst, sizeof(dst), ';'), "hello");
}

#if 0
TEST(XrTrims, CopyValTruncates)
{
    char dst[5];

    EXPECT_STREQ(_CopyVal("abcdef", dst, sizeof(dst)), "abcd");
}
#endif

TEST(XrTrims, GetItem)
{
    char dst[64];

    EXPECT_STREQ(_GetItem("one,two,three", 0, dst, sizeof(dst)), "one");
    EXPECT_STREQ(_GetItem("one,two,three", 1, dst, sizeof(dst)), "two");
    EXPECT_STREQ(_GetItem("one,two,three", 2, dst, sizeof(dst)), "three");
}

TEST(XrTrims, GetItemTrimsByDefault)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItem("  one  ,  two  ,  three  ", 1, dst, sizeof(dst)),
        "two");
}

TEST(XrTrims, GetItemWithoutTrim)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItem("  one  ,  two  ,  three  ", 1, dst, sizeof(dst), ',', "", false),
        "  two  ");
}

TEST(XrTrims, GetItemDefault)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItem("one,two", 10, dst, sizeof(dst), ',', "default"),
        "default");
}

TEST(XrTrims, GetItemCustomSeparator)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItem("one;two;three", 1, dst, sizeof(dst), ';'),
        "two");
}

TEST(XrTrims, GetItems)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItems("one,two,three,four", 1, 3, dst),
        "two,three");
}

TEST(XrTrims, GetItemsFromBeginning)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItems("one,two,three", 0, 2, dst),
        "one,two");
}

TEST(XrTrims, GetItemsSingleItem)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItems("one,two,three", 1, 2, dst),
        "two");
}

TEST(XrTrims, GetItemsCustomSeparator)
{
    char dst[64];

    EXPECT_STREQ(
        _GetItems("one;two;three", 1, 3, dst, ';'),
        "two;three");
}

TEST(XrTrims, ChangeSymbol)
{
    char s[] = "a-b-c";

    EXPECT_STREQ(_ChangeSymbol(s, '-', '_'), "a_b_c");
}

TEST(XrTrims, ChangeSymbolString)
{
    xr_string s = "a-b-c";

    EXPECT_EQ(&_ChangeSymbol(s, '-', '_'), &s);
    EXPECT_EQ(s, "a_b_c");
}

TEST(XrTrims, ChangeSymbolNoMatches)
{
    char s[] = "abcdef";

    EXPECT_STREQ(_ChangeSymbol(s, '-', '_'), "abcdef");
}

TEST(XrTrims, ReplaceItem)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItem("one,two,three", 1, "replacement", dst, ','),
        "one,replacement,three");
}

TEST(XrTrims, ReplaceFirstItem)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItem("one,two,three", 0, "replacement", dst, ','),
        "replacement,two,three");
}

TEST(XrTrims, ReplaceLastItem)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItem("one,two,three", 2, "replacement", dst, ','),
        "one,two,replacement");
}

TEST(XrTrims, ReplaceItemWithEmpty)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItem("one,two,three", 1, "", dst, ','),
        "one,,three");
}

TEST(XrTrims, ReplaceItemCustomSeparator)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItem("one;two;three", 1, "replacement", dst, ';'),
        "one;replacement;three");
}

TEST(XrTrims, ReplaceItems)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItems("one,two,three,four", 1, 3, "replacement", dst, ','),
        "one,replacement,four");
}

TEST(XrTrims, ReplaceItemsFromBeginning)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItems("one,two,three", 0, 2, "replacement", dst, ','),
        "replacement,three");
}

TEST(XrTrims, ReplaceItemsToEnd)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItems("one,two,three", 1, 3, "replacement", dst, ','),
        "one,replacement");
}

TEST(XrTrims, ReplaceItemsCustomSeparator)
{
    char dst[128];

    EXPECT_STREQ(
        _ReplaceItems("one;two;three;four", 1, 3, "replacement", dst, ';'),
        "one;replacement;four");
}

TEST(XrTrims, SequenceToList)
{
    RStringVec result;

    _SequenceToList(result, "one,two,three");

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(*result[0], "one");
    EXPECT_EQ(*result[1], "two");
    EXPECT_EQ(*result[2], "three");
}

TEST(XrTrims, SequenceToListTrimsItems)
{
    RStringVec result;

    _SequenceToList(result, " one , two \t, three ");

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(*result[0], "one");
    EXPECT_EQ(*result[1], "two");
    EXPECT_EQ(*result[2], "three");
}

TEST(XrTrims, SequenceToListSkipsEmptyItems)
{
    RStringVec result;

    _SequenceToList(result, "one,,two, ,three");

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(*result[0], "one");
    EXPECT_EQ(*result[1], "two");
    EXPECT_EQ(*result[2], "three");
}

TEST(XrTrims, SequenceToListClearsExistingRStringVec)
{
    RStringVec result;
    result.push_back(shared_str("old"));

    _SequenceToList(result, "one,two");

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(*result[0], "one");
    EXPECT_EQ(*result[1], "two");
}

TEST(XrTrims, SequenceToListCustomSeparator)
{
    SStringVec result;

    _SequenceToList(result, "one;two;three", ';');

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "one");
    EXPECT_EQ(result[1], "two");
    EXPECT_EQ(result[2], "three");
}

TEST(XrTrims, SequenceToListStringVec)
{
    SStringVec result;

    _SequenceToList(result, " one , two , three ");

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "one");
    EXPECT_EQ(result[1], "two");
    EXPECT_EQ(result[2], "three");
}

TEST(XrTrims, ListToSequenceStringVec)
{
    SStringVec list;
    list.push_back("one");
    list.push_back("two");
    list.push_back("three");

    EXPECT_EQ(_ListToSequence(list), "one,two,three");
}

TEST(XrTrims, ListToSequenceEmptyStringVec)
{
    SStringVec list;

    EXPECT_EQ(_ListToSequence(list), "");
}

#if 0
TEST(XrTrims, ListToSequenceRStringVec)
{
    RStringVec list;
    list.push_back(shared_str("one"));
    list.push_back(shared_str("two"));
    list.push_back(shared_str("three"));

    EXPECT_STREQ(_ListToSequence(list).c_str(), "one,two,three");
}
#endif

TEST(XrTrims, ListToSequenceSingleItem)
{
    SStringVec list;
    list.push_back("one");

    EXPECT_EQ(_ListToSequence(list), "one");
}

TEST(XrTrims, ParseItem)
{
    xr_token tokens[] = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {nullptr, 0},
    };

    EXPECT_EQ(_ParseItem("one", tokens), 1u);
    EXPECT_EQ(_ParseItem("two", tokens), 2u);
    EXPECT_EQ(_ParseItem("three", tokens), 3u);
}

TEST(XrTrims, ParseItemIsCaseInsensitive)
{
    xr_token tokens[] = {
        {"One", 42},
        {nullptr, 0},
    };

    EXPECT_EQ(_ParseItem("one", tokens), 42u);
    EXPECT_EQ(_ParseItem("ONE", tokens), 42u);
}

TEST(XrTrims, ParseItemUnknown)
{
    xr_token tokens[] = {
        {"one", 1},
        {"two", 2},
        {nullptr, 0},
    };

    EXPECT_EQ(_ParseItem("three", tokens), u32(-1));
}

TEST(XrTrims, ParseItemFromSequence)
{
    xr_token tokens[] = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {nullptr, 0},
    };

    char src[] = "one,two,three";

    EXPECT_EQ(_ParseItem(src, 0, tokens), 1u);
    EXPECT_EQ(_ParseItem(src, 1, tokens), 2u);
    EXPECT_EQ(_ParseItem(src, 2, tokens), 3u);
}

TEST(XrTrims, CopyValString)
{
    xr_string dst;

    EXPECT_STREQ(
        _CopyVal("hello,world", dst),
        "hello");

    EXPECT_EQ(dst, "hello");
}

TEST(XrTrims, CopyValStringWithoutSeparator)
{
    xr_string dst;

    EXPECT_STREQ(
        _CopyVal("hello", dst),
        "hello");

    EXPECT_EQ(dst, "hello");
}

TEST(XrTrims, GetItemString)
{
    xr_string dst;

    EXPECT_STREQ(
        _GetItem("one,two,three", 1, dst),
        "two");

    EXPECT_EQ(dst, "two");
}

TEST(XrTrims, GetItemStringTrims)
{
    xr_string dst;

    EXPECT_STREQ(
        _GetItem(" one , two , three ", 1, dst),
        "two");
}

TEST(XrTrims, GetItemStringWithoutTrim)
{
    xr_string dst;

    EXPECT_STREQ(
        _GetItem(" one , two , three ", 1, dst, ',', "", false),
        " two ");

    EXPECT_EQ(dst, " two ");
}

TEST(XrTrims, GetItemStringDefault)
{
    xr_string dst;

    EXPECT_STREQ(
        _GetItem("one,two", 10, dst, ',', "default"),
        "default");

    EXPECT_EQ(dst, "default");
}

TEST(XrTrims, ListToSequenceReturnsExpectedValue)
{
    SStringVec list;
    list.push_back("one");
    list.push_back("two");

    xr_string result = _ListToSequence(list);

    EXPECT_EQ(result, "one,two");
}

TEST(XrTrims, ListToSequenceEmptyReturnsEmpty)
{
    SStringVec list;

    EXPECT_EQ(_ListToSequence(list), "");
}
}
