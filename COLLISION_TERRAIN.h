#pragma once
#include "COLLISION.h"
class VECTOR3;
class COLLISION_SPHERE;
class COLLISION_SPHERES;
class COLLISION_POINT;
class CONTAINER;
//�v���~�e�B�u�ɑ΂��鉟���o���x�N�g�������Ԃ��Ă����ΕύXOK
//���݂͂�����AABB
class COLLISION_TERRAIN :public COLLISION {
public:
	COLLISION_TERRAIN(CONTAINER* c);
	~COLLISION_TERRAIN();
	//�n�`�̌`�󂪕ς��Ƃ���S���ύX------------------
	VECTOR3 collision(const COLLISION_SPHERE* sphere)const;
	VECTOR3 collision(const COLLISION_SPHERES* spheres)const;
	VECTOR3 collision(const COLLISION_POINT* sphere)const;

	//cv�̓J�����̌����Ă�����̃x�N�g��
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

