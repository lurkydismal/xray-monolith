set(PROJECT_NAME CxImage)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "xfile.h"
    "ximacfg.h"
    "ximadef.h"
    "ximage.h"
    "ximaiter.h"
    "ximajpg.h"
    "ximath.h"
    "xiofile.h"
    "xmemfile.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "ximacfg.cpp"
    "ximaenc.cpp"
    "ximaexif.cpp"
    "ximage.cpp"
    "ximainfo.cpp"
    "ximaint.cpp"
    "ximajpg.cpp"
    "ximalpha.cpp"
    "ximalyr.cpp"
    "ximapal.cpp"
    "ximasel.cpp"
    "ximath.cpp"
    "xmemfile.cpp"
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
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "3rd_party")

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

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "MFCProj"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMMON_LANGUAGE_RUNTIME_VERIFIED         "No"
    COMMON_LANGUAGE_RUNTIME_VERIFIEDDX11     "No"
    COMMON_LANGUAGE_RUNTIME_VERIFIEDDX11ASAN "No"
    COMMON_LANGUAGE_RUNTIME_VERIFIEDDX8      "No"
    COMMON_LANGUAGE_RUNTIME_VERIFIEDDX9      "No"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DX10             "${PROJECT_NAME}"
    TARGET_NAME_DX10AVX          "${PROJECT_NAME}"
    TARGET_NAME_DX11             "${PROJECT_NAME}"
    TARGET_NAME_DX11AVX          "${PROJECT_NAME}"
    TARGET_NAME_DX8              "${PROJECT_NAME}"
    TARGET_NAME_DX8AVX           "${PROJECT_NAME}"
    TARGET_NAME_DX9              "${PROJECT_NAME}"
    TARGET_NAME_DX9AVX           "${PROJECT_NAME}"
    TARGET_NAME_PROFILEDDX11     "${PROJECT_NAME}"
    TARGET_NAME_RELEASE          "${PROJECT_NAME}"
    TARGET_NAME_RELEASEAVX       "${PROJECT_NAME}"
    TARGET_NAME_VERIFIED         "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX11     "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX11ASAN "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX8      "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX9      "${PROJECT_NAME}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
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
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER"
    ">"
    "$<$<CONFIG:Verified>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "WIN32;"
    "NDEBUG;"
    "_LIB;"
    "JAS_WIN_MSVC_BUILD;"
    "CXIMAGE_BUILD"
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
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX10AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX11AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX8AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX9AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi
        >
        $<$<CONFIG:Release>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:ReleaseAVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        /std:c++latest;
        /wd4995;
        /wd4100;
        /wd4702
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Verified>:
            /NOLOGO
        >
        $<$<CONFIG:VerifiedDX11>:
            /NOLOGO
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /NOLOGO
        >
        $<$<CONFIG:VerifiedDX8>:
            /NOLOGO
        >
        $<$<CONFIG:VerifiedDX9>:
            /NOLOGO
        >
    )
elseif(IS_CLANG AND NOT MSVC)
    xray_target_compile_options(${PROJECT_NAME})
    xray_target_link_options(${PROJECT_NAME})
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    xrCore
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include//jpeg-8c/Release/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my/"
)

