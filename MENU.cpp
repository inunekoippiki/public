#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/INDEV.h"
#include "../Library/IMAGE_2D.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "SOUND_MANAGER.h"
#include "FADE.h"
#include "MENU_UI_LAYOUT.h"
#include "MENU_UI_LAYOUT_ROUND.h"
#include "MENU_UI_LAYOUT_UPGRADE.h"
#include "MENU_UI_LAYOUT_SETTING.h"
#include "SAVE.h"
#include "UPGRADE.h"
#include "SETTING.h"
#include "MENU.h"
MENU::MENU() {
}

MENU::~MENU() {
	SAFE_DELETE(UiLayoutRound);
	SAFE_DELETE(UiLayoutUpgrade);
	SAFE_DELETE(UiLayoutSetting);
}

void MENU::create(STATE_MANAGER* stateManager){
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();
	Save = gameDataCommon->save();
	Setting = gameDataCommon->setting();
	Upgrade = gameDataCommon->upgrade();
	//ラウンド、アップグレード、設定画面を作成
	UiLayoutRound = new MENU_UI_LAYOUT_ROUND(this);
	UiLayoutRound->create(c, gameDataCommon->font(), gameDataCommon->save());
	UiLayout[0] = UiLayoutRound;
	UiLayoutUpgrade = new MENU_UI_LAYOUT_UPGRADE();
	UiLayoutUpgrade->create(c, gameDataCommon->font(), gameDataCommon->upgrade());
	UiLayout[1] = UiLayoutUpgrade;
	UiLayoutSetting = new MENU_UI_LAYOUT_SETTING(this);
	UiLayoutSetting->create(c, gameDataCommon->setting());
	UiLayout[2] = UiLayoutSetting;
	//最初の画面を設定
	SelectUiLayout = UiLayoutRound;
	//UPGRADEに貯められていた与ダメージをスキルポイントに換算
	Upgrade->convertSkillPoint();
	//セーブする
	Save->save(Upgrade);
	//サウンド
	SoundChoice = c->sound("ui_choice");
	SoundCancel = c->sound("ui_cancel");
	SoundEnter = c->sound("ui_enter");
	BgmMenu = c->sound("bgm_menu");
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->setNextBgm(BgmMenu);
	//フェードインスタート
	stateManager->fade()->fadeInTrigger();
	INDEV::instance()->reset();
}

void MENU::proc(STATE_MANAGER* stateManager) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	INDEV* indev = INDEV::instance();
	if (stateManager->fade()->fadeInEndFlag()) {//ロード完了までキー入力を受け取らない
		indev->getState();
	}
	DEBUG_STR* ds = DEBUG_STR::instance();
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->update();
	//デバック表示
	ds->set("volume:%d", Setting->volume()->value());
	ds->set("sevolume:%d", Setting->soundVolume()->value());
	ds->set("bgmvolume:%d", Setting->bgmVolume()->value());
	ds->set("aim:%d", Setting->aimSensitivity()->value());


	SelectUiLayout->update();
	//メニュー画面切り替え////////////////////////////////////////////////////
	if (in->isTriggerMenuRight()) {
		sm->playSound(SoundChoice);
		switch (MenuUiState){
		case MENU_UI_STATE::ROUND:
			changeUiLayoutUpgrade();
			break;
		case MENU_UI_STATE::UPGRADE:
			changeUiLayoutSeting();
			break;
		case MENU_UI_STATE::SETTING:
			changeUiLayoutRound();
			break;
		default:
			WARNING(true, "MENU", "MENU_UI_STATE:over");
			break;
		}
	}
	if (in->isTriggerMenuLeft()) {
		sm->playSound(SoundChoice);
		switch (MenuUiState) {
		case MENU_UI_STATE::ROUND:
			changeUiLayoutSeting();
			break;
		case MENU_UI_STATE::UPGRADE:
			changeUiLayoutRound();
			break;
		case MENU_UI_STATE::SETTING:
			changeUiLayoutUpgrade();
			break;
		default:
			WARNING(true, "MENU", "MENU_UI_STATE:over");
			break;
		}
	}
	//フェードアウト開始
	if (IsSelectRound) {//ラウンドが選ばれた
		stateManager->fade()->fadeOutTrigger();
		indev->reset();
		IsSelectRound = false;
	}
	//Draw/////////////////////////////////////////////////////////////////////////////
	GRAPHIC* g = GRAPHIC::instance();
	g->clearTarget(0.3f, 0.6f, 1.0f);
	SHADER* shader = gameDataCommon->image2dShader();
	BEGIN_PATH_
		SelectUiLayout->draw(shader);
		stateManager->fade()->draw(shader);//不透明⇔透明 画像表示
		ds->draw(shader);
	END_PATH_
	g->present();
	
	//遷移//////////////////////////////////////////////////////////////////////////////

	//完全にフェードアウトしたら次のステートへ
	if (stateManager->fade()->fadeOutEndFlag()) {
		int state = SelectRound;
		delete this;
		switch (state){
		case 0:
			stateManager->setNextState(STATE_FACTORY::instanceStory(stateManager, STATE_FACTORY::STORY_TYPE::s00_00));
			break;
		case 1:
			stateManager->setNextState(STATE_FACTORY::instanceStory(stateManager, STATE_FACTORY::STORY_TYPE::s01_00));
			break;
		case 2:
			stateManager->setNextState(STATE_FACTORY::instanceStory(stateManager, STATE_FACTORY::STORY_TYPE::s02_00));
			break;
		default:
			WARNING(true, "ラウンドがありません","");
			break;
		}
	}
	//オプションへ
	if (in->isTriggerOption()) {
		stateManager->setNextState(STATE_FACTORY::instanceOption(stateManager, this));
	}
}

void MENU::changeUiLayoutRound(){
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->load(Setting);
	Save->save(Upgrade);
	Setting->save();
	MenuUiState = MENU_UI_STATE::ROUND;
	SelectUiLayout = UiLayout[static_cast<int>(MenuUiState)];
	SelectUiLayout->init();
}

void MENU::changeUiLayoutSeting(){
	Save->save(Upgrade);
	MenuUiState = MENU_UI_STATE::SETTING;
	SelectUiLayout = UiLayout[static_cast<int>(MenuUiState)];
	SelectUiLayout->init();
}

void MENU::changeUiLayoutUpgrade(){
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->load(Setting);
	Setting->save();
	MenuUiState = MENU_UI_STATE::UPGRADE;
	SelectUiLayout = UiLayout[static_cast<int>(MenuUiState)];
	SelectUiLayout->init();
}

void MENU::selectRound(int round){
	if (Save->isOpenRound(round)) {
		IsSelectRound = true;
		SelectRound = round;
	}
}

void MENU::volumeUp(){
	Setting->volume()->upValue();
}
void MENU::volumeDown(){
	Setting->volume()->downValue();
}
void MENU::soundVolumeUp(){
	Setting->soundVolume()->upValue();
}
void MENU::soundVolumeDown(){
	Setting->soundVolume()->downValue();
}
void MENU::bgmVolumeUp(){
	Setting->bgmVolume()->upValue();
}
void MENU::bgmVolumeDown(){
	Setting->bgmVolume()->downValue();
}
void MENU::aimSensitivityUp(){
	Setting->aimSensitivity()->upValue();
}
void MENU::aimSensitivityDown(){
	Setting->aimSensitivity()->downValue();
}

