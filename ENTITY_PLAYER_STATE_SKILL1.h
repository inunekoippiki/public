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
class ENTITY_PLAYER_STATE_SKILL1 :public ENTITY_STATE<ENTITY_PLAYER> {
public:
	ENTITY_PLAYER_STATE_SKILL1(ENTITY_PLAYER* owner) :ENTITY_STATE<ENTITY_PLAYER>(owner) {
	}
	void onEnter() {
		auto e = owner();
		e->tree()->setNextAnimation(e->anim_Skill(), e->toAnim_skill(),0.0f,e->animSpeed_Skill());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		INPUT_COMMON* in = INPUT_COMMON::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		//�w��̃t���[���ɒB������X�L������
		if (Cnt == e->activateFrame_Skill()) {
			if (e->SkillActivateAttackBoost()) {
				//����
				sm->playSound(e->soundSkill1());
			}
			else {
				//���s
			}
		}
		//�A�j���[�V�����t���[�����I������玟�̃X�e�[�g��
		if (Cnt >= e->animEndFrame_Skill()) {
			bool isWalk = !in->isNoneMoveAxis();
			if (isWalk) {
				e->states()->change("MOVE");
			}
			else {
				e->states()->change("IDEL");
			}
		}
		//hp��0�ȉ��ɂȂ�����DOWN�X�e�[�g��
		if (e->hp() <= 0) {
			States->change("DOWN");
		}

		Cnt++;
	}
	void onExit() {
		owner()->setVelo(VECTOR3());
	}
	const char* name()const {
		return "SKILL1";
	}
private:
	int Cnt = 0;
};