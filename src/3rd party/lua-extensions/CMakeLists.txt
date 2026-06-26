set(PROJECT_NAME lua_extensions)

################################################################################
# Source groups
################################################################################
set(Headers
    "lfs.h"
    "lmarshal.h"
    "luapanda.h"
    "luasocket/auxiliar.h"
    "luasocket/buffer.h"
    "luasocket/compat.h"
    "luasocket/except.h"
    "luasocket/inet.h"
    "luasocket/io.h"
    "luasocket/luasocket.h"
    "luasocket/mime.h"
    "luasocket/options.h"
    "luasocket/pierror.h"
    "luasocket/select.h"
    "luasocket/socket.h"
    "luasocket/tcp.h"
    "luasocket/timeout.h"
    "luasocket/udp.h"
    "luasocket/wsocket.h"
    "script_additional_libs.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "base.cpp"
    "lfs.c"
    "lmarshal.c"
    "luapanda.cpp"
    "luasocket/auxiliar.c"
    "luasocket/buffer.c"
    "luasocket/compat.c"
    "luasocket/except.c"
    "luasocket/inet.c"
    "luasocket/io.c"
    "luasocket/luasocket.c"
    "luasocket/mime.c"
    "luasocket/options.c"
    "luasocket/select.c"
    "luasocket/tcp.c"
    "luasocket/timeout.c"
    "luasocket/udp.c"
    "luasocket/wsocket.c"
    "script_additional_libs.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
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

set(ROOT_NAMESPACE rvp)

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
    ARCHIVE_OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DX10             "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX10AVX          "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11             "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11AVX          "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8              "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8AVX           "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9              "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9AVX           "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_PROFILEDDX11     "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASE          "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASEAVX       "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIED         "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11     "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11ASAN "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX8      "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX9      "$ENV{xrLibDir}${TARGET_NAME}"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/mnt/hdd/Projects/xray-monolith/src/3rd party/luajit-2/src"
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
    "_WINDLL;"
    "_CRT_SECURE_NO_WARNINGS"
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
            /W3;
            /ZI;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        >
        $<$<CONFIG:VerifiedDX11>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        >
        $<$<CONFIG:VerifiedDX8>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        >
        $<$<CONFIG:VerifiedDX9>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        >
        /std:c++17;
        /wd4996;
        /wd4244;
        /wd4018
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /MANIFEST;
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    LuaJIT-2
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/3rd party/luajit-2/src/"
)

