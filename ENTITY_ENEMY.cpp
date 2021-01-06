#include "../Library/DATA.h"
#include "../Library/CONTAINER.h"
#include "STATE_MANAGER.h"
#include "BILLBOARDS.h"
#include "UI_MANAGER.h"
#include "UI_3D_CENTERED.h"
#include "UI_3D_LEFT.h"
#include "ENTITY_PLAYER.h"
#include "UPGRADE.h"
#include "UI_DRAWER_FACTORY.h"
#include "ENTITY_ENEMY.h"
UPGRADE* ENTITY_ENEMY::Upgrade = nullptr;
ENTITY_PLAYER* ENTITY_ENEMY::Player = nullptr;
ENTITY_ENEMY::ENTITY_ENEMY() {

}

ENTITY_ENEMY::~ENTITY_ENEMY() {
}

void ENTITY_ENEMY::create(ENTITY* owner, const VECTOR3& upperPosOffest, const TREE_ORIGIN* treeOrigin, int maxHp, float gravity){
	Owner = owner;
	CONTAINER* c = owner->gameDataCommon()->container();
	DisappearTime = c->data("ENTITY_ENEMY::DisappearTime");
	DisappearFrequency = c->data("ENTITY_ENEMY::DisappearFrequency");
	UpperPosOffest = upperPosOffest;
	Tree = treeOrigin;
	HpGauge.create(c, owner->uiManager());
	HitPoint.setMaxHp(maxHp);
	HitPoint.hpFull();
	hpGaugeWidthUpdate();
	Gravity = gravity;
}

void ENTITY_ENEMY::treeUpdate(){
	MATRIX world;
	world.mulTranslate(Owner->pos());
	world.mulRotateY(Owner->ry());
	Tree.update(world);
}

void ENTITY_ENEMY::damage(int damage){
	Upgrade->addGiveDamage(damage);
	//プレーヤーにダメージを与えることを出来たことを通知する
	Player->damageDealt(damage);
	//ヒットポイントを減らす
	HitPoint.damage(damage);
	//ヒットエフェクトを出す
	Owner->billboards()->appearHit(Owner->centerPos(), 3.0f);
	if (HitPoint.isDead()) {
		if (IsDeath == false) {//deathを一回しか呼ばないようにする
			death();
		}
	}
	//表示しているhpバーの長さを再計算
	hpGaugeWidthUpdate();
}

void ENTITY_ENEMY::gravityUpdate(){
	Owner->setVy(Owner->vy() + Gravity);
}

void ENTITY_ENEMY::draw(SHADER* shader){
	if (!IsDisappear) {
		Tree.draw(shader);
	}
}

void ENTITY_ENEMY::hpGaugeUpdate(){
	HpGauge.setPos(upperPos());
}

void ENTITY_ENEMY::hpGaugeWidthUpdate(){
	HpGauge.setWidth(HitPoint);
}

void ENTITY_ENEMY::DisappearUpdate(int DisappearCnt){
	IsDisappear = ((int)(DisappearCnt / DisappearFrequency) % 2 == 0);
}

VECTOR3 ENTITY_ENEMY::upperPos(){
	return Owner->pos() + UpperPosOffest;
}


