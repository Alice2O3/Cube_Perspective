#pragma once

#ifndef _TEST_Shader
#define _TEST_Shader

class Shader {
public:
	//Draw 2D fonts on the screen
	static void Font2D(std::string&, CVector767&, const double&, const double&, const int&);
	//Const Variables
	static const int ball_lon, ball_lat, array_siz;
	static GLuint* texture;
	static CVector767 *ball_vert, *ball_norm;
	static float** ball_texture_coordinate;
	//Pre-process Functions
	static void Initialize();
	static void SetRC();
	//Pre-process Datas of Sphere (Longitude and Latitude, Coordinates, Normal Vectors and Texture Coordinates)
	static void initBall();
	//Calculate Normal Vectors
	static CVector767 CalculateNormal(CVector767&, CVector767&, CVector767&);
	//Lights
	static GLfloat* light_amb;
	static GLfloat* light_dif;
	static GLfloat* light_spe;
	//Materials
	static GLfloat* mat_amb;
	static GLfloat* mat_dif;
	static GLfloat* mat_spe;
	//Rendering functions
	static void Draw_Sphere(CSphere767&);
	static void Draw_Axis();
};

#endif