set(PROJECT_NAME luabind)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "adopt_policy.hpp"
    "back_reference.hpp"
    "back_reference_fwd.hpp"
    "class.hpp"
    "class_info.hpp"
    "config.hpp"
    "copy_policy.hpp"
    "dependency_policy.hpp"
    "detail/calc_arity.hpp"
    "detail/calc_has_arg.hpp"
    "detail/call.hpp"
    "detail/call_function.hpp"
    "detail/call_member.hpp"
    "detail/call_operator_iterate.hpp"
    "detail/class_cache.hpp"
    "detail/class_registry.hpp"
    "detail/class_rep.hpp"
    "detail/construct_rep.hpp"
    "detail/constructor.hpp"
    "detail/convert_to_lua.hpp"
    "detail/decorate_type.hpp"
    "detail/enum_maker.hpp"
    "detail/find_best_match.hpp"
    "detail/garbage_collector.hpp"
    "detail/get_overload_signature.hpp"
    "detail/get_signature.hpp"
    "detail/implicit_cast.hpp"
    "detail/link_compatibility.hpp"
    "detail/method_rep.hpp"
    "detail/object_funs.hpp"
    "detail/object_rep.hpp"
    "detail/open.hpp"
    "detail/operator_id.hpp"
    "detail/other.hpp"
    "detail/overload_rep.hpp"
    "detail/overload_rep_base.hpp"
    "detail/overload_rep_impl.hpp"
    "detail/pcall.hpp"
    "detail/pointee_sizeof.hpp"
    "detail/pointee_typeid.hpp"
    "detail/policy.hpp"
    "detail/policy_cons.hpp"
    "detail/primitives.hpp"
    "detail/property.hpp"
    "detail/ref.hpp"
    "detail/signature_match.hpp"
    "detail/stack_utils.hpp"
    "detail/typetraits.hpp"
    "discard_result_policy.hpp"
    "error.hpp"
    "function.hpp"
    "functor.hpp"
    "iterator_pair_policy.hpp"
    "iterator_policy.hpp"
    "lua_include.hpp"
    "luabind.hpp"
    "luabind/src/class.cpp"
    "luabind/src/class_info.cpp"
    "luabind/src/class_registry.cpp"
    "luabind/src/class_rep.cpp"
    "luabind/src/create_class.cpp"
    "luabind/src/error.cpp"
    "luabind/src/find_best_match.cpp"
    "luabind/src/function.cpp"
    "luabind/src/implicit_cast.cpp"
    "luabind/src/link_compatibility.cpp"
    "luabind/src/luabind_api.h"
    "luabind/src/object.cpp"
    "luabind/src/object_rep.cpp"
    "luabind/src/open.cpp"
    "luabind/src/pcall.cpp"
    "luabind/src/ref.cpp"
    "luabind/src/scope.cpp"
    "luabind/src/stack_content_by_name.cpp"
    "luabind/src/weak_ref.cpp"
    "luabind/src/wrapper_base.cpp"
    "luabind_api.h"
    "luabind_delete.h"
    "luabind_memory.h"
    "luabind_memory_allocator.h"
    "luabind_memory_allocator_inline.h"
    "luabind_memory_manager_generator.h"
    "luabind_types.h"
    "object.hpp"
    "open.hpp"
    "operator.hpp"
    "out_value_policy.hpp"
    "prefix.hpp"
    "proxy_object.hpp"
    "raw_policy.hpp"
    "return_reference_to_policy.hpp"
    "scope.hpp"
    "weak_ref.hpp"
    "wrapper_base.hpp"
    "yield_policy.hpp"
)
source_group("" FILES ${no_group_source_files})

set(ALL_FILES
    ${no_group_source_files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "3rd_party")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "../../Common.cmake")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DX10             "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX10AVX          "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11             "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11AVX          "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8              "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8AVX           "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9              "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9AVX           "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_PROFILEDDX11     "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASE          "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASEAVX       "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIED         "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11     "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11ASAN "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX8      "${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX9      "${TARGET_NAME}"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_DX10             "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX10AVX          "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX11             "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX11AVX          "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX8              "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX8AVX           "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX9              "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX9AVX           "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_PROFILEDDX11     "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASE          "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASEAVX       "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIED         "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11     "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11ASAN "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX8      "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX9      "FALSE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../luajit-2/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include/luabind;"
    "${CMAKE_CURRENT_SOURCE_DIR}/luabind/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/."
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER"
    ">"
    "$<$<CONFIG:Verified>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE;"
        "_MBCS"
    ">"
    "WIN32;"
    "NDEBUG;"
    "LUABIND_BUILDING;"
    "_SECURE_SCL=0;"
    "_HAS_ITERATOR_DEBUGGING=0;"
    "LUABIND_NO_EXCEPTIONS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:DX10AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:DX11>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:DX11AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:DX8>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:DX8AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:DX9>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:DX9AVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:ProfiledDX11>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Z7
        >
        $<$<CONFIG:Release>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:ReleaseAVX>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Z7;
            /Ob3
        >
        $<$<CONFIG:Verified>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /Z7
        >
        $<$<CONFIG:VerifiedDX11>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /Z7
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /Z7
        >
        $<$<CONFIG:VerifiedDX8>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /Z7
        >
        $<$<CONFIG:VerifiedDX9>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /Z7
        >
        /MP;
        /std:c++20;
        /wd4073;
        /wd4100;
        /wd4390;
        /wd4714;
        /wd4127;
        /wd4273;
        /wd4595;
        /wd4996;
        /wd4005;
        /wd4530;
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            /OPT:NOREF
        >
        $<$<CONFIG:DX10AVX>:
            /OPT:NOREF
        >
        $<$<CONFIG:DX11>:
            /OPT:NOREF
        >
        $<$<CONFIG:DX11AVX>:
            /OPT:NOREF
        >
        $<$<CONFIG:DX8>:
            /OPT:NOREF
        >
        $<$<CONFIG:DX8AVX>:
            /OPT:NOREF
        >
        $<$<CONFIG:DX9>:
            /OPT:NOREF
        >
        $<$<CONFIG:DX9AVX>:
            /OPT:NOREF
        >
        $<$<CONFIG:ProfiledDX11>:
            /OPT:NOREF
        >
        $<$<CONFIG:Release>:
            /OPT:NOREF
        >
        $<$<CONFIG:ReleaseAVX>:
            /OPT:NOREF
        >
        $<$<CONFIG:Verified>:
            /OPT:NOREF
        >
        $<$<CONFIG:VerifiedDX11>:
            /OPT:NOREF
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /OPT:NOREF
        >
        $<$<CONFIG:VerifiedDX8>:
            /OPT:NOREF
        >
        $<$<CONFIG:VerifiedDX9>:
            /OPT:NOREF
        >
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "kernel32;"
    "user32;"
    "gdi32;"
    "winspool;"
    "shell32;"
    "ole32;"
    "oleaut32;"
    "uuid;"
    "comdlg32;"
    "advapi32"
    LuaJIT-2
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/./;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../luajit-2/src/"
)

