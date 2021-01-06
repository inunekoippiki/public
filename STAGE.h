#pragma once
#include "../Library/CONTAINER.h"
#include "../Library/MATRIX.h"
#include "../Library/COLOR.h"
#include "../Library/VECTOR3.h"
#include "DIALOG_RETRY.h"
#include "STATE.h"
class SHADER;
class CAMERA_FOLLOW;
class STATE_MANAGER;
class BILLBOARDS;
class COLLISION_MANAGER;
class ENTITY_MANAGER;
class ENTITY_PLAYER;
class UI_MANAGER;
class STAGE_UI_LAYOUT;
class SOUND;
class EFFEKSSER;
class SAVE;
//ステート
enum class BATTLE_STATE {
	START,
	BATTLE,
	BATTLE_END_CLEAR,
	BATTLE_END_GAMEOVER,
	BATTLE_END_RETRY,
	BATTLE_FADE_END_CLEAR,
	BATTLE_FADE_END_GAMEOVER,
	BATTLE_FADE_END_RETRY,
};
//各STAGEステートで利用する機能が入ったクラス
//使う前にcreate系のは利用側で全て呼んでおくこと
class STAGE {
public:
	STAGE();
	~STAGE();
	void create(STATE_MANAGER* stateManager);
	//マップを設定する
	void createMap(TREE* map);
	//スタート時に出るメッセージを設定
	void createStartMessage(const char* storyFileName, const char* charaName);
	//クリア時に時に出るメッセージを設定
	void createEndMessage(const char* storyFileName, const char* charaName);
	//メインループ
	void proc(STATE_MANAGER* stateManager);
	//クリアしたとき呼ぶ
	void gameClear(int round);
	//失敗したとき呼ぶ
	void gameOver();

	ENTITY_PLAYER* player() { return Player; }
	ENTITY_MANAGER* entityManager() { return EntityManager; }
	BATTLE_STATE battleState() { return BattleState; }
private:
	void createSahder(STATE_MANAGER* stateManager);
	void createBillboard();
	void createViewProj(STATE_MANAGER* stateManager);
	void createLight(STATE_MANAGER* stateManager);
	void createLightViewProj(STATE_MANAGER* stateManager);
	void createUiManager(STATE_MANAGER* stateManager);
	void createEntityManager(STATE_MANAGER* stateManager);
	void createCollisionManager();
	void createPlayer(STATE_MANAGER* stateManager);
	void createCamera(STATE_MANAGER* stateManager);
	void fadeInStart(STATE_MANAGER* stateManager);
	//バトルをスタートさせる
	void BattleStart();
	//Uiのアップデート
	void stageUiLayoutUpdate();
	//3DのUIの描画位置のアップデート
	void ui3dUpdate();
	//エンティティのアップデート
	void entityUpdate();
	//当たり判定のアップデート
	void collisionManagerUpdate();
	//ビルボードのアップデート
	void billboardUpdate();
	//カメラのアップデート
	void cameraUpdate();
	//クリアステートのとき実行するアップデート
	void battleClearStateUpdate(STATE_MANAGER* stateManager);
	//シェーダーとその情報を設定
	void shaderSet(SHADER** shader);
	//エンティティの描画
	void entityManagerDraw(SHADER* shader);
	//ビルボードの描画
	void billboardDraw(SHADER* shader);
	//UIの描画
	void uiManagerDraw(SHADER* shader);
	//フェード用の画像描画
	void fadeDraw(STATE_MANAGER* stateManager, SHADER* shader);

	STATE_MANAGER* StateManager = nullptr;
	//マップ
	TREE* Map = nullptr;
	//Shader
	SHADER* VariantShader = nullptr;
	SHADER* Image2dShader = nullptr;
	SHADER* Image3dShader = nullptr;
	//Container
	CONTAINER* C = nullptr;
	STATIC_FONT* Font = nullptr;
	//View、Proj
	CAMERA_FOLLOW* CameraFollow = nullptr;
	MATRIX View;
	MATRIX Proj;
	COLOR ClearTargetColor;
	//Light
	VECTOR3 LightPos;
	float Ambient = 0;
	COLOR Diffuse;
	//LightからのView,Proj
	MATRIX LightView;
	MATRIX LightProj;
	//ビルボード
	BILLBOARDS* Billboards = nullptr;
	//コリジョンマネージャー
	COLLISION_MANAGER* CollisionManager = nullptr;
	//ENTITY
	ENTITY_MANAGER* EntityManager = nullptr;
	ENTITY_PLAYER* Player = nullptr;
	//UI
	UI_MANAGER* UiManager = nullptr;
	STAGE_UI_LAYOUT* StageUiLayout = nullptr;
	//エフェクト
	EFFEKSSER* Effeksser = nullptr;
	BATTLE_STATE BattleState = BATTLE_STATE::START;
	//ゲームオーバー遷移用
	int GameoverStateTime = 0;
	int GameoverStateCnt = 0;
	bool IsClear = false;
	//音
	SOUND* SoundGameover = nullptr;
	SOUND* SoundStart = nullptr;
	SOUND* SoundClear = nullptr;
	//リトライダイヤログ
	DIALOG_RETRY DialogRetry;
	//選択中のダイヤログ
	IDIALOG* SelectDialog = nullptr;
	//セーブデータ
	SAVE* Save = nullptr;
};

