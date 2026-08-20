////////////////////////////////////////////////////////////////////////////
//	Module 		: restriction_space.h
//	Created 	: 30.08.2004
//  Modified 	: 30.08.2004
//	Author		: Dmitriy Iassenev
//	Description : Restriction space
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ERestrictorTypes.hpp"

namespace RestrictionSpace
{
	struct CTimeIntrusiveBase : public intrusive_base_deferred
	{
		u32 m_last_time_dec;

		IC CTimeIntrusiveBase() : m_last_time_dec(0)
		{
		}

		IC void on_deferred_release()
		{
			m_last_time_dec = Device.dwTimeGlobal;
		}
	};
};
