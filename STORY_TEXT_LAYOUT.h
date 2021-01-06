#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/STATIC_FONT.h"
#include "TEXT_DISP.h"
class CONTAINER;
class SHADER;
//1ページのテキストのクラス
class STORY_TEXT_LAYOUT {
public:
	STORY_TEXT_LAYOUT();
	~STORY_TEXT_LAYOUT();
	void create(CONTAINER* c,STATIC_FONT* font, TEXT_DISP* text, const char* charaName);
	//テキストを設定
	void setText(TEXT_DISP* text) { Text = text; }
	//全ての文字を表示する
	void allDisp();
	//最後まで表示されているか
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
	TEXT_DISP* Text = nullptr;//ページのテキスト
	char CharaName[256] = {};//ページを喋ってるキャラ名
};