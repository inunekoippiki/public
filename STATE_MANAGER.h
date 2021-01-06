#pragma once
#include "../Library/common.h"
#include "GAME_DATA_COMMON.h"
class FADE;
class STATE;
class STATE_MANAGER {
public:
	STATE_MANAGER();
	~STATE_MANAGER();
	void create();
	void proc();
	void setNextState(STATE* nextState);
	GAME_DATA_COMMON* gameDataCommon() { return &GameDataCommon; };
	FADE* fade() { return Fade; };
private:
	//�e�X�e�[�g��this�|�C���^��n�����Ƃɂ���āA�ȉ��̃I�u�W�F�N�g���g�p�\�ƂȂ�
	STATE* State = nullptr;
	//���ʃf�[�^
	GAME_DATA_COMMON GameDataCommon;
	//�t�F�[�h�p
	FADE* Fade = nullptr;
};