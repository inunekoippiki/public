#include <string.h>
#include "../Library/common.h"
#include "../Library/CONTAINER.h"
#include "../Library/STATIC_FONT.h"
#include "../Library/TEXTURE.h"
#include "../Library/DATA.h"
#include "DATA_LIB.h"
#include "STORY_TEXT_LAYOUT.h"
STORY_TEXT_LAYOUT::STORY_TEXT_LAYOUT(){
}

STORY_TEXT_LAYOUT::~STORY_TEXT_LAYOUT(){
	SAFE_DELETE(Text);
}

void STORY_TEXT_LAYOUT::create(CONTAINER* c, STATIC_FONT* font, TEXT_DISP* text, const char* charaName){
	Font = font;
	TextureTextBox = c->texture("textBox");
	FontSize = c->data("StoryCharaNameFontSize");
	TextBoxPos = DATA_LIB::vector2(c, "StoryTextBoxPos");
	TextPos = DATA_LIB::vector2(c, "StoryTextPos");
	CharaNamePos = DATA_LIB::vector2(c, "StoryCharaNamePos");
	Text = text;
	strcpy(CharaName, charaName);
	Text->setPos(TextPos);
}

void STORY_TEXT_LAYOUT::allDisp(){
	Text->allDisp();
}

bool STORY_TEXT_LAYOUT::isEnd(){
	return Text->isEnd();
}

void STORY_TEXT_LAYOUT::update(){
	Text->update();
}

void STORY_TEXT_LAYOUT::draw(SHADER* shader){
	TextureTextBox->draw(shader, TextBoxPos);
	Text->draw(shader);
	Font->draw(shader, CharaName, CharaNamePos,VECTOR2(FontSize,FontSize), COLOR());
}
