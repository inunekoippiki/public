#pragma once
#include "../Library/VECTOR3.h"
#include "BILLBOARDS.h"
#include "ENTITY.h"
class BILLBOARD_LASER;
class COLLISION_CYLINDER;
class ENTITY_LASER {
public:
	ENTITY_LASER();
	~ENTITY_LASER();
	void create(ENTITY* owner, BILLBOARD_LASER* billboard, const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime);
	void update();
	void hit(COLLISION* entity);
	ENTITY_TYPE entityType()const;
private:
	ENTITY* Owner = nullptr;
	BILLBOARD_LASER* Billboard = nullptr;
	VECTOR3 Vec;//レーザーの方向ベクトル
	COLLISION_CYLINDER* Collision = nullptr;
	int Damage = 0;
	int MaxLifeTime = 0;
	int LifeTime = 0;
	float R = 0.0f;
};

