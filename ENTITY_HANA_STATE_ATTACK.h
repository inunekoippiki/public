#pragma once
#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_HANA.h"
#include "ENTITY_STATE.h"
#include "BILLBOARDS.h"
#include "ENTITY_PLAYER.h"
class ENTITY_HANA_STATE_ATTACK :public ENTITY_STATE<ENTITY_HANA> {
public:
	ENTITY_HANA_STATE_ATTACK(ENTITY_HANA* owner) :ENTITY_STATE<ENTITY_HANA>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Attack(),e->toAnim_Attack(),0.0f,e->animSpeed_Attack());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		INDEV* in = INDEV::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		if (Cnt == e->activateFrame_Attack()) {
			e->entityManager()->appearLaserHana(e->centerPos(),
				normalize(VECTOR3(sinf(e->ry()),0.0f,cosf(e->ry()))) * e->laserLength(),
				e->laserSize(),
				e->attackDamage(),
				e->laserLifeTime());

			sm->playSound(e->soundAttack(), e->pos());
		}
		if (Cnt >= e->animEndFrame_Attack()) {
			e->states()->change("IDEL");
		}
		//死んでたらDOWNステートへ
		if (emeny->isDeath()) {
			e->states()->change("DOWN");
		}
		Cnt ++;
	}
	void onExit() {

	}
	const char* name()const {
		return "ATTACK";
	}
private:
	int Cnt = 0;
};