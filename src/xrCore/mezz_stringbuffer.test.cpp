#include "stdafx.h"

#include "mezz_stringbuffer.h"

#include <gtest/gtest.h>

namespace
{

TEST(MezzStringBuffer, DefaultConstruction)
{
	MezzStringBuffer buffer;

	EXPECT_EQ(buffer.GetSize(), 4096u);
	EXPECT_NE(buffer.GetBuffer(), nullptr);
	EXPECT_EQ(static_cast<char*>(buffer), buffer.GetBuffer());
}

TEST(MezzStringBuffer, CustomSize)
{
	MezzStringBuffer buffer(128);

	EXPECT_EQ(buffer.GetSize(), 128u);
	EXPECT_NE(buffer.GetBuffer(), nullptr);
	EXPECT_EQ(static_cast<char*>(buffer), buffer.GetBuffer());
}

TEST(MezzStringBuffer, BufferIsWritable)
{
	MezzStringBuffer buffer(16);

	char* data = buffer.GetBuffer();

	ASSERT_NE(data, nullptr);

	data[0] = 'a';
	data[1] = 'b';
	data[2] = '\0';

	EXPECT_STREQ(data, "ab");
	EXPECT_EQ(static_cast<char*>(buffer), data);
}

TEST(MezzStringBuffer, ZeroSize)
{
	MezzStringBuffer buffer(0);

	EXPECT_EQ(buffer.GetSize(), 0u);

	// Do not require GetBuffer() to be nullptr.
	// std::make_unique<char[]>(0) is allowed to return a non-null pointer.
	EXPECT_EQ(static_cast<char*>(buffer), buffer.GetBuffer());
}


// -----------------------------------------------------------------------------
// splitStringMulti
// -----------------------------------------------------------------------------

TEST(StringUtils, SplitStringMultiSingleSeparator)
{
	EXPECT_EQ(
		splitStringMulti("one,two,three", ","),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringMultiMultipleSeparators)
{
	// separator is interpreted as a set of separator characters because
	// std::string::find_first_of() is used.
	EXPECT_EQ(
		splitStringMulti("one,two;three four", ",; "),
		(std::vector<std::string>{"one", "two", "three", "four"}));
}

TEST(StringUtils, SplitStringMultiRepeatedSeparators)
{
	// Empty elements between consecutive separators are discarded.
	EXPECT_EQ(
		splitStringMulti("one,,two,,,three", ","),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringMultiLeadingAndTrailingSeparators)
{
	EXPECT_EQ(
		splitStringMulti(",one,two,", ","),
		(std::vector<std::string>{"one", "two"}));
}

TEST(StringUtils, SplitStringMultiNoSeparators)
{
	EXPECT_EQ(
		splitStringMulti("one two three", ","),
		(std::vector<std::string>{"one two three"}));
}

TEST(StringUtils, SplitStringMultiEmptyString)
{
	EXPECT_TRUE(splitStringMulti("", ",").empty());
}

TEST(StringUtils, SplitStringMultiIncludeSeparators)
{
	EXPECT_EQ(
		splitStringMulti("one,two,three", ",", true),
		(std::vector<std::string>{
			"one", ",",
			"two", ",",
			"three"
		}));
}

TEST(StringUtils, SplitStringMultiIncludeRepeatedSeparators)
{
	EXPECT_EQ(
		splitStringMulti("one,,two", ",", true),
		(std::vector<std::string>{
			"one", ",", ",", "two"
		}));
}

TEST(StringUtils, SplitStringMultiTrimStrings)
{
	EXPECT_EQ(
		splitStringMulti("  one  ,  two  ,  three  ", ",", false, true),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringMultiDoesNotTrimByDefault)
{
	EXPECT_EQ(
		splitStringMulti("  one  ,  two  ", ","),
		(std::vector<std::string>{"  one  ", "  two  "}));
}

TEST(StringUtils, SplitStringMultiMultipleLines)
{
	EXPECT_EQ(
		splitStringMulti("one,two\nthree,four", ","),
		(std::vector<std::string>{"one", "two", "three", "four"}));
}

TEST(StringUtils, SplitStringMultiTrailingNewline)
{
	EXPECT_EQ(
		splitStringMulti("one,two\n", ","),
		(std::vector<std::string>{"one", "two"}));
}


// -----------------------------------------------------------------------------
// splitStringLimit
// -----------------------------------------------------------------------------

TEST(StringUtils, SplitStringLimitZero)
{
	EXPECT_EQ(
		splitStringLimit("one,two,three", ",", 0),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringLimitNegative)
{
	// limit <= 0 behaves like unlimited splitting.
	EXPECT_EQ(
		splitStringLimit("one,two,three", ",", -1),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringLimitOne)
{
	EXPECT_EQ(
		splitStringLimit("one,two,three", ",", 1),
		(std::vector<std::string>{"one", "two,three"}));
}

TEST(StringUtils, SplitStringLimitTwo)
{
	EXPECT_EQ(
		splitStringLimit("one,two,three,four", ",", 2),
		(std::vector<std::string>{"one", "two", "three,four"}));
}

TEST(StringUtils, SplitStringLimitGreaterThanNumberOfParts)
{
	EXPECT_EQ(
		splitStringLimit("one,two,three", ",", 10),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringLimitRepeatedSeparators)
{
	EXPECT_EQ(
		splitStringLimit("one,,two,,,three", ",", 2),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringLimitTrimStrings)
{
	EXPECT_EQ(
		splitStringLimit("  one  ,  two  ,  three  ", ",", 0, true),
		(std::vector<std::string>{"one", "two", "three"}));
}

TEST(StringUtils, SplitStringLimitMultipleLines)
{
	EXPECT_EQ(
		splitStringLimit("one,two\nthree,four", ",", 0),
		(std::vector<std::string>{"one", "two", "three", "four"}));
}


// -----------------------------------------------------------------------------
// getFilename
// -----------------------------------------------------------------------------

TEST(StringUtils, GetFilename)
{
	EXPECT_EQ(getFilename(R"(C:\Games\STALKER\gamedata\config.ltx)"),
		"config.ltx");
}

TEST(StringUtils, GetFilenameNestedPath)
{
	EXPECT_EQ(getFilename(R"(foo\bar\baz.txt)"),
		"baz.txt");
}

TEST(StringUtils, GetFilenameOnlyFilename)
{
	EXPECT_EQ(getFilename("config.ltx"),
		"config.ltx");
}

TEST(StringUtils, GetFilenameEmpty)
{
	EXPECT_EQ(getFilename(""),
		"");
}

TEST(StringUtils, GetFilenameTrailingSeparator)
{
	// Current implementation drops the empty final component.
	EXPECT_EQ(getFilename(R"(foo\bar\)"),
		"bar");
}

TEST(StringUtils, GetFilenameForwardSlashIsNotSeparator)
{
	// The implementation only splits on '\\'.
	EXPECT_EQ(getFilename("foo/bar/baz.txt"),
		"foo/bar/baz.txt");
}


// -----------------------------------------------------------------------------
// trim
// -----------------------------------------------------------------------------

TEST(StringUtils, Trim)
{
	std::string value = "  hello  ";

	trim(value);

	EXPECT_EQ(value, "hello");
}

TEST(StringUtils, TrimAllDefaultWhitespace)
{
	std::string value = " \t\n\r\f\vhello \t\n\r\f\v";

	trim(value);

	EXPECT_EQ(value, "hello");
}

TEST(StringUtils, TrimLeadingWhitespace)
{
	std::string value = "   hello";

	trim(value);

	EXPECT_EQ(value, "hello");
}

TEST(StringUtils, TrimTrailingWhitespace)
{
	std::string value = "hello   ";

	trim(value);

	EXPECT_EQ(value, "hello");
}

TEST(StringUtils, TrimEmptyString)
{
	std::string value;

	trim(value);

	EXPECT_TRUE(value.empty());
}

TEST(StringUtils, TrimWhitespaceOnly)
{
	std::string value = " \t\n\r\f\v";

	trim(value);

	EXPECT_TRUE(value.empty());
}

TEST(StringUtils, TrimCustomCharacters)
{
	std::string value = "---hello---";

	trim(value, "-");

	EXPECT_EQ(value, "hello");
}

TEST(StringUtils, TrimPreservesInternalWhitespace)
{
	std::string value = "  hello   world  ";

	trim(value);

	EXPECT_EQ(value, "hello   world");
}

TEST(StringUtils, TrimCopy)
{
	const std::string original = "  hello  ";

	EXPECT_EQ(trimCopy(original), "hello");
	EXPECT_EQ(original, "  hello  ");
}

TEST(StringUtils, TrimCopyCustomCharacters)
{
	EXPECT_EQ(trimCopy("---hello---", "-"), "hello");
}


// -----------------------------------------------------------------------------
// toLowerCase
// -----------------------------------------------------------------------------

TEST(StringUtils, ToLowerCase)
{
	std::string value = "Hello WORLD";

	toLowerCase(value);

	EXPECT_EQ(value, "hello world");
}

TEST(StringUtils, ToLowerCaseEmpty)
{
	std::string value;

	toLowerCase(value);

	EXPECT_TRUE(value.empty());
}

TEST(StringUtils, ToLowerCaseAlreadyLowercase)
{
	std::string value = "hello world 123";

	toLowerCase(value);

	EXPECT_EQ(value, "hello world 123");
}

TEST(StringUtils, ToLowerCaseCopy)
{
	const std::string original = "Hello WORLD";

	EXPECT_EQ(toLowerCaseCopy(original), "hello world");
	EXPECT_EQ(original, "Hello WORLD");
}

TEST(StringUtils, ToLowerCasePreservesNonAlphabeticCharacters)
{
	EXPECT_EQ(
		toLowerCaseCopy(xr_string("ABC123!@#$%^&*()_+-=")),
		"abc123!@#$%^&*()_+-=");
}


// -----------------------------------------------------------------------------
// replaceAll
// -----------------------------------------------------------------------------

TEST(StringUtils, ReplaceAll)
{
	std::string value = "hello world";

	replaceAll(value, "world", "there");

	EXPECT_EQ(value, "hello there");
}

TEST(StringUtils, ReplaceAllMultipleOccurrences)
{
	std::string value = "foo bar foo baz foo";

	replaceAll(value, "foo", "qux");

	EXPECT_EQ(value, "qux bar qux baz qux");
}

TEST(StringUtils, ReplaceAllNoMatch)
{
	std::string value = "hello world";

	replaceAll(value, "xyz", "abc");

	EXPECT_EQ(value, "hello world");
}

TEST(StringUtils, ReplaceAllEmptyFrom)
{
	std::string value = "hello";

	replaceAll(value, "", "xyz");

	EXPECT_EQ(value, "hello");
}

TEST(StringUtils, ReplaceAllWithEmptyTo)
{
	std::string value = "hello world";

	replaceAll(value, " ", "");

	EXPECT_EQ(value, "helloworld");
}

TEST(StringUtils, ReplaceAllWithLongerString)
{
	std::string value = "aaaa";

	replaceAll(value, "a", "xyz");

	EXPECT_EQ(value, "xyzxyzxyzxyz");
}

TEST(StringUtils, ReplaceAllCopy)
{
	const std::string original = "hello world";

	EXPECT_EQ(
		replaceAllCopy(original, "world", "there"),
		"hello there");

	EXPECT_EQ(original, "hello world");
}

TEST(StringUtils, ReplaceAllReplacementContainingSearchString)
{
	std::string value = "x";

	replaceAll(value, "x", "yx");

	EXPECT_EQ(value, "yx");
}

TEST(StringUtils, ReplaceAllOverlappingOccurrences)
{
	std::string value = "aaa";

	// std::string::replace() advances past the replacement.
	EXPECT_EQ(replaceAllCopy(value, "aa", "b"), "ba");
}

} // namespace
