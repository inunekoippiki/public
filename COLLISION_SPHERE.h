#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION.h"
//球のコリジョン
class COLLISION_SPHERE:public COLLISION{
public:
	COLLISION_SPHERE(ENTITY* entity,const VECTOR3* pos,float r);
	COLLISION_SPHERE(ENTITY* entity, const VECTOR3* pos,const VECTOR3& offsetPos, float r);

	~COLLISION_SPHERE();
	bool isHit(const COLLISION_SPHERE* sphere)const;
	bool isHit(const COLLISION_POINT* point)const;
	bool isHit(const COLLISION_CYLINDER* sylinder)const;
	bool isHit(const COLLISION_SPHERES* spheres)const;

	virtual bool isHit(const COLLISION* collision)const;
	virtual VECTOR3 isHit(const COLLISION_TERRAIN* collision)const;
	//ゲッター
	VECTOR3 pos() const { return *Pos+OffestPos; }
	float px()const { return Pos->x+ OffestPos.x; }
	float py()const { return Pos->y + OffestPos.y; }
	float pz()const { return Pos->z + OffestPos.z; }
	float r()const { return R; }
	//デバッグ用表示
	void draw(STATE_MANAGER* stateManager);

private:
	const VECTOR3* Pos = nullptr;
	VECTOR3 OffestPos;
	float R = 0;
};
