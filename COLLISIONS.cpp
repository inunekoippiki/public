#include "COLLISION.h"
#include "ENTITY.h"
#include "COLLISIONS.h"
COLLISIONS::COLLISIONS() {
}

COLLISIONS::~COLLISIONS() {
	for (auto& i : Collisions) {
		delete i;
	}
}

void COLLISIONS::add(COLLISION* collsion){
	Collisions.push_back(collsion);
}

void COLLISIONS::deleteUpdate(){
	//deleteフラグが入っている当たり判定オブジェクトを消す
	for (unsigned i = 0;i < Collisions.size();) {
		if (Collisions[i]->isDelete()) {
			delete Collisions[i];//デリートして
			Collisions[i] = Collisions[Collisions.size() - 1];//最後尾で上書きして
			Collisions.pop_back();//最後尾を消す
			continue;
		}
		i++;
	}
}

void COLLISIONS::exeCollision(COLLISION_TERRAIN* collision){
	//地形と当たり判定
	for (auto& i : Collisions) {
		i->entity()->hit(i->isHit(collision));
	}
}

void COLLISIONS::exeCollision(COLLISIONS* collisions){
	//総当りで当たり判定
	for (auto& i : Collisions) {
		for (auto i2 : collisions->Collisions) {
			if (i->isHit(i2)) {
				i->entity()->hit(i2);
				i2->entity()->hit(i);
			}
		}
	}
}
