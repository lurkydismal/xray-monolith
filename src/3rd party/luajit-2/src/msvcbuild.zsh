#!/usr/bin/env zsh

set -e

# Change to the directory containing this script
cd "$(dirname "${(%):-%N}")"

if [[ -z "${INCLUDE:-}" ]]; then
    echo 'You must open a "Visual Studio .NET Command Prompt" to run this script'
    exit 1
fi

if [[ "$1" == "clean" ]]; then
    rm -f \
        buildvm.ilk \
        buildvm.pdb \
        lua51.dll \
        lua51.lib \
        luajit.exe \
        luajit.ilk \
        luajit.pdb \
        luajit.vcxproj.user \
        minilua.ilk \
        minilua.pdb \
        vc140.pdb

    rm -rf x64
    exit 0
fi

LJCOMPILE=(
    cl
    /nologo
    /c
    /O2
    /Ob3
    /Oi
    /Ot
    /Oy
    /GT
    /GL
    /W3
    /fp:precise
    /MD
    /GF
    /GS-
    /Zi
    /D_CRT_SECURE_NO_DEPRECATE
)

LJLINK=(
    link
    /nologo
    /debug
    /OPT:REF
    /OPT:ICF
    /LTCG
)

LJMT=(mt /nologo)
LJLIB=(lib /nologo)

DASMDIR="../dynasm"
DASM="../dynasm/dynasm.lua"

LJDLLNAME="lua51.dll"
LJLIBNAME="lua51.lib"

ALL_LIB=(
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

"${LJCOMPILE[@]}" host/minilua.c

"${LJLINK[@]}" \
    /out:minilua.exe \
    minilua.obj

if [[ -f minilua.exe.manifest ]]; then
    "${LJMT[@]}" \
        -manifest minilua.exe.manifest \
        -outputresource:minilua.exe
fi

DASMFLAGS=(-D WIN -D JIT -D FFI -D P64)
LJARCH="x64"

./minilua.exe
if [[ $? -lt 8 ]]; then
    DASMFLAGS=(-D WIN -D JIT -D FFI)
    LJARCH="x86"
fi

./minilua.exe \
    "$DASM" \
    -LN \
    "${DASMFLAGS[@]}" \
    -o host/buildvm_arch.h \
    vm_x86.dasc

"${LJCOMPILE[@]}" \
    /I . \
    /I "$DASMDIR" \
    host/buildvm*.c

"${LJLINK[@]}" \
    /out:buildvm.exe \
    buildvm*.obj

if [[ -f buildvm.exe.manifest ]]; then
    "${LJMT[@]}" \
        -manifest buildvm.exe.manifest \
        -outputresource:buildvm.exe
fi

./buildvm.exe -m peobj   -o lj_vm.obj
./buildvm.exe -m bcdef   -o lj_bcdef.h  "${ALL_LIB[@]}"
./buildvm.exe -m ffdef   -o lj_ffdef.h  "${ALL_LIB[@]}"
./buildvm.exe -m libdef  -o lj_libdef.h "${ALL_LIB[@]}"
./buildvm.exe -m recdef  -o lj_recdef.h "${ALL_LIB[@]}"
./buildvm.exe -m vmdef   -o jit/vmdef.lua "${ALL_LIB[@]}"
./buildvm.exe -m folddef -o lj_folddef.h lj_opt_fold.c

BUILDTYPE="$1"

if [[ "$BUILDTYPE" == "debug" ]]; then
    BUILDTYPE="$2"
    LJCOMPILE+=(/Zi)
    LJLINK+=(/debug)
fi

case "$BUILDTYPE" in
    amalg)
        "${LJCOMPILE[@]}" \
            /MD \
            /DLUA_BUILD_AS_DLL \
            ljamalg.c

        "${LJLINK[@]}" \
            /DLL \
            /out:"$LJDLLNAME" \
            ljamalg.obj \
            lj_vm.obj
        ;;

    static)
        "${LJCOMPILE[@]}" \
            lj_*.c \
            lib_*.c \
            xr_*.c

        "${LJLIB[@]}" \
            /OUT:"$LJLIBNAME" \
            lj_*.obj \
            lib_*.obj \
            xr_*.obj
        ;;

    *)
        "${LJCOMPILE[@]}" \
            /MD \
            /DLUA_BUILD_AS_DLL \
            lj_*.c \
            lib_*.c \
            xr_*.c

        "${LJLINK[@]}" \
            /DLL \
            /out:"$LJDLLNAME" \
            lj_*.obj \
            lib_*.obj \
            xr_*.obj
        ;;
esac

if [[ -f "${LJDLLNAME}.manifest" ]]; then
    "${LJMT[@]}" \
        -manifest "${LJDLLNAME}.manifest" \
        "-outputresource:${LJDLLNAME};2"
fi

"${LJCOMPILE[@]}" luajit.c

"${LJLINK[@]}" \
    /out:luajit.exe \
    luajit.obj \
    "$LJLIBNAME"

if [[ -f luajit.exe.manifest ]]; then
    "${LJMT[@]}" \
        -manifest luajit.exe.manifest \
        -outputresource:luajit.exe
fi

cp lua51.lib ../../../../_build/_game/bin_dbg/x64

rm -f \
    *.obj \
    *.manifest \
    minilua.exe \
    buildvm.exe

echo
echo "=== Successfully built LuaJIT for Windows/$LJARCH ==="
