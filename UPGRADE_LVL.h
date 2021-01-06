#pragma once
#include <Windows.h>
#include <fstream>
#include <array>
//UPGRADE_LVL�̃C���^�[�t�F�[�X
class IUPGRADE_LVL {
public:
	virtual ~IUPGRADE_LVL() {};
	virtual void load(std::ifstream& ifs) = 0;
	virtual void save(std::ofstream& ofs) = 0;
	virtual bool canUpgrade()const = 0;
	virtual int lvl() const = 0;
	virtual void lvlUp() = 0;
};

//���x���Ƃ���ɑΉ������l���i�[�ł���N���X
//�{���ȂǕ�������������΁A�̗͂Ȃǐ���������̂Ńe���v���[�g
template<class dataType,size_t maxlvl>
class UPGRADE_LVL :public IUPGRADE_LVL{
public:
	using arrayType = std::array < dataType, maxlvl>;
	UPGRADE_LVL() {

	};
	~UPGRADE_LVL() {

	};
	void create(arrayType&& lvlValue) {
		LvlValue = lvlValue;
	}
	void load(std::ifstream& ifs)override {
		ifs >> Lvl;
	}
	void save(std::ofstream& ofs) override {
		ofs << Lvl << std::endl;
	}
	//�A�b�v�O���[�h�ł��邩
	bool canUpgrade()const override {
		//���x�����グ���Ƃ��ɏ���𒴂��Ȃ���
		return (Lvl+1 <= maxlvl-1);
	}
	//���݂̃��x��
	int lvl() const override {
		return Lvl;
	}
	//���x���A�b�v������
	void lvlUp() override {
		Lvl = min(Lvl + 1, maxlvl-1);
	}
	//���x���ɑ΂���l
	dataType lvlValue()const {
		return LvlValue[Lvl];
	}
private:
	int Lvl = 0;
	arrayType LvlValue;
};