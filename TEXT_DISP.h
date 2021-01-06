#pragma once
#include <string>
#include <vector>
#include "../Library/VECTOR2.h"
#include "../Library/FILE_BUFFER.h"
#include "../Library/COLOR.h"
class SHADER;
class STATIC_FONT;
class TEXT_DISP{
public:
	TEXT_DISP(STATIC_FONT* staticFont);
	~TEXT_DISP();
	void create(const char* fileName);
	void update();
	void draw(SHADER* shader);
	//表示文字を最後まで進める
	void allDisp();
	//デフォルトカラーを設定する
	void setColor(const COLOR& color);
	//表示基準位置を設定する
	void setPos(const VECTOR2& pos);
	//フォントのサイズを設定する
	void setFontSize(int fontSize) { FontSize = fontSize; }
	//表示時間の間隔を設定する
	void setInterval(int interval) { Interval = interval; }
	//中央揃えで表示するかを設定する
	void setIsCentered(bool isCentered) { IsCentered = isCentered; }
	//文字が最後まで表示されているか
	bool isEnd() { return End; }
protected:
	bool IsCentered = false;
	VECTOR2 Pos;
	FILE_BUFFER FileBuffer;
	//テキストの文字数
	int CharCnt = 0;
	int Timer = 0;
	int Interval = 0;
	//現在表示文字数
	int Ins = 0;
	int FontSize = 0;
	bool End = false;
	STATIC_FONT* StaticFont = nullptr;
	//文字ごとのカラーリストへのidx
	unsigned char* ColorIdx = nullptr;
	//使用カラーパレット
	std::vector<COLOR> Color;

};