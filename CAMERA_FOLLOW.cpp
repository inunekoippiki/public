#include <math.h>
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/MATRIX.h"
#include "../Library/DEBUG_STR.h"
#include "INPUT_COMMON.h"
#include "COLLISION_TERRAIN.h"
#include "CAMERA_FOLLOW.h"
CAMERA_FOLLOW::CAMERA_FOLLOW(CONTAINER* container, const VECTOR3* pos) {
	VerticalRad = container->data("CAMERA_FOLLOW::VerticalRad");
	VerticalRadLimmitHigh = container->data("CAMERA_FOLLOW::VerticalRadLimmitHigh");
	VerticalRadLimmitLow = container->data("CAMERA_FOLLOW::VerticalRadLimmitLow");
	HorizontalRad = container->data("CAMERA_FOLLOW::HorizontalRad");
	Distance = container->data("CAMERA_FOLLOW::DistanceFromLookatPos");
	RotateSpeed = container->data("CAMERA_FOLLOW::RotateSpeed");
	ViewPos = pos;
	Offset.x = container->data("CAMERA_FOLLOW::Offset.x");
	Offset.y = container->data("CAMERA_FOLLOW::Offset.y");
	Offset.z = container->data("CAMERA_FOLLOW::Offset.z");
	AutoRotateSpeed = container->data("CAMERA_FOLLOW::AutoRotateSpeed");
}

CAMERA_FOLLOW::~CAMERA_FOLLOW() {
}

void CAMERA_FOLLOW::update(MATRIX* view) {
	INPUT_COMMON* in = INPUT_COMMON::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	ds->set("HorizontalRad:%f VerticalRad:%f", HorizontalRad, VerticalRad);
	//見る対象があればそっちを向く
	if (ViewPos != nullptr) {
		LookatPos = *ViewPos;
	}
	if (IsAutoRotate) {	//自動で回るフラグが入っていたら
		HorizontalRad -= AutoRotateSpeed;
	}
	else{
		HorizontalRad -= RotateSpeed * in->aimAxisHorizontal() * AimSensitivity;
		VerticalRad -= RotateSpeed * in->aimAxisVertical() * AimSensitivity;
		//クランプ
		VerticalRad = min(max(VerticalRad, VerticalRadLimmitLow), VerticalRadLimmitHigh);
	}
	//HorizontalRad,VerticalRadからCameraPosを計算
	CameraPos = LookatPos;
	CameraPos.x += sinf(HorizontalRad) * cosf(VerticalRad) * Distance;
	CameraPos.y += sinf(VerticalRad) * Distance;
	CameraPos.z += cosf(HorizontalRad) * cosf(VerticalRad) * Distance;
	//回転に合わせてrotateOffsetを変換
	VECTOR3 rotateOffset;
	MATRIX rotateOffsetM;
	rotateOffsetM.mulRotateY(HorizontalRad);
	rotateOffsetM.mulRotateX(-VerticalRad);
	rotateOffset = rotateOffsetM * Offset;
	//カメラの地形押し出し処理（地形が無かったらやらない）
	if (Terrain != nullptr) {
		pushOut(Terrain->collision(CameraPos + rotateOffset,(LookatPos+VECTOR3(0.0f, rotateOffset.y,0.0f))-(CameraPos+rotateOffset)));
	}
	//rotateOffsetで視点ごとカメラを平行移動
	CameraPos += rotateOffset;
	LookatPos += rotateOffset;
	view->set(CameraPos, LookatPos, VECTOR3(0, 1, 0));
}

void CAMERA_FOLLOW::setViewPos(const VECTOR3* pos) { 	
	ViewPos = pos; 
}

void CAMERA_FOLLOW::setAutoRotate(bool isAutoRotate){
	IsAutoRotate = isAutoRotate;
}

void CAMERA_FOLLOW::pushOut(const VECTOR3& vec){
	CameraPos += vec;
	LookatPos += vec;
}

float CAMERA_FOLLOW::verticalRad() const {
	return VerticalRad;
}

float CAMERA_FOLLOW::horizontalRad()const {
	return HorizontalRad;
}
