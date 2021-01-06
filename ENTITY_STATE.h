#pragma once
#include "ENTITY.h"
#include "STATE_MANAGER.h"
#include "ENTITY_STATE_BASE.h"
#include "ENTITY_STATES.h"
template <typename T>
class ENTITY_STATE:public ENTITY_STATE_BASE {
public:
	ENTITY_STATE(T* owner)
		:Owner(owner){
		States=owner->states();
		GameDataCommon = owner->gameDataCommon();
	}
	virtual void onEnter() = 0;
	virtual void update() = 0;
	virtual void onExit() = 0;
	virtual const char* name()const = 0;
	T* owner() { return Owner; }
private:
	T* Owner = nullptr;
};