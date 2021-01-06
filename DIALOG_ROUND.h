#pragma once
#include "../Library/STATIC_FONT.h"
#include "STRING_DIALOG.h"
#include "IDIALOG.h"
class DIALOG_ROUND :public IDIALOG {
public:
	DIALOG_ROUND();
	~DIALOG_ROUND();
	void create(CONTAINER* c, STATIC_FONT* font, int round);
	void init()override;
	void update()override;
	void draw(SHADER* shader)override;
	STRING_DIALOG* stringDialog() { return &StringDialog; }
private:
	STRING_DIALOG StringDialog;
	char String[256] = {};
	VECTOR2 StringPos;
};

