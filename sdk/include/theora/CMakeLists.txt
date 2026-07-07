set(PROJECT_NAME libtheora_static)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "lib/analyze.c"
    "lib/apiwrapper.c"
    "lib/apiwrapper.h"
    "lib/bitpack.c"
    "lib/bitpack.h"
    "lib/cpu.c"
    "lib/cpu.h"
    "lib/dct.h"
    "lib/decapiwrapper.c"
    "lib/decinfo.c"
    "lib/decint.h"
    "lib/decode.c"
    "lib/dequant.c"
    "lib/dequant.h"
    "lib/encapiwrapper.c"
    "lib/encfrag.c"
    "lib/encinfo.c"
    "lib/encint.h"
    "lib/encode.c"
#    "lib/encoder_disabled.c"
    "lib/enquant.c"
    "lib/enquant.h"
    "lib/fdct.c"
    "lib/fragment.c"
    "lib/huffdec.c"
    "lib/huffdec.h"
    "lib/huffenc.c"
    "lib/huffenc.h"
    "lib/huffman.h"
    "lib/idct.c"
    # "lib/idct.h"
    "lib/info.c"
    "lib/internal.c"
    "lib/internal.h"
    "lib/mathops.c"
    "lib/mathops.h"
    "lib/mcenc.c"
    "lib/modedec.h"
    "lib/ocintrin.h"
    "lib/quant.c"
    "lib/quant.h"
    "lib/rate.c"
    "lib/state.c"
    "lib/tokenize.c"
    "lib/x86_vc/mmxencfrag.c"
    "lib/x86_vc/mmxfdct.c"
    "lib/x86_vc/mmxfrag.c"
    "lib/x86_vc/mmxidct.c"
    "lib/x86_vc/mmxstate.c"
    "lib/x86_vc/x86enc.c"
    "lib/x86_vc/x86state.c"
    "codec.h"
    "theora.h"
    "theoradec.h"
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
use_props(${PROJECT_NAME} DX10             "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX11             "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX8              "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX9              "../../../src/Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../../../src/Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../../../src/Common.cmake")
use_props(${PROJECT_NAME} Release          "../../../src/Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../../../src/Common.cmake")
use_props(${PROJECT_NAME} Verified         "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../../../src/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../../../src/Common.cmake")

set(ROOT_NAMESPACE libtheora)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DX10             "libtheora_static"
    TARGET_NAME_DX10AVX          "libtheora_static"
    TARGET_NAME_DX11             "libtheora_static"
    TARGET_NAME_DX11AVX          "libtheora_static"
    TARGET_NAME_DX8              "libtheora_static"
    TARGET_NAME_DX8AVX           "libtheora_static"
    TARGET_NAME_DX9              "libtheora_static"
    TARGET_NAME_DX9AVX           "libtheora_static"
    TARGET_NAME_PROFILEDDX11     "libtheora_static"
    TARGET_NAME_RELEASE          "libtheora_static"
    TARGET_NAME_RELEASEAVX       "libtheora_static"
    TARGET_NAME_VERIFIED         "libtheora_static"
    TARGET_NAME_VERIFIEDDX11     "libtheora_static"
    TARGET_NAME_VERIFIEDDX11ASAN "libtheora_static"
    TARGET_NAME_VERIFIEDDX8      "libtheora_static"
    TARGET_NAME_VERIFIEDDX9      "libtheora_static"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_DX10             "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX10AVX          "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX11             "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX11AVX          "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX8              "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX8AVX           "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX9              "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_DX9AVX           "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_PROFILEDDX11     "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASE          "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASEAVX       "TRUE"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
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
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE;"
        "UNICODE;"
        "_UNICODE"
    ">"
    "_CRT_SECURE_NO_DEPRECATE;"
    "_CRT_NONSTDC_NO_DEPRECATE;"
    "_BIND_TO_CURRENT_CRT_VERSION;"
    "WIN32;"
    "NDEBUG;"
    "_WINDOWS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX10AVX>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3;
            /Y-
        >
        $<$<CONFIG:DX11>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX11AVX>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3;
            /Y-
        >
        $<$<CONFIG:DX8>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX8AVX>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3;
            /Y-
        >
        $<$<CONFIG:DX9>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX9AVX>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3;
            /Y-
        >
        $<$<CONFIG:ProfiledDX11>:
            /GL-;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi;
            /Y-
        >
        $<$<CONFIG:Release>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:ReleaseAVX>:
            /GL;
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3;
            /Y-
        >
        $<$<CONFIG:Verified>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX11>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX8>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /TC;
            /Y-
        >
        $<$<CONFIG:VerifiedDX9>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /ZI;
            /TC;
            /Y-
        >
        /std:c++17;
        /wd4244;
        /wd4267;
        /wd4057;
        /wd4100;
        /wd4245
    )
endif()

