#include "../Library/VECTOR3.h"
#include "COLLISION.h"
COLLISION::COLLISION():
	IsCollision(true) {

}
COLLISION::~COLLISION() {

}

bool COLLISION::isHit(const COLLISION_SPHERE* sphere) const{
	return false;
}

bool COLLISION::isHit(const COLLISION_POINT* point)const {
	return false;
}

bool COLLISION::isHit(const COLLISION_CYLINDER* cyliner) const{
	return false;
}

bool COLLISION::isHit(const COLLISION_SPHERES* spheres) const{
	return false;
}

bool COLLISION::isHit(const COLLISION* collision) const{
	return false;
}

VECTOR3 COLLISION::isHit(const COLLISION_TERRAIN* collision) const{
	return VECTOR3();
}

void COLLISION::Delete(){
	IsDelete = true;
}

void COLLISION::draw(STATE_MANAGER* stateManager) {

}