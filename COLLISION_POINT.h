#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION.h"
//点のコリジョン
class COLLISION_POINT:public COLLISION{
public:
	COLLISION_POINT(ENTITY* entity,const VECTOR3* pos);
	~COLLISION_POINT();
	bool isHit(const COLLISION_SPHERE* sphere)const;
	bool isHit(const COLLISION_POINT* point)const;
	bool isHit(const COLLISION_CYLINDER* sylinder)const;
	bool isHit(const COLLISION_SPHERES* spheres)const;

	virtual bool isHit(const COLLISION* collision)const;
	virtual VECTOR3 isHit(const COLLISION_TERRAIN* collision)const;
	//ゲッター
	VECTOR3 pos()const { return *Pos; }
	float px()const { return Pos->x; }
	float py()const { return Pos->y; }
	float pz()const { return Pos->z; }
private:
	const VECTOR3* Pos = nullptr;
};

