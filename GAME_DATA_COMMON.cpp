#include "../Library/common.h"
#include "../Library/VARIANT_SHADER.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/IMAGE_3D.h"
#include "../Library/CONTAINER.h"
#include "createAssets.h"
#include "LOAD_DISP.h"
#include "SAVE.h"
#include "UPGRADE.h"
#include "SETTING.h"
#include "FADE.h"
#include "ENTITY.h"
#include "GAME_DATA_COMMON.h"
GAME_DATA_COMMON::GAME_DATA_COMMON() {
}

GAME_DATA_COMMON::~GAME_DATA_COMMON() {
	SAFE_DELETE(Font);
	SAFE_DELETE(Container);
	SAFE_DELETE(ValiantShader);
	SAFE_DELETE(Image3dShader);
	SAFE_DELETE(Image2dShader);
	SAFE_DELETE(Save);
	SAFE_DELETE(Upgrade);
	SAFE_DELETE(Setting);
}

void GAME_DATA_COMMON::create(){
	//全ステート共通使用の「データ、または、オブジェクト」準備---------------------------
	// Shader
	ValiantShader = new VARIANT_SHADER(2048, 2048);
	Image3dShader = new IMAGE_3D();
	Image2dShader = new IMAGE_2D();
	//コンテナの読み込み
	createAssets();//Release版でこの処理はスキップされる
	Container = new CONTAINER(CONTAINER::LOAD_FROM_FILE_THREAD, "Assets/Assets.txt");
	LOAD_DISP* loadDisp = new LOAD_DISP();
	loadDisp->create(Container, Image2dShader);
	loadDisp->startProc();
	delete loadDisp;
	Save = new SAVE();
	Upgrade = new UPGRADE();
	Upgrade->create(Container);
	Setting = new SETTING(Container);
	Setting->load(Container);
	Font = new STATIC_FONT(64, "Assets/font/PixelMplus12-Regular.ttf", "PixelMplus12");
	ENTITY::setGameDataCommon(this);
}
