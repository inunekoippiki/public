#include "../Library/CONTAINER.h"
#include "UI_3D_CENTERED.h"
#include "UI_2D_LEFT.h"
#include "UI_MANAGER.h"
#include "UI_DRAWER_FACTORY.h"
#include "BOSS_FLASH.h"
BOSS_FLASH::BOSS_FLASH() {
}

BOSS_FLASH::~BOSS_FLASH() {
	//投げっぱ
	//リストに入れるので最後にはちゃんとデリートされる
}

void BOSS_FLASH::create(CONTAINER* c, UI_MANAGER* uiManager){
	//広がっていく光
	BossDeathFlash = new UI_3D_CENTERED();
	BossDeathFlash->setDrawer(UI_DRAWER_FACTORY::instance(c, "bossDeath"));
	BossDeathFlash->setInvisible(true);
	uiManager->add(BossDeathFlash, 10000);
	//全体の光
	BossDeathFlash2 = new UI_2D_LEFT();
	BossDeathFlash2->setDrawer(UI_DRAWER_FACTORY::instance(c, "white"));
	BossDeathFlash2->setInvisible(true);
	uiManager->add(BossDeathFlash2, 10001);
}

void BOSS_FLASH::update(){
	if (IsPlay) {
		BossDeathFlash->setScale(VECTOR2(BossDeathFlashScale, BossDeathFlashScale));
		BossDeathFlashScale += 4.0f;
		BossDeathFlash2->setColor(COLOR(1.0f, 1.0f, 1.0f, BossDeathFlashAlpha));
		BossDeathFlashAlpha += 1.0f / 170.0f;
	}
}

void BOSS_FLASH::startPlay(const VECTOR3& pos){
	IsPlay = true;
	BossDeathFlash->setInvisible(false);
	BossDeathFlash->setPos(pos);
	BossDeathFlash2->setInvisible(false);
}
