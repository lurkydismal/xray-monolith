#include "stdafx.h"

#include "FS_internal.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

namespace
{
    class FsInternalTest : public ::testing::Test
    {
    protected:
        std::filesystem::path test_dir;

        void SetUp() override
        {
            test_dir =
                std::filesystem::temp_directory_path() /
                ("xray_fs_test_" + std::to_string(
                    static_cast<unsigned long long>(
                        std::hash<std::string>{}(
                            std::to_string(
                                reinterpret_cast<uintptr_t>(this))))));

            std::filesystem::create_directories(test_dir);
        }

        void TearDown() override
        {
            std::error_code ec;
            std::filesystem::remove_all(test_dir, ec);
        }

        std::string Path(const char* name) const
        {
            return (test_dir / name).string();
        }

        static std::vector<u8> ReadFile(const std::string& path)
        {
            FILE* file = std::fopen(path.c_str(), "rb");
            EXPECT_NE(file, nullptr);

            if (!file)
                return {};

            EXPECT_EQ(std::fseek(file, 0, SEEK_END), 0);

            const long size = std::ftell(file);
            EXPECT_GE(size, 0);

            EXPECT_EQ(std::fseek(file, 0, SEEK_SET), 0);

            std::vector<u8> result(static_cast<size_t>(size));

            if (!result.empty())
            {
                EXPECT_EQ(
                    std::fread(
                        result.data(),
                        1,
                        result.size(),
                        file),
                    result.size());
            }

            std::fclose(file);

            return result;
        }
    };
}

// ============================================================================
// CFileWriter
// ============================================================================

TEST_F(FsInternalTest, CFileWriterCreatesFile)
{
    const std::string path = Path("test.bin");

    {
        CFileWriter writer(path.c_str(), false);

        ASSERT_TRUE(writer.valid());
        EXPECT_EQ(writer.tell(), 0u);
    }

    EXPECT_TRUE(std::filesystem::exists(path));
}

TEST_F(FsInternalTest, CFileWriterWritesData)
{
    const std::string path = Path("test.bin");

    const std::array<u8, 8> expected = {
        0x00,
        0x11,
        0x22,
        0x33,
        0x44,
        0x55,
        0x66,
        0xFF
    };

    {
        CFileWriter writer(path.c_str(), false);

        ASSERT_TRUE(writer.valid());

        writer.w(
            expected.data(),
            static_cast<u32>(expected.size()));

        EXPECT_EQ(writer.tell(), expected.size());
    }

    const std::vector<u8> actual = ReadFile(path);

    EXPECT_EQ(actual, std::vector<u8>(
        expected.begin(),
        expected.end()));
}

TEST_F(FsInternalTest, CFileWriterWritesPrimitiveValues)
{
    const std::string path = Path("values.bin");

    {
        CFileWriter writer(path.c_str(), false);

        ASSERT_TRUE(writer.valid());

        writer.w_u32(0x11223344);
        writer.w_u16(0x5566);
        writer.w_u8(0x77);
        writer.w_s32(-123456);
        writer.w_float(123.5f);

        writer.flush();
    }

    CFileReader reader(path.c_str());

    EXPECT_EQ(reader.r_u32(), 0x11223344u);
    EXPECT_EQ(reader.r_u16(), 0x5566u);
    EXPECT_EQ(reader.r_u8(), 0x77u);
    EXPECT_EQ(reader.r_s32(), -123456);
    EXPECT_FLOAT_EQ(reader.r_float(), 123.5f);
    EXPECT_TRUE(reader.eof());
}

TEST_F(FsInternalTest, CFileWriterSupportsSeek)
{
    const std::string path = Path("seek.bin");

    {
        CFileWriter writer(path.c_str(), false);

        ASSERT_TRUE(writer.valid());

        writer.w_u32(0x11111111);
        writer.w_u32(0x22222222);

        EXPECT_EQ(writer.tell(), 8u);

        writer.seek(0);

        EXPECT_EQ(writer.tell(), 0u);

        writer.w_u32(0xAAAAAAAA);

        writer.flush();
    }

    CFileReader reader(path.c_str());

    EXPECT_EQ(reader.r_u32(), 0xAAAAAAAAu);
    EXPECT_EQ(reader.r_u32(), 0x22222222u);
}

TEST_F(FsInternalTest, CFileWriterTruncatesExistingFile)
{
    const std::string path = Path("truncate.bin");

    {
        CFileWriter writer(path.c_str(), false);

        writer.w_u32(0x11111111);
        writer.w_u32(0x22222222);
    }

    {
        CFileWriter writer(path.c_str(), false);

        writer.w_u32(0xAAAAAAAA);
    }

    CFileReader reader(path.c_str());

    EXPECT_EQ(reader.length(), static_cast<int>(sizeof(u32)));
    EXPECT_EQ(reader.r_u32(), 0xAAAAAAAAu);
}

TEST_F(FsInternalTest, CFileWriterWritesEmptyBufferWithoutChangingPosition)
{
    const std::string path = Path("empty.bin");

    {
        CFileWriter writer(path.c_str(), false);

        ASSERT_TRUE(writer.valid());

        writer.w(nullptr, 0);

        EXPECT_EQ(writer.tell(), 0u);
    }

    EXPECT_TRUE(std::filesystem::exists(path));
    EXPECT_EQ(std::filesystem::file_size(path), 0u);
}

TEST_F(FsInternalTest, CFileWriterCreatesParentDirectories)
{
    const std::string path =
        (test_dir / "one" / "two" / "three.bin").string();

    {
        CFileWriter writer(path.c_str(), false);

        ASSERT_TRUE(writer.valid());

        writer.w_u32(0x12345678);
    }

    ASSERT_TRUE(std::filesystem::exists(path));

    CFileReader reader(path.c_str());

    EXPECT_EQ(reader.r_u32(), 0x12345678u);
}

TEST_F(FsInternalTest, CFileWriterFNameContainsPath)
{
    const std::string path = Path("name.bin");

    CFileWriter writer(path.c_str(), false);

    EXPECT_EQ(writer.fName, path.c_str());
}

TEST_F(FsInternalTest, CFileWriterFlushMakesDataVisible)
{
    const std::string path = Path("flush.bin");

    CFileWriter writer(path.c_str(), false);

    writer.w_u32(0x12345678);
    writer.flush();

    EXPECT_EQ(std::filesystem::file_size(path), sizeof(u32));
}

// ============================================================================
// CFileReader
// ============================================================================

TEST_F(FsInternalTest, CFileReaderReadsFile)
{
    const std::string path = Path("reader.bin");

    {
        CFileWriter writer(path.c_str(), false);

        writer.w_u32(0x11223344);
        writer.w_u32(0x55667788);
    }

    CFileReader reader(path.c_str());

    EXPECT_EQ(reader.length(), 8);
    EXPECT_EQ(reader.tell(), 0);

    EXPECT_EQ(reader.r_u32(), 0x11223344u);
    EXPECT_EQ(reader.r_u32(), 0x55667788u);

    EXPECT_TRUE(reader.eof());
}

TEST_F(FsInternalTest, CFileReaderSupportsSeek)
{
    const std::string path = Path("reader_seek.bin");

    {
        CFileWriter writer(path.c_str(), false);

        writer.w_u32(1);
        writer.w_u32(2);
        writer.w_u32(3);
    }

    CFileReader reader(path.c_str());

    reader.seek(sizeof(u32));

    EXPECT_EQ(reader.r_u32(), 2u);

    reader.seek(0);

    EXPECT_EQ(reader.r_u32(), 1u);

    reader.seek(2 * sizeof(u32));

    EXPECT_EQ(reader.r_u32(), 3u);
}

TEST_F(FsInternalTest, CFileReaderReadsStrings)
{
    const std::string path = Path("strings.bin");

    {
        CFileWriter writer(path.c_str(), false);

        writer.w_stringZ("hello");
        writer.w_stringZ("world");
    }

    CFileReader reader(path.c_str());

    xr_string first;
    xr_string second;

    reader.r_stringZ(first);
    reader.r_stringZ(second);

    EXPECT_EQ(first, "hello");
    EXPECT_EQ(second, "world");
}

TEST_F(FsInternalTest, CFileReaderReadsChunks)
{
    const std::string path = Path("chunks.bin");

    const u32 first = 0x11111111;
    const u32 second = 0x22222222;

    {
        CFileWriter writer(path.c_str(), false);

        writer.w_chunk(
            100,
            const_cast<u32*>(&first),
            sizeof(first));

        writer.w_chunk(
            200,
            const_cast<u32*>(&second),
            sizeof(second));
    }

    CFileReader reader(path.c_str());

    EXPECT_EQ(reader.find_chunk(100), sizeof(first));
    EXPECT_EQ(reader.r_u32(), first);

    reader.rewind();

    IReader* chunk = reader.open_chunk(200);

    ASSERT_NE(chunk, nullptr);

    EXPECT_EQ(chunk->r_u32(), second);

    chunk->close();
}

// ============================================================================
// FileDownload
// ============================================================================

TEST_F(FsInternalTest, FileDownloadReadsEntireFile)
{
    const std::string path = Path("download.bin");

    const std::array<u8, 16> expected = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B,
        0x0C, 0x0D, 0x0E, 0x0F
    };

    {
        CFileWriter writer(path.c_str(), false);

        writer.w(
            expected.data(),
            static_cast<u32>(expected.size()));
    }

    u32 size = 0;

    void* data = FileDownload(path.c_str(), &size);

    ASSERT_NE(data, nullptr);
    EXPECT_EQ(size, expected.size());

    EXPECT_EQ(
        std::memcmp(
            data,
            expected.data(),
            expected.size()),
        0);

    Memory.mem_free(data);
}

TEST_F(FsInternalTest, FileDownloadSupportsEmptyFile)
{
    const std::string path = Path("empty_download.bin");

    {
        CFileWriter writer(path.c_str(), false);
    }

    u32 size = 0;

    void* data = FileDownload(path.c_str(), &size);

    EXPECT_EQ(size, 0u);

    // Current implementation allocates even for zero-sized files.
    // The important contract here is that the reported size is zero.
    Memory.mem_free(data);
}

// ============================================================================
// FileCompress / FileDecompress
// ============================================================================

TEST_F(FsInternalTest, FileCompressAndDecompressRoundTrip)
{
    const std::string path = Path("compressed.bin");

    std::vector<u8> source;

    for (int i = 0; i < 8192; ++i)
        source.push_back(static_cast<u8>(i % 32));

    FileCompress(
        path.c_str(),
        "TEST",
        source.data(),
        static_cast<u32>(source.size()));

    u32 decompressed_size = 0;

    void* result = FileDecompress(
        path.c_str(),
        "TEST",
        &decompressed_size);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(decompressed_size, source.size());

    EXPECT_EQ(
        std::memcmp(
            result,
            source.data(),
            source.size()),
        0);

    Memory.mem_free(result);
}

TEST_F(FsInternalTest, FileCompressWritesEightByteSignature)
{
    const std::string path = Path("signature.bin");

    const std::array<u8, 4> source = {
        1, 2, 3, 4
    };

    FileCompress(
        path.c_str(),
        "TEST",
        const_cast<u8*>(source.data()),
        static_cast<u32>(source.size()));

    const std::vector<u8> file = ReadFile(path);

    ASSERT_GE(file.size(), 8u);

    EXPECT_EQ(file[0], 'T');
    EXPECT_EQ(file[1], 'E');
    EXPECT_EQ(file[2], 'S');
    EXPECT_EQ(file[3], 'T');
}

TEST_F(FsInternalTest, FileCompressSignatureIsLimitedToEightCharacters)
{
    const std::string path = Path("long_signature.bin");

    const std::array<u8, 4> source = {
        1, 2, 3, 4
    };

    FileCompress(
        path.c_str(),
        "123456789ABCDEF",
        const_cast<u8*>(source.data()),
        static_cast<u32>(source.size()));

    u32 size = 0;

    void* result = FileDecompress(
        path.c_str(),
        "12345678",
        &size);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(size, source.size());

    EXPECT_EQ(
        std::memcmp(result, source.data(), source.size()),
        0);

    Memory.mem_free(result);
}

TEST_F(FsInternalTest, FileDecompressCanOmitSize)
{
    const std::string path = Path("no_size.bin");

    const std::array<u8, 8> source = {
        1, 2, 3, 4, 5, 6, 7, 8
    };

    FileCompress(
        path.c_str(),
        "TEST",
        const_cast<u8*>(source.data()),
        static_cast<u32>(source.size()));

    void* result = FileDecompress(
        path.c_str(),
        "TEST");

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(
        std::memcmp(result, source.data(), source.size()),
        0);

    Memory.mem_free(result);
}

// ============================================================================
// CCompressedReader
// ============================================================================

TEST_F(FsInternalTest, CCompressedReaderReadsCompressedFile)
{
    const std::string path = Path("compressed_reader.bin");

    const std::array<u32, 4> source = {
        0x11111111,
        0x22222222,
        0x33333333,
        0x44444444
    };

    FileCompress(
        path.c_str(),
        "TEST",
        const_cast<u32*>(source.data()),
        sizeof(source));

    CCompressedReader reader(
        path.c_str(),
        "TEST");

    ASSERT_EQ(reader.length(), static_cast<int>(sizeof(source)));

    EXPECT_EQ(reader.r_u32(), source[0]);
    EXPECT_EQ(reader.r_u32(), source[1]);
    EXPECT_EQ(reader.r_u32(), source[2]);
    EXPECT_EQ(reader.r_u32(), source[3]);

    EXPECT_TRUE(reader.eof());
}

// ============================================================================
// CTempReader
// ============================================================================

TEST_F(FsInternalTest, CTempReaderOwnsAndReadsSuppliedMemory)
{
    constexpr char text[] = "temporary reader";

    char* data = static_cast<char*>(
        Memory.mem_alloc(sizeof(text)));

    std::memcpy(data, text, sizeof(text));

    {
        CTempReader reader(
            data,
            static_cast<int>(sizeof(text)),
            0);

        char result[sizeof(text)] = {};

        reader.r(
            result,
            static_cast<int>(sizeof(result)));

        EXPECT_STREQ(result, text);
    }

    // CTempReader destructor owns the supplied allocation.
}

// ============================================================================
// CVirtualFileReader
// ============================================================================

TEST_F(FsInternalTest, CVirtualFileReaderReadsFile)
{
    const std::string path = Path("mapped.bin");

    const std::array<u32, 3> source = {
        0x11111111,
        0x22222222,
        0x33333333
    };

    {
        CFileWriter writer(path.c_str(), false);

        writer.w(
            source.data(),
            sizeof(source));
    }

    CVirtualFileReader reader(path.c_str());

    EXPECT_EQ(reader.length(), static_cast<int>(sizeof(source)));

    EXPECT_EQ(reader.r_u32(), source[0]);
    EXPECT_EQ(reader.r_u32(), source[1]);
    EXPECT_EQ(reader.r_u32(), source[2]);

    EXPECT_TRUE(reader.eof());
}

TEST_F(FsInternalTest, CVirtualFileReaderSupportsSeek)
{
    const std::string path = Path("mapped_seek.bin");

    const std::array<u32, 3> source = {
        10,
        20,
        30
    };

    {
        CFileWriter writer(path.c_str(), false);

        writer.w(
            source.data(),
            sizeof(source));
    }

    CVirtualFileReader reader(path.c_str());

    reader.seek(sizeof(u32));

    EXPECT_EQ(reader.r_u32(), 20u);

    reader.seek(0);

    EXPECT_EQ(reader.r_u32(), 10u);
}

// ============================================================================
// FileWriter -> FileReader compatibility
// ============================================================================

TEST_F(FsInternalTest, FileWriterAndFileReaderRoundTrip)
{
    const std::string path = Path("roundtrip.bin");

    const u64 u64_value = 0x1122334455667788ull;
    const s32 s32_value = -123456;
    const float float_value = 42.25f;
    const char* string_value = "X-Ray Engine";

    {
        CFileWriter writer(path.c_str(), false);

        writer.w_u64(u64_value);
        writer.w_s32(s32_value);
        writer.w_float(float_value);
        writer.w_stringZ(string_value);
    }

    CFileReader reader(path.c_str());

    EXPECT_EQ(reader.r_u64(), u64_value);
    EXPECT_EQ(reader.r_s32(), s32_value);
    EXPECT_FLOAT_EQ(reader.r_float(), float_value);

    char string_result[64] = {};
    reader.r_stringZ(
        string_result,
        sizeof(string_result));

    EXPECT_STREQ(string_result, string_value);
    EXPECT_TRUE(reader.eof());
}
