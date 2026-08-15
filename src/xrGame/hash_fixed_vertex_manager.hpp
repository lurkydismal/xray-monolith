#pragma once

#include "graph_engine_space.h"

#ifndef AI_COMPILER
#	include "operator_condition.h"
#	include "condition_state.h"
#	include "operator_abstract.h"
#endif // AI_COMPILER

namespace hash_fixed_vertex_manager
{
	IC u32 to_u32(GraphEngineSpace::CWorldState const& other)
	{
		return (other.hash_value());
	}

	IC u32 to_u32(shared_str const& string)
	{
		const str_value* get = string._get();
		return (*(u32 const*)&get);
	}
} // namespace hash_fixed_vertex_manager
