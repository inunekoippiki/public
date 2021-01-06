#pragma once
#include <vector>
#include <functional>
class CONTAINER;
class SHADER;
class COLLISION_MANAGER;
class BILLBOARDS;

class ENTITY;
class ENTITY_HANA;
class ENTITY_MEDAMA;
class ENTITY_LIGHT_BULLET_BOSS;
class ENTITY_LIGHT_BULLET_MEDAMA;
class ENTITY_PLAYER;
class ENTITY_PLAYER_SHOT;
class ENTITY_PLAYER_MELEE;
class ENTITY_BOSS;
class ENTITY_LASER_BOSS;
class ENTITY_LASER_HANA;
class ENTITY_ENEMY_SPAWNER;
//�G���e�B�e�B�}�l�[�W���[�N���X
//�e�G���e�B�e�B�̃C���X�^���X������
class ENTITY_MANAGER {
public:
	ENTITY_MANAGER(CONTAINER* container);
	~ENTITY_MANAGER();
	//����
	ENTITY_MEDAMA* appearMedama(const VECTOR3& pos);
	ENTITY_HANA* appearHana(const VECTOR3& pos);
	ENTITY_PLAYER* appearPlayer(const VECTOR3& pos);
	ENTITY_LIGHT_BULLET_BOSS* appearLightBulletBoss(const VECTOR3& pos, const VECTOR3& velo, int damage, float r);
	ENTITY_LIGHT_BULLET_MEDAMA* appearLightBulletMedama(const VECTOR3& pos, const VECTOR3& velo, int damage, float r);
	ENTITY_LASER_BOSS* appearLaserBoss(const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime);
	ENTITY_LASER_HANA* appearLaserHana(const VECTOR3& pos, const VECTOR3& vec, float r, int damage, int lifeTime);
	ENTITY_PLAYER_SHOT* appearPlayerShot(const VECTOR3& pos, const VECTOR3& velo, float collisionRadius, int damage);
	ENTITY_PLAYER_MELEE* appearPlayerMelee(const VECTOR3& pos, float collisionRadius, int damage);
	ENTITY_BOSS* appearBoss(const VECTOR3& pos);
	void update();
	void draw(SHADER* shader);
	//�e�G���e�B�e�B�ɑ΂��ď��������s����
	void execute(std::function<void(ENTITY*)> func);
	//�w��̏�����ENTITY�������Ă���
	ENTITY* entitySearch(std::function<bool(const ENTITY*)> func);
	//�w��̏�������ԏ��Ȃ�ENTITY�������Ă���
	ENTITY* whereMin(std::function<float(const ENTITY*)> func);
	ENTITY* whereMin(std::function<float(const ENTITY*)> func,float& min);

	void EntitySummon();//�ꎞ�G���e�B�e�B���X�g��{�G���e�B�e�B���X�g�Ɉڂ�

	static void setCollisionManager(COLLISION_MANAGER* collisionManager) { CollisionManager = collisionManager; }
	static void setBillboards(BILLBOARDS* billboards) { Billboards = billboards; }
private:
	std::vector<ENTITY*> EntitysTemp;//����ENTITY�����������̂�update��B���̂��߂̃o�b�t�@
	std::vector<ENTITY*> Entitys;
	
	CONTAINER* Container = nullptr;
	static COLLISION_MANAGER* CollisionManager;
	static BILLBOARDS* Billboards;

};

