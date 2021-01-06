#pragma once
#include "../Library/FONT.h"
#include "STATE.h"
class MENU_UI_LAYOUT;
class MENU_UI_LAYOUT_ROUND;
class MENU_UI_LAYOUT_UPGRADE;
class MENU_UI_LAYOUT_SETTING;
class UPGRADE;
class SETTING;
class SOUND;
class SAVE;
//メニューステート
class MENU :public STATE {
public:
	MENU();
	~MENU();
	void create(STATE_MANAGER* stateManager);
	void proc(STATE_MANAGER* stateManager)override;
	//ラウンドを決定する
	void selectRound(int round);

	void volumeUp();
	void volumeDown();
	void soundVolumeUp();
	void soundVolumeDown();
	void bgmVolumeUp();
	void bgmVolumeDown();
	void aimSensitivityUp();
	void aimSensitivityDown();

private:
	//画面をラウンド選択画面にする
	void changeUiLayoutRound();
	//画面を設定にする
	void changeUiLayoutSeting();
	//画面をアップグレード画面にする
	void changeUiLayoutUpgrade();


	MENU_UI_LAYOUT* SelectUiLayout = nullptr;
	MENU_UI_LAYOUT* UiLayout[3] = {};
	MENU_UI_LAYOUT_ROUND* UiLayoutRound = nullptr;
	MENU_UI_LAYOUT_UPGRADE* UiLayoutUpgrade = nullptr;
	MENU_UI_LAYOUT_SETTING* UiLayoutSetting = nullptr;
	enum class MENU_UI_STATE {
		ROUND, UPGRADE, SETTING
	};
	MENU_UI_STATE MenuUiState = MENU_UI_STATE::ROUND;//0:RoundMenu,1:UpgradeMenu,2:SettingMenu
	SETTING* Setting = nullptr;
	UPGRADE* Upgrade = nullptr;
	bool IsSelectRound = false;

	int SelectRound = 0;//0,1,2
	SAVE* Save = nullptr;
	SOUND* BgmMenu = nullptr;
	SOUND* SoundChoice = nullptr;
	SOUND* SoundCancel = nullptr;
	SOUND* SoundEnter = nullptr;
};

