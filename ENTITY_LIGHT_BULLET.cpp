#include <cmath>
#include "COLLISION_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_LIGHT_BULLET.h"
ENTITY_LIGHT_BULLET::ENTITY_LIGHT_BULLET() {

}

ENTITY_LIGHT_BULLET::~ENTITY_LIGHT_BULLET() {
	Collision->Delete();
}

void ENTITY_LIGHT_BULLET::create(ENTITY* owner, const VECTOR3& pos, const VECTOR3& velo, int damage,float r){
	Owner = owner;
	Owner->setPos(pos);
	Owner->setVelo(velo);
	Damage = damage;
	Collision = new COLLISION_SPHERE(Owner, Owner->posPtr(), r);
	Owner->collisionManager()->addCollisionEnemyAttck(Collision);
}

void ENTITY_LIGHT_BULLET::update(){
	Owner->posUpdate();
}

void ENTITY_LIGHT_BULLET::hit(COLLISION* entity) {
	entity->entity()->damage(Damage);
	Owner->Delete();
}

void ENTITY_LIGHT_BULLET::hit(const VECTOR3& pushBack){
	if (!(pushBack == VECTOR3())) {
		Owner->Delete();
	}
}

ENTITY_TYPE ENTITY_LIGHT_BULLET::entityType() const{
	return ENTITY_TYPE::LIGHT_BULLET;
}


