#pragma once

namespace ALife {

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

}
