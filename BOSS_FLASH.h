#pragma once
class UI_3D_CENTERED;
class UI_2D_LEFT;
//ƒ{ƒX‚ª€‚ñ‚¾‚Æ‚«‚ÌŒõ‚Ì‰‰o
class BOSS_FLASH{
public:
	BOSS_FLASH();
	~BOSS_FLASH();
	void create(CONTAINER* c, UI_MANAGER* uiManager);
	void update();
	void startPlay(const VECTOR3& pos);
private:
	bool IsPlay = false;
	UI_3D_CENTERED* BossDeathFlash = nullptr;
	float BossDeathFlashScale = 0.0f;
	UI_2D_LEFT* BossDeathFlash2 = nullptr;
	float BossDeathFlashAlpha = 0.0f;
	float BossHpGaugeWidth = 0.0f;
};

