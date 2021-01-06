#include "ENTITY_STATES.h"

ENTITY_STATES::ENTITY_STATES() {
}

ENTITY_STATES::~ENTITY_STATES() {
	for (auto state : States) {
		delete state.second;
	}
}

void ENTITY_STATES::update() {
	CurrentState->update();
}

void ENTITY_STATES::change(const char* name){
	if (CurrentState)CurrentState->onExit();

	CurrentState = States[name];

	if (CurrentState) {
		CurrentState->onEnter();
	}
	else {
		WARNING(1, "‚±‚ÌOBJECT_STATE‚Í‚ ‚è‚Ü‚¹‚ñ", name)
	}
}

void ENTITY_STATES::regist(ENTITY_STATE_BASE* state) {
	States[state->name()] = state;
}
