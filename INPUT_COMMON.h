#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/SINGLETON.h"
class INDEV;
class INPUT_COMMON:public SINGLETON<INPUT_COMMON>{
public:
	INPUT_COMMON();
	~INPUT_COMMON();
	void getState();
	void resetState();
	void MouseAimOn();
	void MouseAimOff();
	float aimAxisHorizontal()const;
	float aimAxisVertical()const;
	bool isNoneAimAxis()const;
	float moveAxisHorizontal()const;
	float moveAxisVertical()const;
	bool isNoneMoveAxis()const;
	bool isTriggerAvoid()const;
	bool isTriggerShot()const;
	bool isTriggerMelle()const;
	bool isTriggerSkill()const;
	bool isTriggerSkillChange()const;
	bool isTriggerSkillNextChange()const;
	bool isTriggerSkillBackChange()const;
	bool isTriggerEnter()const;
	bool isTriggerCancel()const;
	bool isTriggerUp()const;
	bool isTriggerDown()const;
	bool isTriggerRight()const;
	bool isTriggerLeft()const;
	bool isTriggerMenuRight()const;
	bool isTriggerMenuLeft()const;
	bool isTriggerOption()const;
	bool isTriggerSaveDelete()const;
	bool isTriggerStorySkip()const;
private:
	bool IsMouseAim = false;
	INDEV* In = nullptr;
	VECTOR2 MouseBefore;
};

