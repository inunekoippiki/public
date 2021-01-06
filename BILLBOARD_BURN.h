#pragma once
#include <vector>
#include "BILLBOARD.h"
class CONTAINER;
class TEXTURE;
class BILLBOARD_BURN : public BILLBOARD {
public:
	static void setGraphic(CONTAINER* container);
	static void freeGraphic();
	//�v�[���ɓ����Ă���I�u�W�F�N�g��S�ĊJ��
	static void poolAllDelete();
	//�v�[������I�u�W�F�N�g�����o������������C���X�^���X���ēn��
	static BILLBOARD_BURN* takeFromPool();
private:
	static TEXTURE** Textures;
	static int NumTextures;
	static std::vector<BILLBOARD_BURN*> PoolList;
public:
	BILLBOARD_BURN();
	~BILLBOARD_BURN();
	void init(const VECTOR3& pos, float scale);
	void update()override;
	void draw(SHADER* shader, const VECTOR3& rad)override;
	void addPool()override;//�v�[���ɒǉ��B���̃��X�g����͎����ŏ����Ă�
private:
	int AnimCnt = 0;
	int AnimIdx = 0;

};