#include <stdio.h>
#include <cmath>
#include "../Library/common.h"
#include "../Library/VECTOR2.h"
#include "../Library/CONTAINER.h"
#include "../Library/TEXTURE.h"
#include "../Library/DATA.h"
#include "../Library/MATRIX.h"
#include "BILLBOARD_LASER.h"
ARRAY_P<TEXTURE> BILLBOARD_LASER::Textures[2];
std::vector<BILLBOARD_LASER*> BILLBOARD_LASER::PoolList;
void BILLBOARD_LASER::setGraphic(CONTAINER* container) {
	char* textureName = container->data("BILLBOARD_LASER::textureName1");
	Textures[0].secure((int)container->data("BILLBOARD_LASER::numTexture1"));
	for (int i = 0;i < Textures[0].size();i++) {
		Textures[0][i] = container->texture(textureName, i);
	}	
	textureName = container->data("BILLBOARD_LASER::textureName2");
	Textures[1].secure((int)container->data("BILLBOARD_LASER::numTexture2"));
	for (int i = 0;i < Textures[1].size();i++) {
		Textures[1][i] = container->texture(textureName, i);
	}
	//‚±‚±‚ÅŽg‚¢‚»‚¤‚È”‚¾‚¯ƒv[ƒ‹‚ÉƒCƒ“ƒXƒ^ƒ“ƒX‚µ‚Ä“ü‚ê‚é‚ÆŒy‚­‚È‚é‚©‚à


}
void BILLBOARD_LASER::freeGraphic() {

}

void BILLBOARD_LASER::poolAllDelete() {
	for (auto& i : PoolList) {
		delete i;
	}
	PoolList.clear();
}

BILLBOARD_LASER* BILLBOARD_LASER::takeFromPool() {
	if (PoolList.size() > 0) {
		BILLBOARD_LASER* p = PoolList[PoolList.size() - 1];
		PoolList.pop_back();
		return p;
	}
	return new BILLBOARD_LASER();
}

//Members--------------------------------------------------------------------------------
BILLBOARD_LASER::BILLBOARD_LASER() {
	Aspect = (float)Textures[0][0]->width() / Textures[0][0]->height();
}
BILLBOARD_LASER::~BILLBOARD_LASER() {
}
float BILLBOARD_LASER::rotate(const VECTOR2& pos, const VECTOR2& b) {
	float cosTheta = dot(pos, b);
	float rad = acos(cosTheta);
	if (pos.x * b.y - (pos.y * b.x) > 0.0f) {
		rad *= -1.0f;
	}
	return rad;
}
void BILLBOARD_LASER::init(const VECTOR3& pos, const VECTOR3& rad, float laserSize, float laserLength, int lifeTime, int textureIdx) {
	Pos = pos;
	Rad = rad;
	LaserSize = laserSize;
	LaserLength = laserLength;
	Life = 1;
	TextureIdx = textureIdx;
	Frame = 0;
	//0Š„‚è–hŽ~
	if (lifeTime > 0) {
		MaxLifeTime = lifeTime;
	}
	else{
		MaxLifeTime = 1;
	}
	LifeTime = MaxLifeTime;

}

void BILLBOARD_LASER::init(const VECTOR3& pos1, const VECTOR3& pos2, float laserSize, int lifeTime, int textureIdx) {
	VECTOR3 v = pos2 - pos1;
	VECTOR2 xz = normalize(VECTOR2(v.x, v.z));
	VECTOR3 rad;
	rad.x = (acos(-normalize(v).y) - 1.57f);
	rad.y = rotate(VECTOR2(0.0f, -1.0f), xz);
	init(pos1, rad, laserSize, length(v), lifeTime, textureIdx);
}
void BILLBOARD_LASER::update() {
	if (++Frame >= Textures[TextureIdx].size()) {
		Frame = 0;
	}
}
void BILLBOARD_LASER::draw(SHADER* shader, const VECTOR3& rad) {
	//Šî–{
	MATRIX world;
	world.identity();
	world.mulTranslate(Pos);
	world.mulRotateY(Rad.y);
	world.mulRotateX(Rad.x - 1.57f);
	world.mulRotateZ(Rad.z);

	MATRIX _world = world;
	MATRIX _world2 = world;
	MATRIX _world3 = world;

	//~‚Ý‚½‚¢‚É‚µ‚Ä•`‰æ‚·‚éB— ‚à‚ ‚é‚Ì‚Å‚S‰ñ•`‰æ

	world.mulRotateY((float)RadCnt);
	world.mulScale(( Aspect + LaserSize) * ((float)LifeTime / MaxLifeTime), LaserLength, 1.0f);
	world.mulTranslate(0, 0.5f, 0);
	Textures[TextureIdx][Frame]->draw(shader, world, COLOR(1.0f, 1.0f, 1.0f, 0.5f));

	_world.mulRotateY((float)RadCnt + 3.14f);
	_world.mulScale(( Aspect + LaserSize) * ((float)LifeTime / MaxLifeTime),  LaserLength, 1.0f);
	_world.mulTranslate(0, 0.5f, 0);
	Textures[TextureIdx][Frame]->draw(shader, _world, COLOR(1.0f, 1.0f, 1.0f, 0.5f));

	_world2.mulRotateY((float)RadCnt + 1.57f);
	_world2.mulScale((Aspect + LaserSize) * ((float)LifeTime / MaxLifeTime), LaserLength, 1.0f);
	_world2.mulTranslate(0, 0.5f, 0);
	Textures[TextureIdx][Frame]->draw(shader, _world2, COLOR(1.0f, 1.0f, 1.0f, 0.5f));

	_world3.mulRotateY((float)RadCnt -1.57f);
	_world3.mulScale((Aspect + LaserSize) * ((float)LifeTime / MaxLifeTime), LaserLength, 1.0f);
	_world3.mulTranslate(0, 0.5f, 0);
	Textures[TextureIdx][Frame]->draw(shader, _world3, COLOR(1.0f, 1.0f, 1.0f, 0.5f));
}

void BILLBOARD_LASER::addPool() {
	PoolList.push_back(this);
}
