set(PROJECT_NAME crypto)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "crypto.h"
    "crypto_api_def.h"
    "openssl/openssl/aes.h"
    "openssl/openssl/asn1.h"
    "openssl/openssl/asn1_mac.h"
    "openssl/openssl/asn1t.h"
    "openssl/openssl/bio.h"
    "openssl/openssl/blowfish.h"
    "openssl/openssl/bn.h"
    "openssl/openssl/buffer.h"
    "openssl/openssl/cast.h"
    "openssl/openssl/comp.h"
    "openssl/openssl/conf.h"
    "openssl/openssl/conf_api.h"
    "openssl/openssl/crypto.h"
    "openssl/openssl/des.h"
    "openssl/openssl/des_old.h"
    "openssl/openssl/dh.h"
    "openssl/openssl/dsa.h"
    "openssl/openssl/dso.h"
    "openssl/openssl/dtls1.h"
    "openssl/openssl/e_os2.h"
    "openssl/openssl/ebcdic.h"
    "openssl/openssl/ec.h"
    "openssl/openssl/ecdh.h"
    "openssl/openssl/ecdsa.h"
    "openssl/openssl/engine.h"
    "openssl/openssl/err.h"
    "openssl/openssl/evp.h"
    "openssl/openssl/hmac.h"
    "openssl/openssl/idea.h"
    "openssl/openssl/krb5_asn.h"
    "openssl/openssl/kssl.h"
    "openssl/openssl/lhash.h"
    "openssl/openssl/md2.h"
    "openssl/openssl/md4.h"
    "openssl/openssl/md5.h"
    "openssl/openssl/obj_mac.h"
    "openssl/openssl/objects.h"
    "openssl/openssl/ocsp.h"
    "openssl/openssl/opensslconf.h"
    "openssl/openssl/opensslv.h"
    "openssl/openssl/ossl_typ.h"
    "openssl/openssl/pem.h"
    "openssl/openssl/pem2.h"
    "openssl/openssl/pkcs12.h"
    "openssl/openssl/pkcs7.h"
    "openssl/openssl/pq_compat.h"
    "openssl/openssl/pqueue.h"
    "openssl/openssl/rand.h"
    "openssl/openssl/rc2.h"
    "openssl/openssl/rc4.h"
    "openssl/openssl/ripemd.h"
    "openssl/openssl/rsa.h"
    "openssl/openssl/safestack.h"
    "openssl/openssl/sha.h"
    "openssl/openssl/ssl.h"
    "openssl/openssl/ssl2.h"
    "openssl/openssl/ssl23.h"
    "openssl/openssl/ssl3.h"
    "openssl/openssl/stack.h"
    "openssl/openssl/store.h"
    "openssl/openssl/symhacks.h"
    "openssl/openssl/tls1.h"
    "openssl/openssl/tmdiff.h"
    "openssl/openssl/txt_db.h"
    "openssl/openssl/ui.h"
    "openssl/openssl/ui_compat.h"
    "openssl/openssl/x509.h"
    "openssl/openssl/x509_vfy.h"
    "openssl/openssl/x509v3.h"
    "openssl/src/bio_lcl.h"
    "openssl/src/bn_lcl.h"
    "openssl/src/bn_prime.h"
    "openssl/src/cryptlib.h"
    "openssl/src/e_os.h"
    "openssl/src/eng_int.h"
    "openssl/src/evp_locl.h"
    "openssl/src/md32_common.h"
    "openssl/src/obj_dat.h"
    "openssl/src/rand_lcl.h"
    "openssl/src/sha_locl.h"
    "xr_dsa.h"
    "xr_sha.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "crypto.cpp"
    "openssl/src/a_bitstr.c"
    "openssl/src/a_d2i_fp.c"
    "openssl/src/a_dup.c"
    "openssl/src/a_int.c"
    "openssl/src/a_object.c"
    "openssl/src/a_type.c"
    "openssl/src/asn1_lib.c"
    "openssl/src/b_print.c"
    "openssl/src/bio_lib.c"
    "openssl/src/bn_add.c"
    "openssl/src/bn_asm.c"
    "openssl/src/bn_blind.c"
    "openssl/src/bn_ctx.c"
    "openssl/src/bn_div.c"
    "openssl/src/bn_exp.c"
    "openssl/src/bn_exp2.c"
    "openssl/src/bn_gcd.c"
    "openssl/src/bn_kron.c"
    "openssl/src/bn_lib.c"
    "openssl/src/bn_mod.c"
    "openssl/src/bn_mont.c"
    "openssl/src/bn_mul.c"
    "openssl/src/bn_prime.c"
    "openssl/src/bn_print.c"
    "openssl/src/bn_rand.c"
    "openssl/src/bn_recp.c"
    "openssl/src/bn_shift.c"
    "openssl/src/bn_sqr.c"
    "openssl/src/bn_sqrt.c"
    "openssl/src/bn_word.c"
    "openssl/src/bss_file.c"
    "openssl/src/buf_str.c"
    "openssl/src/buffer.c"
    "openssl/src/cryptlib.c"
    "openssl/src/dh_check.c"
    "openssl/src/dh_key.c"
    "openssl/src/dh_lib.c"
    "openssl/src/digest.c"
    "openssl/src/dsa_asn1.c"
    "openssl/src/dsa_depr.c"
    "openssl/src/dsa_err.c"
    "openssl/src/dsa_gen.c"
    "openssl/src/dsa_key.c"
    "openssl/src/dsa_lib.c"
    "openssl/src/dsa_ossl.c"
    "openssl/src/dsa_sign.c"
    "openssl/src/dsa_utl.c"
    "openssl/src/dsa_vrf.c"
    "openssl/src/eng_ctrl.c"
    "openssl/src/eng_init.c"
    "openssl/src/eng_lib.c"
    "openssl/src/eng_list.c"
    "openssl/src/eng_table.c"
    "openssl/src/err.c"
    "openssl/src/err_def.c"
    "openssl/src/ex_data.c"
    "openssl/src/lhash.c"
    "openssl/src/m_sha1.c"
    "openssl/src/md_rand.c"
    "openssl/src/mem.c"
    "openssl/src/mem_clr.c"
    "openssl/src/obj_dat.c"
    "openssl/src/obj_lib.c"
    "openssl/src/rand_eng.c"
    "openssl/src/rand_lib.c"
    "openssl/src/rand_win.c"
    "openssl/src/rsa_lib.c"
    "openssl/src/rsa_sign.c"
    "openssl/src/sha1_one.c"
    "openssl/src/sha1dgst.c"
    "openssl/src/sha256.c"
    "openssl/src/sha512.c"
    "openssl/src/sha_dgst.c"
    "openssl/src/sha_one.c"
    "openssl/src/stack.c"
    "openssl/src/tasn_dec.c"
    "openssl/src/tasn_enc.c"
    "openssl/src/tasn_fre.c"
    "openssl/src/tasn_new.c"
    "openssl/src/tasn_typ.c"
    "openssl/src/tasn_utl.c"
    "openssl/src/tb_dh.c"
    "openssl/src/tb_digest.c"
    "openssl/src/tb_dsa.c"
    "openssl/src/tb_rand.c"
    "openssl/src/x_algor.c"
    "openssl/src/x_bignum.c"
    "openssl/src/x_long.c"
    "openssl/src/x_sig.c"
    "xr_dsa.cpp"
    "xr_sha.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
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

set(ROOT_NAMESPACE crypto)

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
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIED         "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11     "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX11ASAN "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX8      "FALSE"
#     INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX9      "FALSE"
# )
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/openssl;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Include"
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
    "CRYPTO_BUILD;"
    "_CRT_SECURE_NO_WARNINGS"
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
            /Zi
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
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Zi
        >
        /std:c++latest;
        /wd4005;
        /wd4996
    )
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    xrCore
)

