#include "COLLISION_CYLINDER.h"
#include "COLLISION_MANAGER.h"
#include "BILLBOARD_LASER.h"
#include "ENTITY_LASER.h"
ENTITY_LASER::ENTITY_LASER() {
}

ENTITY_LASER::~ENTITY_LASER() {
	Billboard->Delete();
	Collision->Delete();
}

void ENTITY_LASER::create(ENTITY* owner, BILLBOARD_LASER* billboard, const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime){
	Owner = owner;
	Billboard = billboard;
	Owner->setPos(pos);
	Vec = vec;
	Damage = damage;
	MaxLifeTime = lifeTime;
	LifeTime = MaxLifeTime;
	R = r;
	Collision = new COLLISION_CYLINDER(Owner, Owner->posPtr(), vec, r);
	Owner->collisionManager()->addCollisionEnemyAttck(Collision);
}

void ENTITY_LASER::update() {
	LifeTime--;
	if (LifeTime <= 0) {
		Owner->Delete();
	}
	Collision->setRadius((float)LifeTime / MaxLifeTime * R);
	Billboard->setLifeTime(LifeTime);
}

void ENTITY_LASER::hit(COLLISION* entity) {
	entity->entity()->damage(Damage);
}

ENTITY_TYPE ENTITY_LASER::entityType() const {
	return ENTITY_TYPE::LASER;
}
