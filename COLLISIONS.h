#pragma once
#include <vector>
class COLLISION;
class COLLISION_TERRAIN;
//コリジョンを当たる種類ごとに一纏めにしておくクラス
class COLLISIONS{
public:
	COLLISIONS();
	~COLLISIONS();
	//当たり判定オブジェクトをADD
	void add(COLLISION* collsion);
	//デリートフラグで更新
	void deleteUpdate();
	//当たり判定実行(地形用)
	void exeCollision(COLLISION_TERRAIN* collision);
	//当たり判定実行（同じCOLLISIONSを渡してしまうと２回hit関数が呼ばれてしまう）
	void exeCollision(COLLISIONS* collisions);
private:
	std::vector<COLLISION*> Collisions;
};

