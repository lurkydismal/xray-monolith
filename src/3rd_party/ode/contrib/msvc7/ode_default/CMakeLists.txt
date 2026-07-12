set(PROJECT_NAME ode)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "ReadMe.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "../../../include/ode/collision.h"
    "../../../include/ode/collision_space.h"
    "../../../include/ode/collision_trimesh.h"
    "../../../include/ode/common.h"
    "../../../include/ode/compatibility.h"
    "../../../include/ode/config.h"
    "../../../include/ode/contact.h"
    "../../../include/ode/error.h"
    "../../../include/ode/export-dif.h"
    "../../../include/ode/geom.h"
    "../../../include/ode/mass.h"
    "../../../include/ode/matrix.h"
    "../../../include/ode/memory.h"
    "../../../include/ode/misc.h"
    "../../../include/ode/objects.h"
    "../../../include/ode/ode.h"
    "../../../include/ode/odecpp.h"
    "../../../include/ode/odecpp_collision.h"
    "../../../include/ode/odemath.h"
    "../../../include/ode/rotation.h"
    "../../../include/ode/space.h"
    "../../../include/ode/timer.h"
    "../../../ode/src/array.h"
    "../../../ode/src/Bounder33.h"
    "../../../ode/src/collision_kernel.h"
    "../../../ode/src/collision_space_internal.h"
    "../../../ode/src/collision_std.h"
    "../../../ode/src/collision_transform.h"
    "../../../ode/src/collision_trimesh_internal.h"
    "../../../ode/src/collision_util.h"
    "../../../ode/src/geom_internal.h"
    "../../../ode/src/joint.h"
    "../../../ode/src/lcp.h"
    "../../../ode/src/Lcp33.h"
    "../../../ode/src/mat.h"
    "../../../ode/src/objects.h"
    "../../../ode/src/obstack.h"
    "../../../ode/src/quickstep.h"
    "../../../ode/src/stack.h"
    "../../../ode/src/step.h"
    "../../../ode/src/StepJointInternal.h"
    "../../../ode/src/testing.h"
    "../../../ode/src/util.h"
    "de_padf_integration.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../../../config/msvcdefs.def"
    "../../../ode/src/array.cpp"
    "../../../ode/src/Bounder33.cpp"
    "../../../ode/src/collision_kernel.cpp"
    "../../../ode/src/collision_quadtreespace.cpp"
    "../../../ode/src/collision_space.cpp"
    "../../../ode/src/collision_std.cpp"
    "../../../ode/src/collision_transform.cpp"
    "../../../ode/src/collision_util.cpp"
    "../../../ode/src/error.cpp"
    "../../../ode/src/export-dif.cpp"
    "../../../ode/src/fastdot.c"
    "../../../ode/src/fastldlt.c"
    "../../../ode/src/fastlsolve.c"
    "../../../ode/src/fastltsolve.c"
    "../../../ode/src/joint.cpp"
    "../../../ode/src/lcp.cpp"
    "../../../ode/src/mass.cpp"
    "../../../ode/src/mat.cpp"
    "../../../ode/src/matrix.cpp"
    "../../../ode/src/memory.cpp"
    "../../../ode/src/misc.cpp"
    "../../../ode/src/obstack.cpp"
    "../../../ode/src/ode.cpp"
    "../../../ode/src/odemath.cpp"
    "../../../ode/src/quickstep.cpp"
    "../../../ode/src/rotation.cpp"
    "../../../ode/src/step.cpp"
    "../../../ode/src/stepfast.cpp"
    "../../../ode/src/StepJointInternal.cpp"
    "../../../ode/src/testing.cpp"
    "../../../ode/src/timer.cpp"
    "../../../ode/src/util.cpp"
    "de_padf_integration.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
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
use_props(${PROJECT_NAME} DX10             "../../../../../Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../../../../../Common.cmake")
use_props(${PROJECT_NAME} DX11             "../../../../../Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../../../../../Common.cmake")
use_props(${PROJECT_NAME} DX8              "../../../../../Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../../../../../Common.cmake")
use_props(${PROJECT_NAME} DX9              "../../../../../Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../../../../../Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../../../../../Common.cmake")
use_props(${PROJECT_NAME} Release          "../../../../../Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../../../../../Common.cmake")
use_props(${PROJECT_NAME} Verified         "../../../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../../../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../../../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../../../../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../../../../../Common.cmake")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "AtlProj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../_build/lib/my"
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
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../include"
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
    "_WINDOWS;"
    "NDEBUG;"
    "dSINGLE;"
    "MSVC;"
    "dNODEBUG;"
    "_SECURE_SCL=0"
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7
        >
        $<$<CONFIG:Release>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Z7;
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
            /Z7;
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
            /ZI
        >
        $<$<CONFIG:VerifiedDX11>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Z7
        >
        $<$<CONFIG:VerifiedDX8>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI
        >
        $<$<CONFIG:VerifiedDX9>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI
        >
        /std:c++17;
        /wd4100;
        /wd4505
    )
    string(CONCAT FILE_CL_OPTIONS
        "/wd4244"
    )
    source_file_compile_options(../../../ode/src/collision_quadtreespace.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/wd4244"
    )
    source_file_compile_options(../../../ode/src/collision_std.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Post build events
################################################################################
if(WIN32 AND FALSE)
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMANDS
        COMMAND             $<CONFIG:DX10> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND          $<CONFIG:DX10AVX> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND             $<CONFIG:DX11> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND          $<CONFIG:DX11AVX> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND              $<CONFIG:DX8> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND           $<CONFIG:DX8AVX> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND              $<CONFIG:DX9> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND           $<CONFIG:DX9AVX> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND     $<CONFIG:ProfiledDX11> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND          $<CONFIG:Release> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND       $<CONFIG:ReleaseAVX> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND         $<CONFIG:Verified> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND     $<CONFIG:VerifiedDX11> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND $<CONFIG:VerifiedDX11ASAN> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND      $<CONFIG:VerifiedDX8> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMAND      $<CONFIG:VerifiedDX9> regsvr32 /s /c "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>"
        COMMENT "Performing registration"
    )
endif()

