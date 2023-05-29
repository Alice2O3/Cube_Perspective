#include "stdafx.h"
#include "Pch.h"

using namespace std;

void Entity::Set_Euler(const CVector767& pos_, const CEuler767& dir_) { //Initial position
	pos = pos_, dir = dir_;
	Update_Coordinates(RotateMode::EULER_ROTATION);
}

void Entity::Set_Free(const CVector767& pos_, const CEuler767_ZXY& free_) { //Initial position
	pos = pos_, dir_zxy = free_;
	Update_Coordinates(RotateMode::EULER_ROTATION_ZXY);
}

void Entity::Set_Matrix(const CVector767& pos_, const CMatrix767& E_) { //Initial position
	pos = pos_, E = E_;
	Update_Coordinates(RotateMode::FREE_ROTATION);
}

void Entity::Update_EFM(CEuler767& dir, CEuler767_ZXY& free, CMatrix767& E, RotateMode mode) {
	if (mode == RotateMode::EULER_ROTATION) {
		dir.Normalize();
		E = dir.ToMatrix();
		free = E.ToEuler_ZXY();
	}
	if (mode == RotateMode::EULER_ROTATION_ZXY) {
		free.Normalize();
		E = free.ToMatrix();
		dir = E.ToEuler();
	}
	if (mode == RotateMode::FREE_ROTATION) {
		free = E.ToEuler_ZXY();
		dir = E.ToEuler();
	}
}

void Entity::Update_Coordinates(RotateMode mode) { //Initial position
	M.SetTrans(pos);
	Update_EFM(dir, dir_zxy, E, mode);
	View_M = M * E;
}

void Entity::Render() {
	//do nothing
}