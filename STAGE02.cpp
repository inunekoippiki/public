#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/TREE.h"
#include "SOUND_MANAGER.h"
#include "INPUT_COMMON.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_BOSS.h"
#include "ENTITY_HANA.h"
#include "ENTITY_MEDAMA.h"
#include "ENTITY_PLAYER.h"
#include "FADE.h"
#include "STAGE02.h"
STAGE02::STAGE02(){
}

STAGE02::~STAGE02() {
}

void STAGE02::create(STATE_MANAGER* stateManager){
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();

	Stage.create(stateManager);
	Map = c->treeOrigin("stage02");
	Stage.createMap(&Map);
	Map.update(MATRIX());
	SOUND_MANAGER::instance()->setNextBgm(c->sound("bgm_battle02"));
	//�J�n���A�N���A���̃��b�Z�[�W��ݒ�
	Stage.createStartMessage("Assets/story/battleStartMessage02.txt", "�m�A");
	Stage.createEndMessage("Assets/story/battleEndMessage02.txt", "�m�A");

	//�G�l�~�[
	ENTITY_MANAGER* entityManager = Stage.entityManager();
	entityManager->appearMedama(VECTOR3(5.0f, 0.0f, 5.0f));
	entityManager->appearMedama(VECTOR3(-5.0f, 0.0f, 5.0f));
	entityManager->appearMedama(VECTOR3(5.0f, 0.0f, -5.0f));
	entityManager->appearMedama(VECTOR3(-5.0f, 0.0f, -5.0f));
	entityManager->appearHana(VECTOR3(7.0f, 0.0f, 0.0f));
	entityManager->appearHana(VECTOR3(-7.0f, 0.0f, 0.0f));
	entityManager->appearHana(VECTOR3(0.0f, 0.0f, 7.0f));
	entityManager->appearHana(VECTOR3(0.0f, 0.0f, -7.0f));
	Boss = entityManager->appearBoss(VECTOR3(0.0f, 0.0f, -9.0f));
	entityManager->EntitySummon();
	entityManager->update();
	stateManager->fade()->fadeInTrigger();
}

void STAGE02::proc(STATE_MANAGER* stateManager){
	INPUT_COMMON* in = INPUT_COMMON::instance();
	Stage.proc(stateManager);
	battleEndJudge();
	//�J��-------------------------------------------------------------------------------------
	//�I�v�V����
	if (in->isTriggerOption()) {
		stateManager->setNextState(STATE_FACTORY::instanceOption(stateManager, this));
	}
	//�t�F�[�h�C�����I�������
	if (stateManager->fade()->fadeOutEndFlag()) {
		in->MouseAimOff();
		BATTLE_STATE battleState = Stage.battleState();
		switch (battleState) {
		case BATTLE_STATE::BATTLE_FADE_END_CLEAR:
			delete this;
			stateManager->setNextState(STATE_FACTORY::instanceStory(stateManager, STATE_FACTORY::STORY_TYPE::s02_01));
			break;
		case BATTLE_STATE::BATTLE_FADE_END_GAMEOVER:
			delete this;
			stateManager->setNextState(STATE_FACTORY::instanceMenu(stateManager));
			break;
		case BATTLE_STATE::BATTLE_FADE_END_RETRY:
			delete this;
			stateManager->setNextState(STATE_FACTORY::instanceStage(stateManager, STATE_FACTORY::STAGE_TYPE::s02));
			break;
		}
	}
}

void STAGE02::battleEndJudge(){
	BATTLE_STATE battleState = Stage.battleState();
	if (battleState == BATTLE_STATE::BATTLE) {
		//�v���C���[�����ʂƃQ�[���I�[�o�[
		if (Stage.player()->hp() <= 0) {
			Stage.gameOver();
		}
		//�{�X�����˂΂����N���A
		if (Boss->enemy()->isDeath()) {
			//�G�������X�^�[�ƌ��e�������֐��I�u�W�F
			auto exe = [](ENTITY* e)->void {
				if (e->entityType() == ENTITY_TYPE::HANA) {
					dynamic_cast<ENTITY_HANA*>(e)->enemy()->death();
				} 
				if (e->entityType() == ENTITY_TYPE::MEDAMA) {
					dynamic_cast<ENTITY_MEDAMA*>(e)->enemy()->death();
				}
				if (e->entityType() == ENTITY_TYPE::LIGHT_BULLET) {
					e->Delete();
				}
			};
			//�G�������X�^�[�ƌ��e������
			Stage.entityManager()->execute(exe);
			Stage.gameClear(2);
		};
	}
}
