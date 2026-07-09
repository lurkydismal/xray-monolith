#!/usr/bin/env -S just --justfile

# Build release.
default: build-release

# Builds the project in release mode.
[working-directory('src/build_msvc')]
build-release:
    ninja

# Builds the project documentation target.
[working-directory('src/build_msvc')]
build-docs:
    cmake --build . --target docs

# Creates the out-of-source build directory used for the MSVC build.
make-build-directory:
    mkdir src/build_msvc

# Generates CMake build files for an MSVC Windows DX11 build in the build directory.
[working-directory('src/build_msvc')]
generate-build-files:
    CC=cl CXX=cl \
        cmake .. \
        -DCMAKE_BUILD_TYPE=DX11 \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
