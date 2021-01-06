#include <stdio.h>
#include <cmath>
#include "../Library/common.h"
#include "../Library/CONTAINER.h"
#include "../Library/TEXTURE.h"
#include "../Library/DATA.h"
#include "../Library/MATRIX.h"
#include "BILLBOARD_BURN.h"

//Static members------------------------------------------------------------------------
TEXTURE** BILLBOARD_BURN::Textures = 0;
int BILLBOARD_BURN::NumTextures = 0;
std::vector<BILLBOARD_BURN*> BILLBOARD_BURN::PoolList;
void BILLBOARD_BURN::setGraphic(CONTAINER* container) {
	NumTextures = container->data("BILLBOARD_BURN::NumTextures");
	Textures = new TEXTURE * [NumTextures];
	char* textureName = container->data("BILLBOARD_BURN::textureName");
	for (int i = 0; i < NumTextures; i++) {
		Textures[i] = container->texture(textureName, i);
	}
}
void BILLBOARD_BURN::freeGraphic() {
	SAFE_DELETE_ARRAY(Textures);
}

void BILLBOARD_BURN::poolAllDelete() {
	for (auto& i : PoolList) {
		delete i;
	}
	PoolList.clear();
}

BILLBOARD_BURN* BILLBOARD_BURN::takeFromPool() {
	if (PoolList.size() > 0) {
		BILLBOARD_BURN* p = PoolList[PoolList.size() - 1];
		PoolList.pop_back();
		return p;
	}
	return new BILLBOARD_BURN();
}

//Members--------------------------------------------------------------------------------
BILLBOARD_BURN::BILLBOARD_BURN() {
	Aspect = (float)Textures[0]->width() / Textures[0]->height();
}
BILLBOARD_BURN::~BILLBOARD_BURN() {
}
void BILLBOARD_BURN::init(const VECTOR3& pos, float scale) {
	Pos = pos;
	Scale = scale;
	AnimCnt = 10;
	Life = 1;
}
void BILLBOARD_BURN::update() {
	AnimIdx = AnimCnt++;
	if (AnimIdx >= NumTextures) {
		Life = 0;
	}
}
void BILLBOARD_BURN::draw(SHADER* shader, const VECTOR3& rad) {
	MATRIX world;
	world.mulTranslate(Pos);
	world.mulRotateY(rad.y);
	world.mulRotateX(rad.x);
	world.mulScale(Scale * Aspect, Scale, Scale);
	Textures[AnimIdx]->draw(shader, world);
}

void BILLBOARD_BURN::addPool() {
	PoolList.push_back(this);
}
