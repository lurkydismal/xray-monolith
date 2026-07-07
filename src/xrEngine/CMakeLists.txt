set(PROJECT_NAME xrEngine)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "EngineThreading.cpp"
    "EngineThreading.h"
)
source_group("" FILES ${no_group_source_files})

set(Engine
    "Properties.h"
    "pure.cpp"
    "pure.h"
    "std_classes.h"
)
source_group("Engine" FILES ${Engine})

set(Engine__Collision_Core
    "cl_intersect.h"
)
source_group("Engine\\Collision Core" FILES ${Engine__Collision_Core})

set(Engine__Console
    "XR_IOConsole.cpp"
    "XR_IOConsole.h"
    "XR_IOConsole_callback.cpp"
    "XR_IOConsole_control.cpp"
    "XR_IOConsole_get.cpp"
)
source_group("Engine\\Console" FILES ${Engine__Console})

set(Engine__Console__commands
    "xr_ioc_cmd.cpp"
    "xr_ioc_cmd.h"
)
source_group("Engine\\Console\\commands" FILES ${Engine__Console__commands})

set(Engine__Core
    "Engine.cpp"
    "Engine.h"
    "EngineAPI.cpp"
    "EngineAPI.h"
    "EventAPI.cpp"
    "EventAPI.h"
    "mailSlot.cpp"
)
source_group("Engine\\Core" FILES ${Engine__Core})

set(Engine__Core__Scripting
    "_scripting.cpp"
    "ai_script_lua_debug.cpp"
    "ai_script_lua_extension.cpp"
    "ai_script_lua_extension.h"
    "ai_script_lua_space.h"
    "ai_script_space.h"
)
source_group("Engine\\Core\\Scripting" FILES ${Engine__Core__Scripting})

set(Engine__Noise
    "perlin.cpp"
    "perlin.h"
)
source_group("Engine\\Noise" FILES ${Engine__Noise})

set(Engine__text_editor__edit_actions
    "edit_actions.cpp"
    "edit_actions.h"
)
source_group("Engine\\text_editor\\edit_actions" FILES ${Engine__text_editor__edit_actions})

set(Engine__text_editor__line_editor
    "line_editor.cpp"
    "line_editor.h"
)
source_group("Engine\\text_editor\\line_editor" FILES ${Engine__text_editor__line_editor})

set(Engine__text_editor__line_editor_control
    "line_edit_control.cpp"
    "line_edit_control.h"
)
source_group("Engine\\text_editor\\line_editor_control" FILES ${Engine__text_editor__line_editor_control})

set(Game_API
    "IGame_Level.cpp"
    "IGame_Level.h"
    "IGame_Level_check_textures.cpp"
    "IGame_Persistent.cpp"
    "xrLevel.h"
)
source_group("Game API" FILES ${Game_API})

set(Game_API__Animator
    "bone.cpp"
    "bone.h"
    "Envelope.cpp"
    "envelope.h"
    "interp.cpp"
    "motion.cpp"
    "motion.h"
    "ObjectAnimator.cpp"
    "ObjectAnimator.h"
)
source_group("Game API\\Animator" FILES ${Game_API__Animator})

set(Game_API__Cameras
    "CameraBase.cpp"
    "CameraBase.h"
    "CameraDefs.h"
    "CameraManager.cpp"
    "CameraManager.h"
    "Effector.cpp"
    "Effector.h"
    "EffectorPP.cpp"
    "EffectorPP.h"
)
source_group("Game API\\Cameras" FILES ${Game_API__Cameras})

set(Game_API__Collision
    "cf_dynamic_mesh.cpp"
    "cf_dynamic_mesh.h"
    "xr_collide_form.cpp"
    "xr_collide_form.h"
)
source_group("Game API\\Collision" FILES ${Game_API__Collision})

set(Game_API__Debug
    "ObjectDump.cpp"
    "ObjectDump.h"
)
source_group("Game API\\Debug" FILES ${Game_API__Debug})

set(Game_API__Demo
    "FDemoPlay.cpp"
    "FDemoPlay.h"
    "FDemoRecord.cpp"
    "FDemoRecord.h"
)
source_group("Game API\\Demo" FILES ${Game_API__Demo})

set(Game_API__Environment
    "Environment.cpp"
    "Environment.h"
    "Environment_misc.cpp"
    "Environment_render.cpp"
    "xrHemisphere.cpp"
    "xrHemisphere.h"
)
source_group("Game API\\Environment" FILES ${Game_API__Environment})

set(Game_API__Environment__Effects
    "Rain.cpp"
    "Rain.h"
    "thunderbolt.cpp"
    "thunderbolt.h"
    "xr_efflensflare.cpp"
    "xr_efflensflare.h"
)
source_group("Game API\\Environment\\Effects" FILES ${Game_API__Environment__Effects})

set(Game_API__Feelers
    "Feel_Sound.h"
    "Feel_Touch.cpp"
    "Feel_Touch.h"
    "Feel_Vision.cpp"
    "Feel_Vision.h"
)
source_group("Game API\\Feelers" FILES ${Game_API__Feelers})

set(Game_API__GameMaterials
    "GameMtlLib.cpp"
    "GameMtlLib.h"
    "GameMtlLib_Engine.cpp"
)
source_group("Game API\\GameMaterials" FILES ${Game_API__GameMaterials})

set(Game_API__HUD
    "CustomHUD.cpp"
    "CustomHUD.h"
)
source_group("Game API\\HUD" FILES ${Game_API__HUD})

set(Game_API__Objects
    "IGame_ObjectPool.cpp"
    "IGame_ObjectPool.h"
    "IGame_Persistent.h"
    "pure_relcase.cpp"
    "pure_relcase.h"
    "ShadersExternalData.h"
    "xr_object.cpp"
    "xr_object.h"
    "xr_object_list.cpp"
    "xr_object_list.h"
)
source_group("Game API\\Objects" FILES ${Game_API__Objects})

set(General
    "_d3d_extensions.h"
    "dedicated_server_only.h"
    "defines.cpp"
    "defines.h"
    "mp_logging.h"
    "no_single.h"
    "stdafx.cpp"
    "stdafx.h"
    "trivial_encryptor.h"
    "x_ray.cpp"
    "x_ray.h"
)
source_group("General" FILES ${General})

set(General__Resources
    "resource.h"
)
source_group("General\\Resources" FILES ${General__Resources})

set(Interfaces
    "psystem.h"
)
source_group("Interfaces" FILES ${Interfaces})

set(Interfaces__Collidable
    "ICollidable.cpp"
    "ICollidable.h"
)
source_group("Interfaces\\Collidable" FILES ${Interfaces__Collidable})

set(Interfaces__Discord
    "../3rd party/discord/achievement_manager.cpp"
    "../3rd party/discord/achievement_manager.h"
    "../3rd party/discord/activity_manager.cpp"
    "../3rd party/discord/activity_manager.h"
    "../3rd party/discord/application_manager.cpp"
    "../3rd party/discord/application_manager.h"
    "../3rd party/discord/core.cpp"
    "../3rd party/discord/core.h"
    "../3rd party/discord/discord.h"
    "../3rd party/discord/event.h"
    "../3rd party/discord/ffi.h"
    "../3rd party/discord/image_manager.cpp"
    "../3rd party/discord/image_manager.h"
    "../3rd party/discord/lobby_manager.cpp"
    "../3rd party/discord/lobby_manager.h"
    "../3rd party/discord/network_manager.cpp"
    "../3rd party/discord/network_manager.h"
    "../3rd party/discord/overlay_manager.cpp"
    "../3rd party/discord/overlay_manager.h"
    "../3rd party/discord/relationship_manager.cpp"
    "../3rd party/discord/relationship_manager.h"
    "../3rd party/discord/storage_manager.cpp"
    "../3rd party/discord/storage_manager.h"
    "../3rd party/discord/store_manager.cpp"
    "../3rd party/discord/store_manager.h"
    "../3rd party/discord/types.cpp"
    "../3rd party/discord/types.h"
    "../3rd party/discord/user_manager.cpp"
    "../3rd party/discord/user_manager.h"
    "../3rd party/discord/voice_manager.cpp"
    "../3rd party/discord/voice_manager.h"
)
source_group("Interfaces\\Discord" FILES ${Interfaces__Discord})

set(Interfaces__ImGui
    "imgui_base.cpp"
    "imgui_base.h"
    "imgui_base_input.cpp"
    "imgui_helper.cpp"
    "imgui_helper.h"
)
source_group("Interfaces\\ImGui" FILES ${Interfaces__ImGui})

set(Interfaces__Input
    "IInputReceiver.cpp"
    "IInputReceiver.h"
    "Xr_input.cpp"
    "xr_input.h"
    "xr_input_xinput.cpp"
    "xr_input_xinput.h"
)
source_group("Interfaces\\Input" FILES ${Interfaces__Input})

set(Interfaces__Physics
    "IObjectPhysicsCollision.h"
    "IPHdebug.h"
    "IPhysicsGeometry.h"
    "IPhysicsShell.h"
    "phdebug.cpp"
)
source_group("Interfaces\\Physics" FILES ${Interfaces__Physics})

set(Interfaces__Render
    "IRenderable.cpp"
    "IRenderable.h"
    "Render.cpp"
    "Render.h"
)
source_group("Interfaces\\Render" FILES ${Interfaces__Render})

set(Interfaces__Sheduler
    "ISheduled.cpp"
    "ISheduled.h"
    "xrSheduler.cpp"
    "xrSheduler.h"
)
source_group("Interfaces\\Sheduler" FILES ${Interfaces__Sheduler})

set(OpenAutomate
    "xrSASH.cpp"
    "xrSASH.h"
)
source_group("OpenAutomate" FILES ${OpenAutomate})

set(RenderRef__Execution__3D__Device
    "device.cpp"
    "device.h"
    "Device_create.cpp"
    "Device_destroy.cpp"
    "Device_Initialize.cpp"
    "Device_Misc.cpp"
    "Device_overdraw.cpp"
    "Device_wndproc.cpp"
    "MonitorList.cpp"
    "MonitorList.h"
    "StatGraph.cpp"
    "StatGraph.h"
    "Stats.cpp"
    "Stats.h"
)
source_group("RenderRef\\Execution & 3D\\Device" FILES ${RenderRef__Execution__3D__Device})

set(RenderRef__Execution__3D__Visuals
    "fmesh.cpp"
    "Fmesh.h"
)
source_group("RenderRef\\Execution & 3D\\Visuals" FILES ${RenderRef__Execution__3D__Visuals})

set(RenderRef__Execution__3D__Visuals__Skeleton
    "SkeletonMotionDefs.h"
    "SkeletonMotions.cpp"
    "SkeletonMotions.h"
)
source_group("RenderRef\\Execution & 3D\\Visuals\\Skeleton" FILES ${RenderRef__Execution__3D__Visuals__Skeleton})

set(Render__Execution__3D__Shaders
    "Shader_xrLC.h"
    "WaveForm.h"
)
source_group("Render\\Execution & 3D\\Shaders" FILES ${Render__Execution__3D__Shaders})

set(Render__Execution__3D__Shaders__Textures
    "GIFResource.cpp"
    "GIFResource.h"
    "tntQAVI.cpp"
    "tntQAVI.h"
    "xrImage_Resampler.cpp"
    "xrImage_Resampler.h"
    "xrTheora_Stream.cpp"
    "xrTheora_Stream.h"
    "xrTheora_Surface.cpp"
    "xrTheora_Surface.h"
    "xrTheora_Surface_mmx.cpp"
    "xrTheora_Surface_mmx.h"
)
source_group("Render\\Execution & 3D\\Shaders\\Textures" FILES ${Render__Execution__3D__Shaders__Textures})

set(Render__Execution__3D__TextConsole
    "Text_Console.cpp"
    "Text_Console.h"
    "Text_Console_WndProc.cpp"
)
source_group("Render\\Execution & 3D\\TextConsole" FILES ${Render__Execution__3D__TextConsole})

set(Render__Font_output
    "GameFont.cpp"
    "GameFont.h"
    "MbHelpers.cpp"
    "MbHelpers.h"
)
source_group("Render\\Font output" FILES ${Render__Font_output})

set(Render__Lighting
    "LightAnimLibrary.cpp"
    "LightAnimLibrary.h"
)
source_group("Render\\Lighting" FILES ${Render__Lighting})

set(Render__Particle_system
    "PS_instance.cpp"
    "PS_instance.h"
)
source_group("Render\\Particle system" FILES ${Render__Particle_system})

set(Render__Visibility
    "vis_common.h"
)
source_group("Render\\Visibility" FILES ${Render__Visibility})

set(Render__Visuals__Skeleton
    "EnnumerateVertices.h"
)
source_group("Render\\Visuals\\Skeleton" FILES ${Render__Visuals__Skeleton})

set(ALL_FILES
    ${no_group_source_files}
    ${Engine}
    ${Engine__Collision_Core}
    ${Engine__Console}
    ${Engine__Console__commands}
    ${Engine__Core}
    ${Engine__Core__Scripting}
    ${Engine__Noise}
    ${Engine__text_editor__edit_actions}
    ${Engine__text_editor__line_editor}
    ${Engine__text_editor__line_editor_control}
    ${Game_API}
    ${Game_API__Animator}
    ${Game_API__Cameras}
    ${Game_API__Collision}
    ${Game_API__Debug}
    ${Game_API__Demo}
    ${Game_API__Environment}
    ${Game_API__Environment__Effects}
    ${Game_API__Feelers}
    ${Game_API__GameMaterials}
    ${Game_API__HUD}
    ${Game_API__Objects}
    ${General}
    ${General__Resources}
    ${Interfaces}
    ${Interfaces__Collidable}
    ${Interfaces__Discord}
    ${Interfaces__ImGui}
    ${Interfaces__Input}
    ${Interfaces__Physics}
    ${Interfaces__Render}
    ${Interfaces__Sheduler}
    ${OpenAutomate}
    ${RenderRef__Execution__3D__Device}
    ${RenderRef__Execution__3D__Visuals}
    ${RenderRef__Execution__3D__Visuals__Skeleton}
    ${Render__Execution__3D__Shaders}
    ${Render__Execution__3D__Shaders__Textures}
    ${Render__Execution__3D__TextConsole}
    ${Render__Font_output}
    ${Render__Lighting}
    ${Render__Particle_system}
    ${Render__Visibility}
    ${Render__Visuals__Skeleton}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} DX10             "../Common.cmake")
use_props(${PROJECT_NAME} DX10AVX          "../Common.cmake")
use_props(${PROJECT_NAME} DX11             "../Common.cmake")
use_props(${PROJECT_NAME} DX11AVX          "../Common.cmake")
use_props(${PROJECT_NAME} DX8              "../Common.cmake")
use_props(${PROJECT_NAME} DX8AVX           "../Common.cmake")
use_props(${PROJECT_NAME} DX9              "../Common.cmake")
use_props(${PROJECT_NAME} DX9AVX           "../Common.cmake")
use_props(${PROJECT_NAME} ProfiledDX11     "../Common.cmake")
use_props(${PROJECT_NAME} Release          "../Common.cmake")
use_props(${PROJECT_NAME} ReleaseAVX       "../Common.cmake")
use_props(${PROJECT_NAME} Verified         "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11     "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX11ASAN "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX8      "../Common.cmake")
use_props(${PROJECT_NAME} VerifiedDX9      "../Common.cmake")

set(ROOT_NAMESPACE xrEngine)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DX10             "AnomalyDX10"
    TARGET_NAME_DX10AVX          "AnomalyDX10AVX"
    TARGET_NAME_DX11             "AnomalyDX11"
    TARGET_NAME_DX11AVX          "AnomalyDX11AVX"
    TARGET_NAME_DX8              "AnomalyDX8"
    TARGET_NAME_DX8AVX           "AnomalyDX8AVX"
    TARGET_NAME_DX9              "AnomalyDX9"
    TARGET_NAME_DX9AVX           "AnomalyDX9AVX"
    TARGET_NAME_PROFILEDDX11     "AnomalyDX11"
    TARGET_NAME_RELEASE          "AnomalyDX9"
    TARGET_NAME_RELEASEAVX       "AnomalyDX9AVX"
    TARGET_NAME_VERIFIED         "VerifiedDX11"
    TARGET_NAME_VERIFIEDDX11     "VerifiedDX11"
    TARGET_NAME_VERIFIEDDX11ASAN "VerifiedDX11"
    TARGET_NAME_VERIFIEDDX8      "AnomalyDX8"
    TARGET_NAME_VERIFIEDDX9      "VerifiedDX9"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
    ARCHIVE_OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my"
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
    INTERPROCEDURAL_OPTIMIZATION_VERIFIEDDX8      "TRUE"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd party/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd party/luajit-2/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd party/luabind;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd party/giflib;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/OpenAutomate/inc;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/libogg-1.1.4/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/libtheora-1.1.1/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/OpenAutomate"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:DX10>:"
        "STATIC_RENDERER_R3;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DX10AVX>:"
        "STATIC_RENDERER_R3;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DX11>:"
        "STATIC_RENDERER_R4;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DX11AVX>:"
        "STATIC_RENDERER_R4;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DX8>:"
        "STATIC_RENDERER_R1;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DX8AVX>:"
        "STATIC_RENDERER_R1;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DX9>:"
        "STATIC_RENDERER_R2;"
        "_MBCS"
    ">"
    "$<$<CONFIG:DX9AVX>:"
        "STATIC_RENDERER_R2;"
        "_MBCS"
    ">"
    "$<$<CONFIG:ProfiledDX11>:"
        "XRCORE_PROFILER;"
        "STATIC_RENDERER_R4;"
        "_MBCS"
    ">"
    "$<$<CONFIG:Release>:"
        "STATIC_RENDERER_R2;"
        "_MBCS"
    ">"
    "$<$<CONFIG:ReleaseAVX>:"
        "STATIC_RENDERER_R2;"
        "_MBCS"
    ">"
    "$<$<CONFIG:Verified>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE;"
        "STATIC_RENDERER_R4"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE;"
        "STATIC_RENDERER_R4"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE;"
        "STATIC_RENDERER_R4;"
        "_DISABLE_VECTOR_ANNOTATION;"
        "_DISABLE_STRING_ANNOTATION"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE;"
        "STATIC_RENDERER_R1;"
        "_MBCS"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "XRCORE_PROFILER;"
        "USE_VERIFY_IN_RELEASE;"
        "STATIC_RENDERER_R2"
    ">"
    "NDEBUG;"
    "WIN32;"
    "_WINDOWS;"
    "ENGINE_BUILD;"
    "_SECURE_SCL=0;"
    "AL_LIBTYPE_STATIC"
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
        $<$<CONFIG:DX10>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:DX10AVX>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:DX11>:
            /OPT:REF;
            /LTCG:STATUS;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:DX11AVX>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:DX8>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:DX8AVX>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:DX9>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:DX9AVX>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:ProfiledDX11>:
            /OPT:NOREF;
            /OPT:NOICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:ReleaseAVX>:
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:Verified>:
            /FIXED:NO;
            /OPT:NOREF;
            /OPT:NOICF;
            /INCREMENTAL
        >
        $<$<CONFIG:VerifiedDX11>:
            /FIXED:NO;
            /OPT:NOREF;
            /OPT:NOICF;
            /INCREMENTAL
        >
        $<$<CONFIG:VerifiedDX11ASAN>:
            /FIXED:NO;
            /OPT:NOREF;
            /OPT:NOICF;
            /INCREMENTAL
        >
        $<$<CONFIG:VerifiedDX8>:
            /FIXED:NO;
            /OPT:NOREF;
            /OPT:NOICF;
            /INCREMENTAL
        >
        $<$<CONFIG:VerifiedDX9>:
            /FIXED:NO;
            /OPT:NOREF;
            /OPT:NOICF;
            /INCREMENTAL
        >
        /DEBUG;
        /ignore:4099
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    LuaJIT-2
    ReShadeCompat
    giflib
    imgui
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    luabind
    xrAPI
    xrNetServer
    xrSound
    NVTT
    libjpeg
    libogg_static
    libtheora_static
    libvorbisfile_static
    libvorbis_static
    crypto
    CxImage
    DXERR
    lua_extensions
    ode
    xrCDB
    xrCore
    xrCPU_Pipe
    #xrGame
    xrParticles
    xrPhysics
    xrXMLParser
    OpenAL32
    optick
)

if(CMAKE_BUILD_TYPE MATCHES "^(DX8|DX8AVX|VerifiedDX8)$")
    target_include_directories(${PROJECT_NAME} PRIVATE xrRenderPC_R1)
endif()

if(CMAKE_BUILD_TYPE MATCHES "^(DX9|DX9AVX|VerifiedDX9)$")
    target_include_directories(${PROJECT_NAME} PRIVATE xrRenderPC_R2)
endif()

if(CMAKE_BUILD_TYPE MATCHES "^(DX10|DX10AVX|VerifiedDX10)$")
    target_include_directories(${PROJECT_NAME} PRIVATE xrRenderPC_R3)
endif()

if(CMAKE_BUILD_TYPE MATCHES "^(DX11|DX11AVX|VerifiedDX11)$")
    target_include_directories(${PROJECT_NAME} PRIVATE xrRenderPC_R4)
endif()


set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "vfw32;"
    "libogg_static;"
    "libtheora_static;"
    "winmm;"
    "OpenAL32;"
    "giflib"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:DX10>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:DX10AVX>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release-AVX/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:DX11>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "$<$<CONFIG:DX11AVX>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release-AVX/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "$<$<CONFIG:DX8>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:DX8AVX>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release-AVX/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:DX9>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:DX9AVX>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release-AVX/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:ProfiledDX11>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "$<$<CONFIG:Release>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:ReleaseAVX>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Release-AVX/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64.old"
    ">"
    "$<$<CONFIG:Verified>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Verified/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "$<$<CONFIG:VerifiedDX11>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Verified/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "$<$<CONFIG:VerifiedDX11ASAN>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/VerifiedDX11ASAN/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/VerifiedDX11ASAN;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/VerifiedDX11ASAN;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "$<$<CONFIG:VerifiedDX8>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Verified/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "$<$<CONFIG:VerifiedDX9>:"
        "${OUTPUT_DIRECTORY}${CMAKE_VS_PLATFORM_NAME}/Verified/;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/Verified;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries/x64"
    ">"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd party/luajit-2/src/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/OpenAutomate/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my/"
)

