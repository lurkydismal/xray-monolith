#pragma once

namespace hash_fixed_vertex_manager
{
	IC u32 to_u32(shared_str const& string)
	{
		const str_value* get = string._get();
		return (*(u32 const*)&get);
	}
} // namespace hash_fixed_vertex_manager
