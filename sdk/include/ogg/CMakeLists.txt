set(PROJECT_NAME libogg_static)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "ogg.def"
)
source_group("" FILES ${no_group_source_files})

set(Headers
    "ogg.h"
    "os_types.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "src/bitwise.c"
    "src/framing.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${no_group_source_files}
    ${Headers}
    ${Sources}
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
use_props(${PROJECT_NAME} DX10             "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX11             "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX8              "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX9              "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} Release          "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} Verified         "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "${CMAKE_SOURCE_DIR}/Common.cmake")

set(ROOT_NAMESPACE libogg)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DX10             "libogg_static"
    TARGET_NAME_DX10AVX          "libogg_static"
    TARGET_NAME_DX11             "libogg_static"
    TARGET_NAME_DX11AVX          "libogg_static"
    TARGET_NAME_DX8              "libogg_static"
    TARGET_NAME_DX8AVX           "libogg_static"
    TARGET_NAME_DX9              "libogg_static"
    TARGET_NAME_DX9AVX           "libogg_static"
    TARGET_NAME_PROFILEDDX11     "libogg_static"
    TARGET_NAME_RELEASE          "libogg_static"
    TARGET_NAME_RELEASEAVX       "libogg_static"
    TARGET_NAME_VERIFIED         "libogg_static"
    TARGET_NAME_VERIFIEDDX11     "libogg_static"
    TARGET_NAME_VERIFIEDDX11ASAN "libogg_static"
    TARGET_NAME_VERIFIEDDX8      "libogg_static"
    TARGET_NAME_VERIFIEDDX9      "libogg_static"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX10AVX          "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11             "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11AVX          "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8              "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8AVX           "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9              "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9AVX           "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE          "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASEAVX       "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIED         "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
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
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
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
if(MSVC)
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
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
            /Ob3;
            /Y-
        >
        $<$<CONFIG:ProfiledDX11>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi;
            /Y-
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
            /Ob3;
            /Y-
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
            /TC;
            /Y-
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
            /TC;
            /Y-
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
            /TC;
            /Y-
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
            /TC;
            /Y-
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
            /TC;
            /Y-
        >
        /std:c++17;
        /wd4244
    )
endif()

