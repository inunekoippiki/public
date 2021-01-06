#pragma warning (disable:4996)
#include "../Library/common.h"
#include "../Library/WINDOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/CONTAINER.h"
#include "UI_DRAWER_FACTORY.h"
#include "DATA_LIB.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "SOUND_MANAGER.h"
#include "INPUT_COMMON.h"
#include "DIALOG_OPTION_TITLE.h"
#include "DIALOG_OPTION_EXIT.h"
#include "FADE.h"
#include "SAVE.h"
#include "UI_2D_LEFT.h"
#include "UI_MANAGER.h"
#include "UPGRADE.h"
#include "OPTION.h"
OPTION::OPTION() {
}

OPTION::~OPTION() {
	delete OptionBack;
	delete SelectIcon;
}

void OPTION::create(STATE_MANAGER* stateManager, STATE* state){
	HoldState = state;
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();
	OptionBack = new UI_2D_LEFT();
	OptionBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "pauseBack"));
	OptionBack->setPos(VECTOR2(0.0f, 0.0f));
	DATA_LIB::data(c, "OPTION::SelectIconPos", SelectIconPos);
	SelectIcon = new UI_2D_LEFT();
	SelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "pauseSelectIcon"));
	SelectIcon->setPos(SelectIconPos[static_cast<int>(ChoiceIdx)]);

	//ダイアログ作成
	auto dialogYesFunc = [this]() {
		IsEnter = true;
	};
	auto dialogNoFunc = [this]() {
		SelectDialog = nullptr;
	};
	//タイトルに戻りますかのダイヤログ
	DialogTitle.create(c, gameDataCommon->font());
	DialogTitle.stringDialog()->setYesFunc(dialogYesFunc);
	DialogTitle.stringDialog()->setNoFunc(dialogNoFunc);
	DialogTitle.stringDialog()->setCancelFunc(dialogNoFunc);
	//ゲーム終了しますかのダイヤログ
	DialogExit.create(c, gameDataCommon->font());
	DialogExit.stringDialog()->setYesFunc(dialogYesFunc);
	DialogExit.stringDialog()->setNoFunc(dialogNoFunc);
	DialogExit.stringDialog()->setCancelFunc(dialogNoFunc);
	//サウンド
	SoundChoice = c->sound("ui_choice");
	SoundCancel = c->sound("ui_cancel");
	SoundEnter = c->sound("ui_enter");
}

void OPTION::proc(STATE_MANAGER* stateManager) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();

	//Update-----------------------------------------------------------------------------
	INDEV* indev = INDEV::instance();
	indev->getState();
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	if (SelectDialog==nullptr) {
		//ダイヤログが出てないとき

		if (in->isTriggerRight()) {
			switch (ChoiceIdx) {
			case CHOICE_ID::BACK:
				ChoiceIdx = CHOICE_ID::TITLE;
				break;
			case CHOICE_ID::TITLE:
				ChoiceIdx = CHOICE_ID::EXIT;
				break;
			case CHOICE_ID::EXIT:
				ChoiceIdx = CHOICE_ID::BACK;
				break;
			}
			SelectIcon->setPos(SelectIconPos[static_cast<int>(ChoiceIdx)]);
			sm->playSound(SoundChoice);
		}
		if (in->isTriggerLeft()) {
			switch (ChoiceIdx) {
			case CHOICE_ID::BACK:
				ChoiceIdx = CHOICE_ID::EXIT;
				break;
			case CHOICE_ID::TITLE:
				ChoiceIdx = CHOICE_ID::BACK;
				break;
			case CHOICE_ID::EXIT:
				ChoiceIdx = CHOICE_ID::TITLE;
				break;
			}
			SelectIcon->setPos(SelectIconPos[static_cast<int>(ChoiceIdx)]);
			sm->playSound(SoundChoice);
		}
		if (in->isTriggerEnter()) {
			switch (ChoiceIdx){
			case CHOICE_ID::BACK:
				IsEnter = true;
				break;
			case CHOICE_ID::TITLE:
				IsDialog = true;
				SelectDialog = &DialogTitle;
				SelectDialog->init();
				break;
			case CHOICE_ID::EXIT:
				IsDialog = true;
				SelectDialog = &DialogExit;
				SelectDialog->init();
				break;
			}
			sm->playSound(SoundEnter);
		}
	}
	else{
		SelectDialog->update();
	}
	sm->update();

	//Draw-----------------------------------------------------------------
	GRAPHIC* g = GRAPHIC::instance();
	g->clearTarget(0.3f, 0.6f, 1.0f);
	SHADER* shader = gameDataCommon->image2dShader();
	BEGIN_PATH_
		OptionBack->draw(shader);
		SelectIcon->draw(shader);
		if(SelectDialog!=nullptr){
			SelectDialog->draw(shader);
		}
	END_PATH_
	g->present();

	//遷移------------------------------------------------------------------------------
	if (IsEnter) {
		switch (ChoiceIdx){
		case CHOICE_ID::BACK: 
		{
			STATE* holdState = HoldState;
			delete this;
			stateManager->setNextState(holdState);
			break;
		}
		case CHOICE_ID::TITLE:
		{
			save(stateManager);
			delete HoldState;
			delete this;
			stateManager->setNextState(STATE_FACTORY::instanceTitle(stateManager));
			break;
		}
		case CHOICE_ID::EXIT:
		{			
			save(stateManager);
			WARNING(true, "ゲームを終了します", "");
			SendMessage(WINDOW::instance()->hostHandle(), WM_CLOSE, 0, 0);
			break;
		}
		}
	}
}

void OPTION::save(STATE_MANAGER* stateManager){
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	//セーブデータを読み込んでいれば
	if (gameDataCommon->save()->isLoadSaveData()) {
		//アップグレードの情報をセーブする
		gameDataCommon->save()->save(gameDataCommon->upgrade());
	}
}
