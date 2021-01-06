#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/TEXTURE.h"
#include "../Library/MATRIX.h"
#include "BILLBOARD_LIGHT_BULLET.h"
ARRAY_P<TEXTURE> BILLBOARD_LIGHT_BULLET::Textures;
std::vector<BILLBOARD_LIGHT_BULLET*> BILLBOARD_LIGHT_BULLET::PoolList;
void BILLBOARD_LIGHT_BULLET::setGraphic(CONTAINER* container) {
	char* textureName = container->data("BILLBOARD_LIGHT_BULLET::textureName");
	Textures.secure((int)container->data("BILLBOARD_LIGHT_BULLET::numTexture"));
	for (int i = 0;i < Textures.size();i++) {
		Textures[i] = container->texture(textureName,i);
	}
}
void BILLBOARD_LIGHT_BULLET::freeGraphic() {
}
void BILLBOARD_LIGHT_BULLET::poolAllDelete() {
	for (auto& i : PoolList) {
		delete i;
	}
	PoolList.clear();
}
BILLBOARD_LIGHT_BULLET* BILLBOARD_LIGHT_BULLET::takeFromPool() {
	if (PoolList.size() > 0) {
		BILLBOARD_LIGHT_BULLET* p = PoolList[PoolList.size() - 1];
		PoolList.pop_back();
		return p;
	}
	return new BILLBOARD_LIGHT_BULLET();
}
BILLBOARD_LIGHT_BULLET::BILLBOARD_LIGHT_BULLET() {
	Aspect = (float)Textures[0]->width() / Textures[0]->height();
}

BILLBOARD_LIGHT_BULLET::~BILLBOARD_LIGHT_BULLET() {

}

void BILLBOARD_LIGHT_BULLET::init(const VECTOR3& pos, const VECTOR3& velo, float scale) {
	Pos = pos;
	Velocity = velo;
	Scale = scale;
	Life = 1;
	LifeTime = 60;
	Frame = 0;
}

void BILLBOARD_LIGHT_BULLET::update() {
	Pos += Velocity;
	if (LifeTime-- < 0) {
		Life = 0;
	}
	if (++Frame >= Textures.size()) {
		Frame = 0;
	}
}

void BILLBOARD_LIGHT_BULLET::draw(SHADER* shader, const VECTOR3& rad) {
	MATRIX world;
	world.identity();
	world.mulTranslate(Pos);
	world.mulRotateY(rad.y);
	world.mulRotateX(rad.x);
	world.mulRotateZ(rad.z);
	world.mulScale(Scale * Aspect, Scale, 1.0f);
	world.mulTranslate(0, 0.5f, 0);
	Textures[Frame]->draw(shader, world, COLOR(1.0f, 0.8f, 0.4f));

}

void BILLBOARD_LIGHT_BULLET::addPool() {
	PoolList.push_back(this);
}
