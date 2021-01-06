#include <algorithm>
#include "HIT_POINT.h"
HIT_POINT::HIT_POINT() {
}

HIT_POINT::~HIT_POINT() {
}

//É_ÉÅÅ[ÉWÇó^Ç¶ÇÈ
void HIT_POINT::damage(int damage) {
	Hp = std::max(Hp - damage, 0);
}
