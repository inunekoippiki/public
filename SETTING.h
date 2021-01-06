#pragma once
class CONTAINER;
class SETTING_VALUE {
public:
	SETTING_VALUE();
	~SETTING_VALUE();
	void init(int maxValue, int minValue, int changeAmount);
	int value()const;
	void set(int value);
	void upValue();
	void downValue();

	//値の割合を0~1で返します
	float percentage()const;
private:
	int Value = 0;
	int MaxValue = 0;
	int MinValue = 0;
	int ChangeAmount = 0;
};

class SETTING {
public:
	SETTING(CONTAINER* c);
	~SETTING();
	//ディレクトリからセーブデータをロード
	void load(CONTAINER* c);
	//ディレクトリにセーブデータを保存
	void save()const;
	SETTING_VALUE* volume() { return &Volume; }
	SETTING_VALUE* soundVolume() { return &SoundVolume; }
	SETTING_VALUE* bgmVolume() { return &BgmVolume; }
	SETTING_VALUE* aimSensitivity() { return &AimSensitivity; }
private:
	SETTING_VALUE Volume;
	SETTING_VALUE SoundVolume;
	SETTING_VALUE BgmVolume;
	SETTING_VALUE AimSensitivity;
};

