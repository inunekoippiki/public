
#pragma warning(disable:4996)
#include <stdio.h>
#include "../Library/common.h"
#include "../Library/GRAPHIC.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/INDEV.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/CONTAINER.h"
#include "../Library/SOUND.h"
#include "DATA_LIB.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "STATE_MANAGER.h"
#include "STATE_FACTORY.h"
#include "SAVE_SELECT.h"
#include "UI_2D_LEFT.h"
#include "FADE.h"
#include "DIALOG_STORY_SKIP.h"
#include "UI_DRAWER_FACTORY.h"
#include "STORY_TEXT_LAYOUT.h"
#include "STORY.h"
STORY::STORY() {
}

STORY::~STORY() {
	SAFE_DELETE_ARRAY(Textures);
	for (int i = 0;i < TextsNum;i++) {
		SAFE_DELETE(Texts[i]);
	}
	for (int i = 0;i < SoundsNum;i++) {
		SAFE_DELETE(Sounds[i]);
	}
	SAFE_DELETE_ARRAY(Sounds);
	SAFE_DELETE_ARRAY(Texts);
	SAFE_DELETE(DialogStorySkip);
	delete SkipIcon;
}

void STORY::create(STATE_MANAGER* stateManager, const char* fileName, const std::function<STATE* (STATE_MANAGER*)>& nextState) {
	StateManager = stateManager;
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();
	TextDispSpeed = c->data("StoryDispSpeed");
	TextFontSize = c->data("StoryFontSize");
	//�_�C�A���O
	auto dialogYesFunc = [this]() {
		StateManager->fade()->fadeOutTrigger();
		INPUT_COMMON::instance()->resetState();
	};
	auto dialogNoFunc = [this]() {			
		SelectDialog = nullptr;
	};
	DialogStorySkip = new DIALOG_STORY_SKIP();
	DialogStorySkip->create(c, gameDataCommon->font());
	DialogStorySkip->stringDialog()->setYesFunc(dialogYesFunc);
	DialogStorySkip->stringDialog()->setNoFunc(dialogNoFunc);
	DialogStorySkip->stringDialog()->setCancelFunc(dialogNoFunc);
	//�X�L�b�v�A�C�R��
	SkipIcon = new UI_2D_LEFT();
	SkipIcon->setDrawer(UI_DRAWER_FACTORY::instance(c, "storySkipIcon"));
	SkipIcon->setPos(DATA_LIB::vector2(c, "STORY::SkipIconPos"));
	//�X�g�[����ǂݍ���
	storyLoad(stateManager, fileName);
	//���̃X�e�[�g�̊֐���ݒ�
	NextState = nextState;
	//�t�F�[�h�C���X�^�[�g
	stateManager->fade()->fadeInTrigger();
}

void STORY::storyLoad(STATE_MANAGER* stateManager, const char* fileName) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	CONTAINER* c = gameDataCommon->container();
	//�X�g�[���[�C���[�W���C�A�E�g�ǂݍ���/////////////////////////////////////////////////////
	FILE* fp = fopen(fileName, "r");
	WARNING(!fp, "�X�g�[���[�f�[�^������܂���", fileName);
	fscanf(fp, "%d", &TexturesNum);
	char s[256] = {0};
	Textures = new IMG[TexturesNum];
	int feedInFrame = 0;
	int feedOutFrame = 0;
	for (int i = 0;i < TexturesNum;i++) {
		fscanf(fp, "%s %f %f %d %d %d %d",
			s,
			&Textures[i].Pos.x,
			&Textures[i].Pos.y,
			&Textures[i].DispPage,
			&feedInFrame,
			&Textures[i].DispPageEnd,
			&feedOutFrame);
		Textures[i].Texture = c->texture(s);
		//0�y�[�W����\���͂����œ����x��������
		if (Textures[i].DispPage == 0) {
			Textures[i].Alpha = 1.0f;
		}
		//�t�F�[�h�t���[����1�ȉ��ɂ͂Ȃ�Ȃ�
		Textures[i].FeedInSpeed = max((1.0f / feedInFrame), 1.0f);
		Textures[i].FeedOutSpeed = max((1.0f / feedOutFrame), 1.0f);
	}

	
	//�X�g�[���[���͓ǂݍ���////////////////////////////////////////////////////////
	fscanf(fp, "%d", &TextsNum);
	char storyFileName[256];//Assets/story/�Z�Z�@�܂ł�����
	strcpy(storyFileName, fileName);
	size_t len = strlen(storyFileName);
	storyFileName[len - 4] = storyFileName[len];//.txt�𖳂��������Ƃɂ���
	char storyCatBack[256] = {0};//�e�L�X�g�̖��O
	Texts = new STORY_TEXT_LAYOUT * [TextsNum];
	for (int i = 0;i < TextsNum;i++) {
		Texts[i] = new STORY_TEXT_LAYOUT;
		char _storyFileName[256] = {0};
		char charaNameBuffer[256] = {0};
		fscanf(fp, "%s %s", charaNameBuffer, storyCatBack);
		if (charaNameBuffer[0] == '_') {
			charaNameBuffer[0] = '\0';
		};

		strcpy(_storyFileName, storyFileName);
		strcat(_storyFileName, "/");
		strcat(_storyFileName, storyCatBack);
		strcat(_storyFileName, ".txt");
		TEXT_DISP* textLeft = new TEXT_DISP(gameDataCommon->font());
		textLeft->create(_storyFileName);
		textLeft->setInterval(TextDispSpeed);
		textLeft->setFontSize(TextFontSize);
		Texts[i]->create(c, gameDataCommon->font(), textLeft, charaNameBuffer);
	}
	//�����ǂݍ���//////////////////////////////////////////////////////////////////
	fscanf(fp, "%d", &SoundsNum);
	Sounds = new PAGE_SOUND * [SoundsNum];
	char soundName[256] = {0};
	for (int i = 0;i < SoundsNum;i++) {
		Sounds[i] = new PAGE_SOUND;
		fscanf(fp, "%s %d %d", soundName, &Sounds[i]->PlayPage, &Sounds[i]->IsLoop);
		Sounds[i]->Sound = c->sound(soundName);
	}
	fclose(fp);
}

void STORY::proc(STATE_MANAGER* stateManager) {
	GAME_DATA_COMMON* gameDataCommon = stateManager->gameDataCommon();
	DEBUG_STR* ds = DEBUG_STR::instance();
	//Update
	INDEV* indev = INDEV::instance();
	if (stateManager->fade()->fadeInEndFlag()) {
		indev->getState();
	}
	INPUT_COMMON* in = INPUT_COMMON::instance();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();

	//���ʉ��Đ�
	if (SoundsIterator < SoundsNum) {
		if (TextPage == Sounds[SoundsIterator]->PlayPage) {//���̃y�[�W�����ʉ���炷�y�[�W�ƈꏏ��������
			if (Sounds[SoundsIterator]->IsLoop) {//���[�v����Ȃ�
				sm->setNextBgm(Sounds[SoundsIterator]->Sound);//���[�v�ŉ���炷
			}
			else {
				sm->playSound(Sounds[SoundsIterator]->Sound);//����炷
			}
			SoundsIterator++;//����炵�I������玟�ɍĐ��������ʉ��ɕς���
		}
	}
	if (SelectDialog == nullptr) {
		if (in->isTriggerStorySkip()) {
			SelectDialog = DialogStorySkip;
			SelectDialog->init();
		}
		//�X�g�[���\�����I���
		if (Texts[TextPage]->isEnd()) {
			if (in->isTriggerEnter()) {
				TextPage++;
				if (TextPage == TextsNum) {
					TextPage--;
					//���̃X�e�[�g��
					stateManager->fade()->fadeOutTrigger();
					INPUT_COMMON::instance()->resetState();
				}
			}
		}
		else {
			if (in->isTriggerEnter()) {
				Texts[TextPage]->allDisp();
			}
		}
	}
	else {
		SelectDialog->update();
	}
	Texts[TextPage]->update();
	sm->update();

	//Draw-----------------------------------------------------------------------------
	GRAPHIC* g = GRAPHIC::instance();
	g->clearTarget(0.3f, 0.6f, 1.0f);
	SHADER* shader = gameDataCommon->image2dShader();
	BEGIN_PATH_
		int pixcelCnt = 0;
		int textureCnt = 0;
		for (int i = 0;i < TexturesNum;i++) {
			if (TextPage >= Textures[i].DispPage) {
				if (TextPage >= Textures[i].DispPageEnd && Textures[i].DispPageEnd != -1) {
					//�t�F�[�h�A�E�g
					Textures[i].Alpha -= Textures[i].FeedOutSpeed;
					if (Textures[i].Alpha < 0.0f) {
						Textures[i].Alpha = 0.0f;
					}
				}
				else {
					//�t�F�[�h�C��
					Textures[i].Alpha += Textures[i].FeedInSpeed;
					if (Textures[i].Alpha > 1.0f) {
						Textures[i].Alpha = 1.0f;
					}
				}
			}
			//���S�ɓ����̂��͕̂`�悵�Ȃ�
			if (Textures[i].Alpha > 0.0f) {
				Textures[i].Texture->draw(shader, Textures[i].Pos, COLOR(1.0f, 1.0f, 1.0f, Textures[i].Alpha));
				pixcelCnt += Textures[i].Texture->width() * Textures[i].Texture->height();
				textureCnt++;
			}
		}
		ds->set("textureCnt:%d  pixcelCnt:%d", textureCnt, pixcelCnt);
		//�摜�������BDispPageEnd��-1�ɂ��ĂĂ�����
		//�����ʒu�ɏo�Ă鍂���A���������摜�͌�납������Ă���
		for (int i = 0;i < TexturesNum;i++) {
			//�\���O��A�����ł���������̂͏���
			if (TextPage >= Textures[i].DispPage&& Textures[i].Alpha == 1.0f) {
				for (int i2 = i + 1;i2 < TexturesNum;i2++) {
					//�\���O��A�����ł���������̂͏���
					if (TextPage >= Textures[i2].DispPage && Textures[i2].Alpha == 1.0f) {
						//�|�W�V�����ƃT�C�Y��������������
						if (Textures[i].Pos == Textures[i2].Pos&&
							Textures[i].Texture->width() == Textures[i2].Texture->width()&&
							Textures[i].Texture->height() == Textures[i2].Texture->height()) {
							//�O�ɕ\�����n�߂����̂������
							if (Textures[i].DispPage <= Textures[i2].DispPage) {
								Textures[i].DispPageEnd = 0;
							}
							else {
								Textures[i2].DispPageEnd = 0;
							}
						}
					}
				}
			}
		}
		//���݂̃y�[�W�̃e�L�X�g��`��
		Texts[TextPage]->draw(shader);
		if (SelectDialog != nullptr) {
			SelectDialog->draw(shader);
		}
		SkipIcon->draw(shader);
		ds->draw(shader);
		stateManager->fade()->draw(shader);
	END_PATH_
	g->present();

	//�J��-----------------------------------------------------------------------------------
	//�I�v�V����
	if (in->isTriggerOption()) {
		stateManager->setNextState(STATE_FACTORY::instanceOption(stateManager,this));
	}
	//���S�Ƀt�F�[�h�A�E�g�����玟�̃X�e�[�g��
	if (stateManager->fade()->fadeOutEndFlag()) {
		auto nextState = NextState;
		delete this;
		stateManager->setNextState(nextState(stateManager));
	}
}