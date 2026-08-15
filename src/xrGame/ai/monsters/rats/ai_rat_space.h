////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_rat+space.h
//	Created 	: 27.07.2004
//  Modified 	: 27.07.2004
//	Author		: Dmitriy Iassenev
//	Description : Space for monster "Rat"
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace RatSpace {
/// Identifies the different sounds produced by rats.
/// eRatSoundDummy is an invalid/sentinel value.
enum ERatSounds {
    eRatSoundDie = u32( 0 ),   ///< Death sound.
    eRatSoundInjuring,         ///< Injury sound.
    eRatSoundAttack,           ///< Attack sound.
    eRatSoundVoice,            ///< Voice sound.
    eRatSoundEat,              ///< Eating sound.
    eRatSoundDummy = u32( -1 ) ///< Invalid sentinel value.
};

/// Bit masks used to filter rat sounds.
/// eRatSoundMaskDummy is an invalid/sentinel value.
enum ERatSoundMasks {
    eRatSoundMaskAnySound = u32( 0 ),         ///< Matches any sound.
    eRatSoundMaskDie = u32( -1 ),             ///< Death sound mask.
    eRatSoundMaskInjuring = u32( -1 ),        ///< Injury sound mask.
    eRatSoundMaskVoice = u32( 1 << 31 ) | 1,  ///< Voice sound mask.
    eRatSoundMaskAttack = u32( 1 << 30 ) | 2, ///< Attack sound mask.
    eRatSoundMaskEat = u32( 1 << 30 ) | 4,    ///< Eating sound mask.
    eRatSoundMaskDummy = u32( -1 )            ///< Invalid sentinel value.
};
} // namespace RatSpace
