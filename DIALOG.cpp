#include "../Library/CONTAINER.h"
#include "../Library/GRAPHIC.h"
#include "../Library/STATIC_FONT.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "DIALOG.h"

DIALOG::DIALOG() {
}

DIALOG::~DIALOG() {
}

void DIALOG::create(
	CONTAINER* c, 
	TEXTURE* selectIconTexture,
	const VECTOR2& selectIconYes, 
	const VECTOR2& selectIconNo, 
	TEXTURE* windowTexture, 
	const VECTOR2& windowTexturePos){
	SelectIconTexture = selectIconTexture;
	SelectIconYes = selectIconYes;
	SelectIconNo = selectIconNo;
	WindowTexture = windowTexture;
	WindowTexturePos = windowTexturePos;
	//ƒTƒEƒ“ƒh
	SoundChoice = c->sound("ui_choice");
	SoundCancel = c->sound("ui_cancel");
	SoundEnter = c->sound("ui_enter");
}

void DIALOG::init(){
	State = STATE::NO;
}

void DIALOG::update(){
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	if (in->isTriggerRight() ||
		in->isTriggerLeft()) {
		sm->playSound(SoundChoice);
		//‚Í‚¢‚Æ‚¢‚¢‚¦‚ð“ü‚ê‘Ö‚¦
		if (State == STATE::YES) {
			State = STATE::NO;
		}
		else {
			State = STATE::YES;
		}
	}
	if (in->isTriggerEnter()) {
		sm->playSound(SoundEnter);
		if (State == STATE::YES) {
			if (YesFunc != nullptr) {
				YesFunc();
			}
		}
		else {
			if (NoFunc != nullptr) {
				NoFunc();
			}
		}
	}
	if (in->isTriggerCancel()) {
		sm->playSound(SoundCancel);
		if (CancelFunc != nullptr) {
			CancelFunc();
		}
	}
}

void DIALOG::draw(SHADER* shader){
	windowDraw(shader);
	selectIconDraw(shader);
}

void DIALOG::windowDraw(SHADER* shader){
	WindowTexture->draw(shader, WindowTexturePos);
}

void DIALOG::selectIconDraw(SHADER* shader){
	if (State == STATE::YES) {
		SelectIconTexture->draw(shader, SelectIconYes);
	}
	else {
		SelectIconTexture->draw(shader, SelectIconNo);
	}
}
