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
//コリジョン基底
class COLLISION {
public:
	COLLISION();
	virtual ~COLLISION();
	//球と衝突しているかを返します
	virtual bool isHit(const COLLISION_SPHERE* sphere)const;
	//点と衝突しているかを返します
	virtual bool isHit(const COLLISION_POINT* point)const;
	//円柱と衝突しているか返します
	virtual bool isHit(const COLLISION_CYLINDER* point)const;
	//複数の球と衝突しているか返します
	virtual bool isHit(const COLLISION_SPHERES* spheres)const;
	//派生同士それぞれ関数を実行できる
	virtual bool isHit(const COLLISION* collision)const;
	//地形とのコリジョン
	virtual VECTOR3 isHit(const COLLISION_TERRAIN* collision)const;
	//生成したエンティティが消えるとき呼んどく
	void Delete();
	//デバッグ用表示
	virtual void draw(STATE_MANAGER* stateManager);
	//このコリジョンを持っているENTITY
	ENTITY* entity() { return Entity; }
	//コリジョンが有効か
	bool isCollision() { return IsCollision; }
	//すでに削除されているか
	bool isDelete() { return IsDelete; }
	//セッター
	void setIsCollision(bool isCollision) { IsCollision = isCollision; }
protected:
	bool IsDelete = false;
	bool IsCollision = false;
	ENTITY* Entity = nullptr;
};