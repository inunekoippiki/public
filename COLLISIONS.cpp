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
	//delete�t���O�������Ă��铖���蔻��I�u�W�F�N�g������
	for (unsigned i = 0;i < Collisions.size();) {
		if (Collisions[i]->isDelete()) {
			delete Collisions[i];//�f���[�g����
			Collisions[i] = Collisions[Collisions.size() - 1];//�Ō���ŏ㏑������
			Collisions.pop_back();//�Ō��������
			continue;
		}
		i++;
	}
}

void COLLISIONS::exeCollision(COLLISION_TERRAIN* collision){
	//�n�`�Ɠ����蔻��
	for (auto& i : Collisions) {
		i->entity()->hit(i->isHit(collision));
	}
}

void COLLISIONS::exeCollision(COLLISIONS* collisions){
	//������œ����蔻��
	for (auto& i : Collisions) {
		for (auto i2 : collisions->Collisions) {
			if (i->isHit(i2)) {
				i->entity()->hit(i2);
				i2->entity()->hit(i);
			}
		}
	}
}
