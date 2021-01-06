#pragma once
#include <vector>
#include "../Library/ARRAY.h"
#include "../Library/VECTOR3.h"
#include "BILLBOARD.h"
class TEXTURE;
class CONTAINER;
//光弾を描画するクラス
class BILLBOARD_ENTITY_LIGHT_BULLET :public BILLBOARD {
public:
	static void setGraphic(CONTAINER* container);
	static void freeGraphic();
	//プールに入っているオブジェクトを全て開放
	static void poolAllDelete();
	//プールからオブジェクトを取り出す無かったらインスタンスして渡す
	static BILLBOARD_ENTITY_LIGHT_BULLET* takeFromPool();
private:
	static ARRAY_P<TEXTURE> Textures[3];
	static std::vector<BILLBOARD_ENTITY_LIGHT_BULLET*> PoolList;
public:
	BILLBOARD_ENTITY_LIGHT_BULLET();
	~BILLBOARD_ENTITY_LIGHT_BULLET();
	void init(const VECTOR3& pos, float scale,int textureIdx);
	void update()override;
	void draw(SHADER* shader,const VECTOR3& rad)override;
	void addPool()override;//プールに追加。元のリストからは自分で消してね

	//ENTITYが呼ぶ
	void setPos(const VECTOR3& pos);
private:
	int Frame = 0;
	int TextureIdx = 0;
};

