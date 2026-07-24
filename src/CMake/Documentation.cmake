################################################################################
# Documentation generation support
################################################################################
if(BUILD_DOCS)
    find_package(Doxygen QUIET)
    find_program(UV_EXECUTABLE uv)
    find_program(MAKE_EXECUTABLE NAMES make gmake)

    if(DOXYGEN_FOUND AND UV_EXECUTABLE AND MAKE_EXECUTABLE)
        if(DOXYGEN_DOT_FOUND)
            message(STATUS "Graphviz support enabled")
        else()
            message(STATUS "Graphviz not found; graphs disabled")
        endif()

        set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/..")

        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_ROOT}/Doxyfile
            COMMAND ${UV_EXECUTABLE} sync
            COMMAND ${CMAKE_COMMAND} -E chdir
                    ${PROJECT_ROOT}/docs
                    ${UV_EXECUTABLE} run ${MAKE_EXECUTABLE} html
            WORKING_DIRECTORY ${PROJECT_ROOT}
            COMMENT "Generating documentation"
        )
    else()
        message(STATUS "Documentation target disabled (missing Doxygen, uv, or make)")
    endif()
endif()
