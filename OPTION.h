#pragma once
#include <array>
#include "../Library/VECTOR2.h"
#include "STATE.h"
#include "DIALOG_OPTION_TITLE.h"
#include "DIALOG_OPTION_EXIT.h"
class UI_2D_LEFT;
class STATE;
class SOUND;
//オプションステート
class OPTION :public STATE {
public:
	OPTION();
	~OPTION();
	void create(STATE_MANAGER* stateManager, STATE* state);
	void proc(STATE_MANAGER* stateManager)override;
private:
	void save(STATE_MANAGER* stateManager);

	STATE* HoldState = nullptr;//保持した前のステート
	UI_2D_LEFT* OptionBack = nullptr;
	UI_2D_LEFT* SelectIcon = nullptr;
	std::array<VECTOR2, 3> SelectIconPos;
	enum class CHOICE_ID {
		BACK, TITLE, EXIT
	};
	CHOICE_ID ChoiceIdx = CHOICE_ID::BACK;
	bool IsDialog = false;
	bool IsEnter = false;
	SOUND* SoundChoice = nullptr;
	SOUND* SoundCancel = nullptr;
	SOUND* SoundEnter = nullptr;
	IDIALOG* SelectDialog = nullptr;
	DIALOG_OPTION_TITLE DialogTitle;
	DIALOG_OPTION_EXIT DialogExit;
};

