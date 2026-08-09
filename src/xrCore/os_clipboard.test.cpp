#include "stdafx.h"

#include "os_clipboard.h"

#include <gtest/gtest.h>

#include <windows.h>

namespace
{

class OSClipboardTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		if (!OpenClipboard(nullptr))
		{
			GTEST_SKIP() << "Windows clipboard is unavailable";
		}

		EmptyClipboard();
		CloseClipboard();
	}

	void TearDown() override
	{
		if (OpenClipboard(nullptr))
		{
			EmptyClipboard();
			CloseClipboard();
		}
	}
};

bool clipboardAvailable()
{
	if (!OpenClipboard(nullptr))
		return false;

	CloseClipboard();
	return true;
}

void setClipboardText(const char* text)
{
	ASSERT_NE(text, nullptr);

	const SIZE_T size = strlen(text) + 1;

	HGLOBAL handle = GlobalAlloc(GHND, size);
	ASSERT_NE(handle, nullptr);

	char* memory = static_cast<char*>(GlobalLock(handle));
	ASSERT_NE(memory, nullptr);

	memcpy(memory, text, size);

	GlobalUnlock(handle);

	ASSERT_NE(SetClipboardData(CF_TEXT, handle), nullptr);

	// SetClipboardData owns the HGLOBAL after success.
}

std::string getClipboardText()
{
	if (!OpenClipboard(nullptr))
		return {};

	HGLOBAL handle = GetClipboardData(CF_TEXT);
	if (!handle)
	{
		CloseClipboard();
		return {};
	}

	const char* memory =
		static_cast<const char*>(GlobalLock(handle));

	if (!memory)
	{
		CloseClipboard();
		return {};
	}

	std::string result(memory);

	GlobalUnlock(handle);
	CloseClipboard();

	return result;
}


// -----------------------------------------------------------------------------
// copy_to_clipboard
// -----------------------------------------------------------------------------

TEST_F(OSClipboardTest, CopyToClipboardCopiesText)
{
	os_clipboard::copy_to_clipboard("hello");

	EXPECT_EQ(getClipboardText(), "hello");
}

TEST_F(OSClipboardTest, CopyToClipboardCopiesEmptyString)
{
	os_clipboard::copy_to_clipboard("");

	EXPECT_EQ(getClipboardText(), "");
}

TEST_F(OSClipboardTest, CopyToClipboardReplacesExistingClipboard)
{
	os_clipboard::copy_to_clipboard("first");
	ASSERT_EQ(getClipboardText(), "first");

	os_clipboard::copy_to_clipboard("second");

	EXPECT_EQ(getClipboardText(), "second");
}

TEST_F(OSClipboardTest, CopyToClipboardPreservesWhitespace)
{
	os_clipboard::copy_to_clipboard("hello\tworld\nnext");

	EXPECT_EQ(getClipboardText(), "hello\tworld\nnext");
}

TEST_F(OSClipboardTest, CopyToClipboardPreservesEmbeddedNullTerminatedText)
{
	os_clipboard::copy_to_clipboard("abc");

	const std::string result = getClipboardText();

	EXPECT_EQ(result.size(), 3u);
	EXPECT_EQ(result, "abc");
}


// -----------------------------------------------------------------------------
// paste_from_clipboard
// -----------------------------------------------------------------------------

TEST_F(OSClipboardTest, PasteFromClipboardCopiesText)
{
	os_clipboard::copy_to_clipboard("hello");

	char buffer[32] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "hello");
}

TEST_F(OSClipboardTest, PasteFromClipboardCopiesEmptyText)
{
	os_clipboard::copy_to_clipboard("");

	char buffer[32] = "unchanged";

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "");
}

TEST_F(OSClipboardTest, PasteFromClipboardTruncatesToBufferSize)
{
	os_clipboard::copy_to_clipboard("abcdefghijklmnopqrstuvwxyz");

	char buffer[8] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "abcdefg");
	EXPECT_EQ(buffer[7], '\0');
}

TEST_F(OSClipboardTest, PasteFromClipboardWithOneByteBuffer)
{
	os_clipboard::copy_to_clipboard("hello");

	char buffer[1] = {'x'};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_EQ(buffer[0], '\0');
}

TEST_F(OSClipboardTest, PasteFromClipboardPreservesPrintableCharacters)
{
	os_clipboard::copy_to_clipboard(
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789"
		"!@#$%^&*()_+-=[]{}");

	char buffer[256] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(
		buffer,
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789"
		"!@#$%^&*()_+-=[]{}");
}

TEST_F(OSClipboardTest, PasteFromClipboardReplacesTabWithSpace)
{
	setClipboardText("hello\tworld");

	char buffer[32] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "hello world");
}

TEST_F(OSClipboardTest, PasteFromClipboardReplacesNewlineWithSpace)
{
	setClipboardText("hello\nworld");

	char buffer[32] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "hello world");
}

TEST_F(OSClipboardTest, PasteFromClipboardReplacesCarriageReturnWithSpace)
{
	setClipboardText("hello\rworld");

	char buffer[32] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "hello world");
}

TEST_F(OSClipboardTest, PasteFromClipboardReplacesNonPrintableCharacters)
{
	char text[] = {
		'h',
		'e',
		'l',
		'l',
		'o',
		'\x01',
		'\x02',
		'\x07',
		'w',
		'o',
		'r',
		'l',
		'd',
		'\0'
	};

	setClipboardText(text);

	char buffer[32] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "hello   world");
}

TEST_F(OSClipboardTest, PasteFromClipboardDoesNotModifyClipboard)
{
	os_clipboard::copy_to_clipboard("hello\tworld");

	char buffer[32] = {};

	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "hello world");
	EXPECT_EQ(getClipboardText(), "hello\tworld");
}

TEST_F(OSClipboardTest, PasteFromClipboardLeavesBufferEmptyWhenClipboardHasNoText)
{
	char buffer[32] = {};

	// Clipboard was emptied by SetUp().
	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "");
}


// -----------------------------------------------------------------------------
// update_clipboard
// -----------------------------------------------------------------------------

TEST_F(OSClipboardTest, UpdateClipboardAppendsToExistingText)
{
	os_clipboard::copy_to_clipboard("hello");

	os_clipboard::update_clipboard(" world");

	EXPECT_EQ(getClipboardText(), "hello world");
}

TEST_F(OSClipboardTest, UpdateClipboardAppendsEmptyString)
{
	os_clipboard::copy_to_clipboard("hello");

	os_clipboard::update_clipboard("");

	EXPECT_EQ(getClipboardText(), "hello");
}

TEST_F(OSClipboardTest, UpdateClipboardWithEmptyExistingClipboard)
{
	os_clipboard::update_clipboard("hello");

	EXPECT_EQ(getClipboardText(), "hello");
}

TEST_F(OSClipboardTest, UpdateClipboardWithBothStringsEmpty)
{
	os_clipboard::copy_to_clipboard("");

	os_clipboard::update_clipboard("");

	EXPECT_EQ(getClipboardText(), "");
}

TEST_F(OSClipboardTest, UpdateClipboardAppendsMultipleTimes)
{
	os_clipboard::copy_to_clipboard("one");

	os_clipboard::update_clipboard(" two");
	os_clipboard::update_clipboard(" three");
	os_clipboard::update_clipboard(" four");

	EXPECT_EQ(getClipboardText(), "one two three four");
}

TEST_F(OSClipboardTest, UpdateClipboardPreservesWhitespace)
{
	os_clipboard::copy_to_clipboard("hello");

	os_clipboard::update_clipboard("\tworld\n");

	EXPECT_EQ(getClipboardText(), "hello\tworld\n");
}

TEST_F(OSClipboardTest, UpdateClipboardDoesNotModifyExistingClipboardUntilReplacement)
{
	os_clipboard::copy_to_clipboard("first");

	os_clipboard::update_clipboard("second");

	EXPECT_EQ(getClipboardText(), "firstsecond");
}


// -----------------------------------------------------------------------------
// Round trips
// -----------------------------------------------------------------------------

TEST_F(OSClipboardTest, CopyAndPasteRoundTrip)
{
	const char* original = "Hello, clipboard! 123";

	os_clipboard::copy_to_clipboard(original);

	char buffer[128] = {};
	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, original);
}

TEST_F(OSClipboardTest, UpdateAndPasteRoundTrip)
{
	os_clipboard::copy_to_clipboard("Hello");
	os_clipboard::update_clipboard(", world!");

	char buffer[128] = {};
	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "Hello, world!");
}

TEST_F(OSClipboardTest, UpdateClipboardFollowedByPasteSanitizesText)
{
	os_clipboard::copy_to_clipboard("hello");
	os_clipboard::update_clipboard("\tworld\n");

	char buffer[128] = {};
	os_clipboard::paste_from_clipboard(buffer, sizeof(buffer));

	EXPECT_STREQ(buffer, "hello world ");
}

} // namespace
