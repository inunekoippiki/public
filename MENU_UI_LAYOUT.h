#pragma once
class SHADER;
class MENU_UI_LAYOUT{
public:
	MENU_UI_LAYOUT();
	virtual ~MENU_UI_LAYOUT() ;
	virtual void init() = 0;//Ø‚è‘Ö‚¦‚Å‚±‚Ì‰æ–Ê‚ªo‚½‚Æ‚«ŒÄ‚Î‚ê‚é‰Šú‰»
	virtual void update() = 0;
	virtual void draw(SHADER* shader) = 0;
};
