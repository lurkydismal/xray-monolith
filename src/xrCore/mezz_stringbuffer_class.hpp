#pragma once

#include <memory>
#include <cstdint>
#include <sstream>
#include <vector>
#include <regex>

class MezzStringBuffer
{
public:
	MezzStringBuffer(uint32_t Size = 4096);

	char* GetBuffer() const;
	uint32_t GetSize() const;

	operator char* () const;

private:
	std::unique_ptr<char[]> StringBuffer;

	char* BufferRaw;
	uint32_t BufferSize;
};

