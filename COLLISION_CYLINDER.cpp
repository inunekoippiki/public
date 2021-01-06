#include "../Library/collisionUtil.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_POINT.h"
#include "COLLISION_CYLINDER.h"
#include "COLLISION_SPHERES.h"
COLLISION_CYLINDER::COLLISION_CYLINDER(ENTITY* entity, const VECTOR3* pos, const VECTOR3& v, float r){
	Entity = entity;
	Pos = pos;
	V = normalize(v);
	R = r;
}

COLLISION_CYLINDER::~COLLISION_CYLINDER() {
}

bool COLLISION_CYLINDER::isHit(const COLLISION_SPHERE* sphere) const{
	return CalcSphereSylinderIsHit(sphere->pos(),sphere->r(), pos(),V,R);
}

bool COLLISION_CYLINDER::isHit(const COLLISION_POINT* point) const{
	return CalcPointSylinderIsHit(point->pos(), pos(), V, R);
}
//‰~’Œ“¯m–¢À‘•B“–‚½‚ç‚È‚¢
bool COLLISION_CYLINDER::isHit(const COLLISION_CYLINDER* sylinder) const{
	return false;
}

bool COLLISION_CYLINDER::isHit(const COLLISION_SPHERES* spheres) const{
	for (auto& i : spheres->spheres()) {
		if (CalcSphereSylinderIsHit(i.OffsetPos + spheres->pos(), i.R, pos(), V, R)) {
			return true;
		}
	}
	return false;
}
