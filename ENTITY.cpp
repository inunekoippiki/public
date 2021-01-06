#include "../Library/DATA.h"
#include "../Library/CONTAINER.h"
#include "../Library/MATRIX.h"
#include "../Library/VECTOR2.h"
#include "ENTITY_STATES.h"
#include "ENTITY.h"
GAME_DATA_COMMON* ENTITY::GameDataCommon = nullptr;
ENTITY_MANAGER* ENTITY::EntityManager = nullptr;
COLLISION_MANAGER* ENTITY::CollisionManager = nullptr;
BILLBOARDS* ENTITY::Billboards = nullptr;
EFFEKSSER* ENTITY::Effeksser = nullptr;
UI_MANAGER* ENTITY::UiManager = nullptr;
ENTITY::ENTITY() {
	States = new ENTITY_STATES();
}

ENTITY::~ENTITY() {
	delete States;
}

void ENTITY::update() {
}

void ENTITY::draw(SHADER* shader) {
}

void ENTITY::hit(COLLISION* entity) {
}

void ENTITY::damage(int damage){
}

void ENTITY::posUpdate(){
	Pos += Velo;
}

void ENTITY::radUpdate(){
	radUpdate(Velo);
}

void ENTITY::radUpdate(const VECTOR3& velo){
	VECTOR3 v = normalize(velo);
	VECTOR2 xz = normalize(VECTOR2(v.x, v.z));
	Rad.x = (acos(v.y) - 1.57f);
	float beforeRadY = Rad.y;
	Rad.y = acosf(xz.z);
	if (isnan(Rad.y)) {
		Rad.y = beforeRadY;
	}
	if (xz.x < 0.0f) {
		Rad.y *= -1.0f;
	}
}

void ENTITY::lookAt(const VECTOR3& pos){
	VECTOR3 v = pos - Pos;
	radUpdate(v);
}

void ENTITY::hit(const VECTOR3& pushBack){
	//押し出し処理
	Pos += pushBack;
	//ベロシティのリセット
	if (pushBack.x != 0.0f) {
		Velo.x = 0.0f;
	};
	if (pushBack.y != 0.0f) {
		Velo.y = 0.0f;
	};
	if (pushBack.z != 0.0f) {
		Velo.z = 0.0f;
	};
}

VECTOR3 ENTITY::centerPos(){
	return Pos + CenterPosOffest;
}
