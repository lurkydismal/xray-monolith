set(PROJECT_NAME imgui)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "imconfig.h"
    "imgui.cpp"
    "imgui.h"
    "imgui_custom.h"
    "imgui_demo.cpp"
    "imgui_draw.cpp"
    "imgui_internal.h"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"
    "imstb_rectpack.h"
    "imstb_textedit.h"
    "imstb_truetype.h"
)
source_group("" FILES ${no_group_source_files})

set(backends
    "backends/imgui_impl_dx10.cpp"
    "backends/imgui_impl_dx10.h"
    "backends/imgui_impl_dx11.cpp"
    "backends/imgui_impl_dx11.h"
    "backends/imgui_impl_dx9.cpp"
    "backends/imgui_impl_dx9.h"
    "imgui_custom.cpp"
)
source_group("backends" FILES ${backends})

set(ALL_FILES
    ${no_group_source_files}
    ${backends}
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

set(ROOT_NAMESPACE imgui)

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
# )
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
    "${CMAKE_CURRENT_SOURCE_DIR}/."
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:DX10>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX10AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX11>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX11AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX8>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX8AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX9>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:DX9AVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER;"
        "NDEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:ReleaseAVX>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:Verified>:"
        "_DEBUG;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "_DEBUG;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "_DEBUG;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "_DEBUG;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "_DEBUG;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "_CONSOLE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(IS_CLANG_CL_MINGW OR IS_CLANG_CL_MSVC)
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
            /Oy-;
            /Gy;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /Zi
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oy-;
            /Gy;
            /Zi
        >
        /permissive-;
        /std:c++latest;
        /sdl;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
        >
        $<$<CONFIG:DX10AVX>:
        >
        $<$<CONFIG:DX11>:
        >
        $<$<CONFIG:DX11AVX>:
        >
        $<$<CONFIG:DX8>:
        >
        $<$<CONFIG:DX8AVX>:
        >
        $<$<CONFIG:DX9>:
        >
        $<$<CONFIG:DX9AVX>:
        >
        $<$<CONFIG:ProfiledDX11>:
        >
        $<$<CONFIG:Release>:
        >
        $<$<CONFIG:ReleaseAVX>:
        >
        /SUBSYSTEM:CONSOLE
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
    xrCore
)
