#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION.h"
//始点からの無限円柱
class COLLISION_CYLINDER:public COLLISION{
public:
	COLLISION_CYLINDER(ENTITY* entity, const VECTOR3* pos,const VECTOR3& v/*正規化して*/,float r/*半径*/);
	~COLLISION_CYLINDER();
	bool isHit(const COLLISION_SPHERE* sphere)const;
	bool isHit(const COLLISION_POINT* point)const;
	bool isHit(const COLLISION_CYLINDER* sylinder)const;
	bool isHit(const COLLISION_SPHERES* spheres)const;
	void setRadius(float r) { R = r; }
	void setVelo(const VECTOR3& velo) { V = velo; }
	//ゲッター
	VECTOR3 pos()const { return *Pos; }
	float px()const { return Pos->x; }
	float py()const { return Pos->y; }
	float pz()const { return Pos->z; }
	VECTOR3 v()const { return V; }
	float r()const { return R; }
private:
	const VECTOR3* Pos = nullptr;
	VECTOR3 V;//レーザーの向き
	float R = 0.0f;
};

