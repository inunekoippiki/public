#pragma warning (disable:4996)
#include <string.h>
#include <stdlib.h>
#include<mbstring.h>
#include "../Library/GRAPHIC.h"
#include "DIALOG_SAVE_DELETE.h"
DIALOG_SAVE_DELETE::DIALOG_SAVE_DELETE() {
}

DIALOG_SAVE_DELETE::~DIALOG_SAVE_DELETE() {
}

void DIALOG_SAVE_DELETE::create(CONTAINER* c, STATIC_FONT* font,int saveDataIdx) {
	StringDialog.create(c, font);
	sprintf(String, "%s%d%s","セーブデータ", saveDataIdx,"を削除しますか？");
	StringPos.y = 485.0f;
	StringPos.x = GRAPHIC::instance()->centerX();
}

void DIALOG_SAVE_DELETE::init(){
	StringDialog.init();
}

void DIALOG_SAVE_DELETE::update(){
	StringDialog.update();
}

void DIALOG_SAVE_DELETE::draw(SHADER* shader) {
	StringDialog.draw(shader);
	StringDialog.drawLineStringCentered(shader, String, StringPos);
}
