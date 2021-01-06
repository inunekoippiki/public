#pragma once
#include <string>
class UPGRADE;
class SAVE{
public:
	SAVE();
	~SAVE();
	void init();
	//�f�B���N�g�����[�h����B�Z�[�u�f�[�^��������true��Ԃ��܂�
	bool load(int saveDataId,UPGRADE* upgrade);
	//�f�B���N�g���ɕۑ�����
	void save(UPGRADE* upgrade);
	//���E���h���N���A����
	void clearRound(int round);
	//���̃��E���h���J������Ă��邩��Ԃ�
	bool isOpenRound(int round)const;
	//�Z�[�u�f�[�^��ǂݍ���ł��邩
	bool isLoadSaveData()const { return SaveDataId != 0; }
private:
	std::string FileName;

	time_t SaveTime = 0;
	time_t StartTime = 0;
	time_t PlayTime = 0;

	//1,2,3(0�͓ǂݍ���ł��Ȃ�)
	int SaveDataId = 0;
	//�X�g�[���[�i�s�x0,1,2
	int StoryState = 0;
};

