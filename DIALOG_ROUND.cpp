#pragma warning (disable:4996)
#include <string.h>
#include "../Library/GRAPHIC.h"
#include "DIALOG_ROUND.h"
DIALOG_ROUND::DIALOG_ROUND() {
}

DIALOG_ROUND::~DIALOG_ROUND() {
}

void DIALOG_ROUND::create(CONTAINER* c, STATIC_FONT* font,int round){
	StringDialog.create(c, font);
	sprintf(String, "‘æ%dÍ‚ð‚Í‚¶‚ß‚Ü‚·‚©H", round);
	StringPos.y = 485.0f;
	StringPos.x = GRAPHIC::instance()->centerX();
}

void DIALOG_ROUND::init(){
	StringDialog.init();
}

void DIALOG_ROUND::update(){
	StringDialog.update();
}

void DIALOG_ROUND::draw(SHADER* shader){
	StringDialog.draw(shader);
	StringDialog.drawLineStringCentered(shader, String, StringPos);
}
