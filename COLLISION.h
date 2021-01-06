#pragma once
class VECTOR3;
class STATE_MANAGER;
class COLLISION_SPHERE;
class COLLISION_POINT;
class COLLISION_CYLINDER;
class COLLISION_SPHERES;
class COLLISIONS;
class COLLISION_TERRAIN;
class ENTITY;
//�R���W�������
class COLLISION {
public:
	COLLISION();
	virtual ~COLLISION();
	//���ƏՓ˂��Ă��邩��Ԃ��܂�
	virtual bool isHit(const COLLISION_SPHERE* sphere)const;
	//�_�ƏՓ˂��Ă��邩��Ԃ��܂�
	virtual bool isHit(const COLLISION_POINT* point)const;
	//�~���ƏՓ˂��Ă��邩�Ԃ��܂�
	virtual bool isHit(const COLLISION_CYLINDER* point)const;
	//�����̋��ƏՓ˂��Ă��邩�Ԃ��܂�
	virtual bool isHit(const COLLISION_SPHERES* spheres)const;
	//�h�����m���ꂼ��֐������s�ł���
	virtual bool isHit(const COLLISION* collision)const;
	//�n�`�Ƃ̃R���W����
	virtual VECTOR3 isHit(const COLLISION_TERRAIN* collision)const;
	//���������G���e�B�e�B��������Ƃ��Ă�ǂ�
	void Delete();
	//�f�o�b�O�p�\��
	virtual void draw(STATE_MANAGER* stateManager);
	//���̃R���W�����������Ă���ENTITY
	ENTITY* entity() { return Entity; }
	//�R���W�������L����
	bool isCollision() { return IsCollision; }
	//���łɍ폜����Ă��邩
	bool isDelete() { return IsDelete; }
	//�Z�b�^�[
	void setIsCollision(bool isCollision) { IsCollision = isCollision; }
protected:
	bool IsDelete = false;
	bool IsCollision = false;
	ENTITY* Entity = nullptr;
};