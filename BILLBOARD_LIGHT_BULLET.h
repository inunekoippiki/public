#pragma once
#include <vector>
#include "../Library/ARRAY.h"
#include "../Library/VECTOR3.h"
#include "BILLBOARD.h"
class TEXTURE;
class CONTAINER;
//光弾を描画するクラス
class BILLBOARD_LIGHT_BULLET :public BILLBOARD {
public:
	static void setGraphic(CONTAINER* container);
	static void freeGraphic();
	//プールに入っているオブジェクトを全て開放
	static void poolAllDelete();
	//プールからオブジェクトを取り出す無かったらインスタンスして渡す
	static BILLBOARD_LIGHT_BULLET* takeFromPool();
private:
	static ARRAY_P<TEXTURE> Textures;
	static std::vector<BILLBOARD_LIGHT_BULLET*> PoolList;
public:
	BILLBOARD_LIGHT_BULLET();
	~BILLBOARD_LIGHT_BULLET();
	void init(const VECTOR3& pos, const VECTOR3& velo, float scale);
	void update()override;
	void draw(SHADER* shader, const VECTOR3& rad)override;
	void addPool()override;//プールに追加。元のリストからは自分で消してね
private:
	VECTOR3 Velocity;
	int LifeTime = 0;
	int Frame = 0;
};

