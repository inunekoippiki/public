#pragma warning (disable:4996)
#include <string.h>
#include "../Library/GRAPHIC.h"
#include "DIALOG_OPTION_TITLE.h"
DIALOG_OPTION_TITLE::DIALOG_OPTION_TITLE() {
}

DIALOG_OPTION_TITLE::~DIALOG_OPTION_TITLE() {
}

void DIALOG_OPTION_TITLE::create(CONTAINER* c,STATIC_FONT* font) {
	StringDialog.create(c, font);
	sprintf(String, "タイトルに戻りますか？");
	StringPos.y = 485.0f;
	StringPos.x = GRAPHIC::instance()->centerX();
}

void DIALOG_OPTION_TITLE::init(){
	StringDialog.init();
}

void DIALOG_OPTION_TITLE::update(){
	StringDialog.update();
}

void DIALOG_OPTION_TITLE::draw(SHADER* shader) {
	StringDialog.draw(shader);
	StringDialog.drawLineStringCentered(shader, String, StringPos);
}
