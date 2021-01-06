#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include "../Library/common.h"
#include "SAVE.h"
#include "UPGRADE.h"
SAVE::SAVE() {
	init();
}

SAVE::~SAVE() {
}

void SAVE::init(){
	StartTime = time(NULL);
	SaveTime = time(NULL);
	PlayTime = 54000;//９時間のズレを治す
	StoryState = 0;
}

bool SAVE::load(int saveDataId,UPGRADE* upgrade){
	//セーブ番号と.txtをつけるところ
	FileName = "Assets/saveData/save" + std::to_string(saveDataId) + ".txt";
	std::ifstream ifs;
	ifs.open(FileName);
	if (!ifs.is_open()) {//ファイルがない
		upgrade->init();
		init();
		return true;
	}
	//セーブデータを読み込んだ時刻＝ゲーム開始時刻
	StartTime = time(NULL);
	//時間をロード
	ifs >> SaveTime;
	ifs >> PlayTime;
	ifs >> StoryState;
	upgrade->load(ifs);
	ifs.close();
	return false;
}

void SAVE::save(UPGRADE* upgrade){
	std::ofstream ofs;
	ofs.open(FileName);
	//セーブ時間を記録
	time_t now = time(NULL);
	tm* pnow = localtime(&now);
	ofs << now << std::endl;
	//プレイ時間の加算
	PlayTime += (size_t)difftime(now, StartTime);
	StartTime = now;
	//プレイ時間を記録
	ofs << PlayTime << std::endl;
	//ストーリー進行度を記録
	ofs << StoryState << std::endl;
	upgrade->save(ofs);
	ofs.close();
}

void SAVE::clearRound(int round){
	if (StoryState <= round) {
		StoryState = round + 1;
	}
}

bool SAVE::isOpenRound(int round)const {
	return StoryState >= round;
}
