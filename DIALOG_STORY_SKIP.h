#pragma once
#include "../Library/STATIC_FONT.h"
#include "STRING_DIALOG.h"
#include "IDIALOG.h"
class DIALOG_STORY_SKIP :public IDIALOG {
public:
	DIALOG_STORY_SKIP();
	~DIALOG_STORY_SKIP();
	void create(CONTAINER* c, STATIC_FONT* font);
	void init()override;
	void update()override;
	void draw(SHADER* shader)override;
	STRING_DIALOG* stringDialog() { return &StringDialog; }
private:
	STRING_DIALOG StringDialog;
	char String[256] = { };
	VECTOR2 StringPos;
};

