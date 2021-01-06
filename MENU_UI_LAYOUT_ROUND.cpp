#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "SOUND_MANAGER.h"
#include "INPUT_COMMON.h"
#include "DATA_LIB.h"
#include "UI_2D_LEFT.h"
#include "DIALOG_ROUND.h"
#include "UI_DRAWER_FACTORY.h"
#include "SAVE.h"
#include "MENU.h"
#include "MENU_UI_LAYOUT_ROUND.h"
MENU_UI_LAYOUT_ROUND::MENU_UI_LAYOUT_ROUND(MENU* menu) :
	Menu(menu) {
}

MENU_UI_LAYOUT_ROUND::~MENU_UI_LAYOUT_ROUND() {
	delete RoundBack;
	delete MenuSelectIcon;
	for (auto& i : ChapterIcon) {
		delete i;
	}
	delete SelectIcon;
	for (auto& i : Dialog) {
		delete i;
	}
}

void MENU_UI_LAYOUT_ROUND::create(CONTAINER* c,STATIC_FONT* font, SAVE* save) {
	//背景
	RoundBack = new UI_2D_LEFT();
	RoundBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "chapterBack"));
	RoundBack->setPos(VECTOR2(0.0f, 0.0f));
	MenuSelectIcon = new UI_2D_LEFT();
	MenuSelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "menuSelectIcon"));
	MenuSelectIcon->setPos(DATA_LIB::vector2(c, "MENU_UI_LAYOUT_ROUND::MenuSelectIcon"));
	//各チャプターの位置
	DATA_LIB::data(c, "MENU_UI_LAYOUT_ROUND::ChapterIconPos", ChapterIconPos);
	//開放されているチャプターは灰色表示
	const char* chapterIconFileName[3][2] = {
		{ "chapter1StringIcon","chapter1StringIcon"},
		{ "chapter2StringIcon","chapter2StringDisableIcon"} ,
		{ "chapter3StringIcon","chapter3StringDisableIcon"} };
	int roundIdx = 0;
	for (auto& i : ChapterIcon) {
		i = new UI_2D_LEFT();
		if (save->isOpenRound(roundIdx)) {
			//ラウンドが開放されているとき
			i->setDrawer(UI_DRAWER_FACTORY::instance(c, chapterIconFileName[roundIdx][0]));
			ChapterEnable[roundIdx] = true;
		}
		else {
			//ラウンドが開放されていないとき
			i->setDrawer(UI_DRAWER_FACTORY::instance(c, chapterIconFileName[roundIdx][1]));
			ChapterEnable[roundIdx] = false;
		}
		i->setPos(ChapterIconPos[roundIdx]);
		roundIdx++;
	}
	//セレクトアイコンの位置
	DATA_LIB::data(c, "MENU_UI_LAYOUT_ROUND::SelectIconPos", SelectIconPos);
	SelectIcon = new UI_2D_LEFT();
	SelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "chapterSelectIcon"));
	SelectIcon->setPos(SelectIconPos[0]);
	//１章２章３章のダイアログ
	auto dialogYesFunc = [this]() {			
		Menu->selectRound(SelectIdx);
	};
	auto dialogNoFunc = [this]() {			
		SelectDialog = nullptr;
	};
	int round = 1;
	for (auto& i : Dialog) {
		i = new DIALOG_ROUND();
		i->create(c, font, round);
		i->stringDialog()->setYesFunc(dialogYesFunc);
		i->stringDialog()->setNoFunc(dialogNoFunc);
		i->stringDialog()->setCancelFunc(dialogNoFunc);
		round++;
	}
	//サウンド
	SoundChoice = c->sound("ui_choice");
	SoundCancel = c->sound("ui_cancel");
	SoundEnter = c->sound("ui_enter");

}

void MENU_UI_LAYOUT_ROUND::init(){
	SelectIdx = 0;
	SelectIcon->setPos(SelectIconPos[SelectIdx]);
}

void MENU_UI_LAYOUT_ROUND::update(){
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	if (SelectDialog != nullptr) {
		SelectDialog->update();
	}
	else{
		if (in->isTriggerUp()) {
			enterUp();
		}
		if (in->isTriggerDown()) {
			enterDown();
		}
		if (in->isTriggerEnter()) {
			enterEnter();
		}
	}
}

void MENU_UI_LAYOUT_ROUND::draw(SHADER* shader){
	RoundBack->draw(shader);
	SelectIcon->draw(shader);
	for (auto& i : ChapterIcon) {
		i->draw(shader);
	}
	if (SelectDialog != nullptr) {
		SelectDialog->draw(shader);
	}
}

void MENU_UI_LAYOUT_ROUND::enterUp() {
	if (SelectDialog == nullptr) {
		if (--SelectIdx < 0) {
			SelectIdx = 2;
		}
		SOUND_MANAGER::instance()->playSound(SoundChoice);
		SelectIcon->setPos(SelectIconPos[SelectIdx]);
	}
}

void MENU_UI_LAYOUT_ROUND::enterDown() {
	if (SelectDialog == nullptr) {
		if (++SelectIdx > 2) {
			SelectIdx = 0;
		}
		SOUND_MANAGER::instance()->playSound(SoundChoice);
		SelectIcon->setPos(SelectIconPos[SelectIdx]);
	}
}

void MENU_UI_LAYOUT_ROUND::enterEnter() {
	if (SelectDialog == nullptr) {//ダイヤログが出てない
		if (ChapterEnable[SelectIdx]) {//ラウンドが開放されている
			SelectDialog = Dialog[SelectIdx];
			SelectDialog->init();
		}
		SOUND_MANAGER::instance()->playSound(SoundEnter);
	}
}