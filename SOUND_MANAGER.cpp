#include "../Library/SOUND.h"
#include "../Library/DEBUG_STR.h"
#include "SETTING.h"
#include "SOUND_MANAGER.h"
SOUND_MANAGER::SOUND_MANAGER() {
	MasterVolume = 1000;
	FadeSpped = 0.01f;
	setMasterVolume(1.0f);
	setSEVolume(1.0f);
	setBGMVolume(1.0f);
	NowBgmVolume = 1.0f;
	Attenuation = 0.01f;
}

SOUND_MANAGER::~SOUND_MANAGER() {
}

void SOUND_MANAGER::update(){
	//次のBGMが入るとフェードして次に置き換える
	if (NewBgm != nullptr) {
		NewBgmVolume += FadeSpped * 2.0f;
		NowBgmVolume -= FadeSpped;
		NewBgm->setVolume(cvt(BGMVolume * NewBgmVolume));
		if (NowBgm != nullptr) {
			NowBgm->setVolume(cvt(BGMVolume * NowBgmVolume));
		}
		if (NowBgmVolume < 0.5f) {//フェードし終わると前のは止めて、Nowに移してNewはNULLに
			if (NowBgm != nullptr) {
				NowBgm->stop();
			}
			NowBgm = NewBgm;
			NewBgm = nullptr;
			NewBgmVolume = 0.0f;
			NowBgmVolume = 1.0f;
		}
	}
	if (IsBgmStop) {
		NewBgmVolume += FadeSpped * 2.0f;
		NowBgmVolume -= FadeSpped;
		if (NowBgm != nullptr) {
			NowBgm->setVolume(cvt(BGMVolume * NowBgmVolume));
		}
		if (NowBgmVolume < 0.5f) {//フェードし終わると前のは止めて、Nowに移してNewはNULLに。Newの方は2倍足してるのでNowが0.5でフェード完了
			if (NowBgm != nullptr) {
				NowBgm->stop();
			}
			NowBgm = nullptr;
			NewBgmVolume = 0.0f;
			NowBgmVolume = 1.0f;
			IsBgmStop = false;
		}

	}
}

void SOUND_MANAGER::stopSound(SOUND* sound){
	sound->stop();
}

void SOUND_MANAGER::playSound(SOUND* sound){
	sound->setVolume(_SEVolume);
	sound->play();
}

void SOUND_MANAGER::playSound(SOUND* sound, const VECTOR3& pos){
	sound->setVolume(cvt(unCvt(_SEVolume) / (1.0f + length(ListenerPos - pos)* Attenuation)));
	sound->play();
}

void SOUND_MANAGER::playSoundLoop(SOUND* sound){
	sound->setVolume(_SEVolume);
	sound->playLoop();
}

void SOUND_MANAGER::playSoundLoop(SOUND* sound, const VECTOR3& pos){
	sound->setVolume(cvt(unCvt(_SEVolume) / (1.0f + length(ListenerPos - pos)* Attenuation)));
	sound->playLoop();
}

long SOUND_MANAGER::cvt(float val){
	return (long)(val*10000)-10000L;
}

float SOUND_MANAGER::unCvt(long val){
	return (val+10000L)/10000.0f;
}

void SOUND_MANAGER::setMasterVolume(float volume) { 
	MasterVolume = volume; 
	_MasterVolume = cvt(MasterVolume);
	_SEVolume = cvt(MasterVolume * SEVolume);
	_BGMVolume = cvt(MasterVolume * BGMVolume);
	if (NewBgm != nullptr) {
		NewBgm->setVolume(_BGMVolume);
	}

}

void SOUND_MANAGER::setSEVolume(float volume){
	_SEVolume = cvt(MasterVolume * volume);
	SEVolume = unCvt(_SEVolume);
}

void SOUND_MANAGER::setBGMVolume(float volume){
	_BGMVolume = cvt(MasterVolume * volume);
	BGMVolume = unCvt(_BGMVolume);
	if (NewBgm != nullptr) {
		NewBgm->setVolume(_BGMVolume);
	}
}

void SOUND_MANAGER::stopBgm(){
	IsBgmStop = true;
}

void SOUND_MANAGER::setNextBgm(SOUND* sound){
	IsBgmStop = false;
	if(NewBgm==nullptr){	//フェード中でなければただNewに入れる
		if (NowBgm == sound) {//いまのと同じBGMだとスルー
			return;
		}
		NewBgm = sound;
		NewBgmVolume = 0.0f;
		NowBgmVolume = 1.0f;
		NewBgm->setVolume(-10000);
		NewBgm->playLoop();
	}
	else{	//フェード中に次のBGMが入ってきた場合
		if (NewBgm == sound) {
			return;
		}
		if (NowBgm == sound) {
			NewBgm->stop();
			NewBgmVolume = 0.0f;
			NowBgmVolume = 1.0f;
			NowBgm->setVolume(_BGMVolume);
			NewBgm = nullptr;
			return;
		}
		NewBgm->stop();
		NewBgm = sound;
		NewBgmVolume = 0.0f;
		NowBgmVolume = 1.0f;
		NewBgm->setVolume(-10000);
		NewBgm->playLoop();
	}

}

void SOUND_MANAGER::load(SETTING* setting){
	setMasterVolume(setting->volume()->value() /100.0f);
	setSEVolume(setting->soundVolume()->value() / 100.0f);
	setBGMVolume(setting->bgmVolume()->value() / 100.0f);
	if (NowBgm != nullptr) {
		NowBgm->setVolume(_BGMVolume);
	}
	if (NewBgm != nullptr) {
		NowBgm->setVolume(_BGMVolume);
	}
}

void SOUND_MANAGER::debug() {
	DEBUG_STR* ds = DEBUG_STR::instance();
	ds->set("%d", MasterVolume);
}
