#pragma once
#include "STATE.h"
#include "../Library/FONT.h"
class TEXTURE;
class SOUND;
//タイトルステート
class TITLE :public STATE {
public:
	TITLE();
	~TITLE();
	void create(STATE_MANAGER* stateManager);
	void proc(STATE_MANAGER* stateManager)override;
private:
	TEXTURE* TextureTitle = nullptr;
	TEXTURE* TextureStart = nullptr;
	TEXTURE* TextureStartEffect = nullptr;
	bool IsEnter = false;
	bool IsStart = false;
	int EffectCnt = 0;
	float EffectPlaySpeed = 0;
	int EffectInterval = 0;
	SOUND* BgmTitle = nullptr;
	SOUND* SoundTitleStart = nullptr;
};

