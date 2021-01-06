#pragma once
#include <vector>
#include "../Library/ARRAY.h"
#include "../Library/VECTOR3.h"
#include "BILLBOARD.h"
class TEXTURE;
class CONTAINER;
//���e��`�悷��N���X
class BILLBOARD_LIGHT_BULLET :public BILLBOARD {
public:
	static void setGraphic(CONTAINER* container);
	static void freeGraphic();
	//�v�[���ɓ����Ă���I�u�W�F�N�g��S�ĊJ��
	static void poolAllDelete();
	//�v�[������I�u�W�F�N�g�����o������������C���X�^���X���ēn��
	static BILLBOARD_LIGHT_BULLET* takeFromPool();
private:
	static ARRAY_P<TEXTURE> Textures;
	static std::vector<BILLBOARD_LIGHT_BULLET*> PoolList;
public:
	BILLBOARD_LIGHT_BULLET();
	~BILLBOARD_LIGHT_BULLET();
	void init(const VECTOR3& pos, const VECTOR3& velo, float scale);
	void update()override;
	void draw(SHADER* shader, const VECTOR3& rad)override;
	void addPool()override;//�v�[���ɒǉ��B���̃��X�g����͎����ŏ����Ă�
private:
	VECTOR3 Velocity;
	int LifeTime = 0;
	int Frame = 0;
};

