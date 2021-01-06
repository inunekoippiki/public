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
	//�\���������Ō�܂Ői�߂�
	void allDisp();
	//�f�t�H���g�J���[��ݒ肷��
	void setColor(const COLOR& color);
	//�\����ʒu��ݒ肷��
	void setPos(const VECTOR2& pos);
	//�t�H���g�̃T�C�Y��ݒ肷��
	void setFontSize(int fontSize) { FontSize = fontSize; }
	//�\�����Ԃ̊Ԋu��ݒ肷��
	void setInterval(int interval) { Interval = interval; }
	//���������ŕ\�����邩��ݒ肷��
	void setIsCentered(bool isCentered) { IsCentered = isCentered; }
	//�������Ō�܂ŕ\������Ă��邩
	bool isEnd() { return End; }
protected:
	bool IsCentered = false;
	VECTOR2 Pos;
	FILE_BUFFER FileBuffer;
	//�e�L�X�g�̕�����
	int CharCnt = 0;
	int Timer = 0;
	int Interval = 0;
	//���ݕ\��������
	int Ins = 0;
	int FontSize = 0;
	bool End = false;
	STATIC_FONT* StaticFont = nullptr;
	//�������Ƃ̃J���[���X�g�ւ�idx
	unsigned char* ColorIdx = nullptr;
	//�g�p�J���[�p���b�g
	std::vector<COLOR> Color;

};