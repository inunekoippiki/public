#pragma once
#include "../Library/VECTOR3.h"
class CONTAINER;
class COLLISION_TERRAIN;
class CAMERA_FOLLOW {
public:
	CAMERA_FOLLOW(CONTAINER* container, const VECTOR3* pos);
	~CAMERA_FOLLOW();
	void update(MATRIX* view);
	//�J�����̈ʒu��ݒ�
	void setViewPos(const VECTOR3* pos);
	//���܂�Ȃ����߂̒n�`��ݒ�
	void setTerrain(const COLLISION_TERRAIN* terrain) { Terrain = terrain; }
	//���_���x��ݒ�
	void setAimSensitivity(float aimSensitivity) {AimSensitivity = aimSensitivity;}
	//true�ŃJ�����������ŉ��
	void setAutoRotate(bool isAutoRotate);
	//�J�����������Ă�x�N�g���i���K������ĂȂ��j
	VECTOR3 lookDirection()const { return LookatPos - CameraPos; }
	//�J�����̈ʒu
	VECTOR3 cameraPos() const { return CameraPos; }
	//�����̊p�x
	float verticalRad()const;
	//�����̊p�x
	float horizontalRad()const;
	//���o
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

