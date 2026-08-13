set(PROJECT_NAME ReShadeCompat)

################################################################################
# Source groups
################################################################################
set(addon
    "addon.cpp"
    "stdafx.cpp"
    "stdafx.h"
)
source_group("addon" FILES ${addon})

set(ALL_FILES
    ${addon}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "3rd_party")

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} DX10             "../Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../Common.cmake")
use_props(${PROJECT_NAME} DX11             "../Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../Common.cmake")
use_props(${PROJECT_NAME} DX8              "../Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../Common.cmake")
use_props(${PROJECT_NAME} DX9              "../Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../Common.cmake")
use_props(${PROJECT_NAME} Release          "../Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../Common.cmake")
use_props(${PROJECT_NAME} Verified         "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../Common.cmake")

set(ROOT_NAMESPACE ReShadeCompat)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
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
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     INTERPROCEDURAL_OPTIMIZATION_DX10             "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX10AVX          "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX11             "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX11AVX          "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX8              "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX8AVX           "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX9              "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX9AVX           "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_PROFILEDDX11     "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_RELEASE          "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_RELEASEAVX       "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIED         "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11     "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11ASAN "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX8      "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX9      "FALSE"
# )
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:DX10>:
        MultiThreadedDLL
    >
    $<$<CONFIG:DX10AVX>:
        MultiThreadedDLL
    >
    $<$<CONFIG:DX11>:
        MultiThreadedDLL
    >
    $<$<CONFIG:DX11AVX>:
        MultiThreadedDLL
    >
    $<$<CONFIG:DX8>:
        MultiThreadedDLL
    >
    $<$<CONFIG:DX8AVX>:
        MultiThreadedDLL
    >
    $<$<CONFIG:DX9>:
        MultiThreadedDLL
    >
    $<$<CONFIG:DX9AVX>:
        MultiThreadedDLL
    >
    $<$<CONFIG:ProfiledDX11>:
        MultiThreadedDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<CONFIG:ReleaseAVX>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:DX10>,$<CONFIG:DX10AVX>,$<CONFIG:DX11>,$<CONFIG:DX11AVX>,$<CONFIG:DX8>,$<CONFIG:DX8AVX>,$<CONFIG:DX9>,$<CONFIG:DX9AVX>,$<CONFIG:ProfiledDX11>,$<CONFIG:Release>,$<CONFIG:ReleaseAVX>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER"
    ">"
    "$<$<CONFIG:Verified>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "PURE_ALLOC;"
    "WIN32;"
    "NDEBUG;"
    "_WINDOWS;"
    "_USRDLL;"
    "XRCORE_EXPORTS;"
    "_SECURE_SCL=0;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:DX10AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /Ot;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:DX11>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:DX11AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /Ot;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:DX8>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:DX8AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /Ot;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:DX9>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:DX9AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /Ot;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:ProfiledDX11>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /W4;
            /Zi;
            /fp:precise;
            /GR;
            /GS
        >
        $<$<CONFIG:Release>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:ReleaseAVX>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /W4;
            /Zi;
            /Ot;
            /fp:precise;
            /GR;
            /Ob3;
            /GS
        >
        $<$<CONFIG:Verified>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        /std:c++latest
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /DYNAMICBASE:NO
    )
endif()

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/BugTrap/Bin;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my/"
)

