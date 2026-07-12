set(PROJECT_NAME xrCore)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../3rd_party/fastdelegate/fastdelegate.h"
    "../3rd_party/robin_hood/robin_hood.h"
    "../build_config_defines.h"
    "ChooseTypes.H"
    "client_id.h"
    "TimeUtils.h"
    "xrParams.cpp"
    "xrParams.h"
)
source_group("" FILES ${no_group_source_files})

set(Compression__lz
    "LzHuf.cpp"
    "lzhuf.h"
)
source_group("Compression\\lz" FILES ${Compression__lz})

set(Compression__lzo
    "lzo_compressor.cpp"
    "lzo_compressor.h"
    "rt_config1x.h"
    "rt_lzo1x.h"
    "rt_lzo1x_1.cpp"
    "rt_lzo1x_9x.cpp"
    "rt_lzo1x_d1.cpp"
    "rt_lzo1x_d2.cpp"
    "rt_lzo1x_d3.cpp"
    "rt_lzo_conf.h"
    "rt_lzo_config.h"
    "rt_lzo_dict.h"
    "rt_lzo_init.cpp"
    "rt_lzo_ptr.h"
    "rt_lzoconf.h"
    "rt_lzodefs.h"
    "rt_miniacc.h"
)
source_group("Compression\\lzo" FILES ${Compression__lzo})

set(Compression__ppmd
    "ppmd_compressor.cpp"
    "ppmd_compressor.h"
)
source_group("Compression\\ppmd" FILES ${Compression__ppmd})

set(Compression__ppmd__common
    "PPMd.h"
    "PPMdType.h"
)
source_group("Compression\\ppmd\\common" FILES ${Compression__ppmd__common})

set(Compression__ppmd__core
    "Coder.hpp"
    "Model.cpp"
)
source_group("Compression\\ppmd\\core" FILES ${Compression__ppmd__core})

set(Compression__ppmd__core__allocator
    "SubAlloc.hpp"
)
source_group("Compression\\ppmd\\core\\allocator" FILES ${Compression__ppmd__core__allocator})

set(Compression__ppmd__stream
    "compression_ppmd_stream.h"
    "compression_ppmd_stream_inline.h"
)
source_group("Compression\\ppmd\\stream" FILES ${Compression__ppmd__stream})

set(Compression__rt
    "rt_compressor.cpp"
    "rt_compressor.h"
    "rt_compressor9.cpp"
)
source_group("Compression\\rt" FILES ${Compression__rt})

set(Debug_core
    "../3rd_party/stackwalker/include/StackWalker.h"
    "xrDebug.h"
    "xrDebug_macros.h"
    "xrDebugNew.cpp"
)
source_group("Debug core" FILES ${Debug_core})

set(Debug_core__BlackBox
    "blackbox/BlackBoxUI.cpp"
    "blackbox/BSUFunctions.cpp"
    "blackbox/BugslayerUtil.h"
    "blackbox/CrashHandler.cpp"
    "blackbox/CrashHandler.h"
    "blackbox/DiagAssert.h"
    "blackbox/GetLoadedModules.cpp"
    "blackbox/Internal.h"
    "blackbox/IsNT.cpp"
    "blackbox/NT4ProcessInfo.cpp"
    "blackbox/stdafx_.cpp"
    "blackbox/stdafx_.h"
    "blackbox/SymbolEngine.h"
    "blackbox/TLHELPProcessInfo.cpp"
    "blackbox/WarningsOff.h"
    "blackbox/WarningsOn.h"
)
if(ENABLE_DEBUG_OLD_RUNTIME)
    list(APPEND Debug_core blackbox/DiagAssert.cpp)
endif()
source_group("Debug core\\BlackBox" FILES ${Debug_core__BlackBox})

set(FS
    "DateTime.cpp"
    "DateTime.hpp"
    "FileSystem.cpp"
    "FileSystem.h"
    "FileSystem_borland.cpp"
    "FS.cpp"
    "FS.h"
    "FS_impl.h"
    "FS_internal.h"
    "LocatorAPI.cpp"
    "LocatorAPI.h"
    "LocatorAPI_auth.cpp"
    "LocatorAPI_defs.cpp"
    "LocatorAPI_defs.h"
    "log.cpp"
    "log.h"
    "NET_utils.cpp"
    "net_utils.h"
    "RingBuffer.h"
    "Xr_ini.cpp"
    "xr_ini.h"
)
if(ENABLE_DEBUG_OLD_RUNTIME)
    list(APPEND FS
        LocatorAPI_Notifications.cpp
        LocatorAPI_Notifications.h
    )
endif()
source_group("FS" FILES ${FS})

set(FS__file_stream_reader
    "file_stream_reader.cpp"
    "file_stream_reader.h"
)
source_group("FS\\file_stream_reader" FILES ${FS__file_stream_reader})

set(FS__stream_reader
    "stream_reader.cpp"
    "stream_reader.h"
    "stream_reader_inline.h"
)
source_group("FS\\stream_reader" FILES ${FS__stream_reader})

set(Kernel
    "_global_functions.h"
    "_noncopyable.h"
    "_thread_types.h"
    "FTimer.cpp"
    "FTimer.h"
    "resource.h"
    "stdafx.cpp"
    "stdafx.h"
    "xr_delegate.h"
    "xrCore.cpp"
    "xrCore.h"
    "xrCore_platform.h"
)
source_group("Kernel" FILES ${Kernel})

set(Math
    "_bitwise.h"
    "_color.h"
    "_compressed_normal.cpp"
    "_compressed_normal.h"
    "_cylinder.h"
    "_fbox.h"
    "_fbox2.h"
    "_flags.h"
    "_math.cpp"
    "_math.h"
    "_matrix.h"
    "_matrix33.h"
    "_obb.h"
    "_plane.h"
    "_plane2.h"
    "_quaternion.h"
    "_random.h"
    "_rect.h"
    "_sphere.cpp"
    "_sphere.h"
    "_types.h"
    "_vector2.h"
    "_vector3d.h"
    "_vector3d_ext.h"
    "_vector4.h"
    "dump_string.cpp"
    "dump_string.h"
    "vector.h"
)
source_group("Math" FILES ${Math})

set(Math__CPU
    "cpuid.cpp"
    "cpuid.h"
)
source_group("Math\\CPU" FILES ${Math__CPU})

set(Math__Extensions
    "_std_extensions.cpp"
    "_std_extensions.h"
    "_stl_extensions.h"
    "_type_traits.h"
    "clsid.cpp"
    "clsid.h"
    "string_concatenations.cpp"
    "string_concatenations.h"
    "string_concatenations_inline.h"
    "xr_trims.cpp"
    "xr_trims.h"
)
source_group("Math\\Extensions" FILES ${Math__Extensions})

set(Math__Extensions__buffer_vector
    "buffer_vector.h"
    "buffer_vector_inline.h"
)
source_group("Math\\Extensions\\buffer_vector" FILES ${Math__Extensions__buffer_vector})

set(Math__STLext
    "FixedMap.h"
    "FixedSet.h"
    "FixedVector.h"
    "xrPool.h"
)
source_group("Math\\STLext" FILES ${Math__STLext})

set(Memory_manager
    "memory_allocation_stats.cpp"
    "memory_usage.cpp"
    "xrMemory.cpp"
    "xrMemory.h"
    "xrMemory_align.cpp"
    "xrMemory_align.h"
    "xrMemory_debug.cpp"
    "xrMemory_POOL.cpp"
    "xrMemory_POOL.h"
    "xrMemory_pso.h"
    "xrMemory_pso_Copy.cpp"
    "xrMemory_pso_Fill.cpp"
    "xrMemory_pso_Fill32.cpp"
    "xrMemory_pure.h"
    "xrMemory_subst_borland.cpp"
    "xrMemory_subst_borland.h"
    "xrMemory_subst_msvc.cpp"
    "xrMemory_subst_msvc.h"
)
source_group("Memory manager" FILES ${Memory_manager})

set(OS
    "os_clipboard.cpp"
    "os_clipboard.h"
)
source_group("OS" FILES ${OS})

set(Profiling
    "profiler.h"
)
source_group("Profiling" FILES ${Profiling})

set(Threading
    "Lock.cpp"
    "Lock.hpp"
    "ScopeLock.cpp"
    "ScopeLock.hpp"
    "xrSyncronize.cpp"
    "xrSyncronize.h"
)
source_group("Threading" FILES ${Threading})

set(intrusive_ptr
    "intrusive_ptr.h"
)
source_group("intrusive_ptr" FILES ${intrusive_ptr})

set(memory_monitor
    "memory_monitor.cpp"
    "memory_monitor.h"
)
source_group("memory_monitor" FILES ${memory_monitor})

set(shared_memory/string_library
    "crc32.cpp"
    "mezz_stringbuffer.cpp"
    "mezz_stringbuffer.h"
    "ShaderSourceCRC.cpp"
    "ShaderSourceCRC.h"
    "xr_resource.h"
    "xr_shared.cpp"
    "xr_shared.h"
    "xrsharedmem.cpp"
    "xrsharedmem.h"
    "xrstring.cpp"
    "xrstring.h"
)
source_group("shared memory/string library" FILES ${shared_memory/string_library})

set(ALL_FILES
    ${no_group_source_files}
    ${Compression__lz}
    ${Compression__lzo}
    ${Compression__ppmd}
    ${Compression__ppmd__common}
    ${Compression__ppmd__core}
    ${Compression__ppmd__core__allocator}
    ${Compression__ppmd__stream}
    ${Compression__rt}
    ${Debug_core}
    ${Debug_core__BlackBox}
    ${FS}
    ${FS__file_stream_reader}
    ${FS__stream_reader}
    ${Kernel}
    ${Math}
    ${Math__CPU}
    ${Math__Extensions}
    ${Math__Extensions__buffer_vector}
    ${Math__STLext}
    ${Memory_manager}
    ${OS}
    ${Profiling}
    ${Threading}
    ${intrusive_ptr}
    ${memory_monitor}
    ${shared_memory/string_library}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/stackwalker/lib/StackWalker.lib"
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

set(ROOT_NAMESPACE xrCore)

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
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/optick-git/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/BugTrap/Bin;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my/"
)

