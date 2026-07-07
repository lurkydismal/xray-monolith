#!/usr/bin/env zsh

set -e

# Change to the directory containing this script
cd "$(dirname "${(%):-%N}")"

echo "[LuaJIT] Determine DynASM path and if platform is x64"

DYNASM="../dynasm/dynasm.lua"

if [[ "$1" == "x64" ]]; then
    echo "[LuaJIT] Platform is x64, set -D P64"
    DFLAGS=(-D WIN -D JIT -D FFI -D P64)
else
    echo "[LuaJIT] Platform is not x64"
    DFLAGS=(-D WIN -D JIT -D FFI)
fi

# Build minilua if missing
if [[ ! -f host/minilua.exe ]]; then
    echo "[LuaJIT] Building host/minilua.exe"

    cl \
        /nologo \
        /c \
        /O2 \
        /Ob3 \
        /Oi \
        /Ot \
        /Oy \
        /GT \
        /W3 \
        /fp:precise \
        /MD \
        /GF \
        /GS- \
        /Zi \
        host/minilua.c

    link \
        /nologo \
        /OPT:REF \
        /OPT:ICF \
        /out:host/minilua.exe \
        minilua.obj
fi

# Generate buildvm_arch.h with DynASM
echo "[LuaJIT] Running DynASM to generate host/buildvm_arch.h"

host/minilua.exe \
    "$DYNASM" \
    -LN \
    "${DFLAGS[@]}" \
    -o host/buildvm_arch.h \
    vm_x86.dasc

# Build buildvm if missing
if [[ ! -f host/buildvm.exe ]]; then
    echo "[LuaJIT] Building host/buildvm.exe"

    cl \
        /nologo \
        /c \
        /O2 \
        /Ob3 \
        /Oi \
        /Ot \
        /Oy \
        /GT \
        /W3 \
        /fp:precise \
        /MD \
        /GF \
        /GS- \
        /Zi \
        /I . \
        /I ../dynasm \
        host/buildvm.c \
        host/buildvm_peobj.c \
        host/buildvm_lib.c \
        host/buildvm_asm.c \
        host/buildvm_fold.c

    link \
        /nologo \
        /OPT:REF \
        /OPT:ICF \
        /out:host/buildvm.exe \
        buildvm.obj \
        buildvm_peobj.obj \
        buildvm_lib.obj \
        buildvm_asm.obj \
        buildvm_fold.obj
fi

LIBS=(
    lib_base.c
    lib_math.c
    lib_bit.c
    lib_string.c
    lib_table.c
    lib_io.c
    lib_os.c
    lib_package.c
    lib_debug.c
    lib_jit.c
    lib_ffi.c
)

echo "[LuaJIT] Generating lj_vm.obj and headers"

host/buildvm.exe -m peobj -o lj_vm.obj

host/buildvm.exe -m bcdef -o lj_bcdef.h "${LIBS[@]}"

host/buildvm.exe -m ffdef -o lj_ffdef.h "${LIBS[@]}"

host/buildvm.exe -m libdef -o lj_libdef.h "${LIBS[@]}"

host/buildvm.exe -m recdef -o lj_recdef.h "${LIBS[@]}"

host/buildvm.exe -m vmdef -o jit/vmdef.lua "${LIBS[@]}"

host/buildvm.exe -m folddef -o lj_folddef.h lj_opt_fold.c

echo "[LuaJIT] Generation complete"
