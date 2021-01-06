#include "UI_DRAWER_ANIM.h"
#include "UI_DRAWER_IMAGE.h"
#include "UI_DRAWER_FACTORY.h"
UI_DRAWER_FACTORY::UI_DRAWER_FACTORY() {
}

UI_DRAWER_FACTORY::~UI_DRAWER_FACTORY() {
}

UI_DRAWER* UI_DRAWER_FACTORY::instance(CONTAINER* c, const char* textureName){
	UI_DRAWER_IMAGE* drawer = new UI_DRAWER_IMAGE();
	drawer->create(c, textureName);
	return drawer;
}

UI_DRAWER* UI_DRAWER_FACTORY::instance(TEXTURE* texture){
	UI_DRAWER_IMAGE* drawer = new UI_DRAWER_IMAGE();
	drawer->create(texture);
	return drawer;
}

UI_DRAWER* UI_DRAWER_FACTORY::instance(CONTAINER* c, const char* textureName, int textureNum){
	UI_DRAWER_ANIM* drawer = new UI_DRAWER_ANIM();
	drawer->create(c, textureName, textureNum);
	return drawer;
}

UI_DRAWER* UI_DRAWER_FACTORY::instance(CONTAINER* c, const char* textureName, int textureNum, float animSpeed){
	UI_DRAWER_ANIM* drawer = new UI_DRAWER_ANIM();
	drawer->create(c, textureName, textureNum,animSpeed);
	return drawer;
}
