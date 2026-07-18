#include "_vector3d.h"
#include "../xrEngine/device.h"

// Float
template<>
typename Fvector::SelfRef Fvector::hud_to_world()
{
    Device.hud_to_world(*this);
    return *this;
}

template<>
typename Fvector::SelfRef Fvector::world_to_hud()
{
    Device.world_to_hud(*this);
    return *this;
}

template<>
typename Fvector::SelfRef Fvector::hud_to_world_dir()
{
    Device.hud_to_world_dir(*this);
    return *this;
}

template<>
typename Fvector::SelfRef Fvector::world_to_hud_dir()
{
    Device.world_to_hud_dir(*this);
    return *this;
}

template<>
typename Fvector::SelfRef Fvector::ema(Self& target, unsigned int steps) {
    float smoothing_alpha = 2.0f / (steps + 1);
    float delta = Device.dwTimeDelta;

    if (steps <= 1 || (fis_zero(x) && fis_zero(y) && fis_zero(z))) {
        x = target.x;
        y = target.y;
        z = target.z;
        return *this;
    }

    x = x + std::min(1.f, smoothing_alpha * (delta / steps)) * (target.x - x);
    y = y + std::min(1.f, smoothing_alpha * (delta / steps)) * (target.y - y);
    z = z + std::min(1.f, smoothing_alpha * (delta / steps)) * (target.z - z);
    return *this;
}
