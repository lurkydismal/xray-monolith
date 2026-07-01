#!/usr/bin/env fish
set -x BIN /mnt/hdd/msvc_wine/bin/x86/
source '/mnt/hdd/Projects/msvc-wine/msvcenv-native.fish'
cmake-gui -S src -B src/build -G "Ninja Multi-Config" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
