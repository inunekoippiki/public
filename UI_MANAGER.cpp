#define UI_PRIORITY_MIN 0
#define UI_PRIORITY_MAX 65535
#include "UI_MANAGER.h"
#include "UI_BASE.h"
UI_MANAGER::UI_MANAGER() {
	UI_BASE::setUiManager(this);
}

UI_MANAGER::~UI_MANAGER() {
	for (auto &i: UiList) {
		delete i;
	}
}

void UI_MANAGER::add(UI_BASE* ui,unsigned int priority){
	//‡”Ô“¹—‚É‘}“ü
	ui->setPriority(priority);
	bool insertSuccess = false;
	for (auto iterator = UiList.begin();iterator != UiList.end(); iterator++) {
		if ((*iterator)->priority() >= ui->priority()) {
			UiList.insert(iterator, ui);
			insertSuccess = true;
			break;
		}
	}
	if (!insertSuccess) {
		UiList.push_back(ui);
	}
}

void UI_MANAGER::draw(SHADER* shader){
	for (auto iterator = UiList.begin();iterator != UiList.end();) {
		//ƒfƒŠ[ƒg‚³‚ê‚Ä‚¢‚½‚çÁ‚·
		if ((*iterator)->isDelete()) {
			delete* iterator;
			iterator = UiList.erase(iterator);
			continue;
		}
		else {
			(*iterator)->draw(shader);
			iterator++;
		}
	}
}
