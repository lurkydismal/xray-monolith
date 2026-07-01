set(PROJECT_NAME OpenAL32)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "default_hrtf.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "al/auxeffectslot.h"
    "al/buffer.h"
    "al/eax/api.h"
    "al/eax/call.h"
    "al/eax/effect.h"
    "al/eax/exception.h"
    "al/eax/fx_slot_index.h"
    "al/eax/fx_slots.h"
    "al/eax/globals.h"
    "al/eax/utils.h"
    "al/eax/x_ram.h"
    "al/effect.h"
    "al/effects/effects.h"
    "al/event.h"
    "al/filter.h"
    "al/listener.h"
    "al/source.h"
    "alc/alconfig.h"
    "alc/alu.h"
    "alc/backends/base.h"
    "alc/backends/dsound.h"
    "alc/backends/loopback.h"
    "alc/backends/null.h"
    "alc/backends/wasapi.h"
    "alc/backends/wave.h"
    "alc/backends/winmm.h"
    "alc/context.h"
    "alc/device.h"
    "alc/effects/base.h"
    "alc/inprogext.h"
    "common/albit.h"
    "common/albyte.h"
    "common/alcomplex.h"
    "common/aldeque.h"
    "common/alfstream.h"
    "common/almalloc.h"
    "common/alnumbers.h"
    "common/alnumeric.h"
    "common/aloptional.h"
    "common/alspan.h"
    "common/alstring.h"
    "common/altraits.h"
    "common/atomic.h"
    "common/comptr.h"
    "common/dynload.h"
    "common/intrusive_ptr.h"
    "common/opthelpers.h"
    "common/phase_shifter.h"
    "common/polyphase_resampler.h"
    "common/pragmadefs.h"
    "common/ringbuffer.h"
    "common/strutils.h"
    "common/threads.h"
    "common/vecmat.h"
    "common/vector.h"
    "core/ambdec.h"
    "core/ambidefs.h"
    "core/async_event.h"
    "core/bformatdec.h"
    "core/bs2b.h"
    "core/bsinc_defs.h"
    "core/bsinc_tables.h"
    "core/buffer_storage.h"
    "core/bufferline.h"
    "core/context.h"
    "core/converter.h"
    "core/cpu_caps.h"
    "core/cubic_defs.h"
    "core/cubic_tables.h"
    "core/devformat.h"
    "core/device.h"
    "core/effects/base.h"
    "core/effectslot.h"
    "core/except.h"
    "core/filters/biquad.h"
    "core/filters/nfc.h"
    "core/filters/splitter.h"
    "core/fmt_traits.h"
    "core/fpu_ctrl.h"
    "core/front_stablizer.h"
    "core/helpers.h"
    "core/hrtf.h"
    "core/logging.h"
    "core/mastering.h"
    "core/mixer.h"
    "core/mixer/defs.h"
    "core/mixer/hrtfbase.h"
    "core/mixer/hrtfdefs.h"
    "core/resampler_limits.h"
    "core/uhjfilter.h"
    "core/voice.h"
    "core/voice_change.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "al/auxeffectslot.cpp"
    "al/buffer.cpp"
    "al/eax/api.cpp"
    "al/eax/call.cpp"
    "al/eax/exception.cpp"
    "al/eax/fx_slot_index.cpp"
    "al/eax/fx_slots.cpp"
    "al/eax/globals.cpp"
    "al/eax/utils.cpp"
    "al/effect.cpp"
    "al/effects/autowah.cpp"
    "al/effects/chorus.cpp"
    "al/effects/compressor.cpp"
    "al/effects/convolution.cpp"
    "al/effects/dedicated.cpp"
    "al/effects/distortion.cpp"
    "al/effects/echo.cpp"
    "al/effects/effects.cpp"
    "al/effects/equalizer.cpp"
    "al/effects/fshifter.cpp"
    "al/effects/modulator.cpp"
    "al/effects/null.cpp"
    "al/effects/pshifter.cpp"
    "al/effects/reverb.cpp"
    "al/effects/vmorpher.cpp"
    "al/error.cpp"
    "al/event.cpp"
    "al/extension.cpp"
    "al/filter.cpp"
    "al/listener.cpp"
    "al/source.cpp"
    "al/state.cpp"
    "alc/alc.cpp"
    "alc/alconfig.cpp"
    "alc/alu.cpp"
    "alc/backends/base.cpp"
    "alc/backends/dsound.cpp"
    "alc/backends/loopback.cpp"
    "alc/backends/null.cpp"
    "alc/backends/wasapi.cpp"
    "alc/backends/wave.cpp"
    "alc/backends/winmm.cpp"
    "alc/context.cpp"
    "alc/device.cpp"
    "alc/effects/autowah.cpp"
    "alc/effects/chorus.cpp"
    "alc/effects/compressor.cpp"
    "alc/effects/convolution.cpp"
    "alc/effects/dedicated.cpp"
    "alc/effects/distortion.cpp"
    "alc/effects/echo.cpp"
    "alc/effects/equalizer.cpp"
    "alc/effects/fshifter.cpp"
    "alc/effects/modulator.cpp"
    "alc/effects/null.cpp"
    "alc/effects/pshifter.cpp"
    "alc/effects/reverb.cpp"
    "alc/effects/vmorpher.cpp"
    "alc/panning.cpp"
    "common/alcomplex.cpp"
    "common/alfstream.cpp"
    "common/almalloc.cpp"
    "common/alstring.cpp"
    "common/dynload.cpp"
    "common/polyphase_resampler.cpp"
    "common/ringbuffer.cpp"
    "common/strutils.cpp"
    "common/threads.cpp"
    "core/ambdec.cpp"
    "core/ambidefs.cpp"
    "core/bformatdec.cpp"
    "core/bs2b.cpp"
    "core/bsinc_tables.cpp"
    "core/buffer_storage.cpp"
    "core/context.cpp"
    "core/converter.cpp"
    "core/cpu_caps.cpp"
    "core/cubic_tables.cpp"
    "core/devformat.cpp"
    "core/device.cpp"
    "core/effectslot.cpp"
    "core/except.cpp"
    "core/filters/biquad.cpp"
    "core/filters/nfc.cpp"
    "core/filters/splitter.cpp"
    "core/fmt_traits.cpp"
    "core/fpu_ctrl.cpp"
    "core/helpers.cpp"
    "core/hrtf.cpp"
    "core/logging.cpp"
    "core/mastering.cpp"
    "core/mixer.cpp"
    "core/mixer/mixer_c.cpp"
    "core/mixer/mixer_sse.cpp"
    "core/mixer/mixer_sse2.cpp"
    "core/mixer/mixer_sse3.cpp"
    "core/mixer/mixer_sse41.cpp"
    "core/uhjfilter.cpp"
    "core/uiddefs.cpp"
    "core/voice.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "3rd party")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} DX10             "../../Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../../Common.cmake")
use_props(${PROJECT_NAME} DX11             "../../Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../../Common.cmake")
use_props(${PROJECT_NAME} DX8              "../../Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../../Common.cmake")
use_props(${PROJECT_NAME} DX9              "../../Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../../Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../../Common.cmake")
use_props(${PROJECT_NAME} Release          "../../Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../../Common.cmake")
use_props(${PROJECT_NAME} Verified         "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../../Common.cmake")

set(ROOT_NAMESPACE OpenAL32)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DX10             "${PROJECT_NAME}"
    TARGET_NAME_DX10AVX          "${PROJECT_NAME}"
    TARGET_NAME_DX11             "${PROJECT_NAME}"
    TARGET_NAME_DX11AVX          "${PROJECT_NAME}"
    TARGET_NAME_DX8              "${PROJECT_NAME}"
    TARGET_NAME_DX8AVX           "${PROJECT_NAME}"
    TARGET_NAME_DX9              "${PROJECT_NAME}"
    TARGET_NAME_DX9AVX           "${PROJECT_NAME}"
    TARGET_NAME_PROFILEDDX11     "${PROJECT_NAME}"
    TARGET_NAME_RELEASE          "${PROJECT_NAME}"
    TARGET_NAME_RELEASEAVX       "${PROJECT_NAME}"
    TARGET_NAME_VERIFIED         "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX11     "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX11ASAN "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX8      "${PROJECT_NAME}"
    TARGET_NAME_VERIFIEDDX9      "${PROJECT_NAME}"
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
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    MultiThreadedDLL
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/common"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER"
    ">"
    "$<$<CONFIG:Verified>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "WIN32;"
    "_WINDOWS;"
    "NDEBUG;"
    "AL_LIBTYPE_STATIC;"
    "AL_BUILD_LIBRARY;"
    "AL_ALEXT_PROTOTYPES;"
    "ALC_API=;"
    "AL_API=;"
    "_WIN32;"
    "NOMINMAX;"
    "RESTRICT=__restrict;"
    "_CRT_SECURE_NO_WARNINGS;"
    "_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
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
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX11>:
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
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX8>:
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
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX9>:
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
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:ProfiledDX11>:
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:Release>:
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
            /O2;
            /Oi;
            /GF;
            /GT;
            /arch:AVX;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:Verified>:
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /ZI
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /ZI
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /ZI
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oi-;
            /GF-;
            /Oy-;
            /Gy;
            /ZI
        >
        /permissive-;
        /std:c++latest;
        /EHsc
        /Gm-;
        /W4;
        /wd4065;
        /wd4127;
        /wd4268;
        /wd4324;
        /wd5030;
        /wd5051;
        /w14640;
        /Y-
    )
endif()

