#pragma once
#include "../Library/STATIC_FONT.h"
#include "DIALOG.h"
//������\������@�\������_�C�����O
class STRING_DIALOG{
public:
	STRING_DIALOG();
	~STRING_DIALOG();
	void create(CONTAINER* c, STATIC_FONT* font);
	//yes�������ꂽ�ۂ̃R�[���o�b�N�֐���ݒ肷��
	template<class T>
	void setYesFunc(const T& yesFunc) { Dialog.setYesFunc(yesFunc); };
	//no�������ꂽ�ۂ̃R�[���o�b�N�֐���ݒ肷��
	template<class T>
	void setNoFunc(const T& noFunc) { Dialog.setNoFunc(noFunc); };
	//cancel�������ꂽ�ۂ̃R�[���o�b�N�֐���ݒ肷��
	template<class T>
	void setCancelFunc(const T& cancelFunc) { Dialog.setCancelFunc(cancelFunc); };
	//�t�H���g�̐F��ݒ肷��
	void setFontColor(const COLOR& fontColor) { FontColor = fontColor; }
	//�����̐F��ݒ肷��
	void setLineColor(const COLOR& lineColor) { LineColor = lineColor; }
	//�t�H���g�̃T�C�Y��ݒ肷��
	void setFontSize(int fontSize);
	void init();
	void update();
	void draw(SHADER* shader);
	//�����t��������`�悷��
	void drawLineString(SHADER* shader, const char* s, const VECTOR2& pos);
	void drawLineStringCentered(SHADER* shader, const char* s, const VECTOR2& pos);

private:
	//������`�悷��
	void drawLine(SHADER* shader, const char* s, const VECTOR2& pos);
	void drawLineCentered(SHADER* shader, const char* s, const VECTOR2& pos);

	STATIC_FONT* Font = nullptr;
	int FontSize = 0;
	COLOR FontColor;
	COLOR LineColor;
	DIALOG Dialog;
	TEXTURE* LineTexture = nullptr;
public:	
	//��ʂ̒����ɒ��������ŕ�����\�����邽�߂̈ʒu��Ԃ�
	static float fontCenteredX(const char* s, int fontSize);

};

