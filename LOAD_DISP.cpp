#include "../Library/common.h"
#include "../Library/Thread/THREAD.h"
#include "../Library/CONTAINER.h"
#include "../Library/GRAPHIC.h"
#include "../Library/IMAGE_2D.h"

#include "LOAD_DISP.h"
LOAD_DISP::LOAD_DISP() {
}

LOAD_DISP::~LOAD_DISP() {
	delete ContainerLoadThread;
}

void LOAD_DISP::create(CONTAINER* container, IMAGE_2D* shader){
	ContainerLoadThread = new CONTAINER_LOAD_THREAD(container);
	G = GRAPHIC::instance();
	Shader = shader;
	Texture[0].create("Assets/images/icon/load1.png");
	Texture[1].create("Assets/images/icon/load2.png");
	Texture[2].create("Assets/images/icon/load3.png");
	Texture[3].create("Assets/images/icon/load4.png");
	Color = COLOR(1.0f, 1.0f, 1.0f, 0.0f);
	Pos = VECTOR2();
	AnimSpeed = 0.04f;
}

void LOAD_DISP::startProc(){
	while (!LoopFlag) {
		//Update-------------------------------------------------------------------------
		switch (Sw) {
		case 0://フェードイン
			Color.a += 0.025f;
			if (Color.a >= 1.0f) {
				Color.a = 1.0f;
				Sw = 1;
			}
			break;
		case 1://ロード終了待ち
			if (ContainerLoadThread->isFinished()) {
				Sw = 2;
			}
			break;
		case 2://フェードアウト後、このループを抜ける
			Color.a -= 0.025f;
			if (Color.a <= 0.0f) {
				Color.a = 0.0f;
				LoopFlag = true;
			}
			break;
		}
		//アニメーション
		TempAnimPlay += AnimSpeed;
		Frame += (int)TempAnimPlay;
		TempAnimPlay -= (int)TempAnimPlay;
		if (Frame >= Texture.size()) {
			Frame = 0;
		}

		//Draw---------------------------------------------------------------------------
		SHADER* shader = Shader;
		BEGIN_PATH_
			G->clearTarget();
			Texture[Frame].draw(Shader, Pos, Color);
		END_PATH_
		G->present();
	}
}
