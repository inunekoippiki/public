#pragma warning (disable:4996)
#include <fstream>
#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "DATA_LIB.h"
#include "ENTITY_ENEMY.h"
#include "UPGRADE.h"
UPGRADE::UPGRADE() {
}

UPGRADE::~UPGRADE() {

}

void UPGRADE::create(CONTAINER* c){
	SkillPoint = 0;
	ConvertSkillPointCoefficient = c->data("ConvertSkillPointCoefficient");

	MaxHp.create(DATA_LIB::data<decltype(MaxHp)::arrayType>(c, "maxHp"));
	AttackDamageBoost.create(DATA_LIB::data<decltype(AttackDamageBoost)::arrayType>(c, "attackDamageBoost"));
	AttackRangeBoost.create(DATA_LIB::data<decltype(AttackRangeBoost)::arrayType>(c, "attackRangeBoost"));
	AttackSpeedBoost.create(DATA_LIB::data<decltype(AttackSpeedBoost)::arrayType>(c, "attackSpeedBoost"));
	MoveSpeedBoost.create(DATA_LIB::data<decltype(MoveSpeedBoost)::arrayType>(c, "moveSpeedBoost"));
	AttackDamageSkillBoost.create(DATA_LIB::data<decltype(AttackDamageSkillBoost)::arrayType>(c, "attackDamageSkillBoost"));
	MoveSpeedSkillBoost.create(DATA_LIB::data<decltype(MoveSpeedSkillBoost)::arrayType>(c, "moveSpeedSkillBoost"));
	HealPower.create(DATA_LIB::data<decltype(HealPower)::arrayType>(c, "healPower"));

	ENTITY_ENEMY::setUpgrade(this);
}

void UPGRADE::init(){
	GiveDamage = 0;
	SkillPoint = 0;
}

void UPGRADE::load(std::ifstream& ifs){
	ifs >> SkillPoint;
	MaxHp.load(ifs);
	AttackDamageBoost.load(ifs);
	AttackRangeBoost.load(ifs);
	AttackSpeedBoost.load(ifs);
	MoveSpeedBoost.load(ifs);
	AttackDamageSkillBoost.load(ifs);
	MoveSpeedSkillBoost.load(ifs);
	HealPower.load(ifs);
}

void UPGRADE::save(std::ofstream& ofs){
	ofs << SkillPoint << std::endl;
	MaxHp.save(ofs);
	AttackDamageBoost.save(ofs);
	AttackRangeBoost.save(ofs);
	AttackSpeedBoost.save(ofs);
	MoveSpeedBoost.save(ofs);
	AttackDamageSkillBoost.save(ofs);
	MoveSpeedSkillBoost.save(ofs);
	HealPower.save(ofs);

}

void UPGRADE::addGiveDamage(int damage){
	GiveDamage += damage;
}

void UPGRADE::convertSkillPoint(){
	SkillPoint += (int)(GiveDamage * ConvertSkillPointCoefficient);
	GiveDamage = 0;
}

bool UPGRADE::useSkillPoint(unsigned char skillLvl){
	int usePoint = skillPointCost(skillLvl);
	if (SkillPoint < usePoint) {
		return false;
	}
	SkillPoint -= usePoint;
	return true;
}
//必要スキルポイントは2のレベル+1乗
int UPGRADE::skillPointCost(int lv){
	int usePoint = 2;
	for (int i = 0;i < lv;i++) {
		usePoint *= 2;
	}
	return usePoint;
}

bool UPGRADE::enoughSkillPoint(int upgradeCost)const {
	return upgradeCost<=SkillPoint;
}

//レベルを上げようとする。スキルポイントが足りる場合消費しレベルを上げる
void UPGRADE::lvUp(IUPGRADE_LVL& upgradeLvl) {
	if (upgradeLvl.canUpgrade()) {
		if (useSkillPoint(upgradeLvl.lvl())) {
			upgradeLvl.lvlUp();
		}
	}
}
