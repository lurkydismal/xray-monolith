set(PROJECT_NAME xrRender_R1)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../xrRender/r__dsgraph_manager.cpp"
    "../xrRender/r__dsgraph_manager.h"
    "../xrRenderDX9/dx9Texture.cpp"
)
source_group("" FILES ${no_group_source_files})

set(Core
    "../../Include/xrRender/particles_systems_library_interface.hpp"
    "../xrRender/CHudInitializer.cpp"
    "../xrRender/CHudInitializer.h"
    "../xrRender/gifPlayer.cpp"
    "../xrRender/gifPlayer.h"
    "../xrRender/PSLibrary.cpp"
    "../xrRender/PSLibrary.h"
    "../xrRender/r__dsgraph_build.cpp"
    "../xrRender/r__dsgraph_render.cpp"
    "../xrRender/r__dsgraph_render_lods.cpp"
    "../xrRender/r__dsgraph_types.h"
    "../xrRender/r__screenshot.cpp"
    "../xrRender/tga.cpp"
    "../xrRender/tga.h"
    "FStaticRender.cpp"
    "FStaticRender.h"
    "FStaticRender_Blenders.cpp"
    "FStaticRender_Loader.cpp"
    "FStaticRender_RenderTarget.cpp"
    "FStaticRender_RenderTarget.h"
)
source_group("Core" FILES ${Core})

set(Core__ColorMap
    "../xrRender/ColorMapManager.cpp"
    "../xrRender/ColorMapManager.h"
)
source_group("Core\\ColorMap" FILES ${Core__ColorMap})

set(Details
    "../xrRender/DetailFormat.h"
    "../xrRender/DetailManager.cpp"
    "../xrRender/DetailManager.h"
    "../xrRender/DetailManager_CACHE.cpp"
    "../xrRender/DetailManager_Decompress.cpp"
    "../xrRender/DetailManager_soft.cpp"
    "../xrRender/DetailManager_VS.cpp"
    "../xrRender/DetailModel.cpp"
    "../xrRender/DetailModel.h"
)
source_group("Details" FILES ${Details})

set(Glows
    "GlowManager.cpp"
    "GlowManager.h"
)
source_group("Glows" FILES ${Glows})

set(Interfase_implementations__ApplicationRender
    "../../Include/xrRender/ApplicationRender.h"
    "../xrRender/dxApplicationRender.cpp"
    "../xrRender/dxApplicationRender.h"
)
source_group("Interfase implementations\\ApplicationRender" FILES ${Interfase_implementations__ApplicationRender})

set(Interfase_implementations__ConsoleRender
    "../../Include/xrRender/ConsoleRender.h"
    "../xrRender/dxConsoleRender.cpp"
    "../xrRender/dxConsoleRender.h"
)
source_group("Interfase implementations\\ConsoleRender" FILES ${Interfase_implementations__ConsoleRender})

set(Interfase_implementations__Debug
    "../../Include/xrRender/DebugShader.h"
)
source_group("Interfase implementations\\Debug" FILES ${Interfase_implementations__Debug})

set(Interfase_implementations__Debug__DebugRender
    "../../Include/xrRender/DebugRender.h"
    "../xrRender/dxDebugRender.cpp"
    "../xrRender/dxDebugRender.h"
)
source_group("Interfase implementations\\Debug\\DebugRender" FILES ${Interfase_implementations__Debug__DebugRender})

set(Interfase_implementations__EnvironmentRender
    "../../Include/xrRender/EnvironmentRender.h"
    "../xrRender/dxEnvironmentRender.cpp"
    "../xrRender/dxEnvironmentRender.h"
)
source_group("Interfase implementations\\EnvironmentRender" FILES ${Interfase_implementations__EnvironmentRender})

set(Interfase_implementations__FactoryPtr
    "../../Include/xrRender/FactoryPtr.h"
)
source_group("Interfase implementations\\FactoryPtr" FILES ${Interfase_implementations__FactoryPtr})

set(Interfase_implementations__FontRender
    "../../Include/xrRender/FontRender.h"
    "../xrRender/dxFontRender.cpp"
    "../xrRender/dxFontRender.h"
)
source_group("Interfase implementations\\FontRender" FILES ${Interfase_implementations__FontRender})

set(Interfase_implementations__ImGuiRender
    "../../Include/xrRender/ImGuiRender.h"
    "../xrRender/dxImGuiRender.cpp"
    "../xrRender/dxImGuiRender.h"
)
source_group("Interfase implementations\\ImGuiRender" FILES ${Interfase_implementations__ImGuiRender})

set(Interfase_implementations__LensFlare
    "../../Include/xrRender/LensFlareRender.h"
    "../xrRender/dxLensFlareRender.cpp"
    "../xrRender/dxLensFlareRender.h"
)
source_group("Interfase implementations\\LensFlare" FILES ${Interfase_implementations__LensFlare})

set(Interfase_implementations__ObjectSpaceRender
    "../../Include/xrRender/ObjectSpaceRender.h"
    "../xrRender/dxObjectSpaceRender.cpp"
    "../xrRender/dxObjectSpaceRender.h"
)
source_group("Interfase implementations\\ObjectSpaceRender" FILES ${Interfase_implementations__ObjectSpaceRender})

set(Interfase_implementations__RainRender
    "../../Include/xrRender/RainRender.h"
    "../xrRender/dxRainRender.cpp"
    "../xrRender/dxRainRender.h"
)
source_group("Interfase implementations\\RainRender" FILES ${Interfase_implementations__RainRender})

set(Interfase_implementations__RenderDeviceRender
    "../../Include/xrRender/RenderDeviceRender.h"
    "../xrRender/dxRenderDeviceRender.cpp"
    "../xrRender/dxRenderDeviceRender.h"
)
source_group("Interfase implementations\\RenderDeviceRender" FILES ${Interfase_implementations__RenderDeviceRender})

set(Interfase_implementations__RenderFactory
    "../../Include/xrRender/RenderFactory.h"
    "../xrRender/dxRenderFactory.cpp"
    "../xrRender/dxRenderFactory.h"
)
source_group("Interfase implementations\\RenderFactory" FILES ${Interfase_implementations__RenderFactory})

set(Interfase_implementations__StatGraphRender
    "../../Include/xrRender/StatGraphRender.h"
    "../xrRender/dxStatGraphRender.cpp"
    "../xrRender/dxStatGraphRender.h"
)
source_group("Interfase implementations\\StatGraphRender" FILES ${Interfase_implementations__StatGraphRender})

set(Interfase_implementations__StatsRender
    "../../Include/xrRender/StatsRender.h"
    "../xrRender/dxStatsRender.cpp"
    "../xrRender/dxStatsRender.h"
)
source_group("Interfase implementations\\StatsRender" FILES ${Interfase_implementations__StatsRender})

set(Interfase_implementations__ThunderboltDescRender
    "../../Include/xrRender/ThunderboltDescRender.h"
    "../xrRender/dxThunderboltDescRender.cpp"
    "../xrRender/dxThunderboltDescRender.h"
)
source_group("Interfase implementations\\ThunderboltDescRender" FILES ${Interfase_implementations__ThunderboltDescRender})

set(Interfase_implementations__ThunderboltRender
    "../../Include/xrRender/ThunderboltRender.h"
    "../xrRender/dxThunderboltRender.cpp"
    "../xrRender/dxThunderboltRender.h"
)
source_group("Interfase implementations\\ThunderboltRender" FILES ${Interfase_implementations__ThunderboltRender})

set(Interfase_implementations__UI__UIRender
    "../../Include/xrRender/UIRender.h"
    "../xrRender/dxUIRender.cpp"
    "../xrRender/dxUIRender.h"
)
source_group("Interfase implementations\\UI\\UIRender" FILES ${Interfase_implementations__UI__UIRender})

set(Interfase_implementations__UI__UISequenceVideoItem
    "../../Include/xrRender/UISequenceVideoItem.h"
    "../xrRender/dxUISequenceVideoItem.cpp"
    "../xrRender/dxUISequenceVideoItem.h"
)
source_group("Interfase implementations\\UI\\UISequenceVideoItem" FILES ${Interfase_implementations__UI__UISequenceVideoItem})

set(Interfase_implementations__UI__UIShader
    "../../Include/xrRender/UIShader.h"
    "../xrRender/dxUIShader.cpp"
    "../xrRender/dxUIShader.h"
)
source_group("Interfase implementations\\UI\\UIShader" FILES ${Interfase_implementations__UI__UIShader})

set(Interfase_implementations__WallMarkArray
    "../../Include/xrRender/WallMarkArray.h"
    "../xrRender/dxWallMarkArray.cpp"
    "../xrRender/dxWallMarkArray.h"
)
source_group("Interfase implementations\\WallMarkArray" FILES ${Interfase_implementations__WallMarkArray})

set(Kernel
    "../xrRender/cl_intersect.h"
    "../xrRender/xrD3DDefs.h"
    "../xrRender/xrRender_console.cpp"
    "../xrRender/xrRender_console.h"
    "stdafx.cpp"
    "stdafx.h"
    "xrRender_R1.cpp"
)
source_group("Kernel" FILES ${Kernel})

set(Lights
    "../../Include/R_light.h"
    "../xrRender/light.cpp"
    "../xrRender/light.h"
    "../xrRender/Light_DB.cpp"
    "../xrRender/Light_DB.h"
    "../xrRender/Light_Package.cpp"
    "../xrRender/Light_Package.h"
    "../xrRender/LightTrack.cpp"
    "LightPPA.cpp"
    "LightPPA.h"
    "LightProjector.cpp"
    "LightProjector.h"
    "LightShadows.cpp"
    "LightShadows.h"
)
source_group("Lights" FILES ${Lights})

set(Models
    "../xrRender/LightTrack.h"
    "../xrRender/ModelPool.cpp"
    "../xrRender/ModelPool.h"
)
source_group("Models" FILES ${Models})

set(Models__Visuals
    "../xrRender/FLOD.cpp"
    "../xrRender/FLOD.h"
    "../xrRender/FProgressive.cpp"
    "../xrRender/FProgressive.h"
    "../xrRender/FSkinned.cpp"
    "../xrRender/FSkinned.h"
    "../xrRender/FTreeVisual.cpp"
    "../xrRender/FTreeVisual.h"
    "../xrRender/FVisual.cpp"
    "../xrRender/FVisual.h"
    "../xrRender/ParticleEffect.cpp"
    "../xrRender/ParticleEffect.h"
    "../xrRender/ParticleEffectActions.cpp"
    "../xrRender/ParticleEffectActions.h"
    "../xrRender/ParticleEffectDef.cpp"
    "../xrRender/ParticleEffectDef.h"
    "../xrRender/ParticleGroup.cpp"
    "../xrRender/ParticleGroup.h"
)
source_group("Models\\Visuals" FILES ${Models__Visuals})

set(Refactored__Backend
    "../xrRender/FVF.h"
    "../xrRender/R_Backend.cpp"
    "../xrRender/R_Backend.h"
    "../xrRender/R_Backend_DBG.cpp"
    "../xrRender/R_Backend_hemi.cpp"
    "../xrRender/R_Backend_hemi.h"
    "../xrRender/R_Backend_Runtime.cpp"
    "../xrRender/R_Backend_Runtime.h"
    "../xrRender/R_Backend_tree.cpp"
    "../xrRender/R_Backend_tree.h"
    "../xrRender/R_Backend_xform.cpp"
    "../xrRender/R_Backend_xform.h"
    "../xrRender/R_DStreams.cpp"
    "../xrRender/R_DStreams.h"
    "../xrRenderDX9/dx9R_Backend_Runtime.h"
)
source_group("Refactored\\Backend" FILES ${Refactored__Backend})

set(Refactored__Execution__3D__DebugDraw
    "../../Include/xrRender/DrawUtils.h"
    "../xrRender/D3DUtils.cpp"
    "../xrRender/D3DUtils.h"
    "../xrRender/du_box.cpp"
    "../xrRender/du_box.h"
    "../xrRender/du_cone.cpp"
    "../xrRender/du_cone.h"
    "../xrRender/du_cylinder.cpp"
    "../xrRender/du_cylinder.h"
    "../xrRender/du_sphere.cpp"
    "../xrRender/du_sphere.h"
    "../xrRender/du_sphere_part.cpp"
    "../xrRender/du_sphere_part.h"
)
source_group("Refactored\\Execution & 3D\\DebugDraw" FILES ${Refactored__Execution__3D__DebugDraw})

set(Refactored__Execution__3D__Gamma
    "../xrRender/xr_effgamma.cpp"
    "../xrRender/xr_effgamma.h"
)
source_group("Refactored\\Execution & 3D\\Gamma" FILES ${Refactored__Execution__3D__Gamma})

set(Refactored__Execution__3D__Shaders__Blender
    "../xrRender/Blender_Recorder_R2.cpp"
    "../xrRender/Blender_Recorder_StandartBinding.cpp"
    "../xrRender/blenders/Blender.cpp"
    "../xrRender/blenders/Blender.h"
    "../xrRender/blenders/Blender_CLSID.h"
    "../xrRender/blenders/Blender_Palette.cpp"
    "../xrRender/blenders/Blender_Recorder.cpp"
    "../xrRender/blenders/Blender_Recorder.h"
    "../xrRender/tss.h"
    "../xrRender/tss_def.cpp"
    "../xrRender/tss_def.h"
)
source_group("Refactored\\Execution & 3D\\Shaders\\Blender" FILES ${Refactored__Execution__3D__Shaders__Blender})

set(Refactored__Execution__3D__Shaders__Resources
    "../xrRender/r_constants.cpp"
    "../xrRender/r_constants.h"
    "../xrRender/SH_Atomic.cpp"
    "../xrRender/SH_Atomic.h"
    "../xrRender/SH_Constant.cpp"
    "../xrRender/SH_Constant.h"
    "../xrRender/SH_Matrix.cpp"
    "../xrRender/SH_Matrix.h"
    "../xrRender/SH_RT.cpp"
    "../xrRender/SH_RT.h"
    "../xrRender/SH_Texture.cpp"
    "../xrRender/SH_Texture.h"
    "../xrRender/Shader.cpp"
    "../xrRender/Shader.h"
)
source_group("Refactored\\Execution & 3D\\Shaders\\Resources" FILES ${Refactored__Execution__3D__Shaders__Resources})

set(Refactored__Execution__3D__Shaders__Resources__dx9_R_shader
    "../xrRender/r_constants_cache.h"
    "../xrRenderDX9/dx9r_constants_cache.cpp"
    "../xrRenderDX9/dx9r_constants_cache.h"
)
source_group("Refactored\\Execution & 3D\\Shaders\\Resources\\dx9_R_shader" FILES ${Refactored__Execution__3D__Shaders__Resources__dx9_R_shader})

set(Refactored__Execution__3D__Shaders__ShaderManager
    "../../xrEngine/ai_script_lua_debug.cpp"
    "../../xrEngine/ai_script_lua_extension.cpp"
    "../xrRender/ETextureParams.cpp"
    "../xrRender/ETextureParams.h"
    "../xrRender/ResourceManager.cpp"
    "../xrRender/ResourceManager.h"
    "../xrRender/ResourceManager_Loader.cpp"
    "../xrRender/ResourceManager_Reset.cpp"
    "../xrRender/ResourceManager_Resources.cpp"
    "../xrRender/ResourceManager_Scripting.cpp"
    "../xrRender/TextureDescrManager.cpp"
    "../xrRender/TextureDescrManager.h"
)
source_group("Refactored\\Execution & 3D\\Shaders\\ShaderManager" FILES ${Refactored__Execution__3D__Shaders__ShaderManager})

set(Refactored__Execution__3D__Visuals
    "../../Include/xrRender/ParticleCustom.h"
    "../../Include/xrRender/RenderVisual.h"
    "../xrRender/dxParticleCustom.cpp"
    "../xrRender/dxParticleCustom.h"
    "../xrRender/FBasicVisual.cpp"
    "../xrRender/FBasicVisual.h"
    "../xrRender/FHierrarhyVisual.cpp"
    "../xrRender/FHierrarhyVisual.h"
)
source_group("Refactored\\Execution & 3D\\Visuals" FILES ${Refactored__Execution__3D__Visuals})

set(Refactored__Execution__3D__Visuals__Skeleton
    "../../Include/xrRender/animation_blend.h"
    "../../Include/xrRender/animation_motion.h"
    "../../Include/xrRender/Kinematics.h"
    "../../Include/xrRender/KinematicsAnimated.h"
    "../xrRender/Animation.cpp"
    "../xrRender/Animation.h"
    "../xrRender/AnimationKeyCalculate.h"
    "../xrRender/KinematicAnimatedDefs.h"
    "../xrRender/SkeletonAnimated.cpp"
    "../xrRender/SkeletonAnimated.h"
    "../xrRender/SkeletonCustom.cpp"
    "../xrRender/SkeletonCustom.h"
    "../xrRender/SkeletonRigid.cpp"
    "../xrRender/SkeletonX.cpp"
    "../xrRender/SkeletonX.h"
    "../xrRender/SkeletonXVertRender.h"
)
source_group("Refactored\\Execution & 3D\\Visuals\\Skeleton" FILES ${Refactored__Execution__3D__Visuals__Skeleton})

set(Refactored__HW
    "../xrRender/HW.cpp"
    "../xrRender/HW.h"
    "../xrRender/HWCaps.cpp"
    "../xrRender/HWCaps.h"
)
source_group("Refactored\\HW" FILES ${Refactored__HW})

set(Refactored__Interfaces
    "../../Include/xrRender/RenderDetailModel.h"
    "../xrRender/IRenderDetailModel.h"
)
source_group("Refactored\\Interfaces" FILES ${Refactored__Interfaces})

set(Refactored__stats_manager
    "../xrRender/stats_manager.cpp"
    "../xrRender/stats_manager.h"
)
source_group("Refactored\\stats_manager" FILES ${Refactored__stats_manager})

set(Shading_templates
    "../xrRender/Blender_BmmD.cpp"
    "../xrRender/Blender_BmmD.h"
    "../xrRender/Blender_detail_still.cpp"
    "../xrRender/Blender_detail_still.h"
    "../xrRender/Blender_Editor_Selection.cpp"
    "../xrRender/Blender_Editor_Selection.h"
    "../xrRender/Blender_Editor_Wire.cpp"
    "../xrRender/Blender_Editor_Wire.h"
    "../xrRender/Blender_Lm(EbB).cpp"
    "../xrRender/Blender_Lm(EbB).h"
    "../xrRender/Blender_Model_EbB.cpp"
    "../xrRender/Blender_Model_EbB.h"
    "../xrRender/Blender_Particle.cpp"
    "../xrRender/Blender_Particle.h"
    "../xrRender/Blender_Screen_SET.cpp"
    "../xrRender/Blender_Screen_SET.h"
    "../xrRender/Blender_tree.cpp"
    "../xrRender/Blender_tree.h"
    "Blender_Blur.cpp"
    "Blender_Blur.h"
    "Blender_default_aref.cpp"
    "Blender_default_aref.h"
    "Blender_LaEmB.cpp"
    "Blender_LaEmB.h"
    "Blender_Model.cpp"
    "Blender_Model.h"
    "Blender_Screen_GRAY.cpp"
    "Blender_Screen_GRAY.h"
    "Blender_Shadow_World.cpp"
    "Blender_Shadow_World.h"
    "Blender_Vertex.cpp"
    "Blender_Vertex.h"
    "Blender_Vertex_aref.cpp"
    "Blender_Vertex_aref.h"
    "BlenderDefault.cpp"
    "BlenderDefault.h"
)
source_group("Shading templates" FILES ${Shading_templates})

set(Stripifier
    "../xrRender/NvTriStrip.cpp"
    "../xrRender/NvTriStrip.h"
    "../xrRender/NvTriStripObjects.cpp"
    "../xrRender/NvTriStripObjects.h"
    "../xrRender/VertexCache.cpp"
    "../xrRender/VertexCache.h"
    "../xrRender/xrStripify.cpp"
    "../xrRender/xrStripify.h"
)
source_group("Stripifier" FILES ${Stripifier})

set(Visibility__HOM_Occlusion
    "../xrRender/HOM.cpp"
    "../xrRender/HOM.h"
    "../xrRender/occRasterizer.cpp"
    "../xrRender/occRasterizer.h"
    "../xrRender/occRasterizer_core.cpp"
)
source_group("Visibility\\HOM Occlusion" FILES ${Visibility__HOM_Occlusion})

set(Visibility__Sector/Portal
    "../xrRender/r__sector.cpp"
    "../xrRender/r__sector.h"
    "../xrRender/r__sector_detect.cpp"
)
source_group("Visibility\\Sector/Portal" FILES ${Visibility__Sector/Portal})

set(Wallmarks
    "../xrRender/WallmarksEngine.cpp"
    "../xrRender/WallmarksEngine.h"
)
source_group("Wallmarks" FILES ${Wallmarks})

set(ALL_FILES
    ${no_group_source_files}
    ${Core}
    ${Core__ColorMap}
    ${Details}
    ${Glows}
    ${Interfase_implementations__ApplicationRender}
    ${Interfase_implementations__ConsoleRender}
    ${Interfase_implementations__Debug}
    ${Interfase_implementations__Debug__DebugRender}
    ${Interfase_implementations__EnvironmentRender}
    ${Interfase_implementations__FactoryPtr}
    ${Interfase_implementations__FontRender}
    ${Interfase_implementations__ImGuiRender}
    ${Interfase_implementations__LensFlare}
    ${Interfase_implementations__ObjectSpaceRender}
    ${Interfase_implementations__RainRender}
    ${Interfase_implementations__RenderDeviceRender}
    ${Interfase_implementations__RenderFactory}
    ${Interfase_implementations__StatGraphRender}
    ${Interfase_implementations__StatsRender}
    ${Interfase_implementations__ThunderboltDescRender}
    ${Interfase_implementations__ThunderboltRender}
    ${Interfase_implementations__UI__UIRender}
    ${Interfase_implementations__UI__UISequenceVideoItem}
    ${Interfase_implementations__UI__UIShader}
    ${Interfase_implementations__WallMarkArray}
    ${Kernel}
    ${Lights}
    ${Models}
    ${Models__Visuals}
    ${Refactored__Backend}
    ${Refactored__Execution__3D__DebugDraw}
    ${Refactored__Execution__3D__Gamma}
    ${Refactored__Execution__3D__Shaders__Blender}
    ${Refactored__Execution__3D__Shaders__Resources}
    ${Refactored__Execution__3D__Shaders__Resources__dx9_R_shader}
    ${Refactored__Execution__3D__Shaders__ShaderManager}
    ${Refactored__Execution__3D__Visuals}
    ${Refactored__Execution__3D__Visuals__Skeleton}
    ${Refactored__HW}
    ${Refactored__Interfaces}
    ${Refactored__stats_manager}
    ${Shading_templates}
    ${Stripifier}
    ${Visibility__HOM_Occlusion}
    ${Visibility__Sector/Portal}
    ${Wallmarks}
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

set(ROOT_NAMESPACE xrRender_R1)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd_party/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd_party/luajit-2/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd_party/luabind;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../xrCore;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include/OpenAutomate/inc;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include/nvapi"
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
            /O2;
            /Oi;
            /GF;
            /GT;
            /Oy;
            /Gy-;
            /Z7
        >
        $<$<CONFIG:Release>:
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
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Z7;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX11>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Z7;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Z7;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX8>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Z7;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:VerifiedDX9>:
            /Od;
            /Ob0;
            /Oi-;
            /Oy-;
            /Gy;
            /W4;
            /Z7;
            /GS;
            /Zc:inline-
        >
        /std:c++latest
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd_party/luajit-2/src/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/libraries/x64;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../x64/Release"
)

