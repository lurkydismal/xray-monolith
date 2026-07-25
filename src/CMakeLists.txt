cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)

project(engine-vs2022 C CXX)

include(CMake/ProjectOptions.cmake)
include(CMake/BuildTypes.cmake)
include(CMake/CompilerOptions.cmake)
include(CMake/LinkerOptions.cmake)
include(CMake/IPO.cmake)

################################################################################
# Fetch packages
################################################################################
include(CMake/Dependencies.cmake)

################################################################################
# Rust integration
################################################################################
include(CMake/Rust.cmake)

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

include(CMake/ThirdParty.cmake)
include(CMake/Renderers.cmake)

################################################################################
# Sub-projects
################################################################################
add_subdirectory(Layers/xrAPI)
add_subdirectory(${RENDERER_DIR})
add_subdirectory(ReShadeCompat)
add_subdirectory(xrCDB)
add_subdirectory(xrCore)
add_subdirectory(xrCPU_Pipe)
add_subdirectory(xrEngine)
add_subdirectory(xrGame)
add_subdirectory(xrNetServer)
add_subdirectory(xrParticles)
add_subdirectory(xrPhysics)
add_subdirectory(xrSound)
add_subdirectory(xrXMLParser)

include(CMake/Documentation.cmake)

################################################################################
# Unit testing support
################################################################################
# Include the project test integration after production targets are declared so
# test executables can link against existing libraries without adding test files
# to any production target.
include(CMake/XRayTesting.cmake)
