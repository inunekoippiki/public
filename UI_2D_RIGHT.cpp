#include "UI_DRAWER.h"
#include "UI_2D_RIGHT.h"
UI_2D_RIGHT::UI_2D_RIGHT():
	Scale(VECTOR2::one()) {
}

UI_2D_RIGHT::~UI_2D_RIGHT() {
}

void UI_2D_RIGHT::update(){
	Drawer->update();
}

void UI_2D_RIGHT::draw(SHADER* shader) {
	if (!isInvisible()) {
		Drawer->draw(shader, Pos - VECTOR2(Drawer->width() * Scale.x, 0.0f), Scale, Color);
	}
}
