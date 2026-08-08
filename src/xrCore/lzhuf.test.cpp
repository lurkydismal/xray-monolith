#include "stdafx.h"

#include "lzhuf.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <random>
#include <string>
#include <vector>
#include <fcntl.h>

namespace
{

struct LZBuffer
{
    u8* data = nullptr;
    unsigned size = 0;

    ~LZBuffer()
    {
        if (data)
            xr_free(data);
    }

    LZBuffer() = default;

    LZBuffer(const LZBuffer&) = delete;
    LZBuffer& operator=(const LZBuffer&) = delete;
};

std::vector<u8> Decompress(const std::vector<u8>& compressed)
{
    LZBuffer output;

    _decompressLZ(
        &output.data,
        &output.size,
        const_cast<u8*>(compressed.data()),
        static_cast<unsigned>(compressed.size())
    );

    return std::vector<u8>(output.data, output.data + output.size);
}

std::vector<u8> Compress(const std::vector<u8>& input)
{
    LZBuffer output;

    _compressLZ(
        &output.data,
        &output.size,
        const_cast<u8*>(input.data()),
        static_cast<unsigned>(input.size())
    );

    std::vector<u8> result(output.data, output.data + output.size);

    // _compressLZ transfers ownership of its output to the caller.
    xr_free(output.data);
    output.data = nullptr;

    return result;
}

void ExpectRoundTrip(const std::vector<u8>& input)
{
    const auto compressed = Compress(input);
    const auto decompressed = Decompress(compressed);

    EXPECT_EQ(decompressed.size(), input.size());
    EXPECT_EQ(decompressed, input);
}

std::vector<u8> MakePatternData(size_t size)
{
    std::vector<u8> data(size);

    for (size_t i = 0; i < size; ++i)
    {
        switch (i % 32)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            data[i] = 0x00;
            break;

        case 4:
        case 5:
        case 6:
        case 7:
            data[i] = 0xff;
            break;

        default:
            data[i] = static_cast<u8>((i * 37 + 17) & 0xff);
            break;
        }
    }

    return data;
}

std::vector<u8> MakeRandomData(size_t size)
{
    std::mt19937 rng(0x12345678);

    std::vector<u8> data(size);
    std::generate(data.begin(), data.end(), [&]
    {
        return static_cast<u8>(rng() & 0xff);
    });

    return data;
}

} // namespace

TEST(LZHUF, EmptyInputRoundTrips)
{
    const std::vector<u8> input;

    ExpectRoundTrip(input);
}

TEST(LZHUF, SingleByteRoundTrips)
{
    ExpectRoundTrip({0x00});
    ExpectRoundTrip({0xff});
    ExpectRoundTrip({'A'});
}

TEST(LZHUF, SmallTextRoundTrips)
{
    const std::string text =
        "The quick brown fox jumps over the lazy dog. "
        "The quick brown fox jumps over the lazy dog.";

    const std::vector<u8> input(text.begin(), text.end());

    ExpectRoundTrip(input);
}

TEST(LZHUF, AllByteValuesRoundTrip)
{
    std::vector<u8> input;

    for (unsigned i = 0; i < 256; ++i)
        input.push_back(static_cast<u8>(i));

    ExpectRoundTrip(input);
}

TEST(LZHUF, AllByteValuesRepeatedRoundTrip)
{
    std::vector<u8> input;

    for (unsigned repetition = 0; repetition < 32; ++repetition)
    {
        for (unsigned i = 0; i < 256; ++i)
            input.push_back(static_cast<u8>(i));
    }

    ExpectRoundTrip(input);
}

TEST(LZHUF, ZeroFilledDataRoundTrips)
{
    const std::vector<u8> input(8192, 0x00);

    ExpectRoundTrip(input);
}

TEST(LZHUF, FFilledDataRoundTrips)
{
    const std::vector<u8> input(8192, 0xff);

    ExpectRoundTrip(input);
}

TEST(LZHUF, HighlyRepetitiveDataRoundTrips)
{
    std::vector<u8> input(16384);

    constexpr std::array<u8, 16> pattern =
    {
        0x00, 0x01, 0x02, 0x03,
        0x10, 0x20, 0x30, 0x40,
        0x40, 0x30, 0x20, 0x10,
        0xfe, 0xfd, 0xfc, 0xfb
    };

    for (size_t i = 0; i < input.size(); ++i)
        input[i] = pattern[i % pattern.size()];

    ExpectRoundTrip(input);
}

TEST(LZHUF, RandomDataRoundTrips)
{
    ExpectRoundTrip(MakeRandomData(1));
    ExpectRoundTrip(MakeRandomData(100));
    ExpectRoundTrip(MakeRandomData(4096));
    ExpectRoundTrip(MakeRandomData(16384));
    ExpectRoundTrip(MakeRandomData(65536));
}

TEST(LZHUF, PatternDataRoundTrips)
{
    ExpectRoundTrip(MakePatternData(100));
    ExpectRoundTrip(MakePatternData(4096));
    ExpectRoundTrip(MakePatternData(16384));
    ExpectRoundTrip(MakePatternData(65536));
}

TEST(LZHUF, SlidingWindowBoundaryRoundTrips)
{
    // N == 4096 is the LZSS sliding-window size.
    ExpectRoundTrip(MakePatternData(4095));
    ExpectRoundTrip(MakePatternData(4096));
    ExpectRoundTrip(MakePatternData(4097));

    ExpectRoundTrip(MakePatternData(8191));
    ExpectRoundTrip(MakePatternData(8192));
    ExpectRoundTrip(MakePatternData(8193));
}

TEST(LZHUF, LookaheadBoundaryRoundTrips)
{
    // F == 60 is the lookahead buffer size.
    ExpectRoundTrip(MakePatternData(59));
    ExpectRoundTrip(MakePatternData(60));
    ExpectRoundTrip(MakePatternData(61));

    ExpectRoundTrip(MakePatternData(119));
    ExpectRoundTrip(MakePatternData(120));
    ExpectRoundTrip(MakePatternData(121));
}

TEST(LZHUF, CompressionProducesFourByteHeaderForEmptyInput)
{
    const std::vector<u8> input;

    const auto compressed = Compress(input);

    ASSERT_EQ(compressed.size(), 4u);

    EXPECT_EQ(compressed[0], 0);
    EXPECT_EQ(compressed[1], 0);
    EXPECT_EQ(compressed[2], 0);
    EXPECT_EQ(compressed[3], 0);
}

TEST(LZHUF, CompressionHeaderContainsUncompressedSize)
{
    const auto input = MakePatternData(12345);
    const auto compressed = Compress(input);

    ASSERT_GE(compressed.size(), 4u);

    const u32 encoded_size =
        static_cast<u32>(compressed[0]) |
        (static_cast<u32>(compressed[1]) << 8) |
        (static_cast<u32>(compressed[2]) << 16) |
        (static_cast<u32>(compressed[3]) << 24);

    EXPECT_EQ(encoded_size, input.size());
}

TEST(LZHUF, CompressionIsDeterministic)
{
    const auto input = MakePatternData(16384);

    const auto compressed1 = Compress(input);
    const auto compressed2 = Compress(input);

    EXPECT_EQ(compressed1, compressed2);
}

TEST(LZHUF, DifferentInputsProduceDifferentStreams)
{
    const auto input1 = MakePatternData(4096);
    auto input2 = input1;

    ASSERT_FALSE(input2.empty());
    input2.back() ^= 0xff;

    const auto compressed1 = Compress(input1);
    const auto compressed2 = Compress(input2);

    EXPECT_NE(compressed1, compressed2);

    EXPECT_EQ(Decompress(compressed1), input1);
    EXPECT_EQ(Decompress(compressed2), input2);
}

TEST(LZHUF, CompressAndDecompressPreserveBinaryData)
{
    std::vector<u8> input =
    {
        0x00, 0xff, 0x00, 0xff,
        0x80, 0x7f, 0x01, 0xfe,
        0x00, 0x00, 0xff, 0xff,
        0x00, 0xff, 0x55, 0xaa
    };

    for (unsigned i = 0; i < 100; ++i)
    {
        input.push_back(static_cast<u8>(i));
        input.push_back(0);
        input.push_back(255);
    }

    ExpectRoundTrip(input);
}

TEST(LZHUF, CompressionCanBeFollowedByAnotherCompression)
{
    const auto input1 = MakePatternData(8192);
    const auto input2 = MakeRandomData(8192);

    const auto compressed1 = Compress(input1);
    const auto compressed2 = Compress(input2);

    EXPECT_EQ(Decompress(compressed1), input1);
    EXPECT_EQ(Decompress(compressed2), input2);
}

TEST(LZHUF, DecompressionCanBeFollowedByAnotherDecompression)
{
    const auto input1 = MakePatternData(8192);
    const auto input2 = MakeRandomData(8192);

    const auto compressed1 = Compress(input1);
    const auto compressed2 = Compress(input2);

    EXPECT_EQ(Decompress(compressed1), input1);
    EXPECT_EQ(Decompress(compressed2), input2);
}

TEST(LZHUF, CompressionOutputCanBeConsumedByDecompression)
{
    const auto input = MakePatternData(32768);

    LZBuffer compressed;

    _compressLZ(
        &compressed.data,
        &compressed.size,
        const_cast<u8*>(input.data()),
        static_cast<unsigned>(input.size())
    );

    ASSERT_NE(compressed.data, nullptr);
    ASSERT_GT(compressed.size, 0u);

    LZBuffer decompressed;

    _decompressLZ(
        &decompressed.data,
        &decompressed.size,
        compressed.data,
        compressed.size
    );

    ASSERT_EQ(decompressed.size, input.size());
    EXPECT_EQ(
        std::memcmp(decompressed.data, input.data(), input.size()),
        0
    );

    xr_free(decompressed.data);
    compressed.data = nullptr;
}

TEST(LZHUF, WriteAndReadRoundTrip)
{
    const auto input = MakePatternData(16384);

    char filename[L_tmpnam];
    ASSERT_NE(std::tmpnam(filename), nullptr);

    const int fd = _open(
        filename,
        _O_BINARY | _O_CREAT | _O_TRUNC | _O_RDWR,
        _S_IREAD | _S_IWRITE
    );

    ASSERT_NE(fd, -1);

    const unsigned written = _writeLZ(
        fd,
        const_cast<u8*>(input.data()),
        static_cast<unsigned>(input.size())
    );

    ASSERT_GT(written, 0u);

    ASSERT_EQ(_lseek(fd, 0, SEEK_SET), 0);

    void* decoded = nullptr;

    const unsigned decoded_size = _readLZ(
        fd,
        decoded,
        written
    );

    ASSERT_EQ(decoded_size, input.size());
    ASSERT_NE(decoded, nullptr);

    EXPECT_EQ(
        std::memcmp(decoded, input.data(), input.size()),
        0
    );

    xr_free(decoded);
    _close(fd);
    std::remove(filename);
}

TEST(LZHUF, WriteAndReadEmptyInput)
{
    const std::vector<u8> input;

    char filename[L_tmpnam];
    ASSERT_NE(std::tmpnam(filename), nullptr);

    const int fd = _open(
        filename,
        _O_BINARY | _O_CREAT | _O_TRUNC | _O_RDWR,
        _S_IREAD | _S_IWRITE
    );

    ASSERT_NE(fd, -1);

    const unsigned written = _writeLZ(
        fd,
        nullptr,
        0
    );

    EXPECT_EQ(written, 4u);

    ASSERT_EQ(_lseek(fd, 0, SEEK_SET), 0);

    void* decoded = nullptr;

    const unsigned decoded_size = _readLZ(
        fd,
        decoded,
        written
    );

    EXPECT_EQ(decoded_size, 0u);
    EXPECT_EQ(decoded, nullptr);

    _close(fd);
    std::remove(filename);
}
