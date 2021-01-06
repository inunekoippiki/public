#pragma warning (disable:4996)
#include "../Library/common.h"
#include "../Library/TEXTURE.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "DATA_LIB.h"
#include "UI_2D_LEFT.h"
#include "UI_DRAWER_FACTORY.h"
#include "SAVE.h"
#include "MENU.h"
#include "SETTING.h"
#include "MENU_UI_LAYOUT_SETTING.h"
MENU_UI_LAYOUT_SETTING::MENU_UI_LAYOUT_SETTING(MENU* menu) :
	Menu(menu) {
}

MENU_UI_LAYOUT_SETTING::~MENU_UI_LAYOUT_SETTING() {
	delete SettingBack;
	delete MenuSelectIcon;
	delete SelectIcon;
}

void MENU_UI_LAYOUT_SETTING::create(CONTAINER* c, SETTING* setting) {
	Setting = setting;
	SettingBack = new UI_2D_LEFT();
	SettingBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "settingBack"));
	SettingBack->setPos(VECTOR2(0.0f, 0.0f));
	MenuSelectIcon = new UI_2D_LEFT();
	MenuSelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "menuSelectIcon"));
	MenuSelectIcon->setPos(DATA_LIB::vector2(c, "MENU_UI_LAYOUT_SETTING::MenuSelectIcon"));
	SettingLvIcon = c->texture("settingLvIcon");
	DATA_LIB::data(c, "MENU_UI_LAYOUT_SETTING::SettingLvIconPos", SettingLvIconPos);
	SettingLvIconSpace = c->data("MENU_UI_LAYOUT_SETTING::SettingLvIconSpace");
	SelectIcon = new UI_2D_LEFT();
	SelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "settingSelectIcon"));
	SelectIconOffsetPos = DATA_LIB::vector2(c, "MENU_UI_LAYOUT_SETTING::SelectIconOffsetPos");
	//サウンド
	SoundChoice = c->sound("ui_choice");
	SoundCancel = c->sound("ui_cancel");
	SoundEnter = c->sound("ui_enter");
}



void MENU_UI_LAYOUT_SETTING::init() {
	SelectIdx = 0;
}

void MENU_UI_LAYOUT_SETTING::update(){
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	if (in->isTriggerUp()) {
		enterUp();
	}
	if (in->isTriggerDown()) {
		enterDown();
	}
	if (in->isTriggerRight()) {
		enterRight();
	}
	if (in->isTriggerLeft()) {
		enterLeft();
	}
}

void MENU_UI_LAYOUT_SETTING::draw(SHADER* shader) {
	SettingBack->draw(shader);
	drawSettingLv(shader);
	SelectIcon->draw(shader);
}

void MENU_UI_LAYOUT_SETTING::drawSettingLv(SHADER* shader) {
	float shiftWidth = 20.0f;
	int lv[4] = { (int)(Setting->volume()->percentage() * shiftWidth) ,
		(int)(Setting->soundVolume()->percentage() * shiftWidth),
		(int)(Setting->bgmVolume()->percentage() * shiftWidth) ,
		(int)(Setting->aimSensitivity()->percentage() * shiftWidth) };
	for (int i = 0;i < SettingLvIconPos.size();i++) {
		for (int i2 = 0;i2 < lv[i];i2++) {
			SettingLvIcon->draw(shader, SettingLvIconPos[i] + VECTOR2(SettingLvIconSpace * i2, 0.0f));
		}
	}
	SelectIcon->setPos(SettingLvIconPos[SelectIdx] + VECTOR2(SettingLvIconSpace * (lv[SelectIdx]-1), 0.0f) + SelectIconOffsetPos);

}

void MENU_UI_LAYOUT_SETTING::enterUp() {
	if (--SelectIdx < 0) {
		//上に行きすぎないようにする
		SelectIdx = 0;
	}
	SOUND_MANAGER::instance()->playSound(SoundChoice);
}

void MENU_UI_LAYOUT_SETTING::enterDown() {
	if (++SelectIdx > 3) {
		//下に行き過ぎないようにする
		SelectIdx = 3;
	}
	SOUND_MANAGER::instance()->playSound(SoundChoice);
}

void MENU_UI_LAYOUT_SETTING::enterRight() {
	switch (SelectIdx) {
	case 0:
		Menu->volumeUp();
		break;
	case 1:
		Menu->soundVolumeUp();
		break;
	case 2:
		Menu->bgmVolumeUp();
		break;
	case 3:
		Menu->aimSensitivityUp();
		break;
	default:
		WARNING(true, "MENU_UI_LAYOUT_SETTING", "enterRight()");
		break;
	}
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->load(Setting);
	sm->playSound(SoundChoice);
}

void MENU_UI_LAYOUT_SETTING::enterLeft() {
	switch (SelectIdx) {
	case 0:
		Menu->volumeDown();
		break;
	case 1:
		Menu->soundVolumeDown();
		break;
	case 2:
		Menu->bgmVolumeDown();
		break;
	case 3:
		Menu->aimSensitivityDown();
		break;
	default:
		WARNING(true, "MENU_UI_LAYOUT_SETTING", "enterLeft()");
		break;
	}
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->load(Setting);
	sm->playSound(SoundChoice);
}