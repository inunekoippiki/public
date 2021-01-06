#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "../Library/ARRAY.h"
#include "UI_DRAWER.h"
class SHADER;
class TEXTURE;
class CONTAINER;
//�����̉摜���A�j���[�V�����\������p
class UI_DRAWER_ANIM :public UI_DRAWER {
public:
	UI_DRAWER_ANIM();
	~UI_DRAWER_ANIM();
	void create(CONTAINER* c, const char* textureName, size_t textureNum, float animSpeed = 1.0f);
	void update()override;
	void draw(SHADER* shader, const VECTOR2& pos, const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR())override;
	void draw(SHADER* shader, const VECTOR2& pos, float rad, const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR())override;
private:
	ARRAY_P<TEXTURE> Textures;
	int Frame = 0;
	float AnimSpeed = 0.0f;
	float TempAnimPlay = 0.0f;
};
