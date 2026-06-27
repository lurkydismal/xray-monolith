cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

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
# Sub-projects
################################################################################
add_subdirectory(../sdk/include/jpeg ${CMAKE_BINARY_DIR}/libjpeg)
add_subdirectory(../sdk/include/ogg ${CMAKE_BINARY_DIR}/libogg_static)
add_subdirectory(../sdk/include/theora ${CMAKE_BINARY_DIR}/libtheora_static)
add_subdirectory(../sdk/include/vorbis ${CMAKE_BINARY_DIR}/libvorbisfile_static)
add_subdirectory(3rd party/crypto)
add_subdirectory(3rd party/cximage)
add_subdirectory(3rd party/DXERR)
add_subdirectory(3rd party/giflib)
add_subdirectory(3rd party/imgui)
add_subdirectory(3rd party/lua-extensions)
add_subdirectory(3rd party/luabind)
add_subdirectory(3rd party/luajit-2/src)
add_subdirectory(3rd party/NVTT)
add_subdirectory(3rd party/ode/contrib/msvc7/ode_default)
add_subdirectory(3rd party/OpenAL-new)
add_subdirectory(3rd party/optick)
add_subdirectory(Layers/xrAPI)
add_subdirectory(Layers/xrRenderPC_R1)
add_subdirectory(Layers/xrRenderPC_R2)
add_subdirectory(Layers/xrRenderPC_R3)
add_subdirectory(Layers/xrRenderPC_R4)
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

