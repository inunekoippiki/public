#pragma once
#include "UI_BASE.h"
//�E������UI��\������N���X
class UI_2D_RIGHT :public UI_BASE {
public:
	UI_2D_RIGHT();
	~UI_2D_RIGHT();
	void update();
	void draw(SHADER* shader);
	//�Z�b�^�[
	void setScale(const VECTOR2& scale) { Scale = scale; }
	void setPos(const VECTOR2& pos) { Pos = pos; }
	void setColor(const COLOR& color) { Color = color; }
private:
	VECTOR2 Scale;
	VECTOR2 Pos;
	COLOR Color;
};

