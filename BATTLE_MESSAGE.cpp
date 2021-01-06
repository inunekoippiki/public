#include "../Library/common.h"
#include "UI_2D_LEFT.h"
#include "BATTLE_MESSAGE.h"
BATTLE_MESSAGE::BATTLE_MESSAGE(TEXT_DISP* text, UI_2D_LEFT* textbox) :
	Text(text),
	TextBox(textbox){
}

BATTLE_MESSAGE::~BATTLE_MESSAGE() {
	SAFE_DELETE(Text);
	SAFE_DELETE(TextBox);
}

void BATTLE_MESSAGE::update(){
}

void BATTLE_MESSAGE::draw(SHADER* shader, const VECTOR2& pos, const VECTOR2& scale, const COLOR& color) {
	draw(shader);
}

void BATTLE_MESSAGE::draw(SHADER* shader, const VECTOR2& pos, float rad, const VECTOR2& scale, const COLOR& color) {
	draw(shader);
}

void BATTLE_MESSAGE::draw(SHADER* shader){
	TextBox->draw(shader);
	Text->draw(shader);
}
