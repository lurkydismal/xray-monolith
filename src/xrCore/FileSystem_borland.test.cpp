#include "stdafx.h"

#include "FileSystem.h"

#include <gtest/gtest.h>

class EFSUtilsBorlandTest : public ::testing::Test
{
protected:
	EFS_Utils efs;
};

// -----------------------------------------------------------------------------
// AppendFolderToName(xr_string&, int, BOOL)
// -----------------------------------------------------------------------------

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringDepthZero)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 0, FALSE),
		"foo_bar_baz.dds"
	);

	EXPECT_EQ(name, "foo_bar_baz.dds");
}

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringOneLevel)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 1, FALSE),
		"foo\\bar_baz.dds"
	);

	EXPECT_EQ(name, "foo\\bar_baz.dds");
}

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringTwoLevels)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 2, FALSE),
		"foo\\bar\\baz.dds"
	);

	EXPECT_EQ(name, "foo\\bar\\baz.dds");
}

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringMoreDepthThanFolders)
{
	xr_string name = "foo_bar.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 10, FALSE),
		"foo\\bar.dds"
	);

	EXPECT_EQ(name, "foo\\bar.dds");
}

#if 0
TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringFullName)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 2, TRUE),
		"foo\\bar\\foo_bar_baz.dds"
	);

	EXPECT_EQ(name, "foo\\bar\\foo_bar_baz.dds");
}
#endif

#if 0
TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringFullNameOneLevel)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 1, TRUE),
		"foo\\foo_bar_baz.dds"
	);

	EXPECT_EQ(name, "foo\\foo_bar_baz.dds");
}
#endif

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringFullNameWithNoFolders)
{
	xr_string name = "foo.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 2, TRUE),
		"foo.dds"
	);

	EXPECT_EQ(name, "foo.dds");
}

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringFullNameDepthZero)
{
	xr_string name = "foo_bar_baz.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 0, TRUE),
		""
	);

	EXPECT_EQ(name, "");
}

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringPreservesExtension)
{
	xr_string name = "textures_wall_brick.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 2, FALSE),
		"textures\\wall\\brick.dds"
	);
}

TEST_F(EFSUtilsBorlandTest, AppendFolderToNameXrStringPreservesCharactersAfterDepth)
{
	xr_string name = "one_two_three_four.dds";

	EXPECT_EQ(
		efs.AppendFolderToName(name, 2, FALSE),
		"one\\two\\three_four.dds"
	);
}
