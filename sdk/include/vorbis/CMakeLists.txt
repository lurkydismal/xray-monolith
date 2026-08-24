set(PROJECT_NAME libvorbis_static)

################################################################################
# Source groups
################################################################################
set(include
    "codec.h"
    "lib/backends.h"
    "lib/bitrate.h"
    "lib/books/coupled/res_books_stereo.h"
    "lib/books/floor/floor_books.h"
    "lib/books/uncoupled/res_books_uncoupled.h"
    "lib/codebook.h"
    "lib/codec_internal.h"
    "lib/envelope.h"
    "lib/highlevel.h"
    "lib/lookup.h"
    "lib/lookup_data.h"
    "lib/lpc.h"
    "lib/lsp.h"
    "lib/masking.h"
    "lib/mdct.h"
    "lib/misc.h"
    "lib/modes/floor_all.h"
    "lib/modes/psych_11.h"
    "lib/modes/psych_16.h"
    "lib/modes/psych_44.h"
    "lib/modes/psych_8.h"
    "lib/modes/residue_16.h"
    "lib/modes/residue_44.h"
    "lib/modes/residue_44u.h"
    "lib/modes/residue_8.h"
    "lib/modes/setup_11.h"
    "lib/modes/setup_16.h"
    "lib/modes/setup_22.h"
    "lib/modes/setup_32.h"
    "lib/modes/setup_44.h"
    "lib/modes/setup_44u.h"
    "lib/modes/setup_8.h"
    "lib/modes/setup_X.h"
    "lib/os.h"
    "lib/psy.h"
    "lib/registry.h"
    "lib/scales.h"
    "lib/smallft.h"
    "lib/window.h"
    "vorbisenc.h"
    "vorbisfile.h"
)
source_group("include" FILES ${include})

set(src
    "lib/analysis.c"
    "lib/bitrate.c"
    "lib/block.c"
    "lib/codebook.c"
    "lib/envelope.c"
    "lib/floor0.c"
    "lib/floor1.c"
    "lib/info.c"
    "lib/lookup.c"
    "lib/lpc.c"
    "lib/lsp.c"
    "lib/mapping0.c"
    "lib/mdct.c"
    "lib/psy.c"
    "lib/registry.c"
    "lib/res0.c"
    "lib/sharedbook.c"
    "lib/smallft.c"
    "lib/synthesis.c"
    "lib/vorbisenc.c"
    "lib/window.c"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${include}
    ${src}
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
use_props(${PROJECT_NAME} DX10             "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX11             "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX8              "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX9              "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../../../src/Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../../../src/Common.cmake")
use_props(${PROJECT_NAME} Release          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../../../src/Common.cmake")
use_props(${PROJECT_NAME} Verified         "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../../../src/Common.cmake")

set(ROOT_NAMESPACE libvorbis)

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
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
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
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "WIN32;"
    "ANALYSIS;"
    "NDEBUG;"
    "_WINDOWS"
)

################################################################################
# Compile and link options
################################################################################
if(IS_CLANG_CL_MINGW OR IS_CLANG_CL_MSVC OR IS_MSVC)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
        >
        $<$<CONFIG:ProfiledDX11>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi;
            /Y-
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
            /Ob3;
            /Y-
        >
        $<$<CONFIG:Verified>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi;
            /TC;
            /Y-
        >
        /wd4244;
        /wd4100;
        /wd4267;
        /wd4189;
        /wd4305;
        /wd4127;
        /wd4706
    )
elseif(IS_CLANG_MINGW OR IS_CLANG_MSVC)
    xray_target_compile_options(${PROJECT_NAME})
    xray_target_link_options(${PROJECT_NAME})
endif()



























set(PROJECT_NAME libvorbisfile_static)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "lib/vorbisfile.c"
    # "vorbis/vorbisfile.h"
)
source_group("" FILES ${no_group_source_files})

set(ALL_FILES
    ${no_group_source_files}
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
use_props(${PROJECT_NAME} DX10             "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX11             "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX8              "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX9              "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../../../src/Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../../../src/Common.cmake")
use_props(${PROJECT_NAME} Release          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../../../src/Common.cmake")
use_props(${PROJECT_NAME} Verified         "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../../../src/Common.cmake")

set(ROOT_NAMESPACE libvorbisfile)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DX10             "${PROJECT_NAME}.lib"
    TARGET_NAME_DX10AVX          "${PROJECT_NAME}.lib"
    TARGET_NAME_DX11             "${PROJECT_NAME}.lib"
    TARGET_NAME_DX11AVX          "${PROJECT_NAME}.lib"
    TARGET_NAME_DX8              "${PROJECT_NAME}.lib"
    TARGET_NAME_DX8AVX           "${PROJECT_NAME}.lib"
    TARGET_NAME_DX9              "${PROJECT_NAME}.lib"
    TARGET_NAME_DX9AVX           "${PROJECT_NAME}.lib"
    TARGET_NAME_PROFILEDDX11     "${PROJECT_NAME}.lib"
    TARGET_NAME_RELEASE          "${PROJECT_NAME}.lib"
    TARGET_NAME_RELEASEAVX       "${PROJECT_NAME}.lib"
    TARGET_NAME_VERIFIED         "${PROJECT_NAME}.lib"
    TARGET_NAME_VERIFIEDDX11     "${PROJECT_NAME}.lib"
    TARGET_NAME_VERIFIEDDX11ASAN "${PROJECT_NAME}.lib"
    TARGET_NAME_VERIFIEDDX8      "${PROJECT_NAME}.lib"
    TARGET_NAME_VERIFIEDDX9      "${PROJECT_NAME}.lib"
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
# )
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
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
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "WIN32;"
    "NDEBUG;"
    "_WINDOWS"
)

################################################################################
# Compile and link options
################################################################################
if(IS_CLANG_CL_MINGW OR IS_CLANG_CL_MSVC OR IS_MSVC)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
        >
        $<$<CONFIG:ProfiledDX11>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi;
            /Y-
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
            /Ob3;
            /Y-
        >
        $<$<CONFIG:Verified>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /W3;
            /Zi;
            /Y-
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /W3;
            /Zi;
            /Y-
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /W3;
            /Zi;
            /Y-
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /W3;
            /Zi;
            /Y-
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /W3;
            /Zi;
            /Y-
        >
    )
elseif(IS_CLANG_MINGW OR IS_CLANG_MSVC)
    xray_target_compile_options(${PROJECT_NAME})
    xray_target_link_options(${PROJECT_NAME})
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    libvorbis_static
)

