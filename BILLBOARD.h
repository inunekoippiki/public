#pragma once
#include "../Library/VECTOR3.h"
class SHADER;
//Base Class!!!!!!!
class BILLBOARD {
public:
	BILLBOARD() {};
	~BILLBOARD() {};
	virtual void update() = 0;
	virtual void draw(SHADER* shader,const VECTOR3& rad) = 0;
	//�v�[���Ɏ�����ǉ�����
	virtual void addPool() = 0;
	//�J��������̋������v�Z����
	void calcDistance(const VECTOR3& cameraPos, const VECTOR3& lookatVec);
	//��������
	int life()const { return Life; }
	//�J��������̋���
	float distance()const { return Distance; }
	//�폜
	void Delete() { Life = 0; };
protected:
	VECTOR3 Pos;
	float Scale = 0;
	int Life = 0;
	float Distance = 0;//�J��������̋���	
	float Aspect = 0;
};

