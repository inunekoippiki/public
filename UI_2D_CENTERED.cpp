#include "UI_DRAWER.h"
#include "UI_2D_CENTERED.h"
UI_2D_CENTERED::UI_2D_CENTERED() :
	Scale(VECTOR2::one()) {
}

UI_2D_CENTERED::~UI_2D_CENTERED() {
}

void UI_2D_CENTERED::update(){
	Drawer->update();
}

void UI_2D_CENTERED::draw(SHADER* shader){
	if (!isInvisible()) {
		Drawer->draw(shader, Pos, Rad, Scale, Color);
	}
}
