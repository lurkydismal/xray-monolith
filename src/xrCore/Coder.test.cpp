#include "stdafx.h"

#include "PPMd.h"
#include "Coder.hpp"

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

namespace
{

class MemoryStream
{
public:
    MemoryStream()
    {
        stream = std::tmpfile();
        EXPECT_NE(stream, nullptr);
    }

    ~MemoryStream()
    {
        if (stream)
            std::fclose(stream);
    }

    MemoryStream(const MemoryStream&) = delete;
    MemoryStream& operator=(const MemoryStream&) = delete;

    void rewind()
    {
        std::fflush(stream);
        std::fseek(stream, 0, SEEK_SET);
    }

    std::vector<std::uint8_t> readAll()
    {
        std::fflush(stream);
        std::fseek(stream, 0, SEEK_END);

        const long size = std::ftell(stream);
        EXPECT_GE(size, 0);

        std::fseek(stream, 0, SEEK_SET);

        std::vector<std::uint8_t> result(static_cast<std::size_t>(size));

        if (!result.empty())
            std::fread(result.data(), 1, result.size(), stream);

        return result;
    }

    _PPMD_FILE* ppmd()
    {
        return reinterpret_cast<_PPMD_FILE*>(stream);
    }

    FILE* stream = nullptr;
};

void setSubRange(DWORD low, DWORD high, DWORD scale)
{
    ppmd::SubRange.low = low;
    ppmd::SubRange.high = high;
    ppmd::SubRange.scale = scale;
}

} // namespace
