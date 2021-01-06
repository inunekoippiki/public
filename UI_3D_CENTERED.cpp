#include "../Library/TEXTURE.h"
#include "../Library/MATRIX.h"
#include "../Library/GRAPHIC.h"
#include "UI_MANAGER.h"
#include "UI_DRAWER.h"
#include "UI_3D_CENTERED.h"
UI_3D_CENTERED::UI_3D_CENTERED():
	Scale(VECTOR2(1.0f,1.0f)) 
{
}

UI_3D_CENTERED::~UI_3D_CENTERED() {
}

void UI_3D_CENTERED::update(){
	Drawer->update();
}

void UI_3D_CENTERED::draw(SHADER* shader) {
	if (!isInvisible()) {
		GRAPHIC* g = GRAPHIC::instance();
		VECTOR3 drawPos;
		drawPos = Pos;
		drawPos = UiManager->projView() * drawPos;
		if (drawPos.z > 0.0f) {
			drawPos.x = (((drawPos.x / drawPos.z) + 1.0f) * (g->baseWidth() / 2.0f));
			drawPos.y = (((-drawPos.y / drawPos.z) + 1.0f) * (g->baseHeight() / 2.0f));
			float z = 1.0f / drawPos.z;
			Drawer->draw(shader, drawPos.xy(), 0.0f, VECTOR2(z * Scale.x, z * Scale.y));
		}
	}
}
