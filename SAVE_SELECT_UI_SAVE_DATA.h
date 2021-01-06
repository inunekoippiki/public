#pragma once
#include "../Library/VECTOR2.h"
#include "UI_BASE.h"
class STATIC_FONT;
class SHADER;
class VECTOR2;
class CONTAINER;
//�Z�[�u�f�[�^�̘g���̏���`�悷��N���X
class SAVE_SELECT_UI_SAVE_DATA{
public:
	SAVE_SELECT_UI_SAVE_DATA();
	void create(
		CONTAINER* c, 
		STATIC_FONT* font,
		const VECTOR2& pos,
		time_t saveTime,
		time_t playTime);
	~SAVE_SELECT_UI_SAVE_DATA();
	void draw(SHADER* shader);
private:
	VECTOR2 Pos;
	STATIC_FONT* Font = nullptr;
	int FontSize = 0;
	char string1[256] = {};
	char string2[256] = {};
};

