set(PROJECT_NAME xrRender_R1)

################################################################################
# Source groups
################################################################################
set(Headers
    "../../Include/R_light.h"
    "../../Include/xrRender/animation_blend.h"
    "../../Include/xrRender/animation_motion.h"
    "../../Include/xrRender/ApplicationRender.h"
    "../../Include/xrRender/ConsoleRender.h"
    "../../Include/xrRender/DebugRender.h"
    "../../Include/xrRender/DebugShader.h"
    "../../Include/xrRender/DrawUtils.h"
    "../../Include/xrRender/EnvironmentRender.h"
    "../../Include/xrRender/FactoryPtr.h"
    "../../Include/xrRender/FontRender.h"
    "../../Include/xrRender/ImGuiRender.h"
    "../../Include/xrRender/Kinematics.h"
    "../../Include/xrRender/KinematicsAnimated.h"
    "../../Include/xrRender/LensFlareRender.h"
    "../../Include/xrRender/ObjectSpaceRender.h"
    "../../Include/xrRender/ParticleCustom.h"
    "../../Include/xrRender/particles_systems_library_interface.hpp"
    "../../Include/xrRender/RainRender.h"
    "../../Include/xrRender/RenderDetailModel.h"
    "../../Include/xrRender/RenderDeviceRender.h"
    "../../Include/xrRender/RenderFactory.h"
    "../../Include/xrRender/RenderVisual.h"
    "../../Include/xrRender/StatGraphRender.h"
    "../../Include/xrRender/StatsRender.h"
    "../../Include/xrRender/ThunderboltDescRender.h"
    "../../Include/xrRender/ThunderboltRender.h"
    "../../Include/xrRender/UIRender.h"
    "../../Include/xrRender/UISequenceVideoItem.h"
    "../../Include/xrRender/UIShader.h"
    "../../Include/xrRender/WallMarkArray.h"
    "../xrRender/Animation.h"
    "../xrRender/AnimationKeyCalculate.h"
    "../xrRender/Blender_BmmD.h"
    "../xrRender/Blender_detail_still.h"
    "../xrRender/Blender_Editor_Selection.h"
    "../xrRender/Blender_Editor_Wire.h"
    "../xrRender/Blender_Lm(EbB).h"
    "../xrRender/Blender_Model_EbB.h"
    "../xrRender/Blender_Particle.h"
    "../xrRender/Blender_Screen_SET.h"
    "../xrRender/Blender_tree.h"
    "../xrRender/blenders/Blender.h"
    "../xrRender/blenders/Blender_CLSID.h"
    "../xrRender/blenders/Blender_Recorder.h"
    "../xrRender/CHudInitializer.h"
    "../xrRender/cl_intersect.h"
    "../xrRender/ColorMapManager.h"
    "../xrRender/D3DUtils.h"
    "../xrRender/DetailFormat.h"
    "../xrRender/DetailManager.h"
    "../xrRender/DetailModel.h"
    "../xrRender/du_box.h"
    "../xrRender/du_cone.h"
    "../xrRender/du_cylinder.h"
    "../xrRender/du_sphere.h"
    "../xrRender/du_sphere_part.h"
    "../xrRender/dxApplicationRender.h"
    "../xrRender/dxConsoleRender.h"
    "../xrRender/dxDebugRender.h"
    "../xrRender/dxEnvironmentRender.h"
    "../xrRender/dxFontRender.h"
    "../xrRender/dxImGuiRender.h"
    "../xrRender/dxLensFlareRender.h"
    "../xrRender/dxObjectSpaceRender.h"
    "../xrRender/dxParticleCustom.h"
    "../xrRender/dxRainRender.h"
    "../xrRender/dxRenderDeviceRender.h"
    "../xrRender/dxRenderFactory.h"
    "../xrRender/dxStatGraphRender.h"
    "../xrRender/dxStatsRender.h"
    "../xrRender/dxThunderboltDescRender.h"
    "../xrRender/dxThunderboltRender.h"
    "../xrRender/dxUIRender.h"
    "../xrRender/dxUISequenceVideoItem.h"
    "../xrRender/dxUIShader.h"
    "../xrRender/dxWallMarkArray.h"
    "../xrRender/ETextureParams.h"
    "../xrRender/FBasicVisual.h"
    "../xrRender/FHierrarhyVisual.h"
    "../xrRender/FLOD.h"
    "../xrRender/FProgressive.h"
    "../xrRender/FSkinned.h"
    "../xrRender/FTreeVisual.h"
    "../xrRender/FVF.h"
    "../xrRender/FVisual.h"
    "../xrRender/gifPlayer.h"
    "../xrRender/HOM.h"
    "../xrRender/HW.h"
    "../xrRender/HWCaps.h"
    "../xrRender/IRenderDetailModel.h"
    "../xrRender/KinematicAnimatedDefs.h"
    "../xrRender/light.h"
    "../xrRender/Light_DB.h"
    "../xrRender/Light_Package.h"
    "../xrRender/LightTrack.h"
    "../xrRender/ModelPool.h"
    "../xrRender/NvTriStrip.h"
    "../xrRender/NvTriStripObjects.h"
    "../xrRender/occRasterizer.h"
    "../xrRender/ParticleEffect.h"
    "../xrRender/ParticleEffectActions.h"
    "../xrRender/ParticleEffectDef.h"
    "../xrRender/ParticleGroup.h"
    "../xrRender/PSLibrary.h"
    "../xrRender/r__dsgraph_manager.h"
    "../xrRender/r__dsgraph_types.h"
    "../xrRender/r__sector.h"
    "../xrRender/R_Backend.h"
    "../xrRender/R_Backend_hemi.h"
    "../xrRender/R_Backend_Runtime.h"
    "../xrRender/R_Backend_tree.h"
    "../xrRender/R_Backend_xform.h"
    "../xrRender/r_constants.h"
    "../xrRender/r_constants_cache.h"
    "../xrRender/R_DStreams.h"
    "../xrRender/ResourceManager.h"
    "../xrRender/SH_Atomic.h"
    "../xrRender/SH_Constant.h"
    "../xrRender/SH_Matrix.h"
    "../xrRender/SH_RT.h"
    "../xrRender/SH_Texture.h"
    "../xrRender/Shader.h"
    "../xrRender/SkeletonAnimated.h"
    "../xrRender/SkeletonCustom.h"
    "../xrRender/SkeletonX.h"
    "../xrRender/SkeletonXVertRender.h"
    "../xrRender/stats_manager.h"
    "../xrRender/TextureDescrManager.h"
    "../xrRender/tga.h"
    "../xrRender/tss.h"
    "../xrRender/tss_def.h"
    "../xrRender/VertexCache.h"
    "../xrRender/WallmarksEngine.h"
    "../xrRender/xr_effgamma.h"
    "../xrRender/xrD3DDefs.h"
    "../xrRender/xrRender_console.h"
    "../xrRender/xrStripify.h"
    "../xrRenderDX9/dx9R_Backend_Runtime.h"
    "../xrRenderDX9/dx9r_constants_cache.h"
    "Blender_Blur.h"
    "Blender_default_aref.h"
    "Blender_LaEmB.h"
    "Blender_Model.h"
    "Blender_Screen_GRAY.h"
    "Blender_Shadow_World.h"
    "Blender_Vertex.h"
    "Blender_Vertex_aref.h"
    "BlenderDefault.h"
    "FStaticRender.h"
    "FStaticRender_RenderTarget.h"
    "GlowManager.h"
    "LightPPA.h"
    "LightProjector.h"
    "LightShadows.h"
    "stdafx.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "../../xrEngine/ai_script_lua_debug.cpp"
    "../../xrEngine/ai_script_lua_extension.cpp"
    "../xrRender/Animation.cpp"
    "../xrRender/Blender_BmmD.cpp"
    "../xrRender/Blender_detail_still.cpp"
    "../xrRender/Blender_Editor_Selection.cpp"
    "../xrRender/Blender_Editor_Wire.cpp"
    "../xrRender/Blender_Lm(EbB).cpp"
    "../xrRender/Blender_Model_EbB.cpp"
    "../xrRender/Blender_Particle.cpp"
    "../xrRender/Blender_Recorder_R2.cpp"
    "../xrRender/Blender_Recorder_StandartBinding.cpp"
    "../xrRender/Blender_Screen_SET.cpp"
    "../xrRender/Blender_tree.cpp"
    "../xrRender/blenders/Blender.cpp"
    "../xrRender/blenders/Blender_Palette.cpp"
    "../xrRender/blenders/Blender_Recorder.cpp"
    "../xrRender/CHudInitializer.cpp"
    "../xrRender/ColorMapManager.cpp"
    "../xrRender/D3DUtils.cpp"
    "../xrRender/DetailManager.cpp"
    "../xrRender/DetailManager_CACHE.cpp"
    "../xrRender/DetailManager_Decompress.cpp"
    "../xrRender/DetailManager_soft.cpp"
    "../xrRender/DetailManager_VS.cpp"
    "../xrRender/DetailModel.cpp"
    "../xrRender/du_box.cpp"
    "../xrRender/du_cone.cpp"
    "../xrRender/du_cylinder.cpp"
    "../xrRender/du_sphere.cpp"
    "../xrRender/du_sphere_part.cpp"
    "../xrRender/dxApplicationRender.cpp"
    "../xrRender/dxConsoleRender.cpp"
    "../xrRender/dxDebugRender.cpp"
    "../xrRender/dxEnvironmentRender.cpp"
    "../xrRender/dxFontRender.cpp"
    "../xrRender/dxImGuiRender.cpp"
    "../xrRender/dxLensFlareRender.cpp"
    "../xrRender/dxObjectSpaceRender.cpp"
    "../xrRender/dxParticleCustom.cpp"
    "../xrRender/dxRainRender.cpp"
    "../xrRender/dxRenderDeviceRender.cpp"
    "../xrRender/dxRenderFactory.cpp"
    "../xrRender/dxStatGraphRender.cpp"
    "../xrRender/dxStatsRender.cpp"
    "../xrRender/dxThunderboltDescRender.cpp"
    "../xrRender/dxThunderboltRender.cpp"
    "../xrRender/dxUIRender.cpp"
    "../xrRender/dxUISequenceVideoItem.cpp"
    "../xrRender/dxUIShader.cpp"
    "../xrRender/dxWallMarkArray.cpp"
    "../xrRender/ETextureParams.cpp"
    "../xrRender/FBasicVisual.cpp"
    "../xrRender/FHierrarhyVisual.cpp"
    "../xrRender/FLOD.cpp"
    "../xrRender/FProgressive.cpp"
    "../xrRender/FSkinned.cpp"
    "../xrRender/FTreeVisual.cpp"
    "../xrRender/FVisual.cpp"
    "../xrRender/gifPlayer.cpp"
    "../xrRender/HOM.cpp"
    "../xrRender/HW.cpp"
    "../xrRender/HWCaps.cpp"
    "../xrRender/light.cpp"
    "../xrRender/Light_DB.cpp"
    "../xrRender/Light_Package.cpp"
    "../xrRender/LightTrack.cpp"
    "../xrRender/ModelPool.cpp"
    "../xrRender/NvTriStrip.cpp"
    "../xrRender/NvTriStripObjects.cpp"
    "../xrRender/occRasterizer.cpp"
    "../xrRender/occRasterizer_core.cpp"
    "../xrRender/ParticleEffect.cpp"
    "../xrRender/ParticleEffectActions.cpp"
    "../xrRender/ParticleEffectDef.cpp"
    "../xrRender/ParticleGroup.cpp"
    "../xrRender/PSLibrary.cpp"
    "../xrRender/r__dsgraph_build.cpp"
    "../xrRender/r__dsgraph_manager.cpp"
    "../xrRender/r__dsgraph_render.cpp"
    "../xrRender/r__dsgraph_render_lods.cpp"
    "../xrRender/r__screenshot.cpp"
    "../xrRender/r__sector.cpp"
    "../xrRender/r__sector_detect.cpp"
    "../xrRender/R_Backend.cpp"
    "../xrRender/R_Backend_DBG.cpp"
    "../xrRender/R_Backend_hemi.cpp"
    "../xrRender/R_Backend_Runtime.cpp"
    "../xrRender/R_Backend_tree.cpp"
    "../xrRender/R_Backend_xform.cpp"
    "../xrRender/r_constants.cpp"
    "../xrRender/R_DStreams.cpp"
    "../xrRender/ResourceManager.cpp"
    "../xrRender/ResourceManager_Loader.cpp"
    "../xrRender/ResourceManager_Reset.cpp"
    "../xrRender/ResourceManager_Resources.cpp"
    "../xrRender/ResourceManager_Scripting.cpp"
    "../xrRender/SH_Atomic.cpp"
    "../xrRender/SH_Constant.cpp"
    "../xrRender/SH_Matrix.cpp"
    "../xrRender/SH_RT.cpp"
    "../xrRender/SH_Texture.cpp"
    "../xrRender/Shader.cpp"
    "../xrRender/SkeletonAnimated.cpp"
    "../xrRender/SkeletonCustom.cpp"
    "../xrRender/SkeletonRigid.cpp"
    "../xrRender/SkeletonX.cpp"
    "../xrRender/stats_manager.cpp"
    "../xrRender/TextureDescrManager.cpp"
    "../xrRender/tga.cpp"
    "../xrRender/tss_def.cpp"
    "../xrRender/VertexCache.cpp"
    "../xrRender/WallmarksEngine.cpp"
    "../xrRender/xr_effgamma.cpp"
    "../xrRender/xrRender_console.cpp"
    "../xrRender/xrStripify.cpp"
    "../xrRenderDX9/dx9r_constants_cache.cpp"
    "../xrRenderDX9/dx9Texture.cpp"
    "Blender_Blur.cpp"
    "Blender_default_aref.cpp"
    "Blender_LaEmB.cpp"
    "Blender_Model.cpp"
    "Blender_Screen_GRAY.cpp"
    "Blender_Shadow_World.cpp"
    "Blender_Vertex.cpp"
    "Blender_Vertex_aref.cpp"
    "BlenderDefault.cpp"
    "FStaticRender.cpp"
    "FStaticRender_Blenders.cpp"
    "FStaticRender_Loader.cpp"
    "FStaticRender_RenderTarget.cpp"
    "GlowManager.cpp"
    "LightPPA.cpp"
    "LightProjector.cpp"
    "LightShadows.cpp"
    "stdafx.cpp"
    "xrRender_R1.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} DX10             "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX11             "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX8              "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX9              "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} Release          "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} Verified         "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "${CMAKE_SOURCE_DIR}/Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "${CMAKE_SOURCE_DIR}/Common.cmake")

set(ROOT_NAMESPACE xrRender_R1)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX10AVX          "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11             "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11AVX          "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8              "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8AVX           "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9              "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9AVX           "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE          "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASEAVX       "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIED         "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "$ENV{xrGameDir}bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DX10             "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX10AVX          "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11             "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX11AVX          "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8              "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX8AVX           "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9              "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_DX9AVX           "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_PROFILEDDX11     "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASE          "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_RELEASEAVX       "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIED         "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11     "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX11ASAN "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX8      "$ENV{xrLibDir}${TARGET_NAME}"
    ARCHIVE_OUTPUT_NAME_VERIFIEDDX9      "$ENV{xrLibDir}${TARGET_NAME}"
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
    $<$<CONFIG:Verified>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX11>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX11ASAN>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX8>:
        MultiThreadedDLL
    >
    $<$<CONFIG:VerifiedDX9>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Verified>,$<CONFIG:VerifiedDX11>,$<CONFIG:VerifiedDX11ASAN>,$<CONFIG:VerifiedDX8>,$<CONFIG:VerifiedDX9>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/mnt/hdd/Projects/xray-monolith/src/3rd party/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/mnt/hdd/Projects/xray-monolith/src/3rd party/luajit-2/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/mnt/hdd/Projects/xray-monolith/src/3rd party/luabind;"
    "${CMAKE_CURRENT_SOURCE_DIR}/mnt/hdd/Projects/xray-monolith/src/xrCore;"
    "$ENV{xrSdkDir}include;"
    "$ENV{XRAY_16X_LIBS}OpenAutomate/inc;"
    "$ENV{XRAY_16X_LIBS}nvapi"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER"
    ">"
    "$<$<CONFIG:Verified>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE;"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE"
    ">"
    "WIN32;"
    "NDEBUG;"
    "_WINDOWS;"
    "_USRDLL;"
    "XRRENDER_R1_EXPORTS;"
    "_SECURE_SCL=0;"
    "_MBCS"
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
            /W4;
            /ZI;
            /GS;
            /Zc:inline-
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
            /GS;
            /Zc:inline-
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
            /GS;
            /Zc:inline-
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
            /GS;
            /Zc:inline-
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
            /GS;
            /Zc:inline-
        >
        /std:c++17
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /NODEFAULTLIB:LIBCMT;
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    xrCPU_Pipe
    xrParticles
    xrAPI
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "d3dx9;"
    "nvapi"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/3rd party/luajit-2/src/;"
    "$ENV{xrSdkDir}libraries/x64;"
    "$ENV{xrLibDir};"
    "${CMAKE_SOURCE_DIR}/x64/Release"
)

