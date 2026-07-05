#!/usr/bin/env fish

cd (dirname (status --current-filename))

if not set -q INCLUDE
    echo 'You must open a "Visual Studio .NET Command Prompt" to run this script'
    exit 1
end

if test "$argv[1]" = clean
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
end

set LJCOMPILE \
    cl \
    /nologo \
    /c \
    /O2 \
    /Ob3 \
    /Oi \
    /Ot \
    /Oy \
    /GT \
    /GL \
    /W3 \
    /fp:precise \
    /MD \
    /GF \
    /GS- \
    /Zi \
    /D_CRT_SECURE_NO_DEPRECATE

set LJLINK \
    link \
    /nologo \
    /debug \
    /OPT:REF \
    /OPT:ICF \
    /LTCG

set LJMT mt /nologo
set LJLIB lib /nologo

set DASMDIR ../dynasm
set DASM ../dynasm/dynasm.lua

set LJDLLNAME lua51.dll
set LJLIBNAME lua51.lib

set ALL_LIB \
    lib_base.c \
    lib_math.c \
    lib_bit.c \
    lib_string.c \
    lib_table.c \
    lib_io.c \
    lib_os.c \
    lib_package.c \
    lib_debug.c \
    lib_jit.c \
    lib_ffi.c

$LJCOMPILE host/minilua.c
or exit 1

$LJLINK /out:minilua.exe minilua.obj
or exit 1

if test -f minilua.exe.manifest
    $LJMT \
        -manifest minilua.exe.manifest \
        -outputresource:minilua.exe
end

set DASMFLAGS -D WIN -D JIT -D FFI -D P64
set LJARCH x64

./minilua.exe
if test $status -ge 8
    # x64
else
    set DASMFLAGS -D WIN -D JIT -D FFI
    set LJARCH x86
end

./minilua.exe \
    $DASM \
    -LN \
    $DASMFLAGS \
    -o host/buildvm_arch.h \
    vm_x86.dasc
or exit 1

$LJCOMPILE \
    /I . \
    /I $DASMDIR \
    host/buildvm*.c
or exit 1

$LJLINK \
    /out:buildvm.exe \
    buildvm*.obj
or exit 1

if test -f buildvm.exe.manifest
    $LJMT \
        -manifest buildvm.exe.manifest \
        -outputresource:buildvm.exe
end

./buildvm.exe -m peobj -o lj_vm.obj
or exit 1

./buildvm.exe -m bcdef -o lj_bcdef.h $ALL_LIB
or exit 1

./buildvm.exe -m ffdef -o lj_ffdef.h $ALL_LIB
or exit 1

./buildvm.exe -m libdef -o lj_libdef.h $ALL_LIB
or exit 1

./buildvm.exe -m recdef -o lj_recdef.h $ALL_LIB
or exit 1

./buildvm.exe -m vmdef -o jit/vmdef.lua $ALL_LIB
or exit 1

./buildvm.exe -m folddef -o lj_folddef.h lj_opt_fold.c
or exit 1

set BUILDTYPE "$argv[1]"

if test "$BUILDTYPE" = debug
    set BUILDTYPE "$argv[2]"
    set -a LJCOMPILE /Zi
    set -a LJLINK /debug
end

switch "$BUILDTYPE"
    case amalg
        $LJCOMPILE \
            /MD \
            /DLUA_BUILD_AS_DLL \
            ljamalg.c
        or exit 1

        $LJLINK \
            /DLL \
            /out:$LJDLLNAME \
            ljamalg.obj \
            lj_vm.obj
        or exit 1

    case static
        $LJCOMPILE \
            lj_*.c \
            lib_*.c \
            xr_*.c
        or exit 1

        $LJLIB \
            /OUT:$LJLIBNAME \
            lj_*.obj \
            lib_*.obj \
            xr_*.obj
        or exit 1

    case '*'
        $LJCOMPILE \
            /MD \
            /DLUA_BUILD_AS_DLL \
            lj_*.c \
            lib_*.c \
            xr_*.c
        or exit 1

        $LJLINK \
            /DLL \
            /out:$LJDLLNAME \
            lj_*.obj \
            lib_*.obj \
            xr_*.obj
        or exit 1
end

if test -f "$LJDLLNAME.manifest"
    $LJMT \
        -manifest "$LJDLLNAME.manifest" \
        -outputresource:$LJDLLNAME";2"
end

$LJCOMPILE luajit.c
or exit 1

$LJLINK \
    /out:luajit.exe \
    luajit.obj \
    $LJLIBNAME
or exit 1

if test -f luajit.exe.manifest
    $LJMT \
        -manifest luajit.exe.manifest \
        -outputresource:luajit.exe
end

cp lua51.lib ../../../../_build/_game/bin_dbg/x64

rm -f \
    *.obj \
    *.manifest \
    minilua.exe \
    buildvm.exe

echo
echo "=== Successfully built LuaJIT for Windows/$LJARCH ==="
