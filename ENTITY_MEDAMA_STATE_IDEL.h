#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_MEDAMA.h"
#include "ENTITY_STATE.h"
class ENTITY_MEDAMA_STATE_IDEL :public ENTITY_STATE<ENTITY_MEDAMA> {
public:
	ENTITY_MEDAMA_STATE_IDEL(ENTITY_MEDAMA* owner) :ENTITY_STATE<ENTITY_MEDAMA>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Idel(),e->toAnim_Idel(),0.0f,e->animSpeed_Idel());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		if (Cnt >= e->idelTime()) {
			e->states()->change("ATTACK");
		}
		//死んでたらDOWNステートへ
		if (emeny->isDeath()) {
			e->states()->change("DOWN");
		}
		Cnt++;
	}
	void onExit() {

	}
	const char* name()const {
		return "IDEL";
	}
private:
	int Cnt = 0;
};