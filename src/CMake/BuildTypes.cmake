################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "DX10"
    "DX10AVX"
    "DX11"
    "DX11AVX"
    "DX8"
    "DX8AVX"
    "DX9"
    "DX9AVX"
    "ProfiledDX11"
    "Release"
    "ReleaseAVX"
    "Verified"
    "VerifiedDX11"
    "VerifiedDX11ASAN"
    "VerifiedDX8"
    "VerifiedDX9"
    CACHE STRING "" FORCE
)

# TODO: Refactor
# set(XR_RENDERER DX11)
# if(XR_RENDERER STREQUAL DX11)

set(DX8_TYPES  DX8 DX8AVX VerifiedDX8)
set(DX9_TYPES  DX9 DX9AVX VerifiedDX9)
set(DX10_TYPES DX10 DX10AVX VerifiedDX10)
set(DX11_TYPES DX11 DX11AVX VerifiedDX11)

set(IS_DX8  FALSE)
set(IS_DX9  FALSE)
set(IS_DX10 FALSE)
set(IS_DX11 FALSE)

if(CMAKE_BUILD_TYPE IN_LIST DX8_TYPES)
    set(IS_DX8 TRUE)
elseif(CMAKE_BUILD_TYPE IN_LIST DX9_TYPES)
    set(IS_DX9 TRUE)
elseif(CMAKE_BUILD_TYPE IN_LIST DX10_TYPES)
    set(IS_DX10 TRUE)
elseif(CMAKE_BUILD_TYPE IN_LIST DX11_TYPES)
    set(IS_DX11 TRUE)
endif()

# TODO: Refactor and rename
if(CMAKE_BUILD_TYPE MATCHES "^(Release|Release-AVX|ProfiledDX11|Verified|VerifiedDX11|VerifiedDX11ASAN)$")
    message(STATUS "Legacy debug runtime: disabled")
    set(ENABLE_DEBUG_OLD_RUNTIME FALSE)
else()
    message(STATUS "Legacy debug runtime: enabled")
    set(ENABLE_DEBUG_OLD_RUNTIME TRUE)
endif()
