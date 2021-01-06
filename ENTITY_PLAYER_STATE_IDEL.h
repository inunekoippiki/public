#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/ANIMATION.h"
#include "../Library/VECTOR2.h"
#include "../Library/MATRIX.h"
#include "ENTITY_MANAGER.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_PLAYER.h"
#include "INPUT_COMMON.h"
#include "ENTITY_STATE.h"
class ENTITY_PLAYER_STATE_IDEL :public ENTITY_STATE<ENTITY_PLAYER> {
public:
	ENTITY_PLAYER_STATE_IDEL(ENTITY_PLAYER* owner) :ENTITY_STATE<ENTITY_PLAYER>(owner) {
	}
	void onEnter() {
		auto e = owner();
		e->tree()->setNextAnimation(e->anim_Idel(),e->toAnim_idel(),0.0f,e->animSpeed_Idel());

	}
	void update() {
		auto e = owner();
		INPUT_COMMON* in = INPUT_COMMON::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		bool isWalk = !in->isNoneMoveAxis();
		if (isWalk) {
			e->states()->change("MOVE");
		}
		if (in->isTriggerShot()) {
			e->states()->change("SHOT");
		}
		if (in->isTriggerMelle()) {
			e->states()->change("MELEE");
		}
		if (in->isTriggerSkill()) {
			switch (e->skillChoiceType()){
			case 0:
				e->states()->change("SKILL1");
				break;
			case 1:
				e->states()->change("SKILL2");
				break;
			case 2:
				e->states()->change("SKILL3");
				break;
			}
		}
		if (in->isTriggerAvoid()) {
			e->states()->change("AVOID");
		}
		//スキルタイプチェンジ
		if (in->isTriggerSkillChange()) {
			sm->playSound(e->soundSkillChange());
			e->SkillTypeChange();
		}
		//hpが0以下になったらDOWNステートへ
		if (e->hp() <= 0) {
			States->change("DOWN");
		}

		e->setVx(e->vx() * e->walkInertia());
		e->setVz(e->vz() * e->walkInertia());
		e->setVy(e->velo().y + e->gravity());
		e->posUpdate();
	}
	void onExit() {

	}
	const char* name()const {
		return "IDEL";
	}
private:
};