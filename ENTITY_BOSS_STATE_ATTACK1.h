#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_BOSS.h"
#include "ENTITY_STATE.h"
#include "BILLBOARDS.h"
#include "ENTITY_PLAYER.h"
#include "ENTITY_MANAGER.h"
class ENTITY_BOSS_STATE_ATTACK1 :public ENTITY_STATE<ENTITY_BOSS> {
public:
	ENTITY_BOSS_STATE_ATTACK1(ENTITY_BOSS* owner) :ENTITY_STATE<ENTITY_BOSS>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Attack1(), e->toAnim_Attack1(),0.0f,e->animSpeed_Attack1());
		VECTOR2 Vec = VECTOR2(sinf(e->rad().y), cosf(e->rad().y));
		TargetVec = emeny->player()->centerPos()-e->centerPos();
		FrameRotateRad = rotate(Vec, normalize(TargetVec.xz())) / e->activateFrame_Attack1();
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		INDEV* in = INDEV::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		if (Cnt < e->activateFrame_Attack1()) {
			e->setRy(e->ry() + FrameRotateRad);
		}
		if (Cnt == e->activateFrame_Attack1()) {
			sm->playSound(e->soundAttack1(),e->centerPos());
			e->entityManager()->appearLaserBoss(e->centerPos(),
				normalize(TargetVec) * e->laserLength(),
				e->laserSize(), e->attackDamage1(),
				e->laserLifeTime());
		}
		if (Cnt >= e->animEndFrame_Attack1()) {
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
		return "ATTACK1";
	}
private:
	int Cnt = 0;
	VECTOR3 TargetVec;
	float FrameRotateRad = 0.0f;
};