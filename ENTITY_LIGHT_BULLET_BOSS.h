#pragma once
#include "ENTITY.h"
#include "ENTITY_LIGHT_BULLET.h"
#include "BILLBOARD_ENTITY_LIGHT_BULLET.h"
class ENTITY_LIGHT_BULLET_BOSS :public ENTITY {
public:
	ENTITY_LIGHT_BULLET_BOSS();
	~ENTITY_LIGHT_BULLET_BOSS();
	void create(const VECTOR3& pos, const VECTOR3& velo, int damage, float r);
	void update()override;
	void hit(COLLISION* collision)override;
	void hit(const VECTOR3& pushBack)override;
	void draw(SHADER* shader)override;
	ENTITY_TYPE entityType()const override;
private:
	BILLBOARD_ENTITY_LIGHT_BULLET* Billboard = nullptr;
	ENTITY_LIGHT_BULLET EntityLightBullet;
};

