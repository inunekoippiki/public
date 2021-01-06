#include "../Library/common.h"
#include "UI_DRAWER.h"
#include "UI_BASE.h"
UI_MANAGER* UI_BASE::UiManager = nullptr;
UI_BASE::UI_BASE() {
}

UI_BASE::~UI_BASE(){
	SAFE_DELETE(Drawer);
}
