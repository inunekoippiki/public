#pragma once
#include <vector>
#include "../Library/ARRAY.h"
#include "BILLBOARD.h"
class CONTAINER;
class TEXTURE;
class VECTOR2;
//レーザーを描画するクラス
class BILLBOARD_LASER : public BILLBOARD {
public:
	static void setGraphic(CONTAINER* container);
	static void freeGraphic();
	//プールに入っているオブジェクトを全て開放
	static void poolAllDelete();
	//プールからオブジェクトを取り出す無かったらインスタンスして渡す
	static BILLBOARD_LASER* takeFromPool();
private:
	static ARRAY_P<TEXTURE> Textures[2];
	static std::vector<BILLBOARD_LASER*> PoolList;
public:
	BILLBOARD_LASER();
	~BILLBOARD_LASER();
	void init(const VECTOR3& pos, const VECTOR3& rad, float laserSize, float laserLength, int lifeTime ,int textureIdx);
	void init(const VECTOR3& pos1, const VECTOR3& pos2, float laserSize, int lifeTime, int textureIdx);

	void update()override;
	void draw(SHADER* shader, const VECTOR3& rad)override;
	void addPool()override;//プールに追加。元のリストからは自分で消してね
	void setLifeTime(int lifeTime) { LifeTime = lifeTime; }
private:
	unsigned RadCnt = 0;
	VECTOR3 Rad;
	float LaserSize = 0;
	float LaserLength = 0;
	int MaxLifeTime = 0;
	int LifeTime = 0;
	int TextureIdx = 0;
	int Frame = 0;

	float rotate(const VECTOR2& pos, const VECTOR2& b);

};