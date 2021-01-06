#pragma once
#include "../Library/VECTOR3.h"
class CONTAINER;
class COLLISION_TERRAIN;
class CAMERA_FOLLOW {
public:
	CAMERA_FOLLOW(CONTAINER* container, const VECTOR3* pos);
	~CAMERA_FOLLOW();
	void update(MATRIX* view);
	//カメラの位置を設定
	void setViewPos(const VECTOR3* pos);
	//埋まらないための地形を設定
	void setTerrain(const COLLISION_TERRAIN* terrain) { Terrain = terrain; }
	//視点感度を設定
	void setAimSensitivity(float aimSensitivity) {AimSensitivity = aimSensitivity;}
	//trueでカメラが自動で回る
	void setAutoRotate(bool isAutoRotate);
	//カメラが向いてるベクトル（正規化されてない）
	VECTOR3 lookDirection()const { return LookatPos - CameraPos; }
	//カメラの位置
	VECTOR3 cameraPos() const { return CameraPos; }
	//垂直の角度
	float verticalRad()const;
	//水平の角度
	float horizontalRad()const;
	//押出
	void pushOut(const VECTOR3& vec);
private:
	VECTOR3 CameraPos;
	VECTOR3 LookatPos;
	float VerticalRad = 0.0f;
	float VerticalRadLimmitHigh = 0.0f;
	float VerticalRadLimmitLow = 0.0f;
	float HorizontalRad = 0.0f;
	float RotateSpeed = 0.0f;
	float AimSensitivity = 0.0f;
	VECTOR3 Offset;
	float Distance = 0.0f;
	const VECTOR3* ViewPos = nullptr;
	const COLLISION_TERRAIN* Terrain = nullptr;
	bool IsAutoRotate = false;
	float AutoRotateSpeed = 0.0f;
};

