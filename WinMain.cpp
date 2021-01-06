#pragma warning(disable:4996)
#include <string>
#include <fstream>
#include "../Library/common.h"
#include "../Library/WINDOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/DSOUND.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/Thread/THREAD_MANAGER.h"
#include "createAssets.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "STATE_MANAGER.h"

int APIENTRY WinMain( HINSTANCE, HINSTANCE, LPSTR, INT ){
    //�R���t�B�O�Ǎ�------------------------------------------------------
    std::ifstream configFile("Assets/config.txt");
    if (!configFile.is_open()) { 
        WARNING(true, "�R���t�B�O�t�@�C����������܂���B", ""); 
    }
    std::string string;
    int isFullscreen = 0;
    configFile >> string >> isFullscreen;
    configFile.close();
    //�E�B���h�E�쐬------------------------------------------------------
    WINDOW* w = nullptr;
    if (isFullscreen) {
       w = new WINDOW("Valiant", 1920, 1080, MODE_FULLSCREEN);
    }
    else {
       w = new WINDOW("Valiant", 1920, 1080, 1024, 576);
    }
    //���ʃf�[�^----------------------------------------------------------
    GRAPHIC* g = new GRAPHIC;
    DSOUND* s = new DSOUND;
    DEBUG_STR* ds = new DEBUG_STR;
    THREAD_MANAGER* th = new THREAD_MANAGER( 0 );
    INPUT_COMMON* in = new INPUT_COMMON;
    SOUND_MANAGER* Sm = new SOUND_MANAGER();

    //���C������----------------------------------------------------------
    STATE_MANAGER* stateManager = new  STATE_MANAGER;
    stateManager->create();
    while( w->msgProc() ){
        if( w->active() ){
			stateManager->proc();
        }
    }
    SAFE_DELETE(stateManager);
    //--------------------------------------------------------------------

    SAFE_DELETE(Sm);
    SAFE_DELETE(in);
    SAFE_DELETE(th);
    SAFE_DELETE(ds);
    SAFE_DELETE(s);
    SAFE_DELETE(g);
    SAFE_DELETE(w);
    return 0;
}

