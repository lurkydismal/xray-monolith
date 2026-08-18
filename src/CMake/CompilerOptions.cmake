################################################################################
# Global compiler options
################################################################################
foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${cfg}" CFG)

    set(CMAKE_C_FLAGS_${CFG} "")
    set(CMAKE_CXX_FLAGS_${CFG} "")
endforeach()

if(IS_CLANG AND NOT MSVC)
    add_compile_options(
        -Wno-c++11-narrowing
        -Wno-microsoft-cast
        -Wno-microsoft-enum-value
        -Wno-invalid-offsetof
        -fms-extensions
        # -fms-compatibility
        -fdelayed-template-parsing
        -march=native
    )
elseif(IS_CLANG AND MSVC)
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
    if(MSVC)
        set(XRAY_OPTIMIZATION_FLAG /Od)
    else()
        set(XRAY_OPTIMIZATION_FLAG -Od)
    endif()
else()
    if(MSVC)
        set(XRAY_OPTIMIZATION_FLAG /O2)
    else()
        set(XRAY_OPTIMIZATION_FLAG -O3)
    endif()
endif()
