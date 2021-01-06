#pragma once
class CONTAINER;
class COLLISION;
class COLLISIONS;
class COLLISION_TERRAIN;
//�R���W�����Ǘ��N���X
//�����Ŏ�ނ��ƂŁA�ǂ�Ƃǂꂪ�������ݒ肷��
class COLLISION_MANAGER{
public:
	COLLISION_MANAGER(CONTAINER* c);
	~COLLISION_MANAGER();
	//�����蔻������s�B�Փ˂����I�u�W�F�N�g��hit�֐��Ȃǂ��Ăяo��
	void exeCollision();
	//�v���C���[�����蔻��O���[�v�ɓ����蔻��I�u�W�F�N�g��ǉ�
	void addCollisionPlayer(COLLISION* collision);
	//�G�l�~�[�����蔻��O���[�v�ɓ����蔻��I�u�W�F�N�g��ǉ�
	void addCollisionEnemy(COLLISION* collision);
	//�v���C���[�U�������蔻��O���[�v�ɓ����蔻��I�u�W�F�N�g��ǉ�
	void addCollisionPlayerAttck(COLLISION* collision);
	//�G�l�~�[�U�������蔻��O���[�v�ɓ����蔻��I�u�W�F�N�g��ǉ�
	void addCollisionEnemyAttck(COLLISION* collision);
	//�n�`�����蔻��I�u�W�F�N�g
	const COLLISION_TERRAIN* collisionTerrain()const{ return CollisionTerrain; }
private:
	//delete�t���O�������Ă��铖���蔻��I�u�W�F�N�g��z�񂩂珜��
	void deleteUpdate();

	COLLISION_TERRAIN* CollisionTerrain = nullptr;
	COLLISIONS* CollisionsPlayer = nullptr;
	COLLISIONS* CollisionsEnemy = nullptr;
	COLLISIONS* CollisionsPlayerAttck = nullptr;
	COLLISIONS* CollisionsEnemyAttck = nullptr;
};

