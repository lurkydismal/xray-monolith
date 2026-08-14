#include "WeaponPistol.h"

#include "Actor.h"
#include "StdAfx.h"

CWeaponPistol::CWeaponPistol() {
    m_eSoundClose = ESoundTypes( SOUND_TYPE_WEAPON_RECHARGING );
    SetPending( FALSE );
}

CWeaponPistol::~CWeaponPistol( void ) {}

void CWeaponPistol::Load( LPCSTR section ) {
    inherited::Load( section );

    m_sounds.LoadSound( section, "snd_close", "sndClose", false,
                        m_eSoundClose );
}
