#pragma once
class STATE_MANAGER;
//ステートのインターフェース
class STATE {
public:
	virtual ~STATE() {}
	virtual void proc(STATE_MANAGER* stateManager) = 0;
};