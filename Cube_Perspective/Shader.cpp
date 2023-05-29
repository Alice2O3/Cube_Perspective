#include "stdafx.h"
#include "Scene.h"

using namespace std;

const int Shader::ball_lon = 32;
const int Shader::ball_lat = 32;
const int Shader::array_siz = Shader::ball_lon * (Shader::ball_lat + 1);
GLuint* Shader::texture = new GLuint[3]();
CVector767* Shader::ball_vert = new CVector767[Shader::array_siz];
CVector767* Shader::ball_norm = new CVector767[Shader::array_siz];
float** Shader::ball_texture_coordinate = new float*[Shader::array_siz];

//Lights and Materials
GLfloat* Shader::light_amb = new GLfloat[4]{ 0.4f, 0.4f, 0.4f, 1 };
GLfloat* Shader::light_dif = new GLfloat[4]{ 1, 1, 1, 1 };
GLfloat* Shader::light_spe = new GLfloat[4]{ 1, 1, 1, 1 };
GLfloat* Shader::mat_amb = new GLfloat[4]{ 0.3f, 0.3f, 0.3f, 1 };
GLfloat* Shader::mat_dif = new GLfloat[4]{ 1, 1, 1, 1 };
GLfloat* Shader::mat_spe = new GLfloat[4]{ 0.1f, 0.1f, 0.1f, 1 };

//Show Texts
void Shader::Font2D(string& s, CVector767& col, const double& x, const double& y, const int& size) {
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	glColor3f(col.x, col.y, col.z);
	//Change Matrix Mode
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//Output strings
	size_t len = s.length();
	glRasterPos2f(x, y);
	for (int i = 0; i < len; ++i)
	{
		switch (size) {
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
			break;
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			break;
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[i]);
			break;
		case 4:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
			break;
		case 5:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
			break;
		case 6:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
			break;
		case 7:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
			break;
		}
	}
	//Reset projections mode
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Shader::SetRC() {
	//Set glut properties
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	//glEnable(GL_LINE_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glLineWidth(0);
}

void Shader::initBall() {
	for (int i = 0; i < array_siz; i++) {
		ball_texture_coordinate[i] = new float[2]();
	}
	GLfloat lonCur, latCur, lonStep = 2 * Util::Pi / ball_lon, latStep = Util::Pi / ball_lat;
	CVector767 normal;
	int index[4], nVert = 0;
	for (int i = 0; i < ball_lon; i++)
	{
		lonCur = i * lonStep;
		for (int j = 0; j <= ball_lat; j++)
		{
			latCur = -Util::Pi / 2 + j * latStep;
			ball_vert[nVert][2] = cos(latCur) * sin(lonCur);
			ball_vert[nVert][0] = cos(latCur) * cos(lonCur);
			ball_vert[nVert][1] = sin(latCur);
			ball_norm[nVert].Set(0, 0, 0);
			ball_texture_coordinate[nVert][0] = float(i) / float(ball_lon);
			ball_texture_coordinate[nVert][1] = float(j) / float(ball_lat);
			nVert++;
		}
	}
	for (int i = 0; i < ball_lon; i++)
	{
		for (int j = 0; j < ball_lat; j++)
		{
			index[0] = i * (ball_lat + 1) + j;
			if (i == ball_lon - 1) {
				index[1] = j;
			}
			else {
				index[1] = index[0] + ball_lat + 1;
			}
			index[2] = index[1] + 1;
			index[3] = index[0] + 1;
			normal = CalculateNormal(ball_vert[index[0]], ball_vert[index[1]], ball_vert[index[2]]);
			for (int k = 0; k < 3; k++)
			{
				ball_norm[index[k]] = ball_norm[index[k]] + normal;
			}
			normal = CalculateNormal(ball_vert[index[2]], ball_vert[index[3]], ball_vert[index[0]]);
			for (int k = 0; k < 4; k++)
			{
				if (k == 1) continue;
				ball_norm[index[k]] = ball_norm[index[k]] + normal;
			}
		}
	}
	while (nVert > 0)
	{
		ball_norm[--nVert].Normalize();
	}
}

CVector767 Shader::CalculateNormal(CVector767& v1, CVector767& v2, CVector767& v3)
{
	CVector767 normal, dirv2_v1, dirv2_v3;
	dirv2_v1 = v1 - v2;
	dirv2_v3 = v3 - v2;
	normal = dirv2_v1.crossMul(dirv2_v3);
	return normal;
}

void Shader::Initialize() {
	initBall();
}

//Render Functions

void Shader::Draw_Axis() {
	glBegin(GL_LINES);
	//Draw x-axis
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(200, 0, 0);
	//Draw y-axis
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 200, 0);
	//Draw z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 200);
	glEnd();
}

void Shader::Draw_Sphere(CSphere767& s) {
	CMatrix767 M;
	M.SetTrans(s.pos);
	float radius = s.radius;
	glPushMatrix();
	glMultMatrixf(M);
	glRotatef(s.pos[0], s.pos[1], s.pos[2], s.pos[0]);
	glRotatef(s.pos[3], s.pos[1], s.pos[2], s.pos[2]);
	glBegin(GL_TRIANGLES);
	//Draw Sphere
	int* index = new int[4]();
	int ord[] = { 0, 1, 2, 2, 3, 0 };
	for (int i = 0; i < ball_lon; i++)	//Longitude
	{
		for (int j = 0; j < ball_lat; j++)	//Latitude
		{
			index[0] = i * (ball_lat + 1) + j;
			if (i == ball_lon - 1) {
				index[1] = j;
			}
			else {
				index[1] = index[0] + ball_lat + 1;
			}
			index[2] = index[1] + 1;
			index[3] = index[0] + 1;
			for (int k = 0; k < 6; k++)
			{
				glTexCoord2f(ball_texture_coordinate[index[ord[k]]][0], ball_texture_coordinate[index[ord[k]]][1]);
				glNormal3fv(ball_norm[index[ord[k]]]);
				glVertex3fv(radius * ball_vert[index[ord[k]]]);
			}
		}
	}
	//Reset States
	glEnd();
	glPopMatrix();
}

//Rendering Functions
const float CRay767::ray_max_render_dist = 1e6;
const float CLine767::line_max_render_dist = 1e6;
const float CAxis767::axis_max_render_dist = 1e4;

void CAxis767::Render() {
	glPushMatrix();
	glMultMatrixf(View_M);

	glBegin(GL_LINES);
	//Draw x-axis
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(axis_max_render_dist, 0, 0);
	//Draw y-axis
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, axis_max_render_dist, 0);
	//Draw z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, axis_max_render_dist);
	glEnd();

	glPopMatrix();
}

void CRay767::Render() {
	glPushMatrix();
	glMultMatrixf(View_M);

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	CVector767 p = ray_max_render_dist * l;
	glVertex3f(0, 0, 0);
	glVertex3f(p.x, p.y, p.z);
	glEnd();

	glPopMatrix();
}

void CPlane767::Render() {
	glPushMatrix();
	glMultMatrixf(View_M);
	
	GLfloat X_min = -Render_dist, X_max = Render_dist;
	GLfloat Z_min = -Render_dist, Z_max = Render_dist;
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	glVertex3f(X_min, 0, Z_min);
	glVertex3f(X_min, 0, Z_max);
	glVertex3f(X_max, 0, Z_max);
	glVertex3f(X_max, 0, Z_min);
	glEnd();

	glPopMatrix();
}

void Rotating_Cube::Render() {
	glPushMatrix();
	glMultMatrixf(View_M);

	glLineWidth(1);
	glColor3f(0, 0, 1);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(X_min, Y_min, Z_min);
	glVertex3f(X_min, Y_min, Z_max);
	glVertex3f(X_max, Y_min, Z_max);
	glVertex3f(X_max, Y_min, Z_min);
	glEnd();
	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(X_min, Y_min, Z_min);
	glVertex3f(X_max, Y_min, Z_min);
	glVertex3f(X_max, Y_max, Z_min);
	glVertex3f(X_min, Y_max, Z_min);
	glEnd();
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(X_min, Y_min, Z_min);
	glVertex3f(X_min, Y_max, Z_min);
	glVertex3f(X_min, Y_max, Z_max);
	glVertex3f(X_min, Y_min, Z_max);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(X_min, Y_min, Z_max);
	glVertex3f(X_min, Y_max, Z_max);
	glVertex3f(X_max, Y_max, Z_max);
	glVertex3f(X_max, Y_min, Z_max);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(X_min, Y_max, Z_min);
	glVertex3f(X_max, Y_max, Z_min);
	glVertex3f(X_max, Y_max, Z_max);
	glVertex3f(X_min, Y_max, Z_max);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(X_max, Y_min, Z_min);
	glVertex3f(X_max, Y_min, Z_max);
	glVertex3f(X_max, Y_max, Z_max);
	glVertex3f(X_max, Y_max, Z_min);
	glEnd();
	for (CRay767 ray : side_array) {
		ray.Render();
	}
	glPopMatrix();
}