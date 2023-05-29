#pragma once

#ifndef _TEST_GameObject
#define _TEST_GameObject

//Objects
class Player : public Entity {
public:
	CVector767 posL;
	CEuler767 dirL; //Euler Mode
	CEuler767_ZXY dirL_zxy;
	CMatrix767 ML, EL, View_ML;
	CMatrix767 EG, View_MG, IView_MG;
	Player() {};
	Player(CVector767 posL, CEuler767 dirL) :
		posL(posL),
		dirL(dirL)
	{
		Update(RotateMode::EULER_ROTATION);
	};
	//void Initialize();
	void Update(RotateMode);
	void SetLocal_Euler(const CVector767&, const CEuler767&);
	void Move_x(const float&, RotateMode);
	void Move_y(const float&, RotateMode);
	void Move_z(const float&, RotateMode);
	void Rotate_x(const float&, RotateMode);
	void Rotate_y(const float&, RotateMode);
	void Rotate_z(const float&, RotateMode);
	//Binding
	void Bind_Object(Entity*);
	//Slerp
	CMatrix767 Slerp(Player&, const float&);
};

class Rotating_Cube : public CCube767 {
public:
	static const float max_h0, max_p0, max_b0;
	float h0{}, p0{}, b0{}; //Euler Angle y-x-y;
	std::vector<CRay767> side_array;
	Rotating_Cube() {};
	Rotating_Cube(float X_min, float X_max, float Y_min, float Y_max, float Z_min, float Z_max);
	void Rotate_x(const float&);
	void Rotate_y(const float&);
	void Rotate_z(const float&);
	virtual void Render();
	void Update();
};

#endif