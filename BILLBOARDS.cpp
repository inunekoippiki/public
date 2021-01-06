#include < algorithm >
#include <vector>
#include "../Library/DEBUG_STR.h"
#include "BILLBOARDS.h"
#include "BILLBOARD.h"
#include "BILLBOARD_LIGHT_BULLET.h"
#include "BILLBOARD_ENTITY_LIGHT_BULLET.h"
#include "BILLBOARD_LASER.h"
#include "BILLBOARD_HIT.h"
#include "BILLBOARD_BURN.h"
BILLBOARDS::BILLBOARDS() {
}

BILLBOARDS::~BILLBOARDS() {
	for (auto& i : Billboards) {
		delete i;
	}
	for (auto& i : BillboardsLaser) {
		delete i;
	}
	BILLBOARD_LIGHT_BULLET::freeGraphic();
	BILLBOARD_LIGHT_BULLET::poolAllDelete();
	BILLBOARD_ENTITY_LIGHT_BULLET::freeGraphic();
	BILLBOARD_ENTITY_LIGHT_BULLET::poolAllDelete();
	BILLBOARD_LASER::freeGraphic();
	BILLBOARD_LASER::poolAllDelete();
	BILLBOARD_HIT::freeGraphic();
	BILLBOARD_HIT::poolAllDelete();
	BILLBOARD_BURN::freeGraphic();
	BILLBOARD_BURN::poolAllDelete();
}

void BILLBOARDS::create(CONTAINER* container){
	BILLBOARD_LIGHT_BULLET::setGraphic(container);
	BILLBOARD_ENTITY_LIGHT_BULLET::setGraphic(container);
	BILLBOARD_LASER::setGraphic(container);
	BILLBOARD_HIT::setGraphic(container);
	BILLBOARD_BURN::setGraphic(container);
	Billboards.reserve(256);
}

BILLBOARD_LIGHT_BULLET* BILLBOARDS::appearFire(const VECTOR3& pos, const VECTOR3& velo, float scale) {
	BILLBOARD_LIGHT_BULLET* p = BILLBOARD_LIGHT_BULLET::takeFromPool();
	p->init(pos, velo, scale);
	Billboards.push_back(p);
	return p;
}

BILLBOARD_LASER* BILLBOARDS::appearLaserBoss(const VECTOR3& pos, const VECTOR3& vec, float laserSize, float laserLength, int lifeTime) {
	BILLBOARD_LASER* p = BILLBOARD_LASER::takeFromPool();
	p->init(pos, vec, laserSize, laserLength, lifeTime, 0);
	BillboardsLaser.push_back(p);
	return p;
}

BILLBOARD_LASER* BILLBOARDS::appearLaserHana(const VECTOR3& pos, const VECTOR3& vec, float laserSize, float laserLength, int lifeTime) {
	BILLBOARD_LASER* p = BILLBOARD_LASER::takeFromPool();
	p->init(pos, vec, laserSize, laserLength, lifeTime, 1);
	BillboardsLaser.push_back(p);
	return p;
}

BILLBOARD_LASER* BILLBOARDS::appearLaserBoss(const VECTOR3& pos1, const VECTOR3& pos2, float laserSize,int lifeTime) {
	BILLBOARD_LASER* p = BILLBOARD_LASER::takeFromPool();
	p->init(pos1, pos2, laserSize, lifeTime, 0);
	BillboardsLaser.push_back(p);
	return p;
}
BILLBOARD_LASER* BILLBOARDS::appearLaserHana(const VECTOR3& pos1, const VECTOR3& pos2, float laserSize, int lifeTime) {
	BILLBOARD_LASER* p = BILLBOARD_LASER::takeFromPool();
	p->init(pos1, pos2, laserSize, lifeTime, 1);
	BillboardsLaser.push_back(p);
	return p;
}

BILLBOARD_ENTITY_LIGHT_BULLET* BILLBOARDS::appearEntityLightBulletBoss(const VECTOR3& pos, float scale){
	BILLBOARD_ENTITY_LIGHT_BULLET* p = BILLBOARD_ENTITY_LIGHT_BULLET::takeFromPool();
	p->init(pos, scale,0);
	Billboards.push_back(p);
	return p;
}

BILLBOARD_ENTITY_LIGHT_BULLET* BILLBOARDS::appearEntityLightBulletMedama(const VECTOR3& pos, float scale) {
	BILLBOARD_ENTITY_LIGHT_BULLET* p = BILLBOARD_ENTITY_LIGHT_BULLET::takeFromPool();
	p->init(pos, scale,1);
	Billboards.push_back(p);
	return p;
}

BILLBOARD_ENTITY_LIGHT_BULLET* BILLBOARDS::appearEntityLightBulletPlayer(const VECTOR3& pos, float scale){
	BILLBOARD_ENTITY_LIGHT_BULLET* p = BILLBOARD_ENTITY_LIGHT_BULLET::takeFromPool();
	p->init(pos, scale, 2);
	Billboards.push_back(p);
	return p;
}


void BILLBOARDS::appearHit(const VECTOR3& pos, float scale){
	BILLBOARD_HIT* p = BILLBOARD_HIT::takeFromPool();
	p->init(pos, scale);
	Billboards.push_back(p);
}

void BILLBOARDS::appearBurn(const VECTOR3& pos, float scale){
	BILLBOARD_BURN* p = BILLBOARD_BURN::takeFromPool();
	p->init(pos, scale);
	Billboards.push_back(p);
}

void BILLBOARDS::update(const VECTOR3 cameraPos, const VECTOR3& cameraLookDirection) {
	individualUpdate(Billboards, cameraPos, cameraLookDirection);
	individualUpdate(BillboardsLaser, cameraPos, cameraLookDirection);
	DEBUG_STR* ds = DEBUG_STR::instance();
	ds->set("billbordsNum:%d", Billboards.size() + BillboardsLaser.size());
}

void BILLBOARDS::draw(SHADER* shader,const VECTOR3& rad) {
	for (auto& i : Billboards) {
		i->draw(shader, rad);
	}
	for (auto& i : BillboardsLaser) {
		i->draw(shader, rad);
	}
}

void BILLBOARDS::individualUpdate(std::vector<BILLBOARD*>& billboardList, const VECTOR3 cameraPos, const VECTOR3& cameraLookDirection){
	for (int i = 0;i < (int)billboardList.size();i++) {
		billboardList[i]->update();
		billboardList[i]->calcDistance(cameraPos, cameraLookDirection);
		//表示終了ビルボードは配列から外す
		if (billboardList[i]->life() == 0) {
			billboardList[i]->addPool();
			billboardList[i] = billboardList[billboardList.size() - 1];
			billboardList.pop_back();
			i--;
		}
	}
	//カメラからの距離が遠い順にソート
	std::sort(billboardList.begin(), billboardList.end(), [](const BILLBOARD* a, const BILLBOARD* b)->bool {return a->distance() > b->distance();});
}

