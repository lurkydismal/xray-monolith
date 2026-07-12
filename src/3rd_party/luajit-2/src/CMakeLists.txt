set(PROJECT_NAME LuaJIT-2)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "vm_x86.dasc"
)
source_group("" FILES ${no_group_source_files})

set(Sources
    "lib_aux.c"
    "lib_base.c"
    "lib_bit.c"
    "lib_debug.c"
    "lib_ffi.c"
    "lib_init.c"
    "lib_io.c"
    "lib_jit.c"
    "lib_math.c"
    "lib_os.c"
    "lib_package.c"
    "lib_string.c"
    "lib_table.c"
    "lj_alloc.c"
    "lj_api.c"
    "lj_asm.c"
    "lj_bc.c"
    "lj_bcread.c"
    "lj_bcwrite.c"
    "lj_carith.c"
    "lj_ccall.c"
    "lj_ccallback.c"
    "lj_cconv.c"
    "lj_cdata.c"
    "lj_char.c"
    "lj_clib.c"
    "lj_cparse.c"
    "lj_crecord.c"
    "lj_ctype.c"
    "lj_debug.c"
    "lj_dispatch.c"
    "lj_err.c"
    "lj_ffrecord.c"
    "lj_func.c"
    "lj_gc.c"
    "lj_gdbjit.c"
    "lj_ir.c"
    "lj_lex.c"
    "lj_lib.c"
    "lj_load.c"
    "lj_mcode.c"
    "lj_meta.c"
    "lj_obj.c"
    "lj_opt_dce.c"
    "lj_opt_fold.c"
    "lj_opt_loop.c"
    "lj_opt_mem.c"
    "lj_opt_narrow.c"
    "lj_opt_sink.c"
    "lj_opt_split.c"
    "lj_parse.c"
    "lj_record.c"
    "lj_snap.c"
    "lj_state.c"
    "lj_str.c"
    "lj_strscan.c"
    "lj_tab.c"
    "lj_trace.c"
    "lj_udata.c"
    "lj_vmevent.c"
    "lj_vmmath.c"
    "xr_alloc.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${no_group_source_files}
    ${Sources}
)

add_library(${PROJECT_NAME} STATIC
    ${ALL_FILES}
)

################################################################################
# Target
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "3rd_party")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} DX10             "../../../Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../../../Common.cmake")
use_props(${PROJECT_NAME} DX11             "../../../Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../../../Common.cmake")
use_props(${PROJECT_NAME} DX8              "../../../Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../../../Common.cmake")
use_props(${PROJECT_NAME} DX9              "../../../Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../../../Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../../../Common.cmake")
use_props(${PROJECT_NAME} Release          "../../../Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../../../Common.cmake")
use_props(${PROJECT_NAME} Verified         "../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../../../Common.cmake")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME "lua51"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
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
    INTERPROCEDURAL_OPTIMIZATION_RELEASE          "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASEAVX       "TRUE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/host"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "WIN32;"
    "NDEBUG;"
    "_CRT_SECURE_NO_DEPRECATE"
)
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
    "WIN32;"
    "NDEBUG;"
    "_CRT_SECURE_NO_DEPRECATE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:DX10AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:DX11>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:DX11AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:DX8>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:DX8AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:DX9>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:DX9AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:ProfiledDX11>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-
        >
        $<$<CONFIG:Release>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:ReleaseAVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Ob3
        >
        $<$<CONFIG:Verified>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy
        >
        $<$<CONFIG:VerifiedDX11>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy
        >
        $<$<CONFIG:VerifiedDX8>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy
        >
        $<$<CONFIG:VerifiedDX9>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy
        >
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /DEBUG:FULL
    )
endif()

################################################################################
# Pre build events
################################################################################
add_custom_command_if(
    TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMANDS
    COMMENT "Ensuring LuaJIT generated files exist"
)
################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "lj_vm.obj"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

