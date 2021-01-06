#include "EFFEKSSER_CONNECT.h"
#include "../Library/MATRIX.h"
#include "../Library/VECTOR3.h"
namespace EFFEKSSER_CONNECT {
	Matrix44 cvtMatrix(const MATRIX& m) {
		Matrix44 ret;
		ret.Values[0][0] = m._11;ret.Values[0][1] = m._12;ret.Values[0][2] = m._13;ret.Values[0][3] = m._14;
		ret.Values[1][0] = m._21;ret.Values[1][1] = m._22;ret.Values[1][2] = m._23;ret.Values[1][3] = m._24;
		ret.Values[2][0] = m._31;ret.Values[2][1] = m._32;ret.Values[2][2] = m._33;ret.Values[2][3] = m._34;
		ret.Values[3][0] = m._41;ret.Values[3][1] = m._42;ret.Values[3][2] = m._43;ret.Values[3][3] = m._44;
		ret.Transpose();
		return ret;
	}

	Vector3D cvtVector3D(const VECTOR3& vector3) {
		return Vector3D(vector3.x, vector3.y, vector3.z);
	}
}