#pragma warning (disable:4996)
#include <string.h>
#include "../Library/TEXTURE.h"
#include "../Library/VECTOR2.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "DIALOG_RETRY.h"
DIALOG_RETRY::DIALOG_RETRY() {
}

DIALOG_RETRY::~DIALOG_RETRY() {
}

void DIALOG_RETRY::create(CONTAINER* c) {
	Dialog.create(
		c,
		c->texture("commandWindowSelectIconRetry"),
		VECTOR2(418.0f, 708.0f),
		VECTOR2(1013.0f, 708.0f),
		c->texture("retry"),
		VECTOR2(291.0f, 162.0f));
}

void DIALOG_RETRY::init(){
	Dialog.init();
}

void DIALOG_RETRY::update(){
	Dialog.update();
}

void DIALOG_RETRY::draw(SHADER* shader) {
	Dialog.draw(shader);
}
