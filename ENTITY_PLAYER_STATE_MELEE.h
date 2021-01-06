#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/ANIMATION.h"
#include "../Library/VECTOR2.h"
#include "../Library/MATRIX.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_PLAYER.h"
#include "INPUT_COMMON.h"
#include "ENTITY_STATE.h"
class ENTITY_PLAYER_STATE_MELEE :public ENTITY_STATE<ENTITY_PLAYER> {
public:
	ENTITY_PLAYER_STATE_MELEE(ENTITY_PLAYER* owner) :ENTITY_STATE<ENTITY_PLAYER>(owner) {
		Cnt = 0;
	}
	void onEnter() {
		auto e = owner();
		e->tree()->setNextAnimation(e->anim_Melee(), e->toAnim_idel(),0.0f,e->animSpeed_Melee()*e->attackSpeedBoost());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		INPUT_COMMON* in = INPUT_COMMON::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		VECTOR3 camera = e->camera()->lookDirection();
		camera.y = 0.0f;
		camera = normalize(camera);
		VECTOR3 move = e->velo();
		bool isWalk = !in->isNoneMoveAxis();
		if (isWalk) {
			move += VECTOR3(-camera.z, 0.0f, camera.x) * in->moveAxisHorizontal();
			move += VECTOR3(camera.x, 0.0f, camera.z) * in->moveAxisVertical();
			if (!move.isZero()) {
				move = normalize(move);
			}
		}
		if (!e->velo().xz().isZero()) {
			move *= length(e->velo().xz());
		}
		else {
			move = VECTOR3();
		}
		if (isWalk) {
			e->setRy(e->ry() + rotate(VECTOR2(sinf(e->rad().y), cosf(e->rad().y)), normalize(e->velo().xz())) / 15.0f);
		}
		e->setVx(move.x * e->walkInertia());
		e->setVz(move.z * e->walkInertia());
		//指定のフレームに達したら近接攻撃実行
		if (Cnt == (int)(e->activateFrame_Melle()/e->attackSpeedBoost())) {
			sm->playSound(e->soundMelle());
			e->Melle();
		}
		//アニメーションフレームが終わったら次のステートへ
		if (Cnt > (int)(e->animEndFrame_Melee()/e->attackSpeedBoost())) {
			bool isWalk = !in->isNoneMoveAxis();
			if (isWalk) {
				e->states()->change("MOVE");
			}
			else{
				e->states()->change("IDEL");
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
		e->setVy(e->velo().y + e->gravity());
		e->posUpdate();
		Cnt++;
	}
	void onExit() {

	}
	const char* name()const {
		return "MELEE";
	}
private:
	int Cnt = 0;
};