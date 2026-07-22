cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(engine-vs2022 C CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "DX10"
    "DX10AVX"
    "DX11"
    "DX11AVX"
    "DX8"
    "DX8AVX"
    "DX9"
    "DX9AVX"
    "ProfiledDX11"
    "Release"
    "ReleaseAVX"
    "Verified"
    "VerifiedDX11"
    "VerifiedDX11ASAN"
    "VerifiedDX8"
    "VerifiedDX9"
    CACHE STRING "" FORCE
)

set(DX8_TYPES  DX8 DX8AVX VerifiedDX8)
set(DX9_TYPES  DX9 DX9AVX VerifiedDX9)
set(DX10_TYPES DX10 DX10AVX VerifiedDX10)
set(DX11_TYPES DX11 DX11AVX VerifiedDX11)

set(IS_DX8  FALSE)
set(IS_DX9  FALSE)
set(IS_DX10 FALSE)
set(IS_DX11 FALSE)

if(CMAKE_BUILD_TYPE IN_LIST DX8_TYPES)
    set(IS_DX8 TRUE)
elseif(CMAKE_BUILD_TYPE IN_LIST DX9_TYPES)
    set(IS_DX9 TRUE)
elseif(CMAKE_BUILD_TYPE IN_LIST DX10_TYPES)
    set(IS_DX10 TRUE)
elseif(CMAKE_BUILD_TYPE IN_LIST DX11_TYPES)
    set(IS_DX11 TRUE)
endif()

# TODO: Refactor and rename
if(CMAKE_BUILD_TYPE MATCHES "^(Release|Release-AVX|ProfiledDX11|Verified|VerifiedDX11|VerifiedDX11ASAN)$")
    message(STATUS "Legacy debug runtime: disabled")
    set(ENABLE_DEBUG_OLD_RUNTIME FALSE)
else()
    message(STATUS "Legacy debug runtime: enabled")
    set(ENABLE_DEBUG_OLD_RUNTIME TRUE)
endif()

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DX10 "")
    set(CMAKE_C_FLAGS_DX10AVX "")
    set(CMAKE_C_FLAGS_DX11 "")
    set(CMAKE_C_FLAGS_DX11AVX "")
    set(CMAKE_C_FLAGS_DX8 "")
    set(CMAKE_C_FLAGS_DX8AVX "")
    set(CMAKE_C_FLAGS_DX9 "")
    set(CMAKE_C_FLAGS_DX9AVX "")
    set(CMAKE_C_FLAGS_PROFILEDDX11 "")
    set(CMAKE_C_FLAGS_RELEASE "")
    set(CMAKE_C_FLAGS_RELEASEAVX "")
    set(CMAKE_C_FLAGS_VERIFIED "")
    set(CMAKE_C_FLAGS_VERIFIEDDX11 "")
    set(CMAKE_C_FLAGS_VERIFIEDDX11ASAN "")
    set(CMAKE_C_FLAGS_VERIFIEDDX8 "")
    set(CMAKE_C_FLAGS_VERIFIEDDX9 "")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DX10 "")
    set(CMAKE_CXX_FLAGS_DX10AVX "")
    set(CMAKE_CXX_FLAGS_DX11 "")
    set(CMAKE_CXX_FLAGS_DX11AVX "")
    set(CMAKE_CXX_FLAGS_DX8 "")
    set(CMAKE_CXX_FLAGS_DX8AVX "")
    set(CMAKE_CXX_FLAGS_DX9 "")
    set(CMAKE_CXX_FLAGS_DX9AVX "")
    set(CMAKE_CXX_FLAGS_PROFILEDDX11 "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS_RELEASEAVX "")
    set(CMAKE_CXX_FLAGS_VERIFIED "")
    set(CMAKE_CXX_FLAGS_VERIFIEDDX11 "")
    set(CMAKE_CXX_FLAGS_VERIFIEDDX11ASAN "")
    set(CMAKE_CXX_FLAGS_VERIFIEDDX8 "")
    set(CMAKE_CXX_FLAGS_VERIFIEDDX9 "")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -clang:-Wno-c++11-narrowing
        -clang:-Wno-microsoft-cast
        -clang:-Wno-microsoft-enum-value
        -clang:-Wno-invalid-offsetof
        -clang:-fms-extensions
        -clang:-fms-compatibility
        -clang:-fdelayed-template-parsing
        -clang:-msse4.2
    )
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DX10 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX10 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX10 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX10 "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DX10AVX "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX10AVX "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX10AVX "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX10AVX "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DX11 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX11 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX11 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX11 "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DX11AVX "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX11AVX "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX11AVX "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX11AVX "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DX8 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX8 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX8 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX8 "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DX8AVX "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX8AVX "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX8AVX "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX8AVX "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DX9 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX9 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX9 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX9 "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DX9AVX "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DX9AVX "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DX9AVX "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DX9AVX "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_PROFILEDDX11 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_PROFILEDDX11 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_PROFILEDDX11 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_PROFILEDDX11 "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASEAVX "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASEAVX "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASEAVX "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASEAVX "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_VERIFIED "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_VERIFIED "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_VERIFIED "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_VERIFIED "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_VERIFIEDDX11 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_VERIFIEDDX11 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_VERIFIEDDX11 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_VERIFIEDDX11 "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_VERIFIEDDX11ASAN "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_VERIFIEDDX11ASAN "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_VERIFIEDDX11ASAN "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_VERIFIEDDX11ASAN "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_VERIFIEDDX8 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_VERIFIEDDX8 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_VERIFIEDDX8 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_VERIFIEDDX8 "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_VERIFIEDDX9 "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_VERIFIEDDX9 "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_VERIFIEDDX9 "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_VERIFIEDDX9 "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# IPO / LTO
################################################################################
option(ENABLE_IPO "Enable interprocedural optimization (LTO)" OFF)

if(ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported)

    if(ipo_supported)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    endif()
endif()

################################################################################
# CPM / Package manager
################################################################################
include("${CMAKE_SOURCE_DIR}/CMake/CPM.cmake")

################################################################################
# Dependencies
################################################################################
CPMAddPackage("gh:fmtlib/fmt#12.2.0")
CPMAddPackage(
    URI "gh:Cyan4973/xxHash@0.8.3"
    OPTIONS
        "XXHASH_BUILD_ENABLE_INLINE_API OFF"
        "XXHASH_BUILD_XXHSUM OFF"
    SOURCE_SUBDIR cmake_unofficial
)
CPMAddPackage(
    URI "gh:google/snappy#1.2.2"
    OPTIONS
        "SNAPPY_BUILD_TESTS OFF"
        "SNAPPY_BUILD_BENCHMARKS OFF"
        "SNAPPY_INSTALL OFF"
)
CPMAddPackage(
    URI "gh:facebook/zstd@1.5.7"
    OPTIONS
        "ZSTD_BUILD_STATIC OFF"
        "ZSTD_BUILD_SHARED ON"
        "ZSTD_BUILD_PROGRAMS OFF"
    SOURCE_SUBDIR build/cmake
)
CPMAddPackage("gh:stephenberry/glaze@7.9.1")
# FIX: Add package
# add_subdirectory(3rd_party/ctre)
add_subdirectory(3rd_party/stdfunc)
CPMAddPackage(
    URI "gh:gabime/spdlog#v2.x"
    OPTIONS
        "SPDLOG_FMT_EXTERNAL ON"
)
if(MSVC)
    target_compile_options(spdlog PRIVATE /EHsc)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(spdlog PRIVATE -fexceptions)
endif()

################################################################################
# Sub-projects
################################################################################
add_subdirectory(../sdk/include/jpeg ${CMAKE_BINARY_DIR}/libjpeg)
add_subdirectory(../sdk/include/ogg ${CMAKE_BINARY_DIR}/libogg_static)
add_subdirectory(../sdk/include/theora ${CMAKE_BINARY_DIR}/libtheora_static)
add_subdirectory(../sdk/include/vorbis ${CMAKE_BINARY_DIR}/libvorbisfile_static)
add_subdirectory("3rd_party/crypto")
add_subdirectory("3rd_party/cximage")
add_subdirectory("3rd_party/DXERR")
add_subdirectory("3rd_party/giflib")
add_subdirectory("3rd_party/imgui")
add_subdirectory("3rd_party/lua-extensions")
add_subdirectory("3rd_party/luabind")
add_subdirectory("3rd_party/luajit-2/src")
add_subdirectory("3rd_party/NVTT")
add_subdirectory("3rd_party/ode/contrib/msvc7/ode_default")
add_subdirectory("3rd_party/OpenAL-new")
add_subdirectory("3rd_party/optick")
add_subdirectory(Layers/xrAPI)

if(IS_DX8)
    message(STATUS "Selected renderer: DirectX 8 (PC_R1)")
    set(RENDERER_LIB xrRender_R1)
    set(RENDERER_DIR Layers/xrRenderPC_R1)
elseif(IS_DX9)
    message(STATUS "Selected renderer: DirectX 9 (PC_R2)")
    set(RENDERER_LIB xrRender_R2)
    set(RENDERER_DIR Layers/xrRenderPC_R2)
elseif(IS_DX10)
    message(STATUS "Selected renderer: DirectX 10 (PC_R3)")
    set(RENDERER_LIB xrRender_R3)
    set(RENDERER_DIR Layers/xrRenderPC_R3)
elseif(IS_DX11)
    message(STATUS "Selected renderer: DirectX 11 (PC_R4)")
    set(RENDERER_LIB xrRender_R4)
    set(RENDERER_DIR Layers/xrRenderPC_R4)
else()
    message(FATAL_ERROR "No renderer selected")
endif()

add_subdirectory(${RENDERER_DIR})

add_subdirectory(ReShadeCompat)
add_subdirectory(xrCDB)
add_subdirectory(xrCore)
add_subdirectory(xrCPU_Pipe)
add_subdirectory(xrEngine)
add_subdirectory(xrGame)
add_subdirectory(xrNetServer)
add_subdirectory(xrParticles)
add_subdirectory(xrPhysics)
add_subdirectory(xrSound)
add_subdirectory(xrXMLParser)


################################################################################
# Unit testing support
################################################################################
# Include the project test integration after production targets are declared so
# test executables can link against existing libraries without adding test files
# to any production target.
include(CMake/XRayTesting.cmake)

option(BUILD_DOCS "Enable documentation target" ON)

if(BUILD_DOCS)
    find_package(Doxygen QUIET)
    find_program(UV_EXECUTABLE uv)
    find_program(MAKE_EXECUTABLE NAMES make gmake)

    if(DOXYGEN_FOUND AND UV_EXECUTABLE AND MAKE_EXECUTABLE)
        if(DOXYGEN_DOT_FOUND)
            message(STATUS "Graphviz support enabled")
        else()
            message(STATUS "Graphviz not found; graphs disabled")
        endif()

        set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/..")

        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_ROOT}/Doxyfile
            COMMAND ${UV_EXECUTABLE} sync
            COMMAND ${CMAKE_COMMAND} -E chdir
                    ${PROJECT_ROOT}/docs
                    ${UV_EXECUTABLE} run ${MAKE_EXECUTABLE} html
            WORKING_DIRECTORY ${PROJECT_ROOT}
            COMMENT "Generating documentation"
        )
    else()
        message(STATUS "Documentation target disabled (missing Doxygen, uv, or make)")
    endif()
endif()
