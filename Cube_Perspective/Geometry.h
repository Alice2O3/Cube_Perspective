#pragma once

#ifndef _TEST_Geometry
#define _TEST_Geometry

//Geometry
class CRay767 : public Entity {
public:
	static const float ray_max_render_dist;
	CVector767 l;
	CRay767() : Entity() {};
	CRay767(CVector767 pos_, CVector767 l_) {
		pos = pos_, l = l_;
		l.Normalize();
		Update_Coordinates(RotateMode::EULER_ROTATION);
	};
	//Basic Functions
	void Set(const CVector767&, const CVector767&);
	//Geometric Detection
	float Collision_Sphere(CSphere767&);
	virtual void Render();
};

class CSphere767 : public Entity {
public:
	float radius{};
	bool Collision_Sphere(CSphere767&);
};

class CCube767 : public Entity {
public:
	float X_min{}, X_max{};
	float Y_min{}, Y_max{};
	float Z_min{}, Z_max{};
	CCube767() : Entity() {};
	CCube767(float X_min, float X_max, float Y_min, float Y_max, float Z_min, float Z_max) :
		X_min(X_min), X_max(X_max),
		Y_min(Y_min), Y_max(Y_max),
		Z_min(Z_min), Z_max(Z_max) {
		Entity();
	};
};

class CPlane767 : public Entity {
public:
	static const float Render_dist;
	CPlane767() : Entity() {};
	CPlane767(CVector767 pos, CEuler767 dir) : Entity(pos, dir) {};
	virtual void Render();
};

class CLine767 : public Entity {
public:
	static const float line_max_render_dist;
	CVector767 l;
	CLine767() : Entity() {};
	CLine767(CVector767 pos_, CVector767 l_) : l(l_) {
		pos = pos_;
		l.Normalize();
	};
	virtual void Render();
};

class CAxis767 : public Entity {
public:
	static const float axis_max_render_dist;
	CAxis767() : Entity() {};
	CAxis767(CVector767 pos, CEuler767 dir) : Entity(pos, dir) {};
	virtual void Render();
};

#endif