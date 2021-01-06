#include "../Library/collisionUtil.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_POINT.h"
#include "COLLISION_CYLINDER.h"
#include "COLLISION_SPHERES.h"
#include "COLLISION_TERRAIN.h"
COLLISION_POINT::COLLISION_POINT(ENTITY* entity,const VECTOR3* pos)
	:Pos(pos){
	Entity = entity;
}

COLLISION_POINT::~COLLISION_POINT() {
}

bool COLLISION_POINT::isHit(const COLLISION_SPHERE* sphere) const{
	return CalcPointSphereIsHit(pos(),sphere->pos(),sphere->r());
}

bool COLLISION_POINT::isHit(const COLLISION_POINT* point) const{
	return Calc2PointIsHit(pos(),point->pos());
}

bool COLLISION_POINT::isHit(const COLLISION_CYLINDER* sylinder) const{
	return CalcPointSylinderIsHit(pos(),sylinder->pos(),sylinder->v(),sylinder->r());
}

bool COLLISION_POINT::isHit(const COLLISION_SPHERES* spheres) const{
	for (auto& i : spheres->spheres()) {
		if (CalcPointSphereIsHit(pos(), i.OffsetPos+spheres->pos(),i.R)) {
			return true;
		}
	}
	return false;

}

bool COLLISION_POINT::isHit(const COLLISION* collision) const{
	return collision->isHit(this);
}

VECTOR3 COLLISION_POINT::isHit(const COLLISION_TERRAIN* collision) const{
	return collision->collision(this);
}
