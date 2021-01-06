#pragma once
#include "ENTITY.h"
class COLLISION;

class ENTITY_LIGHT_BULLET{
public:
	ENTITY_LIGHT_BULLET();
	~ENTITY_LIGHT_BULLET();
	void create(ENTITY*entity, const VECTOR3& pos, const VECTOR3& velo, int damage,float r);
	void update();
	void hit(COLLISION* entity);
	void hit(const VECTOR3& pushBack);
	ENTITY_TYPE entityType()const;
private:
	ENTITY* Owner = nullptr;
	COLLISION* Collision = nullptr;
	int Damage = 0;
};

