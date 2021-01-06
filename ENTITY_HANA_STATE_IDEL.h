#pragma once
#include <math.h>
#include <stdlib.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "ENTITY_HANA.h"
#include "ENTITY_STATE.h"
class ENTITY_HANA_STATE_IDEL :public ENTITY_STATE<ENTITY_HANA> {
public:
	ENTITY_HANA_STATE_IDEL(ENTITY_HANA* owner) :ENTITY_STATE<ENTITY_HANA>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Idel(), e->toAnim_Idel(),0.0f,e->animSpeed_Idel());
		e->setVelo(VECTOR3());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		INDEV* in = INDEV::instance();
		e->setVy(e->velo().y + emeny->gravity());
		e->posUpdate();
		if (Cnt >= e->idelTime()) {
			if (rand() % 2 == 0) {
				e->states()->change("MOVE");
			}
			else{
				e->states()->change("ATTACK");
			}
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