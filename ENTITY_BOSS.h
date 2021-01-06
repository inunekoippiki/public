#pragma once
#include "../Library/TREE.h"
#include "ENTITY_ENEMY.h"
#include "ENTITY.h"
#include "BOSS_GAUGE.h"
#include "BOSS_FLASH.h"
class SHADER;
class COLLISION;
class SOUND;
class ANIMATION;
class ENTITY_BOSS :public ENTITY {
public:
	ENTITY_BOSS();
	~ENTITY_BOSS();
	void create();
	void update() override;
	void draw(SHADER* shader) override;
	void damage(int damage);
	void death();
	void hit(COLLISION* entity) override;
	void hpGaugeUpdate();
	void bodyBlowStart() { IsBodyBlow = true; }
	void bodyBlowEnd() { IsBodyBlow = false; }
	ENTITY_TYPE entityType()const;
	//ÉQÉbÉ^Å[
	ENTITY_ENEMY* enemy() { return &Enemy; }
	float moveSpeed() { return MoveSpeed; }
	int moveTime() { return MoveTime; }
	int bodyBlowDamage() {return BodyBlowDamage; }
	int attackDamage1() {return AttackDamage1; }
	float laserSize() { return LaserSize; }
	float laserLength() { return LaserLength; }
	int laserLifeTime() { return LaserLifeTime; }
	int attackDamage2() {return AttackDamage2; }
	float attack2BulletFluctuation() { return Attack2BulletFluctuation; }
	float bulletSpeed() { return BulletSpeed; }
	float bulletSize() { return BulletSize; }
	int activateFrame_Attack1() { return ActivateFrame_Attack1; }
	int activateFrame_Attack2() { return ActivateFrame_Attack2; }
	int idelTime() { return IdelTime; }
	float idelTimeBoost() { return IdelTimeBoost; }

	ANIMATION* anim_Idel() {return Anim_Idel; }
	ANIMATION* anim_Attack1() {return Anim_Attack1; }
	ANIMATION* anim_Attack2() {return Anim_Attack2; }
	ANIMATION* anim_Move() {return Anim_Move; }
	ANIMATION* anim_Down() {return Anim_Down; }
	float toAnim_Idel() {return ToAnim_Idel; }
	float toAnim_Attack1() {return ToAnim_Attack1; }
	float toAnim_Attack2() {return ToAnim_Attack2; }
	float toAnim_Move() {return ToAnim_Move; }
	float toAnim_Down() {return ToAnim_Down; }
	float animSpeed_Idel() { return AnimSpeed_Idel; }
	float animSpeed_Attack1() { return AnimSpeed_Attack1; }
	float animSpeed_Attack2() { return AnimSpeed_Attack2; }
	float animSpeed_Move() { return AnimSpeed_Move; }
	float animSpeed_Down() { return AnimSpeed_Down; }
	int animEndFrame_Idel() {return AnimEndFrame_Idel; }
	int animEndFrame_Attack1() {return AnimEndFrame_Attack1; }
	int animEndFrame_Attack2() {return AnimEndFrame_Attack2; }
	int animEndFrame_Move() {return AnimEndFrame_Move; }
	int animEndFrame_Down() {return AnimEndFrame_Down; }

	SOUND* soundAppear() { return SoundAppear; }
	SOUND* soundAttack1() { return SoundAttack1; }
	SOUND* soundAttack2() { return SoundAttack2; }
	SOUND* soundBodyBlow() { return SoundBodyBlow; }
	SOUND* soundDamage() { return SoundDamage; }
	SOUND* soundDown() { return SoundDown; }
private:
	ENTITY_ENEMY Enemy;

	COLLISION* Collision = nullptr;

	bool IsDeath = false;
	float MoveSpeed = 0;
	int MoveTime = 0;
	int BodyBlowDamage = 0;
	bool IsBodyBlow = false;
	int AttackDamage1 = 0;
	float LaserSize = 0.0f;
	float LaserLength = 0.0f;
	int LaserLifeTime = 0;
	int AttackDamage2 = 0;
	float Attack2BulletFluctuation = 0.0f;
	float BulletSpeed = 0.0f;
	float BulletSize = 0.0f;
	int ActivateFrame_Attack1 = 0;
	int ActivateFrame_Attack2 = 0;
	int IdelTime = 0;
	float IdelTimeBoost = 0.0f;

	ANIMATION* Anim_Idel = nullptr;
	ANIMATION* Anim_Attack1 = nullptr;
	ANIMATION* Anim_Attack2 = nullptr;
	ANIMATION* Anim_Move = nullptr;
	ANIMATION* Anim_Down = nullptr;
	float ToAnim_Idel = 0;
	float ToAnim_Attack1 = 0;
	float ToAnim_Attack2 = 0;
	float ToAnim_Move = 0;
	float ToAnim_Down = 0;
	float AnimSpeed_Idel = 0;
	float AnimSpeed_Attack1 = 0;
	float AnimSpeed_Attack2 = 0;
	float AnimSpeed_Move = 0;
	float AnimSpeed_Down = 0;
	int AnimEndFrame_Idel = 0;
	int AnimEndFrame_Attack1 = 0;
	int AnimEndFrame_Attack2 = 0;
	int AnimEndFrame_Move = 0;
	int AnimEndFrame_Down = 0;

	SOUND* SoundAppear = nullptr;
	SOUND* SoundAttack1 = nullptr;
	SOUND* SoundAttack2 = nullptr;
	SOUND* SoundBodyBlow = nullptr;
	SOUND* SoundDamage = nullptr;
	SOUND* SoundDown = nullptr;

	BOSS_GAUGE BossHpGauge;
	BOSS_FLASH BossFlash;
};

