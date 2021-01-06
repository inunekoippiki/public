#include "BILLBOARDS.h"
#include "ENTITY_LIGHT_BULLET_BOSS.h"
ENTITY_LIGHT_BULLET_BOSS::ENTITY_LIGHT_BULLET_BOSS() {
}

ENTITY_LIGHT_BULLET_BOSS::~ENTITY_LIGHT_BULLET_BOSS() {
	Billboard->Delete();
}

void ENTITY_LIGHT_BULLET_BOSS::create(const VECTOR3& pos, const VECTOR3& velo, int damage, float r){
	EntityLightBullet.create(this,pos, velo, damage, r);
	Billboard = billboards()->appearEntityLightBulletBoss(pos, r * 2.0f);
}

void ENTITY_LIGHT_BULLET_BOSS::update(){
	EntityLightBullet.update();
	Billboard->setPos(Pos);
}

void ENTITY_LIGHT_BULLET_BOSS::hit(COLLISION* collision){
	EntityLightBullet.hit(collision);
}

void ENTITY_LIGHT_BULLET_BOSS::hit(const VECTOR3& pushBack){
	EntityLightBullet.hit(pushBack);
}

void ENTITY_LIGHT_BULLET_BOSS::draw(SHADER* shader){
}

ENTITY_TYPE ENTITY_LIGHT_BULLET_BOSS::entityType() const{
	return EntityLightBullet.entityType();
}
