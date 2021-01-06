#pragma once
#include <array>
#include "../Library/FONT.h"
#include "../Library/VECTOR2.h"
#include "DIALOG_ROUND.h"
#include "MENU_UI_LAYOUT.h"
class CONTAINER;
class MENU;
class UI_2D_LEFT;
class SETTING;
class TEXTURE;
class MENU_UI_LAYOUT_SETTING :public MENU_UI_LAYOUT {
public:
	MENU_UI_LAYOUT_SETTING(MENU* menu);
	~MENU_UI_LAYOUT_SETTING();
	void create(CONTAINER* c, SETTING* setting);
	void init()override;

	void update()override;
	void draw(SHADER* shader)override;
private:
	void enterUp();
	void enterDown();
	void enterRight();
	void enterLeft();
	MENU* Menu = nullptr;
	void drawSettingLv(SHADER* shader);//äeçÄñ⁄ÇÃÉQÅ[ÉWÇÃï`âÊ
	SETTING* Setting = nullptr;
	int SelectIdx = 0;
	UI_2D_LEFT* SettingBack = nullptr;
	UI_2D_LEFT* MenuSelectIcon = nullptr;
	TEXTURE* SettingLvIcon = nullptr;
	array<VECTOR2, 4> SettingLvIconPos;
	float SettingLvIconSpace = 0.0f;
	UI_2D_LEFT* SelectIcon = nullptr;
	VECTOR2 SelectIconOffsetPos;

	SOUND* SoundChoice = nullptr;
	SOUND* SoundCancel = nullptr;
	SOUND* SoundEnter = nullptr;
};

