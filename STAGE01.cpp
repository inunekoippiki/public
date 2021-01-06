#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/TREE.h"
#include "SOUND_MANAGER.h"
#include "INPUT_COMMON.h"
#include "STATE_MANAGER.h"
#include "ENTITY_MANAGER.h"
#include "STATE_FACTORY.h"
#include "FADE.h"
#include "ENTITY_PLAYER.h"
#include "STAGE01.h"
STAGE01::STAGE01(){

}

STAGE01::~STAGE01() {
}

void STAGE01::create(STATE_MANAGER* stateManager){
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();

	Stage.create(stateManager);
	Map = c->treeOrigin("stage01");
	Stage.createMap(&Map);
	Map.update(MATRIX());
	SOUND_MANAGER::instance()->setNextBgm(c->sound("bgm_battle01"));
	//開始時、クリア時のメッセージを設定
	Stage.createStartMessage("Assets/story/battleStartMessage01.txt", "ノア");
	Stage.createEndMessage("Assets/story/battleEndMessage01.txt", "ノア");

	//エネミー
	ENTITY_MANAGER* entityManager = Stage.entityManager();
	entityManager->appearMedama(VECTOR3(5.0f, 0.0f, 5.0f));
	entityManager->appearMedama(VECTOR3(-5.0f, 0.0f, 5.0f));
	entityManager->appearMedama(VECTOR3(5.0f, 0.0f, -5.0f));
	entityManager->appearMedama(VECTOR3(-5.0f, 0.0f, -5.0f));
	entityManager->appearHana(VECTOR3(7.0f, 0.0f, 0.0f));
	entityManager->appearHana(VECTOR3(-7.0f, 0.0f, 0.0f));
	entityManager->appearHana(VECTOR3(0.0f, 0.0f, 7.0f));
	entityManager->appearHana(VECTOR3(0.0f, 0.0f, -7.0f));
	entityManager->EntitySummon();
	entityManager->update();
	stateManager->fade()->fadeInTrigger();
}

void STAGE01::proc(STATE_MANAGER* stateManager){
	INPUT_COMMON* in = INPUT_COMMON::instance();
	Stage.proc(stateManager);
	battleEndJudge();
	//遷移-----------------------------------------------------------------------------
	//オプション
	if (in->isTriggerOption()) {
		stateManager->setNextState(STATE_FACTORY::instanceOption(stateManager, this));
	}
	//フェードインが終わったら
	if (stateManager->fade()->fadeOutEndFlag()) {
		in->MouseAimOff();
		BATTLE_STATE battleState = Stage.battleState();
		switch (battleState) {
		case BATTLE_STATE::BATTLE_FADE_END_CLEAR:
			delete this;
			stateManager->setNextState(STATE_FACTORY::instanceStory(stateManager, STATE_FACTORY::STORY_TYPE::s01_01));
			break;
		case BATTLE_STATE::BATTLE_FADE_END_GAMEOVER:
			delete this;
			stateManager->setNextState(STATE_FACTORY::instanceMenu(stateManager));
			break;
		case BATTLE_STATE::BATTLE_FADE_END_RETRY:
			delete this;
			stateManager->setNextState(STATE_FACTORY::instanceStage(stateManager, STATE_FACTORY::STAGE_TYPE::s01));
			break;
		}
	}
}

void STAGE01::battleEndJudge(){
	BATTLE_STATE battleState = Stage.battleState();
	if (battleState == BATTLE_STATE::BATTLE) {
		//プレイヤーが死ぬとゲームオーバー
		if (Stage.player()->hp() <= 0) {
			Stage.gameOver();
		}
		//エネミーを検索する関数オブジェ
		auto enemySearch = [](const ENTITY* e)->bool {
			return e->entityType() == ENTITY_TYPE::MEDAMA || e->entityType() == ENTITY_TYPE::HANA || e->entityType() == ENTITY_TYPE::BOSS;};
		//エネミーがいなかったらクリア
		if (nullptr == Stage.entityManager()->entitySearch(enemySearch)) {
			Stage.gameClear(1);
		};
	}
}
