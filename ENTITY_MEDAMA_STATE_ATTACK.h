#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_PLAYER.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_STATE.h"
#include "ENTITY_MEDAMA.h"
class ENTITY_MEDAMA_STATE_ATTACK :public ENTITY_STATE<ENTITY_MEDAMA> {
public:
	ENTITY_MEDAMA_STATE_ATTACK(ENTITY_MEDAMA* owner) :ENTITY_STATE<ENTITY_MEDAMA>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		auto emeny = e->enemy();
		emeny->tree()->setNextAnimation(e->anim_Attack(), e->toAnim_Attack(),0.0f,e->animSpeed_Attack());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		auto emeny = e->enemy();
		ENTITY_PLAYER* player = emeny->player();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		if (Cnt % e->attackInterval() == 0) {
			e->entityManager()->appearLightBulletMedama(e->centerPos(), normalize(player->centerPos() - e->centerPos()) * e->bulletSpeed(), e->attackDamage(), e->bulletSize());
			VECTOR2 v = normalize(emeny->player()->centerPos() - e->centerPos()).xz();
			v = VECTOR2(v.z, -v.x)*3.0f;
			e->entityManager()->appearLightBulletMedama(e->centerPos(), normalize(player->centerPos() - e->centerPos() + VECTOR3(v.x, 0.0f, v.z)) * e->bulletSpeed(), e->attackDamage(), e->bulletSize());
			e->entityManager()->appearLightBulletMedama(e->centerPos(), normalize(player->centerPos() - e->centerPos() + VECTOR3(v.x, 0.0f, v.z) * -1.0f) * e->bulletSpeed(), e->attackDamage(), e->bulletSize());
			sm->playSound(e->soundAttack(), e->pos());
		}
		if (Cnt >= e->attackTime()) {
			e->states()->change("MOVE");
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
		return "ATTACK";
	}
private:
	int Cnt = 0;
};