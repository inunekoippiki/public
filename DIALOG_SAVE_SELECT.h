#pragma once
#include "../Library/STATIC_FONT.h"
#include "STRING_DIALOG.h"
#include "IDIALOG.h"
class DIALOG_SAVE_SELECT :public IDIALOG {
public:
	DIALOG_SAVE_SELECT();
	~DIALOG_SAVE_SELECT();
	void create(CONTAINER* c, STATIC_FONT* font, bool IsEnmptyData);
	void init()override;
	void update()override;
	void draw(SHADER* shader)override;
	STRING_DIALOG* stringDialog() { return &StringDialog; }
private:
	STRING_DIALOG StringDialog;
	char String[256] = { 0 };
	VECTOR2 StringPos;
};

