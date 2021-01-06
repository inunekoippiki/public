#include "UI_DRAWER_FACTORY.h"
#include "HP_GAUGE.h"
HP_GAUGE::HP_GAUGE() {
	HpGauge = new UI_3D_LEFT();
	HpGaugeBack = new UI_3D_LEFT();
}

HP_GAUGE::~HP_GAUGE() {
	HpGauge->Delete();
	HpGaugeBack->Delete();
}

void HP_GAUGE::create(CONTAINER* c,UI_MANAGER* uiManager){
	HpGaugeScale = c->data("ENTITY_ENEMY::HpGaugeScale");
	HpGauge->setDrawer(UI_DRAWER_FACTORY::instance(c, "enemyHpGauge"));
	HpGauge->setScale(VECTOR2(HpGaugeScale, HpGaugeScale));
	HpGauge->setOffset(VECTOR2(-HpGaugeScale * 0.5f, 0.0f));
	uiManager->add(HpGauge, c->data("ENTITY_ENEMY::HpGaugeLayerPriority"));
	HpGaugeBack->setDrawer(UI_DRAWER_FACTORY::instance(c, "enemyHpGaugeBack"));
	HpGaugeBack->setScale(VECTOR2(HpGaugeScale, HpGaugeScale));
	HpGaugeBack->setOffset(VECTOR2(-HpGaugeScale * 0.5f, 0.0f));
	uiManager->add(HpGaugeBack, c->data("ENTITY_ENEMY::HpGaugeBackLayerPriority"));

}

void HP_GAUGE::setWidth(int hp, int maxHp){
	HpGaugeWidth = (float)hp / max(maxHp, 1);
	HpGauge->setScale(VECTOR2(HpGaugeWidth * HpGaugeScale, HpGaugeScale));
}

void HP_GAUGE::setWidth(const HIT_POINT& hitPoint){
	setWidth(hitPoint.hp(), hitPoint.maxHp());
}

void HP_GAUGE::setPos(const VECTOR3& pos){
	HpGauge->setPos(pos);
	HpGaugeBack->setPos(pos);
}
