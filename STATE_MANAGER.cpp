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
	//���ʃf�[�^�쐬
	GameDataCommon.create();
	// �t�F�[�h�C���A�t�F�[�h�A�E�g����N���X
	Fade = new FADE();
	//�ŏ��̃X�e�[�g���Z�b�g
	State = STATE_FACTORY::instanceTitle(this);
}

void STATE_MANAGER::proc() {
	State->proc(this);
}

void STATE_MANAGER::setNextState(STATE* state){
	State = state;
}


