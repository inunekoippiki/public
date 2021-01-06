#include "../Library/CONTAINER.h"
#include "../Library/MATRIX.h"
#include "../Library/DATA.h"
#include "../Library/INDEV.h"
#include "DATA_LIB.h"
#include "EFFEKSSER.h"
#include "ENTITY_STATES.h"
#include "COLLISION_SPHERES.h"
#include "ENTITY_PLAYER_STATE_AVOID.h"
#include "ENTITY_PLAYER_STATE_DOWN.h"
#include "ENTITY_PLAYER_STATE_IDEL.h"
#include "ENTITY_PLAYER_STATE_MELEE.h"
#include "ENTITY_PLAYER_STATE_MOVE.h"
#include "ENTITY_PLAYER_STATE_SHOT.h"
#include "ENTITY_PLAYER_STATE_SKILL1.h"
#include "ENTITY_PLAYER_STATE_SKILL2.h"
#include "ENTITY_PLAYER_STATE_SKILL3.h"
#include "COLLISION_MANAGER.h"
#include "BILLBOARD_ENTITY_LIGHT_BULLET.h"
#include "ENTITY_MANAGER.h"
#include "BILLBOARDS.h"
#include "ENTITY_ENEMY.h"
#include "UPGRADE.h"
#include "UI_3D_CENTERED.h"
#include "INPUT_COMMON.h"
#include "UI_DRAWER_FACTORY.h"
#include "UI_MANAGER.h"
#include "ENTITY_PLAYER.h"
ENTITY_PLAYER::ENTITY_PLAYER() {
}

ENTITY_PLAYER::~ENTITY_PLAYER() {
	Collision->Delete();
	UiLockOn->Delete();
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	sm->stopSound(SoundFootStep);
}

void ENTITY_PLAYER::create(){
	CONTAINER* c = gameDataCommon()->container();
	//コリジョン設定
	COLLISION_SPHERES* p = new COLLISION_SPHERES(this, posPtr());
	p->add(VECTOR3(0.0f, c->data("ENTITY_PLAYER::CollisionOffest1.y"), 0.0f),
		c->data("ENTITY_PLAYER::CollisionRadius1"));
	p->add(VECTOR3(0.0f, c->data("ENTITY_PLAYER::CollisionOffest2.y"), 0.0f),
		c->data("ENTITY_PLAYER::CollisionRadius2"));
	Collision = p;
	collisionManager()->addCollisionPlayer(Collision);
	//モデル設定
	Tree = c->treeOrigin("Noa1");
	TreeSword = c->treeOrigin("sword");
	TreeSwordScale = DATA_LIB::vector3(c, "ENTITY_PLAYER::TreeSwordScale");
	//初期値設定
	CenterPosOffest.y = c->data("ENTITY_PLAYER::CenterPosOffset.y");
	MoveSpeed = c->data("ENTITY_PLAYER::MoveSpeed");
	MaxHp = c->data("ENTITY_PLAYER::MaxHp");
	Hp = MaxHp;
	MaxSp = c->data("ENTITY_PLAYER::MaxSp");
	Sp = MaxSp;
	SpNaturalRecoveryAmount = c->data("ENTITY_PLAYER::SpNaturalRecoveryAmount");
	SpDamageRecoveryAmount = c->data("ENTITY_PLAYER::SpDamageRecoveryAmount");
	MoveSpeedBoost = 1.0f;
	MoveSpeedSkillBoost = 1.0f;
	AvoidSpeed = c->data("ENTITY_PLAYER::AvoidSpeed");
	AttackRange = c->data("ENTITY_PLAYER::AttackRange");
	AttackRangeBoost = 1.0f;
	AttackSpeed = c->data("ENTITY_PLAYER::AttackSpeed");
	AttackSpeedBoost = 1.0f;
	AttackDamage = c->data("ENTITY_PLAYER::AttackDamage");
	AttackDamageBoost = 1.0f;
	AttackDamageSkillBoost = 1.0f;
	ProximityAttackDamageBoost = c->data("ENTITY_PLAYER::ProximityAttackDamageBoost");
	Skill1SpCost = c->data("ENTITY_PLAYER::Skill1SpCost");
	Skill2SpCost = c->data("ENTITY_PLAYER::Skill2SpCost");
	Skill3SpCost = c->data("ENTITY_PLAYER::Skill3SpCost");

	Skill1Time = c->data("ENTITY_PLAYER::Skill1Time");
	Skill2Time = c->data("ENTITY_PLAYER::Skill2Time");
	InvincibleTime = c->data("ENTITY_PLAYER::InvincibleTime");
	BulletSpeed = c->data("ENTITY_PLAYER::BulletSpeed");
	BulletSize = c->data("ENTITY_PLAYER::BulletSize");

	ActivateFrame_Skill = c->data("ENTITY_PLAYER::ActivateFrame_Skill");
	ActivateFrame_Melle = c->data("ENTITY_PLAYER::ActivateFrame_Melle");
	ActivateFrame_Shot = c->data("ENTITY_PLAYER::ActivateFrame_Shot");
	ActivateEndFrame_Avoid = c->data("ENTITY_PLAYER::ActivateEndFrame_Avoid");
	TargetAngleRange = c->data("ENTITY_PLAYER::TargetAngleRange");
	Gravity = c->data("ENTITY_PLAYER::Gravity");
	WalkInertia = c->data("ENTITY_PLAYER::WalkInertia");

	Anim_Avoid = c->animation("Noa_kaihi");
	Anim_Idel = c->animation("Noa_tuuzyou");
	Anim_Melee = c->animation("Noa_kinnsetukougeki");
	Anim_Move = c->animation("Noa_hasiru");
	Anim_Shot = c->animation("Noa_syageki");
	Anim_Skill = c->animation("Noa_skill");
	Anim_Down = c->animation("Noa_down");
	ToAnim_avoid = c->data("ToAnim_Noa_avoid");
	ToAnim_idel = c->data("ToAnim_Noa_idel");
	ToAnim_melee = c->data("ToAnim_Noa_melee");
	ToAnim_move = c->data("ToAnim_Noa_move");
	ToAnim_shot = c->data("ToAnim_Noa_shot");
	ToAnim_skill = c->data("ToAnim_Noa_skill");
	ToAnim_down = c->data("ToAnim_Noa_down");
	AnimSpeed_Avoid = c->data("AnimSpeed_Noa_avoid");
	AnimSpeed_Idel = c->data("AnimSpeed_Noa_idel");
	AnimSpeed_Melee = c->data("AnimSpeed_Noa_melee");
	AnimSpeed_Move = c->data("AnimSpeed_Noa_move");
	AnimSpeed_Shot = c->data("AnimSpeed_Noa_shot");
	AnimSpeed_Skill = c->data("AnimSpeed_Noa_skill");
	AnimSpeed_Down = c->data("AnimSpeed_Noa_down");
	AnimEndFrame_Avoid = c->data("AnimEndFrame_Noa_avoid");
	AnimEndFrame_Idel = c->data("AnimEndFrame_Noa_idel");
	AnimEndFrame_Melee = c->data("AnimEndFrame_Noa_melee");
	AnimEndFrame_Move = c->data("AnimEndFrame_Noa_move");
	AnimEndFrame_Shot = c->data("AnimEndFrame_Noa_shot");
	AnimEndFrame_Skill = c->data("AnimEndFrame_Noa_skill");
	AnimEndFrame_Down = c->data("AnimEndFrame_Noa_down");

	SoundAvoid = c->sound("noa_avoid");
	SoundDamage = c->sound("noa_damage");
	SoundDown = c->sound("noa_down");
	SoundFootStep = c->sound("noa_footStep");
	SoundMelle = c->sound("noa_melle");
	SoundShot = c->sound("noa_shot");
	SoundSkill1 = c->sound("noa_skill1");
	SoundSkill2 = c->sound("noa_skill2");
	SoundSkill3 = c->sound("noa_skill3");
	SoundSkillChange = c->sound("noa_skillChange");
	//UI設定
	UiLockOn = new UI_3D_CENTERED();
	UiLockOn->setDrawer(UI_DRAWER_FACTORY::instance(c, "lockOn"));
	UiLockOn->setScale(DATA_LIB::vector2(c, "ENTITY_PLAYER::UiLockOnScale"));
	uiManager()->add(UiLockOn, c->data("ENTITY_PLAYER::UiLockOnPriority"));
	//エフェクト
	AttackBufHandle = -1;
	SpeedBufHandle = -1;
	EffectBufAppearInterval = c->data("ENTITY_PLAYER::EffectBufAppearInterval");
	//ステート設定
	States->regist(new ENTITY_PLAYER_STATE_AVOID(this));
	States->regist(new ENTITY_PLAYER_STATE_DOWN(this));
	States->regist(new ENTITY_PLAYER_STATE_IDEL(this));
	States->regist(new ENTITY_PLAYER_STATE_MELEE(this));
	States->regist(new ENTITY_PLAYER_STATE_MOVE(this));
	States->regist(new ENTITY_PLAYER_STATE_SHOT(this));
	States->regist(new ENTITY_PLAYER_STATE_SKILL1(this));
	States->regist(new ENTITY_PLAYER_STATE_SKILL2(this));
	States->regist(new ENTITY_PLAYER_STATE_SKILL3(this));
	States->change("IDEL");

	ENTITY_ENEMY::setPlayer(this);
}

void ENTITY_PLAYER::loadStatus(UPGRADE* upgrade){
	MaxHp = upgrade->maxHp()->lvlValue();
	Hp = MaxHp;
	MoveSpeedBoost = upgrade->moveSpeedBoost()->lvlValue();
	MoveSpeedSkillBoost = upgrade->moveSpeedSkillBoost()->lvlValue();
	AttackRangeBoost = upgrade->attackRangeBoost()->lvlValue();
	AttackSpeedBoost = upgrade->attackSpeedBoost()->lvlValue();
	AttackDamageBoost = upgrade->attackDamageBoost()->lvlValue();
	AttackDamageSkillBoost = upgrade->attackDamageSkillBoost()->lvlValue();
	HealPower = upgrade->healPower()->lvlValue();

}

void ENTITY_PLAYER::update(){
	treeUpdate();
	FindTargetEntity();
	UiLockOn->setPos(targetPos());
	//スキルポイントの加算
	Sp += SpNaturalRecoveryAmount;
	if (Sp > MaxSp) {
		Sp = MaxSp;
	}
	//スキルタイマーのカウント
	if (Skill1Cnt-- < 0) {
		SkillEndAttackBoost();
	}
	else{
		if (Skill1Cnt % EffectBufAppearInterval == EffectBufAppearInterval-1) {
			AttackBufHandle = effeksser()->play("AttackBuf", Pos);
		}
		effeksser()->setPos(AttackBufHandle, Pos);
	}
	if (Skill2Cnt-- < 0) {
		SkillEndMoveSpeedBoost();
	}
	else{
		if (Skill2Cnt % EffectBufAppearInterval == EffectBufAppearInterval - 1) {
			SpeedBufHandle= effeksser()->play("SpeedBuf", Pos);
		}
		effeksser()->setPos(SpeedBufHandle, Pos);
	}
	//被弾時無敵時間のカウント
	if (InvincibleCnt-- < 0) {
		InvincibleCnt = 0;
	}
	INDEV* in = INDEV::instance();
	States->update();
}

void ENTITY_PLAYER::treeUpdate(){
	MATRIX world;
	world.mulTranslate(Pos);
	world.mulRotateY(Rad.y);
	Tree.update(world);
	MATRIX swordWorld = *Tree.nodeWorld("locator1");
	swordWorld.mulScale(TreeSwordScale);
	TreeSword.update(swordWorld);
}

void ENTITY_PLAYER::draw(SHADER* shader){
	Tree.draw(shader);
	TreeSword.draw(shader);
}

void ENTITY_PLAYER::hit(COLLISION* entity){

}

void ENTITY_PLAYER::hit(const VECTOR3& pushBack){
	ENTITY::hit(pushBack);
	if (pushBack.y > 0.0) {
		Velo.y = 0;
	}
}

void ENTITY_PLAYER::damage(int damage){
	SOUND_MANAGER* sm = SOUND_MANAGER::instance();
	if (!IsAvoid && InvincibleCnt <= 0) {
		Hp -= damage;
		sm->playSound(SoundDamage);
		InvincibleCnt = InvincibleTime;
		if (Hp < 0) {
			Hp = 0;
		}
	}
}

void ENTITY_PLAYER::damageDealt(int damage){
	Sp += (int)(damage * SpDamageRecoveryAmount);
	if (Sp > MaxSp) {
		Sp = MaxSp;
	}
}

void ENTITY_PLAYER::FindTargetEntity(){
	//プレイヤーの視点の直線との距離が一番近いENEMYを見つける
	TargetEntity = entityManager()->whereMin([=](const ENTITY* e)->float {
		if (!(e->entityType() == ENTITY_TYPE::MEDAMA||
			e->entityType() == ENTITY_TYPE::HANA||
			e->entityType() == ENTITY_TYPE::BOSS)) {
			return FLT_MAX;
		}
		VECTOR3 v = e->pos() - camera()->cameraPos();
		VECTOR3 pv = normalize(camera()->lookDirection());
		float h = dot(pv, v);
		if (h < 0.0f) {
			return FLT_MAX;
		}
		float angle = acosf(h / (length(v)));
		if (angle > TargetAngleRange) {
			return FLT_MAX;
		}
		return angle;
	});
}

void ENTITY_PLAYER::Melle(){
	int giveDamage = (int)(AttackDamage * AttackDamageBoost * ProximityAttackDamageBoost);
	if (Skill1Cnt > 0)giveDamage = (int)(giveDamage * AttackDamageSkillBoost);
	float attackRange = AttackRange * AttackRangeBoost;
	VECTOR3 attackPos = pos() + VECTOR3(sinf(Rad.y) * attackRange, centerPos().y, cosf(Rad.y) * attackRange);
	ENTITY::entityManager()->appearPlayerMelee(attackPos,
		attackRange,
		giveDamage);
	Effekseer::Handle h = effeksser()->play("test", attackPos);
	VECTOR3 scale = VECTOR3(0.3f, 0.3f, 0.3f) * attackRange;
	effeksser()->setRotation(h, Rad);
	effeksser()->setScale(h, scale);
	effeksser()->setPos(h, attackPos);
}

void ENTITY_PLAYER::Shot(){
	const MATRIX* shotPointWorld = tree()->nodeWorld("locator2");
	VECTOR3 shotPoint = VECTOR3(shotPointWorld->_14, shotPointWorld->_24, shotPointWorld->_34);
	int giveDamage = (int)(AttackDamage * AttackDamageBoost) ;
	if (Skill1Cnt > 0)giveDamage = (int)(giveDamage * AttackDamageSkillBoost);
	ENTITY::entityManager()->appearPlayerShot(shotPoint,
		normalize(targetPos() - shotPoint) * BulletSpeed,
		BulletSize,
		giveDamage);
}

void ENTITY_PLAYER::SkillTypeChange(){
	SkillChoiceType++;
	if (SkillChoiceType >= 3) {
		SkillChoiceType = 0;
	}
}

void ENTITY_PLAYER::SkillTypeChange(int SkillType){
	SkillChoiceType = SkillType;
}

bool ENTITY_PLAYER::SkillActivateAttackBoost(){
	if (Skill1SpCost <= Sp) {
		Skill1Cnt = Skill1Time;
		Sp -= Skill1SpCost;
		return true;
	}
	return false;
}

void ENTITY_PLAYER::SkillEndAttackBoost(){
	Skill1Cnt = 0;
}

bool ENTITY_PLAYER::SkillActivateMoveSpeedBoost(){
	if (Skill2SpCost <= Sp) {
		Skill2Cnt = Skill2Time;
		Sp -= Skill2SpCost;
		return true;
	}
	return false;
}

void ENTITY_PLAYER::SkillEndMoveSpeedBoost(){
	Skill2Cnt = 0;
}

bool ENTITY_PLAYER::SkillActivateHeal(){
	if (Skill3SpCost <= Sp) {
		Hp += HealPower;
		if (Hp > MaxHp) {
			Hp = MaxHp;
		}
		Sp -= Skill3SpCost;
		return true;
	}
	return false;
}

ENTITY_TYPE ENTITY_PLAYER::entityType()const {
	return ENTITY_TYPE::PLAYER;
}

VECTOR3 ENTITY_PLAYER::targetPos(){
	if (TargetEntity != nullptr) {
		return TargetEntity->centerPos();
	}
	return camera()->cameraPos() + normalize(camera()->lookDirection())*10.0f;
}


