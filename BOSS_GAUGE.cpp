#include "../Library/CONTAINER.h"
#include "DATA_LIB.h"
#include "UI_2D_LEFT.h"
#include "UI_2D_RIGHT.h"
#include "UI_DRAWER_FACTORY.h"
#include "UI_MANAGER.h"
#include "HIT_POINT.h"
#include "BOSS_GAUGE.h"
BOSS_GAUGE::BOSS_GAUGE() {
}

BOSS_GAUGE::~BOSS_GAUGE() {
	BossHpGauge->Delete();
	BossHpGaugeBack->Delete();
}

void BOSS_GAUGE::create(CONTAINER* c,UI_MANAGER* uiManager){
	VECTOR2 bossHpGaugePos = DATA_LIB::vector2(c, "ENTITY_BOSS::BossHpGaugePos");
	BossHpGauge = new UI_2D_RIGHT();
	BossHpGauge->setPos(bossHpGaugePos);
	BossHpGauge->setDrawer(UI_DRAWER_FACTORY::instance(c, "bossHpGauge"));
	uiManager->add(BossHpGauge, c->data("ENTITY_BOSS::BossHpGaugeLayerPriority"));
	VECTOR2 bossHpGaugeBackPos = DATA_LIB::vector2(c, "ENTITY_BOSS::BossHpGaugeBackPos");
	BossHpGaugeBack = new UI_2D_LEFT();
	BossHpGaugeBack->setPos(bossHpGaugeBackPos);
	BossHpGaugeBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "bossHpGaugeBack"));
	uiManager->add(BossHpGaugeBack, c->data("ENTITY_BOSS::BossHpGaugeLayerBackPriority"));
}

void BOSS_GAUGE::hpGaugeUpdate(const HIT_POINT& hitPoint){
	BossHpGauge->setScale(VECTOR2(hitPoint.ratio(), 1.0f));
}
