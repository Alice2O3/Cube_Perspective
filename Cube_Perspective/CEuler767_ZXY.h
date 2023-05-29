#pragma once

#ifndef _TEST_CEuler767_ZXY
#define _TEST_CEuler767_ZXY

class CEuler767_ZXY {
public:
	static const float euler_eps;
	float x{}, y{}, z{}; //Unit: Deg
	CEuler767_ZXY() {};
	CEuler767_ZXY(float x, float y, float z) :x(x), y(y), z(z) {};
	void Reset();
	void Set(const float&, const float&, const float&);
	operator float* () { return &x; };
	std::string toString();
	void Normalize();
	CMatrix767 ToMatrix();
};

#endif