#pragma once
class STATE;
class STATE_MANAGER;
namespace STATE_FACTORY {

	//タイトルステートをインスタンス
	STATE* instanceTitle(STATE_MANAGER* stateManager);
	//セーブデータ選択ステートをインスタンス
	STATE* instanceSaveSelect(STATE_MANAGER* stateManager);
	//プロローグステートをインスタンス
	STATE* instancePrologue(STATE_MANAGER* stateManager);
	//メニューステートをインスタンス
	STATE* instanceMenu(STATE_MANAGER* stateManager);
	//オプションステートをインスタンス
	STATE* instanceOption(STATE_MANAGER* stateManager,STATE* state);
	//ストーリステートの種類
	enum class STORY_TYPE {
		s00_00,
		s00_01,
		s01_00,
		s01_01,
		s02_00,
		s02_01
	};
	//ストーリステートをインスタンス
	STATE* instanceStory(STATE_MANAGER* stateManager, STORY_TYPE storyType);
	//ステージステートの種類
	enum class STAGE_TYPE {
		s00,
		s01,
		s02
	};
	//ステージステートをインスタンス
	STATE* instanceStage(STATE_MANAGER* stateManager, STAGE_TYPE stageType);
}
