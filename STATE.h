#pragma once
class STATE_MANAGER;
//�X�e�[�g�̃C���^�[�t�F�[�X
class STATE {
public:
	virtual ~STATE() {}
	virtual void proc(STATE_MANAGER* stateManager) = 0;
};