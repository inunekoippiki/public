#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/ANIMATION.h"
#include "../Library/VECTOR2.h"
#include "../Library/MATRIX.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_PLAYER.h"
#include "ENTITY_STATE.h"
class ENTITY_PLAYER_STATE_DOWN :public ENTITY_STATE<ENTITY_PLAYER> {
public:
	ENTITY_PLAYER_STATE_DOWN(ENTITY_PLAYER* owner) :ENTITY_STATE<ENTITY_PLAYER>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		e->tree()->setNextAnimation(e->anim_Down(),e->toAnim_down(),0.0f,e->animSpeed_Down());
		e->setVelo(VECTOR3());
		sm->playSound(e->soundDown());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		INDEV* in = INDEV::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		//座り込むモーションは繰り返さないように最後のフレームで固定する
		if (Cnt == e->animEndFrame_Down()) {
			e->tree()->setNextAnimation(e->anim_Down(), e->toAnim_down(), e->animEndFrame_Down()-1, 0.0f);
		}
		e->setVy(e->velo().y + e->gravity());
		e->posUpdate();
		Cnt++;
	}
	void onExit() {

	}
	const char* name()const {
		return "DOWN";
	}
private:
	int Cnt = 0;
};