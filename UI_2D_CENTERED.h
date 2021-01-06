#pragma once
#include "UI_BASE.h"
//����������UI��\������N���X
class UI_2D_CENTERED :public UI_BASE {
public:
	UI_2D_CENTERED();
	~UI_2D_CENTERED();
	void update();
	void draw(SHADER* shader);
	//�Z�b�^�[
	void setScale(const VECTOR2& scale) { Scale = scale; }
	void setPos(const VECTOR2& pos) { Pos = pos; }
	void setColor(const COLOR& color) { Color = color; }
	void setRad(float rad) { Rad = rad; }
private:
	VECTOR2 Scale;
	VECTOR2 Pos;
	COLOR Color;
	float Rad = 0.0f;
};

