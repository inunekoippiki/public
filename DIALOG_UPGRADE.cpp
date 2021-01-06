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
		//�A�b�v�O���[�h���ڂ̕���
	const char* upgradeTypeString[8] = {
		"�̗̓X�e�[�^�X",
		"�U���̓X�e�[�^�X",
		"�U���͈̓X�e�[�^�X",
		"�U�����x�X�e�[�^�X",
		"�ړ����x�X�e�[�^�X",
		"�U���X�L��",
		"�ړ��X�L��",
		"�񕜃X�L��" };
	sprintf(String1, "%s���������܂����H", upgradeTypeString[upgradeType]);
	int i = 0;
	String1Pos.y = 430.0f;
	String1Pos.x = g->centerX();

	sprintf(String2, "����X�L���|�C���g:");
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
