#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/SHADER.h"
#include "FADE.h"

FADE::FADE() {
	Texture.create("Assets/images/white.jpg");
	Color.r = 0.2f;
	Color.g = 0.2f;
	Color.b = 0.2f;
	Speed = 0.02f;
	FadeState = FADE_OUT_END;
}

FADE::~FADE() {
}

void FADE::fadeInTrigger() {
	if (FadeState == FADE_OUT_END) {
		FadeState = FADE_IN_TRIGGER;
	}
}

void FADE::fadeOutTrigger() {
	if (FadeState == FADE_IN_END) {
		FadeState = FADE_OUT_TRIGGER;
	}
}

void FADE::draw(SHADER* shader) {
	GRAPHIC* g = GRAPHIC::instance();
	switch (FadeState) {
	case FADE_IN_TRIGGER:
		Color.a = 1.0f;
		Texture.draw(shader, Pos, Color);
		FadeState = FADE_IN;
		break;
	case FADE_IN:
		Texture.draw(shader, Pos, Color);
		Color.a -= Speed;
		if (Color.a < 0.0) {
			Color.a = 0.0f;
			FadeState = FADE_IN_END;
		}
		break;
	case FADE_IN_END:
		break;
	case FADE_OUT_TRIGGER:
		Color.a = 0.0f;
		FadeState = FADE_OUT;
		break;
	case FADE_OUT:
		Texture.draw(shader, Pos, Color);
		Color.a += Speed;
		if (Color.a >= 1.0f) {
			Color.a = 1.0f;
			FadeState = FADE_OUT_END;
		}
		break;
	case FADE_OUT_END:
		Texture.draw(shader, Pos, Color);
		break;
	}
}

int FADE::fadeInEndFlag(){
	return (FadeState == FADE_IN_END);
}

int FADE::fadeOutEndFlag() {
	return (FadeState == FADE_OUT_END);
}

void FADE::setSpeed(float speed) {
	Speed = speed;
}

