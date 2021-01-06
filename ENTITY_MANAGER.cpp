#include <float.h>
#include "../Library/SHADER.h"
#include "ENTITY.h"
#include "ENTITY_HANA.h"
#include "ENTITY_MEDAMA.h"
#include "ENTITY_PLAYER.h"
#include "ENTITY_LIGHT_BULLET_BOSS.h"
#include "ENTITY_LIGHT_BULLET_MEDAMA.h"
#include "ENTITY_LASER_BOSS.h"
#include "ENTITY_LASER_HANA.h"
#include "ENTITY_PLAYER_MELEE.h"
#include "ENTITY_PLAYER_SHOT.h"
#include "ENTITY_BOSS.h"
#include "ENTITY_MANAGER.h"

COLLISION_MANAGER* ENTITY_MANAGER::CollisionManager = nullptr;
BILLBOARDS* ENTITY_MANAGER::Billboards = nullptr;
ENTITY_MANAGER::ENTITY_MANAGER(CONTAINER* container):
	Container(container){

}

ENTITY_MANAGER::~ENTITY_MANAGER() {
	for (auto& i : Entitys) {
		delete i;
	}
}

ENTITY_MEDAMA* ENTITY_MANAGER::appearMedama(const VECTOR3& pos){
	ENTITY_MEDAMA* p = new ENTITY_MEDAMA();
	p->create();
	p->setPos(pos);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_HANA* ENTITY_MANAGER::appearHana(const VECTOR3& pos){
	ENTITY_HANA* p = new ENTITY_HANA();
	p->create();
	p->setPos(pos);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_PLAYER* ENTITY_MANAGER::appearPlayer(const VECTOR3& pos){
	ENTITY_PLAYER* p = new ENTITY_PLAYER();
	p->create();
	p->setPos(pos);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_LIGHT_BULLET_BOSS* ENTITY_MANAGER::appearLightBulletBoss(const VECTOR3& pos, const VECTOR3& velo, int damage, float r){
	ENTITY_LIGHT_BULLET_BOSS* p = new ENTITY_LIGHT_BULLET_BOSS();
	p->create(pos, velo, damage,r);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_LIGHT_BULLET_MEDAMA* ENTITY_MANAGER::appearLightBulletMedama(const VECTOR3& pos, const VECTOR3& velo, int damage,float r) {
	ENTITY_LIGHT_BULLET_MEDAMA* p = new ENTITY_LIGHT_BULLET_MEDAMA();
	p->create(pos, velo, damage,r);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_LASER_BOSS* ENTITY_MANAGER::appearLaserBoss(const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime){
	ENTITY_LASER_BOSS* p = new ENTITY_LASER_BOSS();
	p->create(pos, vec, r, damage, lifeTime);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_LASER_HANA* ENTITY_MANAGER::appearLaserHana(const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime) {
	ENTITY_LASER_HANA* p = new ENTITY_LASER_HANA();
	p->create(pos, vec, r,damage,lifeTime);
	EntitysTemp.push_back(p);
	return p;
}


ENTITY_PLAYER_SHOT* ENTITY_MANAGER::appearPlayerShot(const VECTOR3& pos, const VECTOR3& velo, float collisionRadius, int damage) {
	ENTITY_PLAYER_SHOT* p = new ENTITY_PLAYER_SHOT(pos,collisionRadius, damage);
	p->setVelo(velo);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_PLAYER_MELEE* ENTITY_MANAGER::appearPlayerMelee(const VECTOR3& pos, float collisionRadius, int damage){
	ENTITY_PLAYER_MELEE* p = new ENTITY_PLAYER_MELEE(collisionRadius,damage);
	p->setPos(pos);
	EntitysTemp.push_back(p);
	return p;
}

ENTITY_BOSS* ENTITY_MANAGER::appearBoss(const VECTOR3& pos){
	ENTITY_BOSS* p = new ENTITY_BOSS();
	p->create();
	p->setPos(pos);
	EntitysTemp.push_back(p);
	return p;

}

void ENTITY_MANAGER::update() {
	for (unsigned i = 0;i < Entitys.size();) {
		//デリートフラグが入っているENTITYは消す
		if (Entitys[i]->isDelete()) {
			delete Entitys[i];
			Entitys[i] = Entitys[Entitys.size() - 1];
			Entitys.pop_back();
			continue;
		}
		//ENTITYをアップデート
		Entitys[i]->update();
		i++;
	}
	EntitySummon();
}

void ENTITY_MANAGER::draw(SHADER* shader) {
	for (auto& i : Entitys) {
		i->draw(shader);
	}
}

void ENTITY_MANAGER::execute(std::function<void(ENTITY*)> func){
	for (auto& i : Entitys) {
		func(i);
	}
}

ENTITY* ENTITY_MANAGER::entitySearch(std::function<bool(const ENTITY*)> func){
	for (auto& i : Entitys) {
		if(func(i))
		return i;
	}
	return nullptr;
}

ENTITY* ENTITY_MANAGER::whereMin(std::function<float(const ENTITY*)> func){
	float min = FLT_MAX;
	ENTITY* entity = nullptr;
	for (auto& i : Entitys) {
		float value = func(i);
		if (value < min) {
			min = value;
			entity = i;
		}
	}
	return entity;
}

ENTITY* ENTITY_MANAGER::whereMin(std::function<float(const ENTITY*)> func, float& min){
	min = FLT_MAX;
	ENTITY* entity = nullptr;
	for (auto& i : Entitys) {
		float value = func(i);
		if (value < min) {
			min = value;
			entity = i;
		}
	}
	return entity;
}

void ENTITY_MANAGER::EntitySummon(){
	for (auto& i : EntitysTemp) {
		Entitys.push_back(i);
	}
	EntitysTemp.clear();
}
