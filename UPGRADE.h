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
	//�Z�[�u�f�[�^�ǂݍ���
	void load(std::ifstream& ifs);
	//�Z�[�u�f�[�^��������
	void save(std::ofstream& ofs);
	//�G�ɗ^�����_���[�W
	void addGiveDamage(int damage);
	//�^�����_���[�W���X�L���|�C���g�ɕϊ�
	void convertSkillPoint();
	//���݂̃X�L���|�C���g
	int skillPoint() const { return SkillPoint; };
	//�X�L���|�C���g������(����Ȃ���false��Ԃ�)
	bool useSkillPoint(unsigned char skillLvl);
	//����X�L���|�C���g
	int skillPointCost(int lv);
	//�X�L���|�C���g������邩
	bool enoughSkillPoint(int upgradeCost)const;

	//���x�����グ�悤�Ƃ���B�X�L���|�C���g�������ꍇ������x�����グ��
	void lvUp(IUPGRADE_LVL& upgradeLvl);

	//�e���x���I�u�W�F�N�g
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
	//�擾�X�L���|�C���g�̒����p
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

