#pragma once
#include "../Library/VECTOR3.h"
class SHADER;
//Base Class!!!!!!!
class BILLBOARD {
public:
	BILLBOARD() {};
	~BILLBOARD() {};
	virtual void update() = 0;
	virtual void draw(SHADER* shader,const VECTOR3& rad) = 0;
	//プールに自分を追加する
	virtual void addPool() = 0;
	//カメラからの距離を計算する
	void calcDistance(const VECTOR3& cameraPos, const VECTOR3& lookatVec);
	//生存時間
	int life()const { return Life; }
	//カメラからの距離
	float distance()const { return Distance; }
	//削除
	void Delete() { Life = 0; };
protected:
	VECTOR3 Pos;
	float Scale = 0;
	int Life = 0;
	float Distance = 0;//カメラからの距離	
	float Aspect = 0;
};

