#pragma once
#include "ENTITY.h"
class BILLBOARD_ENTITY_LIGHT_BULLET;
class BILLBOARDS;
class COLLISION_MANAGER;
class COLLISION;

class ENTITY_PLAYER_SHOT :public ENTITY {
public:
	ENTITY_PLAYER_SHOT(const VECTOR3& pos,float collisionRadius,int damage);
	~ENTITY_PLAYER_SHOT();
	void update();
	void draw(SHADER* shader);
	void hit(COLLISION* entity);
	void hit(const VECTOR3& pushBack);
	ENTITY_TYPE entityType()const;

private:
	BILLBOARD_ENTITY_LIGHT_BULLET* Billboard = nullptr;
	COLLISION* Collision = nullptr;
	int Damage = 0;
};

