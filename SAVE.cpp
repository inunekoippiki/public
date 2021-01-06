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
	PlayTime = 54000;//�X���Ԃ̃Y��������
	StoryState = 0;
}

bool SAVE::load(int saveDataId,UPGRADE* upgrade){
	//�Z�[�u�ԍ���.txt������Ƃ���
	FileName = "Assets/saveData/save" + std::to_string(saveDataId) + ".txt";
	std::ifstream ifs;
	ifs.open(FileName);
	if (!ifs.is_open()) {//�t�@�C�����Ȃ�
		upgrade->init();
		init();
		return true;
	}
	//�Z�[�u�f�[�^��ǂݍ��񂾎������Q�[���J�n����
	StartTime = time(NULL);
	//���Ԃ����[�h
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
	//�Z�[�u���Ԃ��L�^
	time_t now = time(NULL);
	tm* pnow = localtime(&now);
	ofs << now << std::endl;
	//�v���C���Ԃ̉��Z
	PlayTime += (size_t)difftime(now, StartTime);
	StartTime = now;
	//�v���C���Ԃ��L�^
	ofs << PlayTime << std::endl;
	//�X�g�[���[�i�s�x���L�^
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
