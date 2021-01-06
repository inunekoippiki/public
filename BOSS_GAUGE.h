#pragma once
#include "../Library/VECTOR2.h"
class UI_2D_RIGHT;
class UI_2D_LEFT;
class HIT_POINT;
//BOSS用の特別なゲージ表示用
class BOSS_GAUGE{
public:
	BOSS_GAUGE();
	~BOSS_GAUGE();
	void create(CONTAINER* c,UI_MANAGER* uiManager);
	//hpゲージの長さを更新
	void hpGaugeUpdate(const HIT_POINT& hitPoint);
private:
	UI_2D_RIGHT* BossHpGauge = nullptr;
	UI_2D_LEFT* BossHpGaugeBack = nullptr;
};

