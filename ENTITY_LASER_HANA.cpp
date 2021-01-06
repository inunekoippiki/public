#include "ENTITY_LASER_HANA.h"
ENTITY_LASER_HANA::ENTITY_LASER_HANA() {
}

ENTITY_LASER_HANA::~ENTITY_LASER_HANA() {
}

void ENTITY_LASER_HANA::create(const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime){
	EntityLaser.create(this,
		billboards()->appearLaserHana(pos, vec + pos, r * 2.0f, lifeTime),
		pos,
		vec,
		r,
		damage,
		lifeTime);
}

void ENTITY_LASER_HANA::update(){
	EntityLaser.update();
}

void ENTITY_LASER_HANA::draw(SHADER* shader){
}

void ENTITY_LASER_HANA::hit(COLLISION* entity){
	EntityLaser.hit(entity);
}

ENTITY_TYPE ENTITY_LASER_HANA::entityType() const{
	return EntityLaser.entityType();
}
