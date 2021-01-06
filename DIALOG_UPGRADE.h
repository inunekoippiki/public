#pragma once
#include "../Library/STATIC_FONT.h"
#include "IDIALOG.h"
#include "STRING_DIALOG.h"
class DIALOG_UPGRADE :public IDIALOG{
public:
	DIALOG_UPGRADE();
	~DIALOG_UPGRADE();
	void create(CONTAINER* c, STATIC_FONT* font, int upgradeType, int skillPointCost);
	void init()override;
	void update()override;
	void draw(SHADER* shader)override;
	void setSkillPoint(int skillPointCost);//-1‚ÅMAX‚Æ•\Ž¦
	STRING_DIALOG* stringDialog() { return &StringDialog; }
private:
	STRING_DIALOG StringDialog;
	char String1[256] = { };
	VECTOR2 String1Pos;
	char String2[256] = { };
	VECTOR2 String2Pos;
	char String2Temp[256] = { };


	int SkillPointCost = 0;
};

