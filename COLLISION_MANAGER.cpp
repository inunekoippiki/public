#include "../Library/common.h"
#include "COLLISION_TERRAIN.h"
#include "COLLISIONS.h"
#include "COLLISION_MANAGER.h"

COLLISION_MANAGER::COLLISION_MANAGER(CONTAINER* c) {
	CollisionTerrain = new COLLISION_TERRAIN(c);
	CollisionsPlayer = new COLLISIONS();
	CollisionsEnemy = new COLLISIONS();
	CollisionsPlayerAttck = new COLLISIONS();
	CollisionsEnemyAttck = new COLLISIONS();
}

COLLISION_MANAGER::~COLLISION_MANAGER() {
	SAFE_DELETE(CollisionsEnemyAttck);
	SAFE_DELETE(CollisionsPlayerAttck);
	SAFE_DELETE(CollisionsEnemy);
	SAFE_DELETE(CollisionsPlayer);
	SAFE_DELETE(CollisionTerrain);
}

void COLLISION_MANAGER::exeCollision(){
	deleteUpdate();
	CollisionsPlayer->exeCollision(CollisionsEnemy);
	CollisionsPlayer->exeCollision(CollisionsEnemyAttck);
	CollisionsEnemy->exeCollision(CollisionsPlayerAttck);
	//’nŒ`‚Æ‚Ì”»’è
	CollisionsPlayer->exeCollision(CollisionTerrain);
	CollisionsEnemy->exeCollision(CollisionTerrain);
	CollisionsEnemyAttck->exeCollision(CollisionTerrain);
	CollisionsPlayerAttck->exeCollision(CollisionTerrain);

}

void COLLISION_MANAGER::deleteUpdate(){
	CollisionsPlayer->deleteUpdate();
	CollisionsEnemy->deleteUpdate();
	CollisionsPlayerAttck->deleteUpdate();
	CollisionsEnemyAttck->deleteUpdate();
}

void COLLISION_MANAGER::addCollisionPlayer(COLLISION* collision){
	CollisionsPlayer->add(collision);
}

void COLLISION_MANAGER::addCollisionEnemy(COLLISION* collision){
	CollisionsEnemy->add(collision);
}

void COLLISION_MANAGER::addCollisionPlayerAttck(COLLISION* collision){
	CollisionsPlayerAttck->add(collision);
}

void COLLISION_MANAGER::addCollisionEnemyAttck(COLLISION* collision){
	CollisionsEnemyAttck->add(collision);
}
