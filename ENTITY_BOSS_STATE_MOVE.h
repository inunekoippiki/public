#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_BOSS.h"
#include "ENTITY_STATE.h"
class ENTITY_BOSS_STATE_MOVE :public ENTITY_STATE<ENTITY_BOSS> {
public:
	ENTITY_BOSS_STATE_MOVE(ENTITY_BOSS* owner) :ENTITY_STATE<ENTITY_BOSS>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		e->bodyBlowStart();
		emeny->tree()->setNextAnimation(e->anim_Move(), e->toAnim_Move(),0.0f,e->animSpeed_Move());
		e->setVelo(normalize(((ENTITY*)emeny->player())->pos() - e->pos()) * e->moveSpeed());
		e->radUpdate();
		sm->playSound(e->soundBodyBlow());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		INDEV* in = INDEV::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
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
		e->bodyBlowEnd();
		e->setVelo(VECTOR3());
	}
	const char* name()const {
		return "MOVE";
	}
private:
	float Cnt = 0;
};