#!/usr/bin/env fish
fish_add_path -g /mnt/hdd/msvc_wine/bin/x86/
set -x BIN /mnt/hdd/msvc_wine/bin/x86/
source '/mnt/hdd/Projects/msvc-wine/msvcenv-native.fish'
cmake-gui -S src -B src/build -G "Ninja Multi-Config" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
CC=cl CXX=cl cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
