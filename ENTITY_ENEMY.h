#pragma once
#include "../Library/TREE.h"
#include "ENTITY.h"
#include "HP_GAUGE.h"
class SHADER;
class UPGRADE;
class ENTITY_PLAYER;
class TREE_ORIGIN;
class ENTITY_ENEMY{
public:
	ENTITY_ENEMY();
	~ENTITY_ENEMY();
	void create(ENTITY* owner,const VECTOR3& upperPosOffest,const TREE_ORIGIN* treeOrigin,int maxHp,float gravity);
	//���f�����A�b�v�f�[�g����
	void treeUpdate();
	//�_���[�W��^����
	void damage(int damage);
	//�d�͂̃A�b�v�f�[�g
	void gravityUpdate();
	//�`��
	void draw(SHADER* shader);
	//HP�Q�[�W�̈ʒu���X�V����
	void hpGaugeUpdate();
	//HP�Q�[�W�̕����X�V����
	void hpGaugeWidthUpdate();
	//kill����
	void death() { IsDeath = true; }
	//���őO�̓_�ł̃A�b�v�f�[�g
	void DisappearUpdate(int DisappearCnt);
	//�_�ł�����t���O��ݒ�
	void setIsDisappear(bool isDisappear) { IsDisappear = isDisappear; };
	//���f��
	TREE* tree() { return &Tree; }
	//�_�ł̊Ԋu
	int disappearTime() { return DisappearTime; }
	//���Ɏ���ł��邩
	bool isDeath() { return IsDeath; }
	//������d��
	float gravity() { return Gravity; }
	//����̍��W
	VECTOR3 upperPos();
	//�̗�
	const HIT_POINT& hitPoint() { return HitPoint; }
private:
	ENTITY* Owner = nullptr;
	TREE Tree;
	VECTOR3 UpperPosOffest;
	HIT_POINT HitPoint;
	int DisappearTime = 0;//����ł�����ł܂ł̎���
	int DisappearFrequency = 0;//�_�ł̕p�x
	bool IsDisappear = false;//����ł��������܂œ_�ł�����ׂ̕`�悵�Ȃ��t���O
	bool IsDeath = false;//Hp���O�œ|���ꂽ�t���O
	float Gravity = 0.0f;
	HP_GAUGE HpGauge;

public:
	static void setUpgrade(UPGRADE* upgrade) { Upgrade = upgrade; }
	static void setPlayer(ENTITY_PLAYER* player) { Player = player; }
	static ENTITY_PLAYER* player() { return Player; }
private:
	static UPGRADE* Upgrade;//�^�����_���[�W�̗݌v�������������Ă�
	static ENTITY_PLAYER* Player;
};

