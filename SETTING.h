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

	//�l�̊�����0~1�ŕԂ��܂�
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
	//�f�B���N�g������Z�[�u�f�[�^�����[�h
	void load(CONTAINER* c);
	//�f�B���N�g���ɃZ�[�u�f�[�^��ۑ�
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

