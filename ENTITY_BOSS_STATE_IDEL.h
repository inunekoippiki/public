#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_BOSS.h"
#include "ENTITY_STATE.h"
class ENTITY_BOSS_STATE_IDEL :public ENTITY_STATE<ENTITY_BOSS> {
public:
	ENTITY_BOSS_STATE_IDEL(ENTITY_BOSS* owner) :ENTITY_STATE<ENTITY_BOSS>(owner) {
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
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		emeny->gravity();
		e->posUpdate();
		if (Cnt > e->idelTime()*e->idelTimeBoost()) {
			switch (rand() % 3){
			case 0:
				e->states()->change("MOVE");
				break;
			case 1:
				e->states()->change("ATTACK1");
				break;
			case 2:
				e->states()->change("ATTACK2");
				break;
			default:
				break;
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