#pragma once
#include <Windows.h>
#include <fstream>
#include <array>
//UPGRADE_LVLのインターフェース
class IUPGRADE_LVL {
public:
	virtual ~IUPGRADE_LVL() {};
	virtual void load(std::ifstream& ifs) = 0;
	virtual void save(std::ofstream& ofs) = 0;
	virtual bool canUpgrade()const = 0;
	virtual int lvl() const = 0;
	virtual void lvlUp() = 0;
};

//レベルとそれに対応した値を格納できるクラス
//倍率など浮動小数があれば、体力など整数もあるのでテンプレート
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
	//アップグレードできるか
	bool canUpgrade()const override {
		//レベルを上げたときに上限を超えないか
		return (Lvl+1 <= maxlvl-1);
	}
	//現在のレベル
	int lvl() const override {
		return Lvl;
	}
	//レベルアップさせる
	void lvlUp() override {
		Lvl = min(Lvl + 1, maxlvl-1);
	}
	//レベルに対する値
	dataType lvlValue()const {
		return LvlValue[Lvl];
	}
private:
	int Lvl = 0;
	arrayType LvlValue;
};