# clang-cl-msvc-i686.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

set(CMAKE_C_COMPILER clang-cl)
set(CMAKE_CXX_COMPILER clang-cl)

set(CMAKE_C_COMPILER_TARGET i686-w64-windows-msvc)
set(CMAKE_CXX_COMPILER_TARGET i686-w64-windows-msvc)

set(CMAKE_LINKER lld-link)
