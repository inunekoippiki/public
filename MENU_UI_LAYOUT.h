#pragma once
class SHADER;
class MENU_UI_LAYOUT{
public:
	MENU_UI_LAYOUT();
	virtual ~MENU_UI_LAYOUT() ;
	virtual void init() = 0;//�؂�ւ��ł��̉�ʂ��o���Ƃ��Ă΂�鏉����
	virtual void update() = 0;
	virtual void draw(SHADER* shader) = 0;
};
