set(PROJECT_NAME optick)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "../optick-git/src/optick.config.h"
    "../optick-git/src/optick.h"
    "../optick-git/src/optick_capi.h"
    "../optick-git/src/optick_common.h"
    "../optick-git/src/optick_core.freebsd.h"
    "../optick-git/src/optick_core.h"
    "../optick-git/src/optick_core.linux.h"
    "../optick-git/src/optick_core.macos.h"
    "../optick-git/src/optick_core.platform.h"
    "../optick-git/src/optick_core.win.h"
    "../optick-git/src/optick_gpu.h"
    "../optick-git/src/optick_memory.h"
    "../optick-git/src/optick_message.h"
    "../optick-git/src/optick_miniz.h"
    "../optick-git/src/optick_serialization.h"
    "../optick-git/src/optick_server.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../optick-git/src/optick_capi.cpp"
    "../optick-git/src/optick_core.cpp"
    "../optick-git/src/optick_gpu.cpp"
    "../optick-git/src/optick_gpu.d3d12.cpp"
    "../optick-git/src/optick_gpu.vulkan.cpp"
    "../optick-git/src/optick_message.cpp"
    "../optick-git/src/optick_miniz.cpp"
    "../optick-git/src/optick_serialization.cpp"
    "../optick-git/src/optick_server.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "3rd party")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} DX10             "../../Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../../Common.cmake")
use_props(${PROJECT_NAME} DX11             "../../Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../../Common.cmake")
use_props(${PROJECT_NAME} DX8              "../../Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../../Common.cmake")
use_props(${PROJECT_NAME} DX9              "../../Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../../Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../../Common.cmake")
use_props(${PROJECT_NAME} Release          "../../Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../../Common.cmake")
use_props(${PROJECT_NAME} Verified         "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../../Common.cmake")

set(ROOT_NAMESPACE optick)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_DX10             "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX10AVX          "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX11             "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX11AVX          "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX8              "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX8AVX           "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX9              "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX9AVX           "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_PROFILEDDX11     "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASE          "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASEAVX       "TRUE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../optick-git/src"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:DX10>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX10AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX11>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX11AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX8>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX8AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX9>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX9AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER;"
        "NDEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:ReleaseAVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:Verified>:"
        "USE_VERIFY_IN_RELEASE;"
        "DEBUG"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE;"
        "DEBUG"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "DEBUG"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE;"
        "DEBUG"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE;"
        "DEBUG"
    ">"
    "OPTICK_ENABLE_GPU_VULKAN=0;"
    "_LIB;"
    "_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX10AVX>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX11>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX11AVX>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX8>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX8AVX>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX9>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX9AVX>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:ProfiledDX11>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:ReleaseAVX>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:Verified>:
            /MP;
            /Od;
            /Ob0;
            /Oy-;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:VerifiedDX11>:
            /MP;
            /Od;
            /Ob0;
            /Oy-;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /MP;
            /Od;
            /Ob0;
            /Oy-;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /MP;
            /Od;
            /Ob0;
            /Oy-;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:VerifiedDX9>:
            /MP;
            /Od;
            /Ob0;
            /Oy-;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /permissive-;
        /std:c++17;
        /sdl;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:DX10AVX>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:DX11>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:DX11AVX>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:DX8>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:DX8AVX>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:DX9>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:DX9AVX>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:ProfiledDX11>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:ReleaseAVX>:
            /OPT:REF;
            /OPT:ICF
        >
    )
endif()

