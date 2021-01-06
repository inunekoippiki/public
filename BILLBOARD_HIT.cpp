#include <stdio.h>
#include <cmath>
#include "../Library/common.h"
#include "../Library/CONTAINER.h"
#include "../Library/TEXTURE.h"
#include "../Library/DATA.h"
#include "../Library/MATRIX.h"
#include "BILLBOARD_HIT.h"

//Static members------------------------------------------------------------------------
TEXTURE** BILLBOARD_HIT::Textures = 0;
int BILLBOARD_HIT::NumTextures = 0;
std::vector<BILLBOARD_HIT*> BILLBOARD_HIT::PoolList;
void BILLBOARD_HIT::setGraphic(CONTAINER* container) {
	NumTextures = container->data("BILLBOARD_HIT::NumTextures");
	Textures = new TEXTURE * [NumTextures];
	char* textureName = container->data("BILLBOARD_HIT::textureName");
	for (int i = 0; i < NumTextures; i++) {
		Textures[i] = container->texture(textureName, i);
	}
}
void BILLBOARD_HIT::freeGraphic() {
	SAFE_DELETE_ARRAY(Textures);
}

void BILLBOARD_HIT::poolAllDelete() {
	for (auto& i : PoolList) {
		delete i;
	}
	PoolList.clear();
}

BILLBOARD_HIT* BILLBOARD_HIT::takeFromPool() {
	if (PoolList.size() > 0) {
		BILLBOARD_HIT* p = PoolList[PoolList.size() - 1];
		PoolList.pop_back();
		return p;
	}
	return new BILLBOARD_HIT();
}

//Members--------------------------------------------------------------------------------
BILLBOARD_HIT::BILLBOARD_HIT() {
	Aspect = (float)Textures[0]->width() / Textures[0]->height();
}
BILLBOARD_HIT::~BILLBOARD_HIT() {
}
void BILLBOARD_HIT::init(const VECTOR3& pos, float scale) {
	Pos = pos;
	Scale = scale;
	AnimCnt = 0;
	Life = 1;
}
void BILLBOARD_HIT::update() {
	AnimIdx = AnimCnt++;
	if (AnimIdx >= NumTextures) {
		Life = 0;
	}
}
void BILLBOARD_HIT::draw(SHADER* shader, const VECTOR3& rad) {
	MATRIX world;
	world.mulTranslate(Pos);
	world.mulRotateY(rad.y);
	world.mulRotateX(rad.x);
	world.mulTranslate(VECTOR3(0.0f, 0.0f, 1.0f));
	world.mulScale(Scale * Aspect, Scale, Scale);
	Textures[AnimIdx]->draw(shader, world);
}

void BILLBOARD_HIT::addPool() {
	PoolList.push_back(this);
}
