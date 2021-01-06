#pragma once
#include "UI_BASE.h"
#include "../Library/VECTOR2.h"
#include "../Library/VECTOR3.h"
//�őO�ʃr���{�[�h
//���S��_
class UI_3D_CENTERED :public UI_BASE{
public:
	UI_3D_CENTERED();
	~UI_3D_CENTERED();
	virtual void update();
	virtual void draw(SHADER* shader);
	//�Z�b�^�[
	void setScale(const VECTOR2& scale) { Scale = scale; }
	void setPos(const VECTOR3& pos) { Pos = pos; }
private:
	VECTOR2 Scale;
	VECTOR3 Pos;
};

