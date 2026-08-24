################################################################################
# CPM / Package manager
################################################################################
include("${CMAKE_CURRENT_LIST_DIR}/CPM.cmake")

################################################################################
# Options
################################################################################
if(BUILD_SHARED_LIBS)
    set(XXHASH_BUILD_ENABLE_INLINE_API OFF)
    set(ZSTD_BUILD_STATIC OFF)
    set(ZSTD_BUILD_SHARED ON)
else()
    set(XXHASH_BUILD_ENABLE_INLINE_API ON)
    set(ZSTD_BUILD_STATIC ON)
    set(ZSTD_BUILD_SHARED OFF)
endif()

################################################################################
# Dependencies
################################################################################
CPMAddPackage("gh:microsoft/GSL@4.2.2")

# Portable SIMD
CPMAddPackage("gh:simd-everywhere/simde@0.8.2")

################################################################################
# stdfunc
################################################################################
# CPMAddPackage(
#     URI "gh:Cyan4973/xxHash@0.8.3"
#     OPTIONS
#         "XXHASH_BUILD_ENABLE_INLINE_API ${XXHASH_BUILD_ENABLE_INLINE_API}"
#         "XXHASH_BUILD_XXHSUM OFF"
#     SOURCE_SUBDIR cmake_unofficial
# )
# CPMAddPackage(
#     URI "gh:google/snappy#1.2.2"
#     OPTIONS
#         "SNAPPY_BUILD_TESTS OFF"
#         "SNAPPY_BUILD_BENCHMARKS OFF"
#         "SNAPPY_INSTALL OFF"
# )
# CPMAddPackage(
#     URI "gh:facebook/zstd@1.5.7"
#     OPTIONS
#         "ZSTD_BUILD_STATIC ${ZSTD_BUILD_STATIC}"
#         "ZSTD_BUILD_SHARED ${ZSTD_BUILD_SHARED}"
#         "ZSTD_BUILD_PROGRAMS OFF"
#         "ZSTD_BUILD_TESTS OFF"
#     SOURCE_SUBDIR build/cmake
# )
# CPMAddPackage("gh:stephenberry/glaze@7.9.1")
# CPMAddPackage(
#     URI "gh:hanickadot/compile-time-regular-expressions@3.11.0"
#     OPTIONS
#         "CTRE_BUILD_TESTS OFF"
#         "CTRE_BUILD_PACKAGE OFF"
#         "CTRE_BUILD_PACKAGE_DEB OFF"
#         "CTRE_BUILD_PACKAGE_RPM OFF"
# )

CPMAddPackage(
    URI "gh:lurkydismal/stdfunc@0.3.0"
    OPTIONS
        "STDFUNC_USE_XXHASH OFF"
        "STDFUNC_USE_SNAPPY OFF"
        "STDFUNC_USE_ZSTD OFF"
        "STDFUNC_USE_GLAZE OFF"
        "STDFUNC_USE_CTRE OFF"
)

################################################################################
# Threading / PPL replacement
################################################################################
# CPMAddPackage(
#     URI "gh:uxlfoundation/oneTBB@2023.1.0"
#     OPTIONS
#         "TBB_TEST OFF"
#         "TBB_ENABLE_IPO ${ENABLE_IPO}"
#         "TBB_INSTALL OFF"
#         "TBB_STRICT OFF"
# )
# if(WIN32)
#     if(IS_CLANG_MINGW OR IS_CLANG_MSVC)
#         target_compile_options(tbb PRIVATE -fexceptions)
#         target_compile_options(tbb PRIVATE -mwaitpkg)
#     endif()
# endif()

################################################################################
# Boost
################################################################################
# boost is a huge project and directly downloading the 'alternate release'
# from github is much faster than recursively cloning the repo.
CPMAddPackage(
  NAME Boost
  VERSION 1.92.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.92.0/boost-1.92.0-cmake.tar.xz
  URL_HASH SHA256=9bed76128d4e46755dbe818487788c6fceb6f72b378f4daa49b7e1e600d9088d
  OPTIONS
    "BOOST_ENABLE_CMAKE ON"
    "BOOST_ENABLE_EXCEPTIONS OFF"
    "BOOST_SKIP_INSTALL_RULES ON"
    "BOOST_INCLUDE_LIBRARIES container\\\;stacktrace"
)

################################################################################
# Logging
################################################################################
# CPMAddPackage("gh:fmtlib/fmt#12.2.0")

################################################################################
# Rust
################################################################################
# CPMAddPackage("gh:corrosion-rs/corrosion@0.6.1")
