set(PROJECT_NAME xrPhysics)

################################################################################
# Source groups
################################################################################
set(kernel
    "stdafx.cpp"
    "stdafx.h"
    "xrPhysics.cpp"
    "xrPhysics.h"
)
source_group("kernel" FILES ${kernel})

set(physics
    "console_vars.cpp"
    "console_vars.h"
    "ShellHit.cpp"
)
source_group("physics" FILES ${physics})

set(physics__ActivationBox
    "IActivationShape.cpp"
    "IActivationShape.h"
    "PHActivationShape.cpp"
    "PHActivationShape.h"
    "SpaceUtils.h"
)
source_group("physics\\ActivationBox" FILES ${physics__ActivationBox})

set(physics__Base
    "DamageSource.h"
    "ode_include.h"
    "ode_redefine.h"
    "PhysicsCommon.h"
    "PhysicsExternalCommon.cpp"
    "PhysicsExternalCommon.h"
)
source_group("physics\\Base" FILES ${physics__Base})

set(physics__Base__Debug
    "debug_output.cpp"
    "debug_output.h"
)
source_group("physics\\Base\\Debug" FILES ${physics__Base__Debug})

set(physics__Base__Impact
    "PHImpact.h"
)
source_group("physics\\Base\\Impact" FILES ${physics__Base__Impact})

set(physics__Base__Objects
    "PHDefs.h"
)
source_group("physics\\Base\\Objects" FILES ${physics__Base__Objects})

set(physics__Base__Objects__BaseShell
    "IPhysicsShellHolder.h"
    "PhysicsShell.cpp"
    "PhysicsShell.h"
)
source_group("physics\\Base\\Objects\\BaseShell" FILES ${physics__Base__Objects__BaseShell})

set(physics__Base__Objects__BaseShell__PhysicsShellAnimator
    "PhysicsShellAnimator.cpp"
    "PhysicsShellAnimator.h"
    "PhysicsShellAnimatorBoneData.h"
)
source_group("physics\\Base\\Objects\\BaseShell\\PhysicsShellAnimator" FILES ${physics__Base__Objects__BaseShell__PhysicsShellAnimator})

set(physics__Base__Objects__BodyEffectors
    "PHBaseBodyEffector.h"
    "PHContactBodyEffector.cpp"
    "PHContactBodyEffector.h"
)
source_group("physics\\Base\\Objects\\BodyEffectors" FILES ${physics__Base__Objects__BodyEffectors})

set(physics__Base__Objects__Breakable
    "PHFracture.cpp"
    "PHFracture.h"
    "PHJointDestroyInfo.cpp"
    "PHJointDestroyInfo.h"
    "PHShellSplitter.cpp"
    "PHShellSplitter.h"
)
source_group("physics\\Base\\Objects\\Breakable" FILES ${physics__Base__Objects__Breakable})

set(physics__Base__Objects__CollideValidator
    "ICollideValidator.h"
    "PHCollideValidator.cpp"
    "PHCollideValidator.h"
)
source_group("physics\\Base\\Objects\\CollideValidator" FILES ${physics__Base__Objects__CollideValidator})

set(physics__Base__Objects__Disabling
    "DisablingParams.cpp"
    "DisablingParams.h"
    "PHDisabling.cpp"
    "PHDisabling.h"
)
source_group("physics\\Base\\Objects\\Disabling" FILES ${physics__Base__Objects__Disabling})

set(physics__Base__Objects__Element
    "PHElement.cpp"
    "PHElement.h"
    "PHElementInline.h"
    "PHElementNetState.cpp"
)
source_group("physics\\Base\\Objects\\Element" FILES ${physics__Base__Objects__Element})

set(physics__Base__Objects__Element__Geom
    "ExtendedGeom.cpp"
    "ExtendedGeom.h"
    "Geometry.cpp"
    "Geometry.h"
    "PHGeometryOwner.cpp"
    "PHGeometryOwner.h"
)
source_group("physics\\Base\\Objects\\Element\\Geom" FILES ${physics__Base__Objects__Element__Geom})

set(physics__Base__Objects__Joint
    "PHJoint.cpp"
    "PHJoint.h"
)
source_group("physics\\Base\\Objects\\Joint" FILES ${physics__Base__Objects__Joint})

set(physics__Base__Objects__MoveStorage
    "PHMoveStorage.cpp"
    "PHMoveStorage.h"
)
source_group("physics\\Base\\Objects\\MoveStorage" FILES ${physics__Base__Objects__MoveStorage})

set(physics__Base__Objects__PHIsland
    "PHIsland.cpp"
    "PHIsland.h"
)
source_group("physics\\Base\\Objects\\PHIsland" FILES ${physics__Base__Objects__PHIsland})

set(physics__Base__Objects__PHNet
    "../xrServerEntities/PHNetState.cpp"
    "../xrServerEntities/PHNetState.h"
)
source_group("physics\\Base\\Objects\\PHNet" FILES ${physics__Base__Objects__PHNet})

set(physics__Base__Objects__PHObject
    "PHObject.cpp"
    "PHObject.h"
    "PHUpdateObject.h"
)
source_group("physics\\Base\\Objects\\PHObject" FILES ${physics__Base__Objects__PHObject})

set(physics__Base__Objects__PhyMove__AICharacter
    "PHAICharacter.cpp"
    "PHAICharacter.h"
)
source_group("physics\\Base\\Objects\\PhyMove\\AICharacter" FILES ${physics__Base__Objects__PhyMove__AICharacter})

set(physics__Base__Objects__PhyMove__ActorCaracter
    "PHActorCharacter.cpp"
    "PHActorCharacter.h"
    "PHActorCharacterInline.h"
)
source_group("physics\\Base\\Objects\\PhyMove\\ActorCaracter" FILES ${physics__Base__Objects__PhyMove__ActorCaracter})

set(physics__Base__Objects__PhyMove__BaseCharacter
    "IColisiondamageInfo.h"
    "MovementBoxDynamicActivate.cpp"
    "MovementBoxDynamicActivate.h"
    "PHCharacter.cpp"
    "PHCharacter.h"
)
source_group("physics\\Base\\Objects\\PhyMove\\BaseCharacter" FILES ${physics__Base__Objects__PhyMove__BaseCharacter})

set(physics__Base__Objects__PhyMove__Capture
    "IPHCapture.h"
    "PHCapture.cpp"
    "PHCapture.h"
    "PHCaptureInit.cpp"
)
source_group("physics\\Base\\Objects\\PhyMove\\Capture" FILES ${physics__Base__Objects__PhyMove__Capture})

set(physics__Base__Objects__PhyMove__SipmpleCharacter
    "ElevatorState.cpp"
    "ElevatorState.h"
    "iclimableobject.h"
    "IElevatorState.h"
    "PHSimpleCharacter.cpp"
    "PHSimpleCharacter.h"
    "PHSimpleCharacterInline.h"
)
source_group("physics\\Base\\Objects\\PhyMove\\SipmpleCharacter" FILES ${physics__Base__Objects__PhyMove__SipmpleCharacter})

set(physics__Base__Objects__Shell
    "PHShell.cpp"
    "PHShell.h"
    "PHShellActivate.cpp"
    "PHShellBuildJoint.h"
    "PHShellNetState.cpp"
)
source_group("physics\\Base\\Objects\\Shell" FILES ${physics__Base__Objects__Shell})

set(physics__Base__Objects__SplitedShell
    "PHSplitedShell.cpp"
    "PHSplitedShell.h"
)
source_group("physics\\Base\\Objects\\SplitedShell" FILES ${physics__Base__Objects__SplitedShell})

set(physics__Base__Objects__StaticShell
    "IPHStaticGeomShell.h"
    "PHStaticGeomShell.cpp"
    "PHStaticGeomShell.h"
)
source_group("physics\\Base\\Objects\\StaticShell" FILES ${physics__Base__Objects__StaticShell})

set(physics__Base__Objects__Utils
    "ph_valid_ode.h"
    "phvalide.cpp"
    "phvalide.h"
    "PHValideValues.h"
)
source_group("physics\\Base\\Objects\\Utils" FILES ${physics__Base__Objects__Utils})

set(physics__Base__Objects__Utils__Interpolation
    "PHInterpolation.cpp"
    "PHInterpolation.h"
)
source_group("physics\\Base\\Objects\\Utils\\Interpolation" FILES ${physics__Base__Objects__Utils__Interpolation})

set(physics__Base__Objects__Utils__Math
    "CalculateTriangle.h"
    "MathUtils.cpp"
    "MathUtils.h"
    "MathUtilsOde.h"
    "matrix_utils.h"
    "PHDynamicData.cpp"
    "PHDynamicData.h"
)
source_group("physics\\Base\\Objects\\Utils\\Math" FILES ${physics__Base__Objects__Utils__Math})

set(physics__Base__Objects__Utils__Storage
    "BlockAllocator.h"
    "CycleConstStorage.h"
)
source_group("physics\\Base\\Objects\\Utils\\Storage" FILES ${physics__Base__Objects__Utils__Storage})

set(physics__Base__Objects__World
    "GeometryBits.cpp"
    "GeometryBits.h"
    "IPHWorld.h"
    "params.cpp"
    "params.h"
    "PHItemList.h"
    "PHWorld.cpp"
    "PHWorld.h"
    "Physics.cpp"
    "Physics.h"
)
source_group("physics\\Base\\Objects\\World" FILES ${physics__Base__Objects__World})

set(physics__Base__Objects__script
    "iphysics_scripted.h"
    "physics_scripted.cpp"
    "physics_scripted.h"
)
source_group("physics\\Base\\Objects\\script" FILES ${physics__Base__Objects__script})

set(physics__camera_collision
    "ActorCameraCollision.cpp"
    "ActorCameraCollision.h"
)
source_group("physics\\camera_collision" FILES ${physics__camera_collision})

set(physics__colliders__RayMotions
    "dRayMotions.cpp"
    "dRayMotions.h"
)
source_group("physics\\colliders\\RayMotions" FILES ${physics__colliders__RayMotions})

set(physics__colliders__cyl
    "dcylinder/dCylinder.cpp"
    "dcylinder/dCylinder.h"
)
source_group("physics\\colliders\\cyl" FILES ${physics__colliders__cyl})

set(physics__colliders__tri
    "tri-colliderknoopc/__aabb_tri.h"
    "tri-colliderknoopc/dcTriangle.h"
    "tri-colliderknoopc/dcTriListCollider.h"
    "tri-colliderknoopc/dSortTriPrimitive.cpp"
    "tri-colliderknoopc/dSortTriPrimitive.h"
    "tri-colliderknoopc/dTriBox.cpp"
    "tri-colliderknoopc/dTriBox.h"
    "tri-colliderknoopc/dTriCallideK.cpp"
    "tri-colliderknoopc/dTriCollideK.h"
    "tri-colliderknoopc/dTriColliderCommon.h"
    "tri-colliderknoopc/dTriColliderMath.h"
    "tri-colliderknoopc/dTriCylinder.cpp"
    "tri-colliderknoopc/dTriCylinder.h"
    "tri-colliderknoopc/dTriList.cpp"
    "tri-colliderknoopc/dTriList.h"
    "tri-colliderknoopc/dTriSphere.cpp"
    "tri-colliderknoopc/dTriSphere.h"
    "tri-colliderknoopc/dxTriList.h"
    "tri-colliderknoopc/TriPrimitiveCollideClassDef.h"
)
if(ENABLE_DEBUG_OLD_RUNTIME)
    list(APPEND physics__colliders__tri tri-colliderknoopc/dcTriListCollider.cpp)
endif()
source_group("physics\\colliders\\tri" FILES ${physics__colliders__tri})

set(physics__damage_receiver
    "collisiondamagereceiver.cpp"
    "icollisiondamagereceiver.h"
)
source_group("physics\\damage_receiver" FILES ${physics__damage_receiver})

set(ALL_FILES
    ${kernel}
    ${physics}
    ${physics__ActivationBox}
    ${physics__Base}
    ${physics__Base__Debug}
    ${physics__Base__Impact}
    ${physics__Base__Objects}
    ${physics__Base__Objects__BaseShell}
    ${physics__Base__Objects__BaseShell__PhysicsShellAnimator}
    ${physics__Base__Objects__BodyEffectors}
    ${physics__Base__Objects__Breakable}
    ${physics__Base__Objects__CollideValidator}
    ${physics__Base__Objects__Disabling}
    ${physics__Base__Objects__Element}
    ${physics__Base__Objects__Element__Geom}
    ${physics__Base__Objects__Joint}
    ${physics__Base__Objects__MoveStorage}
    ${physics__Base__Objects__PHIsland}
    ${physics__Base__Objects__PHNet}
    ${physics__Base__Objects__PHObject}
    ${physics__Base__Objects__PhyMove__AICharacter}
    ${physics__Base__Objects__PhyMove__ActorCaracter}
    ${physics__Base__Objects__PhyMove__BaseCharacter}
    ${physics__Base__Objects__PhyMove__Capture}
    ${physics__Base__Objects__PhyMove__SipmpleCharacter}
    ${physics__Base__Objects__Shell}
    ${physics__Base__Objects__SplitedShell}
    ${physics__Base__Objects__StaticShell}
    ${physics__Base__Objects__Utils}
    ${physics__Base__Objects__Utils__Interpolation}
    ${physics__Base__Objects__Utils__Math}
    ${physics__Base__Objects__Utils__Storage}
    ${physics__Base__Objects__World}
    ${physics__Base__Objects__script}
    ${physics__camera_collision}
    ${physics__colliders__RayMotions}
    ${physics__colliders__cyl}
    ${physics__colliders__tri}
    ${physics__damage_receiver}
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

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DX10             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX10AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11             "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX11AVX          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX8AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9              "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_DX9AVX           "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_PROFILEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE          "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASEAVX       "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIED         "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11     "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX11ASAN "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX8      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    OUTPUT_DIRECTORY_VERIFIEDDX9      "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
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
    $<$<CONFIG:ProfiledDX11>:
        MultiThreadedDLL
    >
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
    $<$<NOT:$<OR:$<CONFIG:ProfiledDX11>,$<CONFIG:Verified>,$<CONFIG:VerifiedDX11>,$<CONFIG:VerifiedDX11ASAN>,$<CONFIG:VerifiedDX8>,$<CONFIG:VerifiedDX9>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include"
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
    "dSINGLE;"
    "_USRDLL;"
    "XRPHYSICS_EXPORTS;"
    "MSVC;"
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /W4;
            /Z7;
            /Ot;
            /GS;
            /Zc:inline-
        >
        $<$<CONFIG:Release>:
            /GL;
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
            /GL;
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
            /Z7;
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
        /OPT:NOREF;
        /OPT:NOICF;
        /DYNAMICBASE:NO
    )
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    ode
    xrAPI
    xrCDB
    xrCore
    xrSound
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my/"
)

