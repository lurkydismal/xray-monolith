# clang-msvc-x64.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x64)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang)

set(CMAKE_C_COMPILER_TARGET x86_64-w64-windows-msvc)
set(CMAKE_CXX_COMPILER_TARGET x86_64-w64-windows-msvc)

set(CMAKE_LINKER lld-link)

set(CMAKE_AR llvm-ar)

set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)

set(IS_CLANG_MSVC ON)
