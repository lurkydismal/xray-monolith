set(PROJECT_NAME xrAPI)

################################################################################
# Source groups
################################################################################
set(Kernel
    "../../Include/xrAPI/xrAPI.h"
    "stdafx.cpp"
    "stdafx.h"
    "xrAPI.cpp"
)
source_group("Kernel" FILES ${Kernel})

set(ALL_FILES
    ${Kernel}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

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

set(ROOT_NAMESPACE xrAPI)

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
    ARCHIVE_OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DX10             "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX10AVX          "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11             "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11AVX          "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8              "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8AVX           "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9              "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9AVX           "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_PROFILEDDX11     "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASE          "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASEAVX       "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIED         "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11     "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11ASAN "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX8      "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX9      "${TARGET_NAME}"
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
    INTERPROCEDURAL_OPTIMIZATION_VERIFIED         "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11     "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11ASAN "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX8      "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX9      "FALSE"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Verified>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX11>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX11ASAN>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX8>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX9>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Verified>,$<CONFIG:VerifiedDX11>,$<CONFIG:VerifiedDX11ASAN>,$<CONFIG:VerifiedDX8>,$<CONFIG:VerifiedDX9>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER"
    ">"
    "$<$<CONFIG:Verified>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "XRCORE_PROFILER;"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "WIN32;"
    "NDEBUG;"
    "_WINDOWS;"
    "_USRDLL;"
    "XRAPI_EXPORTS;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MY_MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            /GL;
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
            /GL;
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
            /GL;
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
            /GL;
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
            /GL;
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
            /GL;
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
            /GL;
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
            /GL;
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
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi
        >
        $<$<CONFIG:Release>:
            /GL;
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
            /GL;
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
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX11>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX8>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX9>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /GS;
            /Zc:inline-
        >
        /std:c++latest
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
    )
endif()

