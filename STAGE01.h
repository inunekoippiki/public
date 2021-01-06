#pragma once
#include "../Library/TREE.h"
#include "STATE.h"
#include "STAGE.h"
class STAGE01:public STATE{
public:
	STAGE01();
	~STAGE01();
	void create(STATE_MANAGER* stateManager);
	void proc(STATE_MANAGER* stateManager)override;
private:
	//ƒNƒŠƒAğŒA¸”sğŒ‚ğ”»’è
	void battleEndJudge();
	SOUND* BgmBattle = nullptr;
	TREE Map;
	STAGE Stage;
};

