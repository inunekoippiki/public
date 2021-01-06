#pragma warning (disable:4996)
#include <string.h>
#include <stdlib.h>
#include<mbstring.h>
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "DIALOG_UPGRADE.h"
DIALOG_UPGRADE::DIALOG_UPGRADE() {
}

DIALOG_UPGRADE::~DIALOG_UPGRADE() {
}

void DIALOG_UPGRADE::create(CONTAINER* c, STATIC_FONT* font, int upgradeType, int skillPointCost) {
	GRAPHIC* g = GRAPHIC::instance();
	StringDialog.create(c, font);
	StringDialog.setFontSize(c->data("DIALOG_UPGRADE::FontSize"));
		//アップグレード項目の文字
	const char* upgradeTypeString[8] = {
		"体力ステータス",
		"攻撃力ステータス",
		"攻撃範囲ステータス",
		"攻撃速度ステータス",
		"移動速度ステータス",
		"攻撃スキル",
		"移動スキル",
		"回復スキル" };
	sprintf(String1, "%sを強化しますか？", upgradeTypeString[upgradeType]);
	int i = 0;
	String1Pos.y = 430.0f;
	String1Pos.x = g->centerX();

	sprintf(String2, "消費スキルポイント:");
	String2Pos.y = 540.0f;
	String2Pos.x = g->centerX();

}

void DIALOG_UPGRADE::init(){
	StringDialog.init();
}

void DIALOG_UPGRADE::update(){
	StringDialog.update();
}

void DIALOG_UPGRADE::draw(SHADER* shader) {
	StringDialog.draw(shader);
	StringDialog.drawLineStringCentered(shader, String1, String1Pos);
	StringDialog.drawLineStringCentered(shader, String2Temp, String2Pos);
}

void DIALOG_UPGRADE::setSkillPoint(int skillPointCost){
	if (skillPointCost == -1) {
		sprintf(String2Temp, "%sMAX", String2);
	}
	else {
		SkillPointCost = skillPointCost;
		sprintf(String2Temp, "%s%d", String2, SkillPointCost);
	}
}
