#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION.h"
//�n�_����̖����~��
class COLLISION_CYLINDER:public COLLISION{
public:
	COLLISION_CYLINDER(ENTITY* entity, const VECTOR3* pos,const VECTOR3& v/*���K������*/,float r/*���a*/);
	~COLLISION_CYLINDER();
	bool isHit(const COLLISION_SPHERE* sphere)const;
	bool isHit(const COLLISION_POINT* point)const;
	bool isHit(const COLLISION_CYLINDER* sylinder)const;
	bool isHit(const COLLISION_SPHERES* spheres)const;
	void setRadius(float r) { R = r; }
	void setVelo(const VECTOR3& velo) { V = velo; }
	//�Q�b�^�[
	VECTOR3 pos()const { return *Pos; }
	float px()const { return Pos->x; }
	float py()const { return Pos->y; }
	float pz()const { return Pos->z; }
	VECTOR3 v()const { return V; }
	float r()const { return R; }
private:
	const VECTOR3* Pos = nullptr;
	VECTOR3 V;//���[�U�[�̌���
	float R = 0.0f;
};

