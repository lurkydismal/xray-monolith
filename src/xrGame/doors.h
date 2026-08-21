////////////////////////////////////////////////////////////////////////////
//	Created		: 25.06.2009
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef DOORS_H_INCLUDED
#define DOORS_H_INCLUDED

#include "door_state.hpp"

namespace doors
{
	class door;
	typedef xr_vector<door*> doors_type;

#if 0
	enum door_state
	{
		door_state_open,
		door_state_closed,
	}; // enum door_state
#endif

	extern float const g_door_length;
	extern float const g_door_open_time;
} // namespace doors

#endif // #ifndef DOORS_H_INCLUDED
