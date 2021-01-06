#pragma once
#include <array>
#include "../Library/VECTOR2.h"
#include "DIALOG_ROUND.h"
#include "MENU_UI_LAYOUT.h"
class CONTAINER;
class MENU;
class UI_2D_LEFT;
class SAVE;
class MENU_UI_LAYOUT_ROUND:public MENU_UI_LAYOUT{
public:
	MENU_UI_LAYOUT_ROUND(MENU* menu);
	~MENU_UI_LAYOUT_ROUND();
	void create(CONTAINER* c, STATIC_FONT* font, SAVE* save);
	void init()override;
	void update()override;
	void draw(SHADER* shader)override;

private:
	void enterUp();
	void enterDown();
	void enterEnter();

	MENU* Menu = nullptr;
	int SelectIdx = 0;//0,1,2
	UI_2D_LEFT* RoundBack = nullptr;
	UI_2D_LEFT* MenuSelectIcon = nullptr;
	std::array<VECTOR2, 3> ChapterIconPos = {};
	bool ChapterEnable[3] = {};
	std::array<UI_2D_LEFT*, 3> ChapterIcon = {};
	std::array<VECTOR2, 3> SelectIconPos;
	UI_2D_LEFT* SelectIcon = nullptr;
	std::array<DIALOG_ROUND*, 3> Dialog = {};
	DIALOG_ROUND* SelectDialog = nullptr;//現在選択中のダイアログ

	SOUND* SoundChoice = nullptr;
	SOUND* SoundCancel = nullptr;
	SOUND* SoundEnter = nullptr;
};

