#pragma once
#include <vector>
#include <functional>
#include "../Library/VECTOR2.h"
#include "../Library/STATIC_FONT.h"
#include "TEXT_DISP.h"
#include "DIALOG_STORY_SKIP.h"
#include "STATE.h"
class UI_2D_LEFT;
class TEXTURE;
class SOUND;
class STORY_TEXT_LAYOUT;
//�X�g�[���[�X�e�[�g
class STORY :public STATE {
public:
	STORY();
	~STORY();
	void create(STATE_MANAGER* stateManager, const char* fileName, const std::function<STATE* (STATE_MANAGER*)>& nextState);
	void storyLoad(STATE_MANAGER* stateManager, const char* fileName);
	void proc(STATE_MANAGER* stateManager)override;
private:
	STATE_MANAGER* StateManager = nullptr;
	struct IMG {
		TEXTURE* Texture = nullptr;
		VECTOR2 Pos;
		int DispPage = 0;//�\���J�n�y�[�W
		int DispPageEnd = 0;//�\���I���y�[�W
		float FeedInSpeed = 0;
		float FeedOutSpeed = 0;
		float Alpha = 0.0;//�����x
	};
	IMG* Textures = nullptr;
	int TexturesNum = 0;
	STORY_TEXT_LAYOUT** Texts = nullptr;
	float TextDispSpeed = 0;
	int TextFontSize = 0;
	int TextsNum = 0;
	int TextPage = 0;//���݃e�L�X�g�y�[�W
	struct PAGE_SOUND {
		SOUND* Sound = nullptr;
		int PlayPage = 0;
		int IsLoop = 0;
	};
	PAGE_SOUND** Sounds = nullptr;
	int SoundsNum = 0;
	int SoundsIterator = 0;
	std::function<STATE * (STATE_MANAGER*)> NextState = nullptr;//����STATE
	IDIALOG* SelectDialog = nullptr;
	DIALOG_STORY_SKIP* DialogStorySkip = nullptr;
	UI_2D_LEFT* SkipIcon = nullptr;
};

