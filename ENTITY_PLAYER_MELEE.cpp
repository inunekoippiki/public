#include <math.h>
#include "BILLBOARDS.h"
#include "BILLBOARD.h"
#include "ENTITY.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "BILLBOARD_ENTITY_LIGHT_BULLET.h"
#include "ENTITY_PLAYER_MELEE.h"
ENTITY_PLAYER_MELEE::ENTITY_PLAYER_MELEE(float collisionRadius,int damage) {

	Collision = new COLLISION_SPHERE(this, &Pos, collisionRadius);
	collisionManager()->addCollisionPlayerAttck(Collision);
	DeleteFlag = true;
	Damage = damage;
}

ENTITY_PLAYER_MELEE::~ENTITY_PLAYER_MELEE() {
	Collision->Delete();
}

void ENTITY_PLAYER_MELEE::update() {
}

void ENTITY_PLAYER_MELEE::draw(SHADER* shader){
}

void ENTITY_PLAYER_MELEE::hit(COLLISION* entity) {
	entity->entity()->damage(Damage);
}

ENTITY_TYPE ENTITY_PLAYER_MELEE::entityType() const {
	return ENTITY_TYPE::PLAYER_MELEE;
}
