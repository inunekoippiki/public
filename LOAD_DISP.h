#pragma once
#include <array>
#include "../Library/TEXTURE.h"
#include "../Library/VECTOR2.h"
class GRAPHIC;
class CONTAINER;
class CONTAINER_LOAD_THREAD;
class IMAGE_2D;
//ÉçÅ[ÉhâÊñ ââèo
class LOAD_DISP{
public:
	LOAD_DISP();
	~LOAD_DISP();
	void create(CONTAINER* container, IMAGE_2D* shader);
	void startProc();
private:
	CONTAINER_LOAD_THREAD* ContainerLoadThread;
	IMAGE_2D* Shader = nullptr;
	GRAPHIC* G = nullptr;
	std::array<TEXTURE,4> Texture;
	COLOR Color;
	VECTOR2 Pos;

	int Sw = 0;
	float AnimSpeed = 0;
	float TempAnimPlay = 0.0f;
	int Frame = 0;
	bool LoopFlag = false;
};

