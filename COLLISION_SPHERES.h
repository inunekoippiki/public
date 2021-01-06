#pragma once
#include <vector>
#include <functional>
#include "../Library/VECTOR3.h"
#include "COLLISION.h"
struct SPHERE{
	SPHERE(const VECTOR3& offset, float r) 
		:OffsetPos(offset), R(r) {
	};
	VECTOR3 OffsetPos;
	float R = 0.0f;
};
//�����̋���g�ݍ��킹���R���W����
//�L�����N�^�[�Ƃ��ɂ���g��
class COLLISION_SPHERES:public COLLISION{
public:
	COLLISION_SPHERES(ENTITY* entity,const VECTOR3* pos);
	~COLLISION_SPHERES();
	bool isHit(const COLLISION_SPHERE* sphere)const;
	bool isHit(const COLLISION_POINT* point)const;
	bool isHit(const COLLISION_CYLINDER* sylinder)const;
	bool isHit(const COLLISION_SPHERES* spheres)const;

	virtual bool isHit(const COLLISION* collision)const;
	virtual VECTOR3 isHit(const COLLISION_TERRAIN* collision)const;

	//�ŏ��Ɏg�����m�ۂ����ق����ǂ�
	void reserve(int num);
	//�����蔻��ɋ���ǉ�
	void add(const VECTOR3& offset,float r);
	//�Q�b�^�[
	VECTOR3 pos() const { return *Pos; }
	float px()const { return Pos->x; }
	float py()const { return Pos->y; }
	float pz()const { return Pos->z; }
	const std::vector<SPHERE>& spheres()const { return Spheres; }
	//�f�o�b�O�p�\��
	void draw(STATE_MANAGER* stateManager);
private:
	const VECTOR3* Pos = nullptr;
	std::vector<SPHERE> Spheres;

};

