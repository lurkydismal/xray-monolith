set(PROJECT_NAME xrCore)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "FileSystem.h"
#    "LocatorAPI_Notifications.h"
)
source_group("" FILES ${no_group_source_files})

set(Headers
    "../3rd party/fastdelegate/fastdelegate.h"
    "../3rd party/robin_hood/robin_hood.h"
    "../3rd party/stackwalker/include/StackWalker.h"
    "../build_config_defines.h"
    "_bitwise.h"
    "_color.h"
    "_compressed_normal.h"
    "_cylinder.h"
    "_fbox.h"
    "_fbox2.h"
    "_flags.h"
    "_global_functions.h"
    "_math.h"
    "_matrix.h"
    "_matrix33.h"
    "_noncopyable.h"
    "_obb.h"
    "_plane.h"
    "_plane2.h"
    "_quaternion.h"
    "_random.h"
    "_rect.h"
    "_sphere.h"
    "_std_extensions.h"
    "_stl_extensions.h"
    "_thread_types.h"
    "_type_traits.h"
    "_types.h"
    "_vector2.h"
    "_vector3d.h"
    "_vector3d_ext.h"
    "_vector4.h"
    "blackbox/BugslayerUtil.h"
    "blackbox/CrashHandler.h"
    "blackbox/DiagAssert.h"
    "blackbox/Internal.h"
    "blackbox/stdafx_.h"
    "blackbox/SymbolEngine.h"
    "blackbox/WarningsOff.h"
    "blackbox/WarningsOn.h"
    "buffer_vector.h"
    "buffer_vector_inline.h"
    "ChooseTypes.H"
    "client_id.h"
    "clsid.h"
    "Coder.hpp"
    "compression_ppmd_stream.h"
    "compression_ppmd_stream_inline.h"
    "cpuid.h"
    "DateTime.hpp"
    "dump_string.h"
    "file_stream_reader.h"
    "FixedMap.h"
    "FixedSet.h"
    "FixedVector.h"
    "FS.h"
    "FS_impl.h"
    "FS_internal.h"
    "FTimer.h"
    "intrusive_ptr.h"
    "LocatorAPI.h"
    "LocatorAPI_defs.h"
    "Lock.hpp"
    "log.h"
    "lzhuf.h"
    "lzo_compressor.h"
    "memory_monitor.h"
    "mezz_stringbuffer.h"
    "net_utils.h"
    "os_clipboard.h"
    "PPMd.h"
    "ppmd_compressor.h"
    "PPMdType.h"
    "profiler.h"
    "resource.h"
    "RingBuffer.h"
    "rt_compressor.h"
    "rt_config1x.h"
    "rt_lzo1x.h"
    "rt_lzo_conf.h"
    "rt_lzo_config.h"
    "rt_lzo_dict.h"
    "rt_lzo_ptr.h"
    "rt_lzoconf.h"
    "rt_lzodefs.h"
    "rt_miniacc.h"
    "ScopeLock.hpp"
    "ShaderSourceCRC.h"
    "stdafx.h"
    "stream_reader.h"
    "stream_reader_inline.h"
    "string_concatenations.h"
    "string_concatenations_inline.h"
    "SubAlloc.hpp"
    "TimeUtils.h"
    "vector.h"
    "xr_delegate.h"
    "xr_ini.h"
    "xr_resource.h"
    "xr_shared.h"
    "xr_trims.h"
    "xrCore.h"
    "xrCore_platform.h"
    "xrDebug.h"
    "xrDebug_macros.h"
    "xrMemory.h"
    "xrMemory_align.h"
    "xrMEMORY_POOL.h"
    "xrMemory_pso.h"
    "xrMemory_pure.h"
    "xrMemory_subst_borland.h"
    "xrMemory_subst_msvc.h"
    "xrParams.h"
    "xrPool.h"
    "xrsharedmem.h"
    "xrstring.h"
    "xrSyncronize.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "_compressed_normal.cpp"
    "_math.cpp"
    "_sphere.cpp"
    "_std_extensions.cpp"
    "blackbox/BlackBoxUI.cpp"
    "blackbox/BSUFunctions.cpp"
    "blackbox/CrashHandler.cpp"
#    "blackbox/DiagAssert.cpp"
    "blackbox/GetLoadedModules.cpp"
    "blackbox/IsNT.cpp"
    "blackbox/NT4ProcessInfo.cpp"
    "blackbox/stdafx_.cpp"
    "blackbox/TLHELPProcessInfo.cpp"
    "clsid.cpp"
    "cpuid.cpp"
    "crc32.cpp"
    "DateTime.cpp"
    "dump_string.cpp"
    "file_stream_reader.cpp"
    "FileSystem.cpp"
    "FileSystem_borland.cpp"
    "FS.cpp"
    "FTimer.cpp"
    "LocatorAPI.cpp"
    "LocatorAPI_auth.cpp"
    "LocatorAPI_defs.cpp"
#    "LocatorAPI_Notifications.cpp"
    "Lock.cpp"
    "log.cpp"
    "LzHuf.cpp"
    "lzo_compressor.cpp"
    "memory_allocation_stats.cpp"
    "memory_monitor.cpp"
    "memory_usage.cpp"
    "mezz_stringbuffer.cpp"
    "Model.cpp"
    "NET_utils.cpp"
    "os_clipboard.cpp"
    "ppmd_compressor.cpp"
    "rt_compressor.cpp"
    "rt_compressor9.cpp"
    "rt_lzo1x_1.cpp"
    "rt_lzo1x_9x.cpp"
    "rt_lzo1x_d1.cpp"
    "rt_lzo1x_d2.cpp"
    "rt_lzo1x_d3.cpp"
    "rt_lzo_init.cpp"
    "ScopeLock.cpp"
    "ShaderSourceCRC.cpp"
    "stdafx.cpp"
    "stream_reader.cpp"
    "string_concatenations.cpp"
    "Xr_ini.cpp"
    "xr_shared.cpp"
    "xr_trims.cpp"
    "xrCore.cpp"
#    "xrDebug.cpp"
    "xrDebugNew.cpp"
    "xrMemory.cpp"
    "xrMemory_align.cpp"
    "xrMemory_debug.cpp"
    "xrMemory_POOL.cpp"
    "xrMemory_pso_Copy.cpp"
    "xrMemory_pso_Fill.cpp"
    "xrMemory_pso_Fill32.cpp"
    "xrMemory_subst_borland.cpp"
    "xrMemory_subst_msvc.cpp"
    "xrParams.cpp"
    "xrsharedmem.cpp"
    "xrstring.cpp"
    "xrSyncronize.cpp"
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

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

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

set(ROOT_NAMESPACE xrCore)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/mnt/hdd/Projects/xray-monolith/src/3rd party/optick-git/src;"
    "$ENV{XRAY_16X_LIBS};"
    "$ENV{xrSdkDir}include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:DX10>:"
        "PROFILER_OPTICK"
    ">"
    "$<$<CONFIG:DX11>:"
        "PROFILER_OPTICK"
    ">"
    "$<$<CONFIG:DX8>:"
        "PROFILER_OPTICK"
    ">"
    "$<$<CONFIG:DX9>:"
        "PROFILER_OPTICK"
    ">"
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER;"
        "PROFILER_OPTICK"
    ">"
    "$<$<CONFIG:Release>:"
        "PROFILER_OPTICK"
    ">"
    "$<$<CONFIG:Verified>:"
        "XRCORE_PROFILER;"
        "PROFILER_OPTICK;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "XRCORE_PROFILER;"
        "PROFILER_OPTICK;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "XRCORE_PROFILER;"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "PROFILER_OPTICK;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "XRCORE_PROFILER;"
        "PROFILER_OPTICK;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "XRCORE_PROFILER;"
        "PROFILER_OPTICK;"
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
        /std:c++17;
        /Zc:__cplusplus
    )
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/BlackBoxUI.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/BSUFunctions.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/CrashHandler.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/DiagAssert.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/GetLoadedModules.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/IsNT.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/NT4ProcessInfo.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(blackbox/stdafx_.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(blackbox/TLHELPProcessInfo.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/w;/Y-"
    )
    source_file_compile_options(Model.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    DXERR
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "$ENV{xrSdkDir}libraries;"
    "$ENV{XRAY_16X_LIBS}BugTrap/Bin;"
    "$ENV{xrLibDir}"
)

