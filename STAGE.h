#pragma once
#include "../Library/CONTAINER.h"
#include "../Library/MATRIX.h"
#include "../Library/COLOR.h"
#include "../Library/VECTOR3.h"
#include "DIALOG_RETRY.h"
#include "STATE.h"
class SHADER;
class CAMERA_FOLLOW;
class STATE_MANAGER;
class BILLBOARDS;
class COLLISION_MANAGER;
class ENTITY_MANAGER;
class ENTITY_PLAYER;
class UI_MANAGER;
class STAGE_UI_LAYOUT;
class SOUND;
class EFFEKSSER;
class SAVE;
//�X�e�[�g
enum class BATTLE_STATE {
	START,
	BATTLE,
	BATTLE_END_CLEAR,
	BATTLE_END_GAMEOVER,
	BATTLE_END_RETRY,
	BATTLE_FADE_END_CLEAR,
	BATTLE_FADE_END_GAMEOVER,
	BATTLE_FADE_END_RETRY,
};
//�eSTAGE�X�e�[�g�ŗ��p����@�\���������N���X
//�g���O��create�n�̂͗��p���őS�ČĂ�ł�������
class STAGE {
public:
	STAGE();
	~STAGE();
	void create(STATE_MANAGER* stateManager);
	//�}�b�v��ݒ肷��
	void createMap(TREE* map);
	//�X�^�[�g���ɏo�郁�b�Z�[�W��ݒ�
	void createStartMessage(const char* storyFileName, const char* charaName);
	//�N���A���Ɏ��ɏo�郁�b�Z�[�W��ݒ�
	void createEndMessage(const char* storyFileName, const char* charaName);
	//���C�����[�v
	void proc(STATE_MANAGER* stateManager);
	//�N���A�����Ƃ��Ă�
	void gameClear(int round);
	//���s�����Ƃ��Ă�
	void gameOver();

	ENTITY_PLAYER* player() { return Player; }
	ENTITY_MANAGER* entityManager() { return EntityManager; }
	BATTLE_STATE battleState() { return BattleState; }
private:
	void createSahder(STATE_MANAGER* stateManager);
	void createBillboard();
	void createViewProj(STATE_MANAGER* stateManager);
	void createLight(STATE_MANAGER* stateManager);
	void createLightViewProj(STATE_MANAGER* stateManager);
	void createUiManager(STATE_MANAGER* stateManager);
	void createEntityManager(STATE_MANAGER* stateManager);
	void createCollisionManager();
	void createPlayer(STATE_MANAGER* stateManager);
	void createCamera(STATE_MANAGER* stateManager);
	void fadeInStart(STATE_MANAGER* stateManager);
	//�o�g�����X�^�[�g������
	void BattleStart();
	//Ui�̃A�b�v�f�[�g
	void stageUiLayoutUpdate();
	//3D��UI�̕`��ʒu�̃A�b�v�f�[�g
	void ui3dUpdate();
	//�G���e�B�e�B�̃A�b�v�f�[�g
	void entityUpdate();
	//�����蔻��̃A�b�v�f�[�g
	void collisionManagerUpdate();
	//�r���{�[�h�̃A�b�v�f�[�g
	void billboardUpdate();
	//�J�����̃A�b�v�f�[�g
	void cameraUpdate();
	//�N���A�X�e�[�g�̂Ƃ����s����A�b�v�f�[�g
	void battleClearStateUpdate(STATE_MANAGER* stateManager);
	//�V�F�[�_�[�Ƃ��̏���ݒ�
	void shaderSet(SHADER** shader);
	//�G���e�B�e�B�̕`��
	void entityManagerDraw(SHADER* shader);
	//�r���{�[�h�̕`��
	void billboardDraw(SHADER* shader);
	//UI�̕`��
	void uiManagerDraw(SHADER* shader);
	//�t�F�[�h�p�̉摜�`��
	void fadeDraw(STATE_MANAGER* stateManager, SHADER* shader);

	STATE_MANAGER* StateManager = nullptr;
	//�}�b�v
	TREE* Map = nullptr;
	//Shader
	SHADER* VariantShader = nullptr;
	SHADER* Image2dShader = nullptr;
	SHADER* Image3dShader = nullptr;
	//Container
	CONTAINER* C = nullptr;
	STATIC_FONT* Font = nullptr;
	//View�AProj
	CAMERA_FOLLOW* CameraFollow = nullptr;
	MATRIX View;
	MATRIX Proj;
	COLOR ClearTargetColor;
	//Light
	VECTOR3 LightPos;
	float Ambient = 0;
	COLOR Diffuse;
	//Light�����View,Proj
	MATRIX LightView;
	MATRIX LightProj;
	//�r���{�[�h
	BILLBOARDS* Billboards = nullptr;
	//�R���W�����}�l�[�W���[
	COLLISION_MANAGER* CollisionManager = nullptr;
	//ENTITY
	ENTITY_MANAGER* EntityManager = nullptr;
	ENTITY_PLAYER* Player = nullptr;
	//UI
	UI_MANAGER* UiManager = nullptr;
	STAGE_UI_LAYOUT* StageUiLayout = nullptr;
	//�G�t�F�N�g
	EFFEKSSER* Effeksser = nullptr;
	BATTLE_STATE BattleState = BATTLE_STATE::START;
	//�Q�[���I�[�o�[�J�ڗp
	int GameoverStateTime = 0;
	int GameoverStateCnt = 0;
	bool IsClear = false;
	//��
	SOUND* SoundGameover = nullptr;
	SOUND* SoundStart = nullptr;
	SOUND* SoundClear = nullptr;
	//���g���C�_�C�����O
	DIALOG_RETRY DialogRetry;
	//�I�𒆂̃_�C�����O
	IDIALOG* SelectDialog = nullptr;
	//�Z�[�u�f�[�^
	SAVE* Save = nullptr;
};

