///////////////////////////////////////////////////////////////
// ElectricBall.cpp
// ElectricBall - артефакт электрический шар
///////////////////////////////////////////////////////////////

#include "ElectricBall.h"

#include "../xrPhysics/PhysicsShell.h"
#include "StdAfx.h"

CElectricBall::CElectricBall( void ) {}

CElectricBall::~CElectricBall( void ) {}

void CElectricBall::Load( LPCSTR section ) {
    inherited::Load( section );
}

void CElectricBall::UpdateCLChild() {
    inherited::UpdateCLChild();

    if ( H_Parent() && IsHidden() )
        XFORM().set( H_Parent()->XFORM() );
};
