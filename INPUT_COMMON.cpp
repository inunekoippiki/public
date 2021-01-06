#include <Windows.h>
#include <cmath>
#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/WINDOW.h"
#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"

INPUT_COMMON::INPUT_COMMON() {
	In = new INDEV;
}

INPUT_COMMON::~INPUT_COMMON() {
	SAFE_DELETE(In);
}

void INPUT_COMMON::getState(){
	if (IsMouseAim) {
		In->getState();
		GRAPHIC* g = GRAPHIC::instance();
		WINDOW* w = WINDOW::instance();
		VECTOR2 mousePoint{ (float)In->value(MOUSE_X) ,(float)In->value(MOUSE_Y) };
		POINT p{ mousePoint.x,mousePoint.y };
		ClientToScreen(w->hostHandle(), &p);
		POINT windowCenter{ g->width() * 0.5f, g->height() * 0.5f };
		ClientToScreen(w->hostHandle(), &windowCenter);
		MouseBefore = VECTOR2(p.x - windowCenter.x, windowCenter.y - p.y);
		MouseBefore *= 0.1f;
		SetCursorPos((int)windowCenter.x, (int)windowCenter.y);
	}
	else{
		In->getState();
	}
}

void INPUT_COMMON::resetState(){
	In->reset();
}

void INPUT_COMMON::MouseAimOn(){
	IsMouseAim = true;
	ShowCursor(false);
}

void INPUT_COMMON::MouseAimOff(){
	IsMouseAim = false;
	ShowCursor(true);
}

float INPUT_COMMON::aimAxisHorizontal()const {
	//float pc = (In->isPress(KEY_RIGHT) ? 1.0f : 0.0f) +
	//	(In->isPress(KEY_LEFT) ? -1.0f : 0.0f);
	float pc = MouseBefore.x;
	float gp = In->value(JOY1_AXIS_C) / 128.0f;
	return abs(pc) > abs(gp) ? pc : gp;
}

float INPUT_COMMON::aimAxisVertical()const {
	//float pc = (In->isPress(KEY_UP) ? 1.0f : 0.0f) +
	//	(In->isPress(KEY_DOWN) ? -1.0f : 0.0f);
	float pc = MouseBefore.y;
	float gp = In->value(JOY1_AXIS_D) / -128.0f;
	return abs(pc) > abs(gp) ? pc : gp;
}

bool INPUT_COMMON::isNoneAimAxis()const {
	if (In->value(JOY1_AXIS_C) != 0 || In->value(JOY1_AXIS_D) != 0) {
		return false;
	}
	if (In->isPress(KEY_UP) ||
		In->isPress(KEY_DOWN) ||
		In->isPress(KEY_RIGHT) ||
		In->isPress(KEY_LEFT)) {
		return false;
	}
	return true;
}

float INPUT_COMMON::moveAxisHorizontal()const {
	float pc = (In->isPress(KEY_D) ? 1.0f : 0.0f) +
		(In->isPress(KEY_A) ? -1.0f : 0.0f);
	float gp = In->value(JOY1_AXIS_A) / 128.0f;
	return abs(pc) > abs(gp) ? pc : gp;
}

float INPUT_COMMON::moveAxisVertical()const {
	float pc = (In->isPress(KEY_W) ? 1.0f : 0.0f) +
		(In->isPress(KEY_S) ? -1.0f : 0.0f);
	float gp = In->value(JOY1_AXIS_B) / -128.0f;
	return abs(pc) > abs(gp) ? pc : gp;
}

bool INPUT_COMMON::isNoneMoveAxis()const {
	if (In->value(JOY1_AXIS_A) != 0 || In->value(JOY1_AXIS_B) != 0) {
		return false;
	}
	if (In->isPress(KEY_W) ||
		In->isPress(KEY_S) ||
		In->isPress(KEY_D) ||
		In->isPress(KEY_A)) {
		return false;
	}
	return true;
}

bool INPUT_COMMON::isTriggerAvoid()const {
	if (In->isTrigger(KEY_SHIFT)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON2)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON4)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerShot()const {
	if (In->isTrigger(MOUSE_RBUTTON)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON6)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON8)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerMelle()const {
	if (In->isTrigger(MOUSE_LBUTTON)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON7)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON5)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerSkill()const {
	if (In->isTrigger(KEY_X)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON1)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON3)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerSkillChange()const {
	if (In->isTrigger(KEY_C)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_RIGHT)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_LEFT)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerSkillNextChange()const {
	if (In->isTrigger(JOY1_POV_RIGHT)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_UP)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerSkillBackChange()const {
	if (In->isTrigger(JOY1_POV_LEFT)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_DOWN)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerEnter()const {
	if (In->isTrigger(KEY_Z)) {
		return true;
	}
	if (In->isTrigger(KEY_ENTER)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON1)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON3)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerCancel()const {
	if (In->isTrigger(KEY_X)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON2)) {
		return true;
	}
	if (In->isTrigger(JOY1_BUTTON4)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerUp()const {
	if (In->isTrigger(KEY_UP)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_UP)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_D,-1)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_B, -1)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerDown()const {
	if (In->isTrigger(KEY_DOWN)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_DOWN)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_D,1)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_B, 0)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerRight()const {
	if (In->isTrigger(KEY_RIGHT)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_RIGHT)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_C,1)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_A, 1)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerLeft()const {
	if (In->isTrigger(KEY_LEFT)) {
		return true;
	}
	if (In->isTrigger(JOY1_POV_LEFT)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_C, -1)) {
		return true;
	}
	if (In->isJoyTrigger(JOY1_AXIS_A, -1)) {
		return true;
	}
	return false;
}

bool INPUT_COMMON::isTriggerMenuRight()const {
	return In->isTrigger(KEY_D) || 
		In->isTrigger(JOY1_BUTTON8)|| 
		In->isTrigger(JOY1_BUTTON6);
}

bool INPUT_COMMON::isTriggerMenuLeft()const {
	return In->isTrigger(KEY_A)||
		In->isTrigger(JOY1_BUTTON7)|| 
		In->isTrigger(JOY1_BUTTON5);
}

bool INPUT_COMMON::isTriggerOption()const {
	return In->isTrigger(KEY_O)||
		In->isTrigger(JOY1_BUTTON10);
}

bool INPUT_COMMON::isTriggerSaveDelete()const {
	return In->isTrigger(KEY_X)||
		In->isTrigger(JOY1_BUTTON2);
}

bool INPUT_COMMON::isTriggerStorySkip()const {
	return In->isTrigger(KEY_X) ||
		In->isTrigger(JOY1_BUTTON2);
}
