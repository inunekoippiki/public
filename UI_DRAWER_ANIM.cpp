#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/TEXTURE.h"
#include "UI_DRAWER_ANIM.h"
UI_DRAWER_ANIM::UI_DRAWER_ANIM(){
}

void UI_DRAWER_ANIM::create(CONTAINER* c, const char* textureName, size_t textureNum, float animSpeed) {
	Textures.secure(textureNum);
	for (int i = 0; i < Textures.size(); i++) {
		Textures[i] = c->texture(textureName, i);
	}
	Size = VECTOR2((float)Textures[0]->width(), (float)Textures[0]->height());
}

void UI_DRAWER_ANIM::update() {
	TempAnimPlay += AnimSpeed;
	Frame += (int)TempAnimPlay;
	TempAnimPlay -= (int)TempAnimPlay;
	if (Frame >= Textures.size()) {
		Frame = 0;
	}
}

void UI_DRAWER_ANIM::draw(SHADER* shader, const VECTOR2& pos, const VECTOR2& scale, const COLOR& color) {
	Textures[Frame]->draw(shader, pos, scale, color);
}

void UI_DRAWER_ANIM::draw(SHADER* shader, const VECTOR2& pos, float rad, const VECTOR2& scale, const COLOR& color){
	Textures[Frame]->draw(shader, pos, rad, scale, color);
}

UI_DRAWER_ANIM::~UI_DRAWER_ANIM() {
}