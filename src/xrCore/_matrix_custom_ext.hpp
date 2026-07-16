#pragma once

#include "../xrEngine/stdafx.h"

template<class T>
typename _matrix<T>::SelfRef _matrix<T>::hud_to_world()
{
    Device.hud_to_world(*this);
    return *this;
}

template<class T>
typename _matrix<T>::SelfRef _matrix<T>::world_to_hud()
{
    Device.world_to_hud(*this);
    return *this;
}
