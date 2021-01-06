#pragma warning (disable:4996)
#include <time.h>
#include <chrono>
#include "../Library/STATIC_FONT.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "SAVE_SELECT_UI_SAVE_DATA.h"
SAVE_SELECT_UI_SAVE_DATA::SAVE_SELECT_UI_SAVE_DATA() {
}

void SAVE_SELECT_UI_SAVE_DATA::create(
	CONTAINER* c,
	STATIC_FONT* font,
	const VECTOR2& pos, 
	time_t saveTime, 
	time_t playTime){
	Pos = pos;
	Font = font;
	FontSize = c->data("SAVE_SELECT_UI_SAVE_DATA::FontSize");

	tm saveTimeTm;
	localtime_s(&saveTimeTm, &saveTime);
	//セーブ時間を文字列化
	sprintf(string1, "%04d/%02d/%02d %02d:%02d:%02d",
		saveTimeTm.tm_year + 1900,
		saveTimeTm.tm_mon + 1,
		saveTimeTm.tm_mday,
		saveTimeTm.tm_hour,
		saveTimeTm.tm_min,
		saveTimeTm.tm_sec);
	tm playTimeTm; 
	localtime_s(&playTimeTm, &playTime);
	//プレイ時間を文字列化
	sprintf(string2, "プレイ時間 %02d:%02d:%02d",
		playTimeTm.tm_hour,
		playTimeTm.tm_min,
		playTimeTm.tm_sec);
}

SAVE_SELECT_UI_SAVE_DATA::~SAVE_SELECT_UI_SAVE_DATA() {
}

void SAVE_SELECT_UI_SAVE_DATA::draw(SHADER* shader){
	Font->draw(shader, string1, Pos, VECTOR2(FontSize, FontSize));
	Font->draw(shader, string2, Pos+VECTOR2(0.0f, (float)FontSize), VECTOR2(FontSize, FontSize));
}
