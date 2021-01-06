#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_BOSS.h"
#include "ENTITY_STATE.h"
#include "BILLBOARDS.h"
class ENTITY_BOSS_STATE_ATTACK2 :public ENTITY_STATE<ENTITY_BOSS> {
public:
	ENTITY_BOSS_STATE_ATTACK2(ENTITY_BOSS* owner) :ENTITY_STATE<ENTITY_BOSS>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Attack2(), e->toAnim_Attack2(),0.0f,e->animSpeed_Attack2());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		INDEV* in = INDEV::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		if (Cnt >= e->activateFrame_Attack2()) {
			if (Cnt >= e->activateFrame_Attack2()) {
				sm->playSound(e->soundAttack2(), e->centerPos());
			}
			e->entityManager()->appearLightBulletBoss(e->centerPos(), 
				normalize(emeny->player()->centerPos()-e->centerPos()+
					VECTOR3(((float)rand() / RAND_MAX) - 0.5f, ((float)rand() / RAND_MAX) - 0.5f, ((float)rand() / RAND_MAX) - 0.5f)*e->attack2BulletFluctuation())*e->bulletSpeed(),
				e->attackDamage2(),e->bulletSize());
		}
		if (Cnt >= e->animEndFrame_Attack2()) {
			e->states()->change("IDEL");
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
		return "ATTACK2";
	}
private:
	int Cnt = 0;
};