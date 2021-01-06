#include "BILLBOARDS.h"
#include "ENTITY_LIGHT_BULLET_MEDAMA.h"
ENTITY_LIGHT_BULLET_MEDAMA::ENTITY_LIGHT_BULLET_MEDAMA() {
}

ENTITY_LIGHT_BULLET_MEDAMA::~ENTITY_LIGHT_BULLET_MEDAMA() {
	Billboard->Delete();
}

void ENTITY_LIGHT_BULLET_MEDAMA::create(const VECTOR3& pos, const VECTOR3& velo, int damage, float r){
	EntityLightBullet.create(this, pos, velo, damage, r);
	Billboard = billboards()->appearEntityLightBulletMedama(pos, r * 2.0f);
}

void ENTITY_LIGHT_BULLET_MEDAMA::update(){
	EntityLightBullet.update();
	Billboard->setPos(Pos);
}

void ENTITY_LIGHT_BULLET_MEDAMA::hit(COLLISION* collision){
	EntityLightBullet.hit(collision);
}

void ENTITY_LIGHT_BULLET_MEDAMA::hit(const VECTOR3& pushBack){
	EntityLightBullet.hit(pushBack);
}

void ENTITY_LIGHT_BULLET_MEDAMA::draw(SHADER* shader){
}

ENTITY_TYPE ENTITY_LIGHT_BULLET_MEDAMA::entityType() const{
	return EntityLightBullet.entityType();
}

