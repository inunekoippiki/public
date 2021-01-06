#include "BILLBOARD.h"

void BILLBOARD::calcDistance(const VECTOR3& cameraPos, const VECTOR3& lookatVec) {
	VECTOR3 v = Pos - cameraPos;
	Distance = dot(v, lookatVec);
}
