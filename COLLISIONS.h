#pragma once
#include <vector>
class COLLISION;
class COLLISION_TERRAIN;
//�R���W�����𓖂����ނ��ƂɈ�Z�߂ɂ��Ă����N���X
class COLLISIONS{
public:
	COLLISIONS();
	~COLLISIONS();
	//�����蔻��I�u�W�F�N�g��ADD
	void add(COLLISION* collsion);
	//�f���[�g�t���O�ōX�V
	void deleteUpdate();
	//�����蔻����s(�n�`�p)
	void exeCollision(COLLISION_TERRAIN* collision);
	//�����蔻����s�i����COLLISIONS��n���Ă��܂��ƂQ��hit�֐����Ă΂�Ă��܂��j
	void exeCollision(COLLISIONS* collisions);
private:
	std::vector<COLLISION*> Collisions;
};

