// TODO: Implement
#if 0
#include "stdafx.h"

#include "file_stream_reader.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <string>

namespace
{
class FileStreamReaderTest : public ::testing::Test
{
protected:
    std::string m_file_name;

    void SetUp() override
    {
        char path[MAX_PATH];
        GetTempPathA(sizeof(path), path);

        char file_name[MAX_PATH];
        GetTempFileNameA(path, "xray", 0, file_name);

        m_file_name = file_name;
    }

    void TearDown() override
    {
        DeleteFileA(m_file_name.c_str());
    }

    void write_file(const void* data, size_t size)
    {
        std::ofstream file(m_file_name, std::ios::binary | std::ios::trunc);
        ASSERT_TRUE(file.is_open());

        file.write(
            static_cast<const char*>(data),
            static_cast<std::streamsize>(size)
        );

        ASSERT_TRUE(file.good());
    }
};

} // namespace

// -----------------------------------------------------------------------------
// Lifecycle
// -----------------------------------------------------------------------------

TEST_F(FileStreamReaderTest, ConstructAndDestroy)
{
    static constexpr char data[] = "XRay file stream reader";

    write_file(data, sizeof(data) - 1);

    CFileStreamReader reader;

    reader.construct(m_file_name.c_str(), 4096);
    reader.destroy();
}

TEST_F(FileStreamReaderTest, ConstructAndDestroyEmptyFile)
{
    write_file(nullptr, 0);

    CFileStreamReader reader;

    reader.construct(m_file_name.c_str(), 4096);
    reader.destroy();
}

// -----------------------------------------------------------------------------
// Different window sizes
// -----------------------------------------------------------------------------

TEST_F(FileStreamReaderTest, ConstructWithSmallWindow)
{
    static constexpr char data[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";

    write_file(data, sizeof(data) - 1);

    CFileStreamReader reader;

    reader.construct(m_file_name.c_str(), 1);
    reader.destroy();
}

TEST_F(FileStreamReaderTest, ConstructWithExactFileSizeWindow)
{
    static constexpr char data[] = "0123456789";

    write_file(data, sizeof(data) - 1);

    CFileStreamReader reader;

    reader.construct(
        m_file_name.c_str(),
        static_cast<u32>(sizeof(data) - 1)
    );

    reader.destroy();
}

TEST_F(FileStreamReaderTest, ConstructWithLargerWindowThanFile)
{
    static constexpr char data[] = "small file";

    write_file(data, sizeof(data) - 1);

    CFileStreamReader reader;

    reader.construct(m_file_name.c_str(), 1024);
    reader.destroy();
}
#endif
