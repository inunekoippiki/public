#include "../Library/TEXTURE.h"
#include "../Library/MATRIX.h"
#include "../Library/GRAPHIC.h"
#include "UI_MANAGER.h"
#include "UI_DRAWER.h"
#include "UI_3D_LEFT.h"
UI_3D_LEFT::UI_3D_LEFT():
	Scale(VECTOR2::one()){
}

UI_3D_LEFT::~UI_3D_LEFT() {
}

void UI_3D_LEFT::update(){
}

void UI_3D_LEFT::draw(SHADER* shader) {
	if (!isInvisible()) {
		GRAPHIC* g = GRAPHIC::instance();
		VECTOR3 drawPos;
		drawPos = Pos;
		drawPos = UiManager->projView() * drawPos;
		if (drawPos.z > 0.0f) {
			drawPos.x = (((drawPos.x / drawPos.z) + 1.0f) * (g->baseWidth() / 2.0f));
			drawPos.y = (((-drawPos.y / drawPos.z) + 1.0f) * (g->baseHeight() / 2.0f));
			float z = 1.0f / drawPos.z;
			float yScale = z * Scale.y;
			Drawer->draw(shader,drawPos.xy() +VECTOR2(0.0f, -Drawer->height() * 0.5f * yScale)+Offset*z, VECTOR2(z * Scale.x, yScale));
		}
	}
}

void UI_3D_LEFT::setOffset(const VECTOR2& offset) {
	Offset = VECTOR2(offset.x * Drawer->width(), offset.y * Drawer->height());
}
