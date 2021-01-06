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
//���j���[�X�e�[�g
class MENU :public STATE {
public:
	MENU();
	~MENU();
	void create(STATE_MANAGER* stateManager);
	void proc(STATE_MANAGER* stateManager)override;
	//���E���h�����肷��
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
	//��ʂ����E���h�I����ʂɂ���
	void changeUiLayoutRound();
	//��ʂ�ݒ�ɂ���
	void changeUiLayoutSeting();
	//��ʂ��A�b�v�O���[�h��ʂɂ���
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

