set(PROJECT_NAME xrServerEntities)

################################################################################
# Source groups
################################################################################
file(GLOB XR_SERVER_ENTITIES_FILES CONFIGURE_DEPENDS
    "*.c"
    "*.cpp"
    "*.h"
    "*.hpp"
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${XR_SERVER_ENTITIES_FILES})

################################################################################
# Target
################################################################################
set(OBJECT_TARGET ${PROJECT_NAME}_objects)
xray_add_dual_library(${PROJECT_NAME} ${OBJECT_TARGET} ${XR_SERVER_ENTITIES_FILES})

target_precompile_headers(${OBJECT_TARGET} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/../xrGame/StdAfx.h>"
)

use_props(${OBJECT_TARGET} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${OBJECT_TARGET} DX10             "../Common.cmake")
use_props(${OBJECT_TARGET} DX10AVX          "../Common.cmake")
use_props(${OBJECT_TARGET} DX11             "../Common.cmake")
use_props(${OBJECT_TARGET} DX11AVX          "../Common.cmake")
use_props(${OBJECT_TARGET} DX8              "../Common.cmake")
use_props(${OBJECT_TARGET} DX8AVX           "../Common.cmake")
use_props(${OBJECT_TARGET} DX9              "../Common.cmake")
use_props(${OBJECT_TARGET} DX9AVX           "../Common.cmake")
use_props(${OBJECT_TARGET} ProfiledDX11     "../Common.cmake")
use_props(${OBJECT_TARGET} Release          "../Common.cmake")
use_props(${OBJECT_TARGET} ReleaseAVX       "../Common.cmake")
use_props(${OBJECT_TARGET} Verified         "../Common.cmake")
use_props(${OBJECT_TARGET} VerifiedDX11     "../Common.cmake")
use_props(${OBJECT_TARGET} VerifiedDX11ASAN "../Common.cmake")
use_props(${OBJECT_TARGET} VerifiedDX8      "../Common.cmake")
use_props(${OBJECT_TARGET} VerifiedDX9      "../Common.cmake")

target_include_directories(${PROJECT_NAME} PUBLIC "$<TARGET_PROPERTY:${OBJECT_TARGET},INCLUDE_DIRECTORIES>")
target_include_directories(${PROJECT_NAME}_shared PUBLIC "$<TARGET_PROPERTY:${OBJECT_TARGET},INCLUDE_DIRECTORIES>")

set(ROOT_NAMESPACE xrServerEntities)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_shared PROPERTIES
    FOLDER "engine"
)

################################################################################
# Include directories
################################################################################
target_include_directories(${OBJECT_TARGET} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../xrCore;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../xrGame;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/luajit-2/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/luabind;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${OBJECT_TARGET} PRIVATE
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
        "USE_VERIFY_IN_RELEASE;"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION"
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
    "XRGAME_EXPORTS;"
    "dSINGLE;"
    "MSVC;"
    "_SECURE_SCL=0;"
    "_MBCS"
)

################################################################################
# Dependencies
################################################################################
xray_link_project_libraries(${PROJECT_NAME} PUBLIC
    luabind
)
xray_link_project_libraries(${PROJECT_NAME}_shared PUBLIC
    luabind
)
