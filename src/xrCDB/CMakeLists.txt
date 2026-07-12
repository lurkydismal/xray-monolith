set(PROJECT_NAME xrCDB)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "ReadMe.txt"
)
source_group("" FILES ${no_group_source_files})

set(Kernel
    "Frustum.cpp"
    "Frustum.h"
    "StdAfx.cpp"
    "StdAfx.h"
    "xrCDB.cpp"
    "xrCDB.h"
    "xrCDB_box.cpp"
    "xrCDB_Collector.cpp"
    "xrCDB_frustum.cpp"
    "xrCDB_ray.cpp"
)
source_group("Kernel" FILES ${Kernel})

set(Opcode
    "OPC_AABB.cpp"
    "OPC_AABB.h"
    "OPC_AABBCollider.cpp"
    "OPC_AABBCollider.h"
    "OPC_AABBTree.cpp"
    "OPC_AABBTree.h"
    "OPC_BoundingSphere.h"
    "OPC_BoxBoxOverlap.h"
    "OPC_BVTCache.h"
    "OPC_Collider.cpp"
    "OPC_Collider.h"
    "OPC_Common.cpp"
    "OPC_Common.h"
    "OPC_Container.cpp"
    "OPC_Container.h"
    "OPC_FPU.h"
    "OPC_Matrix3x3.cpp"
    "OPC_Matrix3x3.h"
    "OPC_Matrix4x4.cpp"
    "OPC_Matrix4x4.h"
    "OPC_MemoryMacros.h"
    "OPC_Model.cpp"
    "OPC_Model.h"
    "OPC_OBB.cpp"
    "OPC_OBB.h"
    "OPC_OBBCollider.cpp"
    "OPC_OBBCollider.h"
    "OPC_OptimizedTree.cpp"
    "OPC_OptimizedTree.h"
    "OPC_Plane.cpp"
    "OPC_Plane.h"
    "OPC_PlanesAABBOverlap.h"
    "OPC_PlanesCollider.cpp"
    "OPC_PlanesCollider.h"
    "OPC_PlanesTriOverlap.h"
    "OPC_Point.cpp"
    "OPC_Point.h"
    "OPC_Preprocessor.h"
    "OPC_Ray.cpp"
    "OPC_Ray.h"
    "OPC_RayAABBOverlap.h"
    "OPC_RayCollider.cpp"
    "OPC_RayCollider.h"
    "OPC_RayTriOverlap.h"
    "OPC_Settings.h"
    "OPC_SphereAABBOverlap.h"
    "OPC_SphereCollider.cpp"
    "OPC_SphereCollider.h"
    "OPC_SphereTriOverlap.h"
    "OPC_TreeBuilders.cpp"
    "OPC_TreeBuilders.h"
    "OPC_TreeCollider.cpp"
    "OPC_TreeCollider.h"
    "OPC_Triangle.cpp"
    "OPC_Triangle.h"
    "OPC_TriBoxOverlap.h"
    "OPC_TriTriOverlap.h"
    "OPC_Types.h"
    "OPC_VolumeCollider.cpp"
    "OPC_VolumeCollider.h"
    "Opcode.cpp"
    "Opcode.h"
)
source_group("Opcode" FILES ${Opcode})

set(engine
    "ISpatial.cpp"
    "ISpatial.h"
    "ISpatial_q_box.cpp"
    "ISpatial_q_frustum.cpp"
    "ISpatial_q_ray.cpp"
    "ISpatial_verify.cpp"
    "sse_intersect.h"
    "xr_area.cpp"
    "xr_area.h"
    "xr_area_raypick.cpp"
    "xr_collide_defs.h"
    "xrXRC.cpp"
    "xrXRC.h"
)
source_group("engine" FILES ${engine})

set(ALL_FILES
    ${no_group_source_files}
    ${Kernel}
    ${Opcode}
    ${engine}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.h>"
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

set(ROOT_NAMESPACE xrCDB)

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
    ARCHIVE_OUTPUT_NAME_DX10             "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX10AVX          "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11             "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11AVX          "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8              "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8AVX           "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9              "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9AVX           "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_PROFILEDDX11     "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASE          "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASEAVX       "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIED         "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11     "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11ASAN "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX8      "${${PROPS_TARGET}_TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX9      "${${PROPS_TARGET}_TARGET_NAME}"
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
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../xrCore;"
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
    "XRCDB_EXPORTS;"
    "_SECURE_SCL=0;"
    "_MBCS"
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
        /std:c++17
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /NOLOGO;
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    xrAPI
    xrCore
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my/"
)

