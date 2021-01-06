#pragma once
#include<string>
#include<unordered_map>
#include "../Library/common.h"
#include "ENTITY_STATE.h"

class ENTITY_STATE_BASE;
class STATE_MANAGER;
class ENTITY_STATES {
public:
	ENTITY_STATES();
	~ENTITY_STATES();
	void update();
	void change(const char* name);
	void regist(ENTITY_STATE_BASE* state);
private:
	std::unordered_map<std::string,ENTITY_STATE_BASE*> States;
	ENTITY_STATE_BASE* CurrentState = nullptr;
};