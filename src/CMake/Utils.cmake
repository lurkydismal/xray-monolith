################################################################################
# Wrap each token of the command with condition
################################################################################
cmake_policy(PUSH)
cmake_policy(SET CMP0054 NEW)
macro(prepare_commands)
    unset(TOKEN_ROLE)
    unset(COMMANDS)
    foreach(TOKEN ${ARG_COMMANDS})
        if("${TOKEN}" STREQUAL "COMMAND")
            set(TOKEN_ROLE "KEYWORD")
        elseif("${TOKEN_ROLE}" STREQUAL "KEYWORD")
            set(TOKEN_ROLE "CONDITION")
        elseif("${TOKEN_ROLE}" STREQUAL "CONDITION")
            set(TOKEN_ROLE "COMMAND")
        elseif("${TOKEN_ROLE}" STREQUAL "COMMAND")
            set(TOKEN_ROLE "ARG")
        endif()

        if("${TOKEN_ROLE}" STREQUAL "KEYWORD")
            list(APPEND COMMANDS "${TOKEN}")
        elseif("${TOKEN_ROLE}" STREQUAL "CONDITION")
            set(CONDITION ${TOKEN})
        elseif("${TOKEN_ROLE}" STREQUAL "COMMAND")
            list(APPEND COMMANDS "$<$<NOT:${CONDITION}>:${DUMMY}>$<${CONDITION}:${TOKEN}>")
        elseif("${TOKEN_ROLE}" STREQUAL "ARG")
            list(APPEND COMMANDS "$<${CONDITION}:${TOKEN}>")
        endif()
    endforeach()
endmacro()
cmake_policy(POP)

################################################################################
# Transform all the tokens to absolute paths
################################################################################
macro(prepare_output)
    unset(OUTPUT)
    foreach(TOKEN ${ARG_OUTPUT})
        if(IS_ABSOLUTE ${TOKEN})
            list(APPEND OUTPUT "${TOKEN}")
        else()
            list(APPEND OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${TOKEN}")
        endif()
    endforeach()
endmacro()

################################################################################
# Parse add_custom_command_if args.
#
# Input:
#     PRE_BUILD  - Pre build event option
#     PRE_LINK   - Pre link event option
#     POST_BUILD - Post build event option
#     TARGET     - Target
#     OUTPUT     - List of output files
#     DEPENDS    - List of files on which the command depends
#     COMMANDS   - List of commands(COMMAND condition1 commannd1 args1 COMMAND
#                  condition2 commannd2 args2 ...)
# Output:
#     OUTPUT     - Output files
#     DEPENDS    - Files on which the command depends
#     COMMENT    - Comment
#     PRE_BUILD  - TRUE/FALSE
#     PRE_LINK   - TRUE/FALSE
#     POST_BUILD - TRUE/FALSE
#     TARGET     - Target name
#     COMMANDS   - Prepared commands(every token is wrapped in CONDITION)
#     NAME       - Unique name for custom target
#     STEP       - PRE_BUILD/PRE_LINK/POST_BUILD
################################################################################
function(add_custom_command_if_parse_arguments)
    cmake_parse_arguments("ARG" "PRE_BUILD;PRE_LINK;POST_BUILD" "TARGET;COMMENT" "DEPENDS;OUTPUT;COMMANDS" ${ARGN})

    if(WIN32)
        set(DUMMY "cd.")
    elseif(UNIX)
        set(DUMMY "true")
    endif()

    prepare_commands()
    prepare_output()

    set(DEPENDS "${ARG_DEPENDS}")
    set(COMMENT "${ARG_COMMENT}")
    set(PRE_BUILD "${ARG_PRE_BUILD}")
    set(PRE_LINK "${ARG_PRE_LINK}")
    set(POST_BUILD "${ARG_POST_BUILD}")
    set(TARGET "${ARG_TARGET}")
    if(PRE_BUILD)
        set(STEP "PRE_BUILD")
    elseif(PRE_LINK)
        set(STEP "PRE_LINK")
    elseif(POST_BUILD)
        set(STEP "POST_BUILD")
    endif()
    set(NAME "${TARGET}_${STEP}")

    set(OUTPUT "${OUTPUT}" PARENT_SCOPE)
    set(DEPENDS "${DEPENDS}" PARENT_SCOPE)
    set(COMMENT "${COMMENT}" PARENT_SCOPE)
    set(PRE_BUILD "${PRE_BUILD}" PARENT_SCOPE)
    set(PRE_LINK "${PRE_LINK}" PARENT_SCOPE)
    set(POST_BUILD "${POST_BUILD}" PARENT_SCOPE)
    set(TARGET "${TARGET}" PARENT_SCOPE)
    set(COMMANDS "${COMMANDS}" PARENT_SCOPE)
    set(STEP "${STEP}" PARENT_SCOPE)
    set(NAME "${NAME}" PARENT_SCOPE)
endfunction()

################################################################################
# Add conditional custom command
#
# Generating Files
# The first signature is for adding a custom command to produce an output:
#     add_custom_command_if(
#         <OUTPUT output1 [output2 ...]>
#         <COMMANDS>
#         <COMMAND condition command1 [args1...]>
#         [COMMAND condition command2 [args2...]]
#         [DEPENDS [depends...]]
#         [COMMENT comment]
#
# Build Events
#     add_custom_command_if(
#         <TARGET target>
#         <PRE_BUILD | PRE_LINK | POST_BUILD>
#         <COMMAND condition command1 [args1...]>
#         [COMMAND condition command2 [args2...]]
#         [COMMENT comment]
#
# Input:
#     output     - Output files the command is expected to produce
#     condition  - Generator expression for wrapping the command
#     command    - Command-line(s) to execute at build time.
#     args       - Command`s args
#     depends    - Files on which the command depends
#     comment    - Display the given message before the commands are executed at
#                  build time.
#     PRE_BUILD  - Run before any other rules are executed within the target
#     PRE_LINK   - Run after sources have been compiled but before linking the
#                  binary
#     POST_BUILD - Run after all other rules within the target have been
#                  executed
################################################################################
function(add_custom_command_if)
    add_custom_command_if_parse_arguments(${ARGN})

    if(OUTPUT AND TARGET)
        message(FATAL_ERROR  "Wrong syntax. A TARGET and OUTPUT can not both be specified.")
    endif()

    if(OUTPUT)
        add_custom_command(OUTPUT ${OUTPUT}
                           ${COMMANDS}
                           DEPENDS ${DEPENDS}
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                           COMMENT ${COMMENT})
    elseif(TARGET)
        if(PRE_BUILD AND NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
            add_custom_target(
                ${NAME}
                ${COMMANDS}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT ${COMMENT})
            add_dependencies(${TARGET} ${NAME})
        else()
            add_custom_command(
                TARGET ${TARGET}
                ${STEP}
                ${COMMANDS}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT ${COMMENT})
        endif()
    else()
        message(FATAL_ERROR "Wrong syntax. A TARGET or OUTPUT must be specified.")
    endif()
endfunction()

################################################################################
# Use props file for a target and configs
#     use_props(<target> <configs...> <props_file>)
# Inside <props_file> there are following variables:
#     PROPS_TARGET   - <target>
#     PROPS_CONFIG   - One of <configs...>
#     PROPS_CONFIG_U - Uppercase PROPS_CONFIG
# Input:
#     target      - Target to apply props file
#     configs     - Build configurations to apply props file
#     props_file  - CMake script
################################################################################
macro(use_props TARGET CONFIGS PROPS_FILE)
    set(PROPS_TARGET "${TARGET}")
    foreach(PROPS_CONFIG ${CONFIGS})
        string(TOUPPER "${PROPS_CONFIG}" PROPS_CONFIG_U)

        get_filename_component(ABSOLUTE_PROPS_FILE "${PROPS_FILE}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
        if(EXISTS "${ABSOLUTE_PROPS_FILE}")
            include("${ABSOLUTE_PROPS_FILE}")
        else()
            message(WARNING "Corresponding cmake file from props \"${ABSOLUTE_PROPS_FILE}\" doesn't exist")
        endif()
    endforeach()
endmacro()

################################################################################
# Add compile options to source file
#     source_file_compile_options(<source_file> [compile_options...])
# Input:
#     source_file     - Source file
#     compile_options - Options to add to COMPILE_FLAGS property
################################################################################
function(source_file_compile_options SOURCE_FILE)
    if("${ARGC}" LESS_EQUAL "1")
        return()
    endif()

    get_source_file_property(COMPILE_OPTIONS "${SOURCE_FILE}" COMPILE_OPTIONS)

    if(COMPILE_OPTIONS)
        list(APPEND COMPILE_OPTIONS ${ARGN})
    else()
        set(COMPILE_OPTIONS "${ARGN}")
    endif()

    set_source_files_properties("${SOURCE_FILE}" PROPERTIES COMPILE_OPTIONS "${COMPILE_OPTIONS}")
endfunction()

################################################################################
# Default properties of visual studio projects
################################################################################
set(DEFAULT_CXX_PROPS "${CMAKE_CURRENT_LIST_DIR}/DefaultCXX.cmake")
set(DEFAULT_Fortran_PROPS "${CMAKE_CURRENT_LIST_DIR}/DefaultFortran.cmake")

################################################################################
# Add static and shared variants from one object library.
#
# xray_add_dual_library keeps the historical target name as the static library
# used by production targets, and creates <target>_shared for tests without
# duplicating source lists or recompiling the same source files in CMake.
################################################################################
function(xray_add_dual_library TARGET OBJECT_TARGET)
    add_library(${OBJECT_TARGET} OBJECT ${ARGN})

    if(PROJECT_SHARED_LIBS)
        set_target_properties(${OBJECT_TARGET}
            PROPERTIES
            POSITION_INDEPENDENT_CODE ON
        )
    endif()

    add_library(${TARGET} STATIC
        $<TARGET_OBJECTS:${OBJECT_TARGET}>
    )

    add_library(${TARGET}_shared SHARED
        $<TARGET_OBJECTS:${OBJECT_TARGET}>
    )

    set_target_properties(${TARGET}_shared
        PROPERTIES
        OUTPUT_NAME "${TARGET}_shared"
    )

    set_property(TARGET ${TARGET} PROPERTY
        XRAY_SHARED_VARIANT FALSE
    )

    set_property(TARGET ${TARGET}_shared PROPERTY
        XRAY_SHARED_VARIANT TRUE
    )

    # Mark both libraries as belonging to the same pair.
    set_target_properties(${TARGET} PROPERTIES
        XRAY_DUAL_TARGET "${TARGET}"
    )
    set_target_properties(${TARGET}_shared PROPERTIES
        XRAY_DUAL_TARGET "${TARGET}"
    )

    # Store object target name.
    set_target_properties(${TARGET} PROPERTIES
        XRAY_OBJECT_TARGET "${OBJECT_TARGET}"
    )

    set_target_properties(${TARGET}_shared PROPERTIES
        XRAY_OBJECT_TARGET "${OBJECT_TARGET}"
    )
endfunction()

################################################################################
# xray_project_link_variant returns the correct link target for a project library.
# Shared-library consumers and PROJECT_SHARED_LIBS builds use <target>_shared
# when that variant exists; the default production build keeps historical static
# target links.
################################################################################
function(xray_project_link_variant OUT_VAR LINK_TARGET USE_SHARED)
    if(NOT TARGET "${LINK_TARGET}")
        set(${OUT_VAR} "${LINK_TARGET}" PARENT_SCOPE)
        return()
    endif()

    if(USE_SHARED AND TARGET "${LINK_TARGET}_shared")
        set(${OUT_VAR} "${LINK_TARGET}_shared" PARENT_SCOPE)
    else()
        set(${OUT_VAR} "${LINK_TARGET}" PARENT_SCOPE)
    endif()
endfunction()

################################################################################
# xray_link_project_libraries mirrors target_link_libraries while remapping
# project dual-library dependencies to their shared variants when requested.
################################################################################
function(xray_link_project_libraries XRAY_TARGET_NAME SCOPE)
    set(USE_SHARED "${PROJECT_SHARED_LIBS}")

    get_property(USE_SHARED
        TARGET ${XRAY_TARGET_NAME}
        PROPERTY XRAY_SHARED_VARIANT
    )

    set(LINK_LIBRARIES)
    foreach(LINK_LIBRARY IN LISTS ARGN)
        xray_project_link_variant(RESOLVED_LINK_LIBRARY "${LINK_LIBRARY}" ${USE_SHARED})
        list(APPEND LINK_LIBRARIES "${RESOLVED_LINK_LIBRARY}")
    endforeach()

    target_link_libraries(${XRAY_TARGET_NAME} ${SCOPE} ${LINK_LIBRARIES})
endfunction()

function(xray_dual_targets OUT_VAR TARGET)
    set(TARGETS)

    if(TARGET "${TARGET}")
        list(APPEND TARGETS "${TARGET}")
    endif()

    if(TARGET "${TARGET}_shared")
        list(APPEND TARGETS "${TARGET}_shared")
    endif()

    set(${OUT_VAR} "${TARGETS}" PARENT_SCOPE)
endfunction()

function(xray_target_include_directories TARGET OBJECT_TARGET SCOPE)
    target_include_directories(${OBJECT_TARGET}
        ${SCOPE}
        ${ARGN}
    )

    xray_dual_targets(TARGETS ${TARGET})

    foreach(T IN LISTS TARGETS)
        target_include_directories(${T}
            ${SCOPE}
            "$<TARGET_PROPERTY:${OBJECT_TARGET},INTERFACE_INCLUDE_DIRECTORIES>"
            "$<TARGET_PROPERTY:${OBJECT_TARGET},INCLUDE_DIRECTORIES>"
        )
    endforeach()
endfunction()

function(xray_target_compile_definitions TARGET SCOPE)
    get_property(OBJECT_TARGET
        TARGET ${TARGET}
        PROPERTY XRAY_OBJECT_TARGET
    )

    if(OBJECT_TARGET)
        target_compile_definitions(${OBJECT_TARGET}
            ${SCOPE}
            ${ARGN}
        )
    else()
        target_compile_definitions(${TARGET}
            ${SCOPE}
            ${ARGN}
        )
    endif()

    if(SCOPE STREQUAL "PUBLIC" OR SCOPE STREQUAL "INTERFACE")
        xray_dual_targets(TARGETS ${TARGET})

        foreach(T IN LISTS TARGETS)
            target_compile_definitions(${T}
                ${SCOPE}
                ${ARGN}
            )
        endforeach()
    endif()
endfunction()

function(xray_target_compile_options OBJECT_TARGET SCOPE)
    target_compile_options(${OBJECT_TARGET}
        ${SCOPE}
        ${ARGN}
    )
endfunction()

function(xray_target_precompile_headers OBJECT_TARGET SCOPE)
    target_precompile_headers(${OBJECT_TARGET}
        ${SCOPE}
        ${ARGN}
    )
endfunction()

function(xray_add_dependencies TARGET)
    xray_dual_targets(TARGETS ${TARGET})

    foreach(T IN LISTS TARGETS)
        add_dependencies(${T} ${ARGN})
    endforeach()
endfunction()

function(xray_target_link_libraries TARGET SCOPE)
    get_property(OBJECT_TARGET
        TARGET ${TARGET}
        PROPERTY XRAY_OBJECT_TARGET
    )

    if(OBJECT_TARGET)
        target_link_libraries(${OBJECT_TARGET}
            ${SCOPE}
            ${ARGN}
        )
    endif()

    xray_dual_targets(TARGETS ${TARGET})

    foreach(T IN LISTS TARGETS)
        xray_link_project_libraries(${T} ${SCOPE} ${ARGN})
    endforeach()
endfunction()

function(xray_target_link_options TARGET SCOPE)
    xray_dual_targets(TARGETS ${TARGET})

    foreach(T IN LISTS TARGETS)
        target_link_options(${T} ${SCOPE} ${ARGN})
    endforeach()
endfunction()

function(xray_target_link_directories TARGET SCOPE)
    xray_dual_targets(TARGETS ${TARGET})

    foreach(T IN LISTS TARGETS)
        target_link_directories(${T} ${SCOPE} ${ARGN})
    endforeach()
endfunction()

function(xray_set_target_properties TARGET)
    xray_dual_targets(TARGETS ${TARGET})

    foreach(T IN LISTS TARGETS)
        set_target_properties(${T}
            PROPERTIES
            ${ARGN}
        )
    endforeach()
endfunction()
