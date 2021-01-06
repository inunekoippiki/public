#pragma warning (disable:4996)
#include <string.h>
#include "../Library/GRAPHIC.h"
#include "../Library/TEXTURE.h"
#include "../Library/VECTOR2.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "DIALOG_OPTION_EXIT.h"
DIALOG_OPTION_EXIT::DIALOG_OPTION_EXIT() {
}

DIALOG_OPTION_EXIT::~DIALOG_OPTION_EXIT() {
}

void DIALOG_OPTION_EXIT::create(CONTAINER* c,STATIC_FONT* font) {
	StringDialog.create(c, font);
	sprintf(String, "ƒQ[ƒ€‚ðI—¹‚µ‚Ü‚·‚©H");
	StringPos.y = 485.0f;
	StringPos.x = GRAPHIC::instance()->centerX();
}

void DIALOG_OPTION_EXIT::init(){
	StringDialog.init();
}

void DIALOG_OPTION_EXIT::update(){
	StringDialog.update();
}

void DIALOG_OPTION_EXIT::draw(SHADER* shader) {
	StringDialog.draw(shader);
	StringDialog.drawLineStringCentered(shader, String, StringPos);
}
