#pragma once
#include "../Effekseer/Effekseer.h"
class MATRIX;
class VECTOR3;
//�����̃��C�u������EFFEKSEER�̌^��ϊ�����
namespace EFFEKSSER_CONNECT {
	using namespace ::Effekseer;
	Matrix44 cvtMatrix(const MATRIX& m);
	Vector3D cvtVector3D(const VECTOR3& vector3);
}