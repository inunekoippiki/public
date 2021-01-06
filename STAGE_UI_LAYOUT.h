#pragma once
#include <array>
class UI_2D_LEFT;
class UI_2D_CENTERED;
class CONTAINER;
class UI_MANAGER;
class ENTITY_PLAYER;
//バトル画面のUIの配置と更新をするクラス
class STAGE_UI_LAYOUT{
public:
	STAGE_UI_LAYOUT();
	~STAGE_UI_LAYOUT();
	void create(CONTAINER* c, UI_MANAGER* uiManager);
	void update();
	//プレイヤーを渡す纏めてデータを取得してUiに反映する
	void setPlayerDataUpdate(ENTITY_PLAYER* entityPlayer);
	//スタート時のメッセージを非表示にする
	void closeStartMessage();
	//ゲームオーバ画面を表示する
	void showGameOver();
	//クリア画面を表示する
	void showClear();
	//スタート前に出すセリフを設定
	void initStartMessage(CONTAINER* c, STATIC_FONT* font, UI_MANAGER* uiManager, const char* fileName, const char* charaName);
	//クリア時に出すセリフを設定
	void initEndMessage(CONTAINER* c, STATIC_FONT* font, UI_MANAGER* uiManager, const char* fileName, const char* charaName);
private:
	//プレイヤーの情報を更新
	void setPlayerMaxHp(int playerMaxHp);
	void setPlayerHp(int playerHp);
	void setPlayerMaxSp(int playerMaxSp);
	void setPlayerSp(int playerSp);
	void setPlayerChoiceSkillType(int playerChoiceSkillType);

	//バトル開始時終了時のメッセージのUIをインスタンス
	UI_2D_LEFT* instanceMassage(CONTAINER* c, STATIC_FONT* font, UI_MANAGER* uiManager, const char* fileName, const char* charaName);
	UI_2D_LEFT* StartMessage = nullptr;
	UI_2D_LEFT* BattleStartIcon = nullptr;
	UI_2D_LEFT* StatusBack = nullptr;
	UI_2D_LEFT* HpGauge = nullptr;
	UI_2D_LEFT* SkillGauge = nullptr;
	UI_2D_CENTERED* SkillIcon1 = nullptr;
	UI_2D_CENTERED* SkillIcon2 = nullptr;
	UI_2D_CENTERED* SkillIcon3 = nullptr;
	UI_2D_CENTERED* SkillSelectIcon = nullptr;
	UI_2D_CENTERED* CrossHair = nullptr;
	UI_2D_CENTERED* GameOver = nullptr;
	bool IsGameOver = false;
	float GameOverFead = 0;
	UI_2D_LEFT* EndMessage = nullptr;
	UI_2D_LEFT* BattleClearIcon = nullptr;
	UI_2D_LEFT* KeyIcon = nullptr;

	std::array<VECTOR2, 3> SkillIconPos;
	int PlayerHp = 0;
	int PlayerMaxHp = 0;
	float HpGaugeWidth = 0.0f;
	int PlayerSp = 0;
	int PlayerMaxSp = 0;
	float SkillGaugeWidth = 0.0f;
	int PlayerChoiceSkillType = 0;//0,1,2
	int KeyIconDispCnt = 0;
	float KeyIconAlpha = 0.0f;
};

