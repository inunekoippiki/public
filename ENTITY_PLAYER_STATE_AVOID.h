#pragma once
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/ANIMATION.h"
#include "../Library/VECTOR2.h"
#include "../Library/MATRIX.h"
#include "../Library/INDEV.h"
#include "ENTITY_MANAGER.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_PLAYER.h"
#include "CAMERA_FOLLOW.h"
#include "INPUT_COMMON.h"
#include "ENTITY_STATE.h"

class ENTITY_PLAYER_STATE_AVOID :public ENTITY_STATE<ENTITY_PLAYER> {
public:
	ENTITY_PLAYER_STATE_AVOID(ENTITY_PLAYER* owner) :ENTITY_STATE<ENTITY_PLAYER>(owner) {
	}
	void onEnter() {
		auto e = owner();
		e->tree()->setNextAnimation(e->anim_Avoid(),e->toAnim_avoid(),0.0f,e->animSpeed_Avoid());
		INPUT_COMMON* in = INPUT_COMMON::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		VECTOR3 camera = e->camera()->lookDirection();
		camera.y = 0.0f;
		camera = normalize(camera);
		VECTOR3 move;
		bool isWalk = !in->isNoneMoveAxis();
		if (isWalk) {
			move += VECTOR3(-camera.z, 0.0f, camera.x) * in->moveAxisHorizontal();
			move += camera*in->moveAxisVertical();
		}
		else{
			move += -camera;
		}
		if (!move.isZero()) {
			move = normalize(move);
		}
		move *= e->avoidSpeed() * e->moveSpeedBoost();
		if (e->skill2Cnt() > 0) {
			move *= e->moveSpeedSkillBoost();
		}
		e->setVelo(move);
		//回避時の無敵
		e->setIsAvoid(true);
		Cnt = 0;
		sm->playSound(e->soundAvoid());
	}
	void update() {
		auto e = owner();
		INPUT_COMMON* in = INPUT_COMMON::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		//回避時の無敵時間解除
		if (Cnt == e->activateEndFrame_Avoid()*e->moveSpeedSkillBoost()) { 
			e->setIsAvoid(false); 
		}
		//アニメーションフレームが終わったら次のステートへ
		if (Cnt>e->animEndFrame_Avoid()) {
			bool isWalk = !in->isNoneMoveAxis();
			if (isWalk) {
				e->states()->change("MOVE");
			}
			else {
				e->states()->change("IDEL");
			}
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
		auto e = owner();
		e->setIsAvoid(false);
		e->setVelo(VECTOR3(0.0f,0.0f,0.0f));
	}
	const char* name()const {
		return "AVOID";
	}
private:
	int Cnt = 0;
};