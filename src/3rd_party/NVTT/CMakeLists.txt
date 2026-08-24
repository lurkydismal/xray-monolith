set(PROJECT_NAME NVTT)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "src/nvtt/squish/singlecolourlookup.inl"
)
source_group("" FILES ${no_group_source_files})

set(include
    "include/nvconfig.h"
    "include/nvtt/nvtt.h"
    "include/nvtt/nvtt_wrapper.h"
)
source_group("include" FILES ${include})

set(src
    "src/nvcore/BitArray.h"
    "src/nvcore/Containers.h"
    "src/nvcore/Debug.cpp"
    "src/nvcore/Debug.h"
    "src/nvcore/DefsGnucDarwin.h"
    "src/nvcore/DefsGnucLinux.h"
    "src/nvcore/DefsGnucWin32.h"
    "src/nvcore/DefsVcWin32.h"
    "src/nvcore/Library.cpp"
    "src/nvcore/Library.h"
    "src/nvcore/Memory.cpp"
    "src/nvcore/Memory.h"
    "src/nvcore/nvcore.h"
    "src/nvcore/poshlib/posh.c"
    "src/nvcore/poshlib/posh.h"
    "src/nvcore/Prefetch.h"
    "src/nvcore/Ptr.h"
    "src/nvcore/Radix.cpp"
    "src/nvcore/Radix.h"
    "src/nvcore/StdStream.h"
    "src/nvcore/Stream.h"
    "src/nvcore/StrLib.cpp"
    "src/nvcore/StrLib.h"
    "src/nvcore/TextReader.cpp"
    "src/nvcore/TextReader.h"
    "src/nvcore/TextWriter.cpp"
    "src/nvcore/TextWriter.h"
    "src/nvcore/Tokenizer.cpp"
    "src/nvcore/Tokenizer.h"
    "src/nvimage/BlockDXT.cpp"
    "src/nvimage/BlockDXT.h"
    "src/nvimage/ColorBlock.cpp"
    "src/nvimage/ColorBlock.h"
    "src/nvimage/ConeMap.h"
    "src/nvimage/DirectDrawSurface.cpp"
    "src/nvimage/DirectDrawSurface.h"
    "src/nvimage/Filter.cpp"
    "src/nvimage/Filter.h"
    "src/nvimage/FloatImage.cpp"
    "src/nvimage/FloatImage.h"
    "src/nvimage/HoleFilling.cpp"
    "src/nvimage/HoleFilling.h"
    "src/nvimage/Image.cpp"
    "src/nvimage/Image.h"
    "src/nvimage/ImageIO.cpp"
    "src/nvimage/ImageIO.h"
    "src/nvimage/NormalMap.cpp"
    "src/nvimage/NormalMap.h"
    "src/nvimage/NormalMipmap.cpp"
    "src/nvimage/NormalMipmap.h"
    "src/nvimage/nvimage.h"
    "src/nvimage/PixelFormat.h"
    "src/nvimage/PsdFile.h"
    "src/nvimage/Quantize.cpp"
    "src/nvimage/Quantize.h"
    "src/nvimage/TgaFile.h"
    "src/nvmath/Basis.cpp"
    "src/nvmath/Basis.h"
    "src/nvmath/Box.h"
    "src/nvmath/Color.h"
    "src/nvmath/Matrix.h"
    "src/nvmath/Montecarlo.cpp"
    "src/nvmath/Montecarlo.h"
    "src/nvmath/nvmath.h"
    "src/nvmath/Plane.cpp"
    "src/nvmath/Plane.h"
    "src/nvmath/Quaternion.h"
    "src/nvmath/Random.cpp"
    "src/nvmath/Random.h"
    "src/nvmath/SphericalHarmonic.cpp"
    "src/nvmath/SphericalHarmonic.h"
    "src/nvmath/Triangle.cpp"
    "src/nvmath/Triangle.h"
    "src/nvmath/TriBox.cpp"
    "src/nvmath/Vector.h"
    "src/nvtt/CompressDXT.cpp"
    "src/nvtt/CompressDXT.h"
    "src/nvtt/CompressionOptions.cpp"
    "src/nvtt/CompressionOptions.h"
    "src/nvtt/Compressor.cpp"
    "src/nvtt/Compressor.h"
    "src/nvtt/CompressRGB.cpp"
    "src/nvtt/CompressRGB.h"
    "src/nvtt/cuda/Bitmaps.h"
    "src/nvtt/cuda/CudaCompressDXT.cpp"
    "src/nvtt/cuda/CudaCompressDXT.h"
    "src/nvtt/cuda/CudaMath.h"
    "src/nvtt/cuda/CudaUtils.cpp"
    "src/nvtt/cuda/CudaUtils.h"
    "src/nvtt/InputOptions.cpp"
    "src/nvtt/InputOptions.h"
    "src/nvtt/nvtt.cpp"
    "src/nvtt/nvtt.h"
    "src/nvtt/nvtt_wrapper.cpp"
    "src/nvtt/nvtt_wrapper.h"
    "src/nvtt/OptimalCompressDXT.cpp"
    "src/nvtt/OptimalCompressDXT.h"
    "src/nvtt/OutputOptions.cpp"
    "src/nvtt/OutputOptions.h"
    "src/nvtt/QuickCompressDXT.cpp"
    "src/nvtt/QuickCompressDXT.h"
    "src/nvtt/SingleColorLookup.h"
    "src/nvtt/squish/alpha.cpp"
    "src/nvtt/squish/alpha.h"
    "src/nvtt/squish/clusterfit.cpp"
    "src/nvtt/squish/clusterfit.h"
    "src/nvtt/squish/colourblock.cpp"
    "src/nvtt/squish/colourblock.h"
    "src/nvtt/squish/colourfit.cpp"
    "src/nvtt/squish/colourfit.h"
    "src/nvtt/squish/colourset.cpp"
    "src/nvtt/squish/colourset.h"
    "src/nvtt/squish/config.h"
    "src/nvtt/squish/fastclusterfit.cpp"
    "src/nvtt/squish/fastclusterfit.h"
    "src/nvtt/squish/maths.cpp"
    "src/nvtt/squish/maths.h"
    "src/nvtt/squish/rangefit.cpp"
    "src/nvtt/squish/rangefit.h"
    "src/nvtt/squish/simd.h"
    "src/nvtt/squish/simd_3dnow.h"
    "src/nvtt/squish/simd_sse.h"
    "src/nvtt/squish/simd_ve.h"
    "src/nvtt/squish/singlechannelfit.cpp"
    "src/nvtt/squish/singlechannelfit.h"
    "src/nvtt/squish/singlecolourfit.cpp"
    "src/nvtt/squish/singlecolourfit.h"
    "src/nvtt/squish/squish.cpp"
    "src/nvtt/squish/squish.h"
    "src/nvtt/squish/weightedclusterfit.cpp"
    "src/nvtt/squish/weightedclusterfit.h"
)
if(ENABLE_DEBUG_OLD_RUNTIME)
    list(APPEND src src/nvimage/ConeMap.cpp)
endif()
source_group("src" FILES ${src})

set(ALL_FILES
    ${no_group_source_files}
    ${include}
    ${src}
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

set(ROOT_NAMESPACE nvtt)

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
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     INTERPROCEDURAL_OPTIMIZATION_DX10             "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX10AVX          "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX11             "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX11AVX          "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX8              "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX8AVX           "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX9              "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_DX9AVX           "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_PROFILEDDX11     "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_RELEASE          "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_RELEASEAVX       "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIED         "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11     "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11ASAN "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX8      "TRUE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX9      "TRUE"
# )
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nvcore;"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/nvtt/squish"
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
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "WIN32;"
    "NDEBUG;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(IS_CLANG_CL_MINGW OR IS_CLANG_CL_MSVC OR IS_MSVC)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:DX10>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX10AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX11AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX8AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:DX9AVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Zi
        >
        $<$<CONFIG:Release>:
            ${XRAY_OPTIMIZATION_FLAG};
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy;
            /Zi;
            /Ob3
        >
        $<$<CONFIG:ReleaseAVX>:
            ${XRAY_OPTIMIZATION_FLAG};
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
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        /wd4005
    )
    target_link_options(${PROJECT_NAME} PRIVATE
    )
elseif(IS_CLANG_MINGW OR IS_CLANG_MSVC)
    xray_target_compile_options(${PROJECT_NAME})
    xray_target_link_options(${PROJECT_NAME})
endif()

