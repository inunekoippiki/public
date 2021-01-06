#include "../Library/common.h"
#include "STATE.h"
#include "STATE_FACTORY.h"
#include "FADE.h"
#include "STORY_TEXT_LAYOUT.h"
#include "STATE_MANAGER.h"

STATE_MANAGER::STATE_MANAGER() {
}

STATE_MANAGER::~STATE_MANAGER() {
	SAFE_DELETE(State);
	SAFE_DELETE(Fade);
}

void STATE_MANAGER::create(){
	//共通データ作成
	GameDataCommon.create();
	// フェードイン、フェードアウト制御クラス
	Fade = new FADE();
	//最初のステートをセット
	State = STATE_FACTORY::instanceTitle(this);
}

void STATE_MANAGER::proc() {
	State->proc(this);
}

void STATE_MANAGER::setNextState(STATE* state){
	State = state;
}


