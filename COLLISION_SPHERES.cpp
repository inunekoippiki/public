#include "../Library/collisionUtil.h"
#include "COLLISION_SPHERES.h"
#include "COLLISION_CYLINDER.h"
#include "COLLISION_POINT.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_TERRAIN.h"

COLLISION_SPHERES::COLLISION_SPHERES(ENTITY* entity, const VECTOR3* pos){
	Entity = entity;
	Pos = pos;
}

COLLISION_SPHERES::~COLLISION_SPHERES() {
}

bool COLLISION_SPHERES::isHit(const COLLISION_SPHERE* sphere) const{
	for (auto& i : Spheres) {
		if (Calc2SphereIsHit(sphere->pos(),sphere->r(),i.OffsetPos+pos(),i.R)) {
			return true;
		}
	}
	return false;
}

bool COLLISION_SPHERES::isHit(const COLLISION_POINT* point) const{
	for (auto& i : Spheres) {
		if (CalcPointSphereIsHit(point->pos(),i.OffsetPos+pos(),i.R)) {
			return true;
		}
	}
	return false;
}

bool COLLISION_SPHERES::isHit(const COLLISION_CYLINDER* sylinder) const{
	for (auto& i : Spheres) {
		if (CalcSphereSylinderIsHit(i.OffsetPos+pos(),i.R,sylinder->pos(),sylinder->v(),sylinder->r())) {
			return true;
		}
	}
	return false;
}

bool COLLISION_SPHERES::isHit(const COLLISION_SPHERES* spheres) const{
	for (auto& i : Spheres) {
		for (auto& i2 : spheres->spheres()) {
			if (Calc2SphereIsHit(i.OffsetPos+pos(),i.R,i2.OffsetPos+spheres->pos(),i2.R)) {
				return true;
			}
		}
	}
	return false;
}

bool COLLISION_SPHERES::isHit(const COLLISION* collision) const{
	return collision->isHit(this);
}

VECTOR3 COLLISION_SPHERES::isHit(const COLLISION_TERRAIN* collision) const{
	return collision->collision(this);
}

void COLLISION_SPHERES::reserve(int num){
	Spheres.reserve(num);
}

void COLLISION_SPHERES::add(const VECTOR3& offset, float r){
	Spheres.push_back(SPHERE(offset, r));
}

void COLLISION_SPHERES::draw(STATE_MANAGER* stateManager){
}
