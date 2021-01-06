#include <math.h>
#include "../Library/common.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/CONTAINER.h"
#include "SOUND_MANAGER.h"
#include "INPUT_COMMON.h"
#include "SETTING.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "SAVE_SELECT.h"
#include "OPTION.h"
#include "FADE.h"
#include "TITLE.h"
TITLE::TITLE() {
}

TITLE::~TITLE() {

}
void TITLE::create(STATE_MANAGER* stateManager) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();
	TextureTitle = c->texture("title");
	TextureStart = c->texture("titleStart");
	TextureStartEffect = c->texture("titleStartEffect");
	EffectInterval = 30;
	EffectPlaySpeed = 0.06f;
	//�ݒ�f�[�^�����[�h
	gameDataCommon->setting()->load(c);
	//��
	BgmTitle = c->sound("bgm_title");
	SoundTitleStart = c->sound("title_start");
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->load(gameDataCommon->setting());
	sm->setNextBgm(BgmTitle);
	//�t�F�[�h�C���X�^�[�g
	stateManager->fade()->fadeInTrigger();
}

void TITLE::proc(STATE_MANAGER* stateManager){
	//update-------------------------------------------------------------------------
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	INDEV* indev = INDEV::instance();
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	//���͂̎�t�̓t�B�[�h�C�����I����Ă��炷��
	if (stateManager->fade()->fadeInEndFlag()) {
		indev->getState();
	}
	sm->update();
	ds->set("1:%d,2:%d,3:%d,4:%d,5:%d,6:%d,7:%d,8:%d,9:%d", 
		indev->value(JOY1_BUTTON1),
		indev->value(JOY1_BUTTON2),
		indev->value(JOY1_BUTTON3),
		indev->value(JOY1_BUTTON4), 
		indev->value(JOY1_BUTTON5), 
		indev->value(JOY1_BUTTON6), 
		indev->value(JOY1_BUTTON7), 
		indev->value(JOY1_BUTTON8), 
		indev->value(JOY1_BUTTON9) );
	ds->set("j1:%d,j2:%d,j3:%d,j4:%d,j5:%d,j6:%d",
		indev->value(JOY1_AXIS_A),
		indev->value(JOY1_AXIS_B),
		indev->value(JOY1_AXIS_C),
		indev->value(JOY1_AXIS_D),
		indev->value(JOY1_AXIS_E),
		indev->value(JOY1_AXIS_F));
	//�t�F�[�h�C�����I�����āA����L�[�������ꂽ��t�F�[�h�A�E�g�J�n
	if (!IsEnter && stateManager->fade()->fadeInEndFlag()) {
		if (in->isTriggerEnter()) {
			sm->playSound(SoundTitleStart);
			IsEnter = true;
			IsStart = true;
			EffectCnt = 0;
		}
	}
	//�G�t�F�N�g�̔���
	if (IsStart) {
		EffectCnt += 2;
	}
	else {
		if (--EffectCnt < 0) {
			EffectCnt = 0;
		}
	}
	//Draw-------------------------------------------------------------------------
	GRAPHIC* g = GRAPHIC::instance();
	g->clearTarget(0.3f, 0.6f, 1.0f);
	SHADER* shader = gameDataCommon->image2dShader();
	BEGIN_PATH_
		TextureTitle->draw(shader,VECTOR2(0.0f,0.0f));
		TextureStartEffect->draw(shader, VECTOR2(767.0f, 852.0f), COLOR(1.0f, 1.0f, 1.0f, EffectCnt * EffectPlaySpeed));
		TextureStart->draw(shader, VECTOR2(767.0f, 852.0f));
		stateManager->fade()->draw(shader);
		ds->draw(shader);
	END_PATH_
	g->present();
	//�J��-------------------------------------------------------------------------
	//���莞�̃X�^�[�g����̔������I�������t�B�[�h�A�E�g�J�n
	if (EffectCnt > EffectInterval) {
		IsStart = false;
		stateManager->fade()->fadeOutTrigger();
	}
	//���S�Ƀt�F�[�h�A�E�g�����玟�̃X�e�[�g��
	if (stateManager->fade()->fadeOutEndFlag()) {
		delete this;
		stateManager->setNextState(STATE_FACTORY::instanceSaveSelect(stateManager));
	}
	//�I�v�V�����֑J��
	if (in->isTriggerOption()) {
		stateManager->setNextState(STATE_FACTORY::instanceOption(stateManager,this));
	}
}

