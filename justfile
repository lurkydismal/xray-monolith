#!/usr/bin/env -S just --justfile

# Build release
default: build-release

# Builds the project in release mode.
[script('fish')]
[working-directory('src/build_msvc')]
build-release:
    source {{ invocation_directory() }}/init.fish
    ninja

[script]
make-build-directory:
    mkdir src/build_msvc

[script]
[working-directory('src/build_msvc')]
generate-build-files:
    source {{ invocation_directory() }}/init.fish
    CC=cl CXX=cl \
        cmake .. \
        -DCMAKE_BUILD_TYPE=DX11 \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
