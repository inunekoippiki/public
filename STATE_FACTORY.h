#pragma once
class STATE;
class STATE_MANAGER;
namespace STATE_FACTORY {

	//�^�C�g���X�e�[�g���C���X�^���X
	STATE* instanceTitle(STATE_MANAGER* stateManager);
	//�Z�[�u�f�[�^�I���X�e�[�g���C���X�^���X
	STATE* instanceSaveSelect(STATE_MANAGER* stateManager);
	//�v�����[�O�X�e�[�g���C���X�^���X
	STATE* instancePrologue(STATE_MANAGER* stateManager);
	//���j���[�X�e�[�g���C���X�^���X
	STATE* instanceMenu(STATE_MANAGER* stateManager);
	//�I�v�V�����X�e�[�g���C���X�^���X
	STATE* instanceOption(STATE_MANAGER* stateManager,STATE* state);
	//�X�g�[���X�e�[�g�̎��
	enum class STORY_TYPE {
		s00_00,
		s00_01,
		s01_00,
		s01_01,
		s02_00,
		s02_01
	};
	//�X�g�[���X�e�[�g���C���X�^���X
	STATE* instanceStory(STATE_MANAGER* stateManager, STORY_TYPE storyType);
	//�X�e�[�W�X�e�[�g�̎��
	enum class STAGE_TYPE {
		s00,
		s01,
		s02
	};
	//�X�e�[�W�X�e�[�g���C���X�^���X
	STATE* instanceStage(STATE_MANAGER* stateManager, STAGE_TYPE stageType);
}
