#pragma once
#include <vector>
#include "BILLBOARD.h"
class CONTAINER;
class TEXTURE;

class BILLBOARD_HIT : public BILLBOARD {
public:
	static void setGraphic(CONTAINER* container);
	static void freeGraphic();
	//プールに入っているオブジェクトを全て開放
	static void poolAllDelete();
	//プールからオブジェクトを取り出す無かったらインスタンスして渡す
	static BILLBOARD_HIT* takeFromPool();
private:
	static TEXTURE** Textures;
	static int NumTextures;
	static std::vector<BILLBOARD_HIT*> PoolList;
public:
	BILLBOARD_HIT();
	~BILLBOARD_HIT();
	void init(const VECTOR3& pos, float scale);
	void update()override;
	void draw(SHADER* shader, const VECTOR3& rad)override;
	void addPool()override;//プールに追加。元のリストからは自分で消してね
private:
	int AnimCnt = 0;
	int AnimIdx = 0;
};