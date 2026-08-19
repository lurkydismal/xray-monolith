if(WIN32)
    set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
endif()

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(DISABLE_OPTIMIZATIONS "Disable compiler optimizations (-O0 or /Od)" OFF)

option(ENABLE_IPO "Enable interprocedural optimization (LTO)" OFF)

option(ENABLE_INCREMENTAL_LINKING "Enable MSVC incremental linking" OFF)

option(BUILD_DOCS "Enable documentation target" ON)
