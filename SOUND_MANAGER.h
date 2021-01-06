#pragma once
#include "../Library/VECTOR3.h"
#include "../Library/SINGLETON.h"
class SETTING;
class SOUND;
class SOUND_MANAGER:public SINGLETON<SOUND_MANAGER>{
public:
	SOUND_MANAGER();
	~SOUND_MANAGER();
	//BGM�t�F�[�h���g���Ȃ�Ζ��t���[���Ă΂Ȃ���΂Ȃ�Ȃ�
	void update();
	//�����~�߂�
	void stopSound(SOUND* sound);
	//SE��炷
	void playSound(SOUND* sound);
	//SE��炷�i���������L��j
	void playSound(SOUND* sound,const VECTOR3& pos);
	//SE��炷�i���[�v����j
	void playSoundLoop(SOUND* sound);
	//SE��炷�i���[�v����j�i���������L��j
	void playSoundLoop(SOUND* sound, const VECTOR3& pos);
	//���ʂ�0~1��-10000~0�ɕϊ�
	long cvt(float val);
	//���ʂ�-10000~0��0~1�ɕϊ�
	float unCvt(long val);
	//�}�X�^�[�{�����[����ݒ�(0~1)
	void setMasterVolume(float volume);
	//SE�{�����[����ݒ�(0~1)
	void setSEVolume(float volume);
	//BGM�{�����[����ݒ�(0~1)
	void setBGMVolume(float volume);
	//BGM���~�߂�i�񐄏��j
	void stopBgm();
	//BGM�ύX����B�N���X�t�F�[�h����
	void setNextBgm(SOUND* sound);
	//���X�i�[�̈ʒu��ݒ�
	void setListenerPos(const VECTOR3& listenerPos) { ListenerPos = listenerPos; }
	//�Z�b�e�B���O���特�ʂ�ǂݍ���
	void load(SETTING* setting);

	void debug();
private:
	//���X�i�[�̈ʒu
	VECTOR3 ListenerPos;
	//�����ɂ�錸����
	float Attenuation = 0.0f;
	//0min 1max
	float MasterVolume = 0;
	float SEVolume = 0;
	float BGMVolume = 0;
	//�����Ŏg���v�Z�ςݒl-10000min 0max
	long _MasterVolume = 0;
	long _SEVolume = 0;
	long _BGMVolume = 0;
	//�t�F�[�h�֘A
	float FadeSpped = 0.0f;
	SOUND* NewBgm = nullptr;
	float NewBgmVolume = 0;
	SOUND* NowBgm = nullptr;
	float NowBgmVolume = 0;
	
	bool IsBgmStop = false;
};

