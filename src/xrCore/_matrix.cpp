#include "_matrix.h"

#include "../xrEngine/device.h"

template <>
typename Fmatrix::SelfRef Fmatrix::hud_to_world() {
    Device.hud_to_world( *this );
    return *this;
}

template <>
typename Fmatrix::SelfRef Fmatrix::world_to_hud() {
    Device.world_to_hud( *this );
    return *this;
}
