#pragma warning (disable:4996)
#include "../Library/TEXTURE.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/FONT_CREATE_SET.h"
#include "SOUND_MANAGER.h"
#include "INPUT_COMMON.h"
#include "DATA_LIB.h"
#include "UI_2D_LEFT.h"
#include "DIALOG_UPGRADE.h"
#include "UI_DRAWER_FACTORY.h"
#include "SAVE.h"
#include "MENU.h"
#include "UPGRADE.h"
#include "MENU_UI_LAYOUT_UPGRADE.h"
MENU_UI_LAYOUT_UPGRADE::MENU_UI_LAYOUT_UPGRADE() {
}

MENU_UI_LAYOUT_UPGRADE::~MENU_UI_LAYOUT_UPGRADE() {
	delete UpgradeBack;
	delete MenuSelectIcon;
	delete SelectIcon;
	for (auto& i : Dialog) {
		delete i;
	}
}

void MENU_UI_LAYOUT_UPGRADE::create(CONTAINER* c,STATIC_FONT* font, UPGRADE* upgrade) {
	Upgrade = upgrade;
	Font = font;
	//背景
	UpgradeBack = new UI_2D_LEFT();
	UpgradeBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "upgradeBack"));
	UpgradeBack->setPos(VECTOR2(0.0f, 0.0f));

	UpgradeItemSpace = c->data("MENU_UI_LAYOUT_UPGRADE::UpgradeItemSpace");
	
	MenuSelectIcon = new UI_2D_LEFT();
	MenuSelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "menuSelectIcon"));
	MenuSelectIcon->setPos(DATA_LIB::vector2(c,"MENU_UI_LAYOUT_UPGRADE::MenuSelectIcon"));
	//セレクトアイコンの位置
	DATA_LIB::data(c, "MENU_UI_LAYOUT_UPGRADE::SelectIconPos", SelectIconPos);
	//セレクトアイコン
	SelectIcon = new UI_2D_LEFT();
	SelectIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "upgradeSelectIcon"));
	SelectIcon->setPos(SelectIconPos[0]);
	//スキルポイントの位置
	SkillPointPos = DATA_LIB::vector2(c, "MENU_UI_LAYOUT_UPGRADE::SkillPointPos");
	//スキルポイント表示用のフォント作成
	FontSize = c->data("MENU_UI_LAYOUT_UPGRADE::SkillPointSize");
	//レベル項目の並び初期化
	initUpgradeLv();
	//各項目ごとの星の位置
	DATA_LIB::data(c, "MENU_UI_LAYOUT_UPGRADE::UpgradeItemPos", UpgradeItemPos);
	//星のテクスチャ
	UpgradeItemIcon = c->texture("upgradeLvIcon");

	//ダイヤログ
	auto dialogEnterFunc = [this]() {
		//ダイヤログで、はいが押されたらレベルを上げ更新
		bool successLvUp = false;
		IUPGRADE_LVL* upgradeLvl = UpgradeLvl[SelectIdx];
		if (upgradeLvl->canUpgrade() &&
			Upgrade->enoughSkillPoint(Upgrade->skillPointCost(upgradeLvl->lvl()))) {
			Upgrade->lvUp(*upgradeLvl);
			successLvUp = true;
		}
		if (successLvUp) {
			//アップグレードが成功したらダイヤログを閉じる
			SelectDialog = nullptr;
		}
	};
	auto dialogNoFunc = [this]() {
		SelectDialog = nullptr;
	};
	int dialogIdx = 0;
	for (int i = 0;i < Dialog.size();i++) {
		Dialog[i] = new DIALOG_UPGRADE();
		Dialog[i]->stringDialog()->setYesFunc(dialogEnterFunc);
		Dialog[i]->stringDialog()->setNoFunc(dialogNoFunc);
		Dialog[i]->stringDialog()->setCancelFunc(dialogNoFunc);
		Dialog[i]->create(c, font, i, 0);
	}

	//サウンド
	SoundChoice = c->sound("ui_choice");
	SoundCancel = c->sound("ui_cancel");
	SoundEnter = c->sound("ui_enter");

}

void MENU_UI_LAYOUT_UPGRADE::init() {
	SelectIdx = 0;
	SelectIcon->setPos(SelectIconPos[SelectIdx]);
}


void MENU_UI_LAYOUT_UPGRADE::update(){
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	if (SelectDialog == nullptr) {
		if (in->isTriggerUp()) {
			enterUp();
		}
		if (in->isTriggerDown()) {
			enterDown();
		}
		if (in->isTriggerEnter()) {
			//ダイヤログを表示
			SelectDialog = Dialog[SelectIdx];
			SelectDialog->init();
			if (UpgradeLvl[SelectIdx]->canUpgrade()) {
				SelectDialog->setSkillPoint(Upgrade->skillPointCost(UpgradeLvl[SelectIdx]->lvl()));
			}
			else {
				//-1にするとMAX表記になる
				SelectDialog->setSkillPoint(-1);
			}
			sm->playSound(SoundEnter);
		}
	}
	else {
		SelectDialog->update();
	}


}

void MENU_UI_LAYOUT_UPGRADE::draw(SHADER* shader) {
	UpgradeBack->draw(shader);
	//MenuSelectIcon->draw(shader);
	sprintf(SkillPoint, "%d", Upgrade->skillPoint());
	Font->draw(shader, SkillPoint, SkillPointPos, VECTOR2(FontSize, FontSize));
	SelectIcon->draw(shader);
	drawUpgradeItem(shader);
	if (SelectDialog != nullptr) {
		SelectDialog->draw(shader);
	}
}

void MENU_UI_LAYOUT_UPGRADE::initUpgradeLv(){
	UpgradeLvl[0] = Upgrade->maxHp();
	UpgradeLvl[1] = Upgrade->attackDamageBoost();
	UpgradeLvl[2] = Upgrade->attackRangeBoost();
	UpgradeLvl[3] = Upgrade->attackSpeedBoost();
	UpgradeLvl[4] = Upgrade->moveSpeedBoost();
	UpgradeLvl[5] = Upgrade->attackDamageSkillBoost();
	UpgradeLvl[6] = Upgrade->moveSpeedSkillBoost();
	UpgradeLvl[7] = Upgrade->healPower();
}

void MENU_UI_LAYOUT_UPGRADE::drawUpgradeItem(SHADER* shader){
	for (int i = 0;i < UpgradeItemPos.size();i++) {
		for (int i2 = 0;i2 < UpgradeLvl[i]->lvl();i2++) {
			UpgradeItemIcon->draw(shader, UpgradeItemPos[i]+ VECTOR2(i2 * UpgradeItemSpace, 0.0f));
		}
	}
}
void MENU_UI_LAYOUT_UPGRADE::enterUp() {
	if (SelectDialog == nullptr) {
		SelectIdx = max(SelectIdx - 1, 0);
		SOUND_MANAGER::instance()->playSound(SoundChoice);
		SelectIcon->setPos(SelectIconPos[SelectIdx]);
	}
}

void MENU_UI_LAYOUT_UPGRADE::enterDown() {
	if (SelectDialog == nullptr) {
		SelectIdx = min(SelectIdx + 1, UpgradeLvl.size()-1);
		SOUND_MANAGER::instance()->playSound(SoundChoice);
		SelectIcon->setPos(SelectIconPos[SelectIdx]);
	}
}