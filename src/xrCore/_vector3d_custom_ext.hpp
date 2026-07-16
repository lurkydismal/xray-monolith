#pragma once

#include "../xrEngine/stdafx.h"

template<class T>
typename _vector3<T>::SelfRef _vector3<T>::hud_to_world()
{
    Device.hud_to_world(*this);
    return *this;
}

template<class T>
typename _vector3<T>::SelfRef _vector3<T>::world_to_hud()
{
    Device.world_to_hud(*this);
    return *this;
}

template<class T>
typename _vector3<T>::SelfRef _vector3<T>::hud_to_world_dir()
{
    Device.hud_to_world_dir(*this);
    return *this;
}

template<class T>
typename _vector3<T>::SelfRef _vector3<T>::world_to_hud_dir()
{
    Device.world_to_hud_dir(*this);
    return *this;
}
