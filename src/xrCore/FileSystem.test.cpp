#include "stdafx.h"

#include "FileSystem.h"

#include <gtest/gtest.h>

// MakeFilter is implemented in FileSystem.cpp but isn't declared in FileSystem.h.
void MakeFilter(string1024& dest, LPCSTR info, LPCSTR ext);

class EFSUtilsTest : public ::testing::Test
{
protected:
	EFS_Utils efs;
};

TEST_F(EFSUtilsTest, ExtractFileName)
{
	EXPECT_EQ(efs.ExtractFileName("textures\\wall\\brick.dds"), "brick");
	EXPECT_EQ(efs.ExtractFileName("C:\\textures\\wall\\brick.dds"), "brick");
	EXPECT_EQ(efs.ExtractFileName("brick.dds"), "brick");
	EXPECT_EQ(efs.ExtractFileName("brick"), "brick");
}

TEST_F(EFSUtilsTest, ExtractFileNameWithMultipleDots)
{
	EXPECT_EQ(efs.ExtractFileName("textures\\wall\\brick.large.dds"), "brick.large");
}

TEST_F(EFSUtilsTest, ExtractFileExt)
{
	EXPECT_EQ(efs.ExtractFileExt("textures\\wall\\brick.dds"), ".dds");
	EXPECT_EQ(efs.ExtractFileExt("C:\\textures\\wall\\brick.dds"), ".dds");
	EXPECT_EQ(efs.ExtractFileExt("brick.dds"), ".dds");
	EXPECT_EQ(efs.ExtractFileExt("brick"), "");
}

TEST_F(EFSUtilsTest, ExtractFileExtWithMultipleDots)
{
	EXPECT_EQ(efs.ExtractFileExt("textures\\wall\\brick.large.dds"), ".dds");
}

TEST_F(EFSUtilsTest, ExtractFilePath)
{
	EXPECT_EQ(
		efs.ExtractFilePath("textures\\wall\\brick.dds"),
		"textures\\wall\\"
	);

	EXPECT_EQ(
		efs.ExtractFilePath("C:\\textures\\wall\\brick.dds"),
		"C:\\textures\\wall\\"
	);

	EXPECT_EQ(
		efs.ExtractFilePath("brick.dds"),
		""
	);
}

TEST_F(EFSUtilsTest, ExtractFilePathWithDrive)
{
	EXPECT_EQ(
		efs.ExtractFilePath("D:\\game\\gamedata\\textures\\brick.dds"),
		"D:\\game\\gamedata\\textures\\"
	);
}

TEST_F(EFSUtilsTest, ExcludeBasePath)
{
	EXPECT_EQ(
		efs.ExcludeBasePath(
			"C:\\game\\gamedata\\textures\\wall.dds",
			"C:\\game\\gamedata\\"
		),
		"textures\\wall.dds"
	);
}

TEST_F(EFSUtilsTest, ExcludeBasePathWhenBaseIsAbsent)
{
	EXPECT_EQ(
		efs.ExcludeBasePath(
			"C:\\game\\textures\\wall.dds",
			"C:\\other\\"
		),
		"C:\\game\\textures\\wall.dds"
	);
}

TEST_F(EFSUtilsTest, ExcludeBasePathFindsSubstring)
{
	// This captures the current implementation's strstr() semantics.
	// It does not require excl_path to be a prefix.
	EXPECT_EQ(
		efs.ExcludeBasePath(
			"C:\\game\\gamedata\\textures\\wall.dds",
			"gamedata\\"
		),
		"textures\\wall.dds"
	);
}

TEST_F(EFSUtilsTest, ChangeFileExt)
{
	EXPECT_EQ(
		efs.ChangeFileExt("textures\\wall\\brick.dds", ".png"),
		"textures\\wall\\brick.png"
	);

	EXPECT_EQ(
		efs.ChangeFileExt("textures\\wall\\brick.dds", ".tga"),
		"textures\\wall\\brick.tga"
	);
}

TEST_F(EFSUtilsTest, ChangeFileExtWithoutExistingExtension)
{
	EXPECT_EQ(
		efs.ChangeFileExt("textures\\wall\\brick", ".dds"),
		"textures\\wall\\brick.dds"
	);
}

TEST_F(EFSUtilsTest, ChangeFileExtWithMultipleDots)
{
	EXPECT_EQ(
		efs.ChangeFileExt("textures\\wall\\brick.large.dds", ".png"),
		"textures\\wall\\brick.large.png"
	);
}

TEST_F(EFSUtilsTest, ChangeFileExtAcceptsXrString)
{
	xr_string path = "textures\\wall\\brick.dds";

	EXPECT_EQ(
		efs.ChangeFileExt(path, ".png"),
		"textures\\wall\\brick.png"
	);
}

TEST_F(EFSUtilsTest, ChangeFileExtDoesNotAddDot)
{
	EXPECT_EQ(
		efs.ChangeFileExt("brick.dds", "png"),
		"brickpng"
	);
}

TEST_F(EFSUtilsTest, AppendFolderToNameDepthZero)
{
	char result[256];

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo_bar_baz.dds",
			result,
			sizeof(result),
			0,
			FALSE
		),
		"foo_bar_baz.dds"
	);
}

TEST_F(EFSUtilsTest, AppendFolderToNameReplacesUnderscores)
{
	char result[256];

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo_bar_baz.dds",
			result,
			sizeof(result),
			1,
			FALSE
		),
		"foo\\bar_baz.dds"
	);

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo_bar_baz.dds",
			result,
			sizeof(result),
			2,
			FALSE
		),
		"foo\\bar\\baz.dds"
	);
}

TEST_F(EFSUtilsTest, AppendFolderToNameDepthGreaterThanNumberOfUnderscores)
{
	char result[256];

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo_bar.dds",
			result,
			sizeof(result),
			5,
			FALSE
		),
		"foo\\bar.dds"
	);
}

TEST_F(EFSUtilsTest, AppendFolderToNameDoesNotModifyRemainingUnderscores)
{
	char result[256];

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo_bar_baz_qux.dds",
			result,
			sizeof(result),
			2,
			FALSE
		),
		"foo\\bar\\baz_qux.dds"
	);
}

TEST_F(EFSUtilsTest, AppendFolderToNameInPlace)
{
	char name[256];
	xr_strcpy(name, sizeof(name), "foo_bar_baz.dds");

	EXPECT_STREQ(
		efs.AppendFolderToName(
			name,
			sizeof(name),
			2,
			FALSE
		),
		"foo\\bar\\baz.dds"
	);
}

#if 0
TEST_F(EFSUtilsTest, AppendFolderToNameFullName)
{
	char result[256];

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo_bar_baz.dds",
			result,
			sizeof(result),
			2,
			TRUE
		),
		"foo\\bar\\foo_bar_baz.dds"
	);
}

TEST_F(EFSUtilsTest, AppendFolderToNameFullNameWithNoFolders)
{
	char result[256];

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo.dds",
			result,
			sizeof(result),
			2,
			TRUE
		),
		"foo.dds"
	);
}

TEST_F(EFSUtilsTest, AppendFolderToNameFullNameDepthZero)
{
	char result[256];

	EXPECT_STREQ(
		efs.AppendFolderToName(
			"foo_bar.dds",
			result,
			sizeof(result),
			0,
			TRUE
		),
		""
	);
}
#endif

TEST_F(EFSUtilsTest, AppendFolderToNameReturnsDestination)
{
	char result[256];

	LPCSTR returned = efs.AppendFolderToName(
		"foo_bar.dds",
		result,
		sizeof(result),
		1,
		FALSE
	);

	EXPECT_EQ(returned, result);
}

TEST_F(EFSUtilsTest, AppendFolderToNameXrString)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 2, FALSE),
		"foo\\bar\\baz.dds"
	);
}

#if 0
TEST_F(EFSUtilsTest, AppendFolderToNameXrStringFullName)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 2, TRUE),
		"foo\\bar\\foo_bar_baz.dds"
	);
}
#endif

TEST_F(EFSUtilsTest, MakeFilterWithSingleExtension)
{
	string1024 filter;

	MakeFilter(filter, "Textures", "*.dds");

	// MakeFilter produces a Win32 OPENFILENAME double-NUL-style filter.
	EXPECT_STREQ(
		filter,
		"Textures(*.dds)\0*.dds\0\0"
	);
}

TEST_F(EFSUtilsTest, MakeFilterWithMultipleExtensions)
{
	string1024 filter;

	MakeFilter(filter, "Textures", "*.dds;*.tga");

	EXPECT_STREQ(
		filter,
		"Textures(*.dds;*.tga)\0"
		"*.dds;*.tga\0"
		"Textures(*.dds)\0*.dds\0"
		"Textures(*.tga)\0*.tga\0"
		"\0"
	);
}

TEST_F(EFSUtilsTest, MakeFilterWithNullExtension)
{
	string1024 filter;

	MakeFilter(filter, "Ignored", nullptr);

	EXPECT_STREQ(
		filter,
		"All files(*.*)\0*.*\0\0"
	);
}
