#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "../Library/ARRAY.h"
#include "UI_DRAWER.h"
class SHADER;
class TEXTURE;
class CONTAINER;
//‰æ‘œ‚ð1–‡‚ð•\Ž¦‚·‚é—p
class UI_DRAWER_IMAGE :public UI_DRAWER {
public:
	UI_DRAWER_IMAGE();
	~UI_DRAWER_IMAGE();
	void create(CONTAINER* c, const char* textureName);
	void create(TEXTURE* texture);
	void update()override;
	void draw(SHADER* shader, const VECTOR2& pos, const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR())override;
	void draw(SHADER* shader, const VECTOR2& pos, float rad, const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR())override;
private:
	TEXTURE* Texture = nullptr;
};
