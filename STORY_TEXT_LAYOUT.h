#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/STATIC_FONT.h"
#include "TEXT_DISP.h"
class CONTAINER;
class SHADER;
//1�y�[�W�̃e�L�X�g�̃N���X
class STORY_TEXT_LAYOUT {
public:
	STORY_TEXT_LAYOUT();
	~STORY_TEXT_LAYOUT();
	void create(CONTAINER* c,STATIC_FONT* font, TEXT_DISP* text, const char* charaName);
	//�e�L�X�g��ݒ�
	void setText(TEXT_DISP* text) { Text = text; }
	//�S�Ă̕�����\������
	void allDisp();
	//�Ō�܂ŕ\������Ă��邩
	bool isEnd();
	void update();
	void draw(SHADER* shader);

private:
	STATIC_FONT* Font = nullptr;
	int FontSize = 0;
	VECTOR2 TextBoxPos;
	VECTOR2 TextPos;
	VECTOR2 CharaNamePos;
	TEXTURE* TextureTextBox = nullptr;
	TEXT_DISP* Text = nullptr;//�y�[�W�̃e�L�X�g
	char CharaName[256] = {};//�y�[�W�𒝂��Ă�L������
};