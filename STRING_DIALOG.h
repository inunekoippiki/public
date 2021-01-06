#pragma once
#include "../Library/STATIC_FONT.h"
#include "DIALOG.h"
//文字を表示する機能があるダイヤログ
class STRING_DIALOG{
public:
	STRING_DIALOG();
	~STRING_DIALOG();
	void create(CONTAINER* c, STATIC_FONT* font);
	//yesが押された際のコールバック関数を設定する
	template<class T>
	void setYesFunc(const T& yesFunc) { Dialog.setYesFunc(yesFunc); };
	//noが押された際のコールバック関数を設定する
	template<class T>
	void setNoFunc(const T& noFunc) { Dialog.setNoFunc(noFunc); };
	//cancelが押された際のコールバック関数を設定する
	template<class T>
	void setCancelFunc(const T& cancelFunc) { Dialog.setCancelFunc(cancelFunc); };
	//フォントの色を設定する
	void setFontColor(const COLOR& fontColor) { FontColor = fontColor; }
	//下線の色を設定する
	void setLineColor(const COLOR& lineColor) { LineColor = lineColor; }
	//フォントのサイズを設定する
	void setFontSize(int fontSize);
	void init();
	void update();
	void draw(SHADER* shader);
	//下線付き文字を描画する
	void drawLineString(SHADER* shader, const char* s, const VECTOR2& pos);
	void drawLineStringCentered(SHADER* shader, const char* s, const VECTOR2& pos);

private:
	//下線を描画する
	void drawLine(SHADER* shader, const char* s, const VECTOR2& pos);
	void drawLineCentered(SHADER* shader, const char* s, const VECTOR2& pos);

	STATIC_FONT* Font = nullptr;
	int FontSize = 0;
	COLOR FontColor;
	COLOR LineColor;
	DIALOG Dialog;
	TEXTURE* LineTexture = nullptr;
public:	
	//画面の中央に中央揃えで文字を表示するための位置を返す
	static float fontCenteredX(const char* s, int fontSize);

};

