#pragma once
#ifndef _TEST_Entity
#define _TEST_Entity

enum class RotateMode {
	EULER_ROTATION,
	EULER_ROTATION_ZXY,
	FREE_ROTATION
};

class Entity {
public:
	static void Update_EFM(CEuler767&, CEuler767_ZXY&, CMatrix767&, RotateMode);
	CVector767 pos;
	CEuler767 dir;
	CEuler767_ZXY dir_zxy;
	CMatrix767 M, E, View_M;
	Entity() {
		Update_Coordinates(RotateMode::EULER_ROTATION);
	};
	Entity(CVector767 pos, CEuler767 dir) :
		pos(pos),
		dir(dir)
	{
		Update_Coordinates(RotateMode::EULER_ROTATION);
	};
	void Set_Euler(const CVector767&, const CEuler767&);
	void Set_Free(const CVector767&, const CEuler767_ZXY&);
	void Set_Matrix(const CVector767&, const CMatrix767&);
	//TODO
	virtual void Update_Coordinates(RotateMode);
	virtual void Render();
};

#endif