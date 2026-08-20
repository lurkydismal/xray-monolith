################################################################################
# Common.cmake
#
# Variables available:
#   PROPS_TARGET
#   PROPS_CONFIG
#   PROPS_CONFIG_U
################################################################################

# ------------------------------------------------------------------------------
# Equivalent of UserMacros
# ------------------------------------------------------------------------------

set(xrBinRootDir      "${CMAKE_SOURCE_DIR}/../_build/bin")
set(xrBinPlugRootDir  "${CMAKE_SOURCE_DIR}/../_build/bin_plugs")
set(xrLibRootDir      "${CMAKE_SOURCE_DIR}/../_build/lib")

set(xrBinDir          "${CMAKE_SOURCE_DIR}/../_build/bin/${PROPS_CONFIG}")
set(xrBinPlugDir      "${CMAKE_SOURCE_DIR}/../_build/bin_plugs/${PROPS_CONFIG}")
set(xrLibDir          "${CMAKE_SOURCE_DIR}/../_build/lib/${PROPS_CONFIG}")

set(xrIntDir          "${CMAKE_SOURCE_DIR}/../_build/intermediate/${PROPS_CONFIG}")

set(xrSdkDir          "${CMAKE_SOURCE_DIR}/../sdk")
set(xrGameDir         "${CMAKE_SOURCE_DIR}/../_build/_game")
set(xrGameBinDir      "${CMAKE_SOURCE_DIR}/../_build/_game/bin")
set(xr3rdPartyDir     "${CMAKE_SOURCE_DIR}/3rd_party")
set(dxSdkDir          "${CMAKE_SOURCE_DIR}/../sdk/include/dxsdk")

# ------------------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------------------

target_include_directories(${PROPS_TARGET}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/../src/3rd_party"
        "${CMAKE_SOURCE_DIR}/3rd_party/icu/include"
        "${CMAKE_SOURCE_DIR}/../sdk/include"
        "${CMAKE_SOURCE_DIR}/../sdk/include/OpenAutomate"
        "${CMAKE_SOURCE_DIR}/../sdk/include/nvapi"
        "${CMAKE_SOURCE_DIR}/../sdk/include/dxsdk"
)

# ------------------------------------------------------------------------------
# Output directory
# ------------------------------------------------------------------------------

set_target_properties(${PROPS_TARGET}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_SOURCE_DIR}/../_build/_game/bin_dbg"
)

# ------------------------------------------------------------------------------
# Compiler definitions
# ------------------------------------------------------------------------------

target_compile_definitions(${PROPS_TARGET}
    PRIVATE
        _VC80_UPGRADE=0x0710
        _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
        XRAY_MSVC_COMPAT
)

if(IS_CLANG_MINGW OR IS_CLANG_CL_MINGW)
    target_compile_definitions(${PROPS_TARGET}
        PRIVATE
            _MT
    )
endif()

# There is no direct equivalent of
# <UndefinePreprocessorDefinitions>USE_LUAJIT_ONE</...>
# If another script adds it, remove it there instead.

# ------------------------------------------------------------------------------
# MSVC compiler options
# ------------------------------------------------------------------------------

target_compile_options(${PROPS_TARGET}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /MP
            /GS
            ${XRAY_OPTIMIZATION_FLAG}
            /fp:precise
            /Gy
        >
)

# ------------------------------------------------------------------------------
# MSVC linker options
# ------------------------------------------------------------------------------

target_link_options(${PROPS_TARGET}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /LARGEADDRESSAWARE
            /DYNAMICBASE:NO
            /DEBUG:NONE
        >
)
