#pragma warning (disable:4996)
#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/CONTAINER.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "SOUND_MANAGER.h"
#include "INPUT_COMMON.h"
#include "SAVE.h"
#include "FADE.h"
#include "SAVE_SELECT_UI_LAYOUT.h"
#include "UI_MANAGER.h"
#include "SAVE_SELECT.h"
SAVE_SELECT::SAVE_SELECT() {
}

SAVE_SELECT::~SAVE_SELECT() {
	SAFE_DELETE(UiLayout);
	SAFE_DELETE(DialogNewData);
	SAFE_DELETE(DialogLoadData);
	for (auto& i : DialogSaveDelete) {
		SAFE_DELETE(i);
	}
	SAFE_DELETE(UiManager);
}

void SAVE_SELECT::create(STATE_MANAGER* stateManager){
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();
	UiManager = new UI_MANAGER();
	//�����\����ǂݍ���
	const char* SaveFileName = "Assets/saveData/save";
	for (int i = 0;i < SaveData.size();i++) {
		sprintf(SaveData[i].fileName, "%s%d%s", SaveFileName, i + 1, ".txt");
		FILE* fp;
		fp = fopen(SaveData[i].fileName, "r");
		if (fp == nullptr) {
			SaveData[i].isEmpty = true;
			continue;
		}
		fscanf(fp, "%I64d", &SaveData[i].SaveTime);
		fscanf(fp, "%I64d", &SaveData[i].PlayTime);
		fclose(fp);
	}
	//�Z�[�u�f�[�^��\������UI�����
	UiLayout = new SAVE_SELECT_UI_LAYOUT();
	UiLayout->create(c, gameDataCommon->font(), UiManager, SaveData);
	//�_�C�����O-------------------------------------------------
	auto saveDeleteFunc = [this]() {
		SaveData[choiceIdx].isEmpty = true;
		UiLayout->SaveDataDeleteUpdate(SaveData);
		remove(SaveData[choiceIdx].fileName);
		SelectDialog = nullptr;
	};
	auto saveSelectFunc = [this]() {
		Enter = true;
	};
	auto dialogNoFunc = [this]() {
		SelectDialog = nullptr;
	};
	//�V�����n�߂���������Ƃ��̃_�C�����O
	DialogNewData = new DIALOG_SAVE_SELECT();
	DialogNewData->create(c, gameDataCommon->font(), true);
	DialogNewData->stringDialog()->setYesFunc(saveSelectFunc);
	DialogNewData->stringDialog()->setNoFunc(dialogNoFunc);
	DialogNewData->stringDialog()->setCancelFunc(dialogNoFunc);
	//��������n�߂���������Ƃ��̃_�C�����O
	DialogLoadData = new DIALOG_SAVE_SELECT();
	DialogLoadData->create(c, gameDataCommon->font(), false);
	DialogLoadData->stringDialog()->setYesFunc(saveSelectFunc);
	DialogLoadData->stringDialog()->setNoFunc(dialogNoFunc);
	DialogLoadData->stringDialog()->setCancelFunc(dialogNoFunc);
	//�Z�[�u�f�[�^���������Ƃ����Ƃ��̃_�C�����O
	for (int i = 0;i < DialogSaveDelete.size();i++) {
		DialogSaveDelete[i] = new DIALOG_SAVE_DELETE();
		DialogSaveDelete[i]->create(c, gameDataCommon->font(), i + 1);
		DialogSaveDelete[i]->stringDialog()->setYesFunc(saveDeleteFunc);
		DialogSaveDelete[i]->stringDialog()->setNoFunc(dialogNoFunc);
		DialogSaveDelete[i]->stringDialog()->setCancelFunc(dialogNoFunc);
	}
	//�T�E���h
	SoundChoice = c->sound("ui_choice");
	SoundCancel = c->sound("ui_cancel");
	SoundEnter = c->sound("ui_enter");
	//�t�F�[�h�C���X�^�[�g
	stateManager->fade()->fadeInTrigger();
	INDEV::instance()->reset();
}

void SAVE_SELECT::proc(STATE_MANAGER* stateManager) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	//Update------------------------------------------------------------------------------------------
	INDEV* indev = INDEV::instance();
	if (!IsFead&& stateManager->fade()->fadeInEndFlag()) {
		indev->getState();
	}
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	if (SelectDialog == nullptr) {
		if (in->isTriggerDown()) {
			choiceIdx++;
			//��ɖ߂�
			if (choiceIdx > 2) {
				choiceIdx = 0;
			}
			sm->playSound(SoundChoice);
		}
		if (in->isTriggerUp()) {
			choiceIdx--;
			//���ɔ��
			if (choiceIdx < 0) {
				choiceIdx = 2;
			}
			sm->playSound(SoundChoice);
		}
		if (in->isTriggerEnter()) {
			if (SaveData[choiceIdx].isEmpty) {
				//���肳�ꂽ�Z�[�u�f�[�^���V�����n�߂邾������
				//�V�����n�߂�p�̃_�C�����O���o��
				SelectDialog = DialogNewData;
				SelectDialog->init();
			}
			else {
				//���肳�ꂽ�Z�[�u�f�[�^���r������n�߂邾������
				//���[�h�p�̃_�C�����O���o��
				SelectDialog = DialogLoadData;
				SelectDialog->init();
			}
			sm->playSound(SoundEnter);
		}
		if (in->isTriggerSaveDelete()) {
			if (!SaveData[choiceIdx].isEmpty) {
				SelectDialog = DialogSaveDelete[choiceIdx];
				SelectDialog->init();
				sm->playSound(SoundEnter);
			}
		}
	}
	else {
		SelectDialog->update();
	}
	sm->update();
	UiLayout->choiceIdx(choiceIdx);
	//Draw------------------------------------------------------------------------------------------
	GRAPHIC* g = GRAPHIC::instance();
	g->clearTarget(0.3f, 0.6f, 1.0f);
	SHADER* shader = gameDataCommon->image2dShader();
	BEGIN_PATH_
		UiManager->draw(shader);
		UiLayout->draw(shader);
		if (SelectDialog != nullptr) {
			SelectDialog->draw(shader);
		}
		stateManager->fade()->draw(shader);//�s�����̓��� �摜�\��
	END_PATH_
	g->present();

	//�J��------------------------------------------------------------------------------------------
	//�Z�[�u�f�[�^���I�΂ꂽ�烍�[�h���đJ��
	if (Enter) {
		if (gameDataCommon->save()->load(choiceIdx + 1, gameDataCommon->upgrade())) {
			//�Z�[�u�f�[�^���Ȃ��ꍇ

		}
		stateManager->fade()->fadeOutTrigger();
		indev->reset();
		Enter = false;
		IsFead = true;
	}
	//���S�Ƀt�F�[�h�A�E�g�����玟�̃X�e�[�g��
	if (stateManager->fade()->fadeOutEndFlag()) {
		if (SaveData[choiceIdx].isEmpty) {
			stateManager->setNextState(STATE_FACTORY::instancePrologue(stateManager));
		}
		else{
			stateManager->setNextState(STATE_FACTORY::instanceMenu(stateManager));
		}
		delete this;
		return;
	}
	//�I�v�V����
	if (in->isTriggerOption()) {
		stateManager->setNextState(STATE_FACTORY::instanceOption(stateManager,this));
	}

}
