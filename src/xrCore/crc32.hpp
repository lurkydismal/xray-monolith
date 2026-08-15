#pragma once

#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

// Public API (unchanged behavior/signatures from the original file)
u32 crc32( const void* P, u32 len );
u32 crc32( const void* P, u32 len, u32 starting_crc );
u32 path_crc32( const char* path, u32 len );

// Internals exposed ONLY so tests can exercise each code path directly,
// independent of whatever CPU::ID.feature resolves to at runtime.
namespace crc32_internal {
// Raw accumulator functions: caller supplies the initial CRC register
// value directly (no implicit ~0 init / final XOR-out). This mirrors
// exactly what the original inline loops did, just given names.
u32 crc32_sse42( const void* P, u32 len, u32 starting_crc ) noexcept;
u32 crc32_table_based( const void* P, u32 len, u32 starting_crc ) noexcept;
} // namespace crc32_internal
