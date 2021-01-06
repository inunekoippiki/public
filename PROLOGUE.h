#pragma once
#include "STATE.h"
class TEXT_DISP;
class TEXTURE;
class SOUND;
//プロローグステート
class PROLOGUE :public STATE {
public:
	PROLOGUE();
	~PROLOGUE();
	void create(STATE_MANAGER* stateManager);
	void proc(STATE_MANAGER* stateManager)override;
private:
	TEXTURE* TexturePrologue = nullptr;
	TEXT_DISP* TextCentered = nullptr;
	SOUND* BgmPrologue = nullptr;
};

