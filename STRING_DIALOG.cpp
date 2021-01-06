#include "../Library/CONTAINER.h"
#include "../Library/GRAPHIC.h"
#include "DATA_LIB.h"
#include "STRING_DIALOG.h"
STRING_DIALOG::STRING_DIALOG() {
}

STRING_DIALOG::~STRING_DIALOG() {
}

void STRING_DIALOG::create(CONTAINER* c, STATIC_FONT* font) {
	Font = font;
	FontSize = c->data("DIALOG::FontSize");
	FontColor = DATA_LIB::color(c, "DIALOG::FontColor");
	LineColor = DATA_LIB::color(c, "DIALOG::LineColor");
	Dialog.create(
		c,
		c->texture("commandWindowSelectIcon"),
		VECTOR2(600.0f, 710.0f),
		VECTOR2(1030.0f, 710.0f),
		c->texture("commandWindowEmptyYesNo"),
		VECTOR2(465.0f, 280.0f)
	);
	LineTexture = c->texture("commandWindowLine");
}

void STRING_DIALOG::setFontSize(int fontSize){
	FontSize = fontSize;
}

void STRING_DIALOG::init(){
	Dialog.init();
}

void STRING_DIALOG::update(){
	Dialog.update();
}

void STRING_DIALOG::draw(SHADER* shader){
	Dialog.windowDraw(shader);
	Dialog.selectIconDraw(shader);
}

void STRING_DIALOG::drawLineString(SHADER* shader, const char* s, const VECTOR2& pos){
	Font->draw(shader, s, pos, VECTOR2(FontSize, FontSize), FontColor);
	drawLine(shader, s, pos);
}

void STRING_DIALOG::drawLineStringCentered(SHADER* shader, const char* s, const VECTOR2& pos){
	Font->draw(shader, s, pos, VECTOR2(FontSize, FontSize), FontColor,STATIC_FONT::CENTERED());
	drawLineCentered(shader, s, pos);
}

void STRING_DIALOG::drawLine(SHADER* shader, const char* s, const VECTOR2& pos) {
	LineTexture->draw(shader, pos + VECTOR2(0.0f, (float)FontSize), VECTOR2((float)STATIC_FONT::stringWidth(s, FontSize), 1.0f), LineColor);
}

void STRING_DIALOG::drawLineCentered(SHADER* shader, const char* s, const VECTOR2& pos) {
	LineTexture->draw(shader, pos + VECTOR2(0.0f, (float)FontSize), 0.0f, VECTOR2((float)STATIC_FONT::stringWidth(s, FontSize), 1.0f), LineColor);
}

float STRING_DIALOG::fontCenteredX(const char* s, int fontSize) {
	return (GRAPHIC::instance()->baseWidth() - STATIC_FONT::stringWidth(s, fontSize)) * 0.5f;
}
