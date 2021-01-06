#pragma once
#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/VECTOR3.h"
#include "UI_BASE.h"
//拡大縮小左基点
class UI_3D_LEFT :public UI_BASE {
public:
	UI_3D_LEFT();
	~UI_3D_LEFT();
	void update();
	void draw(SHADER* shader);
	//セッター
	void setScale(const VECTOR2& scale) { Scale = scale; }
	void setPos(const VECTOR3& pos) { Pos = pos; }
	void setOffset(const VECTOR2& offset);
private:
	VECTOR2 Scale;
	VECTOR3 Pos;
	VECTOR2 Offset;
};

