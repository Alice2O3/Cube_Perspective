#include "stdafx.h"
#include "Pch.h"

using namespace std;

void Player::SetLocal_Euler(const CVector767& posL_, const CEuler767& dirL_) {
	posL = posL_, dirL = dirL_;
	Update(RotateMode::EULER_ROTATION);
}

void Player::Update(RotateMode mode) {
	Entity::Update_Coordinates(mode);
	ML.SetTrans(posL);
	Update_EFM(dirL, dirL_zxy, EL, mode);
	EG = E * EL;
	View_ML = ML * EL;
	View_MG = View_M * View_ML;
	IView_MG = View_MG.GetInverse();
}

void Player::Move_x(const float& t, RotateMode mode) {
	CVector767 d = CVector767(View_ML.m00, View_ML.m10, View_ML.m20);
	posL = posL + t * d;
	Update(mode);
}

void Player::Move_y(const float& t, RotateMode mode) {
	CVector767 d = CVector767(View_ML.m01, View_ML.m11, View_ML.m21);
	posL = posL + t * d;
	Update(mode);
}

void Player::Move_z(const float& t, RotateMode mode) {
	CVector767 d = CVector767(View_ML.m02, View_ML.m12, View_ML.m22);
	posL = posL + t * d;
	Update(mode);
}

void Player::Rotate_x(const float& t, RotateMode mode) {
	if (mode == RotateMode::EULER_ROTATION) {
		dirL.p += t;
	}
	if (mode == RotateMode::EULER_ROTATION_ZXY) {
		dirL_zxy.x += t;
	}
	if (mode == RotateMode::FREE_ROTATION) {
		CMatrix767 T;
		T.SetRotate(t, CVector767(1, 0, 0));
		EL = EL * T;
	}
	Update(mode);
}

void Player::Rotate_y(const float& t, RotateMode mode) {
	if (mode == RotateMode::EULER_ROTATION) {
		dirL.h += t;
	}
	if (mode == RotateMode::EULER_ROTATION_ZXY) {
		dirL_zxy.y += t;
	}
	if (mode == RotateMode::FREE_ROTATION) {
		CMatrix767 T;
		T.SetRotate(t, CVector767(0, 1, 0));
		EL = EL * T;
	}
	Update(mode);
}

void Player::Rotate_z(const float& t, RotateMode mode) {
	if (mode == RotateMode::EULER_ROTATION) {
		dirL.b += t;
	}
	if (mode == RotateMode::EULER_ROTATION_ZXY) {
		dirL_zxy.z += t;
	}
	if (mode == RotateMode::FREE_ROTATION) {
		CMatrix767 T;
		T.SetRotate(t, CVector767(0, 0, 1));
		EL = EL * T;
	}
	Update(mode);
}

void Player::Bind_Object(Entity* other) {
	if (other == NULL) {
		return;
	}
	Set_Matrix(other->pos, other->E);
	Update(RotateMode::FREE_ROTATION);
}

CMatrix767 Player::Slerp(Player& other, const float& t) {
	CVector767 va = View_M.posMul(posL), vb = other.View_M.posMul(other.posL);
	CVector767 vc = va.Slerp(vb, t);
	CQuaternion767 qa = EG.ToQuaternion(), qb = other.EG.ToQuaternion();
	CQuaternion767 qc = qa.Slerp(qb, t);
	CMatrix767 M;
	M.SetTrans(vc);
	return (M * qc.ToMatrix()).GetInverse();
}