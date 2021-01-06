#pragma once
class ENTITY_STATES;
class GAME_DATA_COMMON;
class ENTITY_STATE_BASE{
public:
	ENTITY_STATE_BASE() {};
	~ENTITY_STATE_BASE() {};
	virtual void onEnter() = 0;
	virtual void update() = 0;
	virtual void onExit() = 0;
	virtual const char* name()const = 0;
	ENTITY_STATES* states() { return States; };
	GAME_DATA_COMMON* gameDataCommon() { return GameDataCommon; }
protected:
	ENTITY_STATES* States = nullptr;
	GAME_DATA_COMMON* GameDataCommon = nullptr;

};
