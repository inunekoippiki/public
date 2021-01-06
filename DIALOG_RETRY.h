#pragma once
#include "DIALOG.h"
#include "IDIALOG.h"
class DIALOG_RETRY :public IDIALOG {
public:
	DIALOG_RETRY();
	~DIALOG_RETRY();
	void create(CONTAINER* c);
	void init()override;
	void update()override;
	void draw(SHADER* shader)override;
	DIALOG* dialog() { return &Dialog; }
private:
	DIALOG Dialog;
};

