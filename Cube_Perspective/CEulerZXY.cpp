#include "stdafx.h"
#include "Pch.h"

using namespace std;

//CFree767
string CEuler767_ZXY::toString() {
	return Util::format("%.2f,%.2f,%.2f", x, y, z);
}

void CEuler767_ZXY::Reset() {
	x = 0.0f, y = 0.0f, z = 0.0f;
}

void CEuler767_ZXY::Set(const float& x_, const float& y_, const float& z_) {
	x = x_, y = y_, z = z_;
}

void CEuler767_ZXY::Normalize() {
	x = Util::WrapAngle(x), y = Util::WrapAngle(y), z = Util::WrapAngle(z);
}

CMatrix767 CEuler767_ZXY::ToMatrix() {
	CMatrix767 ry, rx, rz;
	ry.SetRotate(y, CVector767(0, 1, 0));
	rx.SetRotate(x, CVector767(1, 0, 0));
	rz.SetRotate(z, CVector767(0, 0, 1));
	return rz * rx * ry;
}