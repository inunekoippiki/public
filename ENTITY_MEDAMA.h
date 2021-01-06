#pragma once
#include "../Library/TREE.h"
#include "ENTITY_ENEMY.h"
#include "ENTITY.h"
class SHADER;
class COLLISION;
class SOUND;
class ENTITY_MEDAMA:public ENTITY{
public:
	ENTITY_MEDAMA();
	~ENTITY_MEDAMA();
	void create();
	void update()override;
	void draw(SHADER* shader)override;
	void damage(int damage);
	ENTITY_TYPE entityType()const override;
	//ÉQÉbÉ^Å[
	ENTITY_ENEMY* enemy() { return &Enemy; }
	int attackDamage() { return AttackDamage; }
	int activateFrame_Attack() { return ActivateFrame_Attack; }
	int attackTime() { return AttackTime; }
	int idelTime() { return IdelTime; }
	int moveTime() { return MoveTime; }
	float moveSpeed() { return MoveSpeed; }
	float moveRadCntSpeed() { return MoveRadCntSpeed; }
	int attackInterval() { return AttackInterval; }
	float bulletSpeed() { return BulletSpeed; }
	float bulletSize() { return BulletSize; }
	ANIMATION* anim_Idel() { return Anim_Idel; }
	ANIMATION* anim_Attack() { return Anim_Attack; }
	ANIMATION* anim_Move() { return Anim_Move; }
	ANIMATION* anim_Down() { return Anim_Down; }
	float toAnim_Idel() { return ToAnim_Idel; }
	float toAnim_Attack() { return ToAnim_Attack; }
	float toAnim_Move() { return ToAnim_Move; }
	float toAnim_Down() { return ToAnim_Down; }
	float animSpeed_Idel() { return AnimSpeed_Idel; }
	float animSpeed_Attack() { return AnimSpeed_Attack; }
	float animSpeed_Move() { return AnimSpeed_Move; }
	float animSpeed_Down() { return AnimSpeed_Down; }
	int animEndFrame_Idel() { return AnimEndFrame_Idel; }
	int animEndFrame_Attack() { return AnimEndFrame_Attack; }
	int animEndFrame_Move() { return AnimEndFrame_Move; }
	int animEndFrame_Down() { return AnimEndFrame_Down; }

	SOUND* soundAppear() { return SoundAppear; }
	SOUND* soundAttack() { return SoundAttack; }
	SOUND* soundDamage() { return SoundDamage; }
	SOUND* soundDown() { return SoundDown; }

private:
	ENTITY_ENEMY Enemy;
	COLLISION* Collision = nullptr;
	int AttackDamage = 0;
	int ActivateFrame_Attack = 0;
	int AttackTime = 0;
	int IdelTime = 0;
	int MoveTime = 0;
	float MoveSpeed = 0.0f;
	float MoveRadCntSpeed = 0.0f;
	int AttackInterval = 0;
	float BulletSpeed = 0.0f;
	float BulletSize = 0.0f;
	ANIMATION* Anim_Idel = nullptr;
	ANIMATION* Anim_Attack = nullptr;
	ANIMATION* Anim_Move = nullptr;
	ANIMATION* Anim_Down = nullptr;
	float ToAnim_Idel = 0;
	float ToAnim_Attack = 0;
	float ToAnim_Move = 0;
	float ToAnim_Down = 0;
	float AnimSpeed_Idel = 0;
	float AnimSpeed_Attack = 0;
	float AnimSpeed_Move = 0;
	float AnimSpeed_Down = 0;
	int AnimEndFrame_Idel = 0;
	int AnimEndFrame_Attack = 0;
	int AnimEndFrame_Move = 0;
	int AnimEndFrame_Down = 0;

	SOUND* SoundAppear = nullptr;
	SOUND* SoundAttack = nullptr;
	SOUND* SoundDamage = nullptr;
	SOUND* SoundDown = nullptr;

};

