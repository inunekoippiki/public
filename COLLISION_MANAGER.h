#pragma once
class CONTAINER;
class COLLISION;
class COLLISIONS;
class COLLISION_TERRAIN;
//コリジョン管理クラス
//ここで種類ごとで、どれとどれが当たるを設定する
class COLLISION_MANAGER{
public:
	COLLISION_MANAGER(CONTAINER* c);
	~COLLISION_MANAGER();
	//当たり判定を実行。衝突したオブジェクトのhit関数などを呼び出す
	void exeCollision();
	//プレイヤー当たり判定グループに当たり判定オブジェクトを追加
	void addCollisionPlayer(COLLISION* collision);
	//エネミー当たり判定グループに当たり判定オブジェクトを追加
	void addCollisionEnemy(COLLISION* collision);
	//プレイヤー攻撃当たり判定グループに当たり判定オブジェクトを追加
	void addCollisionPlayerAttck(COLLISION* collision);
	//エネミー攻撃当たり判定グループに当たり判定オブジェクトを追加
	void addCollisionEnemyAttck(COLLISION* collision);
	//地形当たり判定オブジェクト
	const COLLISION_TERRAIN* collisionTerrain()const{ return CollisionTerrain; }
private:
	//deleteフラグが入っている当たり判定オブジェクトを配列から除く
	void deleteUpdate();

	COLLISION_TERRAIN* CollisionTerrain = nullptr;
	COLLISIONS* CollisionsPlayer = nullptr;
	COLLISIONS* CollisionsEnemy = nullptr;
	COLLISIONS* CollisionsPlayerAttck = nullptr;
	COLLISIONS* CollisionsEnemyAttck = nullptr;
};

