////////////////////////////////////////////////////////////////////////////
//	Module 		: alife_space.h
//	Created 	: 08.01.2002
//  Modified 	: 08.01.2003
//	Author		: Dmitriy Iassenev
//	Description : ALife space
////////////////////////////////////////////////////////////////////////////

#ifndef XRAY_ALIFE_SPACE
#define XRAY_ALIFE_SPACE
//#include "../xrCore/_std_extensions.h"

#define ALIFE_VERSION             0x0006 ///< Version of the ALife save data format.
#define ALIFE_CHUNK_DATA          0x0000 ///< Chunk containing ALife simulation data.
#define SPAWN_CHUNK_DATA          0x0001 ///< Chunk containing spawn data.
#define OBJECT_CHUNK_DATA         0x0002 ///< Chunk containing object data.
#define GAME_TIME_CHUNK_DATA      0x0005 ///< Chunk containing game time data.
#define REGISTRY_CHUNK_DATA       0x0009 ///< Chunk containing ALife registry data.
#define SECTION_HEADER            "location_" ///< Prefix used for location section names.
#define SAVE_EXTENSION            ".scop" ///< File extension for ALife save files.
#define MAX_ITEM_VOLUME           100 ///< Maximum inventory volume (rucksack capacity).
#define INVALID_STORY_ID          ALife::_STORY_ID(-1) ///< Invalid story identifier.
#define INVALID_SPAWN_STORY_ID    ALife::_SPAWN_STORY_ID(-1) ///< Invalid spawn story identifier.

class CSE_ALifeDynamicObject;
class CSE_ALifeMonsterAbstract;
class CSE_ALifeTrader;
class CSE_ALifeInventoryItem;
class CSE_ALifeItemWeapon;
class CSE_ALifeSchedulable;
class CGameGraph;

namespace ALife
{
	typedef u64 _CLASS_ID;        ///< Unique class identifier.
	typedef u16 _OBJECT_ID;       ///< Unique object identifier.
	typedef u64 _TIME_ID;         ///< ALife simulation time identifier.
	typedef u32 _EVENT_ID;        ///< Event identifier.
	typedef u32 _TASK_ID;         ///< Task identifier.
	typedef u16 _SPAWN_ID;        ///< Spawn point identifier.
	typedef u16 _TERRAIN_ID;      ///< Smart terrain identifier.
	typedef u32 _STORY_ID;        ///< Story object identifier.
	typedef u32 _SPAWN_STORY_ID;  ///< Spawn story identifier.

	/// Represents a search state used while exploring item cost combinations.
	struct SSumStackCell
	{
		int i1;           ///< Current position in the index array.
		int i2;           ///< Highest candidate item index to consider.
		int iCurrentSum;  ///< Sum of the selected item costs.
	};

	/// Represents the outcome of a combat encounter.
	/// eCombatDummy is an invalid/sentinel value.
	enum ECombatResult
	{
		eCombatResultRetreat1 = u32(0), ///< Combatant 1 retreats.
		eCombatResultRetreat2,          ///< Combatant 2 retreats.
		eCombatResultRetreat12,         ///< Both combatants retreat.
		eCombatResult1Kill2,            ///< Combatant 1 kills combatant 2.
		eCombatResult2Kill1,            ///< Combatant 2 kills combatant 1.
		eCombatResultBothKilled,        ///< Both combatants are killed.
		eCombatDummy = u32(-1),         ///< Invalid sentinel value.
	};

	/// Specifies the combat action to perform.
	/// eCombatActionDummy is an invalid/sentinel value.
	enum ECombatAction
	{
		eCombatActionAttack = u32(0), ///< Attack the target.
		eCombatActionRetreat,         ///< Retreat from combat.
		eCombatActionDummy = u32(-1), ///< Invalid sentinel value.
	};

	/// Specifies the action to take when two ALife objects meet.
	/// eMeetActionTypeDummy is an invalid/sentinel value.
	enum EMeetActionType
	{
		eMeetActionTypeAttack = u32(0), ///< Attack the other object.
		eMeetActionTypeInteract,        ///< Interact with the other object.
		eMeetActionTypeIgnore,          ///< Ignore the other object.
		eMeetActionSmartTerrain,        ///< Perform a smart terrain action.
		eMeetActionTypeDummy = u32(-1), ///< Invalid sentinel value.
	};

	/// Describes the relationship between two ALife objects.
	/// eRelationTypeDummy is an invalid/sentinel value.
	enum ERelationType
	{
		eRelationTypeFriend = u32(0), ///< Friendly.
		eRelationTypeNeutral,         ///< Neutral.
		eRelationTypeEnemy,           ///< Hostile.
		eRelationTypeWorstEnemy,      ///< Highest-priority hostile target.
		eRelationTypeLast,            ///< Number of valid relation types.
		eRelationTypeDummy = u32(-1), ///< Invalid sentinel value.
	};

	/// Types of damage that can be inflicted on an object.
	enum EHitType
	{
		eHitTypeBurn = u32(0), ///< Thermal burn damage.
		eHitTypeShock,         ///< Electrical damage.
		eHitTypeChemicalBurn,  ///< Chemical damage.
		eHitTypeRadiation,     ///< Radiation damage.
		eHitTypeTelepatic,     ///< Psychic damage.
		eHitTypeWound,         ///< Generic wound damage.
		eHitTypeFireWound,     ///< Firearm wound damage.
		eHitTypeStrike,        ///< Melee or impact damage.
		eHitTypeExplosion,     ///< Explosion damage.
		eHitTypeWound_2,       ///< Secondary wound damage type.
		// eHitTypePhysicStrike, ///< Knife alternative attack.
		eHitTypeLightBurn,     ///< Light burn damage.
		eHitTypeMax,           ///< Number of hit types.
	};

	/// Types of environmental influences affecting an object.
	enum EInfluenceType
	{
		infl_rad = u32(0), ///< Radiation.
		infl_fire,         ///< Fire.
		infl_acid,         ///< Chemical acid.
		infl_psi,          ///< Psychic influence.
		infl_electra,      ///< Electrical influence.
		infl_max_count     ///< Number of influence types.
	};

	/// Identifies the type of actor condition restored over time.
	enum EConditionRestoreType
	{
		eHealthRestoreSpeed = u32(0), ///< Health restoration rate.
		eSatietyRestoreSpeed,         ///< Satiety restoration rate.
		ePowerRestoreSpeed,           ///< Stamina restoration rate.
		eBleedingRestoreSpeed,        ///< Bleeding recovery rate.
		eRadiationRestoreSpeed,       ///< Radiation recovery rate.
		eRestoreTypeMax,              ///< Number of restore types.
	};

	/// Specifies how items should be taken from an inventory.
	enum ETakeType
	{
		eTakeTypeAll,  ///< Take all available items.
		eTakeTypeMin,  ///< Take the minimum required items.
		eTakeTypeRest, ///< Take all remaining items.
	};

	/// Categorizes weapons by priority for AI weapon selection.
	/// eWeaponPriorityTypeDummy is an invalid/sentinel value.
	enum EWeaponPriorityType
	{
		eWeaponPriorityTypeKnife = u32(0), ///< Knife or other melee weapon.
		eWeaponPriorityTypeSecondary,      ///< Secondary weapon (e.g. pistol).
		eWeaponPriorityTypePrimary,        ///< Primary weapon.
		eWeaponPriorityTypeGrenade,        ///< Grenade.
		eWeaponPriorityTypeDummy = u32(-1) ///< Invalid sentinel value.
	};

	/// Identifies the type of ALife combat or interaction being processed.
	/// eCombatTypeDummy is an invalid/sentinel value.
	enum ECombatType
	{
		eCombatTypeMonsterMonster = u32(0), ///< Monster versus monster.
		eCombatTypeMonsterAnomaly,          ///< Monster versus anomaly.
		eCombatTypeAnomalyMonster,          ///< Anomaly versus monster.
		eCombatTypeSmartTerrain,            ///< Smart terrain interaction.
		eCombatTypeDummy = u32(-1)          ///< Invalid sentinel value.
	};

	/// Describes whether a weapon supports a particular addon.
	enum EWeaponAddonStatus
	{
		eAddonDisabled = 0, ///< This addon is not supported by the weapon.
		eAddonPermanent = 1, ///< The addon is built into the weapon and cannot be detached.
		eAddonAttachable = 2, ///< The addon may be attached to or detached from the weapon.
	};

	/// Parses a hit type name from configuration data into an EHitType.
	/// Terminates execution if the hit type is unsupported.
	IC EHitType g_tfString2HitType(LPCSTR caHitType)
	{
		if (!_stricmp(caHitType, "burn"))
			return (eHitTypeBurn);
		else if (!_stricmp(caHitType, "light_burn"))
			return (eHitTypeLightBurn);
		else if (!_stricmp(caHitType, "shock"))
			return (eHitTypeShock);
		else if (!_stricmp(caHitType, "strike"))
			return (eHitTypeStrike);
		else if (!_stricmp(caHitType, "wound"))
			return (eHitTypeWound);
		else if (!_stricmp(caHitType, "radiation"))
			return (eHitTypeRadiation);
		else if (!_stricmp(caHitType, "telepatic"))
			return (eHitTypeTelepatic);
		else if (!_stricmp(caHitType, "fire_wound"))
			return (eHitTypeFireWound);
		else if (!_stricmp(caHitType, "chemical_burn"))
			return (eHitTypeChemicalBurn);
		else if (!_stricmp(caHitType, "explosion"))
			return (eHitTypeExplosion);
		else if (!_stricmp(caHitType, "wound_2"))
			return (eHitTypeWound_2);
		else
			FATAL("Unsupported hit type!");
		NODEFAULT;
#ifdef DEBUG
		return(eHitTypeMax);
#endif
	}
#ifndef	_EDITOR
	/// Maps hit type names from configuration files to their corresponding EHitType values.
	extern xr_token hit_types_token [ ];

	/// Returns the configuration string corresponding to the specified hit type.
	IC LPCSTR g_cafHitType2String(EHitType tHitType)
	{
		return get_token_name(hit_types_token, tHitType);
	}
#endif
	/// Defines aliases for a vector of integers and its iterator type.
	DEFINE_VECTOR(int, INT_VECTOR, INT_IT);

	/// Defines aliases for a vector of object IDs and its iterator type.
	DEFINE_VECTOR(_OBJECT_ID, OBJECT_VECTOR, OBJECT_IT);

	/// Defines aliases for a vector of ALife inventory items and its iterator type.
	DEFINE_VECTOR(CSE_ALifeInventoryItem*, ITEM_P_VECTOR, ITEM_P_IT);

	/// Defines aliases for a vector of ALife weapon items and its iterator type.
	DEFINE_VECTOR(CSE_ALifeItemWeapon*, WEAPON_P_VECTOR, WEAPON_P_IT);

	/// Defines aliases for a vector of ALife objects that participate in the scheduler and its iterator type.
	DEFINE_VECTOR(CSE_ALifeSchedulable*, SCHEDULE_P_VECTOR, SCHEDULE_P_IT);

	/// Defines aliases for a map of object IDs to dynamic ALife objects and its iterator type.
	DEFINE_MAP(_OBJECT_ID, CSE_ALifeDynamicObject*, D_OBJECT_P_MAP, D_OBJECT_P_PAIR_IT);

	/// Defines aliases for a map of story IDs to dynamic ALife objects and its iterator type.
	DEFINE_MAP(_STORY_ID, CSE_ALifeDynamicObject*, STORY_P_MAP, STORY_P_PAIR_IT);
};

#endif //XRAY_ALIFE_SPACE
