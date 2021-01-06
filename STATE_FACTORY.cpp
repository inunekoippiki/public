#include "../Library/common.h"
#include "TITLE.h"
#include "SAVE_SELECT.h"
#include "PROLOGUE.h"
#include "MENU.h"
#include "OPTION.h"
#include "STORY.h"
#include "STAGE00.h"
#include "STAGE01.h"
#include "STAGE02.h"
#include "STATE_FACTORY.h"
namespace STATE_FACTORY {
	STATE* instanceTitle(STATE_MANAGER* stateManager) {
		TITLE* p = new TITLE();
		p->create(stateManager);
		return p;
	}

	STATE* instanceSaveSelect(STATE_MANAGER* stateManager) {
		SAVE_SELECT* p = new SAVE_SELECT();
		p->create(stateManager);
		return p;
	}

	STATE* instancePrologue(STATE_MANAGER* stateManager) {
		PROLOGUE* p = new PROLOGUE();
		p->create(stateManager);
		return p;
	}

	STATE* instanceMenu(STATE_MANAGER* stateManager) {
		MENU* p = new MENU();
		p->create(stateManager);
		return p;
	}

	STATE* instanceOption(STATE_MANAGER* stateManager, STATE* state) {
		OPTION* p = new OPTION();
		p->create(stateManager, state);
		return p;
	}

	STATE* instanceStory(STATE_MANAGER* stateManager, STORY_TYPE storyType) {
		const char* fileName;
		std::function<STATE* (STATE_MANAGER*)> nextState;
		switch (storyType) {
		case STORY_TYPE::s00_00:
			fileName = "Assets/story/001.txt";
			nextState = [](STATE_MANAGER* stateManager)->STATE* {
				return STATE_FACTORY::instanceStage(stateManager, STATE_FACTORY::STAGE_TYPE::s00);};
			break;
		case STORY_TYPE::s00_01:
			fileName = "Assets/story/002.txt";
			nextState = [](STATE_MANAGER* stateManager)->STATE* {
				return STATE_FACTORY::instanceMenu(stateManager);};
			break;
		case STORY_TYPE::s01_00:
			fileName = "Assets/story/003.txt";
			nextState = [](STATE_MANAGER* stateManager)->STATE* {
				return STATE_FACTORY::instanceStage(stateManager, STATE_FACTORY::STAGE_TYPE::s01);};
			break;
		case STORY_TYPE::s01_01:
			fileName = "Assets/story/004.txt";
			nextState = [](STATE_MANAGER* stateManager)->STATE* {
				return STATE_FACTORY::instanceMenu(stateManager);};
			break;
		case STORY_TYPE::s02_00:
			fileName = "Assets/story/005.txt";
			nextState = [](STATE_MANAGER* stateManager)->STATE* {
				return STATE_FACTORY::instanceStage(stateManager, STATE_FACTORY::STAGE_TYPE::s02);};
			break;
		case STORY_TYPE::s02_01:
			fileName = "Assets/story/006.txt";
			nextState = [](STATE_MANAGER* stateManager)->STATE* {
				return STATE_FACTORY::instanceTitle(stateManager);};
			break;
		default:
			WARNING(true, "STORY_TYPE‚ª”ÍˆÍŠO‚Å‚·", "");
			fileName = "";
			nextState = [](STATE_MANAGER* stateManager)->STATE* {return nullptr;};
			break;
		}
		STORY* p = new STORY();
		p->create(stateManager, fileName, nextState);
		return p;
	}
	STATE* instanceStage(STATE_MANAGER* stateManager, STAGE_TYPE stageType) {
		switch (stageType) {
		case STATE_FACTORY::STAGE_TYPE::s00:
		{
			STAGE00* p = new STAGE00();
			p->create(stateManager);
			return p;
		}
		case STATE_FACTORY::STAGE_TYPE::s01:
		{
			STAGE01* p = new STAGE01();
			p->create(stateManager);
			return p;
		}
		case STATE_FACTORY::STAGE_TYPE::s02:
		{
			STAGE02* p = new STAGE02();
			p->create(stateManager);
			return p;
		}
		default:
		WARNING(true, "STAGE_TYPE‚ª”ÍˆÍŠO‚Å‚·", "");
		return nullptr;
		}
	}
}