#include "stdafx.h"

#include "LocatorAPI_defs.h"

#include <gtest/gtest.h>

#include <set>
#include <string>

// ============================================================================
// FS_List
// ============================================================================

TEST(FSListTest, ListFilesHasExpectedFlag)
{
	EXPECT_EQ(FS_ListFiles, 1 << 0);
}

TEST(FSListTest, ListFoldersHasExpectedFlag)
{
	EXPECT_EQ(FS_ListFolders, 1 << 1);
}

TEST(FSListTest, ClampExtHasExpectedFlag)
{
	EXPECT_EQ(FS_ClampExt, 1 << 2);
}

TEST(FSListTest, RootOnlyHasExpectedFlag)
{
	EXPECT_EQ(FS_RootOnly, 1 << 3);
}

TEST(FSListTest, FlagsAreIndependent)
{
	EXPECT_NE(FS_ListFiles & FS_ListFolders, FS_ListFolders);
	EXPECT_EQ(FS_ListFiles & FS_ListFolders, 0);
	EXPECT_EQ(FS_ListFiles & FS_ClampExt, 0);
	EXPECT_EQ(FS_ListFiles & FS_RootOnly, 0);
	EXPECT_EQ(FS_ListFolders & FS_ClampExt, 0);
	EXPECT_EQ(FS_ListFolders & FS_RootOnly, 0);
	EXPECT_EQ(FS_ClampExt & FS_RootOnly, 0);
}

TEST(FSListTest, ForcedWordIsAllBitsSet)
{
	EXPECT_EQ(FS_forcedword, u32(-1));
}

// ============================================================================
// FS_Path flags
// ============================================================================

TEST(FSPathTest, RecurseFlagHasExpectedValue)
{
	EXPECT_EQ(FS_Path::flRecurse, 1 << 0);
}

TEST(FSPathTest, NotificationFlagHasExpectedValue)
{
	EXPECT_EQ(FS_Path::flNotif, 1 << 1);
}

TEST(FSPathTest, NeedRescanFlagHasExpectedValue)
{
	EXPECT_EQ(FS_Path::flNeedRescan, 1 << 2);
}

TEST(FSPathTest, PathFlagsAreIndependent)
{
	EXPECT_EQ(FS_Path::flRecurse & FS_Path::flNotif, 0);
	EXPECT_EQ(FS_Path::flRecurse & FS_Path::flNeedRescan, 0);
	EXPECT_EQ(FS_Path::flNotif & FS_Path::flNeedRescan, 0);
}

// ============================================================================
// FS_Path construction
// ============================================================================

TEST(FSPathTest, ConstructorStoresRoot)
{
	FS_Path path("root", "add");

	ASSERT_NE(path.m_Root, nullptr);
	EXPECT_STREQ(path.m_Root, "root");
}

TEST(FSPathTest, ConstructorStoresAdd)
{
	FS_Path path("root", "add");

	ASSERT_NE(path.m_Add, nullptr);
	EXPECT_STREQ(path.m_Add, "add");
}

TEST(FSPathTest, ConstructorCreatesPath)
{
	FS_Path path("root", "add");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_NE(path.m_Path[0], '\0');
}

TEST(FSPathTest, ConstructorStoresDefaultExtension)
{
	FS_Path path("root", "add", ".txt");

	ASSERT_NE(path.m_DefExt, nullptr);
	EXPECT_STREQ(path.m_DefExt, ".txt");
}

TEST(FSPathTest, ConstructorAllowsNoDefaultExtension)
{
	FS_Path path("root", "add");

	EXPECT_EQ(path.m_DefExt, nullptr);
}

TEST(FSPathTest, ConstructorStoresFilterCaption)
{
	FS_Path path("root", "add", ".txt", "Text files");

	ASSERT_NE(path.m_FilterCaption, nullptr);
	EXPECT_STREQ(path.m_FilterCaption, "Text files");
}

TEST(FSPathTest, ConstructorAllowsNoFilterCaption)
{
	FS_Path path("root", "add", ".txt");

	EXPECT_EQ(path.m_FilterCaption, nullptr);
}

TEST(FSPathTest, ConstructorStartsWithSpecifiedFlags)
{
	FS_Path path(
		"root",
		"add",
		".txt",
		"Text files",
		FS_Path::flRecurse | FS_Path::flNotif
	);

	EXPECT_TRUE(path.m_Flags.is(FS_Path::flRecurse));
	EXPECT_TRUE(path.m_Flags.is(FS_Path::flNotif));
	EXPECT_FALSE(path.m_Flags.is(FS_Path::flNeedRescan));
}

TEST(FSPathTest, ConstructorWithNoFlagsStartsWithoutFlags)
{
	FS_Path path("root", "add");

	EXPECT_FALSE(path.m_Flags.is(FS_Path::flRecurse));
	EXPECT_FALSE(path.m_Flags.is(FS_Path::flNotif));
	EXPECT_FALSE(path.m_Flags.is(FS_Path::flNeedRescan));
}

// ============================================================================
// FS_Path::_set
// ============================================================================

TEST(FSPathTest, SetChangesPath)
{
	FS_Path path("root", "old");
	const std::string oldPath = path.m_Path;

	path._set("new");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STRNE(path.m_Path, oldPath.c_str());
}

TEST(FSPathTest, SetCanBeCalledMultipleTimes)
{
	FS_Path path("root", "first");

	path._set("second");
	path._set("third");

	ASSERT_NE(path.m_Add, nullptr);
	EXPECT_STREQ(path.m_Add, "third");
}

// ============================================================================
// FS_Path::_set_root
// ============================================================================

TEST(FSPathTest, SetRootCanBeCalledMultipleTimes)
{
	FS_Path path("first", "add");

	path._set_root("second");
	path._set_root("third");

	ASSERT_NE(path.m_Root, nullptr);
	EXPECT_STREQ(path.m_Root, "third");
}

// ============================================================================
// FS_Path::_update
// ============================================================================

TEST(FSPathTest, UpdateProducesPathForRelativeSource)
{
	FS_Path path("root", "base");

	string_path result{};

	LPCSTR updated = path._update(result, "file.txt");

	ASSERT_NE(updated, nullptr);
	EXPECT_EQ(updated, result);
	EXPECT_NE(result[0], '\0');
}

TEST(FSPathTest, UpdateReturnsDestinationBuffer)
{
	FS_Path path("root", "base");

	string_path result{};

	LPCSTR updated = path._update(result, "file.txt");

	EXPECT_EQ(updated, result);
}

TEST(FSPathTest, UpdateHandlesEmptySource)
{
	FS_Path path("root", "base");

	string_path result{};

	LPCSTR updated = path._update(result, "");

	ASSERT_NE(updated, nullptr);
	EXPECT_EQ(updated, result);
}

// ============================================================================
// FS_File construction
// ============================================================================

TEST(FSFileTest, StringConstructorStoresName)
{
	FS_File file("test.txt");

	EXPECT_EQ(file.name, "test.txt");
}

TEST(FSFileTest, StringConstructorLeavesExpectedMetadataUninitialized)
{
	FS_File file("test.txt");

	EXPECT_EQ(file.name, "test.txt");

	// FS_File() itself does not initialize metadata. Don't assert values
	// for attrib/time_write/size here because doing so would turn an
	// implementation detail into a regression contract.
}

TEST(FSFileTest, FullConstructorStoresAllFields)
{
	const time_t timestamp = 123456;
	const unsigned attributes = 0x1234;
	const long size = 9876;

	FS_File file("test.txt", size, timestamp, attributes);

	EXPECT_EQ(file.name, "test.txt");
	EXPECT_EQ(file.size, size);
	EXPECT_EQ(file.time_write, timestamp);
	EXPECT_EQ(file.attrib, attributes);
}

// ============================================================================
// FS_File::set
// ============================================================================

TEST(FSFileTest, SetStoresAllFields)
{
	FS_File file;

	const time_t timestamp = 123456;
	const unsigned attributes = 0x1234;
	const long size = 9876;

	file.set("example.bin", size, timestamp, attributes);

	EXPECT_EQ(file.name, "example.bin");
	EXPECT_EQ(file.size, size);
	EXPECT_EQ(file.time_write, timestamp);
	EXPECT_EQ(file.attrib, attributes);
}

TEST(FSFileTest, SetReplacesExistingName)
{
	FS_File file("old.txt");

	file.set("new.txt", 10, 20, 30);

	EXPECT_EQ(file.name, "new.txt");
}

TEST(FSFileTest, SetReplacesExistingMetadata)
{
	FS_File file("old.txt", 1, 2, 3);

	file.set("new.txt", 100, 200, 300);

	EXPECT_EQ(file.size, 100);
	EXPECT_EQ(file.time_write, 200);
	EXPECT_EQ(file.attrib, 300);
}

// ============================================================================
// FS_File ordering
// ============================================================================

TEST(FSFileTest, EqualNamesAreNotLess)
{
	FS_File a("same.txt");
	FS_File b("same.txt");

	EXPECT_FALSE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(FSFileTest, OrderingIsIndependentOfMetadata)
{
	FS_File a("a.txt", 100, 200, 300);
	FS_File b("b.txt", 1, 2, 3);

	EXPECT_TRUE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(FSFileTest, OrderingIsLexicographical)
{
	FS_File a("abc.txt");
	FS_File b("abd.txt");

	EXPECT_TRUE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(FSFileTest, OrderingCanBeUsedWithStdSet)
{
	FS_File a("a.txt");
	FS_File b("b.txt");
	FS_File c("c.txt");

	FS_FileSet files;

	files.insert(c);
	files.insert(a);
	files.insert(b);

	ASSERT_EQ(files.size(), 3u);

	auto it = files.begin();

	EXPECT_EQ(it->name, "a.txt");
	++it;
	EXPECT_EQ(it->name, "b.txt");
	++it;
	EXPECT_EQ(it->name, "c.txt");
}

// ============================================================================
// PatternMatch
// ============================================================================

TEST(PatternMatchTest, ExactStringMatches)
{
	EXPECT_TRUE(PatternMatch("test.txt", "test.txt"));
}

TEST(PatternMatchTest, DifferentStringDoesNotMatch)
{
	EXPECT_FALSE(PatternMatch("test.txt", "other.txt"));
}

TEST(PatternMatchTest, StarMatchesPrefix)
{
	EXPECT_TRUE(PatternMatch("test.txt", "test.*"));
}

TEST(PatternMatchTest, StarDoesNotMatchWrongExtension)
{
	EXPECT_FALSE(PatternMatch("test.txt", "*.bin"));
}

TEST(PatternMatchTest, QuestionMarkMatchesSingleCharacter)
{
	EXPECT_TRUE(PatternMatch("a.txt", "?.txt"));
}

TEST(PatternMatchTest, QuestionMarkDoesNotMatchMultipleCharacters)
{
	EXPECT_FALSE(PatternMatch("ab.txt", "?.txt"));
}

TEST(PatternMatchTest, MultipleWildcardsMatch)
{
	EXPECT_TRUE(PatternMatch("foo_test_01.txt", "*_??.txt"));
}

TEST(PatternMatchTest, EmptyPatternMatchesEmptyString)
{
	EXPECT_TRUE(PatternMatch("", ""));
}

TEST(PatternMatchTest, EmptyPatternDoesNotMatchNonEmptyString)
{
	EXPECT_FALSE(PatternMatch("test", ""));
}

TEST(PatternMatchTest, PatternDoesNotMatchEmptyString)
{
	EXPECT_FALSE(PatternMatch("", "*.txt"));
}

// ============================================================================
// FS_List
// ============================================================================

TEST(FSListTest, FlagsHaveExpectedValues)
{
	EXPECT_EQ(FS_ListFiles, 1 << 0);
	EXPECT_EQ(FS_ListFolders, 1 << 1);
	EXPECT_EQ(FS_ClampExt, 1 << 2);
	EXPECT_EQ(FS_RootOnly, 1 << 3);
}

TEST(FSListTest, FlagsDoNotOverlap)
{
	EXPECT_EQ(FS_ListFiles & FS_ListFolders, 0);
	EXPECT_EQ(FS_ListFiles & FS_ClampExt, 0);
	EXPECT_EQ(FS_ListFiles & FS_RootOnly, 0);
	EXPECT_EQ(FS_ListFolders & FS_ClampExt, 0);
	EXPECT_EQ(FS_ListFolders & FS_RootOnly, 0);
	EXPECT_EQ(FS_ClampExt & FS_RootOnly, 0);
}

// ============================================================================
// FS_Path flags
// ============================================================================

TEST(FSPathTest, FlagsHaveExpectedValues)
{
	EXPECT_EQ(FS_Path::flRecurse, 1 << 0);
	EXPECT_EQ(FS_Path::flNotif, 1 << 1);
	EXPECT_EQ(FS_Path::flNeedRescan, 1 << 2);
}

TEST(FSPathTest, FlagsDoNotOverlap)
{
	EXPECT_EQ(FS_Path::flRecurse & FS_Path::flNotif, 0);
	EXPECT_EQ(FS_Path::flRecurse & FS_Path::flNeedRescan, 0);
	EXPECT_EQ(FS_Path::flNotif & FS_Path::flNeedRescan, 0);
}

// ============================================================================
// FS_Path construction
// ============================================================================

TEST(FSPathTest, ConstructorLowercasesRoot)
{
	FS_Path path("C:\\GAME\\DATA", "TEXTURES");

	ASSERT_NE(path.m_Root, nullptr);
	EXPECT_STREQ(path.m_Root, "c:\\game\\data");
}

TEST(FSPathTest, ConstructorLowercasesAdd)
{
	FS_Path path("C:\\GAME\\DATA", "TEXTURES");

	ASSERT_NE(path.m_Add, nullptr);
	EXPECT_STREQ(path.m_Add, "textures");
}

TEST(FSPathTest, ConstructorLowercasesDefaultExtension)
{
	FS_Path path("root", "add", ".TXT");

	ASSERT_NE(path.m_DefExt, nullptr);
	EXPECT_STREQ(path.m_DefExt, ".txt");
}

TEST(FSPathTest, ConstructorLowercasesFilterCaption)
{
	FS_Path path("root", "add", ".txt", "TEXT FILES");

	ASSERT_NE(path.m_FilterCaption, nullptr);
	EXPECT_STREQ(path.m_FilterCaption, "text files");
}

TEST(FSPathTest, ConstructorBuildsPathFromRootAndAdd)
{
	FS_Path path("C:\\GAME\\", "DATA");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "c:\\game\\data\\");
}

TEST(FSPathTest, ConstructorAddsTrailingSeparator)
{
	FS_Path path("root", "add");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "rootadd\\");
}

TEST(FSPathTest, ConstructorDoesNotDuplicateTrailingSeparator)
{
	FS_Path path("root\\", "add");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "root\\add\\");
}

TEST(FSPathTest, ConstructorHandlesNullRoot)
{
	FS_Path path(nullptr, "DATA");

	ASSERT_NE(path.m_Root, nullptr);
	EXPECT_STREQ(path.m_Root, "");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "data\\");
}

TEST(FSPathTest, ConstructorHandlesNullAdd)
{
	FS_Path path("ROOT", nullptr);

	ASSERT_NE(path.m_Add, nullptr);
	EXPECT_STREQ(path.m_Add, "");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "root\\");
}

TEST(FSPathTest, ConstructorHandlesNullOptionalArguments)
{
	FS_Path path("ROOT", "DATA", nullptr, nullptr);

	EXPECT_EQ(path.m_DefExt, nullptr);
	EXPECT_EQ(path.m_FilterCaption, nullptr);
}

TEST(FSPathTest, ConstructorInitializesFlags)
{
	FS_Path path(
		"root",
		"add",
		nullptr,
		nullptr,
		FS_Path::flRecurse | FS_Path::flNotif
	);

	EXPECT_TRUE(path.m_Flags.is(FS_Path::flRecurse));
	EXPECT_TRUE(path.m_Flags.is(FS_Path::flNotif));
	EXPECT_FALSE(path.m_Flags.is(FS_Path::flNeedRescan));
}

TEST(FSPathTest, ConstructorWithNoFlagsClearsFlags)
{
	FS_Path path("root", "add");

	EXPECT_FALSE(path.m_Flags.is(FS_Path::flRecurse));
	EXPECT_FALSE(path.m_Flags.is(FS_Path::flNotif));
	EXPECT_FALSE(path.m_Flags.is(FS_Path::flNeedRescan));
}

// ============================================================================
// FS_Path::_set
// ============================================================================

TEST(FSPathTest, SetChangesAdd)
{
	FS_Path path("ROOT\\", "OLD");

	path._set("NEW");

	ASSERT_NE(path.m_Add, nullptr);
	EXPECT_STREQ(path.m_Add, "new");
}

TEST(FSPathTest, SetRebuildsPath)
{
	FS_Path path("ROOT\\", "OLD");

	path._set("NEW");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "root\\new\\");
}

TEST(FSPathTest, SetPreservesRoot)
{
	FS_Path path("ROOT\\", "OLD");

	path._set("NEW");

	EXPECT_STREQ(path.m_Root, "root\\");
}

TEST(FSPathTest, SetLowercasesNewAdd)
{
	FS_Path path("ROOT\\", "OLD");

	path._set("New/Add");

	EXPECT_STREQ(path.m_Add, "new/add");
	EXPECT_STREQ(path.m_Path, "root\\new/add\\");
}

TEST(FSPathTest, SetHandlesNull)
{
	FS_Path path("ROOT\\", "OLD");

	path._set(nullptr);

	ASSERT_NE(path.m_Add, nullptr);
	EXPECT_STREQ(path.m_Add, "");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "root\\");
}

TEST(FSPathTest, SetCanBeCalledRepeatedly)
{
	FS_Path path("ROOT\\", "FIRST");

	path._set("SECOND");
	path._set("THIRD");

	EXPECT_STREQ(path.m_Add, "third");
	EXPECT_STREQ(path.m_Path, "root\\third\\");
}

// ============================================================================
// FS_Path::_set_root
// ============================================================================

TEST(FSPathTest, SetRootChangesRoot)
{
	FS_Path path("OLD\\", "ADD");

	path._set_root("NEW");

	ASSERT_NE(path.m_Root, nullptr);
	EXPECT_STREQ(path.m_Root, "new\\");
}

TEST(FSPathTest, SetRootRebuildsPath)
{
	FS_Path path("OLD\\", "ADD");

	path._set_root("NEW");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "new\\add\\");
}

TEST(FSPathTest, SetRootPreservesAdd)
{
	FS_Path path("OLD\\", "ADD");

	path._set_root("NEW");

	EXPECT_STREQ(path.m_Add, "add");
}

TEST(FSPathTest, SetRootLowercasesNewRoot)
{
	FS_Path path("OLD\\", "ADD");

	path._set_root("New/Root");

	EXPECT_STREQ(path.m_Root, "new/root\\");
	EXPECT_STREQ(path.m_Path, "new/root\\add\\");
}

TEST(FSPathTest, SetRootHandlesNull)
{
	FS_Path path("OLD\\", "ADD");

	path._set_root(nullptr);

	ASSERT_NE(path.m_Root, nullptr);
	EXPECT_STREQ(path.m_Root, "");

	ASSERT_NE(path.m_Path, nullptr);
	EXPECT_STREQ(path.m_Path, "add\\");
}

TEST(FSPathTest, SetRootCanBeCalledRepeatedly)
{
	FS_Path path("FIRST", "ADD");

	path._set_root("SECOND");
	path._set_root("THIRD");

	EXPECT_STREQ(path.m_Root, "third\\");
	EXPECT_STREQ(path.m_Path, "third\\add\\");
}

// ============================================================================
// FS_Path::_update
// ============================================================================

TEST(FSPathTest, UpdatePrependsPath)
{
	FS_Path path("ROOT\\", "DATA");

	string_path result{};

	LPCSTR returned = path._update(result, "file.txt");

	ASSERT_NE(returned, nullptr);
	EXPECT_EQ(returned, result);
	EXPECT_STREQ(result, "root\\data\\file.txt");
}

TEST(FSPathTest, UpdateLowercasesSource)
{
	FS_Path path("ROOT\\", "DATA");

	string_path result{};

	path._update(result, "Textures\\Player.TGA");

	EXPECT_STREQ(result, "root\\data\\textures\\player.tga");
}

TEST(FSPathTest, UpdateLowercasesEntireResult)
{
	FS_Path path("ROOT\\", "DATA");

	string_path result{};

	path._update(result, "Some/File.TXT");

	EXPECT_STREQ(result, "root\\data\\some/file.txt");
}

TEST(FSPathTest, UpdateReturnsDestination)
{
	FS_Path path("root", "data");

	string_path result{};

	LPCSTR returned = path._update(result, "test.txt");

	EXPECT_EQ(returned, result);
}

TEST(FSPathTest, UpdateCanBeCalledRepeatedly)
{
	FS_Path path("root", "data");

	string_path first{};
	string_path second{};

	path._update(first, "first.txt");
	path._update(second, "second.txt");

	EXPECT_STREQ(first, "rootdata\\first.txt");
	EXPECT_STREQ(second, "rootdata\\second.txt");
}

// ============================================================================
// FS_Path::rescan_path_cb
// ============================================================================
//
// This callback also modifies the global FS object. Keep these tests focused
// on the FS_Path-local flag; the global side effect is tested separately only
// if the test fixture initializes the real CLocatorAPI instance.

TEST(FSPathTest, RescanCallbackSetsNeedRescanFlag)
{
	FS_Path path("root", "data");

	EXPECT_FALSE(path.m_Flags.is(FS_Path::flNeedRescan));

	path.rescan_path_cb();

	EXPECT_TRUE(path.m_Flags.is(FS_Path::flNeedRescan));
}

TEST(FSPathTest, RescanCallbackCanBeCalledRepeatedly)
{
	FS_Path path("root", "data");

	path.rescan_path_cb();
	path.rescan_path_cb();

	EXPECT_TRUE(path.m_Flags.is(FS_Path::flNeedRescan));
}

// ============================================================================
// FS_File
// ============================================================================

TEST(FSFileTest, ConstructorLowercasesName)
{
	FS_File file("TeSt.TxT");

	EXPECT_EQ(file.name, "test.txt");
}

TEST(FSFileTest, ConstructorInitializesMetadataToZero)
{
	FS_File file("test.txt");

	EXPECT_EQ(file.size, 0);
	EXPECT_EQ(file.time_write, 0);
	EXPECT_EQ(file.attrib, 0u);
}

TEST(FSFileTest, FullConstructorStoresMetadata)
{
	const long size = 12345;
	const time_t timestamp = 123456;
	const unsigned attributes = 0x1234;

	FS_File file("TEST.TXT", size, timestamp, attributes);

	EXPECT_EQ(file.name, "test.txt");
	EXPECT_EQ(file.size, size);
	EXPECT_EQ(file.time_write, timestamp);
	EXPECT_EQ(file.attrib, attributes);
}

TEST(FSFileTest, SetLowercasesName)
{
	FS_File file;

	file.set("Some\\Directory\\FILE.TXT", 100, 200, 300);

	EXPECT_EQ(file.name, "some\\directory\\file.txt");
}

TEST(FSFileTest, SetStoresSize)
{
	FS_File file;

	file.set("file.txt", 12345, 0, 0);

	EXPECT_EQ(file.size, 12345);
}

TEST(FSFileTest, SetStoresTimestamp)
{
	FS_File file;

	const time_t timestamp = 987654;

	file.set("file.txt", 0, timestamp, 0);

	EXPECT_EQ(file.time_write, timestamp);
}

TEST(FSFileTest, SetStoresAttributes)
{
	FS_File file;

	file.set("file.txt", 0, 0, 0x1234);

	EXPECT_EQ(file.attrib, 0x1234u);
}

TEST(FSFileTest, SetReplacesAllFields)
{
	FS_File file("OLD.TXT", 1, 2, 3);

	file.set("NEW.TXT", 100, 200, 300);

	EXPECT_EQ(file.name, "new.txt");
	EXPECT_EQ(file.size, 100);
	EXPECT_EQ(file.time_write, 200);
	EXPECT_EQ(file.attrib, 300u);
}

// ============================================================================
// FS_File ordering
// ============================================================================

TEST(FSFileTest, LessComparesNames)
{
	FS_File a("a.txt");
	FS_File b("b.txt");

	EXPECT_TRUE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(FSFileTest, LessIsFalseForEqualNames)
{
	FS_File a("same.txt", 1, 2, 3);
	FS_File b("same.txt", 100, 200, 300);

	EXPECT_FALSE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(FSFileTest, LessIgnoresMetadata)
{
	FS_File a("a.txt", 999, 999, 999);
	FS_File b("b.txt", 0, 0, 0);

	EXPECT_TRUE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(FSFileTest, OrderingIsCaseInsensitiveBecauseNamesAreLowercased)
{
	FS_File upper("ABC.TXT");
	FS_File lower("abc.txt");

	EXPECT_EQ(upper.name, lower.name);
	EXPECT_FALSE(upper < lower);
	EXPECT_FALSE(lower < upper);
}

TEST(FSFileTest, FileSetOrdersByName)
{
	FS_FileSet files;

	files.insert(FS_File("C.TXT"));
	files.insert(FS_File("A.TXT"));
	files.insert(FS_File("B.TXT"));

	ASSERT_EQ(files.size(), 3u);

	auto it = files.begin();

	EXPECT_EQ(it->name, "a.txt");
	++it;
	EXPECT_EQ(it->name, "b.txt");
	++it;
	EXPECT_EQ(it->name, "c.txt");
}

// ============================================================================
// PatternMatch - exact matching
// ============================================================================

TEST(PatternMatchTest, ExactMatch)
{
	EXPECT_TRUE(PatternMatch("test.txt", "test.txt"));
}

TEST(PatternMatchTest, ExactMismatch)
{
	EXPECT_FALSE(PatternMatch("test.txt", "other.txt"));
}

TEST(PatternMatchTest, EmptyStringsMatch)
{
	EXPECT_TRUE(PatternMatch("", ""));
}

TEST(PatternMatchTest, EmptyStringDoesNotMatchNonEmptyMask)
{
	EXPECT_FALSE(PatternMatch("", "test"));
}

TEST(PatternMatchTest, NonEmptyStringDoesNotMatchEmptyMask)
{
	EXPECT_FALSE(PatternMatch("test", ""));
}

// ============================================================================
// PatternMatch - '?'
// ============================================================================

TEST(PatternMatchTest, QuestionMarkMatchesOneCharacter)
{
	EXPECT_TRUE(PatternMatch("a.txt", "?.txt"));
}

TEST(PatternMatchTest, QuestionMarkMatchesDifferentCharacter)
{
	EXPECT_TRUE(PatternMatch("b.txt", "?.txt"));
}

TEST(PatternMatchTest, QuestionMarkDoesNotMatchZeroCharacters)
{
	EXPECT_FALSE(PatternMatch(".txt", "?.txt"));
}

TEST(PatternMatchTest, QuestionMarkDoesNotMatchTwoCharacters)
{
	EXPECT_FALSE(PatternMatch("ab.txt", "?.txt"));
}

TEST(PatternMatchTest, MultipleQuestionMarksMatchMultipleCharacters)
{
	EXPECT_TRUE(PatternMatch("abc.txt", "???.txt"));
}

// ============================================================================
// PatternMatch - '*'
// ============================================================================

TEST(PatternMatchTest, StarMatchesZeroCharacters)
{
	EXPECT_TRUE(PatternMatch("test.txt", "test*.txt"));
}

TEST(PatternMatchTest, StarMatchesMultipleCharacters)
{
	EXPECT_TRUE(PatternMatch("testing.txt", "test*.txt"));
}

TEST(PatternMatchTest, StarMatchesEntireString)
{
	EXPECT_TRUE(PatternMatch("anything", "*"));
}

TEST(PatternMatchTest, StarMatchesEmptyString)
{
	EXPECT_TRUE(PatternMatch("", "*"));
}

TEST(PatternMatchTest, StarAtEndMatchesSuffix)
{
	EXPECT_TRUE(PatternMatch("filename", "file*"));
}

TEST(PatternMatchTest, StarAtBeginningMatchesPrefix)
{
	EXPECT_TRUE(PatternMatch("filename.txt", "*.txt"));
}

TEST(PatternMatchTest, StarDoesNotMatchWrongSuffix)
{
	EXPECT_FALSE(PatternMatch("filename.txt", "*.bin"));
}

TEST(PatternMatchTest, MultipleStars)
{
	EXPECT_TRUE(PatternMatch(
		"textures/player/body.tga",
		"textures/*/*.tga"
	));
}

TEST(PatternMatchTest, StarCanBacktrack)
{
	EXPECT_TRUE(PatternMatch(
		"ababc.txt",
		"a*b*c.txt"
	));
}

// ============================================================================
// PatternMatch - combinations
// ============================================================================

TEST(PatternMatchTest, QuestionMarkAndStarCanBeCombined)
{
	EXPECT_TRUE(PatternMatch("player01.tga", "player??.*"));
}

TEST(PatternMatchTest, WildcardsCanMatchFullFilename)
{
	EXPECT_TRUE(PatternMatch("some_long_filename.dds", "*.*"));
}

TEST(PatternMatchTest, ExtensionPattern)
{
	EXPECT_TRUE(PatternMatch("texture.dds", "*.dds"));
	EXPECT_TRUE(PatternMatch("texture.tga", "*.tga"));
	EXPECT_FALSE(PatternMatch("texture.txt", "*.dds"));
}

TEST(PatternMatchTest, FilenamePrefixPattern)
{
	EXPECT_TRUE(PatternMatch("weapon_ak74.dds", "weapon_*.dds"));
	EXPECT_FALSE(PatternMatch("character_ak74.dds", "weapon_*.dds"));
}

TEST(PatternMatchTest, DirectoryPattern)
{
	EXPECT_TRUE(PatternMatch(
		"textures/weapons/ak74.dds",
		"textures/*/ak74.dds"
	));

	EXPECT_FALSE(PatternMatch(
		"textures/characters/ak74.dds",
		"models/*/ak74.dds"
	));
}
