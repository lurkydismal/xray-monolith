#pragma once

namespace SightManager {

enum ESightType
{
    eSightTypeCurrentDirection = u32(0),
    eSightTypePathDirection,
    eSightTypeDirection,
    eSightTypePosition,
    eSightTypeObject,
    eSightTypeCover,
    eSightTypeSearch,
    eSightTypeLookOver,
    eSightTypeCoverLookOver,
    eSightTypeFireObject,
    eSightTypeFirePosition,
    // must be removed
    eSightTypeAnimationDirection,
    eSightTypeDummy = u32(-1),
};

}
