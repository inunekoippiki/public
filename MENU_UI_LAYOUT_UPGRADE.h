#pragma once
#include <array>
#include "../Library/STATIC_FONT.h"
#include "../Library/VECTOR2.h"
#include "DIALOG_ROUND.h"
#include "MENU_UI_LAYOUT.h"
class CONTAINER;
class UI_2D_LEFT;
class DIALOG_UPGRADE;
class UPGRADE;
class IUPGRADE_LVL;
class MENU_UI_LAYOUT_UPGRADE :public MENU_UI_LAYOUT {
public:
	MENU_UI_LAYOUT_UPGRADE();
	~MENU_UI_LAYOUT_UPGRADE();
	void create(CONTAINER* c, STATIC_FONT* font, UPGRADE* upgrade);
	void init()override;
	void update()override;
	void draw(SHADER* shader)override;
private:
	//各項目を配列に入れる
	void initUpgradeLv();
	//アップグレードの星を描画する
	void drawUpgradeItem(SHADER* shader);
	void enterUp();
	void enterDown();
	STATIC_FONT* Font = nullptr;
	int FontSize = 0;
	VECTOR2 SkillPointPos;
	char SkillPoint[64] = {};
	UPGRADE* Upgrade = nullptr;
	int SelectIdx = 0;//0,1,2,3,4,5,6,7
	UI_2D_LEFT* UpgradeBack = nullptr;
	UI_2D_LEFT* MenuSelectIcon = nullptr;
	//各項目をアップグレードしようとしたときののダイヤログ
	std::array<DIALOG_UPGRADE*, 8> Dialog = {};
	//選択中のダイヤログ
	DIALOG_UPGRADE* SelectDialog = nullptr;
	//選択アイコン
	UI_2D_LEFT* SelectIcon = nullptr;
	std::array<VECTOR2, 8> SelectIconPos;
	//星のアイコン
	TEXTURE* UpgradeItemIcon = nullptr;
	std::array<VECTOR2, 8> UpgradeItemPos;
	std::array<IUPGRADE_LVL*, 8> UpgradeLvl;
	float UpgradeItemSpace = 0.0f;

	SOUND* SoundChoice = nullptr;
	SOUND* SoundCancel = nullptr;
	SOUND* SoundEnter = nullptr;

};

