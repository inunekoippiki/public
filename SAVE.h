#pragma once
#include <string>
class UPGRADE;
class SAVE{
public:
	SAVE();
	~SAVE();
	void init();
	//ディレクトリロードする。セーブデータが無いとtrueを返します
	bool load(int saveDataId,UPGRADE* upgrade);
	//ディレクトリに保存する
	void save(UPGRADE* upgrade);
	//ラウンドをクリアした
	void clearRound(int round);
	//そのラウンドが開放されているかを返す
	bool isOpenRound(int round)const;
	//セーブデータを読み込んでいるか
	bool isLoadSaveData()const { return SaveDataId != 0; }
private:
	std::string FileName;

	time_t SaveTime = 0;
	time_t StartTime = 0;
	time_t PlayTime = 0;

	//1,2,3(0は読み込んでいない)
	int SaveDataId = 0;
	//ストーリー進行度0,1,2
	int StoryState = 0;
};

