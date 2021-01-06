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
//エンティティマネージャークラス
//各エンティティのインスタンスもここ
class ENTITY_MANAGER {
public:
	ENTITY_MANAGER(CONTAINER* container);
	~ENTITY_MANAGER();
	//召喚
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
	//各エンティティに対して処理を実行する
	void execute(std::function<void(ENTITY*)> func);
	//指定の条件のENTITYを見つけてくる
	ENTITY* entitySearch(std::function<bool(const ENTITY*)> func);
	//指定の条件が一番少ないENTITYを見つけてくる
	ENTITY* whereMin(std::function<float(const ENTITY*)> func);
	ENTITY* whereMin(std::function<float(const ENTITY*)> func,float& min);

	void EntitySummon();//一時エンティティリストを本エンティティリストに移す

	static void setCollisionManager(COLLISION_MANAGER* collisionManager) { CollisionManager = collisionManager; }
	static void setBillboards(BILLBOARDS* billboards) { Billboards = billboards; }
private:
	std::vector<ENTITY*> EntitysTemp;//実際ENTITYが召喚されるのはupdate後。そのためのバッファ
	std::vector<ENTITY*> Entitys;
	
	CONTAINER* Container = nullptr;
	static COLLISION_MANAGER* CollisionManager;
	static BILLBOARDS* Billboards;

};

