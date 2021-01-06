#include "../Library/VECTOR3.h"
#include "../Library/CONTAINER.h"
#include "COLLISION_POINT.h"
#include "COLLISION_SPHERE.h"
#include "COLLISION_TERRAIN.h"
#include "COLLISION_SPHERES.h"
#include <cmath>

COLLISION_TERRAIN::COLLISION_TERRAIN(CONTAINER* c) {
	Floor = c->data("COLLISION_TERRAIN::Floor");
	Sx = c->data("COLLISION_TERRAIN::Sx");
	Sz = c->data("COLLISION_TERRAIN::Sz");
	Ex = c->data("COLLISION_TERRAIN::Ex");
	Ez = c->data("COLLISION_TERRAIN::Ez");
}

COLLISION_TERRAIN::~COLLISION_TERRAIN() {

}

VECTOR3 COLLISION_TERRAIN::collision(const COLLISION_SPHERE* sphere)const{
	float overSx = Sx - (sphere->px() - sphere->r());
	float overSz = Sz - (sphere->pz() - sphere->r());
	float overEx = sphere->px() + sphere->r() - Ex;
	float overEz = sphere->pz() + sphere->r() - Ez;
	float overY = Floor - (sphere->py() - sphere->r());
	VECTOR3 v;
	if (overSx>0) {
		v.x = overSx;
	}
	if (overSz > 0) {
		v.z = overSz;
	}
	if (overEx > 0) {
		v.x = -overEx;
	}
	if (overEz > 0) {
		v.z = -overEz;
	}
	if (overY > 0) {
		v.y = overY;
	}
	return v;
}

VECTOR3 COLLISION_TERRAIN::collision(const COLLISION_SPHERES* spheres) const{
	VECTOR3 v;
	for (auto& i : spheres->spheres()) {
		float px = i.OffsetPos.x + spheres->px();
		float pz= i.OffsetPos.z + spheres->pz();
		float overSx = Sx - (px - i.R);
		float overSz = Sz - (pz - i.R);
		float overEx = px + i.R - Ex;
		float overEz = pz + i.R - Ez;
		float overY = Floor - (i.OffsetPos.y+spheres->py() - i.R);
		VECTOR3 _v;
		if (overSx > 0) {
			v.x = overSx;
		}
		if (overSz > 0) {
			v.z = overSz;
		}
		if (overEx > 0) {
			v.x = -overEx;
		}
		if (overEz > 0) {
			v.z = -overEz;
		}
		if (overY > 0) {
			if (overY > _v.y) {
				v.y = overY;
			}
		}
		if (abs(v.x) < abs(_v.x)) {
			v.x = _v.x;
		}
		if (abs(v.z) < abs(_v.z)) {
			v.z = _v.z;
		}
	}
	return v;
}

VECTOR3 COLLISION_TERRAIN::collision(const COLLISION_POINT* point)const{
	float overSx = Sx - point->px() ;
	float overSz = Sz - point->pz();
	float overEx = point->px() - Ex;
	float overEz = point->pz() - Ez;
	float overY = Floor - point->py();
	VECTOR3 v;
	if (overSx > 0) {
		v.x = overSx;
	}
	if (overSz > 0) {
		v.z = overSz;
	}
	if (overEx > 0) {
		v.x = -overEx;
	}
	if (overEz > 0) {
		v.z = -overEz;
	}
	if (overY > 0) {
		v.y = overY;
	}
	return v;
}

VECTOR3 COLLISION_TERRAIN::collision(const VECTOR3& pos, const VECTOR3& cv) const{
	float overSx = Sx - pos.x;
	float overSz = Sz - pos.z;
	float overEx = pos.x - Ex;
	float overEz = pos.z - Ez;
	float overY = Floor - pos.y;
	VECTOR3 v;
	if (overSx > 0) {
		v = cv * (overSx/cv.x);
	}
	if (overSz > 0) {
		VECTOR3 _v = cv * (overSz / cv.z);
		if (length2(v) < length2(_v)) {
			v = _v;
		}
	}
	if (overEx > 0) {
		VECTOR3 _v = cv * (-overEx / cv.x);
		if (length2(v) < length2(_v)) {
			v = _v;
		}
	}
	if (overEz > 0) {
		VECTOR3 _v = cv * (-overEz / cv.z);
		if (length2(v) < length2(_v)) {
			v = _v;
		}
	}
	if (overY > 0) {
		VECTOR3 _v = cv * (overY / cv.y);
		if (length2(v) < length2(_v)) {
			v = _v;
		}
	}
	return v;
}
