#include "../Library/GRAPHIC.h"
#include "UI_DRAWER.h"
#include "UI_2D_LEFT.h"
UI_2D_LEFT::UI_2D_LEFT() :
	Scale(VECTOR2(1.0f, 1.0f)) 
{
}

UI_2D_LEFT::~UI_2D_LEFT() {
}

void UI_2D_LEFT::update(){
	Drawer->update();
}

void UI_2D_LEFT::draw(SHADER* shader) {
	if (!isInvisible()) {
		Drawer->draw(shader, Pos, Scale, Color);
	}
}
