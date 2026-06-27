#include "icollidable.h"

#include "../xrcdb/ispatial.h"
#include "stdafx.h"
#include "xr_collide_form.h"

ICollidable::ICollidable() {
    collidable.model = nullptr;
}

ICollidable::~ICollidable() {
    xr_delete( collidable.model );
}
