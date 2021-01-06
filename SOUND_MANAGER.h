#pragma once
#include "../Library/VECTOR3.h"
#include "../Library/SINGLETON.h"
class SETTING;
class SOUND;
class SOUND_MANAGER:public SINGLETON<SOUND_MANAGER>{
public:
	SOUND_MANAGER();
	~SOUND_MANAGER();
	//BGMフェードを使うならば毎フレーム呼ばなければならない
	void update();
	//音を止める
	void stopSound(SOUND* sound);
	//SEを鳴らす
	void playSound(SOUND* sound);
	//SEを鳴らす（距離減衰有り）
	void playSound(SOUND* sound,const VECTOR3& pos);
	//SEを鳴らす（ループあり）
	void playSoundLoop(SOUND* sound);
	//SEを鳴らす（ループあり）（距離減衰有り）
	void playSoundLoop(SOUND* sound, const VECTOR3& pos);
	//音量の0~1を-10000~0に変換
	long cvt(float val);
	//音量の-10000~0を0~1に変換
	float unCvt(long val);
	//マスターボリュームを設定(0~1)
	void setMasterVolume(float volume);
	//SEボリュームを設定(0~1)
	void setSEVolume(float volume);
	//BGMボリュームを設定(0~1)
	void setBGMVolume(float volume);
	//BGMを止める（非推奨）
	void stopBgm();
	//BGM変更する。クロスフェードする
	void setNextBgm(SOUND* sound);
	//リスナーの位置を設定
	void setListenerPos(const VECTOR3& listenerPos) { ListenerPos = listenerPos; }
	//セッティングから音量を読み込む
	void load(SETTING* setting);

	void debug();
private:
	//リスナーの位置
	VECTOR3 ListenerPos;
	//距離による減衰率
	float Attenuation = 0.0f;
	//0min 1max
	float MasterVolume = 0;
	float SEVolume = 0;
	float BGMVolume = 0;
	//内部で使う計算済み値-10000min 0max
	long _MasterVolume = 0;
	long _SEVolume = 0;
	long _BGMVolume = 0;
	//フェード関連
	float FadeSpped = 0.0f;
	SOUND* NewBgm = nullptr;
	float NewBgmVolume = 0;
	SOUND* NowBgm = nullptr;
	float NowBgmVolume = 0;
	
	bool IsBgmStop = false;
};

