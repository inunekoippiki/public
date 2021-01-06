#pragma warning (disable:4996)
#include <string.h>
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "DIALOG_SAVE_SELECT.h"
DIALOG_SAVE_SELECT::DIALOG_SAVE_SELECT() {
}

DIALOG_SAVE_SELECT::~DIALOG_SAVE_SELECT() {
}

void DIALOG_SAVE_SELECT::create(CONTAINER* c,STATIC_FONT* font, bool IsEnmptyData){
	StringDialog.create(c, font);
	if (IsEnmptyData) {
		strcpy(String, "�V�����Q�[�����n�߂܂����H");
	}
	else{
		strcpy(String, "�f�[�^�����[�h���܂����H");
	}
	StringPos.y = 485.0f;
	StringPos.x = GRAPHIC::instance()->centerX();
}

void DIALOG_SAVE_SELECT::init(){
	StringDialog.init();
}

void DIALOG_SAVE_SELECT::update(){
	StringDialog.update();
}

void DIALOG_SAVE_SELECT::draw(SHADER* shader){
	StringDialog.draw(shader);
	StringDialog.drawLineStringCentered(shader, String, StringPos);
}
