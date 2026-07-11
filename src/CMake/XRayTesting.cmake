################################################################################
# X-Ray unit test support
################################################################################
# This file is included by the existing top-level CMakeLists.txt so testing is
# added without replacing the current project layout or production targets.

# Keep tests opt-in for normal engine builds while still making CTest integration
# available from the root project when XRay_BUILD_TESTING is enabled.
option(XRay_BUILD_TESTING "Build X-Ray unit tests" ON)

if(NOT XRay_BUILD_TESTING)
    return()
endif()

# CTest must be enabled at the top level before test executables are registered.
include(CTest)

# CPM.cmake is the required dependency manager for test-only dependencies.
include("${CMAKE_CURRENT_LIST_DIR}/CPM.cmake")

# GoogleTest's CMake package also provides GoogleMock targets; both are fetched
# through CPM so tests can link to GTest::gtest_main and GTest::gmock.
CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.15.2
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

# gtest_discover_tests is used below so newly added tests are automatically
# exposed to CTest after the test binary is built.
include(GoogleTest)

# Collect every side-by-side unit test under src while deliberately skipping all
# vendored code beneath src/3rd_party. CONFIGURE_DEPENDS lets CMake reconfigure
# automatically when a new *.test.cpp file is added or removed.
file(GLOB_RECURSE XRAY_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/*.test.cpp"
)
list(FILTER XRAY_TEST_SOURCES EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/3rd_party/")

# add_xray_discovered_tests creates the single aggregate unit-test executable.
# Keeping the production libraries separate ensures *.test.cpp files never become
# part of the existing production targets.
function(add_xray_discovered_tests)
    if(NOT XRAY_TEST_SOURCES)
        message(STATUS "No X-Ray unit tests found")
        return()
    endif()

    add_executable(xray_unit_tests ${XRAY_TEST_SOURCES})

    file(GLOB XRAY_RUNTIME_DLLS
        "${CMAKE_SOURCE_DIR}/../sdk/binaries/*.dll"
    )

    add_custom_command(TARGET xray_unit_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${XRAY_RUNTIME_DLLS}
            "$<TARGET_FILE_DIR:xray_unit_tests>"
    )

    # Tests include production headers directly from src and link against the
    # existing production targets rather than recompiling production sources.
    target_include_directories(xray_unit_tests PRIVATE
        "${CMAKE_SOURCE_DIR}"
    )

    xray_collect_test_link_targets(XRAY_TEST_LINK_TARGETS)

    # GoogleTest supplies the test runner entry point; GoogleMock is linked so
    # tests can use mocks when they add value without requiring extra CMake edits.
    target_link_libraries(xray_unit_tests PRIVATE
        GTest::gtest_main
        GTest::gmock
        ${XRAY_TEST_LINK_TARGETS}
    )

    # Match the engine's C++ language level for test translation units.
    target_compile_features(xray_unit_tests PRIVATE cxx_std_17)

    # Discover individual TEST/TEST_F cases from the built binary and register
    # them with CTest automatically.
    gtest_discover_tests(xray_unit_tests)
endfunction()

# xray_collect_test_link_targets discovers all linkable project targets so the
# aggregate test binary exercises the same CMake targets declared by sdk/, src/,
# and src/3rd_party/. Dual libraries are resolved to their shared variants to
# preserve the default test behavior when PROJECT_SHARED_LIBS is OFF.
function(xray_collect_test_link_targets OUT_VAR)
    xray_collect_directory_targets("${CMAKE_SOURCE_DIR}" DISCOVERED_TARGETS)

    set(RESULT)
    foreach(DISCOVERED_TARGET IN LISTS DISCOVERED_TARGETS)
        if(DISCOVERED_TARGET STREQUAL "xray_unit_tests")
            continue()
        endif()

        get_target_property(TARGET_TYPE "${DISCOVERED_TARGET}" TYPE)
        if(NOT TARGET_TYPE MATCHES "^(STATIC_LIBRARY|SHARED_LIBRARY|MODULE_LIBRARY|INTERFACE_LIBRARY|UNKNOWN_LIBRARY)$")
            continue()
        endif()

        if(TARGET "${DISCOVERED_TARGET}_shared")
            set(DISCOVERED_TARGET "${DISCOVERED_TARGET}_shared")
        endif()

        if(NOT DISCOVERED_TARGET IN_LIST RESULT)
            list(APPEND RESULT "${DISCOVERED_TARGET}")
        endif()
    endforeach()

    set(${OUT_VAR} "${RESULT}" PARENT_SCOPE)
endfunction()

# xray_collect_directory_targets recursively walks CMake's directory tree and
# returns targets declared in the root project, including out-of-tree sdk targets
# that were added with add_subdirectory().
function(xray_collect_directory_targets DIRECTORY OUT_VAR)
    get_property(LOCAL_TARGETS DIRECTORY "${DIRECTORY}" PROPERTY BUILDSYSTEM_TARGETS)
    set(RESULT ${LOCAL_TARGETS})

    get_property(SUBDIRECTORIES DIRECTORY "${DIRECTORY}" PROPERTY SUBDIRECTORIES)
    foreach(SUBDIRECTORY IN LISTS SUBDIRECTORIES)
        xray_collect_directory_targets("${SUBDIRECTORY}" SUBDIRECTORY_TARGETS)
        list(APPEND RESULT ${SUBDIRECTORY_TARGETS})
    endforeach()

    set(${OUT_VAR} "${RESULT}" PARENT_SCOPE)
endfunction()

add_xray_discovered_tests()
