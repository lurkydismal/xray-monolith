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

    # Tests include production headers directly from src and link against the
    # existing production targets rather than recompiling production sources.
    target_include_directories(xray_unit_tests PRIVATE
        "${CMAKE_SOURCE_DIR}"
    )

    # GoogleTest supplies the test runner entry point; GoogleMock is linked so
    # tests can use mocks when they add value without requiring extra CMake edits.
    target_link_libraries(xray_unit_tests PRIVATE
        GTest::gtest_main
        GTest::gmock
        xrCore
    )

    # Match the engine's C++ language level for test translation units.
    target_compile_features(xray_unit_tests PRIVATE cxx_std_17)

    # Discover individual TEST/TEST_F cases from the built binary and register
    # them with CTest automatically.
    gtest_discover_tests(xray_unit_tests)
endfunction()

add_xray_discovered_tests()
