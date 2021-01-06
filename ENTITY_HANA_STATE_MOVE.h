#pragma once
#include <math.h>
#include <stdlib.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "ENTITY_HANA.h"
#include "ENTITY_STATE.h"
class ENTITY_HANA_STATE_MOVE :public ENTITY_STATE<ENTITY_HANA> {
public:
	ENTITY_HANA_STATE_MOVE(ENTITY_HANA* owner) :ENTITY_STATE<ENTITY_HANA>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Move(), e->toAnim_Move(),0.0f,e->animSpeed_Move());
		float randRad = (float)rand();
		VECTOR3 v = VECTOR3(sinf(randRad), 0.0f, cosf(randRad));
		v *= e->moveSpeed();
		e->setVelo(v);
		e->radUpdate();
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		INDEV* in = INDEV::instance();
		VECTOR3 move;
		emeny->gravityUpdate();
		e->posUpdate();
		if (Cnt >= e->moveTime()) {
			e->states()->change("IDEL");
		}
		//死んでたらDOWNステートへ
		if (emeny->isDeath()) {
			e->states()->change("DOWN");
		}
		Cnt++;
	}
	void onExit() {
		auto e = owner();
		e->setVelo(VECTOR3());
	}
	const char* name()const {
		return "MOVE";
	}
private:
	int Cnt = 0;
};