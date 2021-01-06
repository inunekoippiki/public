#pragma once
#include "TEXT_DISP.h"
#include "UI_DRAWER.h"
class SHADER;
class UI_2D_LEFT;
class VECTOR2;
//バトル前後に出るメッセージのUI
class BATTLE_MESSAGE:public UI_DRAWER{
public:
	BATTLE_MESSAGE(TEXT_DISP* text, UI_2D_LEFT* textbox);
	~BATTLE_MESSAGE();
	void update()override;
	void draw(SHADER* shader, const VECTOR2& pos, const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR())override;
	void draw(SHADER* shader, const VECTOR2& pos, float rad, const VECTOR2& scale = VECTOR2(1.0f, 1.0f), const COLOR& color = COLOR())override;
private:
	void draw(SHADER* shader);
	TEXT_DISP* Text = nullptr;
	UI_2D_LEFT* TextBox = nullptr;
};