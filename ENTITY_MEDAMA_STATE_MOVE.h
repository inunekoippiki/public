#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_MEDAMA.h"
#include "ENTITY_STATE.h"
class ENTITY_MEDAMA_STATE_MOVE :public ENTITY_STATE<ENTITY_MEDAMA> {
public:
	ENTITY_MEDAMA_STATE_MOVE(ENTITY_MEDAMA* owner) :ENTITY_STATE<ENTITY_MEDAMA>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Move(), e->toAnim_Idel(), 0.0f, e->animSpeed_Move());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		e->setVelo(normalize(e->velo() + VECTOR3(sinf(RadCnt), 0.0f, cos(RadCnt))) * e->moveSpeed());
		e->posUpdate();
		e->radUpdate();
		if (Cnt >= e->moveTime()) {
			e->states()->change("ATTACK");
		}
		//死んでたらDOWNステートへ
		if (emeny->isDeath()) {
			e->states()->change("DOWN");
		}
		RadCnt += e->moveRadCntSpeed();
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
	float RadCnt = 0;
	int Cnt = 0;
};