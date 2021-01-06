#include <Windows.h>
#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/DATA.h"
#include "../Library/INDEV.h"
#include "../Library/VARIANT_SHADER.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/IMAGE_3D.h"
#include "../Library/TREE.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "FADE.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "EFFEKSSER.h"
#include "BILLBOARDS.h"
#include "COLLISION_MANAGER.h"
#include "UI_MANAGER.h"
#include "UI_3D_CENTERED.h"
#include "STAGE_UI_LAYOUT.h"
#include "CAMERA_FOLLOW.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY.h"
#include "ENTITY_PLAYER.h"
#include "SETTING.h"
#include "SAVE.h"
#include "STAGE.h"
STAGE::STAGE() {
}

STAGE::~STAGE() {
	SAFE_DELETE(StageUiLayout);
	SAFE_DELETE(CollisionManager);
	SAFE_DELETE(EntityManager);
	SAFE_DELETE(UiManager);
	SAFE_DELETE(CameraFollow);
	SAFE_DELETE(Billboards);
	SAFE_DELETE(Effeksser);
}

void STAGE::create(STATE_MANAGER* stateManager){
	//���ʃf�[�^���Z�b�g------------------------------------------
	StateManager = stateManager;
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	C = gameDataCommon->container();
	Effeksser = new EFFEKSSER();
	Font = gameDataCommon->font();
	Save = gameDataCommon->save();
	ENTITY::setEffeksser(Effeksser);
	//������--------------------------------------------------------
	createSahder(stateManager);
	createBillboard();
	createViewProj(stateManager);
	createLight(stateManager);
	createLightViewProj(stateManager);
	createUiManager(stateManager);
	createEntityManager(stateManager);
	createCollisionManager();
	createPlayer(stateManager);
	createCamera(stateManager);
	//�_�C�A���O------------------------------------------------------
	auto dialogYesFunc = [this]() {
		BattleState = BATTLE_STATE::BATTLE_FADE_END_RETRY;
		StateManager->fade()->fadeOutTrigger();
		SelectDialog = nullptr;
	};
	auto dialogNoFunc = [this]() {
		BattleState = BATTLE_STATE::BATTLE_FADE_END_GAMEOVER;
		StateManager->fade()->fadeOutTrigger();
		SelectDialog = nullptr;
	};
	DialogRetry.create(C);
	DialogRetry.dialog()->setYesFunc(dialogYesFunc);
	DialogRetry.dialog()->setNoFunc(dialogNoFunc);
	DialogRetry.dialog()->setCancelFunc(dialogNoFunc);
	//STAGE���ʉ�-----------------------------------------------------
	SoundGameover = C->sound("gameover");
	SoundClear = C->sound("028_se_kirakira8");
	SoundStart = C->sound("se_maoudamashii_system42");
	GameoverStateTime = C->data("STAGE::GameoverStateTime");
	//�}�E�X�Ŏ��_�𑀍�ł���悤�ɂ���
	INPUT_COMMON::instance()->MouseAimOn();
	INPUT_COMMON::instance()->resetState();
}

void STAGE::createMap(TREE* map){
	Map = map;
}

void STAGE::createStartMessage( const char* storyFileName, const char* charaName){
	StageUiLayout->initStartMessage(C, Font,UiManager, storyFileName, charaName);
}

void STAGE::createEndMessage( const char* storyFileName, const char* charaName){
	StageUiLayout->initEndMessage(C, Font, UiManager, storyFileName, charaName);
}

void STAGE::proc(STATE_MANAGER* stateManager) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	//Update-------------------------------------------------------------------
	GRAPHIC* g = GRAPHIC::instance();
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	in->getState();
	DEBUG_STR* ds = DEBUG_STR::instance();
	if (BattleState == BATTLE_STATE::START) {
		if (in->isTriggerEnter()) {//����Ńo�g���X�^�[�g
			BattleStart();
		}
	}
	// View�X�V
	if (BattleState == BATTLE_STATE::START) {
		//START�̒i�K�ł͈ꕔ�̃A�b�v�f�[�g���~�߂�
		cameraUpdate();
		ui3dUpdate();
	}
	else {
		cameraUpdate();
		stageUiLayoutUpdate();
		entityUpdate();
		collisionManagerUpdate();
		billboardUpdate();
		ui3dUpdate();
	}
	//�G�t�F�N�g�̃A�b�v�f�[�g
	Effeksser->updateProj(Proj);
	Effeksser->updateView(View);
	Effeksser->update();

	if (SelectDialog != nullptr) {
		SelectDialog->update();
	}
	else{
		if (BattleState == BATTLE_STATE::BATTLE_END_GAMEOVER) {
			//�Q�[���I�[�o���̓Q�[���I�[�o�[��ʂ��o�I���܂Ń��j���[�ɖ߂�Ȃ�
			if (++GameoverStateCnt >= GameoverStateTime) {
				if (in->isTriggerEnter()) {
					SelectDialog = &DialogRetry;
					SelectDialog->init();
					BattleState = BATTLE_STATE::BATTLE_END_RETRY;
				}
			}
		}
		//�Q�[���I�[�o�[���ŏI���ƃ��g���C�_�C�����O�\��
		if (BattleState == BATTLE_STATE::BATTLE_END_GAMEOVER) {
			if (++GameoverStateCnt > GameoverStateTime) {
				SelectDialog = &DialogRetry;
				SelectDialog->init();
			}
		}
	}
	if (BattleState == BATTLE_STATE::BATTLE_END_CLEAR) {
		battleClearStateUpdate(stateManager);
	}

	sm->update();
	ds->set("hp:%d sp:%d", Player->hp(), Player->sp());
	ds->set("pos.x:%f pos.y:%f pos.z:%f", Player->px(), Player->py(), Player->pz());
	//Draw---------------------------------------------------------------------
	g->clearTarget(ClearTargetColor);

	//Batch,Tree�\��
	SHADER* shader;
	shaderSet(&shader);
	BEGIN_PATH_
		g->setTextureSamplerWrap();
		entityManagerDraw(shader);
		Map->draw(shader);
		g->setTextureSamplerClamp();
	END_PATH_

	//�u���[����������p�̃��C���[�Ƀ����_�[�^�[�Q�b�g��ύX
	g->setRenderTargetBloom();
	//�G�t�F�N�g
	g->setDepthWritingDisable();
	Effeksser->draw();

	//�r���{�[�h
	shader = Image3dShader;
	//�������[�h�����Z��
	g->SetBlendStateAdd();
	//�[�x�������ݖ���
	g->setDepthWritingDisable();
	BEGIN_PATH_
		billboardDraw(shader);
	END_PATH_
	//�[�x�������ݗL��
	g->setDepthWritingEnable();
	//�������[�h��ʏ��
	g->SetBlendStateAlign();
	//�u���[���e�N�X�`��������
	g->bloomDraw();
	//�����_�[�^�[�Q�b�g�����C���ɖ߂�
	g->setRenderTargetMain();
	//�Q�c
	shader = Image2dShader;
	BEGIN_PATH_
		uiManagerDraw(shader);
		if (SelectDialog != nullptr) {
			SelectDialog->draw(shader);
		}
		fadeDraw(stateManager, shader);
		ds->draw(shader);
	END_PATH_

	g->present();
}
void STAGE::gameClear(int round){
	StageUiLayout->showClear();
	BattleState = BATTLE_STATE::BATTLE_END_CLEAR;
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->playSound(SoundClear);
	Save->clearRound(round);
}

void STAGE::gameOver(){
	StageUiLayout->showGameOver();
	BattleState = BATTLE_STATE::BATTLE_END_GAMEOVER;
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->playSound(SoundGameover);
}

void STAGE::createSahder(STATE_MANAGER* stateManager){
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	VariantShader = gameDataCommon->valiantShader();
	Image2dShader = gameDataCommon->image2dShader();
	Image3dShader = gameDataCommon->image3dShader();
}

void STAGE::createBillboard(){
	Billboards = new BILLBOARDS();
	Billboards->create(C);
	ENTITY::setBillboards(Billboards);
	ENTITY_MANAGER::setBillboards(Billboards);
}

void STAGE::createViewProj(STATE_MANAGER* stateManager){
	GRAPHIC* g = GRAPHIC::instance();
	// Proj
	Proj.setPers(3.141592f / 4.0f, g->aspect(), -0.1f, -50.1f);
	ClearTargetColor.r = C->data("STAGE::ClearTargetColor.r");
	ClearTargetColor.g = C->data("STAGE::ClearTargetColor.g");
	ClearTargetColor.b = C->data("STAGE::ClearTargetColor.b");
}

void STAGE::createLight(STATE_MANAGER* stateManager){
	// Light
	LightPos = VECTOR3(C->data("STAGE::LightPos.x"), 
		C->data("STAGE::LightPos.y"),
		C->data("STAGE::LightPos.z"));
	Ambient = C->data("STAGE::Ambient");
	Diffuse = COLOR(C->data("STAGE::Diffuse.r"),
		C->data("STAGE::Diffuse.g"), 
		C->data("STAGE::Diffuse.b"),
		1.0f);
}

void STAGE::createLightViewProj(STATE_MANAGER* stateManager){
	// Light�����View��Proj
	LightView.set(LightPos, VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//���C�g���猩�����_�Q�ɕϊ�����}�g���b�N�X
	LightProj.setOrtho(35.0f, 35.0f, -1.0f, -20.0f);//�����e�i�����܂�܁��������̂����������Ȃ��j�}�g���b�N�X
}

void STAGE::createUiManager(STATE_MANAGER* stateManager){
	//UI
	UiManager = new UI_MANAGER();
	ENTITY::setUiManager(UiManager);
	StageUiLayout = new STAGE_UI_LAYOUT();
	StageUiLayout->create(C, UiManager);
}

void STAGE::createEntityManager(STATE_MANAGER* stateManager){
	//�G���e�B�e�B�}�l�[�W���[
	EntityManager = new ENTITY_MANAGER(C);
	ENTITY::setEntityManager(EntityManager);
}

void STAGE::createCollisionManager(){
	CollisionManager = new COLLISION_MANAGER(C);
	ENTITY_MANAGER::setCollisionManager(CollisionManager);//�G���e�B�e�B�}�l�[�W���[�ɃR���W�����}�l�[�W���[���Z�b�g
	ENTITY::setCollisionManager(CollisionManager);
}

void STAGE::createPlayer(STATE_MANAGER* stateManager){
	Player = EntityManager->appearPlayer(VECTOR3(0.0f, 0.0f, 0.0f));
	Player->loadStatus(stateManager->gameDataCommon()->upgrade());
}

void STAGE::createCamera(STATE_MANAGER* stateManager){
	CameraFollow = new CAMERA_FOLLOW(C, nullptr);
	CameraFollow->setAimSensitivity(stateManager->gameDataCommon()->setting()->aimSensitivity()->percentage());
	CameraFollow->setViewPos(Player->posPtr());
	CameraFollow->setTerrain(CollisionManager->collisionTerrain());
	CameraFollow->setAutoRotate(true);
	Player->setCamera(CameraFollow);
}

void STAGE::fadeInStart(STATE_MANAGER* stateManager){
	//�t�F�[�h�C���X�^�[�g
	stateManager->fade()->fadeInTrigger();
}

void STAGE::BattleStart(){
	BattleState = BATTLE_STATE::BATTLE;
	CameraFollow->setAutoRotate(false);
	StageUiLayout->closeStartMessage();
	INPUT_COMMON::instance()->getState();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->playSound(SoundStart);

}

void STAGE::stageUiLayoutUpdate(){
	StageUiLayout->setPlayerDataUpdate(Player);
	StageUiLayout->update();
}

void STAGE::ui3dUpdate(){
	UiManager->setProjView(Proj * View);
}

void STAGE::entityUpdate() {
	EntityManager->update();
}
void STAGE::collisionManagerUpdate() {
	CollisionManager->exeCollision();
}
void STAGE::billboardUpdate(){
	Billboards->update(CameraFollow->cameraPos(), CameraFollow->lookDirection());
}

void STAGE::cameraUpdate(){
	CameraFollow->update(&View);
}

void STAGE::battleClearStateUpdate(STATE_MANAGER* stateManager){
	//�N���A���̃��b�Z�[�W�̓t�F�[�h�Ȃ��Ȃ̂ŏo���惁�j���[�ɖ߂��悤�ɂ���
	if (INPUT_COMMON::instance()->isTriggerEnter()) {
		stateManager->fade()->fadeOutTrigger();
		BattleState = BATTLE_STATE::BATTLE_FADE_END_CLEAR;
	}
}

void STAGE::shaderSet(SHADER** shader) {
	SHADER*& s = *shader;
	s = VariantShader;
	s->setLightPosition(LightPos);
	s->setLightAmbient(Ambient);
	s->setDiffuse(Diffuse);
	s->setProjView(Proj * View);
	s->setLight_ProjView(LightProj * LightView);
}

void STAGE::entityManagerDraw(SHADER* shader){
	EntityManager->draw(shader);
}

void STAGE::billboardDraw(SHADER* shader) {
	Billboards->draw(shader, VECTOR3(-CameraFollow->verticalRad(), CameraFollow->horizontalRad(), 0));
}

void STAGE::uiManagerDraw(SHADER* shader){
	UiManager->draw(shader);
}

void STAGE::fadeDraw(STATE_MANAGER* stateManager,SHADER* shader){
	stateManager->fade()->draw(shader);
}
