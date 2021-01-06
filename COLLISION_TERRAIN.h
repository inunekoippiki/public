#pragma once
#include "COLLISION.h"
class VECTOR3;
class COLLISION_SPHERE;
class COLLISION_SPHERES;
class COLLISION_POINT;
class CONTAINER;
//プリミティブに対する押し出しベクトルさえ返してくれれば変更OK
//現在はただのAABB
class COLLISION_TERRAIN :public COLLISION {
public:
	COLLISION_TERRAIN(CONTAINER* c);
	~COLLISION_TERRAIN();
	//地形の形状が変わるとこれ全部変更------------------
	VECTOR3 collision(const COLLISION_SPHERE* sphere)const;
	VECTOR3 collision(const COLLISION_SPHERES* spheres)const;
	VECTOR3 collision(const COLLISION_POINT* sphere)const;

	//cvはカメラの向いてる方向のベクトル
	VECTOR3 collision(const VECTOR3& pos,const VECTOR3& cv)const;
private:
	float Floor = 0;
	float Sx = 0;
	float Sy = 0;
	float Sz = 0;
	float Ex = 0;
	float Ey = 0;
	float Ez = 0;
};

