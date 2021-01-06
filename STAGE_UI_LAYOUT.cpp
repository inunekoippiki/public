#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "ENTITY_PLAYER.h"
#include "UI_2D_LEFT.h"
#include "UI_2D_CENTERED.h"
#include "DATA_LIB.h"
#include "UI_MANAGER.h"
#include "UI_DRAWER_FACTORY.h"
#include "BATTLE_MESSAGE.h"
#include "STAGE_UI_LAYOUT.h"
STAGE_UI_LAYOUT::STAGE_UI_LAYOUT() {
}

STAGE_UI_LAYOUT::~STAGE_UI_LAYOUT(){
	StartMessage->Delete();
	StatusBack->Delete();
	HpGauge->Delete();
	SkillGauge->Delete();
	SkillIcon1->Delete();
	SkillIcon2->Delete();
	SkillIcon3->Delete();
	SkillSelectIcon->Delete();
	CrossHair->Delete();
	GameOver->Delete();
	EndMessage->Delete();
	KeyIcon->Delete();
}

void STAGE_UI_LAYOUT::create(CONTAINER* c, UI_MANAGER* uiManager){
	StatusBack = new UI_2D_LEFT();
	StatusBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "statusBack"));
	StatusBack->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::StatusBackPos"));
	uiManager->add(StatusBack, c->data("STAGE_UI_LAYOUT::StatusBackLayerPriority"));
	HpGauge = new UI_2D_LEFT();
	HpGauge->setDrawer(UI_DRAWER_FACTORY::instance(c, "hpGauge"));
	HpGauge->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::HpGaugePos"));
	uiManager->add(HpGauge, c->data("STAGE_UI_LAYOUT::HpGaugeLayerPriority"));
	SkillGauge = new UI_2D_LEFT();
	SkillGauge->setDrawer(UI_DRAWER_FACTORY::instance(c, "skillGauge"));
	SkillGauge->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::SkillGaugePos"));
	uiManager->add(SkillGauge, c->data("STAGE_UI_LAYOUT::SkillGaugeLayerPriority"));
	//スキルアイコンの位置
	DATA_LIB::data(c, "STAGE_UI_LAYOUT::SkillIconPos", SkillIconPos);
	SkillIcon1 = new UI_2D_CENTERED();
	SkillIcon1->setDrawer(UI_DRAWER_FACTORY::instance(c, "skillIcon1"));
	SkillIcon1->setPos(SkillIconPos[0]);
	uiManager->add(SkillIcon1, c->data("STAGE_UI_LAYOUT::SkillIconLayerPriority"));
	SkillIcon2 = new UI_2D_CENTERED();
	SkillIcon2->setDrawer(UI_DRAWER_FACTORY::instance(c, "skillIcon2"));
	SkillIcon2->setPos(SkillIconPos[1]);
	uiManager->add(SkillIcon2, c->data("STAGE_UI_LAYOUT::SkillIconLayerPriority"));
	SkillIcon3 = new UI_2D_CENTERED();
	SkillIcon3->setDrawer(UI_DRAWER_FACTORY::instance(c, "skillIcon3"));
	SkillIcon3->setPos(SkillIconPos[2]);
	uiManager->add(SkillIcon3, c->data("STAGE_UI_LAYOUT::SkillIconLayerPriority"));
	SkillSelectIcon = new UI_2D_CENTERED();
	SkillSelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "skillIconSelectIcon"));
	SkillSelectIcon->setPos(SkillIconPos[0]);
	uiManager->add(SkillSelectIcon, c->data("STAGE_UI_LAYOUT::SkillIconSelectLayerPriority"));
	//クロスヘア
	CrossHair = new UI_2D_CENTERED();
	CrossHair->setDrawer(UI_DRAWER_FACTORY::instance(c, "crossHair"));
	CrossHair->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::CrossHairPos"));
	uiManager->add(CrossHair, c->data("STAGE_UI_LAYOUT::CrossHairLayerPriority"));
	//ゲームオーバー
	GameOver = new UI_2D_CENTERED();
	GameOver->setInvisible(true);
	GameOver->setColor(COLOR(1.0f, 1.0f, 1.0f, 0.0f));
	GameOver->setDrawer(UI_DRAWER_FACTORY::instance(c, "gameOver"));
	GameOver->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::GameOverPos"));
	uiManager->add(GameOver, c->data("STAGE_UI_LAYOUT::GameOverLayerPriority"));
	//バトルスタート
	BattleStartIcon = new UI_2D_LEFT();
	BattleStartIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "battleStrat"));
	uiManager->add(BattleStartIcon, c->data("STAGE_UI_LAYOUT::BattleStartIconLayerPriority"));
	//バトルクリア
	BattleClearIcon = new UI_2D_LEFT();
	BattleClearIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "battleClear"));
	BattleClearIcon->setInvisible(true);
	uiManager->add(BattleClearIcon, c->data("STAGE_UI_LAYOUT::BattleClearIconLayerPriority"));
	//キー説明
	KeyIcon = new UI_2D_LEFT();
	KeyIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "battleKeyIcon"));
	KeyIcon->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::KeyIconPos"));
	uiManager->add(KeyIcon, c->data("STAGE_UI_LAYOUT::KeyIconLayerPriority"));
}

void STAGE_UI_LAYOUT::update(){
	if (IsGameOver) {
		GameOverFead += 0.02f;
		GameOver->setColor(COLOR(1.0f, 1.0f, 1.0f, GameOverFead - 1.0f));
	}
}

void STAGE_UI_LAYOUT::setPlayerDataUpdate(ENTITY_PLAYER* entityPlayer) {
	setPlayerMaxHp(entityPlayer->maxHp());
	setPlayerHp(entityPlayer->hp());
	setPlayerMaxSp(entityPlayer->maxSp());
	setPlayerSp(entityPlayer->sp());
	setPlayerChoiceSkillType(entityPlayer->skillChoiceType());
	if (entityPlayer->isAvoid()||entityPlayer->maxSp()==entityPlayer->sp()) {
		KeyIconDispCnt++;
	}
	else{
		KeyIconDispCnt = 0;
	}
	if (KeyIconDispCnt > 400) {
		KeyIcon->setInvisible(false);
		KeyIconAlpha += 0.02f;
		if (KeyIconAlpha > 1.0f) {
			KeyIconAlpha = 1.0f;
		}
		KeyIcon->setColor(COLOR(1.0f, 1.0f, 1.0f, KeyIconAlpha));
	}
	else{
		KeyIconAlpha -= 0.02f;
		if (KeyIconAlpha < 0.0f) {
			KeyIcon->setInvisible(true);
			KeyIconAlpha = 0.0f;
		}
		KeyIcon->setColor(COLOR(1.0f, 1.0f, 1.0f, KeyIconAlpha));
	}
}

void STAGE_UI_LAYOUT::setPlayerMaxHp(int playerMaxHp) {
	PlayerMaxHp = playerMaxHp; 
	HpGaugeWidth = (float)PlayerHp / max(PlayerMaxHp, 1);
	HpGauge->setScale(VECTOR2(HpGaugeWidth, 1.0f));
}

void STAGE_UI_LAYOUT::setPlayerHp(int playerHp) { 
	PlayerHp = playerHp; 
	HpGaugeWidth = (float)PlayerHp / max(PlayerMaxHp,1);
	HpGauge->setScale(VECTOR2(HpGaugeWidth, 1.0f));
}

void STAGE_UI_LAYOUT::setPlayerMaxSp(int playerMaxSkillPoint) {
	PlayerMaxSp = playerMaxSkillPoint; 
	SkillGaugeWidth = (float)PlayerSp / max(PlayerMaxSp,1);
	SkillGauge->setScale(VECTOR2(SkillGaugeWidth, 1.0f));
}

void STAGE_UI_LAYOUT::setPlayerSp(int playerSkillPoint) {
	PlayerSp = playerSkillPoint; 
	SkillGaugeWidth = (float)PlayerSp / max(PlayerMaxSp, 1);
	SkillGauge->setScale(VECTOR2(SkillGaugeWidth, 1.0f));
}

void STAGE_UI_LAYOUT::setPlayerChoiceSkillType(int playerChoiceSkillType){
	PlayerChoiceSkillType = playerChoiceSkillType;
	SkillSelectIcon->setPos(SkillIconPos[PlayerChoiceSkillType]);

}

void STAGE_UI_LAYOUT::closeStartMessage(){
	StartMessage->setInvisible(true);
	BattleStartIcon->setInvisible(true);
}

void STAGE_UI_LAYOUT::showGameOver(){
	IsGameOver = true;
	GameOver->setInvisible(false);
}

void STAGE_UI_LAYOUT::showClear(){
	EndMessage->setInvisible(false);
	BattleClearIcon->setInvisible(false);
}

void STAGE_UI_LAYOUT::initStartMessage(CONTAINER* c, STATIC_FONT* font, UI_MANAGER* uiManager, const char* fileName, const char* charaName){
	StartMessage = instanceMassage(c, font,uiManager, fileName, charaName);
}

void STAGE_UI_LAYOUT::initEndMessage(CONTAINER* c, STATIC_FONT* font, UI_MANAGER* uiManager, const char* fileName, const char* charaName){
	EndMessage = instanceMassage(c, font,uiManager, fileName,charaName);
	EndMessage->setInvisible(true);
}

UI_2D_LEFT* STAGE_UI_LAYOUT::instanceMassage(CONTAINER* c,STATIC_FONT* font, UI_MANAGER* uiManager, const char* fileName,const char* charaName){
	UI_2D_LEFT* textBox = new UI_2D_LEFT();
	TEXT_DISP* text;
	if (strcmp(charaName, "ノア") == 0) {//ノアの場合は別
		text = new TEXT_DISP(font);
		text->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::BattleMessageTextNoaPos"));
		text->create(fileName);
		text->setFontSize(c->data("STAGE_UI_LAYOUT::BattleMessageBoxNoaFontSize"));
		text->allDisp();
		textBox->setDrawer(UI_DRAWER_FACTORY::instance(c, "battleMessageNoa"));
		textBox->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::BattleMessageBoxNoaPos"));
	}
	else{
		text = new TEXT_DISP(font);
		text->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::BattleMessageTextKurusuPos"));
		text->create(fileName);
		text->setFontSize(c->data("STAGE_UI_LAYOUT::BattleMessageBoxKurusuFontSize"));
		text->allDisp();
		textBox->setDrawer(UI_DRAWER_FACTORY::instance(c, "battleMessageKrusu"));
		textBox->setPos(DATA_LIB::vector2(c, "STAGE_UI_LAYOUT::BattleMessageBoxKurusuPos"));
	}
	UI_2D_LEFT* Message = new UI_2D_LEFT();
	Message->setDrawer(new BATTLE_MESSAGE(text,textBox));
	uiManager->add(Message, c->data("STAGE_UI_LAYOUT::TextLayerPriority"));
	return Message;
}

