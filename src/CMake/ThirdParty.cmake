set(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")

################################################################################
# SDK/ 3rd party sub-projects
################################################################################
add_subdirectory("${PROJECT_ROOT}/../sdk/include/jpeg" "${CMAKE_BINARY_DIR}/libjpeg")
add_subdirectory("${PROJECT_ROOT}/../sdk/include/ogg" "${CMAKE_BINARY_DIR}/libogg_static")
add_subdirectory("${PROJECT_ROOT}/../sdk/include/theora" "${CMAKE_BINARY_DIR}/libtheora_static")
add_subdirectory("${PROJECT_ROOT}/../sdk/include/vorbis" "${CMAKE_BINARY_DIR}/libvorbisfile_static")
add_subdirectory("${PROJECT_ROOT}/3rd_party/crypto")
add_subdirectory("${PROJECT_ROOT}/3rd_party/cximage")
add_subdirectory("${PROJECT_ROOT}/3rd_party/DXERR")
add_subdirectory("${PROJECT_ROOT}/3rd_party/giflib")
add_subdirectory("${PROJECT_ROOT}/3rd_party/imgui")
add_subdirectory("${PROJECT_ROOT}/3rd_party/lua-extensions")
add_subdirectory("${PROJECT_ROOT}/3rd_party/luabind")
add_subdirectory("${PROJECT_ROOT}/3rd_party/luajit-2/src")
add_subdirectory("${PROJECT_ROOT}/3rd_party/NVTT")
add_subdirectory("${PROJECT_ROOT}/3rd_party/ode/contrib/msvc7/ode_default")
add_subdirectory("${PROJECT_ROOT}/3rd_party/OpenAL-new")
