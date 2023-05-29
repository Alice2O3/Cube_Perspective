#pragma once

#ifndef _TEST_Util
#define _TEST_Util

enum class Err_Code {
	NO_ERR = 0,
	ERR_FILEIO = 404,
	ERR_INVALID = 418 
};

class Util {
public:
	static const double Pi, Pi2, Pi180, Pi180r;
	static const float eps;
	//String Formatting
	static const int sizeOfBuffer;
	static char* format_char;
	static std::string format(const char*, ...);
	//Math Functions
	static float DegToRad(const float&);
	static float RadToDeg(const float&);
	static float WrapAngle(const float&);
	static float BoundRange(const float&, const float&);
	static float Ratio(const int&, const int&);
	static bool RoughEqual(const float&, const float&);
	//Random Functions
	static std::default_random_engine Random; // Random Engine
	static void Set_Random_Seed();
	static float Get_Random_Float(const float&, const float&); //Get random float between [l, r]
	static CVector767 Get_Random_Position(const float&, const float&, const float&, const float&, const float&, const float&); //Get random position
	static CVector767 Get_Random_Color(); //Get random color
	static CVector767 Get_Random_Direction(); //Get random vector uniformly distributed on a sphere
};

#endif