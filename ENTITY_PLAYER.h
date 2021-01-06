#pragma once
#include <vector>
#include "../Effekseer/Effekseer.h"
#include "../Library/TREE.h"
#include "ENTITY.h"
#include "ENTITY_STATES.h"
#include "ENTITY_PLAYER.h"
class COLLISION;
class UPGRADE;
class UI_3D_CENTERED;
class SOUND;
class CAMERA_FOLLOW;
class ENTITY_PLAYER:public ENTITY{
public:
	ENTITY_PLAYER();
	~ENTITY_PLAYER();
	void create();
	void loadStatus(UPGRADE* upgrade);
	void update() override;
	void treeUpdate();
	void draw(SHADER* shader)override;
	void hit(COLLISION* entity);
	void hit(const VECTOR3& pushBack);
	void damage(int damage);
	void damageDealt(int damage);
	void FindTargetEntity();
	void Melle();
	void Shot();
	void SkillTypeChange();
	void SkillTypeChange(int SkillType);
	bool SkillActivateAttackBoost();
	void SkillEndAttackBoost();
	bool SkillActivateMoveSpeedBoost();
	void SkillEndMoveSpeedBoost();
	bool SkillActivateHeal();
	//�Q�b�^�[
	TREE* tree() { return &Tree; }
	ENTITY_TYPE entityType()const;
	ENTITY* targetEntity() { return TargetEntity; }
	CAMERA_FOLLOW* camera() {return Camera; }
	VECTOR3 targetPos();
	int hp() { return Hp; }
	int maxHp() { return MaxHp; }
	int sp() { return Sp; }
	int maxSp() { return MaxSp; }
	int skillChoiceType() { return SkillChoiceType; }
	float moveSpeed() { return MoveSpeed; }
	float moveSpeedBoost() { return MoveSpeedBoost; }
	float moveSpeedSkillBoost() { return MoveSpeedSkillBoost; }
	float attackRange() { return AttackRange; }
	float attackSpeed() { return AttackSpeed; }
	float attackSpeedBoost() { return AttackSpeedBoost; }
	float attackDamage() { return AttackDamage; }
	float attackDamageBoost() { return AttackDamageBoost; }
	float proximityAttackDamageBoost() { return ProximityAttackDamageBoost; }
	int skill1Cnt() { return Skill1Cnt; }
	int skill2Cnt() { return Skill2Cnt; }
	float avoidSpeed() { return AvoidSpeed; }
	int activateFrame_Skill(){ return ActivateFrame_Skill;}
	int activateFrame_Melle(){ return ActivateFrame_Melle;}
	int activateFrame_Shot(){ return ActivateFrame_Shot;}
	int activateEndFrame_Avoid(){ return ActivateEndFrame_Avoid;}
	float gravity() { return Gravity; }
	float walkInertia() { return WalkInertia; }
	bool isAvoid() { return IsAvoid; }


	ANIMATION* anim_Avoid(){ return Anim_Avoid;}
	ANIMATION* anim_Idel() { return Anim_Idel; }
	ANIMATION* anim_Melee(){ return Anim_Melee;}
	ANIMATION* anim_Move(){ return Anim_Move;}
	ANIMATION* anim_Shot(){ return Anim_Shot;}
	ANIMATION* anim_Skill() { return Anim_Skill; }
	ANIMATION* anim_Down(){ return Anim_Down;}
	float toAnim_avoid() { return ToAnim_avoid; }
	float toAnim_idel() { return ToAnim_idel; }
	float toAnim_melee() { return ToAnim_melee; }
	float toAnim_move() { return ToAnim_move; }
	float toAnim_shot() { return ToAnim_shot; }
	float toAnim_skill() { return ToAnim_skill; }
	float toAnim_down() { return ToAnim_down; }
	float animSpeed_Avoid() { return AnimSpeed_Avoid; }
	float animSpeed_Idel() { return AnimSpeed_Idel; }
	float animSpeed_Melee() { return AnimSpeed_Melee; }
	float animSpeed_Move() { return AnimSpeed_Move; }
	float animSpeed_Shot() { return AnimSpeed_Shot; }
	float animSpeed_Skill() { return AnimSpeed_Skill; }
	float animSpeed_Down() { return AnimSpeed_Down; }
	int animEndFrame_Avoid() { return AnimEndFrame_Avoid; }
	int animEndFrame_Idel() { return AnimEndFrame_Idel; }
	int animEndFrame_Melee() { return AnimEndFrame_Melee; }
	int animEndFrame_Move() { return AnimEndFrame_Move; }
	int animEndFrame_Shot() { return AnimEndFrame_Shot; }
	int animEndFrame_Skill() { return AnimEndFrame_Skill; }
	int animEndFrame_Down() { return AnimEndFrame_Down; }

	SOUND* soundAvoid() { return SoundAvoid; }
	SOUND* soundDamage() { return SoundDamage; }
	SOUND* soundDown() { return SoundDown; }
	SOUND* soundFootStep() { return SoundFootStep; }
	SOUND* soundMelle() { return SoundMelle; }
	SOUND* soundShot() { return SoundShot; }
	SOUND* soundSkill1() { return SoundSkill1; }
	SOUND* soundSkill2() { return SoundSkill2; }
	SOUND* soundSkill3() { return SoundSkill3; }
	SOUND* soundSkillChange() { return SoundSkillChange; }

	//�Z�b�^�[
	void setTargetEntity(ENTITY* entity) { TargetEntity = entity; }
	void setIsAvoid(bool isAvoid) { IsAvoid = isAvoid; }
	void setCamera(CAMERA_FOLLOW* camera) { Camera = camera; }
private:
	ENTITY* TargetEntity = nullptr;
	COLLISION* Collision = nullptr;
	CAMERA_FOLLOW* Camera = nullptr;
	TREE Tree;
	TREE TreeSword;
	VECTOR3 TreeSwordScale;
	UI_3D_CENTERED* UiLockOn = nullptr;
	Effekseer::Handle AttackBufHandle = 0;
	Effekseer::Handle SpeedBufHandle = 0;
	int EffectBufAppearInterval = 0;

	int MaxHp = 0;
	int Hp = 0;
	int MaxSp = 0;
	int Sp = 0;
	int SpNaturalRecoveryAmount = 0;//Sp�̂P�t���[���񕜗�
	float SpDamageRecoveryAmount = 0;//�I�Ƀ_���[�W��^�����Ƃ���Sp�񕜗ʁi�P�_���[�W�ɂ�����j
	int SkillChoiceType = 0;//0,1,2
	float MoveSpeed = 0.0f;//��{�ړ����x
	float MoveSpeedBoost = 0.0f;//�ړ����x�{��
	float MoveSpeedSkillBoost = 0.0f;//�X�L���ɂ��ړ����x�i������܂�)
	float AttackRange = 0.0f;//��{�U���͈�
	float AttackRangeBoost = 0.0f;//�U���͈͔{��
	float AttackSpeed = 0.0f;//��{�U�����x
	float AttackSpeedBoost = 0.0f;//�U�����x�{��
	float AttackDamage = 0.0f;//��{�U����
	float AttackDamageBoost = 0.0f;//�U���͔{��
	float AttackDamageSkillBoost = 0.0f;//�X�L���ɂ��U���͔{��
	float ProximityAttackDamageBoost = 0;//�ߐڔ{��
	int HealPower = 0;//�񕜗�
	int Skill1SpCost = 0;//�U���̓u�[�X�g�̏���Sp
	int Skill2SpCost = 0;//�ړ����x�u�[�X�g�̏���Sp
	int Skill3SpCost = 0;//�񕜂̏���Sp
	int Skill1Time = 0;//�U���̓u�[�X�g�̌��ʎ���
	int Skill1Cnt = 0;//�U���̓u�[�X�g
	int Skill2Time = 0;//�ړ����x�u�[�X�g�̌��ʎ���
	int Skill2Cnt = 0;//�ړ����x�u�[�X�g
	int InvincibleTime = 0;//�_���[�W��H������ۂ̖��G����
	int InvincibleCnt = 0;
	float AvoidSpeed = 0.0f;
	bool IsAvoid = false;//true�Ń_���[�W����
	float BulletSpeed = 0.0f;
	float BulletSize = 0.0f;
	int ActivateFrame_Skill = 0;
	int ActivateFrame_Melle = 0;
	int ActivateFrame_Shot = 0;
	int ActivateEndFrame_Avoid = 0;
	float TargetAngleRange = 0.0f;//���b�N�I������鎋��p
	float Gravity = 0.0f;
	float WalkInertia = 0.0f;

	ANIMATION* Anim_Avoid = nullptr;
	ANIMATION* Anim_Idel = nullptr;
	ANIMATION* Anim_Melee = nullptr;
	ANIMATION* Anim_Move = nullptr;
	ANIMATION* Anim_Shot = nullptr;
	ANIMATION* Anim_Skill = nullptr;
	ANIMATION* Anim_Down = nullptr;
	float ToAnim_avoid = 0;
	float ToAnim_idel = 0;
	float ToAnim_melee = 0;
	float ToAnim_move = 0;
	float ToAnim_shot = 0;
	float ToAnim_skill = 0;
	float ToAnim_down = 0;
	float AnimSpeed_Avoid = 0;
	float AnimSpeed_Idel = 0;
	float AnimSpeed_Melee = 0;
	float AnimSpeed_Move = 0;
	float AnimSpeed_Shot = 0;
	float AnimSpeed_Skill = 0;
	float AnimSpeed_Down = 0;
	int AnimEndFrame_Avoid = 0;
	int AnimEndFrame_Idel = 0;
	int AnimEndFrame_Melee = 0;
	int AnimEndFrame_Move = 0;
	int AnimEndFrame_Shot = 0;
	int AnimEndFrame_Skill = 0;
	int AnimEndFrame_Down = 0;

	SOUND* SoundAvoid = nullptr;
	SOUND* SoundDamage = nullptr;
	SOUND* SoundDown = nullptr;
	SOUND* SoundFootStep = nullptr;
	SOUND* SoundMelle = nullptr;
	SOUND* SoundShot = nullptr;
	SOUND* SoundSkill1 = nullptr;
	SOUND* SoundSkill2 = nullptr;
	SOUND* SoundSkill3 = nullptr;
	SOUND* SoundSkillChange = nullptr;
};

