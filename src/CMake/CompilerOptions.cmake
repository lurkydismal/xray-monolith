################################################################################
# Global compiler options
################################################################################
# TODO: Refactor
if(TRUE)
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

# NOTE: With this
# foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
#     string(TOUPPER "${cfg}" CFG)
#
#     set(CMAKE_C_FLAGS_${CFG} "" CACHE STRING "" FORCE)
#     set(CMAKE_CXX_FLAGS_${CFG} "" CACHE STRING "" FORCE)
# endforeach()

if(IS_CLANG_MINGW OR IS_CLANG_MSVC)
    set(CMAKE_CXX_STANDARD 26)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)

    add_compile_options(
        -Wno-c++11-narrowing
        -Wno-microsoft-cast
        -Wno-microsoft-enum-value
        -Wno-invalid-offsetof
        -fms-extensions
        -fms-compatibility
        -fdelayed-template-parsing
        -march=native
    )
elseif(IS_CLANG_CL_MINGW OR IS_CLANG_CL_MSVC)
    add_compile_options(
        -clang:-Wno-c++11-narrowing
        -clang:-Wno-microsoft-cast
        -clang:-Wno-microsoft-enum-value
        -clang:-Wno-invalid-offsetof
        -clang:-fms-extensions
        -clang:-fms-compatibility
        -clang:-fdelayed-template-parsing
        -clang:-march=native
    )
endif()

if(DISABLE_OPTIMIZATIONS)
    if(CLANG_CL_MINGW OR CLANG_CL_MSVC)
        set(XRAY_OPTIMIZATION_FLAG /Od)
    else()
        set(XRAY_OPTIMIZATION_FLAG -O0)
    endif()
else()
    if(CLANG_CL_MINGW OR CLANG_CL_MSVC)
        set(XRAY_OPTIMIZATION_FLAG /O2)
    else()
        set(XRAY_OPTIMIZATION_FLAG -O3)
    endif()
endif()
