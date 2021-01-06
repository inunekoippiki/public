#pragma once
#include <vector>
class SHADER;
class VECTOR3;
class CONTAINER;
class BILLBOARD;
class BILLBOARD_LASER;
class BILLBOARD_LIGHT_BULLET;
class BILLBOARD_ENTITY_LIGHT_BULLET;
class BILLBOARDS {
public:
	BILLBOARDS();
	~BILLBOARDS();
	void create(CONTAINER* container);
	//ビルボ追加
	BILLBOARD_LIGHT_BULLET* appearFire(const VECTOR3& pos, const VECTOR3& velo, float scale);
	BILLBOARD_LASER* appearLaserBoss(const VECTOR3& pos, const VECTOR3& vec, float laserSize, float laserLength, int lifeTime);
	BILLBOARD_LASER* appearLaserHana(const VECTOR3& pos, const VECTOR3& vec, float laserSize, float laserLength, int lifeTime);
	BILLBOARD_LASER* appearLaserBoss(const VECTOR3& pos1, const VECTOR3& pos2, float laserSize, int lifeTime);
	BILLBOARD_LASER* appearLaserHana(const VECTOR3& pos1, const VECTOR3& pos2, float laserSize, int lifeTime);
	BILLBOARD_ENTITY_LIGHT_BULLET* appearEntityLightBulletBoss(const VECTOR3& pos, float scale);
	BILLBOARD_ENTITY_LIGHT_BULLET* appearEntityLightBulletMedama(const VECTOR3& pos, float scale);
	BILLBOARD_ENTITY_LIGHT_BULLET* appearEntityLightBulletPlayer(const VECTOR3& pos, float scale);
	void appearHit(const VECTOR3& pos, float scale);
	void appearBurn(const VECTOR3& pos, float scale);

	void update(const VECTOR3 cameraPos, const VECTOR3& cameraLookDirection);
	void draw(SHADER* shader,const VECTOR3& rad);
private:
	//指定のビルボードリストをupdateする
	void individualUpdate(std::vector<BILLBOARD*>& BbillboardList,const VECTOR3 cameraPos, const VECTOR3& cameraLookDirection);
	std::vector<BILLBOARD*> Billboards;
	std::vector<BILLBOARD*> BillboardsLaser;
};

