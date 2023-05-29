#include "stdafx.h"
#include "Pch.h"

using namespace std;

const float Rotating_Cube::max_h0 = 90.0f;
const float Rotating_Cube::max_p0 = 90.0f;
const float Rotating_Cube::max_b0 = 90.0f;

Rotating_Cube::Rotating_Cube(float X_min, float X_max, float Y_min, float Y_max, float Z_min, float Z_max) :
	CCube767(X_min, X_max, Y_min, Y_max, Z_min, Z_max) {
	side_array.push_back(CRay767(CVector767(X_max, Y_min, Z_min), CVector767(1, 0, 0)));
	side_array.push_back(CRay767(CVector767(X_max, Y_max, Z_min), CVector767(1, 0, 0)));
	side_array.push_back(CRay767(CVector767(X_max, Y_min, Z_max), CVector767(1, 0, 0)));
	side_array.push_back(CRay767(CVector767(X_max, Y_max, Z_max), CVector767(1, 0, 0)));

	side_array.push_back(CRay767(CVector767(X_min, Y_min, Z_min), CVector767(0, 0, -1)));
	side_array.push_back(CRay767(CVector767(X_min, Y_max, Z_min), CVector767(0, 0, -1)));
	side_array.push_back(CRay767(CVector767(X_max, Y_min, Z_min), CVector767(0, 0, -1)));
	side_array.push_back(CRay767(CVector767(X_max, Y_max, Z_min), CVector767(0, 0, -1)));

	side_array.push_back(CRay767(CVector767(X_min, Y_min, Z_min), CVector767(0, -1, 0)));
	side_array.push_back(CRay767(CVector767(X_min, Y_min, Z_max), CVector767(0, -1, 0)));
	side_array.push_back(CRay767(CVector767(X_max, Y_min, Z_min), CVector767(0, -1, 0)));
	side_array.push_back(CRay767(CVector767(X_max, Y_min, Z_max), CVector767(0, -1, 0)));
};

void Rotating_Cube::Rotate_x(const float& t) {
	p0 = Util::BoundRange(p0 + t, max_p0);
	Update();
}

void Rotating_Cube::Rotate_y(const float& t) {
	h0 = Util::BoundRange(h0 + t, max_h0);
	Update();
}

void Rotating_Cube::Rotate_z(const float& t) {
	b0 = Util::BoundRange(b0 + t, max_b0);
	Update();
}

void Rotating_Cube::Update() {
	CMatrix767 ry1, rx, ry0;
	ry0.SetRotate(h0, CVector767(0, 1, 0));
	rx.SetRotate(p0, CVector767(1, 0, 0));
	ry1.SetRotate(b0, CVector767(0, 1, 0));
	E = ry0 * rx * ry1;
	Entity::Update_Coordinates(RotateMode::FREE_ROTATION);
}