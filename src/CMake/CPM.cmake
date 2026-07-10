# Minimal CPM.cmake-compatible dependency helper for this project.
# It implements the CPMAddPackage arguments used by the test integration while
# delegating the actual download/populate work to CMake's FetchContent module.
include(FetchContent)

# CPMAddPackage declares and makes a dependency available by name.
# Supported arguments intentionally match this repository's usage: NAME,
# GITHUB_REPOSITORY, GIT_TAG, and OPTIONS.
function(CPMAddPackage)
    set(oneValueArgs NAME GITHUB_REPOSITORY GIT_TAG)
    set(multiValueArgs OPTIONS)
    cmake_parse_arguments(CPM "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT CPM_NAME)
        message(FATAL_ERROR "CPMAddPackage requires NAME")
    endif()

    # Apply dependency-specific cache options before FetchContent configures the
    # dependency so callers can keep third-party settings local to the package.
    foreach(option_pair IN LISTS CPM_OPTIONS)
        string(REGEX MATCH "^([^ ]+) (.*)$" option_match "${option_pair}")
        if(option_match)
            set("${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}" CACHE BOOL "CPM option for ${CPM_NAME}" FORCE)
        endif()
    endforeach()

    if(CPM_GITHUB_REPOSITORY)
        set(CPM_GIT_REPOSITORY "https://github.com/${CPM_GITHUB_REPOSITORY}.git")
    else()
        message(FATAL_ERROR "CPMAddPackage(${CPM_NAME}) requires GITHUB_REPOSITORY")
    endif()

    # FetchContent_MakeAvailable preserves the normal add_subdirectory behavior
    # expected by CPM-managed CMake dependencies such as GoogleTest/GoogleMock.
    FetchContent_Declare(
        ${CPM_NAME}
        GIT_REPOSITORY "${CPM_GIT_REPOSITORY}"
        GIT_TAG "${CPM_GIT_TAG}"
    )
    FetchContent_MakeAvailable(${CPM_NAME})
endfunction()
