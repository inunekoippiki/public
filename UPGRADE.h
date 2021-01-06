#pragma once
#include <array>
#include <stdio.h>
#include "UPGRADE_LVL.h"
class CONTAINER;

class UPGRADE{
public:
	UPGRADE();
	~UPGRADE();
	void create(CONTAINER* c);
	void init();
	//セーブデータ読み込み
	void load(std::ifstream& ifs);
	//セーブデータ書き込み
	void save(std::ofstream& ofs);
	//敵に与えたダメージ
	void addGiveDamage(int damage);
	//与えたダメージをスキルポイントに変換
	void convertSkillPoint();
	//現在のスキルポイント
	int skillPoint() const { return SkillPoint; };
	//スキルポイントを消費(足りないとfalseを返す)
	bool useSkillPoint(unsigned char skillLvl);
	//消費スキルポイント
	int skillPointCost(int lv);
	//スキルポイントが足りるか
	bool enoughSkillPoint(int upgradeCost)const;

	//レベルを上げようとする。スキルポイントが足りる場合消費しレベルを上げる
	void lvUp(IUPGRADE_LVL& upgradeLvl);

	//各レベルオブジェクト
	auto maxHp() { return &MaxHp; }
	auto attackDamageBoost() { return &AttackDamageBoost; }
	auto attackRangeBoost() { return &AttackRangeBoost; }
	auto attackSpeedBoost() { return &AttackSpeedBoost; }
	auto moveSpeedBoost() { return &MoveSpeedBoost; }
	auto attackDamageSkillBoost() { return &AttackDamageSkillBoost; }
	auto moveSpeedSkillBoost() { return &MoveSpeedSkillBoost; }
	auto healPower() { return &HealPower; }

private:

	int GiveDamage = 0;
	//取得スキルポイントの調整用
	float ConvertSkillPointCoefficient = 0.0f;
	int SkillPoint = 0;

	UPGRADE_LVL<int, 5> MaxHp;
	UPGRADE_LVL< float, 5> AttackDamageBoost;
	UPGRADE_LVL< float, 5> AttackRangeBoost;
	UPGRADE_LVL< float, 5> AttackSpeedBoost;
	UPGRADE_LVL< float, 5> MoveSpeedBoost;
	UPGRADE_LVL< float, 3> AttackDamageSkillBoost;
	UPGRADE_LVL< float, 3> MoveSpeedSkillBoost;
	UPGRADE_LVL<int, 3> HealPower;

};

