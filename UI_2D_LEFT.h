#pragma once
#include "../Library/COLOR.h"
#include "../Library/MATRIX.h"
#include "../Library/VECTOR2.h"
#include "UI_BASE.h"
//��������UI��\������N���X
class UI_2D_LEFT :public UI_BASE {
public:
	UI_2D_LEFT();
	~UI_2D_LEFT();
	void update();
	void draw(SHADER* shader);
	//�Z�b�^�[
	void setScale(const VECTOR2& scale) { Scale = scale; }
	void setPos(const VECTOR2& pos) { Pos = pos; }
	void setColor(const COLOR& color) { Color = color; }
protected:
	VECTOR2 Scale;
	VECTOR2 Pos;
	COLOR Color;
};

