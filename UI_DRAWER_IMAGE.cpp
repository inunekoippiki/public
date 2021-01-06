#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/TEXTURE.h"
#include "UI_DRAWER_IMAGE.h"
UI_DRAWER_IMAGE::UI_DRAWER_IMAGE(){
}

void UI_DRAWER_IMAGE::create(CONTAINER* c, const char* textureName) {
	Texture = c->texture(textureName);
	Size = VECTOR2((float)Texture->width(), (float)Texture->height());
}

void UI_DRAWER_IMAGE::create(TEXTURE* texture){
	Texture = texture;
	Size = VECTOR2((float)Texture->width(), (float)Texture->height());
}

void UI_DRAWER_IMAGE::update() {

}

void UI_DRAWER_IMAGE::draw(SHADER* shader, const VECTOR2& pos, const VECTOR2& scale, const COLOR& color) {
	Texture->draw(shader, pos, scale, color);
}

void UI_DRAWER_IMAGE::draw(SHADER* shader, const VECTOR2& pos, float rad, const VECTOR2& scale, const COLOR& color){
	Texture->draw(shader, pos, rad, scale, color);
}

UI_DRAWER_IMAGE::~UI_DRAWER_IMAGE() {
}