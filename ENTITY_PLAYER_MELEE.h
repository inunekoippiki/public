#pragma once
#include "ENTITY.h"
class COLLISION_MANAGER;
class COLLISION;
class ENTITY_PLAYER_MELEE :public ENTITY {
public:
	ENTITY_PLAYER_MELEE(float collisionRadius, int damage);
	~ENTITY_PLAYER_MELEE();
	void update() override;
	void draw(SHADER* shader) override;
	void hit(COLLISION* entity);
	ENTITY_TYPE entityType()const;

private:
	int Damage = 0;
	int loop = 0;
	COLLISION* Collision = nullptr;
};

