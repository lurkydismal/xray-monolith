set(PROJECT_NAME libjpeg)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "ansi2knr.c"
    "cdjpeg.c"
    "cjpeg.c"
    "ckconfig.c"
    "djpeg.c"
    "jcapimin.c"
    "jcapistd.c"
    "jccoefct.c"
    "jccolor.c"
    "jcdctmgr.c"
    "jchuff.c"
    "jcinit.c"
    "jcmainct.c"
    "jcmarker.c"
    "jcmaster.c"
    "jcomapi.c"
    "jconfig.h"
    "jcparam.c"
    "jcphuff.c"
    "jcprepct.c"
    "jcsample.c"
    "jctrans.c"
    "jdapimin.c"
    "jdapistd.c"
    "jdatadst.c"
    "jdatasrc.c"
    "jdcoefct.c"
    "jdcolor.c"
    "jddctmgr.c"
    "jdhuff.c"
    "jdinput.c"
    "jdmainct.c"
    "jdmarker.c"
    "jdmaster.c"
    "jdmerge.c"
    "jdphuff.c"
    "jdpostct.c"
    "jdsample.c"
    "jdtrans.c"
    "jerror.c"
    "jfdctflt.c"
    "jfdctfst.c"
    "jfdctint.c"
    "jidctflt.c"
    "jidctfst.c"
    "jidctint.c"
    "jidctred.c"
    "jmemansi.c"
    "jmemmgr.c"
    "jmemname.c"
    "jmemnobs.c"
    "jpegtran.c"
    "jquant1.c"
    "jquant2.c"
    "jutils.c"
    "rdbmp.c"
    "rdcolmap.c"
    "rdgif.c"
    "rdjpgcom.c"
    "rdppm.c"
    "rdrle.c"
    "rdswitch.c"
    "rdtarga.c"
    "transupp.c"
    "wrbmp.c"
    "wrgif.c"
    "wrjpgcom.c"
    "wrppm.c"
    "wrrle.c"
    "wrtarga.c"
)
source_group("" FILES ${no_group_source_files})

set(src
    "cderror.h"
    "cdjpeg.h"
    "jchuff.h"
    "jdct.h"
    "jdhuff.h"
    "jerror.h"
    "jinclude.h"
    "jmemsys.h"
    "jmorecfg.h"
    "jpegint.h"
    "jpeglib.h"
    "jversion.h"
    "transupp.h"
)
source_group("src" FILES ${src})

set(ALL_FILES
    ${no_group_source_files}
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

set(ROOT_NAMESPACE libjpeg)

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
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER;"
        "_VC80_UPGRADE=0x0710;"
        "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS"
    ">"
    "$<$<CONFIG:Verified>:"
        "USE_VERIFY_IN_RELEASE;"
        "_VC80_UPGRADE=0x0710;"
        "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "USE_VERIFY_IN_RELEASE;"
        "_VC80_UPGRADE=0x0710;"
        "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION;"
        "USE_VERIFY_IN_RELEASE;"
        "_VC80_UPGRADE=0x0710;"
        "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "USE_VERIFY_IN_RELEASE;"
        "_VC80_UPGRADE=0x0710;"
        "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "USE_VERIFY_IN_RELEASE;"
        "_VC80_UPGRADE=0x0710;"
        "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;"
        "_MBCS"
    ">"
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
            /Ob3
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
            /Ob3
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
            /Ob3
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
            /Zi
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
            /Ob3
        >
        $<$<CONFIG:Verified>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI
        >
        $<$<CONFIG:VerifiedDX11>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI
        >
        $<$<CONFIG:VerifiedDX9>:
            /GL-;
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W3;
            /ZI
        >
        /std:c++17
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /OPT:REF;
        /OPT:ICF
    )
endif()

