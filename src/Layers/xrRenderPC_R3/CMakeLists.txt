set(PROJECT_NAME xrRender_R3)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../xrRender/r__dsgraph_manager.cpp"
    "../xrRender/r__dsgraph_manager.h"
)
source_group("" FILES ${no_group_source_files})

set(3DFluid
    "../xrRenderDX10/3DFluid/dx103DFluidData.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidData.h"
    "../xrRenderDX10/3DFluid/dx103DFluidEmitters.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidEmitters.h"
    "../xrRenderDX10/3DFluid/dx103DFluidGrid.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidGrid.h"
    "../xrRenderDX10/3DFluid/dx103DFluidManager.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidManager.h"
    "../xrRenderDX10/3DFluid/dx103DFluidObstacles.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidObstacles.h"
    "../xrRenderDX10/3DFluid/dx103DFluidRenderer.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidRenderer.h"
)
source_group("3DFluid" FILES ${3DFluid})

set(Core
    "../../Include/xrRender/particles_systems_library_interface.hpp"
    "../xrRender/CHudInitializer.cpp"
    "../xrRender/CHudInitializer.h"
    "../xrRender/gifPlayer.cpp"
    "../xrRender/gifPlayer.h"
    "../xrRender/lights_render.cpp"
    "../xrRender/PSLibrary.cpp"
    "../xrRender/PSLibrary.h"
    "../xrRender/QueryHelper.h"
    "../xrRender/r2_blenders.cpp"
    "../xrRender/r__dsgraph_build.cpp"
    "../xrRender/r__dsgraph_render.cpp"
    "../xrRender/r__dsgraph_render_lods.cpp"
    "../xrRender/r__dsgraph_types.h"
    "../xrRender/r__occlusion.cpp"
    "../xrRender/r__occlusion.h"
    "../xrRender/r__pixel_calculator.cpp"
    "../xrRender/r__pixel_calculator.h"
    "../xrRender/r__screenshot.cpp"
    "../xrRender/R_calculate.cpp"
    "../xrRender/R_sun.cpp"
    "../xrRender/r_sun_cascades.h"
    "../xrRender/R_sun_support.cpp"
    "../xrRender/R_sun_support.h"
    "../xrRender/tga.cpp"
    "../xrRender/tga.h"
    "../xrRenderDX10/dx10Texture.cpp"
    "r2_test_hw.cpp"
    "r2_types.h"
    "r3.cpp"
    "r3.h"
    "r3_loader.cpp"
    "r3_R_rain.cpp"
    "r3_R_render.cpp"
)
source_group("Core" FILES ${Core})

set(Core_Target
    "../xrRender/rendertarget_phase_blur.cpp"
    "../xrRender/rendertarget_phase_dof.cpp"
    "../xrRender/rendertarget_phase_gasmask_drops.cpp"
    "../xrRender/rendertarget_phase_gasmask_dudv.cpp"
    "../xrRender/rendertarget_phase_lut.cpp"
    "../xrRender/rendertarget_phase_nightvision.cpp"
    "../xrRender/rendertarget_phase_pp_bloom.cpp"
    "../xrRender/rendertarget_phase_smaa.cpp"
    "../xrRender/rendertarget_phase_sunshafts.cpp"
    "r3_rendertarget.cpp"
    "r3_rendertarget.h"
    "r3_rendertarget_accum_direct.cpp"
    "r3_rendertarget_accum_omnipart_geom.cpp"
    "r3_rendertarget_accum_point.cpp"
    "r3_rendertarget_accum_point_geom.cpp"
    "r3_rendertarget_accum_reflected.cpp"
    "r3_rendertarget_accum_spot.cpp"
    "r3_rendertarget_accum_spot_geom.cpp"
    "r3_rendertarget_create_minmaxSM.cpp"
    "r3_rendertarget_draw_rain.cpp"
    "r3_rendertarget_draw_volume.cpp"
    "r3_rendertarget_enable_scissor.cpp"
    "r3_rendertarget_mark_msaa_edges.cpp"
    "r3_rendertarget_phase_accumulator.cpp"
    "r3_rendertarget_phase_bloom.cpp"
    "r3_rendertarget_phase_combine.cpp"
    "r3_rendertarget_phase_luminance.cpp"
    "r3_rendertarget_phase_occq.cpp"
    "r3_rendertarget_phase_PP.cpp"
    "r3_rendertarget_phase_rain.cpp"
    "r3_rendertarget_phase_scene.cpp"
    "r3_rendertarget_phase_smap_D.cpp"
    "r3_rendertarget_phase_smap_S.cpp"
    "r3_rendertarget_phase_ssao.cpp"
    "r3_rendertarget_wallmarks.h"
)
source_group("Core_Target" FILES ${Core_Target})

set(Core_Target__ColorMap
    "../xrRender/ColorMapManager.cpp"
    "../xrRender/ColorMapManager.h"
)
source_group("Core_Target\\ColorMap" FILES ${Core_Target__ColorMap})

set(Debug
    "../xrRender/Debug/dxPixEventWrapper.cpp"
    "../xrRender/Debug/dxPixEventWrapper.h"
)
source_group("Debug" FILES ${Debug})

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
    "../xrRenderDX10/dx10DetailManager_VS.cpp"
)
source_group("Details" FILES ${Details})

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

set(Interfase_implementations__MSAARender
    "../xrRenderDX10/MSAA/dx10MSAABlender.cpp"
    "../xrRenderDX10/MSAA/dx10MSAABlender.h"
)
source_group("Interfase implementations\\MSAARender" FILES ${Interfase_implementations__MSAARender})

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
    "../../xrEngine/cl_intersect.h"
    "../xrRender/xrD3DDefs.h"
    "../xrRender/xrRender_console.cpp"
    "../xrRender/xrRender_console.h"
    "stdafx.cpp"
    "stdafx.h"
    "xrRender_R3.cpp"
)
source_group("Kernel" FILES ${Kernel})

set(Lights
    "../xrRender/light.cpp"
    "../xrRender/light.h"
    "../xrRender/Light_DB.cpp"
    "../xrRender/Light_DB.h"
    "../xrRender/Light_Package.cpp"
    "../xrRender/Light_Package.h"
    "../xrRender/light_vis.cpp"
    "../xrRender/LightTrack.cpp"
    "../xrRender/LightTrack.h"
    "light_GI.cpp"
    "light_gi.h"
    "SMAP_Allocator.h"
)
source_group("Lights" FILES ${Lights})

set(Models
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
    "../xrRenderDX10/3DFluid/dx103DFluidVolume.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidVolume.h"
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
    "../xrRenderDX10/dx10R_Backend_Runtime.h"
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
    "../xrRenderDX10/Blender_Recorder_R3.cpp"
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
    "../xrRender/SH_RT.h"
    "../xrRender/SH_Texture.h"
    "../xrRender/Shader.cpp"
    "../xrRender/Shader.h"
    "../xrRenderDX10/dx10ConstantBuffer.cpp"
    "../xrRenderDX10/dx10ConstantBuffer.h"
    "../xrRenderDX10/dx10ConstantBuffer_impl.h"
    "../xrRenderDX10/dx10r_constants.cpp"
    "../xrRenderDX10/dx10SH_RT.cpp"
    "../xrRenderDX10/dx10SH_Texture.cpp"
)
source_group("Refactored\\Execution & 3D\\Shaders\\Resources" FILES ${Refactored__Execution__3D__Shaders__Resources})

set(Refactored__Execution__3D__Shaders__Resources__dx10_R_shader
    "../xrRender/r_constants_cache.h"
    "../xrRenderDX10/dx10r_constants_cache.cpp"
    "../xrRenderDX10/dx10r_constants_cache.h"
)
source_group("Refactored\\Execution & 3D\\Shaders\\Resources\\dx10_R_shader" FILES ${Refactored__Execution__3D__Shaders__Resources__dx10_R_shader})

set(Refactored__Execution__3D__Shaders__ShaderManager
    "../../xrEngine/ai_script_lua_debug.cpp"
    "../../xrEngine/ai_script_lua_extension.cpp"
    "../xrRender/ETextureParams.cpp"
    "../xrRender/ETextureParams.h"
    "../xrRender/ResourceManager.cpp"
    "../xrRender/ResourceManager.h"
    "../xrRender/ResourceManager_Loader.cpp"
    "../xrRender/ResourceManager_Reset.cpp"
    "../xrRender/TextureDescrManager.cpp"
    "../xrRender/TextureDescrManager.h"
    "../xrRenderDX10/dx10ResourceManager_Resources.cpp"
    "../xrRenderDX10/dx10ResourceManager_Scripting.cpp"
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
    "../../Include/xrRender/Kinematics.h"
    "../../Include/xrRender/KinematicsAnimated.h"
    "../xrRender/Animation.cpp"
    "../xrRender/Animation.h"
    "../xrRender/SkeletonAnimated.cpp"
    "../xrRender/SkeletonAnimated.h"
    "../xrRender/SkeletonCustom.cpp"
    "../xrRender/SkeletonCustom.h"
    "../xrRender/SkeletonRigid.cpp"
    "../xrRender/SkeletonX.cpp"
    "../xrRender/SkeletonX.h"
)
source_group("Refactored\\Execution & 3D\\Visuals\\Skeleton" FILES ${Refactored__Execution__3D__Visuals__Skeleton})

set(Refactored__HW
    "../xrRender/HW.h"
    "../xrRender/HWCaps.cpp"
    "../xrRender/HWCaps.h"
    "../xrRenderDX10/dx10HW.cpp"
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
    "../xrRender/Blender_Editor_Selection.cpp"
    "../xrRender/Blender_Editor_Selection.h"
    "../xrRender/Blender_Editor_Wire.cpp"
    "../xrRender/Blender_Editor_Wire.h"
    "../xrRender/Blender_Particle.cpp"
    "../xrRender/Blender_Particle.h"
    "../xrRender/uber_deffer.cpp"
    "../xrRender/uber_deffer.h"
    "blender_bloom_build.cpp"
    "blender_bloom_build.h"
    "blender_blur.cpp"
    "blender_blur.h"
    "blender_combine.cpp"
    "blender_combine.h"
    "blender_deffer_aref.cpp"
    "blender_deffer_aref.h"
    "blender_deffer_flat.cpp"
    "blender_deffer_flat.h"
    "blender_deffer_model.cpp"
    "blender_deffer_model.h"
    "blender_dof.cpp"
    "blender_dof.h"
    "blender_gasmask_drops.cpp"
    "blender_gasmask_drops.h"
    "blender_gasmask_dudv.cpp"
    "blender_gasmask_dudv.h"
    "blender_light_direct.cpp"
    "blender_light_direct.h"
    "blender_light_mask.cpp"
    "blender_light_mask.h"
    "blender_light_occq.cpp"
    "blender_light_occq.h"
    "blender_light_point.cpp"
    "blender_light_point.h"
    "blender_light_reflected.cpp"
    "blender_light_reflected.h"
    "blender_light_spot.cpp"
    "blender_light_spot.h"
    "blender_luminance.cpp"
    "blender_luminance.h"
    "blender_lut.cpp"
    "blender_lut.h"
    "blender_nightvision.cpp"
    "blender_nightvision.h"
    "blender_pp_bloom.cpp"
    "blender_pp_bloom.h"
    "blender_smaa.cpp"
    "blender_smaa.h"
    "blender_ss_sunshafts.cpp"
    "blender_ss_sunshafts.h"
    "blender_ssao.cpp"
    "blender_ssao.h"
    "dx10MinMaxSMBlender.cpp"
    "dx10MinMaxSMBlender.h"
)
source_group("Shading templates" FILES ${Shading_templates})

set(Shading_templates__3dFluid
    "../xrRenderDX10/3DFluid/dx103DFluidBlenders.cpp"
    "../xrRenderDX10/3DFluid/dx103DFluidBlenders.h"
)
source_group("Shading templates\\3dFluid" FILES ${Shading_templates__3dFluid})

set(Shading_templates__DX10_Rain
    "../xrRenderDX10/DX10 Rain/dx10RainBlender.cpp"
    "../xrRenderDX10/DX10 Rain/dx10RainBlender.h"
)
source_group("Shading templates\\DX10 Rain" FILES ${Shading_templates__DX10_Rain})

set(Shading_templates__R1
    "../xrRender/Blender_detail_still.cpp"
    "../xrRender/Blender_detail_still.h"
    "../xrRender/Blender_Lm(EbB).cpp"
    "../xrRender/Blender_Lm(EbB).h"
    "../xrRender/Blender_Model_EbB.cpp"
    "../xrRender/Blender_Model_EbB.h"
    "../xrRender/Blender_Screen_SET.cpp"
    "../xrRender/Blender_Screen_SET.h"
    "../xrRender/Blender_tree.cpp"
    "../xrRender/Blender_tree.h"
)
source_group("Shading templates\\R1" FILES ${Shading_templates__R1})

set(StateManager
    "../xrRenderDX10/StateManager/dx10SamplerStateCache.cpp"
    "../xrRenderDX10/StateManager/dx10SamplerStateCache.h"
    "../xrRenderDX10/StateManager/dx10ShaderResourceStateCache.cpp"
    "../xrRenderDX10/StateManager/dx10ShaderResourceStateCache.h"
    "../xrRenderDX10/StateManager/dx10State.cpp"
    "../xrRenderDX10/StateManager/dx10State.h"
    "../xrRenderDX10/StateManager/dx10StateCache.cpp"
    "../xrRenderDX10/StateManager/dx10StateCache.h"
    "../xrRenderDX10/StateManager/dx10StateCacheImpl.h"
    "../xrRenderDX10/StateManager/dx10StateManager.cpp"
    "../xrRenderDX10/StateManager/dx10StateManager.h"
)
source_group("StateManager" FILES ${StateManager})

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

set(Utils
    "../xrRender/Utils/dxHashHelper.cpp"
    "../xrRender/Utils/dxHashHelper.h"
)
source_group("Utils" FILES ${Utils})

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

set(dx9_to_dx10_Utils
    "../xrRenderDX10/dx10BufferUtils.cpp"
    "../xrRenderDX10/dx10BufferUtils.h"
    "../xrRenderDX10/dx10StateUtils.cpp"
    "../xrRenderDX10/dx10StateUtils.h"
    "../xrRenderDX10/dx10TextureUtils.cpp"
    "../xrRenderDX10/dx10TextureUtils.h"
)
source_group("dx9 to dx10 Utils" FILES ${dx9_to_dx10_Utils})

set(ALL_FILES
    ${no_group_source_files}
    ${3DFluid}
    ${Core}
    ${Core_Target}
    ${Core_Target__ColorMap}
    ${Debug}
    ${Details}
    ${Interfase_implementations__ApplicationRender}
    ${Interfase_implementations__ConsoleRender}
    ${Interfase_implementations__Debug}
    ${Interfase_implementations__Debug__DebugRender}
    ${Interfase_implementations__EnvironmentRender}
    ${Interfase_implementations__FactoryPtr}
    ${Interfase_implementations__FontRender}
    ${Interfase_implementations__ImGuiRender}
    ${Interfase_implementations__LensFlare}
    ${Interfase_implementations__MSAARender}
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
    ${Refactored__Execution__3D__Shaders__Resources__dx10_R_shader}
    ${Refactored__Execution__3D__Shaders__ShaderManager}
    ${Refactored__Execution__3D__Visuals}
    ${Refactored__Execution__3D__Visuals__Skeleton}
    ${Refactored__HW}
    ${Refactored__Interfaces}
    ${Refactored__stats_manager}
    ${Shading_templates}
    ${Shading_templates__3dFluid}
    ${Shading_templates__DX10_Rain}
    ${Shading_templates__R1}
    ${StateManager}
    ${Stripifier}
    ${Utils}
    ${Visibility__HOM_Occlusion}
    ${Visibility__Sector/Portal}
    ${Wallmarks}
    ${dx9_to_dx10_Utils}
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

set(ROOT_NAMESPACE xrRender_R3)

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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd party/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd party/luajit-2/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd party/luabind;"
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
    "USE_DX10;"
    "WIN32;"
    "NDEBUG;"
    "_WINDOWS;"
    "_USRDLL;"
    "XRRENDER_R3_EXPORTS;"
    "_SECURE_SCL=0;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MY_MSVC)
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
        /std:c++17;
        /wd4005;
        /wd4099;
        -Zm110
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
    "dxguid;"
    "d3dcompiler;"
    "d3d10;"
    "d3dx10;"
    "dxgi;"
    "nvapi"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd party/luajit-2/src/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/libraries/x64;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/lib/my/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include/OpenAutomate/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../x64/Release"
)

