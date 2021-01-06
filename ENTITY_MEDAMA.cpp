#include "../Library/CONTAINER.h"
#include "../Library/MATRIX.h"
#include "SOUND_MANAGER.h"
#include "BILLBOARDS.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_MEDAMA_STATE_ATTACK.h"
#include "ENTITY_MEDAMA_STATE_DOWN.h"
#include "ENTITY_MEDAMA_STATE_IDEL.h"
#include "ENTITY_MEDAMA_STATE_MOVE.h"
#include "ENTITY_MEDAMA.h"
ENTITY_MEDAMA::ENTITY_MEDAMA() {
}

ENTITY_MEDAMA::~ENTITY_MEDAMA() {
	Collision->Delete();
}

void ENTITY_MEDAMA::create(){
	CONTAINER* c = gameDataCommon()->container();

	Enemy.create(this,
		VECTOR3(0.0f, c->data("ENTITY_MEDAMA::UpperPosOffset.y"), 0.0f),
		c->treeOrigin("Medama"),
		c->data("ENTITY_MEDAMA::MaxHp"),
		c->data("ENTITY_MEDAMA::Gravity"));

	//コリジョン設定
	Collision = new COLLISION_SPHERE(this, posPtr(),
		VECTOR3(0.0f, c->data("ENTITY_MEDAMA::CollisionOffest.y"), 0.0f),
		c->data("ENTITY_MEDAMA::CollisionRadius"));
	collisionManager()->addCollisionEnemy(Collision);

	//初期値設定
	CenterPosOffest.y = c->data("ENTITY_MEDAMA::CenterPosOffset.y");
	AttackDamage = c->data("ENTITY_MEDAMA::AttackDamage");
	ActivateFrame_Attack = c->data("ENTITY_MEDAMA::ActivateFrame_Attack");
	AttackTime = c->data("ENTITY_MEDAMA::AttackTime");
	IdelTime = c->data("ENTITY_MEDAMA::IdelTime");
	MoveTime = c->data("ENTITY_MEDAMA::MoveTime");
	MoveSpeed = c->data("ENTITY_MEDAMA::MoveSpeed");
	MoveRadCntSpeed = c->data("ENTITY_MEDAMA::MoveRadCntSpeed");
	AttackInterval = c->data("ENTITY_MEDAMA::AttackInterval");
	BulletSpeed = c->data("ENTITY_MEDAMA::BulletSpeed");
	BulletSize = c->data("ENTITY_MEDAMA::BulletSize");
	Anim_Idel = c->animation("Medama_Idel");
	Anim_Attack = c->animation("Medama_kougeki");
	Anim_Move = c->animation("Medama_Idel");//飛んでるんでIdelと一緒
	Anim_Down = c->animation("Medama_down");
	ToAnim_Idel = c->data("ToAnim_Medama_idel");
	ToAnim_Attack = c->data("ToAnim_Medama_attack");
	ToAnim_Move = c->data("ToAnim_Medama_move");
	ToAnim_Down = c->data("ToAnim_Medama_down");
	AnimSpeed_Idel = c->data("AnimSpeed_Medama_idel");
	AnimSpeed_Attack = c->data("AnimSpeed_Medama_attack");
	AnimSpeed_Move = c->data("AnimSpeed_Medama_move");
	AnimSpeed_Down = c->data("AnimSpeed_Medama_down");
	AnimEndFrame_Idel = c->data("AnimEndFrame_Medama_idel");
	AnimEndFrame_Attack = c->data("AnimEndFrame_Medama_attack");
	AnimEndFrame_Move = c->data("AnimEndFrame_Medama_move");
	AnimEndFrame_Down = c->data("AnimEndFrame_Medama_down");

	SoundAppear = c->sound("medama_appear");
	SoundAttack = c->sound("medama_attack");
	SoundDamage = c->sound("medama_damage");
	SoundDown = c->sound("medama_down");
	//ステート設定
	States->regist(new ENTITY_MEDAMA_STATE_ATTACK(this));
	States->regist(new ENTITY_MEDAMA_STATE_DOWN(this));
	States->regist(new ENTITY_MEDAMA_STATE_IDEL(this));
	States->regist(new ENTITY_MEDAMA_STATE_MOVE(this));
	States->change("MOVE");
}

void ENTITY_MEDAMA::update(){
	Enemy.hpGaugeUpdate();
	States->update();
	Enemy.treeUpdate();
}

void ENTITY_MEDAMA::draw(SHADER* shader){
	Enemy.draw(shader);
}

void ENTITY_MEDAMA::damage(int damage){
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->playSound(SoundDamage, Pos);
	Enemy.damage(damage);
}

ENTITY_TYPE ENTITY_MEDAMA::entityType()const {
	return ENTITY_TYPE::MEDAMA;
}
