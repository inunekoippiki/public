#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_MEDAMA.h"
#include "ENTITY_STATE.h"
class ENTITY_MEDAMA_STATE_DOWN :public ENTITY_STATE<ENTITY_MEDAMA> {
public:
	ENTITY_MEDAMA_STATE_DOWN(ENTITY_MEDAMA* owner) :ENTITY_STATE<ENTITY_MEDAMA>(owner) {
		Cnt = 0;
		DisappearCnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		emeny->tree()->setNextAnimation(e->anim_Down(), e->toAnim_Down(), 0.0f, e->animSpeed_Down());
		sm->playSound(e->soundDown(), e->pos());
		Cnt = 0;
		DisappearCnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->gravity();
		e->posUpdate();
		if (Cnt == e->animEndFrame_Down()) {
			emeny->tree()->setNextAnimation(e->anim_Down(), e->toAnim_Down(),e->animEndFrame_Down()-1,0.0f);
		}
		if (Cnt >= e->animEndFrame_Down()) {
			emeny->DisappearUpdate(DisappearCnt++);
			if (DisappearCnt >= emeny->disappearTime()) {
				e->Delete();
			}
		}
		Cnt++;
	}
	void onExit() {

	}
	const char* name()const {
		return "DOWN";
	}
private:
	int Cnt = 0;
	int DisappearCnt = 0;
};