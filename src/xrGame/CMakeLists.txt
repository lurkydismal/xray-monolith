set(PROJECT_NAME xrGame)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "searchlight_script.cpp"
    "searchlight_struct.cpp"
)
source_group("" FILES ${no_group_source_files})

set(AI
    "mt_config.h"
)
source_group("AI" FILES ${AI})

set(AI__AComponents__DamageManager
    "damage_manager.cpp"
    "damage_manager.h"
    "damage_manager_inline.h"
    "DamageSource.h"
)
source_group("AI\\AComponents\\DamageManager" FILES ${AI__AComponents__DamageManager})

set(AI__AComponents__DecisionManagement
    "wrapper_abstract.h"
    "wrapper_abstract_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement" FILES ${AI__AComponents__DecisionManagement})

set(AI__AComponents__DecisionManagement__ActionManagement
    "action_management_config.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement" FILES ${AI__AComponents__DecisionManagement__ActionManagement})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionBase
    "action_base.h"
    "action_base_inline.h"
    "action_base_script.cpp"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionBase" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionBase})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionBase__ActionScriptBase
    "action_script_base.h"
    "action_script_base_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionBase\\ActionScriptBase" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionBase__ActionScriptBase})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionBase__ScriptActionWrapper
    "script_action_wrapper.cpp"
    "script_action_wrapper.h"
    "script_action_wrapper_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionBase\\ScriptActionWrapper" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionBase__ScriptActionWrapper})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner
    "action_planner.h"
    "action_planner_inline.h"
    "action_planner_script.cpp"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionPlanner" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction
    "action_planner_action.h"
    "action_planner_action_inline.h"
    "action_planner_action_script.cpp"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionPlannerAction" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction__ActionPlannerActionScript
    "action_planner_action_script.h"
    "action_planner_action_script_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionPlannerAction\\ActionPlannerActionScript" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction__ActionPlannerActionScript})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction__ScriptActionPlannerActionWrapper
    "script_action_planner_action_wrapper.cpp"
    "script_action_planner_action_wrapper.h"
    "script_action_planner_action_wrapper_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionPlannerAction\\ScriptActionPlannerActionWrapper" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction__ScriptActionPlannerActionWrapper})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner__ActionPlannerScript
    "action_planner_script.h"
    "action_planner_script_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionPlanner\\ActionPlannerScript" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner__ActionPlannerScript})

set(AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner__ScriptActionPlannerWrapper
    "script_action_planner_wrapper.cpp"
    "script_action_planner_wrapper.h"
    "script_action_planner_wrapper_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\ActionPlanner\\ScriptActionPlannerWrapper" FILES ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner__ScriptActionPlannerWrapper})

set(AI__AComponents__DecisionManagement__ActionManagement__PropertyStorage
    "property_storage.h"
    "property_storage_inline.h"
    "property_storage_script.cpp"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\PropertyStorage" FILES ${AI__AComponents__DecisionManagement__ActionManagement__PropertyStorage})

set(AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator
    "property_evaluator.h"
    "property_evaluator_inline.h"
    "property_evaluator_script.cpp"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\WorldPropertyEvaluator" FILES ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator})

set(AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__ScriptPropertyEvaluatorWrapper
    "script_property_evaluator_wrapper.cpp"
    "script_property_evaluator_wrapper.h"
    "script_property_evaluator_wrapper_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\WorldPropertyEvaluator\\ScriptPropertyEvaluatorWrapper" FILES ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__ScriptPropertyEvaluatorWrapper})

set(AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__const
    "property_evaluator_const.h"
    "property_evaluator_const_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\WorldPropertyEvaluator\\const" FILES ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__const})

set(AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__member
    "property_evaluator_member.h"
    "property_evaluator_member_inline.h"
)
source_group("AI\\AComponents\\DecisionManagement\\ActionManagement\\WorldPropertyEvaluator\\member" FILES ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__member})

set(AI__AComponents__MaterialManager
    "material_manager.cpp"
    "material_manager.h"
    "material_manager_inline.h"
)
source_group("AI\\AComponents\\MaterialManager" FILES ${AI__AComponents__MaterialManager})

set(AI__AComponents__MemoryManager
    "memory_manager.cpp"
    "memory_manager.h"
    "memory_manager_inline.h"
    "memory_space.h"
    "memory_space_impl.h"
    "memory_space_script.cpp"
)
source_group("AI\\AComponents\\MemoryManager" FILES ${AI__AComponents__MemoryManager})

set(AI__AComponents__MemoryManager__clsuterized_data_managers__DangerManager
    "danger_manager.cpp"
    "danger_manager.h"
    "danger_manager_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\clsuterized_data_managers\\DangerManager" FILES ${AI__AComponents__MemoryManager__clsuterized_data_managers__DangerManager})

set(AI__AComponents__MemoryManager__clsuterized_data_managers__DangerManager__danger_object
    "danger_object.cpp"
    "danger_object.h"
    "danger_object_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\clsuterized_data_managers\\DangerManager\\danger_object" FILES ${AI__AComponents__MemoryManager__clsuterized_data_managers__DangerManager__danger_object})

set(AI__AComponents__MemoryManager__clsuterized_data_managers__EnemyManager
    "enemy_manager.cpp"
    "enemy_manager.h"
    "enemy_manager_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\clsuterized_data_managers\\EnemyManager" FILES ${AI__AComponents__MemoryManager__clsuterized_data_managers__EnemyManager})

set(AI__AComponents__MemoryManager__clsuterized_data_managers__ItemManager
    "item_manager.cpp"
    "item_manager.h"
)
source_group("AI\\AComponents\\MemoryManager\\clsuterized_data_managers\\ItemManager" FILES ${AI__AComponents__MemoryManager__clsuterized_data_managers__ItemManager})

set(AI__AComponents__MemoryManager__clsuterized_data_managers__ObjectManager
    "object_manager.h"
    "object_manager_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\clsuterized_data_managers\\ObjectManager" FILES ${AI__AComponents__MemoryManager__clsuterized_data_managers__ObjectManager})

set(AI__AComponents__MemoryManager__raw_data_managers__HitMemoryManager
    "hit_memory_manager.cpp"
    "hit_memory_manager.h"
    "hit_memory_manager_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\raw_data_managers\\HitMemoryManager" FILES ${AI__AComponents__MemoryManager__raw_data_managers__HitMemoryManager})

set(AI__AComponents__MemoryManager__raw_data_managers__SoundMemoryManager
    "sound_memory_manager.cpp"
    "sound_memory_manager.h"
    "sound_memory_manager_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\raw_data_managers\\SoundMemoryManager" FILES ${AI__AComponents__MemoryManager__raw_data_managers__SoundMemoryManager})

set(AI__AComponents__MemoryManager__raw_data_managers__SoundMemoryManager__SoundUserDataVisitor
    "sound_user_data_visitor.h"
)
source_group("AI\\AComponents\\MemoryManager\\raw_data_managers\\SoundMemoryManager\\SoundUserDataVisitor" FILES ${AI__AComponents__MemoryManager__raw_data_managers__SoundMemoryManager__SoundUserDataVisitor})

set(AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager
    "visual_memory_manager.cpp"
    "visual_memory_manager.h"
    "visual_memory_manager_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\raw_data_managers\\VisualMemoryManager" FILES ${AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager})

set(AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager__vision_client
    "vision_client.cpp"
    "vision_client.h"
    "vision_client_inline.h"
)
source_group("AI\\AComponents\\MemoryManager\\raw_data_managers\\VisualMemoryManager\\vision_client" FILES ${AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager__vision_client})

set(AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager__visual_memory_params
    "visual_memory_params.cpp"
    "visual_memory_params.h"
)
source_group("AI\\AComponents\\MemoryManager\\raw_data_managers\\VisualMemoryManager\\visual_memory_params" FILES ${AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager__visual_memory_params})

set(AI__AComponents__MovementManager
    "movement_manager.cpp"
    "movement_manager.h"
    "movement_manager_game.cpp"
    "movement_manager_impl.h"
    "movement_manager_inline.h"
    "movement_manager_level.cpp"
    "movement_manager_patrol.cpp"
    "movement_manager_physic.cpp"
    "movement_manager_space.h"
)
source_group("AI\\AComponents\\MovementManager" FILES ${AI__AComponents__MovementManager})

set(AI__AComponents__MovementManager__LocationManager
    "location_manager.cpp"
    "location_manager.h"
    "location_manager_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\LocationManager" FILES ${AI__AComponents__MovementManager__LocationManager})

set(AI__AComponents__MovementManager__LocationSelectors__AbstractLocationSelector
    "abstract_location_selector.h"
    "abstract_location_selector_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\LocationSelectors\\AbstractLocationSelector" FILES ${AI__AComponents__MovementManager__LocationSelectors__AbstractLocationSelector})

set(AI__AComponents__MovementManager__LocationSelectors__GameLocationSelector
    "game_location_selector.h"
    "game_location_selector_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\LocationSelectors\\GameLocationSelector" FILES ${AI__AComponents__MovementManager__LocationSelectors__GameLocationSelector})

set(AI__AComponents__MovementManager__LocationSelectors__LevelLocationSelector
    "level_location_selector.h"
    "level_location_selector_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\LocationSelectors\\LevelLocationSelector" FILES ${AI__AComponents__MovementManager__LocationSelectors__LevelLocationSelector})

set(AI__AComponents__MovementManager__PathManagers__AbstractPathManager
    "abstract_path_manager.h"
    "abstract_path_manager_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\PathManagers\\AbstractPathManager" FILES ${AI__AComponents__MovementManager__PathManagers__AbstractPathManager})

set(AI__AComponents__MovementManager__PathManagers__DetailPathManager
    "detail_path_builder.h"
    "detail_path_manager.cpp"
    "detail_path_manager.h"
    "detail_path_manager_inline.h"
    "detail_path_manager_smooth.cpp"
    "detail_path_manager_space.h"
)
source_group("AI\\AComponents\\MovementManager\\PathManagers\\DetailPathManager" FILES ${AI__AComponents__MovementManager__PathManagers__DetailPathManager})

set(AI__AComponents__MovementManager__PathManagers__GamePathManager
    "game_path_manager.h"
    "game_path_manager_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\PathManagers\\GamePathManager" FILES ${AI__AComponents__MovementManager__PathManagers__GamePathManager})

set(AI__AComponents__MovementManager__PathManagers__LevelPathManager
    "level_path_builder.h"
    "level_path_manager.h"
    "level_path_manager_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\PathManagers\\LevelPathManager" FILES ${AI__AComponents__MovementManager__PathManagers__LevelPathManager})

set(AI__AComponents__MovementManager__PathManagers__PatrolPathManager
    "patrol_path_manager.cpp"
    "patrol_path_manager.h"
    "patrol_path_manager_inline.h"
    "patrol_path_manager_space.h"
)
source_group("AI\\AComponents\\MovementManager\\PathManagers\\PatrolPathManager" FILES ${AI__AComponents__MovementManager__PathManagers__PatrolPathManager})

set(AI__AComponents__MovementManager__RestrictedObject
    "restricted_object.cpp"
    "restricted_object.h"
    "restricted_object_inline.h"
)
source_group("AI\\AComponents\\MovementManager\\RestrictedObject" FILES ${AI__AComponents__MovementManager__RestrictedObject})

set(AI__AComponents__ObjectHandler
    "object_handler.cpp"
    "object_handler.h"
    "object_handler_inline.h"
    "object_handler_space.h"
)
source_group("AI\\AComponents\\ObjectHandler" FILES ${AI__AComponents__ObjectHandler})

set(AI__AComponents__ObjectHandler__planner
    "object_handler_planner.cpp"
    "object_handler_planner.h"
    "object_handler_planner_impl.h"
    "object_handler_planner_inline.h"
    "object_handler_planner_missile.cpp"
    "object_handler_planner_weapon.cpp"
)
source_group("AI\\AComponents\\ObjectHandler\\planner" FILES ${AI__AComponents__ObjectHandler__planner})

set(AI__AComponents__ObjectHandler__planner__actions
    "object_actions.cpp"
    "object_actions.h"
    "object_actions_inline.h"
)
source_group("AI\\AComponents\\ObjectHandler\\planner\\actions" FILES ${AI__AComponents__ObjectHandler__planner__actions})

set(AI__AComponents__ObjectHandler__planner__properties
    "object_property_evaluators.cpp"
    "object_property_evaluators.h"
    "object_property_evaluators_inline.h"
)
source_group("AI\\AComponents\\ObjectHandler\\planner\\properties" FILES ${AI__AComponents__ObjectHandler__planner__properties})

set(AI__AComponents__ProblemSolver
    "problem_solver.h"
    "problem_solver_inline.h"
)
source_group("AI\\AComponents\\ProblemSolver" FILES ${AI__AComponents__ProblemSolver})

set(AI__AComponents__ProblemSolver__condition_state
    "condition_state.h"
    "condition_state_inline.h"
)
source_group("AI\\AComponents\\ProblemSolver\\condition_state" FILES ${AI__AComponents__ProblemSolver__condition_state})

set(AI__AComponents__ProblemSolver__condition_state__ScriptWorldState
    "script_world_state.h"
    "script_world_state_script.cpp"
)
source_group("AI\\AComponents\\ProblemSolver\\condition_state\\ScriptWorldState" FILES ${AI__AComponents__ProblemSolver__condition_state__ScriptWorldState})

set(AI__AComponents__ProblemSolver__operator_abstract
    "operator_abstract.h"
    "operator_abstract_inline.h"
)
source_group("AI\\AComponents\\ProblemSolver\\operator_abstract" FILES ${AI__AComponents__ProblemSolver__operator_abstract})

set(AI__AComponents__ProblemSolver__operator_condition
    "operator_condition.h"
    "operator_condition_inline.h"
)
source_group("AI\\AComponents\\ProblemSolver\\operator_condition" FILES ${AI__AComponents__ProblemSolver__operator_condition})

set(AI__AComponents__ProblemSolver__operator_condition__ScriptWorldProperty
    "script_world_property.h"
    "script_world_property_inline.h"
    "script_world_property_script.cpp"
)
source_group("AI\\AComponents\\ProblemSolver\\operator_condition\\ScriptWorldProperty" FILES ${AI__AComponents__ProblemSolver__operator_condition__ScriptWorldProperty})

set(AI__AComponents__SetupManager
    "setup_manager.h"
    "setup_manager_inline.h"
)
source_group("AI\\AComponents\\SetupManager" FILES ${AI__AComponents__SetupManager})

set(AI__AComponents__SightManager
    "sight_manager.cpp"
    "sight_manager.h"
    "sight_manager_inline.h"
    "sight_manager_space.h"
    "sight_manager_target.cpp"
)
source_group("AI\\AComponents\\SightManager" FILES ${AI__AComponents__SightManager})

set(AI__AComponents__SightManager__aimers__base
    "aimers_base.cpp"
    "aimers_base.h"
    "aimers_base_inline.h"
)
source_group("AI\\AComponents\\SightManager\\aimers\\base" FILES ${AI__AComponents__SightManager__aimers__base})

set(AI__AComponents__SightManager__aimers__bone
    "aimers_bone.h"
    "aimers_bone_inline.h"
)
source_group("AI\\AComponents\\SightManager\\aimers\\bone" FILES ${AI__AComponents__SightManager__aimers__bone})

set(AI__AComponents__SightManager__aimers__weapon
    "aimers_weapon.cpp"
    "aimers_weapon.h"
    "aimers_weapon_inline.h"
)
source_group("AI\\AComponents\\SightManager\\aimers\\weapon" FILES ${AI__AComponents__SightManager__aimers__weapon})

set(AI__AComponents__SightManager__control_action
    "control_action.h"
    "control_action_inline.h"
)
source_group("AI\\AComponents\\SightManager\\control_action" FILES ${AI__AComponents__SightManager__control_action})

set(AI__AComponents__SightManager__sight_action
    "sight_action.cpp"
    "sight_action.h"
    "sight_action_inline.h"
)
source_group("AI\\AComponents\\SightManager\\sight_action" FILES ${AI__AComponents__SightManager__sight_action})

set(AI__AComponents__SightManager__sight_control_action
    "sight_control_action.h"
    "sight_control_action_inline.h"
)
source_group("AI\\AComponents\\SightManager\\sight_control_action" FILES ${AI__AComponents__SightManager__sight_control_action})

set(AI__AComponents__SoundPlayer
    "sound_player.cpp"
    "sound_player.h"
    "sound_player_inline.h"
)
source_group("AI\\AComponents\\SoundPlayer" FILES ${AI__AComponents__SoundPlayer})

set(AI__AComponents__SoundPlayer__sound_collection_storage
    "sound_collection_storage.cpp"
    "sound_collection_storage.h"
    "sound_collection_storage_inline.h"
)
source_group("AI\\AComponents\\SoundPlayer\\sound_collection_storage" FILES ${AI__AComponents__SoundPlayer__sound_collection_storage})

set(AI__AComponents__SpaceRestrictionManager
    "../xrServerEntities/restriction_space.h"
    "space_restriction_manager.cpp"
    "space_restriction_manager.h"
    "space_restriction_manager_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager" FILES ${AI__AComponents__SpaceRestrictionManager})

set(AI__AComponents__SpaceRestrictionManager__SpaceRestriction
    "space_restriction.cpp"
    "space_restriction.h"
    "space_restriction_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager\\SpaceRestriction" FILES ${AI__AComponents__SpaceRestrictionManager__SpaceRestriction})

set(AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder
    "space_restriction_holder.cpp"
    "space_restriction_holder.h"
    "space_restriction_holder_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager\\SpaceRestrictionHolder" FILES ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder})

set(AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionAbstract
    "space_restriction_abstract.h"
    "space_restriction_abstract_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager\\SpaceRestrictionHolder\\SpaceRestrictionAbstract" FILES ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionAbstract})

set(AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionBase
    "space_restriction_base.cpp"
    "space_restriction_base.h"
    "space_restriction_base_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager\\SpaceRestrictionHolder\\SpaceRestrictionBase" FILES ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionBase})

set(AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionBridge
    "space_restriction_bridge.cpp"
    "space_restriction_bridge.h"
    "space_restriction_bridge_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager\\SpaceRestrictionHolder\\SpaceRestrictionBridge" FILES ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionBridge})

set(AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionComposition
    "space_restriction_composition.cpp"
    "space_restriction_composition.h"
    "space_restriction_composition_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager\\SpaceRestrictionHolder\\SpaceRestrictionComposition" FILES ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionComposition})

set(AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionShape
    "space_restriction_shape.cpp"
    "space_restriction_shape.h"
    "space_restriction_shape_inline.h"
)
source_group("AI\\AComponents\\SpaceRestrictionManager\\SpaceRestrictionHolder\\SpaceRestrictionShape" FILES ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionShape})

set(AI__AComponents__Step_Manager
    "step_manager.cpp"
    "step_manager.h"
    "step_manager_defs.h"
)
source_group("AI\\AComponents\\Step Manager" FILES ${AI__AComponents__Step_Manager})

set(AI__AComponents__doors_manager
    "doors.h"
)
source_group("AI\\AComponents\\doors_manager" FILES ${AI__AComponents__doors_manager})

set(AI__AComponents__doors_manager__actor
    "doors_actor.cpp"
    "doors_actor.h"
)
source_group("AI\\AComponents\\doors_manager\\actor" FILES ${AI__AComponents__doors_manager__actor})

set(AI__AComponents__doors_manager__door
    "doors_door.cpp"
    "doors_door.h"
)
source_group("AI\\AComponents\\doors_manager\\door" FILES ${AI__AComponents__doors_manager__door})

set(AI__AComponents__doors_manager__manager
    "doors_manager.cpp"
    "doors_manager.h"
)
source_group("AI\\AComponents\\doors_manager\\manager" FILES ${AI__AComponents__doors_manager__manager})

set(AI__AComponents__moving_objects
    "moving_objects.cpp"
    "moving_objects.h"
    "moving_objects_dynamic.cpp"
    "moving_objects_dynamic_collision.cpp"
    "moving_objects_impl.h"
    "moving_objects_inline.h"
    "moving_objects_static.cpp"
)
source_group("AI\\AComponents\\moving_objects" FILES ${AI__AComponents__moving_objects})

set(AI__AComponents__moving_objects__moving_object
    "moving_object.cpp"
    "moving_object.h"
    "moving_object_inline.h"
)
source_group("AI\\AComponents\\moving_objects\\moving_object" FILES ${AI__AComponents__moving_objects__moving_object})

set(AI__AComponents__moving_objects__obstacles_query
    "obstacles_query.cpp"
    "obstacles_query.h"
    "obstacles_query_inline.h"
)
source_group("AI\\AComponents\\moving_objects\\obstacles_query" FILES ${AI__AComponents__moving_objects__obstacles_query})

set(AI__ACover
    "cover_manager.cpp"
    "cover_manager.h"
    "cover_manager_inline.h"
)
source_group("AI\\ACover" FILES ${AI__ACover})

set(AI__ACover__cover_point
    "cover_point.h"
    "cover_point_inline.h"
    "cover_point_script.cpp"
)
source_group("AI\\ACover\\cover_point" FILES ${AI__ACover__cover_point})

set(AI__ACover__smart_cover__cover
    "smart_cover.cpp"
    "smart_cover.h"
    "smart_cover_inline.h"
)
source_group("AI\\ACover\\smart_cover\\cover" FILES ${AI__ACover__smart_cover__cover})

set(AI__ACover__smart_cover__detail
    "smart_cover_detail.cpp"
    "smart_cover_detail.h"
)
source_group("AI\\ACover\\smart_cover\\detail" FILES ${AI__ACover__smart_cover__detail})

set(AI__ACover__smart_cover__object
    "smart_cover_object.cpp"
    "smart_cover_object.h"
    "smart_cover_object_inline.h"
    "smart_cover_object_script.cpp"
)
source_group("AI\\ACover\\smart_cover\\object" FILES ${AI__ACover__smart_cover__object})

set(AI__ACover__smart_cover__storage
    "smart_cover_storage.cpp"
    "smart_cover_storage.h"
)
source_group("AI\\ACover\\smart_cover\\storage" FILES ${AI__ACover__smart_cover__storage})

set(AI__ACover__smart_cover__storage__description
    "smart_cover_description.cpp"
    "smart_cover_description.h"
    "smart_cover_description_inline.h"
)
source_group("AI\\ACover\\smart_cover\\storage\\description" FILES ${AI__ACover__smart_cover__storage__description})

set(AI__ACover__smart_cover__storage__description__loophole
    "smart_cover_loophole.cpp"
    "smart_cover_loophole.h"
    "smart_cover_loophole_inline.h"
)
source_group("AI\\ACover\\smart_cover\\storage\\description\\loophole" FILES ${AI__ACover__smart_cover__storage__description__loophole})

set(AI__ACover__smart_cover__storage__description__loophole__action
    "smart_cover_action.cpp"
    "smart_cover_action.h"
    "smart_cover_action_inline.h"
)
source_group("AI\\ACover\\smart_cover\\storage\\description\\loophole\\action" FILES ${AI__ACover__smart_cover__storage__description__loophole__action})

set(AI__ACover__smart_cover__storage__description__transitions__animation
    "smart_cover_transition_animation.cpp"
    "smart_cover_transition_animation.hpp"
    "smart_cover_transition_animation_inline.hpp"
)
source_group("AI\\ACover\\smart_cover\\storage\\description\\transitions\\animation" FILES ${AI__ACover__smart_cover__storage__description__transitions__animation})

set(AI__ACover__smart_cover__storage__description__transitions__transition
    "smart_cover_transition.cpp"
    "smart_cover_transition.hpp"
)
source_group("AI\\ACover\\smart_cover\\storage\\description\\transitions\\transition" FILES ${AI__ACover__smart_cover__storage__description__transitions__transition})

set(AI__ADebug
    "ai_debug.h"
    "ai_debug_variables.cpp"
    "ai_debug_variables.h"
    "dbg_draw_frustum.cpp"
    "debug_text_tree.cpp"
    "debug_text_tree.h"
    "debug_text_tree_inline.h"
)
source_group("AI\\ADebug" FILES ${AI__ADebug})

set(AI__AEval__functions__base
    "ef_base.h"
)
source_group("AI\\AEval\\functions\\base" FILES ${AI__AEval__functions__base})

set(AI__AEval__functions__patterns
    "ef_pattern.cpp"
    "ef_pattern.h"
)
source_group("AI\\AEval\\functions\\patterns" FILES ${AI__AEval__functions__patterns})

set(AI__AEval__functions__primary
    "ef_primary.cpp"
    "ef_primary.h"
)
source_group("AI\\AEval\\functions\\primary" FILES ${AI__AEval__functions__primary})

set(AI__AEval__storage
    "ef_storage.cpp"
    "ef_storage.h"
    "ef_storage_inline.h"
    "ef_storage_script.cpp"
)
source_group("AI\\AEval\\storage" FILES ${AI__AEval__storage})

set(AI__AGroup__agent_manager
    "agent_manager.cpp"
    "agent_manager.h"
    "agent_manager_inline.h"
    "agent_manager_space.h"
)
source_group("AI\\AGroup\\agent_manager" FILES ${AI__AGroup__agent_manager})

set(AI__AGroup__agent_manager__agent_corpse_manager
    "agent_corpse_manager.cpp"
    "agent_corpse_manager.h"
    "agent_corpse_manager_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_corpse_manager" FILES ${AI__AGroup__agent_manager__agent_corpse_manager})

set(AI__AGroup__agent_manager__agent_corpse_manager__member_corpse
    "member_corpse.h"
    "member_corpse_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_corpse_manager\\member_corpse" FILES ${AI__AGroup__agent_manager__agent_corpse_manager__member_corpse})

set(AI__AGroup__agent_manager__agent_enemy_manager
    "agent_enemy_manager.cpp"
    "agent_enemy_manager.h"
    "agent_enemy_manager_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_enemy_manager" FILES ${AI__AGroup__agent_manager__agent_enemy_manager})

set(AI__AGroup__agent_manager__agent_enemy_manager__member_enemy
    "member_enemy.h"
    "member_enemy_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_enemy_manager\\member_enemy" FILES ${AI__AGroup__agent_manager__agent_enemy_manager__member_enemy})

set(AI__AGroup__agent_manager__agent_explosive_manager
    "agent_explosive_manager.cpp"
    "agent_explosive_manager.h"
    "agent_explosive_manager_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_explosive_manager" FILES ${AI__AGroup__agent_manager__agent_explosive_manager})

set(AI__AGroup__agent_manager__agent_explosive_manager__danger_explosive
    "danger_explosive.cpp"
    "danger_explosive.h"
    "danger_explosive_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_explosive_manager\\danger_explosive" FILES ${AI__AGroup__agent_manager__agent_explosive_manager__danger_explosive})

set(AI__AGroup__agent_manager__agent_location_manager
    "agent_location_manager.cpp"
    "agent_location_manager.h"
    "agent_location_manager_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_location_manager" FILES ${AI__AGroup__agent_manager__agent_location_manager})

set(AI__AGroup__agent_manager__agent_location_manager__danger_cover_location
    "danger_cover_location.cpp"
    "danger_cover_location.h"
    "danger_cover_location_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_location_manager\\danger_cover_location" FILES ${AI__AGroup__agent_manager__agent_location_manager__danger_cover_location})

set(AI__AGroup__agent_manager__agent_location_manager__danger_location
    "danger_location.cpp"
    "danger_location.h"
    "danger_location_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_location_manager\\danger_location" FILES ${AI__AGroup__agent_manager__agent_location_manager__danger_location})

set(AI__AGroup__agent_manager__agent_location_manager__danger_object_location
    "danger_object_location.cpp"
    "danger_object_location.h"
    "danger_object_location_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_location_manager\\danger_object_location" FILES ${AI__AGroup__agent_manager__agent_location_manager__danger_object_location})

set(AI__AGroup__agent_manager__agent_member_manager
    "agent_member_manager.cpp"
    "agent_member_manager.h"
    "agent_member_manager_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_member_manager" FILES ${AI__AGroup__agent_manager__agent_member_manager})

set(AI__AGroup__agent_manager__agent_member_manager__member_order
    "member_order.h"
    "member_order_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_member_manager\\member_order" FILES ${AI__AGroup__agent_manager__agent_member_manager__member_order})

set(AI__AGroup__agent_manager__agent_memory_manager
    "agent_memory_manager.cpp"
    "agent_memory_manager.h"
    "agent_memory_manager_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_memory_manager" FILES ${AI__AGroup__agent_manager__agent_memory_manager})

set(AI__AGroup__agent_manager__agent_planner
    "agent_manager_planner.cpp"
    "agent_manager_planner.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_planner" FILES ${AI__AGroup__agent_manager__agent_planner})

set(AI__AGroup__agent_manager__agent_planner__actions
    "agent_manager_actions.cpp"
    "agent_manager_actions.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_planner\\actions" FILES ${AI__AGroup__agent_manager__agent_planner__actions})

set(AI__AGroup__agent_manager__agent_planner__properties
    "agent_manager_properties.cpp"
    "agent_manager_properties.h"
    "agent_manager_properties_inline.h"
)
source_group("AI\\AGroup\\agent_manager\\agent_planner\\properties" FILES ${AI__AGroup__agent_manager__agent_planner__properties})

set(AI__ALife
    "../xrServerEntities/alife_space.cpp"
    "../xrServerEntities/alife_space.h"
    "alife_simulator.cpp"
    "alife_simulator.h"
    "alife_simulator_inline.h"
    "alife_simulator_script.cpp"
)
source_group("AI\\ALife" FILES ${AI__ALife})

set(AI__ALife__interaction_manager
    "alife_interaction_manager.cpp"
    "alife_interaction_manager.h"
    "alife_interaction_manager_inline.h"
)
source_group("AI\\ALife\\interaction_manager" FILES ${AI__ALife__interaction_manager})

set(AI__ALife__interaction_manager__combat_manager
    "alife_combat_manager.cpp"
    "alife_combat_manager.h"
    "alife_combat_manager_inline.h"
)
source_group("AI\\ALife\\interaction_manager\\combat_manager" FILES ${AI__ALife__interaction_manager__combat_manager})

set(AI__ALife__interaction_manager__communication_manager
    "alife_communication_manager.cpp"
    "alife_communication_manager.h"
    "alife_communication_manager_inline.h"
    "alife_communication_space.h"
)
source_group("AI\\ALife\\interaction_manager\\communication_manager" FILES ${AI__ALife__interaction_manager__communication_manager})

set(AI__ALife__inventory_upgrade
    "inventory_upgrade_manager.cpp"
    "inventory_upgrade_manager.h"
    "inventory_upgrade_manager_inline.h"
)
source_group("AI\\ALife\\inventory_upgrade" FILES ${AI__ALife__inventory_upgrade})

set(AI__ALife__inventory_upgrade__property
    "inventory_upgrade_property.cpp"
    "inventory_upgrade_property.h"
    "inventory_upgrade_property_inline.h"
)
source_group("AI\\ALife\\inventory_upgrade\\property" FILES ${AI__ALife__inventory_upgrade__property})

set(AI__ALife__inventory_upgrade__upgrade
    "inventory_upgrade.cpp"
    "inventory_upgrade.h"
    "inventory_upgrade_inline.h"
)
source_group("AI\\ALife\\inventory_upgrade\\upgrade" FILES ${AI__ALife__inventory_upgrade__upgrade})

set(AI__ALife__inventory_upgrade__upgrade_base
    "inventory_upgrade_base.cpp"
    "inventory_upgrade_base.h"
    "inventory_upgrade_base_inline.h"
)
source_group("AI\\ALife\\inventory_upgrade\\upgrade_base" FILES ${AI__ALife__inventory_upgrade__upgrade_base})

set(AI__ALife__inventory_upgrade__upgrade_group
    "inventory_upgrade_group.cpp"
    "inventory_upgrade_group.h"
    "inventory_upgrade_group_inline.h"
)
source_group("AI\\ALife\\inventory_upgrade\\upgrade_group" FILES ${AI__ALife__inventory_upgrade__upgrade_group})

set(AI__ALife__inventory_upgrade__upgrade_root
    "inventory_upgrade_root.cpp"
    "inventory_upgrade_root.h"
    "inventory_upgrade_root_inline.h"
)
source_group("AI\\ALife\\inventory_upgrade\\upgrade_root" FILES ${AI__ALife__inventory_upgrade__upgrade_root})

set(AI__ALife__saved_game_wrapper
    "saved_game_wrapper.cpp"
    "saved_game_wrapper.h"
    "saved_game_wrapper_inline.h"
    "saved_game_wrapper_script.cpp"
)
source_group("AI\\ALife\\saved_game_wrapper" FILES ${AI__ALife__saved_game_wrapper})

set(AI__ALife__server_entities__anomalous_zone
    "alife_anomalous_zone.cpp"
)
source_group("AI\\ALife\\server_entities\\anomalous_zone" FILES ${AI__ALife__server_entities__anomalous_zone})

set(AI__ALife__server_entities__creature_abstract
    "alife_creature_abstract.cpp"
)
source_group("AI\\ALife\\server_entities\\creature_abstract" FILES ${AI__ALife__server_entities__creature_abstract})

set(AI__ALife__server_entities__dynamic_object
    "alife_dynamic_object.cpp"
)
source_group("AI\\ALife\\server_entities\\dynamic_object" FILES ${AI__ALife__server_entities__dynamic_object})

set(AI__ALife__server_entities__group_abstract
    "alife_group_abstract.cpp"
)
source_group("AI\\ALife\\server_entities\\group_abstract" FILES ${AI__ALife__server_entities__group_abstract})

set(AI__ALife__server_entities__human
    "alife_human_abstract.cpp"
)
source_group("AI\\ALife\\server_entities\\human" FILES ${AI__ALife__server_entities__human})

set(AI__ALife__server_entities__human__brain
    "../xrServerEntities/alife_human_brain.cpp"
    "../xrServerEntities/alife_human_brain.h"
    "../xrServerEntities/alife_human_brain_inline.h"
    "alife_human_brain_save.h"
    "alife_human_brain_script.cpp"
)
source_group("AI\\ALife\\server_entities\\human\\brain" FILES ${AI__ALife__server_entities__human__brain})

set(AI__ALife__server_entities__human__object_handler
    "alife_human_object_handler.cpp"
    "alife_human_object_handler.h"
    "alife_human_object_handler_inline.h"
    "alife_human_object_handler_save.h"
)
source_group("AI\\ALife\\server_entities\\human\\object_handler" FILES ${AI__ALife__server_entities__human__object_handler})

set(AI__ALife__server_entities__monster_abstract
    "alife_monster_abstract.cpp"
    "alife_monster_base.cpp"
)
source_group("AI\\ALife\\server_entities\\monster_abstract" FILES ${AI__ALife__server_entities__monster_abstract})

set(AI__ALife__server_entities__monster_abstract__brain
    "../xrServerEntities/alife_monster_brain.cpp"
    "../xrServerEntities/alife_monster_brain.h"
    "../xrServerEntities/alife_monster_brain_inline.h"
    "alife_monster_brain_script.cpp"
)
source_group("AI\\ALife\\server_entities\\monster_abstract\\brain" FILES ${AI__ALife__server_entities__monster_abstract__brain})

set(AI__ALife__server_entities__monster_abstract__movement_manager
    "alife_monster_movement_manager.cpp"
    "alife_monster_movement_manager.h"
    "alife_monster_movement_manager_inline.h"
    "alife_monster_movement_manager_script.cpp"
)
source_group("AI\\ALife\\server_entities\\monster_abstract\\movement_manager" FILES ${AI__ALife__server_entities__monster_abstract__movement_manager})

set(AI__ALife__server_entities__monster_abstract__movement_manager__detail_path_manager
    "alife_monster_detail_path_manager.cpp"
    "alife_monster_detail_path_manager.h"
    "alife_monster_detail_path_manager_inline.h"
    "alife_monster_detail_path_manager_script.cpp"
)
source_group("AI\\ALife\\server_entities\\monster_abstract\\movement_manager\\detail_path_manager" FILES ${AI__ALife__server_entities__monster_abstract__movement_manager__detail_path_manager})

set(AI__ALife__server_entities__monster_abstract__movement_manager__movement_manager_holder
    "../xrServerEntities/alife_movement_manager_holder.h"
)
source_group("AI\\ALife\\server_entities\\monster_abstract\\movement_manager\\movement_manager_holder" FILES ${AI__ALife__server_entities__monster_abstract__movement_manager__movement_manager_holder})

set(AI__ALife__server_entities__monster_abstract__movement_manager__patrol_path_manager
    "alife_monster_patrol_path_manager.cpp"
    "alife_monster_patrol_path_manager.h"
    "alife_monster_patrol_path_manager_inline.h"
    "alife_monster_patrol_path_manager_script.cpp"
)
source_group("AI\\ALife\\server_entities\\monster_abstract\\movement_manager\\patrol_path_manager" FILES ${AI__ALife__server_entities__monster_abstract__movement_manager__patrol_path_manager})

set(AI__ALife__server_entities__object
    "alife_object.cpp"
)
source_group("AI\\ALife\\server_entities\\object" FILES ${AI__ALife__server_entities__object})

set(AI__ALife__server_entities__online_offline_group
    "alife_online_offline_group.cpp"
)
source_group("AI\\ALife\\server_entities\\online_offline_group" FILES ${AI__ALife__server_entities__online_offline_group})

set(AI__ALife__server_entities__online_offline_group__brain
    "alife_online_offline_group_brain.cpp"
    "alife_online_offline_group_brain.h"
    "alife_online_offline_group_brain_inline.h"
)
source_group("AI\\ALife\\server_entities\\online_offline_group\\brain" FILES ${AI__ALife__server_entities__online_offline_group__brain})

set(AI__ALife__server_entities__smart_zone
    "alife_smart_zone.cpp"
)
source_group("AI\\ALife\\server_entities\\smart_zone" FILES ${AI__ALife__server_entities__smart_zone})

set(AI__ALife__server_entities__trader
    "alife_trader.cpp"
)
source_group("AI\\ALife\\server_entities\\trader" FILES ${AI__ALife__server_entities__trader})

set(AI__ALife__server_entities__trader_abstract
    "alife_trader_abstract.cpp"
)
source_group("AI\\ALife\\server_entities\\trader_abstract" FILES ${AI__ALife__server_entities__trader_abstract})

set(AI__ALife__simulator_base
    "alife_simulator_base.cpp"
    "alife_simulator_base.h"
    "alife_simulator_base2.cpp"
    "alife_simulator_base_inline.h"
)
source_group("AI\\ALife\\simulator_base" FILES ${AI__ALife__simulator_base})

set(AI__ALife__simulator_base__header
    "alife_simulator_header.cpp"
    "alife_simulator_header.h"
    "alife_simulator_header_inline.h"
)
source_group("AI\\ALife\\simulator_base\\header" FILES ${AI__ALife__simulator_base__header})

set(AI__ALife__simulator_base__registries__abstract_registry
    "alife_abstract_registry.h"
    "alife_abstract_registry_inline.h"
    "alife_registry_wrapper.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\abstract_registry" FILES ${AI__ALife__simulator_base__registries__abstract_registry})

set(AI__ALife__simulator_base__registries__graph_registry
    "alife_graph_registry.cpp"
    "alife_graph_registry.h"
    "alife_graph_registry_inline.h"
    "graph_abstract.h"
    "graph_abstract_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\graph_registry" FILES ${AI__ALife__simulator_base__registries__graph_registry})

set(AI__ALife__simulator_base__registries__graph_registry__level_registry
    "alife_level_registry.h"
    "alife_level_registry_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\graph_registry\\level_registry" FILES ${AI__ALife__simulator_base__registries__graph_registry__level_registry})

set(AI__ALife__simulator_base__registries__group_registry
    "alife_group_registry.cpp"
    "alife_group_registry.h"
    "alife_group_registry_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\group_registry" FILES ${AI__ALife__simulator_base__registries__group_registry})

set(AI__ALife__simulator_base__registries__object_registry
    "alife_object_registry.cpp"
    "alife_object_registry.h"
    "alife_object_registry_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\object_registry" FILES ${AI__ALife__simulator_base__registries__object_registry})

set(AI__ALife__simulator_base__registries__safe_map_iterator
    "safe_map_iterator.h"
    "safe_map_iterator_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\safe_map_iterator" FILES ${AI__ALife__simulator_base__registries__safe_map_iterator})

set(AI__ALife__simulator_base__registries__schedule_registry
    "alife_schedule_registry.cpp"
    "alife_schedule_registry.h"
    "alife_schedule_registry_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\schedule_registry" FILES ${AI__ALife__simulator_base__registries__schedule_registry})

set(AI__ALife__simulator_base__registries__smart_terrain_registry
    "alife_smart_terrain_registry.cpp"
    "alife_smart_terrain_registry.h"
    "alife_smart_terrain_registry_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\smart_terrain_registry" FILES ${AI__ALife__simulator_base__registries__smart_terrain_registry})

set(AI__ALife__simulator_base__registries__spawn_registry
    "alife_spawn_registry.cpp"
    "alife_spawn_registry.h"
    "alife_spawn_registry_inline.h"
    "alife_spawn_registry_spawn.cpp"
)
source_group("AI\\ALife\\simulator_base\\registries\\spawn_registry" FILES ${AI__ALife__simulator_base__registries__spawn_registry})

set(AI__ALife__simulator_base__registries__spawn_registry__header
    "alife_spawn_registry_header.cpp"
    "alife_spawn_registry_header.h"
    "alife_spawn_registry_header_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\spawn_registry\\header" FILES ${AI__ALife__simulator_base__registries__spawn_registry__header})

set(AI__ALife__simulator_base__registries__spawn_registry__server_entity_wrapper
    "server_entity_wrapper.cpp"
    "server_entity_wrapper.h"
    "server_entity_wrapper_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\spawn_registry\\server_entity_wrapper" FILES ${AI__ALife__simulator_base__registries__spawn_registry__server_entity_wrapper})

set(AI__ALife__simulator_base__registries__story_registry
    "alife_story_registry.cpp"
    "alife_story_registry.h"
    "alife_story_registry_inline.h"
)
source_group("AI\\ALife\\simulator_base\\registries\\story_registry" FILES ${AI__ALife__simulator_base__registries__story_registry})

set(AI__ALife__simulator_base__registry_container
    "alife_registry_container.cpp"
    "alife_registry_container.h"
    "alife_registry_container_inline.h"
    "alife_registry_wrappers.h"
)
source_group("AI\\ALife\\simulator_base\\registry_container" FILES ${AI__ALife__simulator_base__registry_container})

set(AI__ALife__simulator_base__smart_terrain_task
    "alife_smart_terrain_task.cpp"
    "alife_smart_terrain_task.h"
    "alife_smart_terrain_task_inline.h"
    "alife_smart_terrain_task_script.cpp"
)
source_group("AI\\ALife\\simulator_base\\smart_terrain_task" FILES ${AI__ALife__simulator_base__smart_terrain_task})

set(AI__ALife__simulator_base__time_manager
    "alife_time_manager.cpp"
    "alife_time_manager.h"
    "alife_time_manager_inline.h"
)
source_group("AI\\ALife\\simulator_base\\time_manager" FILES ${AI__ALife__simulator_base__time_manager})

set(AI__ALife__update_manager
    "alife_update_manager.cpp"
    "alife_update_manager.h"
    "alife_update_manager_inline.h"
)
source_group("AI\\ALife\\update_manager" FILES ${AI__ALife__update_manager})

set(AI__ALife__update_manager__storage_manager
    "alife_storage_manager.cpp"
    "alife_storage_manager.h"
    "alife_storage_manager_inline.h"
)
source_group("AI\\ALife\\update_manager\\storage_manager" FILES ${AI__ALife__update_manager__storage_manager})

set(AI__ALife__update_manager__surge_manager
    "alife_surge_manager.cpp"
    "alife_surge_manager.h"
    "alife_surge_manager_inline.h"
)
source_group("AI\\ALife\\update_manager\\surge_manager" FILES ${AI__ALife__update_manager__surge_manager})

set(AI__ALife__update_manager__switch_manager
    "alife_switch_manager.cpp"
    "alife_switch_manager.h"
    "alife_switch_manager_inline.h"
)
source_group("AI\\ALife\\update_manager\\switch_manager" FILES ${AI__ALife__update_manager__switch_manager})

set(AI__AMonsters__common__base_monster
    "ai/monsters/basemonster/base_monster.cpp"
    "ai/monsters/basemonster/base_monster.h"
    "ai/monsters/basemonster/base_monster_anim.cpp"
    "ai/monsters/basemonster/base_monster_debug.cpp"
    "ai/monsters/basemonster/base_monster_feel.cpp"
    "ai/monsters/basemonster/base_monster_inline.h"
    "ai/monsters/basemonster/base_monster_misc.cpp"
    "ai/monsters/basemonster/base_monster_net.cpp"
    "ai/monsters/basemonster/base_monster_path.cpp"
    "ai/monsters/basemonster/base_monster_script.cpp"
    "ai/monsters/basemonster/base_monster_startup.cpp"
    "ai/monsters/basemonster/base_monster_think.cpp"
)
source_group("AI\\AMonsters\\common\\base monster" FILES ${AI__AMonsters__common__base_monster})

set(AI__AMonsters__common__components
    "ai/monsters/ai_monster_defs.h"
    "ai/monsters/ai_monster_shared_data.h"
    "ai/monsters/ai_monster_utils.cpp"
    "ai/monsters/ai_monster_utils.h"
    "ai/monsters/anti_aim_ability.cpp"
    "ai/monsters/anti_aim_ability.h"
    "ai/monsters/monster_aura.cpp"
    "ai/monsters/monster_aura.h"
    "ai/monsters/monster_corpse_manager.cpp"
    "ai/monsters/monster_corpse_manager.h"
    "ai/monsters/monster_enemy_manager.cpp"
    "ai/monsters/monster_enemy_manager.h"
    "ai/monsters/monster_sound_defs.h"
    "ai/monsters/monster_velocity_space.h"
)
source_group("AI\\AMonsters\\common\\components" FILES ${AI__AMonsters__common__components})

set(AI__AMonsters__common__components__Abilities__Controlled
    "ai/monsters/controlled_entity.h"
    "ai/monsters/controlled_entity_inline.h"
)
source_group("AI\\AMonsters\\common\\components\\Abilities\\Controlled" FILES ${AI__AMonsters__common__components__Abilities__Controlled})

set(AI__AMonsters__common__components__Abilities__Energy_Holder
    "ai/monsters/energy_holder.cpp"
    "ai/monsters/energy_holder.h"
)
source_group("AI\\AMonsters\\common\\components\\Abilities\\Energy Holder" FILES ${AI__AMonsters__common__components__Abilities__Energy_Holder})

set(AI__AMonsters__common__components__Abilities__Invisibility
    "ai/monsters/invisibility.cpp"
    "ai/monsters/invisibility.h"
)
source_group("AI\\AMonsters\\common\\components\\Abilities\\Invisibility" FILES ${AI__AMonsters__common__components__Abilities__Invisibility})

set(AI__AMonsters__common__components__Abilities__Psy_Aura
    "ai/monsters/psy_aura.cpp"
    "ai/monsters/psy_aura.h"
)
source_group("AI\\AMonsters\\common\\components\\Abilities\\Psy Aura" FILES ${AI__AMonsters__common__components__Abilities__Psy_Aura})

set(AI__AMonsters__common__components__Abilities__Scan
    "ai/monsters/scanning_ability.h"
    "ai/monsters/scanning_ability_inline.h"
)
source_group("AI\\AMonsters\\common\\components\\Abilities\\Scan" FILES ${AI__AMonsters__common__components__Abilities__Scan})

set(AI__AMonsters__common__components__Abilities__Telekinesis
    "ai/monsters/telekinesis.cpp"
    "ai/monsters/telekinesis.h"
    "ai/monsters/telekinesis_inline.h"
    "ai/monsters/telekinetic_object.cpp"
    "ai/monsters/telekinetic_object.h"
    "TeleWhirlwind.cpp"
    "TeleWhirlwind.h"
)
source_group("AI\\AMonsters\\common\\components\\Abilities\\Telekinesis" FILES ${AI__AMonsters__common__components__Abilities__Telekinesis})

set(AI__AMonsters__common__components__Actor_Controller
    "ai/monsters/controlled_actor.cpp"
    "ai/monsters/controlled_actor.h"
)
source_group("AI\\AMonsters\\common\\components\\Actor Controller" FILES ${AI__AMonsters__common__components__Actor_Controller})

set(AI__AMonsters__common__components__Anomaly_Detector
    "ai/monsters/anomaly_detector.cpp"
    "ai/monsters/anomaly_detector.h"
)
source_group("AI\\AMonsters\\common\\components\\Anomaly Detector" FILES ${AI__AMonsters__common__components__Anomaly_Detector})

set(AI__AMonsters__common__components__Bones
    "ai/monsters/ai_monster_bones.cpp"
    "ai/monsters/ai_monster_bones.h"
)
source_group("AI\\AMonsters\\common\\components\\Bones" FILES ${AI__AMonsters__common__components__Bones})

set(AI__AMonsters__common__components__Control_Manager
    "ai/monsters/control_com_defs.h"
    "ai/monsters/control_combase.h"
    "ai/monsters/control_manager.cpp"
    "ai/monsters/control_manager.h"
    "ai/monsters/control_manager_custom.cpp"
    "ai/monsters/control_manager_custom.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager" FILES ${AI__AMonsters__common__components__Control_Manager})

set(AI__AMonsters__common__components__Control_Manager__Base_Controllers__Animation
    "ai/monsters/control_animation_base.cpp"
    "ai/monsters/control_animation_base.h"
    "ai/monsters/control_animation_base_accel.cpp"
    "ai/monsters/control_animation_base_load.cpp"
    "ai/monsters/control_animation_base_update.cpp"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Base Controllers\\Animation" FILES ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Animation})

set(AI__AMonsters__common__components__Control_Manager__Base_Controllers__Direction
    "ai/monsters/control_direction_base.cpp"
    "ai/monsters/control_direction_base.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Base Controllers\\Direction" FILES ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Direction})

set(AI__AMonsters__common__components__Control_Manager__Base_Controllers__Movement
    "ai/monsters/control_movement_base.cpp"
    "ai/monsters/control_movement_base.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Base Controllers\\Movement" FILES ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Movement})

set(AI__AMonsters__common__components__Control_Manager__Base_Controllers__Path_Builder
    "ai/monsters/control_path_builder_base.cpp"
    "ai/monsters/control_path_builder_base.h"
    "ai/monsters/control_path_builder_base_inline.h"
    "ai/monsters/control_path_builder_base_path.cpp"
    "ai/monsters/control_path_builder_base_set.cpp"
    "ai/monsters/control_path_builder_base_update.cpp"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Base Controllers\\Path Builder" FILES ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Path_Builder})

set(AI__AMonsters__common__components__Control_Manager__Custom__CriticalWound
    "ai/monsters/control_critical_wound.cpp"
    "ai/monsters/control_critical_wound.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Custom\\CriticalWound" FILES ${AI__AMonsters__common__components__Control_Manager__Custom__CriticalWound})

set(AI__AMonsters__common__components__Control_Manager__Custom__Jump
    "ai/monsters/control_jump.cpp"
    "ai/monsters/control_jump.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Custom\\Jump" FILES ${AI__AMonsters__common__components__Control_Manager__Custom__Jump})

set(AI__AMonsters__common__components__Control_Manager__Custom__Rotation_Jump
    "ai/monsters/control_melee_jump.cpp"
    "ai/monsters/control_melee_jump.h"
    "ai/monsters/control_rotation_jump.cpp"
    "ai/monsters/control_rotation_jump.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Custom\\Rotation Jump" FILES ${AI__AMonsters__common__components__Control_Manager__Custom__Rotation_Jump})

set(AI__AMonsters__common__components__Control_Manager__Custom__Run_Attack
    "ai/monsters/control_run_attack.cpp"
    "ai/monsters/control_run_attack.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Custom\\Run Attack" FILES ${AI__AMonsters__common__components__Control_Manager__Custom__Run_Attack})

set(AI__AMonsters__common__components__Control_Manager__Custom__Sequencer
    "ai/monsters/control_sequencer.cpp"
    "ai/monsters/control_sequencer.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Custom\\Sequencer" FILES ${AI__AMonsters__common__components__Control_Manager__Custom__Sequencer})

set(AI__AMonsters__common__components__Control_Manager__Custom__Threaten
    "ai/monsters/control_threaten.cpp"
    "ai/monsters/control_threaten.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Custom\\Threaten" FILES ${AI__AMonsters__common__components__Control_Manager__Custom__Threaten})

set(AI__AMonsters__common__components__Control_Manager__Custom__Triple_Animation
    "ai/monsters/anim_triple.cpp"
    "ai/monsters/anim_triple.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Custom\\Triple Animation" FILES ${AI__AMonsters__common__components__Control_Manager__Custom__Triple_Animation})

set(AI__AMonsters__common__components__Control_Manager__Pure_Coms__Animation
    "ai/monsters/control_animation.cpp"
    "ai/monsters/control_animation.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Pure Coms\\Animation" FILES ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Animation})

set(AI__AMonsters__common__components__Control_Manager__Pure_Coms__Direction
    "ai/monsters/control_direction.cpp"
    "ai/monsters/control_direction.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Pure Coms\\Direction" FILES ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Direction})

set(AI__AMonsters__common__components__Control_Manager__Pure_Coms__Movement
    "ai/monsters/control_movement.cpp"
    "ai/monsters/control_movement.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Pure Coms\\Movement" FILES ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Movement})

set(AI__AMonsters__common__components__Control_Manager__Pure_Coms__Path_Builder
    "ai/monsters/control_path_builder.cpp"
    "ai/monsters/control_path_builder.h"
)
source_group("AI\\AMonsters\\common\\components\\Control Manager\\Pure Coms\\Path Builder" FILES ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Path_Builder})

set(AI__AMonsters__common__components__Cover
    "ai/monsters/corpse_cover.cpp"
    "ai/monsters/corpse_cover.h"
)
source_group("AI\\AMonsters\\common\\components\\Cover" FILES ${AI__AMonsters__common__components__Cover})

set(AI__AMonsters__common__components__Cover_Manager
    "ai/monsters/monster_cover_manager.cpp"
    "ai/monsters/monster_cover_manager.h"
)
source_group("AI\\AMonsters\\common\\components\\Cover Manager" FILES ${AI__AMonsters__common__components__Cover_Manager})

set(AI__AMonsters__common__components__Event_Handler
    "ai/monsters/monster_event_manager.cpp"
    "ai/monsters/monster_event_manager.h"
    "ai/monsters/monster_event_manager_defs.h"
)
source_group("AI\\AMonsters\\common\\components\\Event Handler" FILES ${AI__AMonsters__common__components__Event_Handler})

set(AI__AMonsters__common__components__Event_Handler__Custom_Events
    "ai/monsters/custom_events.h"
)
source_group("AI\\AMonsters\\common\\components\\Event Handler\\Custom Events" FILES ${AI__AMonsters__common__components__Event_Handler__Custom_Events})

set(AI__AMonsters__common__components__Home
    "ai/monsters/monster_home.cpp"
    "ai/monsters/monster_home.h"
)
source_group("AI\\AMonsters\\common\\components\\Home" FILES ${AI__AMonsters__common__components__Home})

set(AI__AMonsters__common__components__Melee_Checker
    "ai/monsters/melee_checker.cpp"
    "ai/monsters/melee_checker.h"
    "ai/monsters/melee_checker_inline.h"
)
source_group("AI\\AMonsters\\common\\components\\Melee Checker" FILES ${AI__AMonsters__common__components__Melee_Checker})

set(AI__AMonsters__common__components__Memory
    "ai/monsters/monster_corpse_memory.cpp"
    "ai/monsters/monster_corpse_memory.h"
    "ai/monsters/monster_enemy_memory.cpp"
    "ai/monsters/monster_enemy_memory.h"
    "ai/monsters/monster_hit_memory.cpp"
    "ai/monsters/monster_hit_memory.h"
    "ai/monsters/monster_sound_memory.cpp"
    "ai/monsters/monster_sound_memory.h"
)
source_group("AI\\AMonsters\\common\\components\\Memory" FILES ${AI__AMonsters__common__components__Memory})

set(AI__AMonsters__common__components__Morale
    "ai/monsters/monster_morale.cpp"
    "ai/monsters/monster_morale.h"
    "ai/monsters/monster_morale_inline.h"
)
source_group("AI\\AMonsters\\common\\components\\Morale" FILES ${AI__AMonsters__common__components__Morale})

set(AI__AMonsters__common__components__Motion_Stats
    "ai/monsters/ai_monster_motion_stats.cpp"
    "ai/monsters/ai_monster_motion_stats.h"
)
source_group("AI\\AMonsters\\common\\components\\Motion Stats" FILES ${AI__AMonsters__common__components__Motion_Stats})

set(AI__AMonsters__common__components__Squad
    "ai/monsters/ai_monster_squad.cpp"
    "ai/monsters/ai_monster_squad.h"
    "ai/monsters/ai_monster_squad_attack.cpp"
    "ai/monsters/ai_monster_squad_rest.cpp"
)
source_group("AI\\AMonsters\\common\\components\\Squad" FILES ${AI__AMonsters__common__components__Squad})

set(AI__AMonsters__common__components__Squad__Squad_Manager
    "ai/monsters/ai_monster_squad_manager.cpp"
    "ai/monsters/ai_monster_squad_manager.h"
    "ai/monsters/ai_monster_squad_manager_inline.h"
)
source_group("AI\\AMonsters\\common\\components\\Squad\\Squad Manager" FILES ${AI__AMonsters__common__components__Squad__Squad_Manager})

set(AI__AMonsters__common__components__State
    "ai/monsters/monster_state_manager.h"
    "ai/monsters/monster_state_manager_inline.h"
    "ai/monsters/state.h"
    "ai/monsters/state_defs.h"
    "ai/monsters/state_inline.h"
    "ai/monsters/state_manager.h"
)
source_group("AI\\AMonsters\\common\\components\\State" FILES ${AI__AMonsters__common__components__State})

set(AI__AMonsters__common__custom
    "CustomMonster.cpp"
    "CustomMonster.h"
    "CustomMonster_inline.h"
    "CustomMonster_VCPU.cpp"
)
source_group("AI\\AMonsters\\common\\custom" FILES ${AI__AMonsters__common__custom})

set(AI__AMonsters__common__miscellaneous
    "ai/ai_monsters_anims.h"
    "ai/ai_monsters_misc.cpp"
    "ai/ai_monsters_misc.h"
    "ai/position_prediction.h"
    "ai_monster_space.h"
)
source_group("AI\\AMonsters\\common\\miscellaneous" FILES ${AI__AMonsters__common__miscellaneous})

set(AI__AMonsters__common__script__monster_states__ALife
    "ai/monsters/states/monster_state_smart_terrain_task.h"
    "ai/monsters/states/monster_state_smart_terrain_task_graph_walk.h"
    "ai/monsters/states/monster_state_smart_terrain_task_graph_walk_inline.h"
    "ai/monsters/states/monster_state_smart_terrain_task_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\ALife" FILES ${AI__AMonsters__common__script__monster_states__ALife})

set(AI__AMonsters__common__script__monster_states__Attack
    "ai/monsters/states/monster_state_attack.h"
    "ai/monsters/states/monster_state_attack_inline.h"
    "ai/monsters/states/monster_state_attack_melee.h"
    "ai/monsters/states/monster_state_attack_melee_inline.h"
    "ai/monsters/states/monster_state_attack_on_run.h"
    "ai/monsters/states/monster_state_attack_on_run_inline.h"
    "ai/monsters/states/monster_state_attack_run.h"
    "ai/monsters/states/monster_state_attack_run_attack.h"
    "ai/monsters/states/monster_state_attack_run_attack_inline.h"
    "ai/monsters/states/monster_state_attack_run_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Attack" FILES ${AI__AMonsters__common__script__monster_states__Attack})

set(AI__AMonsters__common__script__monster_states__Camp
    "ai/monsters/states/monster_state_attack_camp.h"
    "ai/monsters/states/monster_state_attack_camp_inline.h"
    "ai/monsters/states/monster_state_attack_camp_stealout.h"
    "ai/monsters/states/monster_state_attack_camp_stealout_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Camp" FILES ${AI__AMonsters__common__script__monster_states__Camp})

set(AI__AMonsters__common__script__monster_states__Controlled
    "ai/monsters/states/monster_state_controlled.h"
    "ai/monsters/states/monster_state_controlled_attack.h"
    "ai/monsters/states/monster_state_controlled_attack_inline.h"
    "ai/monsters/states/monster_state_controlled_follow.h"
    "ai/monsters/states/monster_state_controlled_follow_inline.h"
    "ai/monsters/states/monster_state_controlled_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Controlled" FILES ${AI__AMonsters__common__script__monster_states__Controlled})

set(AI__AMonsters__common__script__monster_states__Dangerous_Sound
    "ai/monsters/states/monster_state_hear_danger_sound.h"
    "ai/monsters/states/monster_state_hear_danger_sound_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Dangerous Sound" FILES ${AI__AMonsters__common__script__monster_states__Dangerous_Sound})

set(AI__AMonsters__common__script__monster_states__Eat
    "ai/monsters/states/monster_state_eat.h"
    "ai/monsters/states/monster_state_eat_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Eat" FILES ${AI__AMonsters__common__script__monster_states__Eat})

set(AI__AMonsters__common__script__monster_states__Eat__Drag
    "ai/monsters/states/monster_state_eat_drag.h"
    "ai/monsters/states/monster_state_eat_drag_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Eat\\Drag" FILES ${AI__AMonsters__common__script__monster_states__Eat__Drag})

set(AI__AMonsters__common__script__monster_states__Eat__Eating
    "ai/monsters/states/monster_state_eat_eat.h"
    "ai/monsters/states/monster_state_eat_eat_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Eat\\Eating" FILES ${AI__AMonsters__common__script__monster_states__Eat__Eating})

set(AI__AMonsters__common__script__monster_states__Find_Enemy
    "ai/monsters/states/monster_state_find_enemy.h"
    "ai/monsters/states/monster_state_find_enemy_angry.h"
    "ai/monsters/states/monster_state_find_enemy_angry_inline.h"
    "ai/monsters/states/monster_state_find_enemy_inline.h"
    "ai/monsters/states/monster_state_find_enemy_look.h"
    "ai/monsters/states/monster_state_find_enemy_look_inline.h"
    "ai/monsters/states/monster_state_find_enemy_run.h"
    "ai/monsters/states/monster_state_find_enemy_run_inline.h"
    "ai/monsters/states/monster_state_find_enemy_walk.h"
    "ai/monsters/states/monster_state_find_enemy_walk_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Find Enemy" FILES ${AI__AMonsters__common__script__monster_states__Find_Enemy})

set(AI__AMonsters__common__script__monster_states__General
    "ai/monsters/states/state_data.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\General" FILES ${AI__AMonsters__common__script__monster_states__General})

set(AI__AMonsters__common__script__monster_states__General__Custom_Action
    "ai/monsters/states/state_custom_action.h"
    "ai/monsters/states/state_custom_action_inline.h"
    "ai/monsters/states/state_custom_action_look.h"
    "ai/monsters/states/state_custom_action_look_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\General\\Custom Action" FILES ${AI__AMonsters__common__script__monster_states__General__Custom_Action})

set(AI__AMonsters__common__script__monster_states__General__Look
    "ai/monsters/states/state_look_point.h"
    "ai/monsters/states/state_look_point_inline.h"
    "ai/monsters/states/state_look_unprotected_area.h"
    "ai/monsters/states/state_look_unprotected_area_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\General\\Look" FILES ${AI__AMonsters__common__script__monster_states__General__Look})

set(AI__AMonsters__common__script__monster_states__General__Movement
    "ai/monsters/states/state_hide_from_point.h"
    "ai/monsters/states/state_hide_from_point_inline.h"
    "ai/monsters/states/state_move_around_point.h"
    "ai/monsters/states/state_move_around_point_inline.h"
    "ai/monsters/states/state_move_to_point.h"
    "ai/monsters/states/state_move_to_point_inline.h"
    "ai/monsters/states/state_move_to_restrictor.h"
    "ai/monsters/states/state_move_to_restrictor_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\General\\Movement" FILES ${AI__AMonsters__common__script__monster_states__General__Movement})

set(AI__AMonsters__common__script__monster_states__General__Test
    "ai/monsters/states/state_hit_object.h"
    "ai/monsters/states/state_hit_object_inline.h"
    "ai/monsters/states/state_test_look_actor.h"
    "ai/monsters/states/state_test_look_actor_inline.h"
    "ai/monsters/states/state_test_state.h"
    "ai/monsters/states/state_test_state_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\General\\Test" FILES ${AI__AMonsters__common__script__monster_states__General__Test})

set(AI__AMonsters__common__script__monster_states__Group_Monsters_Home
    "ai/monsters/group_states/group_state_attack.h"
    "ai/monsters/group_states/group_state_attack_inline.h"
    "ai/monsters/group_states/group_state_attack_run.h"
    "ai/monsters/group_states/group_state_attack_run_inline.h"
    "ai/monsters/group_states/group_state_custom.h"
    "ai/monsters/group_states/group_state_custom_inline.h"
    "ai/monsters/group_states/group_state_eat.h"
    "ai/monsters/group_states/group_state_eat_drag.h"
    "ai/monsters/group_states/group_state_eat_drag_inline.h"
    "ai/monsters/group_states/group_state_eat_eat.h"
    "ai/monsters/group_states/group_state_eat_eat_inline.h"
    "ai/monsters/group_states/group_state_eat_inline.h"
    "ai/monsters/group_states/group_state_hear_danger_sound.h"
    "ai/monsters/group_states/group_state_hear_danger_sound_inline.h"
    "ai/monsters/group_states/group_state_home_point_attack.h"
    "ai/monsters/group_states/group_state_home_point_attack_inline.h"
    "ai/monsters/group_states/group_state_panic.h"
    "ai/monsters/group_states/group_state_panic_inline.h"
    "ai/monsters/group_states/group_state_panic_run.h"
    "ai/monsters/group_states/group_state_panic_run_inline.h"
    "ai/monsters/group_states/group_state_rest.h"
    "ai/monsters/group_states/group_state_rest_idle.h"
    "ai/monsters/group_states/group_state_rest_idle_inline.h"
    "ai/monsters/group_states/group_state_rest_inline.h"
    "ai/monsters/group_states/group_state_squad_move_to_radius.h"
    "ai/monsters/group_states/group_state_squad_move_to_radius_inline.h"
    "ai/monsters/group_states/state_adapter.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Group Monsters Home" FILES ${AI__AMonsters__common__script__monster_states__Group_Monsters_Home})

set(AI__AMonsters__common__script__monster_states__Help_Sound
    "ai/monsters/states/monster_state_help_sound.h"
    "ai/monsters/states/monster_state_help_sound_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Help Sound" FILES ${AI__AMonsters__common__script__monster_states__Help_Sound})

set(AI__AMonsters__common__script__monster_states__Hitted
    "ai/monsters/states/monster_state_hitted.h"
    "ai/monsters/states/monster_state_hitted_hide.h"
    "ai/monsters/states/monster_state_hitted_hide_inline.h"
    "ai/monsters/states/monster_state_hitted_inline.h"
    "ai/monsters/states/monster_state_hitted_moveout.h"
    "ai/monsters/states/monster_state_hitted_moveout_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Hitted" FILES ${AI__AMonsters__common__script__monster_states__Hitted})

set(AI__AMonsters__common__script__monster_states__Home_Point
    "ai/monsters/states/monster_state_home_point_attack.h"
    "ai/monsters/states/monster_state_home_point_attack_inline.h"
    "ai/monsters/states/monster_state_home_point_danger.h"
    "ai/monsters/states/monster_state_home_point_danger_inline.h"
    "ai/monsters/states/monster_state_home_point_rest.h"
    "ai/monsters/states/monster_state_home_point_rest_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Home Point" FILES ${AI__AMonsters__common__script__monster_states__Home_Point})

set(AI__AMonsters__common__script__monster_states__Interesting_Sound
    "ai/monsters/states/monster_state_hear_int_sound.h"
    "ai/monsters/states/monster_state_hear_int_sound_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Interesting Sound" FILES ${AI__AMonsters__common__script__monster_states__Interesting_Sound})

set(AI__AMonsters__common__script__monster_states__Panic
    "ai/monsters/states/monster_state_panic.h"
    "ai/monsters/states/monster_state_panic_inline.h"
    "ai/monsters/states/monster_state_panic_run.h"
    "ai/monsters/states/monster_state_panic_run_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Panic" FILES ${AI__AMonsters__common__script__monster_states__Panic})

set(AI__AMonsters__common__script__monster_states__Rest
    "ai/monsters/states/monster_state_rest.h"
    "ai/monsters/states/monster_state_rest_fun.h"
    "ai/monsters/states/monster_state_rest_fun_inline.h"
    "ai/monsters/states/monster_state_rest_idle.h"
    "ai/monsters/states/monster_state_rest_idle_inline.h"
    "ai/monsters/states/monster_state_rest_inline.h"
    "ai/monsters/states/monster_state_rest_sleep.h"
    "ai/monsters/states/monster_state_rest_sleep_inline.h"
    "ai/monsters/states/monster_state_rest_walk_graph.h"
    "ai/monsters/states/monster_state_rest_walk_graph_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Rest" FILES ${AI__AMonsters__common__script__monster_states__Rest})

set(AI__AMonsters__common__script__monster_states__Steal
    "ai/monsters/states/monster_state_steal.h"
    "ai/monsters/states/monster_state_steal_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Steal" FILES ${AI__AMonsters__common__script__monster_states__Steal})

set(AI__AMonsters__common__script__monster_states__Steal__Squad__Rest
    "ai/monsters/states/monster_state_squad_rest.h"
    "ai/monsters/states/monster_state_squad_rest_follow.h"
    "ai/monsters/states/monster_state_squad_rest_follow_inline.h"
    "ai/monsters/states/monster_state_squad_rest_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\monster states\\Steal\\Squad\\Rest" FILES ${AI__AMonsters__common__script__monster_states__Steal__Squad__Rest})

set(AI__AMonsters__common__script__script_binder
    "script_binder.cpp"
    "script_binder.h"
    "script_binder_inline.h"
)
source_group("AI\\AMonsters\\common\\script\\script_binder" FILES ${AI__AMonsters__common__script__script_binder})

set(AI__AMonsters__common__script__script_entity
    "script_entity.cpp"
    "script_entity.h"
    "script_entity_inline.h"
    "script_entity_space.h"
)
source_group("AI\\AMonsters\\common\\script\\script_entity" FILES ${AI__AMonsters__common__script__script_entity})

set(AI__AMonsters__common__script__script_object
    "script_object.cpp"
    "script_object.h"
)
source_group("AI\\AMonsters\\common\\script\\script_object" FILES ${AI__AMonsters__common__script__script_object})

set(AI__AMonsters__common__steering_behaviours
    "steering_behaviour.cpp"
    "steering_behaviour.h"
)
source_group("AI\\AMonsters\\common\\steering behaviours" FILES ${AI__AMonsters__common__steering_behaviours})

set(AI__AMonsters__common__steering_behaviours__base
    "steering_behaviour_base.h"
    "steering_behaviour_base_inline.h"
)
source_group("AI\\AMonsters\\common\\steering behaviours\\base" FILES ${AI__AMonsters__common__steering_behaviours__base})

set(AI__AMonsters__common__steering_behaviours__components__alignment
    "steering_behaviour_alignment.h"
)
source_group("AI\\AMonsters\\common\\steering behaviours\\components\\alignment" FILES ${AI__AMonsters__common__steering_behaviours__components__alignment})

set(AI__AMonsters__common__steering_behaviours__components__cohesion
    "steering_behaviour_cohesion.h"
)
source_group("AI\\AMonsters\\common\\steering behaviours\\components\\cohesion" FILES ${AI__AMonsters__common__steering_behaviours__components__cohesion})

set(AI__AMonsters__common__steering_behaviours__components__separation
    "steering_behaviour_separation.h"
)
source_group("AI\\AMonsters\\common\\steering behaviours\\components\\separation" FILES ${AI__AMonsters__common__steering_behaviours__components__separation})

set(AI__AMonsters__common__steering_behaviours__manager
    "steering_behaviour_manager.h"
)
source_group("AI\\AMonsters\\common\\steering behaviours\\manager" FILES ${AI__AMonsters__common__steering_behaviours__manager})

set(AI__AMonsters__common__trajectories
    "trajectories.cpp"
    "trajectories.h"
)
source_group("AI\\AMonsters\\common\\trajectories" FILES ${AI__AMonsters__common__trajectories})

set(AI__AMonsters__humans__stalker
    "ai/stalker/ai_stalker.cpp"
    "ai/stalker/ai_stalker.h"
    "ai/stalker/ai_stalker_impl.h"
    "ai/stalker/ai_stalker_inline.h"
    "ai/stalker/ai_stalker_script.cpp"
    "ai/stalker/ai_stalker_space.h"
)
source_group("AI\\AMonsters\\humans\\stalker" FILES ${AI__AMonsters__humans__stalker})

set(AI__AMonsters__humans__stalker__AnimationManager
    "stalker_animation_callbacks.cpp"
    "stalker_animation_global.cpp"
    "stalker_animation_head.cpp"
    "stalker_animation_legs.cpp"
    "stalker_animation_manager.cpp"
    "stalker_animation_manager.h"
    "stalker_animation_manager_debug.cpp"
    "stalker_animation_manager_impl.h"
    "stalker_animation_manager_inline.h"
    "stalker_animation_manager_update.cpp"
    "stalker_animation_script.cpp"
    "stalker_animation_torso.cpp"
)
source_group("AI\\AMonsters\\humans\\stalker\\AnimationManager" FILES ${AI__AMonsters__humans__stalker__AnimationManager})

set(AI__AMonsters__humans__stalker__AnimationManager__data_storage
    "stalker_animation_data_storage.cpp"
    "stalker_animation_data_storage.h"
    "stalker_animation_data_storage_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\AnimationManager\\data_storage" FILES ${AI__AMonsters__humans__stalker__AnimationManager__data_storage})

set(AI__AMonsters__humans__stalker__AnimationManager__data_storage__data
    "stalker_animation_data.cpp"
    "stalker_animation_data.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\AnimationManager\\data_storage\\data" FILES ${AI__AMonsters__humans__stalker__AnimationManager__data_storage__data})

set(AI__AMonsters__humans__stalker__AnimationManager__names
    "stalker_animation_names.cpp"
    "stalker_animation_names.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\AnimationManager\\names" FILES ${AI__AMonsters__humans__stalker__AnimationManager__names})

set(AI__AMonsters__humans__stalker__AnimationManager__pair
    "stalker_animation_pair.cpp"
    "stalker_animation_pair.h"
    "stalker_animation_pair_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\AnimationManager\\pair" FILES ${AI__AMonsters__humans__stalker__AnimationManager__pair})

set(AI__AMonsters__humans__stalker__AnimationManager__script
    "stalker_animation_script.h"
    "stalker_animation_script_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\AnimationManager\\script" FILES ${AI__AMonsters__humans__stalker__AnimationManager__script})

set(AI__AMonsters__humans__stalker__AnimationManager__state
    "stalker_animation_state.cpp"
    "stalker_animation_state.h"
    "stalker_animation_state_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\AnimationManager\\state" FILES ${AI__AMonsters__humans__stalker__AnimationManager__state})

set(AI__AMonsters__humans__stalker__CoverEvaluators
    "cover_evaluators.cpp"
    "cover_evaluators.h"
    "cover_evaluators_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\CoverEvaluators" FILES ${AI__AMonsters__humans__stalker__CoverEvaluators})

set(AI__AMonsters__humans__stalker__DecisionMaker
    "stalker_decision_space.h"
    "stalker_planner.cpp"
    "stalker_planner.h"
    "stalker_planner_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker" FILES ${AI__AMonsters__humans__stalker__DecisionMaker})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions
    "stalker_base_action.cpp"
    "stalker_base_action.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__alife
    "stalker_alife_planner.cpp"
    "stalker_alife_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\alife" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__alife})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__alife__actions
    "stalker_alife_actions.cpp"
    "stalker_alife_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\alife\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__alife__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__alife__task_actions
    "stalker_alife_task_actions.cpp"
    "stalker_alife_task_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\alife\\task_actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__alife__task_actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__anomaly
    "stalker_anomaly_planner.cpp"
    "stalker_anomaly_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\anomaly" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__anomaly})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__anomaly__actions
    "stalker_anomaly_actions.cpp"
    "stalker_anomaly_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\anomaly\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__anomaly__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat
    "stalker_combat_planner.cpp"
    "stalker_combat_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__actions
    "stalker_combat_actions.cpp"
    "stalker_combat_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__actions__base
    "stalker_combat_action_base.cpp"
    "stalker_combat_action_base.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\actions\\base" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__actions__base})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__get_distance
    "stalker_get_distance_planner.cpp"
    "stalker_get_distance_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\get_distance" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__get_distance})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__get_distance__actions
    "stalker_get_distance_actions.cpp"
    "stalker_get_distance_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\get_distance\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__get_distance__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__kill_wounded
    "stalker_kill_wounded_planner.cpp"
    "stalker_kill_wounded_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\kill_wounded" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__kill_wounded})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__kill_wounded__actions
    "stalker_kill_wounded_actions.cpp"
    "stalker_kill_wounded_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\kill_wounded\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__kill_wounded__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__low_cover_planner
    "stalker_low_cover_planner.cpp"
    "stalker_low_cover_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\low_cover_planner" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__low_cover_planner})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__low_cover_planner__actions
    "stalker_low_cover_actions.cpp"
    "stalker_low_cover_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\low_cover_planner\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__low_cover_planner__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__search_planner
    "stalker_search_planner.cpp"
    "stalker_search_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\search_planner" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__search_planner})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__search_planner__actions
    "stalker_search_actions.cpp"
    "stalker_search_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\combat\\search_planner\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__search_planner__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger
    "stalker_danger_planner.cpp"
    "stalker_danger_planner.h"
    "stalker_danger_planner_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__by_sound
    "stalker_danger_by_sound_planner.cpp"
    "stalker_danger_by_sound_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\by_sound" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__by_sound})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__by_sound__actions
    "stalker_danger_by_sound_actions.cpp"
    "stalker_danger_by_sound_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\by_sound\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__by_sound__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__grenade
    "stalker_danger_grenade_planner.cpp"
    "stalker_danger_grenade_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\grenade" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__grenade})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__grenade__actions
    "stalker_danger_grenade_actions.cpp"
    "stalker_danger_grenade_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\grenade\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__grenade__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__in_direction
    "stalker_danger_in_direction_planner.cpp"
    "stalker_danger_in_direction_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\in_direction" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__in_direction})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__in_direction__actions
    "stalker_danger_in_direction_actions.cpp"
    "stalker_danger_in_direction_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\in_direction\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__in_direction__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__unknown
    "stalker_danger_unknown_planner.cpp"
    "stalker_danger_unknown_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\unknown" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__unknown})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__unknown__actions
    "stalker_danger_unknown_actions.cpp"
    "stalker_danger_unknown_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\actions\\unknown\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__unknown__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__properties
    "stalker_danger_property_evaluators.cpp"
    "stalker_danger_property_evaluators.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\danger\\properties" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__properties})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__death
    "stalker_death_planner.cpp"
    "stalker_death_planner.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\death" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__death})

set(AI__AMonsters__humans__stalker__DecisionMaker__actions__death__actions
    "stalker_death_actions.cpp"
    "stalker_death_actions.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\actions\\death\\actions" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__actions__death__actions})

set(AI__AMonsters__humans__stalker__DecisionMaker__properties
    "stalker_property_evaluators.cpp"
    "stalker_property_evaluators.h"
    "stalker_property_evaluators_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\DecisionMaker\\properties" FILES ${AI__AMonsters__humans__stalker__DecisionMaker__properties})

set(AI__AMonsters__humans__stalker__Miscellaneous
    "ai/stalker/ai_stalker_cover.cpp"
    "ai/stalker/ai_stalker_debug.cpp"
    "ai/stalker/ai_stalker_events.cpp"
    "ai/stalker/ai_stalker_feel.cpp"
    "ai/stalker/ai_stalker_fire.cpp"
    "ai/stalker/ai_stalker_misc.cpp"
    "ai/stalker/ai_stalker_script_entity.cpp"
    "ai_stalker_alife.cpp"
)
source_group("AI\\AMonsters\\humans\\stalker\\Miscellaneous" FILES ${AI__AMonsters__humans__stalker__Miscellaneous})

set(AI__AMonsters__humans__stalker__MovementManager
    "stalker_movement_manager_space.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager" FILES ${AI__AMonsters__humans__stalker__MovementManager})

set(AI__AMonsters__humans__stalker__MovementManager__base
    "stalker_movement_manager_base.cpp"
    "stalker_movement_manager_base.h"
    "stalker_movement_manager_base_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\base" FILES ${AI__AMonsters__humans__stalker__MovementManager__base})

set(AI__AMonsters__humans__stalker__MovementManager__base__params
    "stalker_movement_params.cpp"
    "stalker_movement_params.h"
    "stalker_movement_params_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\base\\params" FILES ${AI__AMonsters__humans__stalker__MovementManager__base__params})

set(AI__AMonsters__humans__stalker__MovementManager__base__restriction
    "stalker_movement_restriction.h"
    "stalker_movement_restriction_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\base\\restriction" FILES ${AI__AMonsters__humans__stalker__MovementManager__base__restriction})

set(AI__AMonsters__humans__stalker__MovementManager__base__velocity_collection
    "stalker_velocity_collection.cpp"
    "stalker_velocity_collection.h"
    "stalker_velocity_collection_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\base\\velocity_collection" FILES ${AI__AMonsters__humans__stalker__MovementManager__base__velocity_collection})

set(AI__AMonsters__humans__stalker__MovementManager__base__velocity_holder
    "stalker_velocity_holder.cpp"
    "stalker_velocity_holder.h"
    "stalker_velocity_holder_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\base\\velocity_holder" FILES ${AI__AMonsters__humans__stalker__MovementManager__base__velocity_holder})

set(AI__AMonsters__humans__stalker__MovementManager__obstacles
    "stalker_movement_manager_obstacles.cpp"
    "stalker_movement_manager_obstacles.h"
    "stalker_movement_manager_obstacles_inline.h"
    "stalker_movement_manager_obstacles_path.cpp"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\obstacles" FILES ${AI__AMonsters__humans__stalker__MovementManager__obstacles})

set(AI__AMonsters__humans__stalker__MovementManager__obstacles__obstacle_avoiders__dynamic
    "dynamic_obstacles_avoider.cpp"
    "dynamic_obstacles_avoider.h"
    "dynamic_obstacles_avoider_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\obstacles\\obstacle_avoiders\\dynamic" FILES ${AI__AMonsters__humans__stalker__MovementManager__obstacles__obstacle_avoiders__dynamic})

set(AI__AMonsters__humans__stalker__MovementManager__obstacles__obstacle_avoiders__static
    "static_obstacles_avoider.cpp"
    "static_obstacles_avoider.h"
    "static_obstacles_avoider_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\obstacles\\obstacle_avoiders\\static" FILES ${AI__AMonsters__humans__stalker__MovementManager__obstacles__obstacle_avoiders__static})

set(AI__AMonsters__humans__stalker__MovementManager__obstacles__refreshable_obstacles_query
    "refreshable_obstacles_query.h"
    "refreshable_obstacles_query_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\obstacles\\refreshable_obstacles_query" FILES ${AI__AMonsters__humans__stalker__MovementManager__obstacles__refreshable_obstacles_query})

set(AI__AMonsters__humans__stalker__MovementManager__obstacles__restricted_object_obstacle
    "restricted_object_obstacle.cpp"
    "restricted_object_obstacle.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\obstacles\\restricted_object_obstacle" FILES ${AI__AMonsters__humans__stalker__MovementManager__obstacles__restricted_object_obstacle})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers
    "stalker_movement_manager_smart_cover.cpp"
    "stalker_movement_manager_smart_cover.h"
    "stalker_movement_manager_smart_cover_fov_range.cpp"
    "stalker_movement_manager_smart_cover_inline.h"
    "stalker_movement_manager_smart_cover_loopholes.cpp"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector
    "smart_cover_animation_selector.cpp"
    "smart_cover_animation_selector.h"
    "smart_cover_animation_selector_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\animation_selector" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner
    "smart_cover_animation_planner.cpp"
    "smart_cover_animation_planner.h"
    "smart_cover_animation_planner_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\animation_selector\\animation_planner" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__cover_actions
    "smart_cover_planner_actions.cpp"
    "smart_cover_planner_actions.h"
    "smart_cover_planner_actions_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\animation_selector\\animation_planner\\cover_actions" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__cover_actions})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__loophole_actions
    "smart_cover_loophole_planner_actions.cpp"
    "smart_cover_loophole_planner_actions.h"
    "smart_cover_loophole_planner_actions_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\animation_selector\\animation_planner\\loophole_actions" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__loophole_actions})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector
    "smart_cover_planner_target_selector.cpp"
    "smart_cover_planner_target_selector.h"
    "smart_cover_planner_target_selector_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\animation_selector\\animation_planner\\target_selector" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector__default_behaviour
    "smart_cover_default_behaviour_planner.cpp"
    "smart_cover_default_behaviour_planner.hpp"
    "smart_cover_default_behaviour_planner_inline.hpp"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\animation_selector\\animation_planner\\target_selector\\default_behaviour" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector__default_behaviour})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector__target_provider
    "smart_cover_planner_target_provider.cpp"
    "smart_cover_planner_target_provider.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\animation_selector\\animation_planner\\target_selector\\target_provider" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector__target_provider})

set(AI__AMonsters__humans__stalker__MovementManager__smart_covers__evaluators
    "smart_cover_evaluators.cpp"
    "smart_cover_evaluators.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\MovementManager\\smart_covers\\evaluators" FILES ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__evaluators})

set(AI__AMonsters__humans__stalker__SoundDataVisitor
    "stalker_sound_data_visitor.cpp"
    "stalker_sound_data_visitor.h"
    "stalker_sound_data_visitor_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\SoundDataVisitor" FILES ${AI__AMonsters__humans__stalker__SoundDataVisitor})

set(AI__AMonsters__humans__stalker__SoundUserData
    "stalker_sound_data.cpp"
    "stalker_sound_data.h"
    "stalker_sound_data_inline.h"
)
source_group("AI\\AMonsters\\humans\\stalker\\SoundUserData" FILES ${AI__AMonsters__humans__stalker__SoundUserData})

set(AI__AMonsters__humans__trader
    "ai/trader/ai_trader.cpp"
    "ai/trader/ai_trader.h"
    "ai/trader/ai_trader_script.cpp"
    "ai/trader/trader_animation.cpp"
    "ai/trader/trader_animation.h"
)
source_group("AI\\AMonsters\\humans\\trader" FILES ${AI__AMonsters__humans__trader})

set(AI__AMonsters__monsters__Bloodsucker
    "ai/monsters/bloodsucker/bloodsucker.cpp"
    "ai/monsters/bloodsucker/bloodsucker.h"
    "ai/monsters/bloodsucker/bloodsucker_state_manager.cpp"
    "ai/monsters/bloodsucker/bloodsucker_state_manager.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_effector.cpp"
    "ai/monsters/bloodsucker/bloodsucker_vampire_effector.h"
)
source_group("AI\\AMonsters\\monsters\\Bloodsucker" FILES ${AI__AMonsters__monsters__Bloodsucker})

set(AI__AMonsters__monsters__Bloodsucker__Alien_Feature
    "ai/monsters/bloodsucker/bloodsucker_alien.cpp"
    "ai/monsters/bloodsucker/bloodsucker_alien.h"
)
source_group("AI\\AMonsters\\monsters\\Bloodsucker\\Alien Feature" FILES ${AI__AMonsters__monsters__Bloodsucker__Alien_Feature})

set(AI__AMonsters__monsters__Bloodsucker__Attack
    "ai/monsters/bloodsucker/bloodsucker_attack_state.h"
    "ai/monsters/bloodsucker/bloodsucker_attack_state_hide.h"
    "ai/monsters/bloodsucker/bloodsucker_attack_state_hide_inline.h"
    "ai/monsters/bloodsucker/bloodsucker_attack_state_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Bloodsucker\\Attack" FILES ${AI__AMonsters__monsters__Bloodsucker__Attack})

set(AI__AMonsters__monsters__Bloodsucker__Capture_Jump
    "ai/monsters/bloodsucker/bloodsucker_state_capture_jump.h"
    "ai/monsters/bloodsucker/bloodsucker_state_capture_jump_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Bloodsucker\\Capture Jump" FILES ${AI__AMonsters__monsters__Bloodsucker__Capture_Jump})

set(AI__AMonsters__monsters__Bloodsucker__Predator_State
    "ai/monsters/bloodsucker/bloodsucker_predator.h"
    "ai/monsters/bloodsucker/bloodsucker_predator_inline.h"
    "ai/monsters/bloodsucker/bloodsucker_predator_lite.h"
    "ai/monsters/bloodsucker/bloodsucker_predator_lite_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Bloodsucker\\Predator State" FILES ${AI__AMonsters__monsters__Bloodsucker__Predator_State})

set(AI__AMonsters__monsters__Bloodsucker__Script
    "ai/monsters/bloodsucker/bloodsucker_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Bloodsucker\\Script" FILES ${AI__AMonsters__monsters__Bloodsucker__Script})

set(AI__AMonsters__monsters__Bloodsucker__Vampire_State
    "ai/monsters/bloodsucker/bloodsucker_vampire.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_approach.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_approach_inline.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_execute.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_execute_inline.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_hide.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_hide_inline.h"
    "ai/monsters/bloodsucker/bloodsucker_vampire_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Bloodsucker\\Vampire State" FILES ${AI__AMonsters__monsters__Bloodsucker__Vampire_State})

set(AI__AMonsters__monsters__Boar
    "ai/monsters/boar/boar.cpp"
    "ai/monsters/boar/boar.h"
    "ai/monsters/boar/boar_state_manager.cpp"
    "ai/monsters/boar/boar_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Boar" FILES ${AI__AMonsters__monsters__Boar})

set(AI__AMonsters__monsters__Boar__Script
    "ai/monsters/boar/boar_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Boar\\Script" FILES ${AI__AMonsters__monsters__Boar__Script})

set(AI__AMonsters__monsters__Burer
    "ai/monsters/burer/burer.cpp"
    "ai/monsters/burer/burer.h"
    "ai/monsters/burer/burer_state_manager.cpp"
    "ai/monsters/burer/burer_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Burer" FILES ${AI__AMonsters__monsters__Burer})

set(AI__AMonsters__monsters__Burer__Attack
    "ai/monsters/burer/burer_state_attack.h"
    "ai/monsters/burer/burer_state_attack_antiaim.h"
    "ai/monsters/burer/burer_state_attack_antiaim_inline.h"
    "ai/monsters/burer/burer_state_attack_gravi.h"
    "ai/monsters/burer/burer_state_attack_gravi_inline.h"
    "ai/monsters/burer/burer_state_attack_inline.h"
    "ai/monsters/burer/burer_state_attack_melee.h"
    "ai/monsters/burer/burer_state_attack_melee_inline.h"
    "ai/monsters/burer/burer_state_attack_run_around.h"
    "ai/monsters/burer/burer_state_attack_run_around_inline.h"
    "ai/monsters/burer/burer_state_attack_shield.h"
    "ai/monsters/burer/burer_state_attack_shield_inline.h"
    "ai/monsters/burer/burer_state_attack_tele.h"
    "ai/monsters/burer/burer_state_attack_tele_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Burer\\Attack" FILES ${AI__AMonsters__monsters__Burer__Attack})

set(AI__AMonsters__monsters__Burer__Fast_Gravi
    "ai/monsters/burer/burer_fast_gravi.cpp"
    "ai/monsters/burer/burer_fast_gravi.h"
)
source_group("AI\\AMonsters\\monsters\\Burer\\Fast Gravi" FILES ${AI__AMonsters__monsters__Burer__Fast_Gravi})

set(AI__AMonsters__monsters__Burer__Script
    "ai/monsters/burer/burer_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Burer\\Script" FILES ${AI__AMonsters__monsters__Burer__Script})

set(AI__AMonsters__monsters__Cat
    "ai/monsters/cat/cat.cpp"
    "ai/monsters/cat/cat.h"
    "ai/monsters/cat/cat_state_manager.cpp"
    "ai/monsters/cat/cat_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Cat" FILES ${AI__AMonsters__monsters__Cat})

set(AI__AMonsters__monsters__Cat__Script
    "ai/monsters/cat/cat_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Cat\\Script" FILES ${AI__AMonsters__monsters__Cat__Script})

set(AI__AMonsters__monsters__Chimera
    "ai/monsters/chimera/chimera.cpp"
    "ai/monsters/chimera/chimera.h"
    "ai/monsters/chimera/chimera_state_manager.cpp"
    "ai/monsters/chimera/chimera_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Chimera" FILES ${AI__AMonsters__monsters__Chimera})

set(AI__AMonsters__monsters__Chimera__Script
    "ai/monsters/chimera/chimera_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Chimera\\Script" FILES ${AI__AMonsters__monsters__Chimera__Script})

set(AI__AMonsters__monsters__Chimera__state_attack
    "ai/monsters/chimera/chimera_attack_state.h"
    "ai/monsters/chimera/chimera_attack_state_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Chimera\\state attack" FILES ${AI__AMonsters__monsters__Chimera__state_attack})

set(AI__AMonsters__monsters__Chimera__state_hunting
    "ai/monsters/chimera/chimera_state_hunting.h"
    "ai/monsters/chimera/chimera_state_hunting_come_out.h"
    "ai/monsters/chimera/chimera_state_hunting_come_out_inline.h"
    "ai/monsters/chimera/chimera_state_hunting_inline.h"
    "ai/monsters/chimera/chimera_state_hunting_move_to_cover.h"
    "ai/monsters/chimera/chimera_state_hunting_move_to_cover_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Chimera\\state hunting" FILES ${AI__AMonsters__monsters__Chimera__state_hunting})

set(AI__AMonsters__monsters__Chimera__state_threaten
    "ai/monsters/chimera/chimera_state_threaten.h"
    "ai/monsters/chimera/chimera_state_threaten_inline.h"
    "ai/monsters/chimera/chimera_state_threaten_roar.h"
    "ai/monsters/chimera/chimera_state_threaten_roar_inline.h"
    "ai/monsters/chimera/chimera_state_threaten_steal.h"
    "ai/monsters/chimera/chimera_state_threaten_steal_inline.h"
    "ai/monsters/chimera/chimera_state_threaten_walk.h"
    "ai/monsters/chimera/chimera_state_threaten_walk_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Chimera\\state threaten" FILES ${AI__AMonsters__monsters__Chimera__state_threaten})

set(AI__AMonsters__monsters__Controller
    "ai/monsters/controller/controller.cpp"
    "ai/monsters/controller/controller.h"
    "ai/monsters/controller/controller_state_manager.cpp"
    "ai/monsters/controller/controller_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Controller" FILES ${AI__AMonsters__monsters__Controller})

set(AI__AMonsters__monsters__Controller__Base_Controllers__Animation
    "ai/monsters/controller/controller_animation.cpp"
    "ai/monsters/controller/controller_animation.h"
)
source_group("AI\\AMonsters\\monsters\\Controller\\Base Controllers\\Animation" FILES ${AI__AMonsters__monsters__Controller__Base_Controllers__Animation})

set(AI__AMonsters__monsters__Controller__Base_Controllers__Direction
    "ai/monsters/controller/controller_direction.cpp"
    "ai/monsters/controller/controller_direction.h"
)
source_group("AI\\AMonsters\\monsters\\Controller\\Base Controllers\\Direction" FILES ${AI__AMonsters__monsters__Controller__Base_Controllers__Direction})

set(AI__AMonsters__monsters__Controller__Psy_hit
    "ai/monsters/controller/controller_psy_hit.cpp"
    "ai/monsters/controller/controller_psy_hit.h"
    "ai/monsters/controller/controller_psy_hit_effector.cpp"
    "ai/monsters/controller/controller_psy_hit_effector.h"
)
source_group("AI\\AMonsters\\monsters\\Controller\\Psy hit" FILES ${AI__AMonsters__monsters__Controller__Psy_hit})

set(AI__AMonsters__monsters__Controller__Script
    "ai/monsters/controller/controller_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Controller\\Script" FILES ${AI__AMonsters__monsters__Controller__Script})

set(AI__AMonsters__monsters__Controller__State_Attack
    "ai/monsters/controller/controller_state_attack.h"
    "ai/monsters/controller/controller_state_attack_fast_move.h"
    "ai/monsters/controller/controller_state_attack_fast_move_inline.h"
    "ai/monsters/controller/controller_state_attack_inline.h"
    "ai/monsters/controller/controller_state_control_hit.h"
    "ai/monsters/controller/controller_state_control_hit_inline.h"
    "ai/monsters/controller/controller_tube.h"
    "ai/monsters/controller/controller_tube_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Controller\\State Attack" FILES ${AI__AMonsters__monsters__Controller__State_Attack})

set(AI__AMonsters__monsters__Controller__State_Attack__Cover
    "ai/monsters/controller/controller_state_attack_camp.h"
    "ai/monsters/controller/controller_state_attack_camp_inline.h"
    "ai/monsters/controller/controller_state_attack_fire.h"
    "ai/monsters/controller/controller_state_attack_fire_inline.h"
    "ai/monsters/controller/controller_state_attack_hide.h"
    "ai/monsters/controller/controller_state_attack_hide_inline.h"
    "ai/monsters/controller/controller_state_attack_hide_lite.h"
    "ai/monsters/controller/controller_state_attack_hide_lite_inline.h"
    "ai/monsters/controller/controller_state_attack_moveout.h"
    "ai/monsters/controller/controller_state_attack_moveout_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Controller\\State Attack\\Cover" FILES ${AI__AMonsters__monsters__Controller__State_Attack__Cover})

set(AI__AMonsters__monsters__Controller__State_Panic
    "ai/monsters/controller/controller_state_panic.h"
    "controller_state_panic_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Controller\\State Panic" FILES ${AI__AMonsters__monsters__Controller__State_Panic})

set(AI__AMonsters__monsters__Crow
    "ai/crow/ai_crow.cpp"
    "ai/crow/ai_crow.h"
    "ai_crow_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Crow" FILES ${AI__AMonsters__monsters__Crow})

set(AI__AMonsters__monsters__Dog
    "ai/monsters/dog/dog.cpp"
    "ai/monsters/dog/dog.h"
    "ai/monsters/dog/dog_state_manager.cpp"
    "ai/monsters/dog/dog_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Dog" FILES ${AI__AMonsters__monsters__Dog})

set(AI__AMonsters__monsters__DogPsy
    "ai/monsters/pseudodog/psy_dog.cpp"
    "ai/monsters/pseudodog/psy_dog.h"
    "ai/monsters/pseudodog/psy_dog_aura.cpp"
    "ai/monsters/pseudodog/psy_dog_aura.h"
    "ai/monsters/pseudodog/psy_dog_state_manager.cpp"
    "ai/monsters/pseudodog/psy_dog_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\DogPsy" FILES ${AI__AMonsters__monsters__DogPsy})

set(AI__AMonsters__monsters__DogPsy__Psy_Attack_Hide
    "ai/monsters/pseudodog/psy_dog_state_psy_attack.h"
    "ai/monsters/pseudodog/psy_dog_state_psy_attack_hide.h"
    "ai/monsters/pseudodog/psy_dog_state_psy_attack_hide_inline.h"
    "ai/monsters/pseudodog/psy_dog_state_psy_attack_inline.h"
)
source_group("AI\\AMonsters\\monsters\\DogPsy\\Psy Attack Hide" FILES ${AI__AMonsters__monsters__DogPsy__Psy_Attack_Hide})

set(AI__AMonsters__monsters__Dog__Script
    "ai/monsters/dog/dog_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Dog\\Script" FILES ${AI__AMonsters__monsters__Dog__Script})

set(AI__AMonsters__monsters__Flesh
    "ai/monsters/flesh/flesh.cpp"
    "ai/monsters/flesh/flesh.h"
    "ai/monsters/flesh/flesh_state_manager.cpp"
    "ai/monsters/flesh/flesh_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Flesh" FILES ${AI__AMonsters__monsters__Flesh})

set(AI__AMonsters__monsters__Flesh__Script
    "ai/monsters/flesh/flesh_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Flesh\\Script" FILES ${AI__AMonsters__monsters__Flesh__Script})

set(AI__AMonsters__monsters__Fracture
    "ai/monsters/fracture/fracture.cpp"
    "ai/monsters/fracture/fracture.h"
    "ai/monsters/fracture/fracture_state_manager.cpp"
    "ai/monsters/fracture/fracture_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Fracture" FILES ${AI__AMonsters__monsters__Fracture})

set(AI__AMonsters__monsters__Fracture__Script
    "ai/monsters/fracture/fracture_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Fracture\\Script" FILES ${AI__AMonsters__monsters__Fracture__Script})

set(AI__AMonsters__monsters__Phantom
    "ai/phantom/phantom.cpp"
    "ai/phantom/phantom.h"
)
source_group("AI\\AMonsters\\monsters\\Phantom" FILES ${AI__AMonsters__monsters__Phantom})

set(AI__AMonsters__monsters__Poltergeist
    "ai/monsters/poltergeist/poltergeist.cpp"
    "ai/monsters/poltergeist/poltergeist.h"
    "ai/monsters/poltergeist/poltergeist_movement.cpp"
    "ai/monsters/poltergeist/poltergeist_movement.h"
    "ai/monsters/poltergeist/poltergeist_state_manager.cpp"
    "ai/monsters/poltergeist/poltergeist_state_manager.h"
    "ai/monsters/poltergeist/poltergeist_state_rest.h"
)
source_group("AI\\AMonsters\\monsters\\Poltergeist" FILES ${AI__AMonsters__monsters__Poltergeist})

set(AI__AMonsters__monsters__Poltergeist__Abilities
    "ai/monsters/poltergeist/poltergeist_ability.cpp"
    "ai/monsters/poltergeist/poltergeist_flame_thrower.cpp"
    "ai/monsters/poltergeist/poltergeist_telekinesis.cpp"
)
source_group("AI\\AMonsters\\monsters\\Poltergeist\\Abilities" FILES ${AI__AMonsters__monsters__Poltergeist__Abilities})

set(AI__AMonsters__monsters__Poltergeist__Hidden_Attack
    "ai/monsters/poltergeist/poltergeist_state_attack_hidden.h"
    "ai/monsters/poltergeist/poltergeist_state_attack_hidden_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Poltergeist\\Hidden Attack" FILES ${AI__AMonsters__monsters__Poltergeist__Hidden_Attack})

set(AI__AMonsters__monsters__Poltergeist__Script
    "ai/monsters/poltergeist/poltergeist_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Poltergeist\\Script" FILES ${AI__AMonsters__monsters__Poltergeist__Script})

set(AI__AMonsters__monsters__PseudoDog
    "ai/monsters/pseudodog/pseudodog.cpp"
    "ai/monsters/pseudodog/pseudodog.h"
    "ai/monsters/pseudodog/pseudodog_psi_effector.cpp"
    "ai/monsters/pseudodog/pseudodog_psi_effector.h"
    "ai/monsters/pseudodog/pseudodog_state_manager.cpp"
    "ai/monsters/pseudodog/pseudodog_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\PseudoDog" FILES ${AI__AMonsters__monsters__PseudoDog})

set(AI__AMonsters__monsters__PseudoDog__Script
    "ai/monsters/pseudodog/pseudodog_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\PseudoDog\\Script" FILES ${AI__AMonsters__monsters__PseudoDog__Script})

set(AI__AMonsters__monsters__PseudoGigant
    "ai/monsters/pseudogigant/pseudo_gigant.cpp"
    "ai/monsters/pseudogigant/pseudo_gigant.h"
    "ai/monsters/pseudogigant/pseudo_gigant_step_effector.cpp"
    "ai/monsters/pseudogigant/pseudo_gigant_step_effector.h"
    "ai/monsters/pseudogigant/pseudogigant_state_manager.cpp"
    "ai/monsters/pseudogigant/pseudogigant_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\PseudoGigant" FILES ${AI__AMonsters__monsters__PseudoGigant})

set(AI__AMonsters__monsters__PseudoGigant__Script
    "ai/monsters/pseudogigant/pseudogigant_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\PseudoGigant\\Script" FILES ${AI__AMonsters__monsters__PseudoGigant__Script})

set(AI__AMonsters__monsters__Rats
    "ai/monsters/rats/ai_rat.cpp"
    "ai/monsters/rats/ai_rat.h"
    "ai/monsters/rats/ai_rat_animations.cpp"
    "ai/monsters/rats/ai_rat_behaviour.cpp"
    "ai/monsters/rats/ai_rat_feel.cpp"
    "ai/monsters/rats/ai_rat_fire.cpp"
    "ai/monsters/rats/ai_rat_impl.h"
    "ai/monsters/rats/ai_rat_inline.h"
    "ai/monsters/rats/ai_rat_space.h"
    "ai/monsters/rats/ai_rat_templates.cpp"
)
source_group("AI\\AMonsters\\monsters\\Rats" FILES ${AI__AMonsters__monsters__Rats})

set(AI__AMonsters__monsters__Rats__state_manager
    "rat_state_manager.cpp"
    "rat_state_manager.h"
    "rat_state_manager_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Rats\\state_manager" FILES ${AI__AMonsters__monsters__Rats__state_manager})

set(AI__AMonsters__monsters__Rats__states
    "ai/monsters/rats/rat_state_activation.cpp"
    "ai/monsters/rats/rat_state_initialize.cpp"
    "ai/monsters/rats/rat_state_switch.cpp"
    "rat_states.cpp"
    "rat_states.h"
)
source_group("AI\\AMonsters\\monsters\\Rats\\states" FILES ${AI__AMonsters__monsters__Rats__states})

set(AI__AMonsters__monsters__Rats__states__base
    "rat_state_base.cpp"
    "rat_state_base.h"
    "rat_state_base_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Rats\\states\\base" FILES ${AI__AMonsters__monsters__Rats__states__base})

set(AI__AMonsters__monsters__Snork
    "ai/monsters/snork/snork.cpp"
    "ai/monsters/snork/snork.h"
    "ai/monsters/snork/snork_state_manager.cpp"
    "ai/monsters/snork/snork_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Snork" FILES ${AI__AMonsters__monsters__Snork})

set(AI__AMonsters__monsters__Snork__Script
    "ai/monsters/snork/snork_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Snork\\Script" FILES ${AI__AMonsters__monsters__Snork__Script})

set(AI__AMonsters__monsters__Snork__Special_Jump
    "ai/monsters/snork/snork_jump.cpp"
    "ai/monsters/snork/snork_jump.h"
)
source_group("AI\\AMonsters\\monsters\\Snork\\Special Jump" FILES ${AI__AMonsters__monsters__Snork__Special_Jump})

set(AI__AMonsters__monsters__Tushkano
    "ai/monsters/tushkano/tushkano.cpp"
    "ai/monsters/tushkano/tushkano.h"
    "ai/monsters/tushkano/tushkano_state_manager.cpp"
    "ai/monsters/tushkano/tushkano_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Tushkano" FILES ${AI__AMonsters__monsters__Tushkano})

set(AI__AMonsters__monsters__Tushkano__Script
    "ai/monsters/tushkano/tushkano_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Tushkano\\Script" FILES ${AI__AMonsters__monsters__Tushkano__Script})

set(AI__AMonsters__monsters__Zombie
    "ai/monsters/zombie/zombie.cpp"
    "ai/monsters/zombie/zombie.h"
    "ai/monsters/zombie/zombie_state_manager.cpp"
    "ai/monsters/zombie/zombie_state_manager.h"
)
source_group("AI\\AMonsters\\monsters\\Zombie" FILES ${AI__AMonsters__monsters__Zombie})

set(AI__AMonsters__monsters__Zombie__Script
    "ai/monsters/zombie/zombie_script.cpp"
)
source_group("AI\\AMonsters\\monsters\\Zombie\\Script" FILES ${AI__AMonsters__monsters__Zombie__Script})

set(AI__AMonsters__monsters__Zombie__States
    "ai/monsters/zombie/zombie_state_attack_run.h"
    "ai/monsters/zombie/zombie_state_attack_run_inline.h"
)
source_group("AI\\AMonsters\\monsters\\Zombie\\States" FILES ${AI__AMonsters__monsters__Zombie__States})

set(AI__ANavigation__GameGraph
    "../xrServerEntities/game_graph_space.h"
    "game_graph.h"
    "game_graph_inline.h"
    "game_graph_script.cpp"
)
source_group("AI\\ANavigation\\GameGraph" FILES ${AI__ANavigation__GameGraph})

set(AI__ANavigation__GameLevelCrossTable
    "game_level_cross_table.h"
    "game_level_cross_table_inline.h"
)
source_group("AI\\ANavigation\\GameLevelCrossTable" FILES ${AI__ANavigation__GameLevelCrossTable})

set(AI__ANavigation__GraphAbstract__GraphEdge
    "graph_edge.h"
    "graph_edge_inline.h"
)
source_group("AI\\ANavigation\\GraphAbstract\\GraphEdge" FILES ${AI__ANavigation__GraphAbstract__GraphEdge})

set(AI__ANavigation__GraphAbstract__GraphVertex
    "graph_vertex.h"
    "graph_vertex_inline.h"
)
source_group("AI\\ANavigation\\GraphAbstract\\GraphVertex" FILES ${AI__ANavigation__GraphAbstract__GraphVertex})

set(AI__ANavigation__LevelGraph
    "level_graph.cpp"
    "level_graph.h"
    "level_graph_debug.cpp"
    "level_graph_debug2.cpp"
    "level_graph_inline.h"
    "level_graph_space.h"
    "level_graph_vertex.cpp"
    "level_graph_vertex_inline.h"
)
source_group("AI\\ANavigation\\LevelGraph" FILES ${AI__ANavigation__LevelGraph})

set(AI__ANavigation__ObjectLocation
    "ai_object_location.h"
    "ai_object_location_impl.h"
    "ai_object_location_inline.h"
)
source_group("AI\\ANavigation\\ObjectLocation" FILES ${AI__ANavigation__ObjectLocation})

set(AI__ANavigation__Pathfinding__Algorithms__A2a
    "a_star.h"
    "a_star_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\Algorithms\\A%2a" FILES ${AI__ANavigation__Pathfinding__Algorithms__A2a})

set(AI__ANavigation__Pathfinding__Algorithms__Dijkstra
    "dijkstra.h"
    "dijkstra_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\Algorithms\\Dijkstra" FILES ${AI__ANavigation__Pathfinding__Algorithms__Dijkstra})

set(AI__ANavigation__Pathfinding__DataStorages__constructors
    "data_storage_constructor.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\constructors" FILES ${AI__ANavigation__Pathfinding__DataStorages__constructors})

set(AI__ANavigation__Pathfinding__DataStorages__constructors__builder_allocator
    "builder_allocator_constructor.h"
    "builder_allocator_constructor_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\constructors\\builder_allocator" FILES ${AI__ANavigation__Pathfinding__DataStorages__constructors__builder_allocator})

set(AI__ANavigation__Pathfinding__DataStorages__constructors__manager_builder_allocator
    "manager_builder_allocator_constructor.h"
    "manager_builder_allocator_constructor_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\constructors\\manager_builder_allocator" FILES ${AI__ANavigation__Pathfinding__DataStorages__constructors__manager_builder_allocator})

set(AI__ANavigation__Pathfinding__DataStorages__path_builders__edge_path
    "edge_path.h"
    "edge_path_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\path_builders\\edge_path" FILES ${AI__ANavigation__Pathfinding__DataStorages__path_builders__edge_path})

set(AI__ANavigation__Pathfinding__DataStorages__path_builders__vertex_path
    "vertex_path.h"
    "vertex_path_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\path_builders\\vertex_path" FILES ${AI__ANavigation__Pathfinding__DataStorages__path_builders__vertex_path})

set(AI__ANavigation__Pathfinding__DataStorages__priority_queues
    "data_storage_double_linked_list.h"
    "data_storage_double_linked_list_inline.h"
    "data_storage_single_linked_list.h"
    "data_storage_single_linked_list_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\priority_queues" FILES ${AI__ANavigation__Pathfinding__DataStorages__priority_queues})

set(AI__ANavigation__Pathfinding__DataStorages__priority_queues__binary_heap
    "data_storage_binary_heap.h"
    "data_storage_binary_heap_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\priority_queues\\binary_heap" FILES ${AI__ANavigation__Pathfinding__DataStorages__priority_queues__binary_heap})

set(AI__ANavigation__Pathfinding__DataStorages__priority_queues__bucket_list
    "data_storage_bucket_list.h"
    "data_storage_bucket_list_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\priority_queues\\bucket_list" FILES ${AI__ANavigation__Pathfinding__DataStorages__priority_queues__bucket_list})

set(AI__ANavigation__Pathfinding__DataStorages__vertex_allocators__fixed
    "vertex_allocator_fixed.h"
    "vertex_allocator_fixed_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\vertex_allocators\\fixed" FILES ${AI__ANavigation__Pathfinding__DataStorages__vertex_allocators__fixed})

set(AI__ANavigation__Pathfinding__DataStorages__vertex_managers__fixed
    "vertex_manager_fixed.h"
    "vertex_manager_fixed_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\vertex_managers\\fixed" FILES ${AI__ANavigation__Pathfinding__DataStorages__vertex_managers__fixed})

set(AI__ANavigation__Pathfinding__DataStorages__vertex_managers__hash_fixed
    "vertex_manager_hash_fixed.h"
    "vertex_manager_hash_fixed_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\DataStorages\\vertex_managers\\hash_fixed" FILES ${AI__ANavigation__Pathfinding__DataStorages__vertex_managers__hash_fixed})

set(AI__ANavigation__Pathfinding__GraphEngine
    "graph_engine.h"
    "graph_engine_inline.h"
    "graph_engine_space.h"
    "hash_fixed_vertex_manager.hpp"
)
source_group("AI\\ANavigation\\Pathfinding\\GraphEngine" FILES ${AI__ANavigation__Pathfinding__GraphEngine})

set(AI__ANavigation__Pathfinding__PathManagers
    "path_manager.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers" FILES ${AI__ANavigation__Pathfinding__PathManagers})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_game
    "path_manager_game.h"
    "path_manager_game_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_game" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_game})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_game__level
    "path_manager_game_level.h"
    "path_manager_game_level_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_game\\level" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_game__level})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_game__vertex
    "path_manager_game_vertex.h"
    "path_manager_game_vertex_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_game\\vertex" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_game__vertex})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_generic
    "path_manager_generic.h"
    "path_manager_generic_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_generic" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_generic})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_level
    "path_manager_level.h"
    "path_manager_level_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_level" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_level__flooder
    "path_manager_level_flooder.h"
    "path_manager_level_flooder_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_level\\flooder" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level__flooder})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_level__nearest_vertex
    "path_manager_level_nearest_vertex.h"
    "path_manager_level_nearest_vertex_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_level\\nearest_vertex" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level__nearest_vertex})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_level__straight_line
    "path_manager_level_straight_line.h"
    "path_manager_level_straight_line_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_level\\straight_line" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level__straight_line})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_params
    "path_manager_params.h"
    "path_manager_params_flooder.h"
    "path_manager_params_game_level.h"
    "path_manager_params_game_vertex.h"
    "path_manager_params_nearest_vertex.h"
    "path_manager_params_straight_line.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_params" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_params})

set(AI__ANavigation__Pathfinding__PathManagers__path_manager_solver
    "path_manager_solver.h"
    "path_manager_solver_inline.h"
)
source_group("AI\\ANavigation\\Pathfinding\\PathManagers\\path_manager_solver" FILES ${AI__ANavigation__Pathfinding__PathManagers__path_manager_solver})

set(AI__ANavigation__PatrolPaths__PatrolPath
    "patrol_path.cpp"
    "patrol_path.h"
    "patrol_path_inline.h"
)
source_group("AI\\ANavigation\\PatrolPaths\\PatrolPath" FILES ${AI__ANavigation__PatrolPaths__PatrolPath})

set(AI__ANavigation__PatrolPaths__PatrolPathStorage
    "patrol_path_storage.cpp"
    "patrol_path_storage.h"
    "patrol_path_storage_inline.h"
)
source_group("AI\\ANavigation\\PatrolPaths\\PatrolPathStorage" FILES ${AI__ANavigation__PatrolPaths__PatrolPathStorage})

set(AI__ANavigation__PatrolPaths__PatrolPoint
    "patrol_point.cpp"
    "patrol_point.h"
    "patrol_point_inline.h"
)
source_group("AI\\ANavigation\\PatrolPaths\\PatrolPoint" FILES ${AI__ANavigation__PatrolPaths__PatrolPoint})

set(AI__AScript
    "../xrServerEntities/script_export_macroses.h"
    "../xrServerEntities/script_export_space.h"
    "../xrServerEntities/script_space_forward.h"
)
source_group("AI\\AScript" FILES ${AI__AScript})

set(AI__AScript__ScriptClasses
    "script_bind_macroses.h"
)
source_group("AI\\AScript\\ScriptClasses" FILES ${AI__AScript__ScriptClasses})

set(AI__AScript__ScriptClasses__BaseClientClasses
    "base_client_classes.h"
    "base_client_classes_script.cpp"
    "base_client_classes_wrappers.h"
)
source_group("AI\\AScript\\ScriptClasses\\BaseClientClasses" FILES ${AI__AScript__ScriptClasses__BaseClientClasses})

set(AI__AScript__ScriptClasses__Console
    "console_registrator.h"
    "console_registrator_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\Console" FILES ${AI__AScript__ScriptClasses__Console})

set(AI__AScript__ScriptClasses__KeyBindings
    "key_binding_registrator.h"
    "key_binding_registrator_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\KeyBindings" FILES ${AI__AScript__ScriptClasses__KeyBindings})

set(AI__AScript__ScriptClasses__ScriptActions__acript_animation_action
    "script_animation_action.cpp"
    "script_animation_action.h"
    "script_animation_action_inline.h"
    "script_animation_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\acript_animation_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__acript_animation_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_abstract_action
    "script_abstract_action.cpp"
    "script_abstract_action.h"
    "script_abstract_action_inline.h"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_abstract_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_abstract_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_action_condition
    "script_action_condition.cpp"
    "script_action_condition.h"
    "script_action_condition_inline.h"
    "script_action_condition_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_action_condition" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_action_condition})

set(AI__AScript__ScriptClasses__ScriptActions__script_entity_action
    "script_entity_action.cpp"
    "script_entity_action.h"
    "script_entity_action_inline.h"
    "script_entity_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_entity_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_entity_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_monster_action
    "script_monster_action.cpp"
    "script_monster_action.h"
    "script_monster_action_inline.h"
    "script_monster_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_monster_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_monster_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_movement_action
    "script_movement_action.cpp"
    "script_movement_action.h"
    "script_movement_action_inline.h"
    "script_movement_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_movement_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_movement_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_movement_action__patrol_path_params
    "patrol_path_params.cpp"
    "patrol_path_params.h"
    "patrol_path_params_inline.h"
    "patrol_path_params_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_movement_action\\patrol_path_params" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_movement_action__patrol_path_params})

set(AI__AScript__ScriptClasses__ScriptActions__script_object_action
    "script_object_action.cpp"
    "script_object_action.h"
    "script_object_action_inline.h"
    "script_object_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_object_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_object_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_particle_action
    "script_particle_action.cpp"
    "script_particle_action.h"
    "script_particle_action_inline.h"
    "script_particle_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_particle_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_particle_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_particle_action__particle_params
    "particle_params.cpp"
    "particle_params.h"
    "particle_params_inline.h"
    "particle_params_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_particle_action\\particle_params" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_particle_action__particle_params})

set(AI__AScript__ScriptClasses__ScriptActions__script_sound_action
    "script_sound_action.cpp"
    "script_sound_action.h"
    "script_sound_action_inline.h"
    "script_sound_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_sound_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_sound_action})

set(AI__AScript__ScriptClasses__ScriptActions__script_watch_action
    "script_watch_action.cpp"
    "script_watch_action.h"
    "script_watch_action_inline.h"
    "script_watch_action_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptActions\\script_watch_action" FILES ${AI__AScript__ScriptClasses__ScriptActions__script_watch_action})

set(AI__AScript__ScriptClasses__ScriptBinderObject
    "script_binder_object.cpp"
    "script_binder_object.h"
    "script_binder_object_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptBinderObject" FILES ${AI__AScript__ScriptClasses__ScriptBinderObject})

set(AI__AScript__ScriptClasses__ScriptBinderObject__ScriptBinderObjectWrapper
    "script_binder_object_wrapper.cpp"
    "script_binder_object_wrapper.h"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptBinderObject\\ScriptBinderObjectWrapper" FILES ${AI__AScript__ScriptClasses__ScriptBinderObject__ScriptBinderObjectWrapper})

set(AI__AScript__ScriptClasses__ScriptCallbackEx
    "script_callback_ex.h"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptCallbackEx" FILES ${AI__AScript__ScriptClasses__ScriptCallbackEx})

set(AI__AScript__ScriptClasses__ScriptEffector
    "script_effector.cpp"
    "script_effector.h"
    "script_effector_inline.h"
    "script_effector_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptEffector" FILES ${AI__AScript__ScriptClasses__ScriptEffector})

set(AI__AScript__ScriptClasses__ScriptEffector__ScriptEffectorWrapper
    "script_effector_wrapper.cpp"
    "script_effector_wrapper.h"
    "script_effector_wrapper_inline.h"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptEffector\\ScriptEffectorWrapper" FILES ${AI__AScript__ScriptClasses__ScriptEffector__ScriptEffectorWrapper})

set(AI__AScript__ScriptClasses__ScriptFS
    "fs_registrator.h"
    "fs_registrator_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptFS" FILES ${AI__AScript__ScriptClasses__ScriptFS})

set(AI__AScript__ScriptClasses__ScriptFcolor
    "../xrServerEntities/script_fcolor.h"
    "../xrServerEntities/script_fcolor_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptFcolor" FILES ${AI__AScript__ScriptClasses__ScriptFcolor})

set(AI__AScript__ScriptClasses__ScriptFlags
    "../xrServerEntities/script_flags.h"
    "../xrServerEntities/script_flags_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptFlags" FILES ${AI__AScript__ScriptClasses__ScriptFlags})

set(AI__AScript__ScriptClasses__ScriptFmatrix
    "../xrServerEntities/script_fmatrix.h"
    "../xrServerEntities/script_fmatrix_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptFmatrix" FILES ${AI__AScript__ScriptClasses__ScriptFmatrix})

set(AI__AScript__ScriptClasses__ScriptFvector
    "../xrServerEntities/script_fvector.h"
    "../xrServerEntities/script_fvector_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptFvector" FILES ${AI__AScript__ScriptClasses__ScriptFvector})

set(AI__AScript__ScriptClasses__ScriptGameObject
    "script_game_object.cpp"
    "script_game_object.h"
    "script_game_object2.cpp"
    "script_game_object3.cpp"
    "script_game_object4.cpp"
    "script_game_object_impl.h"
    "script_game_object_inventory_owner.cpp"
    "script_game_object_script.cpp"
    "script_game_object_script2.cpp"
    "script_game_object_script3.cpp"
    "script_game_object_script_trader.cpp"
    "script_game_object_smart_covers.cpp"
    "script_game_object_trader.cpp"
    "script_game_object_use.cpp"
    "script_game_object_use2.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptGameObject" FILES ${AI__AScript__ScriptClasses__ScriptGameObject})

set(AI__AScript__ScriptClasses__ScriptHit
    "script_hit.cpp"
    "script_hit.h"
    "script_hit_inline.h"
    "script_hit_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptHit" FILES ${AI__AScript__ScriptClasses__ScriptHit})

set(AI__AScript__ScriptClasses__ScriptIniFile
    "../xrServerEntities/script_ini_file.cpp"
    "../xrServerEntities/script_ini_file.h"
    "../xrServerEntities/script_ini_file_inline.h"
    "../xrServerEntities/script_ini_file_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptIniFile" FILES ${AI__AScript__ScriptClasses__ScriptIniFile})

set(AI__AScript__ScriptClasses__ScriptIniFile__ScriptRTokenList
    "../xrServerEntities/script_rtoken_list.h"
    "../xrServerEntities/script_rtoken_list_inline.h"
    "../xrServerEntities/script_rtoken_list_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptIniFile\\ScriptRTokenList" FILES ${AI__AScript__ScriptClasses__ScriptIniFile__ScriptRTokenList})

set(AI__AScript__ScriptClasses__ScriptIniFile__ScriptTokenList
    "../xrServerEntities/script_token_list.cpp"
    "../xrServerEntities/script_token_list.h"
    "../xrServerEntities/script_token_list_inline.h"
    "../xrServerEntities/script_token_list_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptIniFile\\ScriptTokenList" FILES ${AI__AScript__ScriptClasses__ScriptIniFile__ScriptTokenList})

set(AI__AScript__ScriptClasses__ScriptLAnim
    "script_lanim.cpp"
    "script_lanim.h"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptLAnim" FILES ${AI__AScript__ScriptClasses__ScriptLAnim})

set(AI__AScript__ScriptClasses__ScriptMonsterHitInfo
    "script_monster_hit_info.h"
    "script_monster_hit_info_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptMonsterHitInfo" FILES ${AI__AScript__ScriptClasses__ScriptMonsterHitInfo})

set(AI__AScript__ScriptClasses__ScriptNetPacket
    "../xrServerEntities/script_net_packet.h"
    "../xrServerEntities/script_net_packet_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptNetPacket" FILES ${AI__AScript__ScriptClasses__ScriptNetPacket})

set(AI__AScript__ScriptClasses__ScriptParticles
    "script_particles.cpp"
    "script_particles.h"
    "script_particles_inline.h"
    "script_particles_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptParticles" FILES ${AI__AScript__ScriptClasses__ScriptParticles})

set(AI__AScript__ScriptClasses__ScriptReader
    "../xrServerEntities/script_reader.h"
    "../xrServerEntities/script_reader_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptReader" FILES ${AI__AScript__ScriptClasses__ScriptReader})

set(AI__AScript__ScriptClasses__ScriptRenderDevice
    "script_render_device.h"
    "script_render_device_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptRenderDevice" FILES ${AI__AScript__ScriptClasses__ScriptRenderDevice})

set(AI__AScript__ScriptClasses__ScriptSound
    "script_sound.cpp"
    "script_sound.h"
    "script_sound_inline.h"
    "script_sound_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptSound" FILES ${AI__AScript__ScriptClasses__ScriptSound})

set(AI__AScript__ScriptClasses__ScriptSoundInfo
    "script_sound_info.h"
    "script_sound_info_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptSoundInfo" FILES ${AI__AScript__ScriptClasses__ScriptSoundInfo})

set(AI__AScript__ScriptClasses__ScriptSoundType
    "../xrServerEntities/script_sound_type.h"
    "../xrServerEntities/script_sound_type_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\ScriptSoundType" FILES ${AI__AScript__ScriptClasses__ScriptSoundType})

set(AI__AScript__ScriptClasses__UI
    "script_ui_registrator.h"
    "ScriptXMLInit.cpp"
    "ScriptXMLInit.h"
    "ui_export_script.cpp"
)
source_group("AI\\AScript\\ScriptClasses\\UI" FILES ${AI__AScript__ScriptClasses__UI})

set(AI__AScript__ScriptDebugger
    "../xrServerEntities/mslotutils.h"
    "../xrServerEntities/script_callStack.cpp"
    "../xrServerEntities/script_callStack.h"
    "../xrServerEntities/script_debugger.cpp"
    "../xrServerEntities/script_debugger.h"
    "../xrServerEntities/script_debugger_messages.h"
    "../xrServerEntities/script_debugger_threads.cpp"
    "../xrServerEntities/script_debugger_threads.h"
    "../xrServerEntities/script_lua_helper.cpp"
    "../xrServerEntities/script_lua_helper.h"
)
source_group("AI\\AScript\\ScriptDebugger" FILES ${AI__AScript__ScriptDebugger})

set(AI__AScript__ScriptEngine
    "../xrServerEntities/script_engine.cpp"
    "../xrServerEntities/script_engine.h"
    "../xrServerEntities/script_engine_export.cpp"
    "../xrServerEntities/script_engine_export.h"
    "../xrServerEntities/script_engine_inline.h"
    "../xrServerEntities/script_engine_script.cpp"
    "../xrServerEntities/script_engine_space.h"
    "script_engine_help.cpp"
)
source_group("AI\\AScript\\ScriptEngine" FILES ${AI__AScript__ScriptEngine})

set(AI__AScript__ScriptProcess
    "../xrServerEntities/script_process.cpp"
    "../xrServerEntities/script_process.h"
    "../xrServerEntities/script_process_inline.h"
)
source_group("AI\\AScript\\ScriptProcess" FILES ${AI__AScript__ScriptProcess})

set(AI__AScript__ScriptStorage
    "../xrServerEntities/script_storage.cpp"
    "../xrServerEntities/script_storage.h"
    "../xrServerEntities/script_storage_inline.h"
    "../xrServerEntities/script_storage_space.h"
)
source_group("AI\\AScript\\ScriptStorage" FILES ${AI__AScript__ScriptStorage})

set(AI__AScript__ScriptThread
    "../xrServerEntities/script_thread.cpp"
    "../xrServerEntities/script_thread.h"
    "../xrServerEntities/script_thread_inline.h"
)
source_group("AI\\AScript\\ScriptThread" FILES ${AI__AScript__ScriptThread})

set(AI__AScript__ScriptThread__ScriptStackTracker
    "../xrServerEntities/script_stack_tracker.cpp"
    "../xrServerEntities/script_stack_tracker.h"
    "../xrServerEntities/script_stack_tracker_inline.h"
)
source_group("AI\\AScript\\ScriptThread\\ScriptStackTracker" FILES ${AI__AScript__ScriptThread__ScriptStackTracker})

set(AI__AScript__lua_studio
    "../xrServerEntities/lua_studio.cpp"
    "../xrServerEntities/lua_studio.h"
)
source_group("AI\\AScript\\lua_studio" FILES ${AI__AScript__lua_studio})

set(AI__ASound
    "../xrServerEntities/ai_sounds.h"
    "ai_sounds.cpp"
)
source_group("AI\\ASound" FILES ${AI__ASound})

set(AI__ASpace
    "ai_space.cpp"
    "ai_space.h"
    "ai_space_inline.h"
)
source_group("AI\\ASpace" FILES ${AI__ASpace})

set(Core
    "../3rd_party/fastdelegate/fastdelegate.h"
    "../xrServerEntities/pch_script.cpp"
    "../xrServerEntities/pch_script.h"
    "StdAfx.cpp"
    "StdAfx.h"
)
source_group("Core" FILES ${Core})

set(Core__Client__Cameras
    "CameraFirstEye.cpp"
    "CameraFirstEye.h"
    "cameralook.cpp"
    "cameralook.h"
)
source_group("Core\\Client\\Cameras" FILES ${Core__Client__Cameras})

set(Core__Client__Effectors__Actor
    "ActorEffector.cpp"
    "ActorEffector.h"
    "ActorEffector_script.cpp"
    "ActorNightVision.cpp"
    "ActorNightVision.h"
    "CameraEffector.cpp"
    "CameraEffector.h"
    "EffectorBobbing.cpp"
    "EffectorBobbing.h"
    "EffectorFall.cpp"
    "EffectorFall.h"
)
source_group("Core\\Client\\Effectors\\Actor" FILES ${Core__Client__Effectors__Actor})

set(Core__Client__Effectors__Postprocess
    "PostprocessAnimator.cpp"
    "PostprocessAnimator.h"
    "zone_effector.cpp"
    "zone_effector.h"
)
source_group("Core\\Client\\Effectors\\Postprocess" FILES ${Core__Client__Effectors__Postprocess})

set(Core__Client__Effectors__Weapon
    "EffectorShot.cpp"
    "EffectorShot.h"
    "EffectorShotX.cpp"
    "EffectorShotX.h"
    "EffectorZoomInertion.cpp"
    "EffectorZoomInertion.h"
)
source_group("Core\\Client\\Effectors\\Weapon" FILES ${Core__Client__Effectors__Weapon})

set(Core__Client__Effectors__monsters
    "ai/monsters/ai_monster_effector.cpp"
    "ai/monsters/ai_monster_effector.h"
    "pp_effector_custom.cpp"
    "pp_effector_custom.h"
    "pp_effector_distance.cpp"
    "pp_effector_distance.h"
)
source_group("Core\\Client\\Effectors\\monsters" FILES ${Core__Client__Effectors__monsters})

set(Core__Client__Effects
    "script_wallmarks_manager.cpp"
    "script_wallmarks_manager.h"
    "script_wallmarks_script.cpp"
)
source_group("Core\\Client\\Effects" FILES ${Core__Client__Effects})

set(Core__Client__Game_Persistent
    "GamePersistent.cpp"
    "GamePersistent.h"
)
source_group("Core\\Client\\Game Persistent" FILES ${Core__Client__Game_Persistent})

set(Core__Client__Level
    "Level.cpp"
    "Level.h"
    "Level_GameSpy_Funcs.cpp"
    "Level_input.cpp"
    "Level_load.cpp"
    "level_map_locations.cpp"
    "Level_network.cpp"
    "Level_network_compressed_updates.cpp"
    "Level_network_messages.cpp"
    "Level_network_spawn.cpp"
    "Level_network_start_client.cpp"
    "level_script.cpp"
    "Level_secure_messaging.cpp"
    "Level_SLS_Default.cpp"
    "Level_SLS_Load.cpp"
    "Level_SLS_Save.cpp"
    "Level_start.cpp"
    "LevelDebugScript.cpp"
    "LevelDebugScript.h"
)
source_group("Core\\Client\\Level" FILES ${Core__Client__Level})

set(Core__Client__Level_Controller
    "xr_level_controller.cpp"
    "xr_level_controller.h"
)
source_group("Core\\Client\\Level Controller" FILES ${Core__Client__Level_Controller})

set(Core__Client__Level_Debug
    "level_debug.cpp"
    "level_debug.h"
)
source_group("Core\\Client\\Level Debug" FILES ${Core__Client__Level_Debug})

set(Core__Client__Level__AutosaveManager
    "autosave_manager.cpp"
    "autosave_manager.h"
    "autosave_manager_inline.h"
)
source_group("Core\\Client\\Level\\AutosaveManager" FILES ${Core__Client__Level__AutosaveManager})

set(Core__Client__Level__Bullet_Manager
    "Level_Bullet_Manager.cpp"
    "Level_Bullet_Manager.h"
    "Level_bullet_manager_firetrace.cpp"
    "Tracer.cpp"
    "Tracer.h"
)
source_group("Core\\Client\\Level\\Bullet Manager" FILES ${Core__Client__Level__Bullet_Manager})

set(Core__Client__Level__ClientDigestComputer
    "Level_network_digest_computer.cpp"
)
source_group("Core\\Client\\Level\\ClientDigestComputer" FILES ${Core__Client__Level__ClientDigestComputer})

set(Core__Client__Level__ClientSpawnManager
    "client_spawn_manager.cpp"
    "client_spawn_manager.h"
    "client_spawn_manager_inline.h"
    "client_spawn_manager_script.cpp"
)
source_group("Core\\Client\\Level\\ClientSpawnManager" FILES ${Core__Client__Level__ClientSpawnManager})

set(Core__Client__Level__Debug_Renderer
    "debug_renderer.cpp"
    "debug_renderer.h"
    "debug_renderer_inline.h"
)
source_group("Core\\Client\\Level\\Debug Renderer" FILES ${Core__Client__Level__Debug_Renderer})

set(Core__Client__Level__GlobalFeelTouch
    "GlobalFeelTouch.cpp"
    "GlobalFeelTouch.hpp"
)
source_group("Core\\Client\\Level\\GlobalFeelTouch" FILES ${Core__Client__Level__GlobalFeelTouch})

set(Core__Client__Level__Level_Sounds
    "level_sounds.cpp"
    "level_sounds.h"
)
source_group("Core\\Client\\Level\\Level Sounds" FILES ${Core__Client__Level__Level_Sounds})

set(Core__Client__Level__LevelMapSync
    "Level_network_map_sync.cpp"
    "Level_network_map_sync.h"
)
source_group("Core\\Client\\Level\\LevelMapSync" FILES ${Core__Client__Level__LevelMapSync})

set(Core__Client__Level__LevelNetworkDemo
    "DemoInfo.cpp"
    "DemoInfo.h"
    "DemoInfo_Loader.cpp"
    "DemoInfo_Loader.h"
    "DemoPLay_Control.cpp"
    "DemoPlay_Control.h"
    "Level_network_Demo.cpp"
    "Level_network_Demo.h"
    "Message_Filter.cpp"
    "Message_Filter.h"
)
source_group("Core\\Client\\Level\\LevelNetworkDemo" FILES ${Core__Client__Level__LevelNetworkDemo})

set(Core__Client__Level__SeniorityHierarchyHolder
    "../xrServerEntities/LevelGameDef.cpp"
    "../xrServerEntities/LevelGameDef.h"
    "seniority_hierarchy_holder.cpp"
    "seniority_hierarchy_holder.h"
    "seniority_hierarchy_holder_inline.h"
    "seniority_hierarchy_space.h"
)
source_group("Core\\Client\\Level\\SeniorityHierarchyHolder" FILES ${Core__Client__Level__SeniorityHierarchyHolder})

set(Core__Client__Level__SeniorityHierarchyHolder__GroupHierarchyHolder
    "group_hierarchy_holder.cpp"
    "group_hierarchy_holder.h"
    "group_hierarchy_holder_inline.h"
)
source_group("Core\\Client\\Level\\SeniorityHierarchyHolder\\GroupHierarchyHolder" FILES ${Core__Client__Level__SeniorityHierarchyHolder__GroupHierarchyHolder})

set(Core__Client__Level__SeniorityHierarchyHolder__SquadHierarchyHolder
    "squad_hierarchy_holder.cpp"
    "squad_hierarchy_holder.h"
    "squad_hierarchy_holder_inline.h"
)
source_group("Core\\Client\\Level\\SeniorityHierarchyHolder\\SquadHierarchyHolder" FILES ${Core__Client__Level__SeniorityHierarchyHolder__SquadHierarchyHolder})

set(Core__Client__Level__SeniorityHierarchyHolder__TeamHierarchyHolder
    "team_hierarchy_holder.cpp"
    "team_hierarchy_holder.h"
    "team_hierarchy_holder_inline.h"
)
source_group("Core\\Client\\Level\\SeniorityHierarchyHolder\\TeamHierarchyHolder" FILES ${Core__Client__Level__SeniorityHierarchyHolder__TeamHierarchyHolder})

set(Core__Client__Objects__DelayedActionFuse
    "DelayedActionFuse.cpp"
    "DelayedActionFuse.h"
)
source_group("Core\\Client\\Objects\\DelayedActionFuse" FILES ${Core__Client__Objects__DelayedActionFuse})

set(Core__Client__Objects__actor__base
    "Actor.cpp"
    "Actor.h"
    "actor_anim_defs.h"
    "actor_communication.cpp"
    "actor_defs.h"
    "Actor_Events.cpp"
    "Actor_Feel.cpp"
    "Actor_Flags.h"
    "actor_input_handler.cpp"
    "actor_input_handler.h"
    "Actor_Movement.cpp"
    "Actor_Network.cpp"
    "actor_script.cpp"
    "Actor_Sleep.cpp"
    "Actor_Weapon.cpp"
    "ActorAnimation.cpp"
    "ActorAnimation.h"
    "ActorBackpack.cpp"
    "ActorBackpack.h"
    "ActorCameras.cpp"
    "ActorCondition.cpp"
    "ActorCondition.h"
    "ActorCondition_script.cpp"
    "ActorInput.cpp"
    "fire_disp_controller.cpp"
    "fire_disp_controller.h"
)
source_group("Core\\Client\\Objects\\actor\\base" FILES ${Core__Client__Objects__actor__base})

set(Core__Client__Objects__actor__base__memory
    "actor_memory.cpp"
    "actor_memory.h"
)
source_group("Core\\Client\\Objects\\actor\\base\\memory" FILES ${Core__Client__Objects__actor__base__memory})

set(Core__Client__Objects__actor__mp__client
    "actor_mp_client.cpp"
    "actor_mp_client.h"
    "actor_mp_client_export.cpp"
    "actor_mp_client_import.cpp"
)
source_group("Core\\Client\\Objects\\actor\\mp\\client" FILES ${Core__Client__Objects__actor__mp__client})

set(Core__Client__Objects__actor__mp__server
    "actor_mp_server.cpp"
    "actor_mp_server.h"
    "actor_mp_server_export.cpp"
    "actor_mp_server_import.cpp"
)
source_group("Core\\Client\\Objects\\actor\\mp\\server" FILES ${Core__Client__Objects__actor__mp__server})

set(Core__Client__Objects__actor__mp__state
    "actor_mp_state.cpp"
    "actor_mp_state.h"
    "actor_mp_state_inline.h"
)
source_group("Core\\Client\\Objects\\actor\\mp\\state" FILES ${Core__Client__Objects__actor__mp__state})

set(Core__Client__Objects__base
    "script_attachment_manager.cpp"
    "script_attachment_manager.h"
    "script_attachment_script.cpp"
)
source_group("Core\\Client\\Objects\\base" FILES ${Core__Client__Objects__base})

set(Core__Client__Objects__base__Entity
    "Entity.cpp"
    "Entity.h"
)
source_group("Core\\Client\\Objects\\base\\Entity" FILES ${Core__Client__Objects__base__Entity})

set(Core__Client__Objects__base__EntityAlive
    "entity_alive.cpp"
    "entity_alive.h"
    "entity_alive_inline.h"
)
source_group("Core\\Client\\Objects\\base\\EntityAlive" FILES ${Core__Client__Objects__base__EntityAlive})

set(Core__Client__Objects__base__EntityCondition
    "EntityCondition.cpp"
    "EntityCondition.h"
    "hit_immunity.cpp"
    "hit_immunity.h"
    "hit_immunity_space.h"
    "Wound.cpp"
    "Wound.h"
)
source_group("Core\\Client\\Objects\\base\\EntityCondition" FILES ${Core__Client__Objects__base__EntityCondition})

set(Core__Client__Objects__base__GameObject
    "game_object_space.h"
    "GameObject.cpp"
    "GameObject.h"
)
source_group("Core\\Client\\Objects\\base\\GameObject" FILES ${Core__Client__Objects__base__GameObject})

set(Core__Client__Objects__base__GameObject__Holder
    "holder_custom.cpp"
    "holder_custom.h"
    "holder_custom_script.cpp"
)
source_group("Core\\Client\\Objects\\base\\GameObject\\Holder" FILES ${Core__Client__Objects__base__GameObject__Holder})

set(Core__Client__Objects__base__GameObject__Holder__ParticlesPlayer
    "ParticlesPlayer.cpp"
    "ParticlesPlayer.h"
)
source_group("Core\\Client\\Objects\\base\\GameObject\\Holder\\ParticlesPlayer" FILES ${Core__Client__Objects__base__GameObject__Holder__ParticlesPlayer})

set(Core__Client__Objects__base__GameObject__ai_obstacle
    "ai_obstacle.cpp"
    "ai_obstacle.h"
    "ai_obstacle_inline.h"
)
source_group("Core\\Client\\Objects\\base\\GameObject\\ai_obstacle" FILES ${Core__Client__Objects__base__GameObject__ai_obstacle})

set(Core__Client__Objects__base__GameObject__ai_obstacle__min_obb
    "min_obb.cpp"
)
source_group("Core\\Client\\Objects\\base\\GameObject\\ai_obstacle\\min_obb" FILES ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb})

set(Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__magic_box
    "magic_box3.cpp"
    "magic_box3.h"
    "magic_box3_inline.h"
)
source_group("Core\\Client\\Objects\\base\\GameObject\\ai_obstacle\\min_obb\\magic_box" FILES ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__magic_box})

set(Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__magic_minimize_nd
    "magic_minimize_nd.h"
    "magic_minimize_nd_inline.h"
)
source_group("Core\\Client\\Objects\\base\\GameObject\\ai_obstacle\\min_obb\\magic_minimize_nd" FILES ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__magic_minimize_nd})

set(Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__minimize_1d
    "magic_minimize_1d.cpp"
    "magic_minimize_1d.h"
    "magic_minimize_1d_inline.h"
)
source_group("Core\\Client\\Objects\\base\\GameObject\\ai_obstacle\\min_obb\\minimize_1d" FILES ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__minimize_1d})

set(Core__Client__Objects__base__UsableScriptObject
    "UsableScriptObject.cpp"
    "UsableScriptObject.h"
)
source_group("Core\\Client\\Objects\\base\\UsableScriptObject" FILES ${Core__Client__Objects__base__UsableScriptObject})

set(Core__Client__Objects__hanging_lamp
    "HangingLamp.cpp"
    "HangingLamp.h"
    "script_light.h"
    "script_light_inline.h"
    "script_light_script.cpp"
)
source_group("Core\\Client\\Objects\\hanging_lamp" FILES ${Core__Client__Objects__hanging_lamp})

set(Core__Client__Objects__inventory
    "../xrServerEntities/inventory_space.h"
    "Inventory.cpp"
    "Inventory.h"
    "inventory_quickswitch.cpp"
)
source_group("Core\\Client\\Objects\\inventory" FILES ${Core__Client__Objects__inventory})

set(Core__Client__Objects__inventory__AttachableItem
    "attachable_item.cpp"
    "attachable_item.h"
    "attachable_item_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\AttachableItem" FILES ${Core__Client__Objects__inventory__AttachableItem})

set(Core__Client__Objects__inventory__AttachmentOwner
    "attachment_owner.cpp"
    "attachment_owner.h"
    "attachment_owner_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\AttachmentOwner" FILES ${Core__Client__Objects__inventory__AttachmentOwner})

set(Core__Client__Objects__inventory__EatableItem
    "eatable_item.cpp"
    "eatable_item.h"
    "eatable_item_script.cpp"
)
source_group("Core\\Client\\Objects\\inventory\\EatableItem" FILES ${Core__Client__Objects__inventory__EatableItem})

set(Core__Client__Objects__inventory__EatableItemObject
    "eatable_item_object.cpp"
    "eatable_item_object.h"
)
source_group("Core\\Client\\Objects\\inventory\\EatableItemObject" FILES ${Core__Client__Objects__inventory__EatableItemObject})

set(Core__Client__Objects__inventory__InventoryItem
    "inventory_item.cpp"
    "inventory_item.h"
    "inventory_item_impl.h"
    "inventory_item_inline.h"
    "inventory_item_script.cpp"
    "inventory_item_upgrade.cpp"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryItem" FILES ${Core__Client__Objects__inventory__InventoryItem})

set(Core__Client__Objects__inventory__InventoryItemObject
    "inventory_item_object.cpp"
    "inventory_item_object.h"
    "inventory_item_object_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryItemObject" FILES ${Core__Client__Objects__inventory__InventoryItemObject})

set(Core__Client__Objects__inventory__InventoryOwner
    "inventory_owner_info.cpp"
    "inventory_owner_inline.h"
    "InventoryOwner.cpp"
    "InventoryOwner.h"
    "InventoryOwner_script.cpp"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner" FILES ${Core__Client__Objects__inventory__InventoryOwner})

set(Core__Client__Objects__inventory__InventoryOwner__character_info
    "../xrServerEntities/character_info.cpp"
    "../xrServerEntities/character_info.h"
    "../xrServerEntities/character_info_defs.h"
    "../xrServerEntities/specific_character.cpp"
    "../xrServerEntities/specific_character.h"
    "character_community.cpp"
    "character_community.h"
    "character_rank.cpp"
    "character_rank.h"
    "character_reputation.cpp"
    "character_reputation.h"
    "ini_id_loader.h"
    "ini_table_loader.h"
    "monster_community.cpp"
    "monster_community.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\character_info" FILES ${Core__Client__Objects__inventory__InventoryOwner__character_info})

set(Core__Client__Objects__inventory__InventoryOwner__relation_registry
    "relation_registry.cpp"
    "relation_registry.h"
    "relation_registry_actions.cpp"
    "relation_registry_defs.h"
    "relation_registry_fights.cpp"
    "relation_registry_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\relation registry" FILES ${Core__Client__Objects__inventory__InventoryOwner__relation_registry})

set(Core__Client__Objects__inventory__InventoryOwner__trade_parameters__purchase_list
    "purchase_list.cpp"
    "purchase_list.h"
    "purchase_list_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\trade_parameters\\purchase_list" FILES ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__purchase_list})

set(Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_action_parameters
    "trade_action_parameters.h"
    "trade_action_parameters_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\trade_parameters\\trade_action_parameters" FILES ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_action_parameters})

set(Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_bool_parameters
    "trade_bool_parameters.h"
    "trade_bool_parameters_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\trade_parameters\\trade_bool_parameters" FILES ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_bool_parameters})

set(Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_factor_parameters
    "trade_factor_parameters.h"
    "trade_factor_parameters_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\trade_parameters\\trade_factor_parameters" FILES ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_factor_parameters})

set(Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_factors
    "trade_factors.h"
    "trade_factors_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\trade_parameters\\trade_factors" FILES ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_factors})

set(Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_parameters
    "trade_parameters.cpp"
    "trade_parameters.h"
    "trade_parameters_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\InventoryOwner\\trade_parameters\\trade_parameters" FILES ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_parameters})

set(Core__Client__Objects__inventory__PhysicItem
    "physic_item.cpp"
    "physic_item.h"
    "physic_item_inline.h"
)
source_group("Core\\Client\\Objects\\inventory\\PhysicItem" FILES ${Core__Client__Objects__inventory__PhysicItem})

set(Core__Client__Objects__inventory_box
    "InventoryBox.cpp"
    "InventoryBox.h"
    "InventoryBox_script.cpp"
)
source_group("Core\\Client\\Objects\\inventory_box" FILES ${Core__Client__Objects__inventory_box})

set(Core__Client__Objects__items__weapons__Artifacts
    "Artefact.cpp"
    "Artefact.h"
    "artefact_activation.cpp"
    "artefact_activation.h"
    "artefact_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts" FILES ${Core__Client__Objects__items__weapons__Artifacts})

set(Core__Client__Objects__items__weapons__Artifacts__BastArtifact
    "BastArtifact.cpp"
    "BastArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\BastArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__BastArtifact})

set(Core__Client__Objects__items__weapons__Artifacts__BlackDrops
    "BlackDrops.cpp"
    "BlackDrops.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\BlackDrops" FILES ${Core__Client__Objects__items__weapons__Artifacts__BlackDrops})

set(Core__Client__Objects__items__weapons__Artifacts__BlackGraviArtifact
    "BlackGraviArtifact.cpp"
    "BlackGraviArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\BlackGraviArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__BlackGraviArtifact})

set(Core__Client__Objects__items__weapons__Artifacts__CtaGameArtefact
    "cta_game_artefact.cpp"
    "cta_game_artefact.h"
    "cta_game_artefact_activation.cpp"
    "cta_game_artefact_activation.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\CtaGameArtefact" FILES ${Core__Client__Objects__items__weapons__Artifacts__CtaGameArtefact})

set(Core__Client__Objects__items__weapons__Artifacts__DummyArtifact
    "DummyArtifact.cpp"
    "DummyArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\DummyArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__DummyArtifact})

set(Core__Client__Objects__items__weapons__Artifacts__Electric_Ball
    "ElectricBall.cpp"
    "ElectricBall.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\Electric Ball" FILES ${Core__Client__Objects__items__weapons__Artifacts__Electric_Ball})

set(Core__Client__Objects__items__weapons__Artifacts__Faded_Ball
    "FadedBall.cpp"
    "FadedBall.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\Faded Ball" FILES ${Core__Client__Objects__items__weapons__Artifacts__Faded_Ball})

set(Core__Client__Objects__items__weapons__Artifacts__Faded_Ball__Mercury_Ball
    "MercuryBall.cpp"
    "MercuryBall.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\Faded Ball\\Mercury Ball" FILES ${Core__Client__Objects__items__weapons__Artifacts__Faded_Ball__Mercury_Ball})

set(Core__Client__Objects__items__weapons__Artifacts__GalantineArtifact
    "GalantineArtifact.cpp"
    "GalantineArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\GalantineArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__GalantineArtifact})

set(Core__Client__Objects__items__weapons__Artifacts__GraviArtifact
    "GraviArtifact.cpp"
    "GraviArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\GraviArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__GraviArtifact})

set(Core__Client__Objects__items__weapons__Artifacts__Needles
    "Needles.cpp"
    "Needles.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\Needles" FILES ${Core__Client__Objects__items__weapons__Artifacts__Needles})

set(Core__Client__Objects__items__weapons__Artifacts__RustyHairArtifact
    "RustyHairArtifact.cpp"
    "RustyHairArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\RustyHairArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__RustyHairArtifact})

set(Core__Client__Objects__items__weapons__Artifacts__ThornArtifact
    "ThornArtifact.cpp"
    "ThornArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\ThornArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__ThornArtifact})

set(Core__Client__Objects__items__weapons__Artifacts__ZudaArtifact
    "ZudaArtifact.cpp"
    "ZudaArtifact.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Artifacts\\ZudaArtifact" FILES ${Core__Client__Objects__items__weapons__Artifacts__ZudaArtifact})

set(Core__Client__Objects__items__weapons__Devices
    "CustomDevice.cpp"
    "CustomDevice.h"
    "Dosimeter.cpp"
    "Dosimeter.h"
    "Flashlight.cpp"
    "Flashlight.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Devices" FILES ${Core__Client__Objects__items__weapons__Devices})

set(Core__Client__Objects__items__weapons__Devices__Detectors
    "CustomDetector.cpp"
    "CustomDetector.h"
    "ui/ArtefactDetectorUI.cpp"
    "ui/ArtefactDetectorUI.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Devices\\Detectors" FILES ${Core__Client__Objects__items__weapons__Devices__Detectors})

set(Core__Client__Objects__items__weapons__Devices__Detectors__AdvancedDetector
    "AdvancedDetector.cpp"
    "AdvancedDetector.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Devices\\Detectors\\AdvancedDetector" FILES ${Core__Client__Objects__items__weapons__Devices__Detectors__AdvancedDetector})

set(Core__Client__Objects__items__weapons__Devices__Detectors__EliteDetector
    "EliteDetector.cpp"
    "EliteDetector.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Devices\\Detectors\\EliteDetector" FILES ${Core__Client__Objects__items__weapons__Devices__Detectors__EliteDetector})

set(Core__Client__Objects__items__weapons__Devices__Detectors__Simple_Detector
    "SimpleDetector.cpp"
    "SimpleDetector.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Devices\\Detectors\\Simple Detector" FILES ${Core__Client__Objects__items__weapons__Devices__Detectors__Simple_Detector})

set(Core__Client__Objects__items__weapons__Devices__Torch
    "Torch.cpp"
    "Torch.h"
    "torch_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Devices\\Torch" FILES ${Core__Client__Objects__items__weapons__Devices__Torch})

set(Core__Client__Objects__items__weapons__Devices__flare
    "flare.cpp"
    "flare.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Devices\\flare" FILES ${Core__Client__Objects__items__weapons__Devices__flare})

set(Core__Client__Objects__items__weapons__Documents
    "InfoDocument.cpp"
    "InfoDocument.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Documents" FILES ${Core__Client__Objects__items__weapons__Documents})

set(Core__Client__Objects__items__weapons__Explosives
    "Explosive.cpp"
    "ExplosiveItem.cpp"
    "ExplosiveItem.h"
    "ExplosiveScript.cpp"
    "wallmark_manager.cpp"
    "wallmark_manager.h"
)
if(ENABLE_DEBUG_OLD_RUNTIME)
    list(APPEND Core__Client__Objects__items__weapons__Explosives Explosive.h)
endif()
source_group("Core\\Client\\Objects\\items & weapons\\Explosives" FILES ${Core__Client__Objects__items__weapons__Explosives})

set(Core__Client__Objects__items__weapons__Food__Drugs
    "antirad.cpp"
    "antirad.h"
    "antirad_script.cpp"
    "BottleItem.cpp"
    "BottleItem.h"
    "BottleItem_script.cpp"
    "FoodItem.cpp"
    "FoodItem.h"
    "FoodItem_script.cpp"
    "medkit.cpp"
    "medkit.h"
    "medkit_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Food & Drugs" FILES ${Core__Client__Objects__items__weapons__Food__Drugs})

set(Core__Client__Objects__items__weapons__HudItem
    "hud_item_object.cpp"
    "hud_item_object.h"
    "HudItem.cpp"
    "HudItem.h"
    "HudSound.cpp"
    "HudSound.h"
    "player_hud.cpp"
    "player_hud.h"
    "player_hud_legs.cpp"
    "player_hud_legs.h"
    "player_hud_script.cpp"
    "player_hud_tune.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\HudItem" FILES ${Core__Client__Objects__items__weapons__HudItem})

set(Core__Client__Objects__items__weapons__MPAnticheat
    "anticheat_dumpable_object.h"
    "mpactor_dump_impl.cpp"
    "shootingObject_dump_impl.cpp"
    "weapon_ammo_dump_impl.cpp"
    "weapon_dump_impl.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\MPAnticheat" FILES ${Core__Client__Objects__items__weapons__MPAnticheat})

set(Core__Client__Objects__items__weapons__MPPlayersBag
    "MPPlayersBag.cpp"
    "MPPlayersBag.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\MPPlayersBag" FILES ${Core__Client__Objects__items__weapons__MPPlayersBag})

set(Core__Client__Objects__items__weapons__Outfit
    "ActorHelmet.cpp"
    "ActorHelmet.h"
    "BoneProtections.cpp"
    "BoneProtections.h"
    "CustomOutfit.cpp"
    "CustomOutfit.h"
    "CustomOutfit_script.cpp"
    "ExoOutfit.cpp"
    "ExoOutfit.h"
    "MilitaryOutfit.cpp"
    "MilitaryOutfit.h"
    "ScientificOutfit.cpp"
    "ScientificOutfit.h"
    "StalkerOutfit.cpp"
    "StalkerOutfit.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Outfit" FILES ${Core__Client__Objects__items__weapons__Outfit})

set(Core__Client__Objects__items__weapons__PDA__information
    "PDA.cpp"
    "PDA.h"
    "pda_space.h"
    "PdaMsg.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\PDA & information" FILES ${Core__Client__Objects__items__weapons__PDA__information})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__GrenadeLauncher
    "GrenadeLauncher.cpp"
    "GrenadeLauncher.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Addons\\GrenadeLauncher" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__GrenadeLauncher})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__Scope
    "Scope.cpp"
    "Scope.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Addons\\Scope" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__Scope})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__Silencer
    "Silencer.cpp"
    "Silencer.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Addons\\Silencer" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__Silencer})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Ammo
    "WeaponAmmo.cpp"
    "WeaponAmmo.h"
    "WeaponAmmo_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Ammo" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Ammo})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Automatic
    "WeaponMagazined.cpp"
    "WeaponMagazined.h"
    "WeaponMagazinedWGrenade.cpp"
    "WeaponMagazinedWGrenade.h"
    "WeaponMagazineExtended.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Automatic" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Automatic})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Grenades__Missiles
    "Grenade.cpp"
    "Grenade.h"
    "Missile.cpp"
    "Missile.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Grenades & Missiles" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Grenades__Missiles})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Pistol
    "WeaponCustomAuto.cpp"
    "WeaponCustomAuto.h"
    "WeaponCustomPistol.cpp"
    "WeaponCustomPistol.h"
    "WeaponPistol.cpp"
    "WeaponPistol.h"
    "WeaponRevolver.cpp"
    "WeaponRevolver.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Pistol" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Pistol})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__RocketLauncher
    "CustomRocket.cpp"
    "CustomRocket.h"
    "ExplosiveRocket.cpp"
    "ExplosiveRocket.h"
    "RocketLauncher.cpp"
    "RocketLauncher.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\RocketLauncher" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__RocketLauncher})

set(Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Weapon_Generic
    "CameraRecoil.h"
    "firedeps.h"
    "first_bullet_controller.cpp"
    "first_bullet_controller.h"
    "ShootingObject.cpp"
    "ShootingObject.h"
    "Weapon.cpp"
    "Weapon.h"
    "WeaponDispersion.cpp"
    "WeaponFire.cpp"
    "WeaponUpgrade.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Custom Weapon\\Weapon Generic" FILES ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Weapon_Generic})

set(Core__Client__Objects__items__weapons__Weapons__StationaryMgun
    "WeaponStatMgun.cpp"
    "WeaponStatMgun.h"
    "WeaponStatMgunBarrel.cpp"
    "WeaponStatMgunFire.cpp"
    "WeaponStatMgunIR.cpp"
    "WeaponStatMgunMisc.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\StationaryMgun" FILES ${Core__Client__Objects__items__weapons__Weapons__StationaryMgun})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__BM-16
    "weaponBM16.cpp"
    "weaponBM16.h"
    "weaponBM16_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\BM-16" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__BM-16})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Binocular
    "WeaponBinoculars.cpp"
    "WeaponBinoculars.h"
    "WeaponBinoculars_script.cpp"
    "WeaponBinocularsVision.cpp"
    "WeaponBinocularsVision.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Binocular" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Binocular})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Bolt
    "Bolt.cpp"
    "Bolt.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Bolt" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Bolt})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__FN2000
    "WeaponFN2000.cpp"
    "WeaponFN2000.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\FN2000" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__FN2000})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__FORT
    "WeaponFORT.cpp"
    "WeaponFORT.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\FORT" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__FORT})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Grenade_F1
    "F1.cpp"
    "F1.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Grenade F1" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Grenade_F1})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__HPSA
    "WeaponHPSA.cpp"
    "WeaponHPSA.h"
    "WeaponHPSA_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\HPSA" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__HPSA})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Knife
    "WeaponKnife.cpp"
    "WeaponKnife.h"
    "WeaponKnife_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Knife" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Knife})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__LR300
    "WeaponLR300.cpp"
    "WeaponLR300.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\LR300" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__LR300})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__PM
    "WeaponPM.cpp"
    "WeaponPM.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\PM" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__PM})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__RGD5
    "RGD5.cpp"
    "RGD5.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\RGD5" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__RGD5})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__RPG7
    "WeaponRPG7.cpp"
    "WeaponRPG7.h"
    "WeaponRPG7_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\RPG7" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__RPG7})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__SSRS
    "WeaponSSRS.cpp"
    "WeaponSSRS.h"
    "WeaponSSRS_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\SSRS" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__SSRS})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__SVD
    "WeaponSVD.cpp"
    "WeaponSVD.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\SVD" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__SVD})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__SVU
    "WeaponSVU.cpp"
    "WeaponSVU.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\SVU" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__SVU})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_AK74
    "WeaponAK74.cpp"
    "WeaponAK74.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon AK74" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_AK74})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_AutomaticShotgun
    "WeaponAutomaticShotgun.cpp"
    "WeaponAutomaticShotgun.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon AutomaticShotgun" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_AutomaticShotgun})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Groza
    "WeaponGroza.cpp"
    "WeaponGroza.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon Groza" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Groza})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_RG6
    "WeaponRG6.cpp"
    "WeaponRG6.h"
    "WeaponRG6_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon RG6" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_RG6})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Shotgun
    "WeaponShotgun.cpp"
    "WeaponShotgun.h"
    "weaponshotgun_script.cpp"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon Shotgun" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Shotgun})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_USP45
    "WeaponUSP45.cpp"
    "WeaponUSP45.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon USP45" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_USP45})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Val
    "WeaponVal.cpp"
    "WeaponVal.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon Val" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Val})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Vintorez
    "WeaponVintorez.cpp"
    "WeaponVintorez.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon Vintorez" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Vintorez})

set(Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Walther_99
    "WeaponWalther.cpp"
    "WeaponWalther.h"
)
source_group("Core\\Client\\Objects\\items & weapons\\Weapons\\Various weapons\\Weapon Walther 99" FILES ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Walther_99})

set(Core__Client__Objects__physics__Breakable
    "BreakableObject.cpp"
    "BreakableObject.h"
)
source_group("Core\\Client\\Objects\\physics\\Breakable" FILES ${Core__Client__Objects__physics__Breakable})

set(Core__Client__Objects__physics__Climable
    "ClimableObject.cpp"
    "ClimableObject.h"
)
source_group("Core\\Client\\Objects\\physics\\Climable" FILES ${Core__Client__Objects__physics__Climable})

set(Core__Client__Objects__physics__CollisionDamageReceiver
    "PHCollisionDamageReceiver.cpp"
    "PHCollisionDamageReceiver.h"
)
source_group("Core\\Client\\Objects\\physics\\CollisionDamageReceiver" FILES ${Core__Client__Objects__physics__CollisionDamageReceiver})

set(Core__Client__Objects__physics__DestroyablePhysicsObject
    "DestroyablePhysicsObject.cpp"
    "DestroyablePhysicsObject.h"
)
source_group("Core\\Client\\Objects\\physics\\DestroyablePhysicsObject" FILES ${Core__Client__Objects__physics__DestroyablePhysicsObject})

set(Core__Client__Objects__physics__PHDestroyable
    "PHDestroyable.cpp"
    "PHDestroyable.h"
)
source_group("Core\\Client\\Objects\\physics\\PHDestroyable" FILES ${Core__Client__Objects__physics__PHDestroyable})

set(Core__Client__Objects__physics__PHSkeleton
    "PHSkeleton.cpp"
    "PHSkeleton.h"
)
source_group("Core\\Client\\Objects\\physics\\PHSkeleton" FILES ${Core__Client__Objects__physics__PHSkeleton})

set(Core__Client__Objects__physics__PhysicObject
    "animation_script_callback.cpp"
    "animation_script_callback.h"
    "PhysicObject.cpp"
    "PhysicObject.h"
    "PhysicObject_script.cpp"
)
source_group("Core\\Client\\Objects\\physics\\PhysicObject" FILES ${Core__Client__Objects__physics__PhysicObject})

set(Core__Client__Objects__physics__PhysicsShellHolder
    "PhysicsShellHolder.cpp"
    "PhysicsShellHolder.h"
)
source_group("Core\\Client\\Objects\\physics\\PhysicsShellHolder" FILES ${Core__Client__Objects__physics__PhysicsShellHolder})

set(Core__Client__Objects__physics__PhysicsSkeletonObject
    "PHDestroyableNotificate.cpp"
    "PHDestroyableNotificate.h"
    "PhysicsSkeletonObject.cpp"
    "PhysicsSkeletonObject.h"
)
source_group("Core\\Client\\Objects\\physics\\PhysicsSkeletonObject" FILES ${Core__Client__Objects__physics__PhysicsSkeletonObject})

set(Core__Client__Objects__searchlight
    "searchlight.cpp"
    "searchlight.h"
)
source_group("Core\\Client\\Objects\\searchlight" FILES ${Core__Client__Objects__searchlight})

set(Core__Client__Objects__searchlight__Trade
    "trade.cpp"
    "trade.h"
    "trade2.cpp"
)
source_group("Core\\Client\\Objects\\searchlight\\Trade" FILES ${Core__Client__Objects__searchlight__Trade})

set(Core__Client__Objects__tasks_info_dialogs
    "../xrServerEntities/InfoPortionDefs.h"
    "../xrServerEntities/xml_str_id_loader.h"
    "InfoPortion.cpp"
    "InfoPortion.h"
)
source_group("Core\\Client\\Objects\\tasks_info_dialogs" FILES ${Core__Client__Objects__tasks_info_dialogs})

set(Core__Client__Objects__tasks_info_dialogs__dialogs
    "AI_PhraseDialogManager.cpp"
    "AI_PhraseDialogManager.h"
    "Phrase.cpp"
    "Phrase.h"
    "PhraseDialog.cpp"
    "PhraseDialog.h"
    "PhraseDialog_script.cpp"
    "PhraseDialog_script.h"
    "PhraseDialogDefs.h"
    "PhraseDialogManager.cpp"
    "PhraseDialogManager.h"
    "PhraseScript.cpp"
    "PhraseScript.h"
)
source_group("Core\\Client\\Objects\\tasks_info_dialogs\\dialogs" FILES ${Core__Client__Objects__tasks_info_dialogs__dialogs})

set(Core__Client__Objects__tasks_info_dialogs__encyclopedia
    "encyclopedia_article.cpp"
    "encyclopedia_article.h"
    "encyclopedia_article_defs.h"
)
source_group("Core\\Client\\Objects\\tasks_info_dialogs\\encyclopedia" FILES ${Core__Client__Objects__tasks_info_dialogs__encyclopedia})

set(Core__Client__Objects__tasks_info_dialogs__game_tasks
    "GameTask.cpp"
    "GameTask.h"
    "GameTask_script.cpp"
    "GameTaskDefs.h"
    "GametaskManager.cpp"
    "GametaskManager.h"
)
source_group("Core\\Client\\Objects\\tasks_info_dialogs\\game tasks" FILES ${Core__Client__Objects__tasks_info_dialogs__game_tasks})

set(Core__Client__Objects__tasks_info_dialogs__map
    "map_location.cpp"
    "map_location.h"
    "map_location_defs.h"
    "map_manager.cpp"
    "map_manager.h"
    "map_manager_script.cpp"
)
source_group("Core\\Client\\Objects\\tasks_info_dialogs\\map" FILES ${Core__Client__Objects__tasks_info_dialogs__map})

set(Core__Client__Objects__tasks_info_dialogs__news
    "game_news.cpp"
    "game_news.h"
)
source_group("Core\\Client\\Objects\\tasks_info_dialogs\\news" FILES ${Core__Client__Objects__tasks_info_dialogs__news})

set(Core__Client__Objects__tasks_info_dialogs__statistics
    "actor_statistic_defs.h"
    "actor_statistic_mgr.cpp"
    "actor_statistic_mgr.h"
)
source_group("Core\\Client\\Objects\\tasks_info_dialogs\\statistics" FILES ${Core__Client__Objects__tasks_info_dialogs__statistics})

set(Core__Client__Objects__vehicles
    "HolderEntityObject.cpp"
    "HolderEntityObject.h"
)
source_group("Core\\Client\\Objects\\vehicles" FILES ${Core__Client__Objects__vehicles})

set(Core__Client__Objects__vehicles__Car
    "Car.cpp"
    "Car.h"
    "CarCameras.cpp"
    "CarDamageParticles.cpp"
    "CarDamageParticles.h"
    "CarDoors.cpp"
    "CarExhaust.cpp"
    "CarInput.cpp"
    "CarLights.cpp"
    "CarLights.h"
    "CarNew.cpp"
    "CarScript.cpp"
    "CarSound.cpp"
    "CarDrone.cpp"
    "CarDrone.h"
    "CarWheels.cpp"
    "DBG_Car.cpp"
)
source_group("Core\\Client\\Objects\\vehicles\\Car" FILES ${Core__Client__Objects__vehicles__Car})

set(Core__Client__Objects__vehicles__Car__CarWeapon
    "CarWeapon.cpp"
    "CarWeapon.h"
)
source_group("Core\\Client\\Objects\\vehicles\\Car\\CarWeapon" FILES ${Core__Client__Objects__vehicles__Car__CarWeapon})

set(Core__Client__Objects__vehicles__Car__car_memory
    "car_memory.cpp"
    "car_memory.h"
)
source_group("Core\\Client\\Objects\\vehicles\\Car\\car_memory" FILES ${Core__Client__Objects__vehicles__Car__car_memory})

set(Core__Client__Objects__vehicles__heli
    "Helicopter.cpp"
    "helicopter.h"
    "Helicopter2.cpp"
    "helicopter_script.cpp"
    "HelicopterMovementManager.cpp"
    "HelicopterWeapon.cpp"
)
source_group("Core\\Client\\Objects\\vehicles\\heli" FILES ${Core__Client__Objects__vehicles__heli})

set(Core__Client__Objects__zones__Ameba
    "AmebaZone.cpp"
    "AmebaZone.h"
)
source_group("Core\\Client\\Objects\\zones\\Ameba" FILES ${Core__Client__Objects__zones__Ameba})

set(Core__Client__Objects__zones__CustomZone
    "CustomZone.cpp"
    "CustomZone.h"
    "CustomZone_script.cpp"
)
source_group("Core\\Client\\Objects\\zones\\CustomZone" FILES ${Core__Client__Objects__zones__CustomZone})

set(Core__Client__Objects__zones__FryUpZone
    "FryupZone.cpp"
    "FryupZone.h"
)
source_group("Core\\Client\\Objects\\zones\\FryUpZone" FILES ${Core__Client__Objects__zones__FryUpZone})

set(Core__Client__Objects__zones__GraviZone
    "GraviZone.cpp"
    "GraviZone.h"
)
source_group("Core\\Client\\Objects\\zones\\GraviZone" FILES ${Core__Client__Objects__zones__GraviZone})

set(Core__Client__Objects__zones__HairsZone
    "HairsZone.cpp"
    "HairsZone.h"
    "HairsZone_script.cpp"
)
source_group("Core\\Client\\Objects\\zones\\HairsZone" FILES ${Core__Client__Objects__zones__HairsZone})

set(Core__Client__Objects__zones__LevelChanger
    "level_changer.cpp"
    "level_changer.h"
)
source_group("Core\\Client\\Objects\\zones\\LevelChanger" FILES ${Core__Client__Objects__zones__LevelChanger})

set(Core__Client__Objects__zones__Mincer
    "Mincer.cpp"
    "Mincer.h"
    "mincer_script.cpp"
)
source_group("Core\\Client\\Objects\\zones\\Mincer" FILES ${Core__Client__Objects__zones__Mincer})

set(Core__Client__Objects__zones__MosquitoBald
    "MosquitoBald.cpp"
    "MosquitoBald.h"
    "MosquitoBald_script.cpp"
)
source_group("Core\\Client\\Objects\\zones\\MosquitoBald" FILES ${Core__Client__Objects__zones__MosquitoBald})

set(Core__Client__Objects__zones__NoGravityZone
    "NoGravityZone.cpp"
    "NoGravityZone.h"
)
source_group("Core\\Client\\Objects\\zones\\NoGravityZone" FILES ${Core__Client__Objects__zones__NoGravityZone})

set(Core__Client__Objects__zones__RadioactiveZone
    "RadioactiveZone.cpp"
    "RadioactiveZone.h"
)
source_group("Core\\Client\\Objects\\zones\\RadioactiveZone" FILES ${Core__Client__Objects__zones__RadioactiveZone})

set(Core__Client__Objects__zones__ScriptZone
    "script_zone.cpp"
    "script_zone.h"
    "script_zone_script.cpp"
)
source_group("Core\\Client\\Objects\\zones\\ScriptZone" FILES ${Core__Client__Objects__zones__ScriptZone})

set(Core__Client__Objects__zones__SmartZone
    "smart_zone.h"
)
source_group("Core\\Client\\Objects\\zones\\SmartZone" FILES ${Core__Client__Objects__zones__SmartZone})

set(Core__Client__Objects__zones__SpaceRestrictor
    "space_restrictor.cpp"
    "space_restrictor.h"
    "space_restrictor_inline.h"
    "space_restrictor_script.cpp"
)
source_group("Core\\Client\\Objects\\zones\\SpaceRestrictor" FILES ${Core__Client__Objects__zones__SpaceRestrictor})

set(Core__Client__Objects__zones__TeamBaseZone
    "team_base_zone.cpp"
    "team_base_zone.h"
)
source_group("Core\\Client\\Objects\\zones\\TeamBaseZone" FILES ${Core__Client__Objects__zones__TeamBaseZone})

set(Core__Client__Objects__zones__TorridZone
    "TorridZone.cpp"
    "TorridZone.h"
)
source_group("Core\\Client\\Objects\\zones\\TorridZone" FILES ${Core__Client__Objects__zones__TorridZone})

set(Core__Client__Objects__zones__ZoneVisual
    "ZoneVisual.cpp"
    "ZoneVisual.h"
)
source_group("Core\\Client\\Objects\\zones\\ZoneVisual" FILES ${Core__Client__Objects__zones__ZoneVisual})

set(Core__Client__Objects__zones__campfire
    "ZoneCampfire.cpp"
    "ZoneCampfire.h"
)
source_group("Core\\Client\\Objects\\zones\\campfire" FILES ${Core__Client__Objects__zones__campfire})

set(Core__Client__Particles
    "ParticlesObject.cpp"
    "ParticlesObject.h"
)
source_group("Core\\Client\\Particles" FILES ${Core__Client__Particles})

set(Core__Client__Spectator
    "Spectator.cpp"
    "Spectator.h"
)
source_group("Core\\Client\\Spectator" FILES ${Core__Client__Spectator})

set(Core__Client__Spectator__Cameras
    "spectator_camera_first_eye.cpp"
    "spectator_camera_first_eye.h"
)
source_group("Core\\Client\\Spectator\\Cameras" FILES ${Core__Client__Spectator__Cameras})

set(Core__Common
    "raypick.cpp"
    "raypick.h"
)
source_group("Core\\Common" FILES ${Core__Common})

set(Core__Common__Console_Commands
    "console_commands.cpp"
    "console_commands_mp.cpp"
)
source_group("Core\\Common\\Console Commands" FILES ${Core__Common__Console_Commands})

set(Core__Common__DateTime
    "date_time.cpp"
    "date_time.h"
)
source_group("Core\\Common\\DateTime" FILES ${Core__Common__DateTime})

set(Core__Common__Dll_Process_Detach
    "xrgame_dll_detach.cpp"
)
source_group("Core\\Common\\Dll Process Detach" FILES ${Core__Common__Dll_Process_Detach})

set(Core__Common__NET_Shared
    "../xrServerEntities/xrMessages.h"
    "NET_Queue.h"
    "traffic_optimization.cpp"
    "traffic_optimization.h"
)
source_group("Core\\Common\\NET Shared" FILES ${Core__Common__NET_Shared})

set(Core__Common__NET_Shared__SecureMessages
    "secure_messaging.cpp"
    "secure_messaging.h"
    "xr_dsa_signer.cpp"
    "xr_dsa_signer.h"
    "xr_dsa_verifyer.cpp"
    "xr_dsa_verifyer.h"
)
source_group("Core\\Common\\NET Shared\\SecureMessages" FILES ${Core__Common__NET_Shared__SecureMessages})

set(Core__Common__ObjectBroker
    "../xrServerEntities/object_broker.h"
    "../xrServerEntities/object_cloner.h"
    "../xrServerEntities/object_comparer.h"
    "../xrServerEntities/object_destroyer.h"
    "../xrServerEntities/object_interfaces.h"
    "../xrServerEntities/object_loader.h"
    "../xrServerEntities/object_saver.h"
    "../xrServerEntities/object_type_traits.h"
)
source_group("Core\\Common\\ObjectBroker" FILES ${Core__Common__ObjectBroker})

set(Core__Common__ObjectFactory
    "../xrServerEntities/clsid_game.h"
    "../xrServerEntities/object_factory.cpp"
    "../xrServerEntities/object_factory.h"
    "../xrServerEntities/object_factory_impl.h"
    "../xrServerEntities/object_factory_inline.h"
    "../xrServerEntities/object_factory_register.cpp"
    "../xrServerEntities/object_factory_script.cpp"
    "../xrServerEntities/object_factory_space.h"
)
source_group("Core\\Common\\ObjectFactory" FILES ${Core__Common__ObjectFactory})

set(Core__Common__ObjectFactory__object_item_abstract
    "../xrServerEntities/object_item_abstract.h"
    "../xrServerEntities/object_item_abstract_inline.h"
)
source_group("Core\\Common\\ObjectFactory\\object_item_abstract" FILES ${Core__Common__ObjectFactory__object_item_abstract})

set(Core__Common__ObjectFactory__object_item_client_server
    "../xrServerEntities/object_item_client_server.h"
    "../xrServerEntities/object_item_client_server_inline.h"
)
source_group("Core\\Common\\ObjectFactory\\object_item_client_server" FILES ${Core__Common__ObjectFactory__object_item_client_server})

set(Core__Common__ObjectFactory__object_item_script
    "../xrServerEntities/object_item_script.cpp"
    "../xrServerEntities/object_item_script.h"
)
source_group("Core\\Common\\ObjectFactory\\object_item_script" FILES ${Core__Common__ObjectFactory__object_item_script})

set(Core__Common__ObjectFactory__object_item_single
    "../xrServerEntities/object_item_single.h"
    "../xrServerEntities/object_item_single_inline.h"
)
source_group("Core\\Common\\ObjectFactory\\object_item_single" FILES ${Core__Common__ObjectFactory__object_item_single})

set(Core__Common__Profiler
#    "profiler.cpp"
    # "profiler_inline.h"
)
source_group("Core\\Common\\Profiler" FILES ${Core__Common__Profiler})

set(Core__Common__QuadTree
    "quadtree.h"
    "quadtree_inline.h"
)
source_group("Core\\Common\\QuadTree" FILES ${Core__Common__QuadTree})

set(Core__Common__Random__32bit
    "random32.cpp"
    "random32.h"
)
source_group("Core\\Common\\Random\\32bit" FILES ${Core__Common__Random__32bit})

set(Core__Common__Random__weighted
    "ai/weighted_random.cpp"
    "ai/weighted_random.h"
)
source_group("Core\\Common\\Random\\weighted" FILES ${Core__Common__Random__weighted})

set(Core__Common__Registry
    "RegistryFuncs.cpp"
    "RegistryFuncs.h"
)
source_group("Core\\Common\\Registry" FILES ${Core__Common__Registry})

set(Core__Common__Shared
    "../xrServerEntities/shared_data.h"
    "new_sds.h"
    "NewZoomFlag.h"
)
source_group("Core\\Common\\Shared" FILES ${Core__Common__Shared})

set(Core__Common__SmartCast
    "../3rd_party/fast_dynamic_cast/fast_dynamic_cast.hpp"
    "../xrServerEntities/smart_cast.h"
)
source_group("Core\\Common\\SmartCast" FILES ${Core__Common__SmartCast})

set(Core__Common__StringTable
    "string_table.cpp"
    "string_table.h"
    "string_table_defs.h"
)
source_group("Core\\Common\\StringTable" FILES ${Core__Common__StringTable})

set(Core__Common__associative_vector__compare
    "../xrServerEntities/associative_vector_compare_predicate.h"
    "../xrServerEntities/associative_vector_compare_predicate_inline.h"
)
source_group("Core\\Common\\associative_vector\\compare" FILES ${Core__Common__associative_vector__compare})

set(Core__Common__associative_vector__vector
    "../xrServerEntities/associative_vector.h"
    "../xrServerEntities/associative_vector_inline.h"
)
source_group("Core\\Common\\associative_vector\\vector" FILES ${Core__Common__associative_vector__vector})

set(Core__Common__debug__make_final
    "debug_make_final.hpp"
)
source_group("Core\\Common\\debug\\make_final" FILES ${Core__Common__debug__make_final})

set(Core__Common__debug__static_cast_checked
    "static_cast_checked.hpp"
)
source_group("Core\\Common\\debug\\static_cast_checked" FILES ${Core__Common__debug__static_cast_checked})

set(Core__Server
    "../xrServerEntities/xrServer_Space.h"
    "screenshot_server.cpp"
    "screenshot_server.h"
    "xrClientsPool.cpp"
    "xrClientsPool.h"
    "xrGame.cpp"
    "xrServer.cpp"
    "xrServer.h"
    "xrServer_balance.cpp"
    "xrServer_info.cpp"
    "xrServer_info.h"
    "xrServer_updates_compressor.cpp"
    "xrServer_updates_compressor.h"
    "xrServerMapSync.cpp"
    "xrServerMapSync.h"
)
source_group("Core\\Server" FILES ${Core__Server})

set(Core__Server__Editor
    "../Include/xrRender/DrawUtils.h"
    "../xrServerEntities/ItemListTypes.h"
    "../xrServerEntities/WaveForm.h"
    "../xrServerEntities/xrEProps.h"
)
source_group("Core\\Server\\Editor" FILES ${Core__Server__Editor})

set(Core__Server__GameSpy__CdkeyDecode
    "gamespy/CdkeyDecode/base32.c"
    "gamespy/CdkeyDecode/base32.h"
    "gamespy/CdkeyDecode/cdkeydecode.c"
    "gamespy/CdkeyDecode/cdkeydecode.h"
)
source_group("Core\\Server\\GameSpy\\CdkeyDecode" FILES ${Core__Server__GameSpy__CdkeyDecode})

set(Core__Server__Games
    "../xrServerEntities/game_base_space.h"
    "game_base.cpp"
    "game_base.h"
    "game_base_kill_type.h"
    "game_base_menu_events.h"
)
source_group("Core\\Server\\Games" FILES ${Core__Server__Games})

set(Core__Server__Games__PlayerAccounts
    "account_manager.cpp"
    "account_manager.h"
    "account_manager_console.cpp"
    "account_manager_console.h"
    "account_manager_script.cpp"
    "atlas_stalkercoppc_v1.c"
    "atlas_stalkercoppc_v1.h"
    "atlas_submit_queue.cpp"
    "atlas_submit_queue.h"
    "awards_store.cpp"
    "awards_store.h"
    "best_scores_store.cpp"
    "best_scores_store.h"
    "gsc_dsigned_ltx.cpp"
    "gsc_dsigned_ltx.h"
    "login_manager.cpp"
    "login_manager.h"
    "login_manager_script.cpp"
    "mixed_delegate.h"
    "mixed_delegate_unique_tags.h"
    "player_account.cpp"
    "player_account.h"
    "profile_data_types.cpp"
    "profile_data_types.h"
    "profile_data_types_script.cpp"
    "profile_store.cpp"
    "profile_store.h"
    "profile_store_script.cpp"
    "queued_async_method.h"
    "stats_submitter.cpp"
    "stats_submitter.h"
    "stats_submitter_dsa_params.cpp"
)
source_group("Core\\Server\\Games\\PlayerAccounts" FILES ${Core__Server__Games__PlayerAccounts})

set(Core__Server__Games__client__artefact_hunt
    "game_cl_artefacthunt.cpp"
    "game_cl_artefacthunt.h"
    "game_cl_artefacthunt_snd_msg.h"
)
source_group("Core\\Server\\Games\\client\\artefact_hunt" FILES ${Core__Server__Games__client__artefact_hunt})

set(Core__Server__Games__client__base
    "game_cl_base.cpp"
    "game_cl_base.h"
    "game_cl_base_weapon_usage_statistic.cpp"
    "game_cl_base_weapon_usage_statistic.h"
    "game_cl_base_weapon_usage_statistic_save.cpp"
)
source_group("Core\\Server\\Games\\client\\base" FILES ${Core__Server__Games__client__base})

set(Core__Server__Games__client__capture_the_artefact
    "game_cl_capture_the_artefact.cpp"
    "game_cl_capture_the_artefact.h"
    "game_cl_capture_the_artefact_captions_manager.cpp"
    "game_cl_capture_the_artefact_captions_manager.h"
    "game_cl_capture_the_artefact_messages_menu.cpp"
    "game_cl_capturetheartefact_buywnd.cpp"
    "game_cl_capturetheartefact_snd_msg.h"
)
source_group("Core\\Server\\Games\\client\\capture_the_artefact" FILES ${Core__Server__Games__client__capture_the_artefact})

set(Core__Server__Games__client__deathmatch
    "game_cl_deathmatch.cpp"
    "game_cl_deathmatch.h"
    "game_cl_deathmatch_buywnd.cpp"
    "game_cl_deathmatch_snd_messages.h"
)
source_group("Core\\Server\\Games\\client\\deathmatch" FILES ${Core__Server__Games__client__deathmatch})

set(Core__Server__Games__client__mp
    "game_cl_mp.cpp"
    "game_cl_mp.h"
    "game_cl_mp_messages_menu.cpp"
    "game_cl_mp_messages_menu.h"
    "game_cl_mp_snd_messages.cpp"
    "game_cl_mp_snd_messages.h"
)
source_group("Core\\Server\\Games\\client\\mp" FILES ${Core__Server__Games__client__mp})

set(Core__Server__Games__client__mp__anticheat
    "configs_common.cpp"
    "configs_common.h"
    "configs_dump_verifyer.cpp"
    "configs_dump_verifyer.h"
    "configs_dumper.cpp"
    "configs_dumper.h"
    "mp_config_sections.cpp"
    "mp_config_sections.h"
)
source_group("Core\\Server\\Games\\client\\mp\\anticheat" FILES ${Core__Server__Games__client__mp__anticheat})

set(Core__Server__Games__client__mp__award_system
    "ammunition_groups.cpp"
    "ammunition_groups.h"
    "bone_groups.cpp"
    "bone_groups.h"
    "event_conditions_collection.cpp"
    "event_conditions_collection.h"
    "game_events_handler.h"
    "reward_event_generator.cpp"
    "reward_event_generator.h"
    "reward_manager.cpp"
    "reward_manager.h"
    "reward_snd_messages.h"
    "rewarding_events_handlers.cpp"
    "rewarding_events_handlers.h"
    "rewarding_state_events.cpp"
    "rewarding_state_events.h"
    "state_arguments_functions.cpp"
    "state_arguments_functions.h"
)
source_group("Core\\Server\\Games\\client\\mp\\award_system" FILES ${Core__Server__Games__client__mp__award_system})

set(Core__Server__Games__client__mp__award_system__event_handlers
    "best_scores_helper.cpp"
    "best_scores_helper.h"
    "reward_event_handler.h"
)
source_group("Core\\Server\\Games\\client\\mp\\award_system\\event_handlers" FILES ${Core__Server__Games__client__mp__award_system__event_handlers})

set(Core__Server__Games__client__mp__award_system__player_state
    "accumulative_states.h"
    "game_state_accumulator.cpp"
    "game_state_accumulator.h"
    "game_state_accumulator_state_register.cpp"
    "hits_store.cpp"
    "hits_store.h"
    "hits_store_inline.h"
    "kills_store.cpp"
    "kills_store.h"
    "kills_store_inline.h"
    "obsolete_queue.h"
    "obsolete_queue_inline.h"
    "player_state_param.h"
)
source_group("Core\\Server\\Games\\client\\mp\\award_system\\player_state" FILES ${Core__Server__Games__client__mp__award_system__player_state})

set(Core__Server__Games__client__mp__award_system__player_state__state_parameters
    "black_list.cpp"
    "black_list.h"
    "command_switch_counter.h"
    "double_shot_double_kill.cpp"
    "double_shot_double_kill.h"
    "faster_than_bullets_time.cpp"
    "faster_than_bullets_time.h"
    "harvest_time.cpp"
    "harvest_time.h"
    "invincible_fury.cpp"
    "invincible_fury.h"
    "killer_victim_velocity_angle.cpp"
    "killer_victim_velocity_angle.h"
    "player_spot_params.cpp"
    "player_spot_params.h"
    "player_state_achilles_heel.cpp"
    "player_state_achilles_heel.h"
    "player_state_ambassador.cpp"
    "player_state_ambassador.h"
    "player_state_ammo_elapsed.cpp"
    "player_state_ammo_elapsed.h"
    "player_state_avenger.cpp"
    "player_state_avenger.h"
    "player_state_blitzkrieg.cpp"
    "player_state_blitzkrieg.h"
    "player_state_cherub.cpp"
    "player_state_cherub.h"
    "player_state_climber.cpp"
    "player_state_climber.h"
    "player_state_mad.cpp"
    "player_state_mad.h"
    "player_state_marksman.cpp"
    "player_state_marksman.h"
    "player_state_multichampion.cpp"
    "player_state_multichampion.h"
    "player_state_opener.cpp"
    "player_state_opener.h"
    "player_state_params.cpp"
    "player_state_params.h"
    "player_state_remembrance.cpp"
    "player_state_remembrance.h"
    "player_state_skewer.cpp"
    "player_state_skewer.h"
    "player_state_toughy.cpp"
    "player_state_toughy.h"
    "player_team_win_score.cpp"
    "player_team_win_score.h"
    "silent_shots.cpp"
    "silent_shots.h"
    "sprinter_stopper.cpp"
    "sprinter_stopper.h"
    "stalker_flair.cpp"
    "stalker_flair.h"
)
source_group("Core\\Server\\Games\\client\\mp\\award_system\\player_state\\state_parameters" FILES ${Core__Server__Games__client__mp__award_system__player_state__state_parameters})

set(Core__Server__Games__client__mp__screenshots
    "screenshot_manager.cpp"
    "screenshot_manager.h"
    "screenshots_common.cpp"
    "screenshots_common.h"
    "screenshots_writer.cpp"
    "screenshots_writer.h"
)
source_group("Core\\Server\\Games\\client\\mp\\screenshots" FILES ${Core__Server__Games__client__mp__screenshots})

set(Core__Server__Games__client__single
    "game_cl_single.cpp"
    "game_cl_single.h"
)
source_group("Core\\Server\\Games\\client\\single" FILES ${Core__Server__Games__client__single})

set(Core__Server__Games__client__team_deathmatch
    "game_cl_teamdeathmatch.cpp"
    "game_cl_teamdeathmatch.h"
    "game_cl_teamdeathmatch_snd_messages.h"
)
source_group("Core\\Server\\Games\\client\\team_deathmatch" FILES ${Core__Server__Games__client__team_deathmatch})

set(Core__Server__Games__server
    "game_sv_base.cpp"
    "game_sv_base.h"
    "game_sv_base_console_vars.cpp"
    "game_sv_base_console_vars.h"
    "game_sv_event_queue.cpp"
    "game_sv_event_queue.h"
    "game_sv_item_respawner.cpp"
    "game_sv_item_respawner.h"
    "xr_time.cpp"
    "xr_time.h"
)
source_group("Core\\Server\\Games\\server" FILES ${Core__Server__Games__server})

set(Core__Server__Games__server__artefact_hunt
    "game_sv_artefacthunt.cpp"
    "game_sv_artefacthunt.h"
    "game_sv_artefacthunt_process_event.cpp"
)
source_group("Core\\Server\\Games\\server\\artefact_hunt" FILES ${Core__Server__Games__server__artefact_hunt})

set(Core__Server__Games__server__capture_the_artefact
    "game_sv_capture_the_artefact.cpp"
    "game_sv_capture_the_artefact.h"
    "game_sv_capture_the_artefact_buy_event.cpp"
    "game_sv_capture_the_artefact_myteam_impl.cpp"
    "game_sv_capture_the_artefact_process_event.cpp"
)
source_group("Core\\Server\\Games\\server\\capture_the_artefact" FILES ${Core__Server__Games__server__capture_the_artefact})

set(Core__Server__Games__server__deathmatch
    "game_sv_deathmatch.cpp"
    "game_sv_deathmatch.h"
    "game_sv_deathmatch_process_event.cpp"
)
source_group("Core\\Server\\Games\\server\\deathmatch" FILES ${Core__Server__Games__server__deathmatch})

set(Core__Server__Games__server__mp
    "cdkey_ban_list.cpp"
    "cdkey_ban_list.h"
    "game_sv_mp.cpp"
    "game_sv_mp.h"
    "game_sv_mp_team.h"
    "game_sv_mp_vote_flags.h"
)
source_group("Core\\Server\\Games\\server\\mp" FILES ${Core__Server__Games__server__mp})

set(Core__Server__Games__server__single
    "game_sv_single.cpp"
    "game_sv_single.h"
)
source_group("Core\\Server\\Games\\server\\single" FILES ${Core__Server__Games__server__single})

set(Core__Server__Games__server__team_deathmatch
    "game_sv_teamdeathmatch.cpp"
    "game_sv_teamdeathmatch.h"
    "game_sv_teamdeathmatch_process_event.cpp"
)
source_group("Core\\Server\\Games\\server\\team_deathmatch" FILES ${Core__Server__Games__server__team_deathmatch})

set(Core__Server__ID_Generator
    "id_generator.h"
)
source_group("Core\\Server\\ID_Generator" FILES ${Core__Server__ID_Generator})

set(Core__Server__ServerConnect
    "xrServer_CL_connect.cpp"
    "xrServer_CL_disconnect.cpp"
    "xrServer_Connect.cpp"
    "xrServer_Disconnect.cpp"
)
source_group("Core\\Server\\ServerConnect" FILES ${Core__Server__ServerConnect})

set(Core__Server__ServerEntities
    "../xrCore/ChooseTypes.H"
    "../xrServerEntities/gametype_chooser.cpp"
    "../xrServerEntities/gametype_chooser.h"
    "../xrServerEntities/PropertiesListTypes.h"
    "../xrServerEntities/ShapeData.h"
    "../xrServerEntities/xrServer_Factory.cpp"
    "../xrServerEntities/xrServer_Objects_Abstract.cpp"
    "../xrServerEntities/xrServer_Objects_Abstract.h"
    "../xrServerEntities/xrServer_Objects_ALife_All.h"
    "../xrServerEntities/xrServer_script_macroses.h"
)
source_group("Core\\Server\\ServerEntities" FILES ${Core__Server__ServerEntities})

set(Core__Server__ServerEntities__objects
    "../xrServerEntities/xrServer_Object_Base.cpp"
    "../xrServerEntities/xrServer_Object_Base.h"
    "../xrServerEntities/xrServer_Objects.cpp"
    "../xrServerEntities/xrServer_Objects.h"
    "../xrServerEntities/xrServer_Objects_script.cpp"
    "../xrServerEntities/xrServer_Objects_script2.cpp"
)
source_group("Core\\Server\\ServerEntities\\objects" FILES ${Core__Server__ServerEntities__objects})

set(Core__Server__ServerEntities__objects_alife
    "../xrServerEntities/xrServer_Objects_ALife.cpp"
    "../xrServerEntities/xrServer_Objects_ALife.h"
    "../xrServerEntities/xrServer_Objects_ALife_script.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_script2.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_script3.cpp"
)
source_group("Core\\Server\\ServerEntities\\objects_alife" FILES ${Core__Server__ServerEntities__objects_alife})

set(Core__Server__ServerEntities__objects_alife_items
    "../xrServerEntities/PHSynchronize.h"
    "../xrServerEntities/xrServer_Objects_ALife_Items.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_Items.h"
    "../xrServerEntities/xrServer_Objects_ALife_Items_script.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_Items_script2.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_Items_script3.cpp"
)
source_group("Core\\Server\\ServerEntities\\objects_alife_items" FILES ${Core__Server__ServerEntities__objects_alife_items})

set(Core__Server__ServerEntities__objects_alife_monsters
    "../xrServerEntities/xrServer_Objects_ALife_Monsters.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_Monsters.h"
    "../xrServerEntities/xrServer_Objects_ALife_Monsters_script.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_Monsters_script2.cpp"
    "../xrServerEntities/xrserver_objects_alife_monsters_script3.cpp"
    "../xrServerEntities/xrServer_Objects_ALife_Monsters_script4.cpp"
)
source_group("Core\\Server\\ServerEntities\\objects_alife_monsters" FILES ${Core__Server__ServerEntities__objects_alife_monsters})

set(Core__Server__ServerEntities__objects_alife_smartcover
    "../xrServerEntities/xrServer_Objects_Alife_Smartcovers.cpp"
    "../xrServerEntities/xrServer_Objects_Alife_Smartcovers.h"
    "../xrServerEntities/xrServer_Objects_Alife_Smartcovers_script.cpp"
)
source_group("Core\\Server\\ServerEntities\\objects_alife_smartcover" FILES ${Core__Server__ServerEntities__objects_alife_smartcover})

set(Core__Server__ServerEntities__script_value_container
    "../xrServerEntities/script_value_container.h"
    "../xrServerEntities/script_value_container_impl.h"
)
source_group("Core\\Server\\ServerEntities\\script_value_container" FILES ${Core__Server__ServerEntities__script_value_container})

set(Core__Server__ServerPerform
    "xrServer_perform_GameExport.cpp"
    "xrServer_perform_migration.cpp"
    "xrServer_perform_RPgen.cpp"
    "xrServer_perform_sls_default.cpp"
    "xrServer_perform_sls_load.cpp"
    "xrServer_perform_sls_save.cpp"
    "xrServer_perform_transfer.cpp"
    "xrServer_secure_messaging.cpp"
    "xrServer_sls_clear.cpp"
)
source_group("Core\\Server\\ServerPerform" FILES ${Core__Server__ServerPerform})

set(Core__Server__ServerProcess
    "xrServer_process_event.cpp"
    "xrServer_process_event_activate.cpp"
    "xrServer_process_event_destroy.cpp"
    "xrServer_process_event_ownership.cpp"
    "xrServer_process_event_reject.cpp"
    "xrServer_process_spawn.cpp"
    "xrServer_process_update.cpp"
    "xrServer_svclient_validation.cpp"
    "xrServer_svclient_validation.h"
)
source_group("Core\\Server\\ServerProcess" FILES ${Core__Server__ServerProcess})

set(Core__Server__filetransfer
    "file_transfer.cpp"
    "file_transfer.h"
    "filereceiver_node.cpp"
    "filereceiver_node.h"
    "filetransfer_common.h"
    "filetransfer_node.cpp"
    "filetransfer_node.h"
)
source_group("Core\\Server\\filetransfer" FILES ${Core__Server__filetransfer})

set(Core__Server__xrGameSpyServer
    "xrGameSpy_GameSpyFuncs.cpp"
    "xrGameSpyServer.cpp"
    "xrGameSpyServer.h"
    "xrGameSpyServer_callbacks.cpp"
    "xrGameSpyServer_callbacks.h"
)
source_group("Core\\Server\\xrGameSpyServer" FILES ${Core__Server__xrGameSpyServer})

set(Physics
    "../xrServerEntities/PHNetState.cpp"
    "../xrServerEntities/PHNetState.h"
    "ph_shell_interface.h"
    "PHShellCreator.cpp"
    "PHShellCreator.h"
    "physics_game.cpp"
    "physics_game.h"
    "PhysicsGamePars.cpp"
    "PhysicsGamePars.h"
)
source_group("Physics" FILES ${Physics})

set(Physics__CharacterSupport
    "ActivatingCharCollisionDelay.cpp"
    "ActivatingCharCollisionDelay.h"
    "animation_utils.cpp"
    "animation_utils.h"
    "character_shell_control.cpp"
    "character_shell_control.h"
    "CharacterPhysicsSupport.cpp"
    "CharacterPhysicsSupport.h"
)
source_group("Physics\\CharacterSupport" FILES ${Physics__CharacterSupport})

set(Physics__CharacterSupport__death_anims
    "death_anims.cpp"
    "death_anims.h"
    "death_anims_predicates.cpp"
)
source_group("Physics\\CharacterSupport\\death_anims" FILES ${Physics__CharacterSupport__death_anims})

set(Physics__CharacterSupport__hit_anims
    "character_hit_animations.cpp"
    "character_hit_animations.h"
    "character_hit_animations_params.h"
)
source_group("Physics\\CharacterSupport\\hit_anims" FILES ${Physics__CharacterSupport__hit_anims})

set(Physics__CharacterSupport__interactive_anims
    "interactive_animation.cpp"
    "interactive_animation.h"
    "physics_shell_animated.cpp"
    "physics_shell_animated.h"
)
source_group("Physics\\CharacterSupport\\interactive_anims" FILES ${Physics__CharacterSupport__interactive_anims})

set(Physics__CharacterSupport__interactive_motion
    "imotion_position.cpp"
    "imotion_position.h"
    "imotion_velocity.cpp"
    "imotion_velocity.h"
    "interactive_motion.cpp"
    "interactive_motion.h"
)
source_group("Physics\\CharacterSupport\\interactive_motion" FILES ${Physics__CharacterSupport__interactive_motion})

set(Physics__DamagableItem
    "DamagableItem.cpp"
    "DamagableItem.h"
)
source_group("Physics\\DamagableItem" FILES ${Physics__DamagableItem})

set(Physics__Debug
    "PHDebug.cpp"
    "PHDebug.h"
)
source_group("Physics\\Debug" FILES ${Physics__Debug})

set(Physics__Hit
    "Hit.cpp"
    "Hit.h"
)
source_group("Physics\\Hit" FILES ${Physics__Hit})

set(Physics__IK
    "ik/aint.cxx"
    "ik/aint.h"
    "ik/Dof7control.cpp"
    "ik/Dof7control.h"
    "ik/eqn.cxx"
    "ik/eqn.h"
    "ik/eulersolver.cxx"
    "ik/eulersolver.h"
    "ik/IKLimb.cpp"
    "ik/IKLimb.h"
    "ik/jtlimits.cxx"
    "ik/jtlimits.h"
    "ik/limb.cxx"
    "ik/limb.h"
    "ik/math3d.cpp"
    "ik/math3d.h"
    "ik/mathTrig.cpp"
    "ik/mathTrig.h"
    "ik_anim_state.cpp"
    "ik_anim_state.h"
    "ik_calculate_data.cpp"
    "ik_calculate_data.h"
    "ik_calculate_state.h"
    "ik_collide_data.h"
    "ik_dbg_matrix.cpp"
    "ik_dbg_matrix.h"
    "ik_foot_collider.cpp"
    "ik_foot_collider.h"
    "ik_limb_state.cpp"
    "ik_limb_state.h"
    "ik_limb_state_predict.h"
    "ik_object_shift.cpp"
    "ik_object_shift.h"
    "IKFoot.cpp"
    "IKFoot.h"
    "IKFoot_inl.h"
    "IKLimbsController.cpp"
    "IKLimbsController.h"
    "pose_extrapolation.cpp"
    "pose_extrapolation.h"
)
source_group("Physics\\IK" FILES ${Physics__IK})

set(Physics__MovementControl
    "CaptureBoneCallback.h"
    "PHMovementControl.cpp"
    "PHMovementControl.h"
    "PHMovementDynamicActivate.cpp"
)
source_group("Physics\\MovementControl" FILES ${Physics__MovementControl})

set(Physics__PHCommander
    "PHCommander.cpp"
    "PHCommander.h"
    "PHReqComparer.h"
    "PHScriptCall.cpp"
    "PHScriptCall.h"
    "PHSimpleCalls.cpp"
    "PHSimpleCalls.h"
    "PHSimpleCallsScript.cpp"
)
source_group("Physics\\PHCommander" FILES ${Physics__PHCommander})

set(Physics__PhysicsSoundPlayer
    "moving_bones_snd_player.cpp"
    "moving_bones_snd_player.h"
    "PHSoundPlayer.cpp"
    "PHSoundPlayer.h"
)
source_group("Physics\\PhysicsSoundPlayer" FILES ${Physics__PhysicsSoundPlayer})

set(Physics__animation_movement_controller
    "animation_movement_controller.cpp"
    "animation_movement_controller.h"
    "poses_blending.cpp"
    "poses_blending.h"
)
source_group("Physics\\animation_movement_controller" FILES ${Physics__animation_movement_controller})

set(Physics__scripts
    "physics_element_scripted.cpp"
    "physics_element_scripted.h"
    "physics_joint_scripted.cpp"
    "physics_joint_scripted.h"
    "physics_shell_scripted.cpp"
    "physics_shell_scripted.h"
    "physics_world_scripted.cpp"
    "physics_world_scripted.h"
)
source_group("Physics\\scripts" FILES ${Physics__scripts})

set(UI
    "ui_base.cpp"
    "ui_base.h"
    "ui_defs.h"
    "UIDialogHolder.cpp"
    "UIDialogHolder.h"
    "UIDosimeter.cpp"
    "UIDosimeter.h"
)
source_group("UI" FILES ${UI})

set(UI__Common__ImGui
    "script_imgui.h"
    "script_imgui_inline.h"
    "script_imgui_script.cpp"
)
source_group("UI\\Common\\ImGui" FILES ${UI__Common__ImGui})

set(UI__Common__Inventory
    "ui/UIActorMenu.cpp"
    "ui/UIActorMenu.h"
    "ui/UIActorMenu_action.cpp"
    "ui/UIActorMenu_script.cpp"
    "ui/UIActorMenuDeadBodySearch.cpp"
    "ui/UIActorMenuInitialize.cpp"
    "ui/UIActorMenuInventory.cpp"
    "ui/UIActorMenuTrade.cpp"
    "ui/UIActorMenuUpgrade.cpp"
    "ui/UIActorStateInfo.cpp"
    "ui/UIActorStateInfo.h"
)
source_group("UI\\Common\\Inventory" FILES ${UI__Common__Inventory})

set(UI__Common__InventoryUtilities
    "ui/UIHelper.cpp"
    "ui/UIHelper.h"
    "ui/UIInventoryUtilities.cpp"
    "ui/UIInventoryUtilities.h"
)
source_group("UI\\Common\\InventoryUtilities" FILES ${UI__Common__InventoryUtilities})

set(UI__Common__InventoryWnd__InventoryUpgrade
    "ui/UIInventoryUpgradeWnd.cpp"
    "ui/UIInventoryUpgradeWnd.h"
    "ui/UIInventoryUpgradeWnd_add.cpp"
    "ui/UIInvUpgrade.cpp"
    "ui/UIInvUpgrade.h"
    "ui/UIInvUpgradeInfo.cpp"
    "ui/UIInvUpgradeInfo.h"
    "ui/UIInvUpgradeProperty.cpp"
    "ui/UIInvUpgradeProperty.h"
)
source_group("UI\\Common\\InventoryWnd\\InventoryUpgrade" FILES ${UI__Common__InventoryWnd__InventoryUpgrade})

set(UI__Common__MainIngame
    "ui/UICarPanel.cpp"
    "ui/UICarPanel.h"
    "ui/UIHudStatesWnd.cpp"
    "ui/UIHudStatesWnd.h"
    "ui/UIMainIngameWnd.cpp"
    "ui/UIMainIngameWnd.h"
    "ui/UIMessagesWindow.cpp"
    "ui/UIMessagesWindow.h"
    "ui/UIMoneyIndicator.cpp"
    "ui/UIMoneyIndicator.h"
    "ui/UIMotionIcon.cpp"
    "ui/UIMotionIcon.h"
    "ui/UIPdaMsgListItem.cpp"
    "ui/UIPdaMsgListItem.h"
    "UIZoneMap.cpp"
    "UIZoneMap.h"
)
source_group("UI\\Common\\MainIngame" FILES ${UI__Common__MainIngame})

set(UI__Common__MainMenu
    "MainMenu.cpp"
    "MainMenu.h"
    "ui/MMSound.cpp"
    "ui/MMSound.h"
    "ui/UIMMShniaga.cpp"
    "ui/UIMMShniaga.h"
)
source_group("UI\\Common\\MainMenu" FILES ${UI__Common__MainMenu})

set(UI__Common__MainMenu__KeyBinding
    "ui/UIEditKeyBind.cpp"
    "ui/UIEditKeyBind.h"
    "ui/UIKeyBinding.cpp"
    "ui/UIKeyBinding.h"
)
source_group("UI\\Common\\MainMenu\\KeyBinding" FILES ${UI__Common__MainMenu__KeyBinding})

set(UI__Common__OptionsConsoleCommands
    "ui/UIOptConCom.cpp"
    "ui/UIOptConCom.h"
)
source_group("UI\\Common\\OptionsConsoleCommands" FILES ${UI__Common__OptionsConsoleCommands})

set(UI__Common__OptionsItem
    "ui/UIOptionsItem.cpp"
    "ui/UIOptionsItem.h"
    "ui/UIOptionsManager.cpp"
    "ui/UIOptionsManager.h"
    "ui/UIOptionsManagerScript.cpp"
    "ui/UIOptionsManagerScript.h"
)
source_group("UI\\Common\\OptionsItem" FILES ${UI__Common__OptionsItem})

set(UI__Common__PDA
    "ui/UIPdaWnd.cpp"
    "ui/UIPdaWnd.h"
)
source_group("UI\\Common\\PDA" FILES ${UI__Common__PDA})

set(UI__Common__PDA__MAP
    "map_spot.cpp"
    "map_spot.h"
    "ui/map_hint.cpp"
    "ui/map_hint.h"
    "ui/UIMap.cpp"
    "ui/UIMap.h"
    "ui/UIMapWnd.cpp"
    "ui/UIMapWnd.h"
    "ui/UIMapWnd2.cpp"
    "ui/UIMapWndActions.cpp"
    "ui/UIMapWndActions.h"
    "ui/UIMapWndActionsSpace.h"
)
source_group("UI\\Common\\PDA\\MAP" FILES ${UI__Common__PDA__MAP})

set(UI__Common__PDA__Statistics__Rankings
    "ui/UIAchievements.cpp"
    "ui/UIAchievements.h"
    "ui/UIRankingsCoC.cpp"
    "ui/UIRankingsCoC.h"
    "ui/UIRankingWnd.cpp"
    "ui/UIRankingWnd.h"
)
source_group("UI\\Common\\PDA\\Statistics & Rankings" FILES ${UI__Common__PDA__Statistics__Rankings})

set(UI__Common__PDA__Tasks
    "ui/UIMapLegend.cpp"
    "ui/UIMapLegend.h"
    "ui/UISecondTaskWnd.cpp"
    "ui/UISecondTaskWnd.h"
    "ui/UITaskWnd.cpp"
    "ui/UITaskWnd.h"
)
source_group("UI\\Common\\PDA\\Tasks" FILES ${UI__Common__PDA__Tasks})

set(UI__Common__PDA__logs
    "ui/UILogsWnd.cpp"
    "ui/UILogsWnd.h"
)
source_group("UI\\Common\\PDA\\logs" FILES ${UI__Common__PDA__logs})

set(UI__Common__PDA__logs__News
    "ui/UINewsItemWnd.cpp"
    "ui/UINewsItemWnd.h"
)
source_group("UI\\Common\\PDA\\logs\\News" FILES ${UI__Common__PDA__logs__News})

set(UI__Common__TALK
    "ui/UITalkDialogWnd.cpp"
    "ui/UITalkDialogWnd.h"
    "ui/UITalkWnd.cpp"
    "ui/UITalkWnd.h"
)
source_group("UI\\Common\\TALK" FILES ${UI__Common__TALK})

set(UI__Common___Debug_Fonts
    "ui/UIDebugFonts.h"
)
if(ENABLE_DEBUG_OLD_RUNTIME)
    list(APPEND UI__Common___Debug_Fonts ui/UIDebugFonts.cpp)
endif()
source_group("UI\\Common\\_Debug Fonts" FILES ${UI__Common___Debug_Fonts})

set(UI__Common__ui-item-infos
    "ui/ui_af_params.cpp"
    "ui/ui_af_params.h"
    "ui/UIBoosterInfo.cpp"
    "ui/UIBoosterInfo.h"
    "ui/UIItemInfo.cpp"
    "ui/UIItemInfo.h"
    "ui/UIOutfitInfo.cpp"
    "ui/UIOutfitInfo.h"
    "ui/UIWpnParams.cpp"
    "ui/UIWpnParams.h"
)
source_group("UI\\Common\\ui-item-infos" FILES ${UI__Common__ui-item-infos})

set(UI__Common__ui-item-infos__CharacterInfo
    "ui/UICharacterInfo.cpp"
    "ui/UICharacterInfo.h"
)
source_group("UI\\Common\\ui-item-infos\\CharacterInfo" FILES ${UI__Common__ui-item-infos__CharacterInfo})

set(UI__Cursor
    "HUDCrosshair.cpp"
    "HUDCrosshair.h"
    "HUDRecon.cpp"
    "HUDRecon.h"
    "HUDTarget.cpp"
    "HUDTarget.h"
    "UICursor.cpp"
    "UICursor.h"
)
source_group("UI\\Cursor" FILES ${UI__Cursor})

set(UI__GameTypes__ArtefactHunt
    "UIGameAHunt.cpp"
    "UIGameAHunt.h"
)
source_group("UI\\GameTypes\\ArtefactHunt" FILES ${UI__GameTypes__ArtefactHunt})

set(UI__GameTypes__CaptureTheArtefact
    "UIGameCTA.cpp"
    "UIGameCTA.h"
)
source_group("UI\\GameTypes\\CaptureTheArtefact" FILES ${UI__GameTypes__CaptureTheArtefact})

set(UI__GameTypes__Deathmatch
    "ui/UIRankIndicator.cpp"
    "ui/UIRankIndicator.h"
    "ui/UIVoteStatusWnd.cpp"
    "ui/UIVoteStatusWnd.h"
    "UIGameDM.cpp"
    "UIGameDM.h"
)
source_group("UI\\GameTypes\\Deathmatch" FILES ${UI__GameTypes__Deathmatch})

set(UI__GameTypes__GameCustom
    "UIGameCustom.cpp"
    "UIGameCustom.h"
    "UIGameCustom_script.cpp"
    "UIGameMP.cpp"
    "UIGameMP.h"
)
source_group("UI\\GameTypes\\GameCustom" FILES ${UI__GameTypes__GameCustom})

set(UI__GameTypes__Single
    "UIGameSP.cpp"
    "UIGameSP.h"
)
source_group("UI\\GameTypes\\Single" FILES ${UI__GameTypes__Single})

set(UI__GameTypes__TeamDeathmatch
    "UIGameTDM.cpp"
    "UIGameTDM.h"
)
source_group("UI\\GameTypes\\TeamDeathmatch" FILES ${UI__GameTypes__TeamDeathmatch})

set(UI__HUD
    "HitMarker.cpp"
    "HitMarker.h"
    "HUDManager.cpp"
    "HUDManager.h"
)
source_group("UI\\HUD" FILES ${UI__HUD})

set(UI__Multiplayer__Achivements
    "UIAchivementsIndicator.cpp"
    "UIAchivementsIndicator.h"
)
source_group("UI\\Multiplayer\\Achivements" FILES ${UI__Multiplayer__Achivements})

set(UI__Multiplayer__AdminMenu
    "ui/UIMPAdminMenu.cpp"
    "ui/UIMPAdminMenu.h"
    "ui/UIMPChangeMapAdm.cpp"
    "ui/UIMPChangeMapAdm.h"
    "ui/UIMPPlayersAdm.cpp"
    "ui/UIMPPlayersAdm.h"
    "ui/UIMPServerAdm.cpp"
    "ui/UIMPServerAdm.h"
)
source_group("UI\\Multiplayer\\AdminMenu" FILES ${UI__Multiplayer__AdminMenu})

set(UI__Multiplayer__BuyWeaponWnd
    "ui/UIBuyWndBase.h"
    "ui/UIBuyWndShared.cpp"
    "ui/UIBuyWndShared.h"
    "ui/UIMpItemsStoreWnd.cpp"
    "ui/UIMpItemsStoreWnd.h"
    "ui/UIMpTradeWnd.cpp"
    "ui/UIMpTradeWnd.h"
    "ui/UIMpTradeWnd_init.cpp"
    "ui/UIMpTradeWnd_items.cpp"
    "ui/UIMpTradeWnd_misc.cpp"
    "ui/UIMpTradeWnd_trade.cpp"
    "ui/UIMpTradeWnd_wpn.cpp"
)
source_group("UI\\Multiplayer\\BuyWeaponWnd" FILES ${UI__Multiplayer__BuyWeaponWnd})

set(UI__Multiplayer__BuyWeaponWnd__TAB
    "ui/UIBuyWeaponTab.cpp"
    "ui/UIBuyWeaponTab.h"
    "ui/UITabButtonMP.cpp"
    "ui/UITabButtonMP.h"
)
source_group("UI\\Multiplayer\\BuyWeaponWnd\\TAB" FILES ${UI__Multiplayer__BuyWeaponWnd__TAB})

set(UI__Multiplayer__BuyWeaponWnd__rank_restrictions
    "ui/Restrictions.cpp"
    "ui/Restrictions.h"
)
source_group("UI\\Multiplayer\\BuyWeaponWnd\\rank_restrictions" FILES ${UI__Multiplayer__BuyWeaponWnd__rank_restrictions})

set(UI__Multiplayer__DemoPlayControl
    "ui/UIDemoPlayControl.cpp"
    "ui/UIDemoPlayControl.h"
)
source_group("UI\\Multiplayer\\DemoPlayControl" FILES ${UI__Multiplayer__DemoPlayControl})

set(UI__Multiplayer__HUD__Chat
    "ui/UIChatWnd.cpp"
    "ui/UIChatWnd.h"
)
source_group("UI\\Multiplayer\\HUD\\Chat" FILES ${UI__Multiplayer__HUD__Chat})

set(UI__Multiplayer__HUD__GameLog
    "ui/UIGameLog.cpp"
    "ui/UIGameLog.h"
)
source_group("UI\\Multiplayer\\HUD\\GameLog" FILES ${UI__Multiplayer__HUD__GameLog})

set(UI__Multiplayer__HUD__SpeechMenu
    "ui/UISpeechMenu.cpp"
    "ui/UISpeechMenu.h"
)
source_group("UI\\Multiplayer\\HUD\\SpeechMenu" FILES ${UI__Multiplayer__HUD__SpeechMenu})

set(UI__Multiplayer__HUD__Stats
    "ui/UIStats.cpp"
    "ui/UIStats.h"
    "ui/UIStatsPlayerInfo.cpp"
    "ui/UIStatsPlayerInfo.h"
    "ui/UIStatsPlayerList.cpp"
    "ui/UIStatsPlayerList.h"
)
source_group("UI\\Multiplayer\\HUD\\Stats" FILES ${UI__Multiplayer__HUD__Stats})

set(UI__Multiplayer__HUD__Stats__TeamStates
    "UIPanelsClassFactory.cpp"
    "UIPanelsClassFactory.h"
    "UIPlayerItem.cpp"
    "UIPlayerItem.h"
    "UITeamHeader.cpp"
    "UITeamHeader.h"
    "UITeamPanels.cpp"
    "UITeamPanels.h"
    "UITeamState.cpp"
    "UITeamState.h"
)
source_group("UI\\Multiplayer\\HUD\\Stats\\TeamStates" FILES ${UI__Multiplayer__HUD__Stats__TeamStates})

set(UI__Multiplayer__HUD__Stats__icons
    "ui/UIStatsIcon.cpp"
    "ui/UIStatsIcon.h"
)
source_group("UI\\Multiplayer\\HUD\\Stats\\icons" FILES ${UI__Multiplayer__HUD__Stats__icons})

set(UI__Multiplayer__HUD__common
    "ui/KillMessageStruct.h"
    "ui/UIPdaKillMessage.cpp"
    "ui/UIPdaKillMessage.h"
)
source_group("UI\\Multiplayer\\HUD\\common" FILES ${UI__Multiplayer__HUD__common})

set(UI__Multiplayer__MM_MP__CDkey
    "player_name_modifyer.cpp"
    "player_name_modifyer.h"
    "ui/UICDkey.cpp"
    "ui/UICDkey.h"
)
source_group("UI\\Multiplayer\\MM_MP\\CDkey" FILES ${UI__Multiplayer__MM_MP__CDkey})

set(UI__Multiplayer__MM_MP__MapList
    "ui/UIMapList.cpp"
    "ui/UIMapList.h"
)
source_group("UI\\Multiplayer\\MM_MP\\MapList" FILES ${UI__Multiplayer__MM_MP__MapList})

set(UI__Multiplayer__MM_MP__ServerList
    "ui/ServerList.cpp"
    "ui/ServerList.h"
    "ui/ServerList_GameSpy_func.cpp"
    "ui/UIListItemServer.cpp"
    "ui/UIListItemServer.h"
)
source_group("UI\\Multiplayer\\MM_MP\\ServerList" FILES ${UI__Multiplayer__MM_MP__ServerList})

set(UI__Multiplayer__MM_MP__TeamInfo
    "ui/TeamInfo.cpp"
    "ui/TeamInfo.h"
)
source_group("UI\\Multiplayer\\MM_MP\\TeamInfo" FILES ${UI__Multiplayer__MM_MP__TeamInfo})

set(UI__Multiplayer__Voting
    "ui/ChangeWeatherDialog.cpp"
    "ui/ChangeWeatherDialog.hpp"
    "ui/UIChangeMap.cpp"
    "ui/UIChangeMap.h"
    "ui/UIKickPlayer.cpp"
    "ui/UIKickPlayer.h"
    "ui/UITextVote.cpp"
    "ui/UITextVote.h"
    "ui/UIVote.cpp"
    "ui/UIVote.h"
    "ui/UIVotingCategory.cpp"
    "ui/UIVotingCategory.h"
)
source_group("UI\\Multiplayer\\Voting" FILES ${UI__Multiplayer__Voting})

set(UI__Multiplayer__team_skin_info__MapDesc
    "ui/UIMapDesc.cpp"
    "ui/UIMapDesc.h"
)
source_group("UI\\Multiplayer\\team_skin_info\\MapDesc" FILES ${UI__Multiplayer__team_skin_info__MapDesc})

set(UI__Multiplayer__team_skin_info__MapDesc__MapInfo
    "ui/UIMapInfo.cpp"
    "ui/UIMapInfo.h"
    "ui/UIMapInfo_script.cpp"
)
source_group("UI\\Multiplayer\\team_skin_info\\MapDesc\\MapInfo" FILES ${UI__Multiplayer__team_skin_info__MapDesc__MapInfo})

set(UI__Multiplayer__team_skin_info__ServerInfo
    "ui/UIServerInfo.cpp"
    "ui/UIServerInfo.h"
)
source_group("UI\\Multiplayer\\team_skin_info\\ServerInfo" FILES ${UI__Multiplayer__team_skin_info__ServerInfo})

set(UI__Multiplayer__team_skin_info__SkinSelector
    "ui/UISkinSelector.cpp"
    "ui/UISkinSelector.h"
    "ui/UIStatix.cpp"
    "ui/UIStatix.h"
)
source_group("UI\\Multiplayer\\team_skin_info\\SkinSelector" FILES ${UI__Multiplayer__team_skin_info__SkinSelector})

set(UI__Multiplayer__team_skin_info__Spawn
    "ui/UISpawnWnd.cpp"
    "ui/UISpawnWnd.h"
)
source_group("UI\\Multiplayer\\team_skin_info\\Spawn" FILES ${UI__Multiplayer__team_skin_info__Spawn})

set(UI__Tutorial
    "ui/UIGameTutorial.cpp"
    "ui/UIGameTutorial.h"
    "ui/UIGameTutorialSimpleItem.cpp"
    "ui/UIGameTutorialVideoItem.cpp"
)
source_group("UI\\Tutorial" FILES ${UI__Tutorial})

set(UI__UIWindows
    "callback_info.h"
    "ui/uiabstract.h"
    "ui/UIMessages.h"
    "ui/UIWndCallback.cpp"
    "ui/UIWndCallback.h"
)
source_group("UI\\UIWindows" FILES ${UI__UIWindows})

set(UI__UIWindows__Buttons
    "ui/UI3tButton.cpp"
    "ui/UI3tButton.h"
    "ui/UIBtnHint.cpp"
    "ui/UIBtnHint.h"
    "ui/UIButton.cpp"
    "ui/UIButton.h"
    "ui/UIButton_script.cpp"
    "ui/UICheckButton.cpp"
    "ui/UICheckButton.h"
    "ui/UIRadioButton.cpp"
    "ui/UIRadioButton.h"
)
source_group("UI\\UIWindows\\Buttons" FILES ${UI__UIWindows__Buttons})

set(UI__UIWindows__ComboBox
    "ui/UIComboBox.cpp"
    "ui/UIComboBox.h"
    "ui/UIComboBox_script.cpp"
)
source_group("UI\\UIWindows\\ComboBox" FILES ${UI__UIWindows__ComboBox})

set(UI__UIWindows__DragDrop
    "ui/UICellCustomItems.cpp"
    "ui/UICellCustomItems.h"
    "ui/UICellItem.cpp"
    "ui/UICellItem.h"
    "ui/UICellItemFactory.cpp"
    "ui/UICellItemFactory.h"
    "ui/UIDragDropListEx.cpp"
    "ui/UIDragDropListEx.h"
    "ui/UIDragDropReferenceList.cpp"
    "ui/UIDragDropReferenceList.h"
)
source_group("UI\\UIWindows\\DragDrop" FILES ${UI__UIWindows__DragDrop})

set(UI__UIWindows__EditBox
    "ui/UIEditBox.cpp"
    "ui/UIEditBox.h"
    "ui/UIEditBoxEx.cpp"
    "ui/UIEditBoxEx.h"
)
source_group("UI\\UIWindows\\EditBox" FILES ${UI__UIWindows__EditBox})

set(UI__UIWindows__EditBox__customEB
    "ui/UICustomEdit.cpp"
    "ui/UICustomEdit.h"
    "ui/UIEditBox_script.cpp"
)
source_group("UI\\UIWindows\\EditBox\\customEB" FILES ${UI__UIWindows__EditBox__customEB})

set(UI__UIWindows__Hint
    "ui/UIHint.cpp"
    "ui/UIHint.h"
)
source_group("UI\\UIWindows\\Hint" FILES ${UI__UIWindows__Hint})

set(UI__UIWindows__InteractiveBackground
    "ui/UI_IB_Static.cpp"
    "ui/UI_IB_Static.h"
    "ui/UIInteractiveBackground.h"
)
source_group("UI\\UIWindows\\InteractiveBackground" FILES ${UI__UIWindows__InteractiveBackground})

set(UI__UIWindows__Lines
    "ui/UILine.cpp"
    "ui/UILine.h"
    "ui/UILines.cpp"
    "ui/UILines.h"
    "ui/uilinestd.h"
    "ui/UISubLine.cpp"
    "ui/UISubLine.h"
)
source_group("UI\\UIWindows\\Lines" FILES ${UI__UIWindows__Lines})

set(UI__UIWindows__ListBox
    "ui/UIListBox.cpp"
    "ui/UIListBox.h"
    "ui/UIListBox_script.cpp"
    "ui/UIListBoxItem.cpp"
    "ui/UIListBoxItem.h"
    "ui/UIListBoxItemMsgChain.cpp"
    "ui/UIListBoxItemMsgChain.h"
)
source_group("UI\\UIWindows\\ListBox" FILES ${UI__UIWindows__ListBox})

set(UI__UIWindows__MessageBox
    "ui/UIMessageBox.cpp"
    "ui/UIMessageBox.h"
    "ui/UIMessageBox_script.cpp"
    "ui/UIMessageBoxEx.cpp"
    "ui/UIMessageBoxEx.h"
)
source_group("UI\\UIWindows\\MessageBox" FILES ${UI__UIWindows__MessageBox})

set(UI__UIWindows__ProgressBar
    "ui/UIDoubleProgressBar.cpp"
    "ui/UIDoubleProgressBar.h"
    "ui/UIProgressBar.cpp"
    "ui/UIProgressBar.h"
    "ui/UIProgressBar_script.cpp"
    "ui/UIProgressShape.cpp"
    "ui/UIProgressShape.h"
)
source_group("UI\\UIWindows\\ProgressBar" FILES ${UI__UIWindows__ProgressBar})

set(UI__UIWindows__PropertiesBox
    "ui/UIPropertiesBox.cpp"
    "ui/UIPropertiesBox.h"
    "ui/UIPropertiesBox_script.cpp"
)
source_group("UI\\UIWindows\\PropertiesBox" FILES ${UI__UIWindows__PropertiesBox})

set(UI__UIWindows__ScriptWnd
    "ui/UIScriptWnd.cpp"
    "ui/UIScriptWnd.h"
    "ui/UIScriptWnd_script.cpp"
    "ui/uiscriptwnd_script.h"
    "ui/uiscriptwnd_script2.cpp"
)
source_group("UI\\UIWindows\\ScriptWnd" FILES ${UI__UIWindows__ScriptWnd})

set(UI__UIWindows__ScrollBar
    "ui/UIFixedScrollBar.cpp"
    "ui/UIFixedScrollBar.h"
    "ui/UIScrollBar.cpp"
    "ui/UIScrollBar.h"
    "ui/UIScrollBox.cpp"
    "ui/UIScrollBox.h"
)
source_group("UI\\UIWindows\\ScrollBar" FILES ${UI__UIWindows__ScrollBar})

set(UI__UIWindows__ScrollView
    "ui/UIScrollView.cpp"
    "ui/UIScrollView.h"
)
source_group("UI\\UIWindows\\ScrollView" FILES ${UI__UIWindows__ScrollView})

set(UI__UIWindows__SpinBox
    "ui/UICustomSpin.cpp"
    "ui/UICustomSpin.h"
    "ui/UISpinNum.cpp"
    "ui/UISpinNum.h"
    "ui/UISpinText.cpp"
    "ui/UISpinText.h"
)
source_group("UI\\UIWindows\\SpinBox" FILES ${UI__UIWindows__SpinBox})

set(UI__UIWindows__Static
    "ui/UIAnimatedStatic.cpp"
    "ui/UIAnimatedStatic.h"
    "ui/UILanimController.cpp"
    "ui/UILanimController.h"
    "ui/UIStatic.cpp"
    "ui/UIStatic.h"
    "ui/UIStatic_script.cpp"
    "UIStaticItem.cpp"
    "UIStaticItem.h"
)
source_group("UI\\UIWindows\\Static" FILES ${UI__UIWindows__Static})

set(UI__UIWindows__TabControl
    "ui/UITabButton.cpp"
    "ui/UITabButton.h"
    "ui/UITabControl.cpp"
    "ui/UITabControl.h"
    "ui/UITabControl_script.cpp"
)
source_group("UI\\UIWindows\\TabControl" FILES ${UI__UIWindows__TabControl})

set(UI__UIWindows__TrackBar
    "ui/UITrackBar.cpp"
    "ui/UITrackBar.h"
    "ui/UITrackButton.cpp"
    "ui/UITrackButton.h"
)
source_group("UI\\UIWindows\\TrackBar" FILES ${UI__UIWindows__TrackBar})

set(UI__UIWindows__Windows
    "ui/UIDialogWnd.cpp"
    "ui/UIDialogWnd.h"
    "ui/UIFrameLineWnd.cpp"
    "ui/UIFrameLineWnd.h"
    "ui/UIFrameWindow.cpp"
    "ui/UIFrameWindow.h"
    "ui/UIWindow.cpp"
    "ui/UIWindow.h"
    "ui/UIWindow_script.cpp"
)
source_group("UI\\UIWindows\\Windows" FILES ${UI__UIWindows__Windows})

set(UI__UIWindows__XML
    "ui/UITextureMaster.cpp"
    "ui/UITextureMaster.h"
    "ui/UIXmlInit.cpp"
    "ui/UIXmlInit.h"
    "ui/xrUIXmlParser.cpp"
    "ui/xrUIXmlParser.h"
)
source_group("UI\\UIWindows\\XML" FILES ${UI__UIWindows__XML})

set(UI__UIWindows__arrow
    "ui/ui_arrow.cpp"
    "ui/ui_arrow.h"
)
source_group("UI\\UIWindows\\arrow" FILES ${UI__UIWindows__arrow})

set(ALL_FILES
    ${no_group_source_files}
    ${AI}
    ${AI__AComponents__DamageManager}
    ${AI__AComponents__DecisionManagement}
    ${AI__AComponents__DecisionManagement__ActionManagement}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionBase}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionBase__ActionScriptBase}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionBase__ScriptActionWrapper}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction__ActionPlannerActionScript}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlannerAction__ScriptActionPlannerActionWrapper}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner__ActionPlannerScript}
    ${AI__AComponents__DecisionManagement__ActionManagement__ActionPlanner__ScriptActionPlannerWrapper}
    ${AI__AComponents__DecisionManagement__ActionManagement__PropertyStorage}
    ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator}
    ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__ScriptPropertyEvaluatorWrapper}
    ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__const}
    ${AI__AComponents__DecisionManagement__ActionManagement__WorldPropertyEvaluator__member}
    ${AI__AComponents__MaterialManager}
    ${AI__AComponents__MemoryManager}
    ${AI__AComponents__MemoryManager__clsuterized_data_managers__DangerManager}
    ${AI__AComponents__MemoryManager__clsuterized_data_managers__DangerManager__danger_object}
    ${AI__AComponents__MemoryManager__clsuterized_data_managers__EnemyManager}
    ${AI__AComponents__MemoryManager__clsuterized_data_managers__ItemManager}
    ${AI__AComponents__MemoryManager__clsuterized_data_managers__ObjectManager}
    ${AI__AComponents__MemoryManager__raw_data_managers__HitMemoryManager}
    ${AI__AComponents__MemoryManager__raw_data_managers__SoundMemoryManager}
    ${AI__AComponents__MemoryManager__raw_data_managers__SoundMemoryManager__SoundUserDataVisitor}
    ${AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager}
    ${AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager__vision_client}
    ${AI__AComponents__MemoryManager__raw_data_managers__VisualMemoryManager__visual_memory_params}
    ${AI__AComponents__MovementManager}
    ${AI__AComponents__MovementManager__LocationManager}
    ${AI__AComponents__MovementManager__LocationSelectors__AbstractLocationSelector}
    ${AI__AComponents__MovementManager__LocationSelectors__GameLocationSelector}
    ${AI__AComponents__MovementManager__LocationSelectors__LevelLocationSelector}
    ${AI__AComponents__MovementManager__PathManagers__AbstractPathManager}
    ${AI__AComponents__MovementManager__PathManagers__DetailPathManager}
    ${AI__AComponents__MovementManager__PathManagers__GamePathManager}
    ${AI__AComponents__MovementManager__PathManagers__LevelPathManager}
    ${AI__AComponents__MovementManager__PathManagers__PatrolPathManager}
    ${AI__AComponents__MovementManager__RestrictedObject}
    ${AI__AComponents__ObjectHandler}
    ${AI__AComponents__ObjectHandler__planner}
    ${AI__AComponents__ObjectHandler__planner__actions}
    ${AI__AComponents__ObjectHandler__planner__properties}
    ${AI__AComponents__ProblemSolver}
    ${AI__AComponents__ProblemSolver__condition_state}
    ${AI__AComponents__ProblemSolver__condition_state__ScriptWorldState}
    ${AI__AComponents__ProblemSolver__operator_abstract}
    ${AI__AComponents__ProblemSolver__operator_condition}
    ${AI__AComponents__ProblemSolver__operator_condition__ScriptWorldProperty}
    ${AI__AComponents__SetupManager}
    ${AI__AComponents__SightManager}
    ${AI__AComponents__SightManager__aimers__base}
    ${AI__AComponents__SightManager__aimers__bone}
    ${AI__AComponents__SightManager__aimers__weapon}
    ${AI__AComponents__SightManager__control_action}
    ${AI__AComponents__SightManager__sight_action}
    ${AI__AComponents__SightManager__sight_control_action}
    ${AI__AComponents__SoundPlayer}
    ${AI__AComponents__SoundPlayer__sound_collection_storage}
    ${AI__AComponents__SpaceRestrictionManager}
    ${AI__AComponents__SpaceRestrictionManager__SpaceRestriction}
    ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder}
    ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionAbstract}
    ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionBase}
    ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionBridge}
    ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionComposition}
    ${AI__AComponents__SpaceRestrictionManager__SpaceRestrictionHolder__SpaceRestrictionShape}
    ${AI__AComponents__Step_Manager}
    ${AI__AComponents__doors_manager}
    ${AI__AComponents__doors_manager__actor}
    ${AI__AComponents__doors_manager__door}
    ${AI__AComponents__doors_manager__manager}
    ${AI__AComponents__moving_objects}
    ${AI__AComponents__moving_objects__moving_object}
    ${AI__AComponents__moving_objects__obstacles_query}
    ${AI__ACover}
    ${AI__ACover__cover_point}
    ${AI__ACover__smart_cover__cover}
    ${AI__ACover__smart_cover__detail}
    ${AI__ACover__smart_cover__object}
    ${AI__ACover__smart_cover__storage}
    ${AI__ACover__smart_cover__storage__description}
    ${AI__ACover__smart_cover__storage__description__loophole}
    ${AI__ACover__smart_cover__storage__description__loophole__action}
    ${AI__ACover__smart_cover__storage__description__transitions__animation}
    ${AI__ACover__smart_cover__storage__description__transitions__transition}
    ${AI__ADebug}
    ${AI__AEval__functions__base}
    ${AI__AEval__functions__patterns}
    ${AI__AEval__functions__primary}
    ${AI__AEval__storage}
    ${AI__AGroup__agent_manager}
    ${AI__AGroup__agent_manager__agent_corpse_manager}
    ${AI__AGroup__agent_manager__agent_corpse_manager__member_corpse}
    ${AI__AGroup__agent_manager__agent_enemy_manager}
    ${AI__AGroup__agent_manager__agent_enemy_manager__member_enemy}
    ${AI__AGroup__agent_manager__agent_explosive_manager}
    ${AI__AGroup__agent_manager__agent_explosive_manager__danger_explosive}
    ${AI__AGroup__agent_manager__agent_location_manager}
    ${AI__AGroup__agent_manager__agent_location_manager__danger_cover_location}
    ${AI__AGroup__agent_manager__agent_location_manager__danger_location}
    ${AI__AGroup__agent_manager__agent_location_manager__danger_object_location}
    ${AI__AGroup__agent_manager__agent_member_manager}
    ${AI__AGroup__agent_manager__agent_member_manager__member_order}
    ${AI__AGroup__agent_manager__agent_memory_manager}
    ${AI__AGroup__agent_manager__agent_planner}
    ${AI__AGroup__agent_manager__agent_planner__actions}
    ${AI__AGroup__agent_manager__agent_planner__properties}
    ${AI__ALife}
    ${AI__ALife__interaction_manager}
    ${AI__ALife__interaction_manager__combat_manager}
    ${AI__ALife__interaction_manager__communication_manager}
    ${AI__ALife__inventory_upgrade}
    ${AI__ALife__inventory_upgrade__property}
    ${AI__ALife__inventory_upgrade__upgrade}
    ${AI__ALife__inventory_upgrade__upgrade_base}
    ${AI__ALife__inventory_upgrade__upgrade_group}
    ${AI__ALife__inventory_upgrade__upgrade_root}
    ${AI__ALife__saved_game_wrapper}
    ${AI__ALife__server_entities__anomalous_zone}
    ${AI__ALife__server_entities__creature_abstract}
    ${AI__ALife__server_entities__dynamic_object}
    ${AI__ALife__server_entities__group_abstract}
    ${AI__ALife__server_entities__human}
    ${AI__ALife__server_entities__human__brain}
    ${AI__ALife__server_entities__human__object_handler}
    ${AI__ALife__server_entities__monster_abstract}
    ${AI__ALife__server_entities__monster_abstract__brain}
    ${AI__ALife__server_entities__monster_abstract__movement_manager}
    ${AI__ALife__server_entities__monster_abstract__movement_manager__detail_path_manager}
    ${AI__ALife__server_entities__monster_abstract__movement_manager__movement_manager_holder}
    ${AI__ALife__server_entities__monster_abstract__movement_manager__patrol_path_manager}
    ${AI__ALife__server_entities__object}
    ${AI__ALife__server_entities__online_offline_group}
    ${AI__ALife__server_entities__online_offline_group__brain}
    ${AI__ALife__server_entities__smart_zone}
    ${AI__ALife__server_entities__trader}
    ${AI__ALife__server_entities__trader_abstract}
    ${AI__ALife__simulator_base}
    ${AI__ALife__simulator_base__header}
    ${AI__ALife__simulator_base__registries__abstract_registry}
    ${AI__ALife__simulator_base__registries__graph_registry}
    ${AI__ALife__simulator_base__registries__graph_registry__level_registry}
    ${AI__ALife__simulator_base__registries__group_registry}
    ${AI__ALife__simulator_base__registries__object_registry}
    ${AI__ALife__simulator_base__registries__safe_map_iterator}
    ${AI__ALife__simulator_base__registries__schedule_registry}
    ${AI__ALife__simulator_base__registries__smart_terrain_registry}
    ${AI__ALife__simulator_base__registries__spawn_registry}
    ${AI__ALife__simulator_base__registries__spawn_registry__header}
    ${AI__ALife__simulator_base__registries__spawn_registry__server_entity_wrapper}
    ${AI__ALife__simulator_base__registries__story_registry}
    ${AI__ALife__simulator_base__registry_container}
    ${AI__ALife__simulator_base__smart_terrain_task}
    ${AI__ALife__simulator_base__time_manager}
    ${AI__ALife__update_manager}
    ${AI__ALife__update_manager__storage_manager}
    ${AI__ALife__update_manager__surge_manager}
    ${AI__ALife__update_manager__switch_manager}
    ${AI__AMonsters__common__base_monster}
    ${AI__AMonsters__common__components}
    ${AI__AMonsters__common__components__Abilities__Controlled}
    ${AI__AMonsters__common__components__Abilities__Energy_Holder}
    ${AI__AMonsters__common__components__Abilities__Invisibility}
    ${AI__AMonsters__common__components__Abilities__Psy_Aura}
    ${AI__AMonsters__common__components__Abilities__Scan}
    ${AI__AMonsters__common__components__Abilities__Telekinesis}
    ${AI__AMonsters__common__components__Actor_Controller}
    ${AI__AMonsters__common__components__Anomaly_Detector}
    ${AI__AMonsters__common__components__Bones}
    ${AI__AMonsters__common__components__Control_Manager}
    ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Animation}
    ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Direction}
    ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Movement}
    ${AI__AMonsters__common__components__Control_Manager__Base_Controllers__Path_Builder}
    ${AI__AMonsters__common__components__Control_Manager__Custom__CriticalWound}
    ${AI__AMonsters__common__components__Control_Manager__Custom__Jump}
    ${AI__AMonsters__common__components__Control_Manager__Custom__Rotation_Jump}
    ${AI__AMonsters__common__components__Control_Manager__Custom__Run_Attack}
    ${AI__AMonsters__common__components__Control_Manager__Custom__Sequencer}
    ${AI__AMonsters__common__components__Control_Manager__Custom__Threaten}
    ${AI__AMonsters__common__components__Control_Manager__Custom__Triple_Animation}
    ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Animation}
    ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Direction}
    ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Movement}
    ${AI__AMonsters__common__components__Control_Manager__Pure_Coms__Path_Builder}
    ${AI__AMonsters__common__components__Cover}
    ${AI__AMonsters__common__components__Cover_Manager}
    ${AI__AMonsters__common__components__Event_Handler}
    ${AI__AMonsters__common__components__Event_Handler__Custom_Events}
    ${AI__AMonsters__common__components__Home}
    ${AI__AMonsters__common__components__Melee_Checker}
    ${AI__AMonsters__common__components__Memory}
    ${AI__AMonsters__common__components__Morale}
    ${AI__AMonsters__common__components__Motion_Stats}
    ${AI__AMonsters__common__components__Squad}
    ${AI__AMonsters__common__components__Squad__Squad_Manager}
    ${AI__AMonsters__common__components__State}
    ${AI__AMonsters__common__custom}
    ${AI__AMonsters__common__miscellaneous}
    ${AI__AMonsters__common__script__monster_states__ALife}
    ${AI__AMonsters__common__script__monster_states__Attack}
    ${AI__AMonsters__common__script__monster_states__Camp}
    ${AI__AMonsters__common__script__monster_states__Controlled}
    ${AI__AMonsters__common__script__monster_states__Dangerous_Sound}
    ${AI__AMonsters__common__script__monster_states__Eat}
    ${AI__AMonsters__common__script__monster_states__Eat__Drag}
    ${AI__AMonsters__common__script__monster_states__Eat__Eating}
    ${AI__AMonsters__common__script__monster_states__Find_Enemy}
    ${AI__AMonsters__common__script__monster_states__General}
    ${AI__AMonsters__common__script__monster_states__General__Custom_Action}
    ${AI__AMonsters__common__script__monster_states__General__Look}
    ${AI__AMonsters__common__script__monster_states__General__Movement}
    ${AI__AMonsters__common__script__monster_states__General__Test}
    ${AI__AMonsters__common__script__monster_states__Group_Monsters_Home}
    ${AI__AMonsters__common__script__monster_states__Help_Sound}
    ${AI__AMonsters__common__script__monster_states__Hitted}
    ${AI__AMonsters__common__script__monster_states__Home_Point}
    ${AI__AMonsters__common__script__monster_states__Interesting_Sound}
    ${AI__AMonsters__common__script__monster_states__Panic}
    ${AI__AMonsters__common__script__monster_states__Rest}
    ${AI__AMonsters__common__script__monster_states__Steal}
    ${AI__AMonsters__common__script__monster_states__Steal__Squad__Rest}
    ${AI__AMonsters__common__script__script_binder}
    ${AI__AMonsters__common__script__script_entity}
    ${AI__AMonsters__common__script__script_object}
    ${AI__AMonsters__common__steering_behaviours}
    ${AI__AMonsters__common__steering_behaviours__base}
    ${AI__AMonsters__common__steering_behaviours__components__alignment}
    ${AI__AMonsters__common__steering_behaviours__components__cohesion}
    ${AI__AMonsters__common__steering_behaviours__components__separation}
    ${AI__AMonsters__common__steering_behaviours__manager}
    ${AI__AMonsters__common__trajectories}
    ${AI__AMonsters__humans__stalker}
    ${AI__AMonsters__humans__stalker__AnimationManager}
    ${AI__AMonsters__humans__stalker__AnimationManager__data_storage}
    ${AI__AMonsters__humans__stalker__AnimationManager__data_storage__data}
    ${AI__AMonsters__humans__stalker__AnimationManager__names}
    ${AI__AMonsters__humans__stalker__AnimationManager__pair}
    ${AI__AMonsters__humans__stalker__AnimationManager__script}
    ${AI__AMonsters__humans__stalker__AnimationManager__state}
    ${AI__AMonsters__humans__stalker__CoverEvaluators}
    ${AI__AMonsters__humans__stalker__DecisionMaker}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__alife}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__alife__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__alife__task_actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__anomaly}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__anomaly__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__actions__base}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__get_distance}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__get_distance__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__kill_wounded}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__kill_wounded__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__low_cover_planner}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__low_cover_planner__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__search_planner}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__combat__search_planner__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__by_sound}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__by_sound__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__grenade}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__grenade__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__in_direction}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__in_direction__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__unknown}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__actions__unknown__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__danger__properties}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__death}
    ${AI__AMonsters__humans__stalker__DecisionMaker__actions__death__actions}
    ${AI__AMonsters__humans__stalker__DecisionMaker__properties}
    ${AI__AMonsters__humans__stalker__Miscellaneous}
    ${AI__AMonsters__humans__stalker__MovementManager}
    ${AI__AMonsters__humans__stalker__MovementManager__base}
    ${AI__AMonsters__humans__stalker__MovementManager__base__params}
    ${AI__AMonsters__humans__stalker__MovementManager__base__restriction}
    ${AI__AMonsters__humans__stalker__MovementManager__base__velocity_collection}
    ${AI__AMonsters__humans__stalker__MovementManager__base__velocity_holder}
    ${AI__AMonsters__humans__stalker__MovementManager__obstacles}
    ${AI__AMonsters__humans__stalker__MovementManager__obstacles__obstacle_avoiders__dynamic}
    ${AI__AMonsters__humans__stalker__MovementManager__obstacles__obstacle_avoiders__static}
    ${AI__AMonsters__humans__stalker__MovementManager__obstacles__refreshable_obstacles_query}
    ${AI__AMonsters__humans__stalker__MovementManager__obstacles__restricted_object_obstacle}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__cover_actions}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__loophole_actions}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector__default_behaviour}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__animation_selector__animation_planner__target_selector__target_provider}
    ${AI__AMonsters__humans__stalker__MovementManager__smart_covers__evaluators}
    ${AI__AMonsters__humans__stalker__SoundDataVisitor}
    ${AI__AMonsters__humans__stalker__SoundUserData}
    ${AI__AMonsters__humans__trader}
    ${AI__AMonsters__monsters__Bloodsucker}
    ${AI__AMonsters__monsters__Bloodsucker__Alien_Feature}
    ${AI__AMonsters__monsters__Bloodsucker__Attack}
    ${AI__AMonsters__monsters__Bloodsucker__Capture_Jump}
    ${AI__AMonsters__monsters__Bloodsucker__Predator_State}
    ${AI__AMonsters__monsters__Bloodsucker__Script}
    ${AI__AMonsters__monsters__Bloodsucker__Vampire_State}
    ${AI__AMonsters__monsters__Boar}
    ${AI__AMonsters__monsters__Boar__Script}
    ${AI__AMonsters__monsters__Burer}
    ${AI__AMonsters__monsters__Burer__Attack}
    ${AI__AMonsters__monsters__Burer__Fast_Gravi}
    ${AI__AMonsters__monsters__Burer__Script}
    ${AI__AMonsters__monsters__Cat}
    ${AI__AMonsters__monsters__Cat__Script}
    ${AI__AMonsters__monsters__Chimera}
    ${AI__AMonsters__monsters__Chimera__Script}
    ${AI__AMonsters__monsters__Chimera__state_attack}
    ${AI__AMonsters__monsters__Chimera__state_hunting}
    ${AI__AMonsters__monsters__Chimera__state_threaten}
    ${AI__AMonsters__monsters__Controller}
    ${AI__AMonsters__monsters__Controller__Base_Controllers__Animation}
    ${AI__AMonsters__monsters__Controller__Base_Controllers__Direction}
    ${AI__AMonsters__monsters__Controller__Psy_hit}
    ${AI__AMonsters__monsters__Controller__Script}
    ${AI__AMonsters__monsters__Controller__State_Attack}
    ${AI__AMonsters__monsters__Controller__State_Attack__Cover}
    ${AI__AMonsters__monsters__Controller__State_Panic}
    ${AI__AMonsters__monsters__Crow}
    ${AI__AMonsters__monsters__Dog}
    ${AI__AMonsters__monsters__DogPsy}
    ${AI__AMonsters__monsters__DogPsy__Psy_Attack_Hide}
    ${AI__AMonsters__monsters__Dog__Script}
    ${AI__AMonsters__monsters__Flesh}
    ${AI__AMonsters__monsters__Flesh__Script}
    ${AI__AMonsters__monsters__Fracture}
    ${AI__AMonsters__monsters__Fracture__Script}
    ${AI__AMonsters__monsters__Phantom}
    ${AI__AMonsters__monsters__Poltergeist}
    ${AI__AMonsters__monsters__Poltergeist__Abilities}
    ${AI__AMonsters__monsters__Poltergeist__Hidden_Attack}
    ${AI__AMonsters__monsters__Poltergeist__Script}
    ${AI__AMonsters__monsters__PseudoDog}
    ${AI__AMonsters__monsters__PseudoDog__Script}
    ${AI__AMonsters__monsters__PseudoGigant}
    ${AI__AMonsters__monsters__PseudoGigant__Script}
    ${AI__AMonsters__monsters__Rats}
    ${AI__AMonsters__monsters__Rats__state_manager}
    ${AI__AMonsters__monsters__Rats__states}
    ${AI__AMonsters__monsters__Rats__states__base}
    ${AI__AMonsters__monsters__Snork}
    ${AI__AMonsters__monsters__Snork__Script}
    ${AI__AMonsters__monsters__Snork__Special_Jump}
    ${AI__AMonsters__monsters__Tushkano}
    ${AI__AMonsters__monsters__Tushkano__Script}
    ${AI__AMonsters__monsters__Zombie}
    ${AI__AMonsters__monsters__Zombie__Script}
    ${AI__AMonsters__monsters__Zombie__States}
    ${AI__ANavigation__GameGraph}
    ${AI__ANavigation__GameLevelCrossTable}
    ${AI__ANavigation__GraphAbstract__GraphEdge}
    ${AI__ANavigation__GraphAbstract__GraphVertex}
    ${AI__ANavigation__LevelGraph}
    ${AI__ANavigation__ObjectLocation}
    ${AI__ANavigation__Pathfinding__Algorithms__A2a}
    ${AI__ANavigation__Pathfinding__Algorithms__Dijkstra}
    ${AI__ANavigation__Pathfinding__DataStorages__constructors}
    ${AI__ANavigation__Pathfinding__DataStorages__constructors__builder_allocator}
    ${AI__ANavigation__Pathfinding__DataStorages__constructors__manager_builder_allocator}
    ${AI__ANavigation__Pathfinding__DataStorages__path_builders__edge_path}
    ${AI__ANavigation__Pathfinding__DataStorages__path_builders__vertex_path}
    ${AI__ANavigation__Pathfinding__DataStorages__priority_queues}
    ${AI__ANavigation__Pathfinding__DataStorages__priority_queues__binary_heap}
    ${AI__ANavigation__Pathfinding__DataStorages__priority_queues__bucket_list}
    ${AI__ANavigation__Pathfinding__DataStorages__vertex_allocators__fixed}
    ${AI__ANavigation__Pathfinding__DataStorages__vertex_managers__fixed}
    ${AI__ANavigation__Pathfinding__DataStorages__vertex_managers__hash_fixed}
    ${AI__ANavigation__Pathfinding__GraphEngine}
    ${AI__ANavigation__Pathfinding__PathManagers}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_game}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_game__level}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_game__vertex}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_generic}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level__flooder}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level__nearest_vertex}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_level__straight_line}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_params}
    ${AI__ANavigation__Pathfinding__PathManagers__path_manager_solver}
    ${AI__ANavigation__PatrolPaths__PatrolPath}
    ${AI__ANavigation__PatrolPaths__PatrolPathStorage}
    ${AI__ANavigation__PatrolPaths__PatrolPoint}
    ${AI__AScript}
    ${AI__AScript__ScriptClasses}
    ${AI__AScript__ScriptClasses__BaseClientClasses}
    ${AI__AScript__ScriptClasses__Console}
    ${AI__AScript__ScriptClasses__KeyBindings}
    ${AI__AScript__ScriptClasses__ScriptActions__acript_animation_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_abstract_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_action_condition}
    ${AI__AScript__ScriptClasses__ScriptActions__script_entity_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_monster_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_movement_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_movement_action__patrol_path_params}
    ${AI__AScript__ScriptClasses__ScriptActions__script_object_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_particle_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_particle_action__particle_params}
    ${AI__AScript__ScriptClasses__ScriptActions__script_sound_action}
    ${AI__AScript__ScriptClasses__ScriptActions__script_watch_action}
    ${AI__AScript__ScriptClasses__ScriptBinderObject}
    ${AI__AScript__ScriptClasses__ScriptBinderObject__ScriptBinderObjectWrapper}
    ${AI__AScript__ScriptClasses__ScriptCallbackEx}
    ${AI__AScript__ScriptClasses__ScriptEffector}
    ${AI__AScript__ScriptClasses__ScriptEffector__ScriptEffectorWrapper}
    ${AI__AScript__ScriptClasses__ScriptFS}
    ${AI__AScript__ScriptClasses__ScriptFcolor}
    ${AI__AScript__ScriptClasses__ScriptFlags}
    ${AI__AScript__ScriptClasses__ScriptFmatrix}
    ${AI__AScript__ScriptClasses__ScriptFvector}
    ${AI__AScript__ScriptClasses__ScriptGameObject}
    ${AI__AScript__ScriptClasses__ScriptHit}
    ${AI__AScript__ScriptClasses__ScriptIniFile}
    ${AI__AScript__ScriptClasses__ScriptIniFile__ScriptRTokenList}
    ${AI__AScript__ScriptClasses__ScriptIniFile__ScriptTokenList}
    ${AI__AScript__ScriptClasses__ScriptLAnim}
    ${AI__AScript__ScriptClasses__ScriptMonsterHitInfo}
    ${AI__AScript__ScriptClasses__ScriptNetPacket}
    ${AI__AScript__ScriptClasses__ScriptParticles}
    ${AI__AScript__ScriptClasses__ScriptReader}
    ${AI__AScript__ScriptClasses__ScriptRenderDevice}
    ${AI__AScript__ScriptClasses__ScriptSound}
    ${AI__AScript__ScriptClasses__ScriptSoundInfo}
    ${AI__AScript__ScriptClasses__ScriptSoundType}
    ${AI__AScript__ScriptClasses__UI}
    ${AI__AScript__ScriptDebugger}
    ${AI__AScript__ScriptEngine}
    ${AI__AScript__ScriptProcess}
    ${AI__AScript__ScriptStorage}
    ${AI__AScript__ScriptThread}
    ${AI__AScript__ScriptThread__ScriptStackTracker}
    ${AI__AScript__lua_studio}
    ${AI__ASound}
    ${AI__ASpace}
    ${Core}
    ${Core__Client__Cameras}
    ${Core__Client__Effectors__Actor}
    ${Core__Client__Effectors__Postprocess}
    ${Core__Client__Effectors__Weapon}
    ${Core__Client__Effectors__monsters}
    ${Core__Client__Effects}
    ${Core__Client__Game_Persistent}
    ${Core__Client__Level}
    ${Core__Client__Level_Controller}
    ${Core__Client__Level_Debug}
    ${Core__Client__Level__AutosaveManager}
    ${Core__Client__Level__Bullet_Manager}
    ${Core__Client__Level__ClientDigestComputer}
    ${Core__Client__Level__ClientSpawnManager}
    ${Core__Client__Level__Debug_Renderer}
    ${Core__Client__Level__GlobalFeelTouch}
    ${Core__Client__Level__Level_Sounds}
    ${Core__Client__Level__LevelMapSync}
    ${Core__Client__Level__LevelNetworkDemo}
    ${Core__Client__Level__SeniorityHierarchyHolder}
    ${Core__Client__Level__SeniorityHierarchyHolder__GroupHierarchyHolder}
    ${Core__Client__Level__SeniorityHierarchyHolder__SquadHierarchyHolder}
    ${Core__Client__Level__SeniorityHierarchyHolder__TeamHierarchyHolder}
    ${Core__Client__Objects__DelayedActionFuse}
    ${Core__Client__Objects__actor__base}
    ${Core__Client__Objects__actor__base__memory}
    ${Core__Client__Objects__actor__mp__client}
    ${Core__Client__Objects__actor__mp__server}
    ${Core__Client__Objects__actor__mp__state}
    ${Core__Client__Objects__base}
    ${Core__Client__Objects__base__Entity}
    ${Core__Client__Objects__base__EntityAlive}
    ${Core__Client__Objects__base__EntityCondition}
    ${Core__Client__Objects__base__GameObject}
    ${Core__Client__Objects__base__GameObject__Holder}
    ${Core__Client__Objects__base__GameObject__Holder__ParticlesPlayer}
    ${Core__Client__Objects__base__GameObject__ai_obstacle}
    ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb}
    ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__magic_box}
    ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__magic_minimize_nd}
    ${Core__Client__Objects__base__GameObject__ai_obstacle__min_obb__minimize_1d}
    ${Core__Client__Objects__base__UsableScriptObject}
    ${Core__Client__Objects__hanging_lamp}
    ${Core__Client__Objects__inventory}
    ${Core__Client__Objects__inventory__AttachableItem}
    ${Core__Client__Objects__inventory__AttachmentOwner}
    ${Core__Client__Objects__inventory__EatableItem}
    ${Core__Client__Objects__inventory__EatableItemObject}
    ${Core__Client__Objects__inventory__InventoryItem}
    ${Core__Client__Objects__inventory__InventoryItemObject}
    ${Core__Client__Objects__inventory__InventoryOwner}
    ${Core__Client__Objects__inventory__InventoryOwner__character_info}
    ${Core__Client__Objects__inventory__InventoryOwner__relation_registry}
    ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__purchase_list}
    ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_action_parameters}
    ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_bool_parameters}
    ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_factor_parameters}
    ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_factors}
    ${Core__Client__Objects__inventory__InventoryOwner__trade_parameters__trade_parameters}
    ${Core__Client__Objects__inventory__PhysicItem}
    ${Core__Client__Objects__inventory_box}
    ${Core__Client__Objects__items__weapons__Artifacts}
    ${Core__Client__Objects__items__weapons__Artifacts__BastArtifact}
    ${Core__Client__Objects__items__weapons__Artifacts__BlackDrops}
    ${Core__Client__Objects__items__weapons__Artifacts__BlackGraviArtifact}
    ${Core__Client__Objects__items__weapons__Artifacts__CtaGameArtefact}
    ${Core__Client__Objects__items__weapons__Artifacts__DummyArtifact}
    ${Core__Client__Objects__items__weapons__Artifacts__Electric_Ball}
    ${Core__Client__Objects__items__weapons__Artifacts__Faded_Ball}
    ${Core__Client__Objects__items__weapons__Artifacts__Faded_Ball__Mercury_Ball}
    ${Core__Client__Objects__items__weapons__Artifacts__GalantineArtifact}
    ${Core__Client__Objects__items__weapons__Artifacts__GraviArtifact}
    ${Core__Client__Objects__items__weapons__Artifacts__Needles}
    ${Core__Client__Objects__items__weapons__Artifacts__RustyHairArtifact}
    ${Core__Client__Objects__items__weapons__Artifacts__ThornArtifact}
    ${Core__Client__Objects__items__weapons__Artifacts__ZudaArtifact}
    ${Core__Client__Objects__items__weapons__Devices}
    ${Core__Client__Objects__items__weapons__Devices__Detectors}
    ${Core__Client__Objects__items__weapons__Devices__Detectors__AdvancedDetector}
    ${Core__Client__Objects__items__weapons__Devices__Detectors__EliteDetector}
    ${Core__Client__Objects__items__weapons__Devices__Detectors__Simple_Detector}
    ${Core__Client__Objects__items__weapons__Devices__Torch}
    ${Core__Client__Objects__items__weapons__Devices__flare}
    ${Core__Client__Objects__items__weapons__Documents}
    ${Core__Client__Objects__items__weapons__Explosives}
    ${Core__Client__Objects__items__weapons__Food__Drugs}
    ${Core__Client__Objects__items__weapons__HudItem}
    ${Core__Client__Objects__items__weapons__MPAnticheat}
    ${Core__Client__Objects__items__weapons__MPPlayersBag}
    ${Core__Client__Objects__items__weapons__Outfit}
    ${Core__Client__Objects__items__weapons__PDA__information}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__GrenadeLauncher}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__Scope}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Addons__Silencer}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Ammo}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Automatic}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Grenades__Missiles}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Pistol}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__RocketLauncher}
    ${Core__Client__Objects__items__weapons__Weapons__Custom_Weapon__Weapon_Generic}
    ${Core__Client__Objects__items__weapons__Weapons__StationaryMgun}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__BM-16}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Binocular}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Bolt}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__FN2000}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__FORT}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Grenade_F1}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__HPSA}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Knife}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__LR300}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__PM}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__RGD5}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__RPG7}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__SSRS}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__SVD}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__SVU}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_AK74}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_AutomaticShotgun}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Groza}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_RG6}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Shotgun}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_USP45}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Val}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Vintorez}
    ${Core__Client__Objects__items__weapons__Weapons__Various_weapons__Weapon_Walther_99}
    ${Core__Client__Objects__physics__Breakable}
    ${Core__Client__Objects__physics__Climable}
    ${Core__Client__Objects__physics__CollisionDamageReceiver}
    ${Core__Client__Objects__physics__DestroyablePhysicsObject}
    ${Core__Client__Objects__physics__PHDestroyable}
    ${Core__Client__Objects__physics__PHSkeleton}
    ${Core__Client__Objects__physics__PhysicObject}
    ${Core__Client__Objects__physics__PhysicsShellHolder}
    ${Core__Client__Objects__physics__PhysicsSkeletonObject}
    ${Core__Client__Objects__searchlight}
    ${Core__Client__Objects__searchlight__Trade}
    ${Core__Client__Objects__tasks_info_dialogs}
    ${Core__Client__Objects__tasks_info_dialogs__dialogs}
    ${Core__Client__Objects__tasks_info_dialogs__encyclopedia}
    ${Core__Client__Objects__tasks_info_dialogs__game_tasks}
    ${Core__Client__Objects__tasks_info_dialogs__map}
    ${Core__Client__Objects__tasks_info_dialogs__news}
    ${Core__Client__Objects__tasks_info_dialogs__statistics}
    ${Core__Client__Objects__vehicles}
    ${Core__Client__Objects__vehicles__Car}
    ${Core__Client__Objects__vehicles__Car__CarWeapon}
    ${Core__Client__Objects__vehicles__Car__car_memory}
    ${Core__Client__Objects__vehicles__heli}
    ${Core__Client__Objects__zones__Ameba}
    ${Core__Client__Objects__zones__CustomZone}
    ${Core__Client__Objects__zones__FryUpZone}
    ${Core__Client__Objects__zones__GraviZone}
    ${Core__Client__Objects__zones__HairsZone}
    ${Core__Client__Objects__zones__LevelChanger}
    ${Core__Client__Objects__zones__Mincer}
    ${Core__Client__Objects__zones__MosquitoBald}
    ${Core__Client__Objects__zones__NoGravityZone}
    ${Core__Client__Objects__zones__RadioactiveZone}
    ${Core__Client__Objects__zones__ScriptZone}
    ${Core__Client__Objects__zones__SmartZone}
    ${Core__Client__Objects__zones__SpaceRestrictor}
    ${Core__Client__Objects__zones__TeamBaseZone}
    ${Core__Client__Objects__zones__TorridZone}
    ${Core__Client__Objects__zones__ZoneVisual}
    ${Core__Client__Objects__zones__campfire}
    ${Core__Client__Particles}
    ${Core__Client__Spectator}
    ${Core__Client__Spectator__Cameras}
    ${Core__Common}
    ${Core__Common__Console_Commands}
    ${Core__Common__DateTime}
    ${Core__Common__Dll_Process_Detach}
    ${Core__Common__NET_Shared}
    ${Core__Common__NET_Shared__SecureMessages}
    ${Core__Common__ObjectBroker}
    ${Core__Common__ObjectFactory}
    ${Core__Common__ObjectFactory__object_item_abstract}
    ${Core__Common__ObjectFactory__object_item_client_server}
    ${Core__Common__ObjectFactory__object_item_script}
    ${Core__Common__ObjectFactory__object_item_single}
    ${Core__Common__Profiler}
    ${Core__Common__QuadTree}
    ${Core__Common__Random__32bit}
    ${Core__Common__Random__weighted}
    ${Core__Common__Registry}
    ${Core__Common__Shared}
    ${Core__Common__SmartCast}
    ${Core__Common__StringTable}
    ${Core__Common__associative_vector__compare}
    ${Core__Common__associative_vector__vector}
    ${Core__Common__debug__make_final}
    ${Core__Common__debug__static_cast_checked}
    ${Core__Server}
    ${Core__Server__Editor}
    ${Core__Server__GameSpy__CdkeyDecode}
    ${Core__Server__Games}
    ${Core__Server__Games__PlayerAccounts}
    ${Core__Server__Games__client__artefact_hunt}
    ${Core__Server__Games__client__base}
    ${Core__Server__Games__client__capture_the_artefact}
    ${Core__Server__Games__client__deathmatch}
    ${Core__Server__Games__client__mp}
    ${Core__Server__Games__client__mp__anticheat}
    ${Core__Server__Games__client__mp__award_system}
    ${Core__Server__Games__client__mp__award_system__event_handlers}
    ${Core__Server__Games__client__mp__award_system__player_state}
    ${Core__Server__Games__client__mp__award_system__player_state__state_parameters}
    ${Core__Server__Games__client__mp__screenshots}
    ${Core__Server__Games__client__single}
    ${Core__Server__Games__client__team_deathmatch}
    ${Core__Server__Games__server}
    ${Core__Server__Games__server__artefact_hunt}
    ${Core__Server__Games__server__capture_the_artefact}
    ${Core__Server__Games__server__deathmatch}
    ${Core__Server__Games__server__mp}
    ${Core__Server__Games__server__single}
    ${Core__Server__Games__server__team_deathmatch}
    ${Core__Server__ID_Generator}
    ${Core__Server__ServerConnect}
    ${Core__Server__ServerEntities}
    ${Core__Server__ServerEntities__objects}
    ${Core__Server__ServerEntities__objects_alife}
    ${Core__Server__ServerEntities__objects_alife_items}
    ${Core__Server__ServerEntities__objects_alife_monsters}
    ${Core__Server__ServerEntities__objects_alife_smartcover}
    ${Core__Server__ServerEntities__script_value_container}
    ${Core__Server__ServerPerform}
    ${Core__Server__ServerProcess}
    ${Core__Server__filetransfer}
    ${Core__Server__xrGameSpyServer}
    ${Physics}
    ${Physics__CharacterSupport}
    ${Physics__CharacterSupport__death_anims}
    ${Physics__CharacterSupport__hit_anims}
    ${Physics__CharacterSupport__interactive_anims}
    ${Physics__CharacterSupport__interactive_motion}
    ${Physics__DamagableItem}
    ${Physics__Debug}
    ${Physics__Hit}
    ${Physics__IK}
    ${Physics__MovementControl}
    ${Physics__PHCommander}
    ${Physics__PhysicsSoundPlayer}
    ${Physics__animation_movement_controller}
    ${Physics__scripts}
    ${UI}
    ${UI__Common__ImGui}
    ${UI__Common__Inventory}
    ${UI__Common__InventoryUtilities}
    ${UI__Common__InventoryWnd__InventoryUpgrade}
    ${UI__Common__MainIngame}
    ${UI__Common__MainMenu}
    ${UI__Common__MainMenu__KeyBinding}
    ${UI__Common__OptionsConsoleCommands}
    ${UI__Common__OptionsItem}
    ${UI__Common__PDA}
    ${UI__Common__PDA__MAP}
    ${UI__Common__PDA__Statistics__Rankings}
    ${UI__Common__PDA__Tasks}
    ${UI__Common__PDA__logs}
    ${UI__Common__PDA__logs__News}
    ${UI__Common__TALK}
    ${UI__Common___Debug_Fonts}
    ${UI__Common__ui-item-infos}
    ${UI__Common__ui-item-infos__CharacterInfo}
    ${UI__Cursor}
    ${UI__GameTypes__ArtefactHunt}
    ${UI__GameTypes__CaptureTheArtefact}
    ${UI__GameTypes__Deathmatch}
    ${UI__GameTypes__GameCustom}
    ${UI__GameTypes__Single}
    ${UI__GameTypes__TeamDeathmatch}
    ${UI__HUD}
    ${UI__Multiplayer__Achivements}
    ${UI__Multiplayer__AdminMenu}
    ${UI__Multiplayer__BuyWeaponWnd}
    ${UI__Multiplayer__BuyWeaponWnd__TAB}
    ${UI__Multiplayer__BuyWeaponWnd__rank_restrictions}
    ${UI__Multiplayer__DemoPlayControl}
    ${UI__Multiplayer__HUD__Chat}
    ${UI__Multiplayer__HUD__GameLog}
    ${UI__Multiplayer__HUD__SpeechMenu}
    ${UI__Multiplayer__HUD__Stats}
    ${UI__Multiplayer__HUD__Stats__TeamStates}
    ${UI__Multiplayer__HUD__Stats__icons}
    ${UI__Multiplayer__HUD__common}
    ${UI__Multiplayer__MM_MP__CDkey}
    ${UI__Multiplayer__MM_MP__MapList}
    ${UI__Multiplayer__MM_MP__ServerList}
    ${UI__Multiplayer__MM_MP__TeamInfo}
    ${UI__Multiplayer__Voting}
    ${UI__Multiplayer__team_skin_info__MapDesc}
    ${UI__Multiplayer__team_skin_info__MapDesc__MapInfo}
    ${UI__Multiplayer__team_skin_info__ServerInfo}
    ${UI__Multiplayer__team_skin_info__SkinSelector}
    ${UI__Multiplayer__team_skin_info__Spawn}
    ${UI__Tutorial}
    ${UI__UIWindows}
    ${UI__UIWindows__Buttons}
    ${UI__UIWindows__ComboBox}
    ${UI__UIWindows__DragDrop}
    ${UI__UIWindows__EditBox}
    ${UI__UIWindows__EditBox__customEB}
    ${UI__UIWindows__Hint}
    ${UI__UIWindows__InteractiveBackground}
    ${UI__UIWindows__Lines}
    ${UI__UIWindows__ListBox}
    ${UI__UIWindows__MessageBox}
    ${UI__UIWindows__ProgressBar}
    ${UI__UIWindows__PropertiesBox}
    ${UI__UIWindows__ScriptWnd}
    ${UI__UIWindows__ScrollBar}
    ${UI__UIWindows__ScrollView}
    ${UI__UIWindows__SpinBox}
    ${UI__UIWindows__Static}
    ${UI__UIWindows__TabControl}
    ${UI__UIWindows__TrackBar}
    ${UI__UIWindows__Windows}
    ${UI__UIWindows__XML}
    ${UI__UIWindows__arrow}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.h>"
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

set(ROOT_NAMESPACE xrGame)

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
    INTERPROCEDURAL_OPTIMIZATION_DX10             "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX10AVX          "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX11             "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX11AVX          "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX8              "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX8AVX           "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX9              "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_DX9AVX           "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_PROFILEDDX11     "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASE          "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASEAVX       "FALSE"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../xrCore;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../xrServerEntities;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/luajit-2/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/luabind;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/OpenAutomate/inc;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/cximage"
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
    "XRGAME_EXPORTS;"
    "dSINGLE;"
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
            /GL-;
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
            /GL-;
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
            /GL-;
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
            /GL-;
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
            /GL-;
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
            /GL-;
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
            /GL-;
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
            /GL-;
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
            /Z7
        >
        $<$<CONFIG:Release>:
            /GL-;
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
            /GL-;
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
            /Z7;
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
            /Z7;
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
            /Z7;
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
            /Z7;
            /GS;
            /Zc:inline-
        >
        /std:c++17;
        /wd4995;
        /wd4005;
        /wd4237
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /NOLOGO;
        /OPT:NOREF;
        /OPT:NOICF;
        /DYNAMICBASE:NO;
        /ignore:4099
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    CxImage
    libjpeg
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    crypto
    luabind
    ode
    xrAPI
    xrNetServer
    xrPhysics
    xrXMLParser
    xrCDB
    xrCore
    imgui
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/luajit-2/src/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/lib/my/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/OpenAutomate/libraries;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include/jpeg/libraries/Release;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../_build/_game/bin_dbg"
)

