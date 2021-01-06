#include "ENTITY_LASER_BOSS.h"
ENTITY_LASER_BOSS::ENTITY_LASER_BOSS() {
}

ENTITY_LASER_BOSS::~ENTITY_LASER_BOSS() {
}

void ENTITY_LASER_BOSS::create(const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime){
	EntityLaser.create(this,
		billboards()->appearLaserBoss(pos, vec + pos, r * 2.0f, lifeTime),
		pos,
		vec,
		r,
		damage,
		lifeTime);
}

void ENTITY_LASER_BOSS::update(){
	EntityLaser.update();
}

void ENTITY_LASER_BOSS::draw(SHADER* shader){
}

void ENTITY_LASER_BOSS::hit(COLLISION* entity){
	EntityLaser.hit(entity);
}

ENTITY_TYPE ENTITY_LASER_BOSS::entityType() const{
	return EntityLaser.entityType();
}

