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
    cmake .. \
        -DCMAKE_BUILD_TYPE=DX11 \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -G "Ninja" \
        --toolchain ../../clang-cl-msvc-x64.cmake

# Check Doxygen documentation comment coverage.
[working-directory('docs')]
check-docs-coverage:
    uv run doc-coverage.py

# TODO: Comment
scan-build target="":
    if [ -n "{{ target }}" ]; then \
        scan-build -enable-checker core,security,nullability,deadcode,cplusplus,optin --exclude sdk --exclude 'src/3rd_party' cmake --build src/build_msvc --target '{{ target }}' --clean-first; \
    else \
        scan-build -enable-checker core,security,nullability,deadcode,cplusplus,optin --exclude sdk --exclude 'src/3rd_party' cmake --build src/build_msvc --clean-first; \
    fi
