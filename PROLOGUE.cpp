#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "TEXT_DISP.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "FADE.h"
#include "PROLOGUE.h"
PROLOGUE::PROLOGUE() {
}

PROLOGUE::~PROLOGUE() {
	SAFE_DELETE(TextCentered);
}

void PROLOGUE::create(STATE_MANAGER* stateManager){
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();
	GRAPHIC* g = GRAPHIC::instance();
	//�w�i
	TexturePrologue = c->texture("prologue");
	//�����\���N���X����
	TextCentered = new TEXT_DISP(gameDataCommon->font());
	TextCentered->create(c->data("PrologueFile"));
	TextCentered->setFontSize(c->data("PrologueFontSize"));
	TextCentered->setInterval(c->data("PrologueDispSpeed"));
	TextCentered->setPos(VECTOR2(g->baseWidth() / 2.0f, c->data("PrologueTextPos.y")));
	TextCentered->setIsCentered(true);
	BgmPrologue = c->sound("bgm_prologue");
	//�T�E���h
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->setNextBgm(BgmPrologue);
	//�t�F�[�h�C���X�^�[�g
	stateManager->fade()->fadeInTrigger();
}

void PROLOGUE::proc(STATE_MANAGER* stateManager) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	//Update----------------------------------------------------------------------------
	INDEV* indev = INDEV::instance();
	indev->getState();
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->update();
	TextCentered->update();
	//Draw----------------------------------------------------------------------------
	GRAPHIC* g = GRAPHIC::instance();
	g->clearTarget(0.3f, 0.6f, 1.0f);
	SHADER* shader = gameDataCommon->image2dShader();
	BEGIN_PATH_
		TexturePrologue->draw(shader, VECTOR2(0.0f, 0.0f));
		TextCentered->draw(shader);
		stateManager->fade()->draw(shader);//�s�����̓��� �摜�\��
	END_PATH_
	g->present();
	//�J��----------------------------------------------------------------------------
	//�t�F�[�h�A�E�g�J�n
	if (TextCentered->isEnd() && in->isTriggerEnter()) {
		stateManager->fade()->fadeOutTrigger();
	}
	if (in->isTriggerEnter()) {
		TextCentered->allDisp();
	}
	//���S�Ƀt�F�[�h�A�E�g�����玟�̃X�e�[�g��
	if (stateManager->fade()->fadeOutEndFlag()) {
		delete this;
		stateManager->setNextState(STATE_FACTORY::instanceMenu(stateManager));
	}

	if (in->isTriggerOption()) {
		stateManager->setNextState(STATE_FACTORY::instanceOption(stateManager, this));
	}
}
