#include "../Library/CONTAINER.h"
#include "../Library/MATRIX.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_HANA_STATE_ATTACK.h"
#include "ENTITY_HANA_STATE_DOWN.h"
#include "ENTITY_HANA_STATE_IDEL.h"
#include "ENTITY_HANA_STATE_MOVE.h"
#include "ENTITY_HANA.h"
ENTITY_HANA::ENTITY_HANA() {
}

ENTITY_HANA::~ENTITY_HANA() {
	Collision->Delete();
}

void ENTITY_HANA::create(){
	CONTAINER* c = gameDataCommon()->container();

	Enemy.create(this,
		VECTOR3(0.0f, c->data("ENTITY_HANA::UpperPosOffset.y"), 0.0f),
		c->treeOrigin("Hana"),
		c->data("ENTITY_HANA::MaxHp"),
		c->data("ENTITY_HANA::Gravity"));


	//コリジョン設定
	Collision = new COLLISION_SPHERE(this, posPtr(),
		VECTOR3(0.0f, c->data("ENTITY_HANA::CollisionOffest.y"), 0.0f),
		c->data("ENTITY_HANA::CollisionRadius"));
	collisionManager()->addCollisionEnemy(Collision);
	//モデル設定
	//初期値設定
	CenterPosOffest.y = c->data("ENTITY_HANA::CenterPosOffset.y");
	MoveSpeed = c->data("ENTITY_HANA::MoveSpeed");
	MoveTime = c->data("ENTITY_HANA::MoveTime");
	AttackDamage = c->data("ENTITY_HANA::AttackDamage");
	LaserSize = c->data("ENTITY_HANA::LaserSize");
	LaserLength = c->data("ENTITY_HANA::LaserLength");
	LaserLifeTime = c->data("ENTITY_HANA::LaserLifeTime");
	ActivateFrame_Attack = c->data("ENTITY_HANA::ActivateFrame_Attack");
	IdelTime = c->data("ENTITY_HANA::IdelTime");
	Anim_Idel = c->animation("Hana_Idel");
	Anim_Attack = c->animation("Hana_kougeki");
	Anim_Move = c->animation("Hana_zyannpuidou");
	Anim_Down = c->animation("Hana_down");
	ToAnim_Idel = c->data("ToAnim_Hana_idel");
	ToAnim_Attack = c->data("ToAnim_Hana_attack");
	ToAnim_Move = c->data("ToAnim_Hana_move");
	ToAnim_Down = c->data("ToAnim_Hana_down");
	AnimSpeed_Idel = c->data("AnimSpeed_Hana_idel");
	AnimSpeed_Attack = c->data("AnimSpeed_Hana_attack");
	AnimSpeed_Move = c->data("AnimSpeed_Hana_move");
	AnimSpeed_Down = c->data("AnimSpeed_Hana_down");
	AnimEndFrame_Idel = c->data("AnimEndFrame_Hana_idel");
	AnimEndFrame_Attack = c->data("AnimEndFrame_Hana_attack");
	AnimEndFrame_Move = c->data("AnimEndFrame_Hana_move");
	AnimEndFrame_Down = c->data("AnimEndFrame_Hana_down");
	SoundAppear = c->sound("hana_appear");
	SoundAttack = c->sound("hana_attack");
	SoundDamage = c->sound("hana_damage");
	SoundDown = c->sound("hana_down");

	//ステート設定
	States->regist(new ENTITY_HANA_STATE_ATTACK(this));
	States->regist(new ENTITY_HANA_STATE_DOWN(this));
	States->regist(new ENTITY_HANA_STATE_IDEL(this));
	States->regist(new ENTITY_HANA_STATE_MOVE(this));
	States->change("IDEL");
}

void ENTITY_HANA::update() {
	Enemy.hpGaugeUpdate();
	States->update();
	Enemy.treeUpdate();
}

void ENTITY_HANA::draw(SHADER* shader) {
	Enemy.draw(shader);
}

void ENTITY_HANA::damage(int damage) {
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->playSound(SoundDamage, Pos);
	Enemy.damage(damage);
}

ENTITY_TYPE ENTITY_HANA::entityType()const {
	return ENTITY_TYPE::HANA;
}
