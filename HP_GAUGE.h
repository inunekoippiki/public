#pragma once
#include "../Library/CONTAINER.h"
#include "UI_MANAGER.h"
#include "UI_3D_LEFT.h"
#include "HIT_POINT.h"
class HP_GAUGE{
public:
	HP_GAUGE();
	~HP_GAUGE();
	void create(CONTAINER* c, UI_MANAGER* uiManager);
	void setWidth(int hp,int maxHp);
	void setWidth(const HIT_POINT& hitPoint);
	void setPos(const VECTOR3& pos);
private:
	UI_3D_LEFT* HpGauge = nullptr;
	UI_3D_LEFT* HpGaugeBack = nullptr;
	float HpGaugeScale = 0.0f;//スケール
	float HpGaugeWidth = 0.0f;//ゲージの幅の割合0~1
};

