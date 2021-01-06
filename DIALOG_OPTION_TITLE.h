#pragma once
#include "../Library/STATIC_FONT.h"
#include "STRING_DIALOG.h"
#include "IDIALOG.h"
class DIALOG_OPTION_TITLE :public IDIALOG {
public:
	DIALOG_OPTION_TITLE();
	~DIALOG_OPTION_TITLE();
	void create(CONTAINER* c, STATIC_FONT* font);
	void init()override;
	void update()override;
	void draw(SHADER* shader);
	STRING_DIALOG* stringDialog() { return &StringDialog; }
private:
	STRING_DIALOG StringDialog;
	char String[256] = {};
	VECTOR2 StringPos;
};

