#pragma once
#include "../Library/STATIC_FONT.h"
class CONTAINER;
class VARIANT_SHADER;
class IMAGE_3D;
class IMAGE_2D;
class SAVE;
class UPGRADE;
class SETTING;
//ステート間での共通データ
class GAME_DATA_COMMON{
public:
	GAME_DATA_COMMON();
	~GAME_DATA_COMMON();
	void create();
	CONTAINER* container() { return Container; }
	VARIANT_SHADER* valiantShader() { return ValiantShader; }
	IMAGE_3D* image3dShader() { return Image3dShader; }
	IMAGE_2D* image2dShader() { return Image2dShader; }
	SAVE* save() { return Save; }
	UPGRADE* upgrade() { return Upgrade; }
	SETTING* setting() { return Setting; }
	STATIC_FONT* font() { return Font; }
private:
	CONTAINER* Container = nullptr;
	VARIANT_SHADER* ValiantShader = nullptr;
	IMAGE_3D* Image3dShader = nullptr;
	IMAGE_2D* Image2dShader = nullptr;
	SAVE* Save = nullptr;
	UPGRADE* Upgrade = nullptr;
	SETTING* Setting = nullptr;
	STATIC_FONT* Font = nullptr;
};

