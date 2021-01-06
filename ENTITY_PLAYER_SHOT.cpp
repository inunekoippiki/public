#include "BILLBOARDS.h"
#include "BILLBOARD.h"
#include "ENTITY.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "BILLBOARD_ENTITY_LIGHT_BULLET.h"
#include "ENTITY_PLAYER_SHOT.h"
ENTITY_PLAYER_SHOT::ENTITY_PLAYER_SHOT(const VECTOR3& pos, float collisionRadius, int damage) {
	Pos = pos;
	Billboard = billboards()->appearEntityLightBulletPlayer(Pos, collisionRadius * 2.0f);
	Collision = new COLLISION_SPHERE(this, &Pos, collisionRadius);
	collisionManager()->addCollisionPlayerAttck(Collision);
	Damage = damage;
}

ENTITY_PLAYER_SHOT::~ENTITY_PLAYER_SHOT() {
	Billboard->Delete();
	Collision->Delete();
}

void ENTITY_PLAYER_SHOT::update() {
	//Velo.y -= 0.03f;
	posUpdate();
	Billboard->setPos(Pos);
}

void ENTITY_PLAYER_SHOT::draw(SHADER* shader) {
}

void ENTITY_PLAYER_SHOT::hit(COLLISION* entity) {
	entity->entity()->damage(Damage);
	billboards()->appearBurn(Pos, 2.0f);
	DeleteFlag = true;
}

void ENTITY_PLAYER_SHOT::hit(const VECTOR3& pushBack){
	if (!(pushBack == VECTOR3())) {
		DeleteFlag = true;
		billboards()->appearBurn(Pos,2.0f);
	}
}

ENTITY_TYPE ENTITY_PLAYER_SHOT::entityType() const {
	return ENTITY_TYPE::PLAYER_SHOT;
}
