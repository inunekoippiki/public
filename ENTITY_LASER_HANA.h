#pragma once
#include "ENTITY_LASER.h"
class VECTOR3;
class ENTITY_LASER_HANA :public ENTITY {
public:
	ENTITY_LASER_HANA();
	~ENTITY_LASER_HANA();
	void create(const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime);
	void update()override;
	void draw(SHADER* shader)override;
	void hit(COLLISION* entity)override;
	ENTITY_TYPE entityType()const override;
private:
	ENTITY_LASER EntityLaser;
};

