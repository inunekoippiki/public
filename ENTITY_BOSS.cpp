#include "../Library/CONTAINER.h"
#include "../Library/MATRIX.h"
#include "DATA_LIB.h"
#include "COLLISION_SPHERES.h"
#include "COLLISION_MANAGER.h"
#include "EFFEKSSER.h"
#include "UI_MANAGER.h"
#include "UPGRADE.h"
#include "UI_DRAWER_FACTORY.h"
#include "ENTITY_BOSS_STATE_ATTACK1.h"
#include "ENTITY_BOSS_STATE_ATTACK2.h"
#include "ENTITY_BOSS_STATE_DOWN.h"
#include "ENTITY_BOSS_STATE_IDEL.h"
#include "ENTITY_BOSS_STATE_MOVE.h"
#include "ENTITY_BOSS.h"
ENTITY_BOSS::ENTITY_BOSS() {
}

ENTITY_BOSS::~ENTITY_BOSS() {
	Collision->Delete();
}

void ENTITY_BOSS::create(){
	CONTAINER* c = gameDataCommon()->container();

	Enemy.create(this,
		VECTOR3(0.0f, c->data("ENTITY_BOSS::UpperPosOffset.y"), 0.0f),
		c->treeOrigin("Boss"),
		c->data("ENTITY_BOSS::MaxHp"),
		c->data("ENTITY_BOSS::Gravity"));

	//コリジョン設定
	COLLISION_SPHERES* p = new COLLISION_SPHERES(this, posPtr());
	p->add(VECTOR3(0.0f, c->data("ENTITY_BOSS::CollisionOffest1.y"), 0.0f),
		c->data("ENTITY_BOSS::CollisionRadius1"));
	p->add(VECTOR3(0.0f, c->data("ENTITY_BOSS::CollisionOffest2.y"), 0.0f),
		c->data("ENTITY_BOSS::CollisionRadius2"));
	p->add(VECTOR3(0.0f, c->data("ENTITY_BOSS::CollisionOffest3.y"), 0.0f),
		c->data("ENTITY_BOSS::CollisionRadius3"));
	Collision = p;
	collisionManager()->addCollisionEnemy(Collision);
	//初期値設定
	CenterPosOffest.y = c->data("ENTITY_BOSS::CenterPosOffset.y");
	MoveSpeed = c->data("ENTITY_BOSS::MoveSpeed");
	MoveTime = c->data("ENTITY_BOSS::MoveTime");
	BodyBlowDamage = c->data("ENTITY_BOSS::BodyBlowDamage");
	AttackDamage1 = c->data("ENTITY_BOSS::AttackDamage1");
	LaserSize = c->data("ENTITY_BOSS::LaserSize");
	LaserLength = c->data("ENTITY_BOSS::LaserLength");
	LaserLifeTime = c->data("ENTITY_BOSS::LaserLifeTime");
	AttackDamage2 = c->data("ENTITY_BOSS::AttackDamage2");
	Attack2BulletFluctuation = c->data("ENTITY_BOSS::Attack2BulletFluctuation");
	BulletSpeed = c->data("ENTITY_BOSS::BulletSpeed");
	BulletSize = c->data("ENTITY_BOSS::BulletSize");
	ActivateFrame_Attack1 = c->data("ENTITY_BOSS::ActivateFrame_Attack1");
	ActivateFrame_Attack2 = c->data("ENTITY_BOSS::ActivateFrame_Attack2");
	IdelTime = c->data("ENTITY_BOSS::IdelTime");
	IdelTimeBoost = 1.0f;
	Anim_Idel = c->animation("Boss_Idel");
	Anim_Attack1 = c->animation("Boss_kougeki");
	Anim_Attack2 = c->animation("Boss_kougeki2");
	Anim_Move = c->animation("Boss_hasiru");
	Anim_Down = c->animation("Boss_down");
	ToAnim_Idel = c->data("ToAnim_Boss_idel");
	ToAnim_Attack1 = c->data("ToAnim_Boss_attack1");
	ToAnim_Attack2 = c->data("ToAnim_Boss_attack2");
	ToAnim_Move = c->data("ToAnim_Boss_move");
	ToAnim_Down = c->data("ToAnim_Boss_down");
	AnimSpeed_Idel = c->data("AnimSpeed_Boss_idel");
	AnimSpeed_Attack1 = c->data("AnimSpeed_Boss_attack1");
	AnimSpeed_Attack2 = c->data("AnimSpeed_Boss_attack2");
	AnimSpeed_Move = c->data("AnimSpeed_Boss_move");
	AnimSpeed_Down = c->data("AnimSpeed_Boss_down");
	AnimEndFrame_Idel = c->data("AnimEndFrame_Boss_idel");
	AnimEndFrame_Attack1 = c->data("AnimEndFrame_Boss_attack1");
	AnimEndFrame_Attack2 = c->data("AnimEndFrame_Boss_attack2");
	AnimEndFrame_Move = c->data("AnimEndFrame_Boss_move");
	AnimEndFrame_Down = c->data("AnimEndFrame_Boss_down");
	SoundAppear = c->sound("boss_appear");
	SoundAttack1 = c->sound("boss_attack1");
	SoundAttack2 = c->sound("boss_attack2");
	SoundBodyBlow = c->sound("boss_bodyBlow");
	SoundDamage = c->sound("boss_damage");
	SoundDown = c->sound("boss_down");
	//UI
	BossHpGauge.create(c, uiManager());
	BossFlash.create(c, uiManager());
	//ステート設定
	States->regist(new ENTITY_BOSS_STATE_ATTACK1(this));
	States->regist(new ENTITY_BOSS_STATE_ATTACK2(this));
	States->regist(new ENTITY_BOSS_STATE_DOWN(this));
	States->regist(new ENTITY_BOSS_STATE_IDEL(this));
	States->regist(new ENTITY_BOSS_STATE_MOVE(this));
	States->change("IDEL");
}

void ENTITY_BOSS::update() {
	hpGaugeUpdate();
	BossFlash.update();
	States->update();
	Enemy.treeUpdate();
}

void ENTITY_BOSS::draw(SHADER* shader) {
	Enemy.draw(shader);
}

void ENTITY_BOSS::damage(int damage) {
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->playSound(SoundDamage, Pos);
	IdelTimeBoost = Enemy.hitPoint().ratio();//BOSSはHP少なくなるとIDEL短くなる
	Enemy.damage(damage);
	if (Enemy.hitPoint().isDead()) {
		if (!IsDeath) {//deathを一回しか呼ばないようにする
			BossFlash.startPlay(centerPos());
			IsDeath = true;
		}
	}
}

void ENTITY_BOSS::death(){
	Enemy.death();
}

void ENTITY_BOSS::hit(COLLISION* entity){
	if (IsBodyBlow) {
		entity->entity()->damage(BodyBlowDamage);
	}
}

void ENTITY_BOSS::hpGaugeUpdate(){
	Enemy.hpGaugeUpdate();
	BossHpGauge.hpGaugeUpdate(Enemy.hitPoint());
}

ENTITY_TYPE ENTITY_BOSS::entityType()const {
	return ENTITY_TYPE::BOSS;
}


