#pragma warning (disable:4996)
#include <fstream>
#include <algorithm>
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "SETTING.h"
SETTING::SETTING(CONTAINER* c) {
	Volume.init(
		c->data("SETTING::VolumeChangeMax"),
		c->data("SETTING::VolumeChangeMin"),
		c->data("SETTING::VolumeChangeAmount")
	);
	SoundVolume.init(
		c->data("SETTING::SoundVolumeChangeMax"),
		c->data("SETTING::SoundVolumeChangeMin"),
		c->data("SETTING::SoundVolumeChangeAmount")
	);	
	BgmVolume.init(
		c->data("SETTING::BgmVolumeChangeMax"),
		c->data("SETTING::BgmVolumeChangeMin"),
		c->data("SETTING::BgmVolumeChangeAmount")
	);	
	AimSensitivity.init(
		c->data("SETTING::AimSensitivityChangeMax"),
		c->data("SETTING::AimSensitivityChangeMin"),
		c->data("SETTING::AimSensitivityChangeAmount")
	);
}

SETTING::~SETTING() {
}

void SETTING::load(CONTAINER* c){
	std::ifstream ifs("Assets/saveData/setting.txt");
	if (ifs.is_open()) {
		int buffer = 0;
		ifs >> buffer;
		Volume.set(buffer);
		ifs >> buffer;
		SoundVolume.set(buffer);
		ifs >> buffer;
		BgmVolume.set(buffer);
		ifs >> buffer;
		AimSensitivity.set(buffer);
		ifs.close();
	}
	else{
		//ファイルが見つからなかったらデフォルト値
		Volume.set(c->data("SETTING::DefaultVolume"));
		SoundVolume.set(c->data("SETTING::DefaultSoundVolume"));
		BgmVolume.set(c->data("SETTING::DefaultBgmVolume"));
		AimSensitivity.set(c->data("SETTING::DefaultAimSensitivity"));
	}
}

void SETTING::save()const {
	std::ofstream ofs("Assets/saveData/setting.txt");
	ofs << Volume.value() << std::endl;
	ofs << SoundVolume.value() << std::endl;
	ofs << BgmVolume.value() << std::endl;
	ofs << AimSensitivity.value() << std::endl;
	ofs.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SETTING_VALUE::SETTING_VALUE() {
}

SETTING_VALUE::~SETTING_VALUE(){
}

void SETTING_VALUE::init(int maxValue, int minValue, int changeAmount){
	MaxValue = maxValue;
	MinValue = minValue;
	ChangeAmount = changeAmount;
}

int SETTING_VALUE::value()const{
	return Value;
}

void SETTING_VALUE::set(int value){
	Value = std::min(std::max(value, MinValue), MaxValue);
}

void SETTING_VALUE::upValue() {
	set(value() + ChangeAmount);
}

void SETTING_VALUE::downValue() {
	set(value() - ChangeAmount);
}

float SETTING_VALUE::percentage()const {
	int difference = MaxValue - MinValue;
	return (float)(Value - MinValue) / difference;
}
