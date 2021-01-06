#pragma warning (disable:4996)
#include <string.h>
#include <stdlib.h>
#include<mbstring.h>
#include "../Library/GRAPHIC.h"
#include "DIALOG_STORY_SKIP.h"
DIALOG_STORY_SKIP::DIALOG_STORY_SKIP() {
}

DIALOG_STORY_SKIP::~DIALOG_STORY_SKIP() {
}

void DIALOG_STORY_SKIP::create(CONTAINER* c,STATIC_FONT* font) {
	StringDialog.create(c, font);
	strcpy(String, "ストーリーをスキップしますか？");
	StringPos.y = 485.0f;
	StringPos.x = GRAPHIC::instance()->centerX();

}

void DIALOG_STORY_SKIP::init(){
	StringDialog.init();
}

void DIALOG_STORY_SKIP::update(){
	StringDialog.update();
}

void DIALOG_STORY_SKIP::draw(SHADER* shader) {
	StringDialog.draw(shader);
	StringDialog.drawLineStringCentered(shader, String, StringPos);
}
