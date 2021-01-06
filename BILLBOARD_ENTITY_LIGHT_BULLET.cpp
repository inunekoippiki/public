#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/TEXTURE.h"
#include "../Library/MATRIX.h"
#include "BILLBOARD_ENTITY_LIGHT_BULLET.h"

ARRAY_P<TEXTURE> BILLBOARD_ENTITY_LIGHT_BULLET::Textures[3];
std::vector<BILLBOARD_ENTITY_LIGHT_BULLET*> BILLBOARD_ENTITY_LIGHT_BULLET::PoolList;
void BILLBOARD_ENTITY_LIGHT_BULLET::setGraphic(CONTAINER* container) {
	char* textureName = container->data("BILLBOARD_ENTITY_LIGHT_BULLET::textureName1");
	Textures[0].secure((int)container->data("BILLBOARD_ENTITY_LIGHT_BULLET::numTexture1"));
	for (int i = 0;i < Textures[0].size();i++) {
		Textures[0][i] = container->texture(textureName,i);
	}
	textureName = container->data("BILLBOARD_ENTITY_LIGHT_BULLET::textureName2");
	Textures[1].secure((int)container->data("BILLBOARD_ENTITY_LIGHT_BULLET::numTexture2"));
	for (int i = 0;i < Textures[1].size();i++) {
		Textures[1][i] = container->texture(textureName, i);
	}
	textureName = container->data("BILLBOARD_ENTITY_LIGHT_BULLET::textureName3");
	Textures[2].secure((int)container->data("BILLBOARD_ENTITY_LIGHT_BULLET::numTexture3"));
	for (int i = 0;i < Textures[2].size();i++) {
		Textures[2][i] = container->texture(textureName, i);
	}
}
void BILLBOARD_ENTITY_LIGHT_BULLET::freeGraphic() {

}
void BILLBOARD_ENTITY_LIGHT_BULLET::poolAllDelete() {
	for (auto& i : PoolList) {
		delete i;
	}
	PoolList.clear();
}
BILLBOARD_ENTITY_LIGHT_BULLET* BILLBOARD_ENTITY_LIGHT_BULLET::takeFromPool() {
	if (PoolList.size() > 0) {
		BILLBOARD_ENTITY_LIGHT_BULLET* p = PoolList[PoolList.size() - 1];
		PoolList.pop_back();
		return p;
	}
	return new BILLBOARD_ENTITY_LIGHT_BULLET();
}
BILLBOARD_ENTITY_LIGHT_BULLET::BILLBOARD_ENTITY_LIGHT_BULLET() {
	Aspect = (float)Textures[0][0]->width() / Textures[0][0]->height();
}

BILLBOARD_ENTITY_LIGHT_BULLET::~BILLBOARD_ENTITY_LIGHT_BULLET() {

}

void BILLBOARD_ENTITY_LIGHT_BULLET::init(const VECTOR3& pos, float scale, int textureIdx) {
	Pos = pos;
	Scale = scale;
	Life = 1;
	TextureIdx = textureIdx;
	Frame = 0;
}

void BILLBOARD_ENTITY_LIGHT_BULLET::update() {
	if (++Frame >= Textures[TextureIdx].size()) {
		Frame = 0;
	}
}

void BILLBOARD_ENTITY_LIGHT_BULLET::draw(SHADER* shader, const VECTOR3& rad) {
	MATRIX world;
	world.identity();
	world.mulTranslate(Pos);
	world.mulRotateY(rad.y);
	world.mulRotateX(rad.x);
	world.mulRotateZ(rad.z);
	world.mulScale(Scale * Aspect, Scale, 1.0f);
	Textures[TextureIdx][Frame]->draw(shader, world);
	Textures[TextureIdx][Frame]->draw(shader, world);
	//‚È‚ñ‚¿‚á‚Á‚Ä‰e‚Ì•`‰æi°‚ª•½–ÊŒÀ’èj
	MATRIX world_;
	world_.identity();
	world_.mulTranslate(VECTOR3(Pos.x,0.1f,Pos.z));
	world_.mulRotateX(-1.57f);
	world_.mulScale(Scale * Aspect, Scale, 1.0f);
	Textures[TextureIdx][Frame]->draw(shader, world_,COLOR(0.1f,0.1f,0.1f,0.5f));

}

void BILLBOARD_ENTITY_LIGHT_BULLET::setPos(const VECTOR3& pos){
	Pos = pos;
}

void BILLBOARD_ENTITY_LIGHT_BULLET::addPool() {
	PoolList.push_back(this);
}
