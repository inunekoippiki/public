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
class ENTITY_PLAYER_STATE_MOVE :public ENTITY_STATE<ENTITY_PLAYER>{
public:
	ENTITY_PLAYER_STATE_MOVE(ENTITY_PLAYER* owner) :ENTITY_STATE<ENTITY_PLAYER>(owner){
	}
	void onEnter(){
		auto e = owner();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		e->tree()->setNextAnimation(e->anim_Move(),e->toAnim_move(),0.0f,e->animSpeed_Move()*e->moveSpeedBoost());
		sm->playSoundLoop(e->soundFootStep());
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
		//移動速度を計算
		float moveSpeed = e->moveSpeed() * e->moveSpeedBoost();
		//スキル２が発動中はスキルでブーストされる
		if (e->skill2Cnt() > 0) { moveSpeed *= e->moveSpeedSkillBoost(); }
		e->setVx(move.x * moveSpeed);
		e->setVz(move.z * moveSpeed);
		e->setVy(e->velo().y + e->gravity());
		e->posUpdate();
		if (isWalk) {
			e->setRy(e->ry() + rotate(VECTOR2(sinf(e->rad().y), cosf(e->rad().y)), normalize(e->velo().xz())) / 15.0f);
		}
		if(!isWalk){
			e->states()->change("IDEL");
		}
		if (in->isTriggerShot()) {
			e->states()->change("SHOT");
		}
		if (in->isTriggerMelle()) {
			e->states()->change("MELEE");
		}
		if (in->isTriggerSkill()) {
			switch (e->skillChoiceType()) {
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

	}
	void onExit(){
		auto e = owner();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		sm->stopSound(e->soundFootStep());
	}
	const char* name()const{
		return "MOVE";
	}
private:
	float MoveAnimSpeed = 0;
};