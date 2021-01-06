#pragma once
#include <list>
#include "../Library/MATRIX.h"
#include "UI_BASE.h"
class UI_BASE;
class SHADER;
//UI��\������N���X�B
//priority��ݒ肷�邱�Ƃŕ`�揇��ݒ�ł���
class UI_MANAGER {
public:
	UI_MANAGER();
	~UI_MANAGER();
	//UI��ǉ�����
	void add(UI_BASE* ui, unsigned int priority);
	void draw(SHADER* shader);
	//3D��ɕ\�������UI�̂��߂̍s��
	MATRIX projView() { return ProjView; }
	//3D��ɕ\�������UI�̂��߂̍s���ݒ肷��
	void setProjView(const MATRIX& projView) { ProjView = projView; }
private:
	std::list < UI_BASE*> UiList;
	MATRIX ProjView;
};

