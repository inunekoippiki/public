#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/COLOR.h"
class SHADER;
//UI•`‰æŠî’ê
class UI_DRAWER {
public:
	UI_DRAWER();
	virtual ~UI_DRAWER();
	virtual void update() = 0;
	virtual void draw(SHADER* shader, const VECTOR2& pos, const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR()) = 0;
	virtual void draw(SHADER* shader, const VECTOR2& pos,float rad,const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR()) = 0;
	float width() {return Size.x; }
	float height() { return Size.y; }
protected :
	VECTOR2 Size;
};

