#include "PHSplitedShell.h"

#include "PHElement.h"
#include "PHInterpolation.h"
#include "PHJoint.h"
#include "PHObject.h"
#include "PHShell.h"
#include "PHWorld.h"
#include "Physics.h"
#include "PhysicsShell.h"
#include "SpaceUtils.h"
#include "stdafx.h"

void CPHSplitedShell::Collide() {
    ///////////////////////////////
    CollideStatic( dSpacedGeom(), CPHObject::SelfPointer() );
    // near_callback(this,0,(dGeomID)dSpace(),ph_world->GetMeshGeom());
}

void CPHSplitedShell::get_spatial_params() {
    spatialParsFromDGeom( ( dGeomID )m_space,
                          SpatialComponent->spatial.sphere.P, AABB,
                          SpatialComponent->spatial.sphere.R );
    if ( SpatialComponent->spatial.sphere.R > m_max_AABBradius )
        SpatialComponent->spatial.sphere.R = m_max_AABBradius;
}

void CPHSplitedShell::DisableObject() {
    CPHObject::deactivate();
}
