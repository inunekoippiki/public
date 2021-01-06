#pragma once
#include "../Library/TREE.h"
#include "ENTITY.h"
#include "HP_GAUGE.h"
class SHADER;
class UPGRADE;
class ENTITY_PLAYER;
class TREE_ORIGIN;
class ENTITY_ENEMY{
public:
	ENTITY_ENEMY();
	~ENTITY_ENEMY();
	void create(ENTITY* owner,const VECTOR3& upperPosOffest,const TREE_ORIGIN* treeOrigin,int maxHp,float gravity);
	//モデルをアップデートする
	void treeUpdate();
	//ダメージを与える
	void damage(int damage);
	//重力のアップデート
	void gravityUpdate();
	//描画
	void draw(SHADER* shader);
	//HPゲージの位置を更新する
	void hpGaugeUpdate();
	//HPゲージの幅を更新する
	void hpGaugeWidthUpdate();
	//killする
	void death() { IsDeath = true; }
	//消滅前の点滅のアップデート
	void DisappearUpdate(int DisappearCnt);
	//点滅させるフラグを設定
	void setIsDisappear(bool isDisappear) { IsDisappear = isDisappear; };
	//モデル
	TREE* tree() { return &Tree; }
	//点滅の間隔
	int disappearTime() { return DisappearTime; }
	//既に死んでいるか
	bool isDeath() { return IsDeath; }
	//かかる重力
	float gravity() { return Gravity; }
	//頭上の座標
	VECTOR3 upperPos();
	//体力
	const HIT_POINT& hitPoint() { return HitPoint; }
private:
	ENTITY* Owner = nullptr;
	TREE Tree;
	VECTOR3 UpperPosOffest;
	HIT_POINT HitPoint;
	int DisappearTime = 0;//死んでから消滅までの時間
	int DisappearFrequency = 0;//点滅の頻度
	bool IsDisappear = false;//死んでから消えるまで点滅させる為の描画しないフラグ
	bool IsDeath = false;//Hpが０で倒されたフラグ
	float Gravity = 0.0f;
	HP_GAUGE HpGauge;

public:
	static void setUpgrade(UPGRADE* upgrade) { Upgrade = upgrade; }
	static void setPlayer(ENTITY_PLAYER* player) { Player = player; }
	static ENTITY_PLAYER* player() { return Player; }
private:
	static UPGRADE* Upgrade;//与えたダメージの累計をこいつが持ってる
	static ENTITY_PLAYER* Player;
};

