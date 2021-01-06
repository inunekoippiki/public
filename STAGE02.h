#pragma once
#include "../Library/TREE.h"
#include "STATE.h"
#include "STAGE.h"
class ENTITY_BOSS;
class STAGE02 :public STATE {
public:
	STAGE02();
	~STAGE02();
	void create(STATE_MANAGER* stateManager);
	void proc(STATE_MANAGER* stateManager)override;
private:
	//�N���A�����A���s�����𔻒�
	void battleEndJudge();
	ENTITY_BOSS* Boss = nullptr;
	SOUND* BgmBattle = nullptr;
	TREE Map;
	STAGE Stage;
};

