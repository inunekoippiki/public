#pragma once
#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/VECTOR3.h"
#include "UI_BASE.h"
//�g��k������_
class UI_3D_LEFT :public UI_BASE {
public:
	UI_3D_LEFT();
	~UI_3D_LEFT();
	void update();
	void draw(SHADER* shader);
	//�Z�b�^�[
	void setScale(const VECTOR2& scale) { Scale = scale; }
	void setPos(const VECTOR3& pos) { Pos = pos; }
	void setOffset(const VECTOR2& offset);
private:
	VECTOR2 Scale;
	VECTOR3 Pos;
	VECTOR2 Offset;
};

