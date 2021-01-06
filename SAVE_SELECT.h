#pragma once
#include <array>
#include "STATE.h"
#include "DIALOG_SAVE_DELETE.h"
#include "DIALOG_SAVE_SELECT.h"
class SAVE_SELECT_UI_LAYOUT;
class UI_MANAGER;
class SOUND;

struct SAVE_DATA {
	char fileName[256] = {};
	bool isEmpty = false;
	time_t SaveTime = 0;
	time_t PlayTime = 0;
};
//セーブデータ選択ステート
class SAVE_SELECT :public STATE {
public:
	SAVE_SELECT();
	~SAVE_SELECT();
	void create(STATE_MANAGER* stateManager);
	void proc(STATE_MANAGER* stateManager)override;
private:
	UI_MANAGER* UiManager = nullptr;
	SAVE_SELECT_UI_LAYOUT* UiLayout = nullptr;
	DIALOG_SAVE_SELECT* DialogNewData = nullptr;
	DIALOG_SAVE_SELECT* DialogLoadData = nullptr;
	std::array< DIALOG_SAVE_DELETE*, 3> DialogSaveDelete = {};
	IDIALOG* SelectDialog = nullptr;
	std::array < SAVE_DATA, 3> SaveData;
	int choiceIdx = 0;//0,1,2
	bool EnterNewData = false;
	bool EnterLoadData = false;
	bool EnterSaveDelete = false;
	bool Enter = false;
	bool IsFead = false;
	//音
	SOUND* SoundChoice = nullptr;
	SOUND* SoundCancel = nullptr;
	SOUND* SoundEnter = nullptr;
};

