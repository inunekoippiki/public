#pragma once
#include "../Library/VECTOR3.h"
#include "../Library/SHADER.h"
class COLLISION;
class GAME_DATA_COMMON;
class ENTITY_STATES;
class ENTITY_MANAGER;
class COLLISION_MANAGER;
class BILLBOARDS;
class EFFEKSSER;
class UI_MANAGER;
enum class ENTITY_TYPE {
	NONE,
	PLAYER,
	PLAYER_MELEE,
	PLAYER_SHOT,
	MEDAMA,
	HANA,
	BOSS,
	BALL,
	LIGHT_BULLET,
	LASER,
};

class ENTITY {
public:
	ENTITY();
	virtual ~ENTITY();
	virtual void update() = 0;
	virtual void draw(SHADER* shader) = 0;
	//�����蔻��ő���Ƃ���������Ă΂��
	virtual void hit(COLLISION* entity);
	virtual void damage(int damage);
	//�����蔻��Œn�`�Ƃ���������Ă΂��
	virtual void hit(const VECTOR3& pushBack);
	virtual ENTITY_TYPE entityType()const = 0;

	//Velo�̕�����Pos�𓮂���
	void posUpdate();
	//Velo�ɉ�����Rad���X�V
	void radUpdate();
	//�n����Velo�̕�����Rad���X�V
	void radUpdate(const VECTOR3& velo);
	//�w��̈ʒu����������
	void lookAt(const VECTOR3& pos);
	//ENTITY���폜
	void Delete() { DeleteFlag = true; }
	//���ɍ폜����Ă��邩
	bool isDelete() { return DeleteFlag; }

	//�R���W�����ɓn��ENTITY�̈ʒu
	const VECTOR3* posPtr() const { return &Pos; }
	VECTOR3 pos()const { return Pos; }
	float px()const { return Pos.x; }
	float py()const { return Pos.y; }
	float pz()const { return Pos.z; }
	VECTOR3 velo()const { return Velo; }
	float vx()const { return Velo.x; }
	float vy()const { return Velo.y; }
	float vz()const { return Velo.z; }
	VECTOR3 rad()const { return Rad; }
	float rx()const { return Rad.x; }
	float ry()const { return Rad.y; }
	float rz()const { return Rad.z; }
	//ENTITY�̒��S�̈ʒu��Ԃ�
	VECTOR3 centerPos();

	ENTITY_STATES* states() { return States; }

	//�Z�b�^�[
	void setPos(const VECTOR3& pos) { Pos = pos; }
	void setPx(float px) { Pos.x = px; }
	void setPy(float py) { Pos.x = py; }
	void setPz(float pz) { Pos.x = pz; }
	void setVelo(const VECTOR3& velo) { Velo = velo; }
	void setVx(float vx) { Velo.x = vx; }
	void setVy(float vy) { Velo.y = vy; }
	void setVz(float vz) { Velo.z = vz; }
	void setRad(const VECTOR3& rad) { Rad = rad; }
	void setRx(float rx) { Rad.x = rx; }
	void setRy(float ry) { Rad.y = ry; }
	void setRz(float rz) { Rad.z = rz; }

protected:
	ENTITY_STATES* States = 0;
	bool DeleteFlag = false;
	VECTOR3 Pos;
	VECTOR3 Velo;
	VECTOR3 Rad;
	VECTOR3 CenterPosOffest;
public:
	//�Z�b�^�[
	static void setGameDataCommon(GAME_DATA_COMMON* gameDataCommon) { GameDataCommon = gameDataCommon; }
	static void setEntityManager(ENTITY_MANAGER* entityManager) { EntityManager = entityManager; }
	static void setCollisionManager(COLLISION_MANAGER* collisionManager) { CollisionManager = collisionManager; }
	static void setBillboards(BILLBOARDS* billboards) { Billboards = billboards; }
	static void setEffeksser(EFFEKSSER* effeksser) { Effeksser = effeksser; }
	static void setUiManager(UI_MANAGER* uiManager) { UiManager = uiManager; }

	//�Q�b�^�[
	static GAME_DATA_COMMON* gameDataCommon() { return GameDataCommon; }
	static ENTITY_MANAGER* entityManager() { return EntityManager; }
	static COLLISION_MANAGER* collisionManager() { return CollisionManager; }
	static BILLBOARDS* billboards() { return Billboards; }
	static EFFEKSSER* effeksser() { return Effeksser; }
	static UI_MANAGER* uiManager() { return UiManager; }
private:
	static GAME_DATA_COMMON* GameDataCommon;
	static ENTITY_MANAGER* EntityManager;
	static COLLISION_MANAGER* CollisionManager;
	static BILLBOARDS* Billboards;
	static EFFEKSSER* Effeksser;
	static UI_MANAGER* UiManager;
};

