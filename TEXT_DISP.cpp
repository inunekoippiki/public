#pragma warning (disable:4996)
#include "../Library/common.h"
#include "../Library/STATIC_FONT.h"
#include "TEXT_DISP.h"
TEXT_DISP::TEXT_DISP(STATIC_FONT* staticFont) :
	StaticFont(staticFont) {
}

TEXT_DISP::~TEXT_DISP(){
	SAFE_DELETE_ARRAY(ColorIdx);
}

void TEXT_DISP::update() {
	if (Ins < CharCnt) {
		if (++Timer % max(Interval, 1) == 0) {
			Ins++;
		}
	}
	else {
		End = true;
	}
}

void TEXT_DISP::draw(SHADER* shader){
	if (IsCentered) {
		StaticFont->draw(shader, FileBuffer.buffer(),Ins, Pos, VECTOR2(FontSize, FontSize), Color, ColorIdx, STATIC_FONT::CENTERED());
	}
	else {
		StaticFont->draw(shader, FileBuffer.buffer(), Ins, Pos, VECTOR2(FontSize, FontSize), Color, ColorIdx);
	}
}

//�������Ƃɐݒ肳�ꂽ�J���[�f�[�^��ǂݍ���
void TEXT_DISP::create(const char* fileName) {
	FileBuffer = fileName;
	FileBuffer.restart();
	const char* character = "";
	CharCnt = 1;
	//���������J�E���g����
	while (character = FileBuffer.readChar()) {
		if (*character != '\n') {
			CharCnt++;
		}
	}
	//�f�t�H���g�J���[���X�g��ݒ�
	ColorIdx = new unsigned char[CharCnt];
	for (int i = 0;i < CharCnt;i++) {
		ColorIdx[i] = 0;
	}
	Color.push_back(COLOR());//�f�t�H���g�J���[

	//�Z�Z.txt��C�����āZ�ZC.txt�ɂ���Ƃ���
	int len = (int)strlen(fileName);
	char* str;
	str = new char[len + 2];
	strcpy(str, fileName);
	for (int i = 0;i < 5;i++) {
		str[len + 1 - i] = str[len - i];
	}
	str[len - 4] = 'C';
	//�J���[�f�[�^�e�L�X�g�ǂݍ���
	FILE* fp = fopen(str, "r");
	SAFE_DELETE_ARRAY(str);
	if (fp!=nullptr) {
		int i;
		fscanf(fp, "%d", &i);
		for (;i > 0;i--) {
			COLOR color;
			fscanf(fp, "%f %f %f %f", &color.r, &color.g, &color.b, &color.a);
			Color.push_back(color);
		}
		fscanf(fp, "%d", &i);
		for (;i > 0;i--) {
			int colorIdx = 0;
			int idx = 0;
			fscanf(fp, "%d %d", &colorIdx, &idx);
			ColorIdx[idx] = colorIdx;
		}
		fclose(fp);
	}
	FileBuffer.restart();

}

void TEXT_DISP::allDisp(){
	Ins = CharCnt;
	End = true;
}

void TEXT_DISP::setColor(const COLOR& color){
	//�z��0�Ԗڂ̓f�t�H���g�J���[
	Color[0] = color;
}

void TEXT_DISP::setPos(const VECTOR2& pos){
	Pos = pos;
}
