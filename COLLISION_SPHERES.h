#pragma once
#include <vector>
#include <functional>
#include "../Library/VECTOR3.h"
#include "COLLISION.h"
struct SPHERE{
	SPHERE(const VECTOR3& offset, float r) 
		:OffsetPos(offset), R(r) {
	};
	VECTOR3 OffsetPos;
	float R = 0.0f;
};
//複数の球を組み合わせたコリジョン
//キャラクターとかにこれ使う
class COLLISION_SPHERES:public COLLISION{
public:
	COLLISION_SPHERES(ENTITY* entity,const VECTOR3* pos);
	~COLLISION_SPHERES();
	bool isHit(const COLLISION_SPHERE* sphere)const;
	bool isHit(const COLLISION_POINT* point)const;
	bool isHit(const COLLISION_CYLINDER* sylinder)const;
	bool isHit(const COLLISION_SPHERES* spheres)const;

	virtual bool isHit(const COLLISION* collision)const;
	virtual VECTOR3 isHit(const COLLISION_TERRAIN* collision)const;

	//最初に使う分確保したほうが良い
	void reserve(int num);
	//当たり判定に球を追加
	void add(const VECTOR3& offset,float r);
	//ゲッター
	VECTOR3 pos() const { return *Pos; }
	float px()const { return Pos->x; }
	float py()const { return Pos->y; }
	float pz()const { return Pos->z; }
	const std::vector<SPHERE>& spheres()const { return Spheres; }
	//デバッグ用表示
	void draw(STATE_MANAGER* stateManager);
private:
	const VECTOR3* Pos = nullptr;
	std::vector<SPHERE> Spheres;

};

