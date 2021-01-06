#pragma once
#include "../Library/CONTAINER.h"
class UI_DRAWER;
class TEXTURE;
//UI_DRAWERÇçÏÇ¡ÇƒìnÇ∑ÉNÉâÉX
class UI_DRAWER_FACTORY{
public:
	UI_DRAWER_FACTORY();
	~UI_DRAWER_FACTORY();
	static UI_DRAWER* instance(CONTAINER* c,const char* textureName);
	static UI_DRAWER* instance(TEXTURE* textureName);
	static UI_DRAWER* instance(CONTAINER* c,const char* textureName,int textureNum);
	static UI_DRAWER* instance(CONTAINER* c,const char* textureName, int textureNum,float animSpeed);
private:
};

