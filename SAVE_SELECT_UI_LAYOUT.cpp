#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "DATA_LIB.h"
#include "ENTITY_PLAYER.h"
#include "UI_2D_LEFT.h"
#include "UI_2D_CENTERED.h"
#include "UI_MANAGER.h"
#include "UI_DRAWER_FACTORY.h"
#include "SAVE_SELECT_UI_SAVE_DATA.h"
#include "SAVE_SELECT.h"
#include "SAVE_SELECT_UI_LAYOUT.h"
SAVE_SELECT_UI_LAYOUT::SAVE_SELECT_UI_LAYOUT() {
}

SAVE_SELECT_UI_LAYOUT::~SAVE_SELECT_UI_LAYOUT() {
	SaveSelectBack->Delete();
	for (auto& i : NewGameIcon) {
		i->Delete();
	}
	ChoiceIcon->Delete();
	for (auto& i : SaveSelectSaveData) {
		if (i != nullptr) {
			delete i;
		}
	}
}

void SAVE_SELECT_UI_LAYOUT::create(CONTAINER* c, STATIC_FONT* font,UI_MANAGER* uiManager, const std::array< SAVE_DATA, 3> saveData){
	//背景
	SaveSelectBack = new UI_2D_LEFT();
	SaveSelectBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "saveDataSelectBack"));
	SaveSelectBack->setPos(VECTOR2(0.0f, 0.0f));
	uiManager->add(SaveSelectBack, c->data("SAVE_SELECT_UI_LAYOUT::SaveSelectBackPosLayerPriority"));
	//新しく始めるアイコン
	NewGameIcon[0] = new UI_2D_LEFT();
	NewGameIcon[0]->setInvisible(true);
	NewGameIcon[0]->setDrawer(UI_DRAWER_FACTORY::instance(c, "newGameStringIcon"));
	NewGameIcon[0]->setPos(DATA_LIB::vector2(c, "SAVE_SELECT_UI_LAYOUT::NewGameIconPos1"));
	uiManager->add(NewGameIcon[0], c->data("SAVE_SELECT_UI_LAYOUT::NewGameIconLayerPriority"));
	NewGameIcon[1] = new UI_2D_LEFT();
	NewGameIcon[1]->setInvisible(true);
	NewGameIcon[1]->setDrawer(UI_DRAWER_FACTORY::instance(c, "newGameStringIcon"));
	NewGameIcon[1]->setPos(DATA_LIB::vector2(c, "SAVE_SELECT_UI_LAYOUT::NewGameIconPos2"));
	uiManager->add(NewGameIcon[1], c->data("SAVE_SELECT_UI_LAYOUT::NewGameIconLayerPriority"));
	NewGameIcon[2] = new UI_2D_LEFT();
	NewGameIcon[2]->setInvisible(true);
	NewGameIcon[2]->setDrawer(UI_DRAWER_FACTORY::instance(c, "newGameStringIcon"));
	NewGameIcon[2]->setPos(DATA_LIB::vector2(c, "SAVE_SELECT_UI_LAYOUT::NewGameIconPos3"));
	uiManager->add(NewGameIcon[2], c->data("SAVE_SELECT_UI_LAYOUT::NewGameIconLayerPriority"));
	DATA_LIB::data(c, "SAVE_SELECT_UI_LAYOUT::ChoiceIconPos", ChoiceIconPos);
	//選択アイコン
	ChoiceIcon = new UI_2D_LEFT();
	ChoiceIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "saveDataSelectIcon"));
	ChoiceIcon->setPos(ChoiceIconPos[0]);
	uiManager->add(ChoiceIcon, c->data("SAVE_SELECT_UI_LAYOUT::ChoiceIconLayerPriority"));

	//各表示位置
	std::array< VECTOR2, 3>SaveSelectSaveDataPos;
	DATA_LIB::data(c, "SAVE_SELECT_UI_LAYOUT::SaveSelectSaveDataPos", SaveSelectSaveDataPos);
	int idx = 0;
	for (auto& i : SaveSelectSaveData) {
		i = nullptr;
		if (!saveData[idx].isEmpty) {
			i = new SAVE_SELECT_UI_SAVE_DATA();
			i->create(c, font, SaveSelectSaveDataPos[idx], saveData[idx].SaveTime, saveData[idx].PlayTime);
		}
		else {
			//セーブデータが無かった場合新しく始めるを表示する
			NewGameIcon[idx]->setInvisible(false);
		}
		idx++;
	}
}

void SAVE_SELECT_UI_LAYOUT::SaveDataDeleteUpdate(const std::array< SAVE_DATA, 3> saveData){
	int idx = 0;
	for (auto& i : SaveSelectSaveData) {
		if (saveData[idx].isEmpty) {
			delete i;
			i = nullptr;
			NewGameIcon[idx]->setInvisible(false);
		}
		idx++;
	}
}

void SAVE_SELECT_UI_LAYOUT::draw(SHADER* shader){
	for (auto &i: SaveSelectSaveData) {
		if (i != nullptr) {
			i->draw(shader);
		}
	}
}

void SAVE_SELECT_UI_LAYOUT::choiceIdx(int idx){
	ChoiceIcon->setPos(ChoiceIconPos[idx]);
}

