#include "../Library/collisionUtil.h"
#include "../Library/CONTAINER.h"
#include "../Library/TEXTURE.h"
#include "STATE_MANAGER.h"
#include "COLLISION_POINT.h"
#include "COLLISION_CYLINDER.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_SPHERES.h"
#include "COLLISION_TERRAIN.h"
COLLISION_SPHERE::COLLISION_SPHERE(ENTITY* entity, const VECTOR3* pos, float r)
	:Pos(pos),
	R(r) {
	Entity = entity;
}

COLLISION_SPHERE::COLLISION_SPHERE(ENTITY* entity, const VECTOR3* pos, const VECTOR3& offsetPos, float r)
	: Pos(pos),
	OffestPos(offsetPos),
	R(r) {
	Entity = entity;
}

COLLISION_SPHERE::~COLLISION_SPHERE() {
}

bool COLLISION_SPHERE::isHit(const COLLISION_SPHERE* sphere)const{
	return Calc2SphereIsHit(pos(),R,sphere->pos(),sphere->r());
}

bool COLLISION_SPHERE::isHit(const COLLISION_POINT* point) const{
	return CalcPointSphereIsHit(point->pos(),pos(),R);
}

bool COLLISION_SPHERE::isHit(const COLLISION_CYLINDER* sylinder) const{
	return CalcSphereSylinderIsHit(pos(),R,sylinder->pos(),sylinder->v(),sylinder->r());
}

bool COLLISION_SPHERE::isHit(const COLLISION_SPHERES* spheres) const{
	for(auto &i:spheres->spheres()){
		if (Calc2SphereIsHit(i.OffsetPos + spheres->pos(), i.R, pos(), R)) {
			return true;
		}
	}
	return false;
}

bool COLLISION_SPHERE::isHit(const COLLISION* collision) const{
	return collision->isHit(this);
}

VECTOR3 COLLISION_SPHERE::isHit(const COLLISION_TERRAIN* collision) const{
	return collision->collision(this);
}

void COLLISION_SPHERE::draw(STATE_MANAGER* stateManager){
	TEXTURE* texture = stateManager->gameDataCommon()->container()->texture("sphere");
}
