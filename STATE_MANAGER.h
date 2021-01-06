#pragma once
#include "../Library/common.h"
#include "GAME_DATA_COMMON.h"
class FADE;
class STATE;
class STATE_MANAGER {
public:
	STATE_MANAGER();
	~STATE_MANAGER();
	void create();
	void proc();
	void setNextState(STATE* nextState);
	GAME_DATA_COMMON* gameDataCommon() { return &GameDataCommon; };
	FADE* fade() { return Fade; };
private:
	//各ステートにthisポインタを渡すことによって、以下のオブジェクトが使用可能となる
	STATE* State = nullptr;
	//共通データ
	GAME_DATA_COMMON GameDataCommon;
	//フェード用
	FADE* Fade = nullptr;
};