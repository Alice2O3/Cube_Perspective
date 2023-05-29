#include "stdafx.h"
#include "Scene.h"

using namespace std;

//Scene Manager
SceneManager scene;

//Functions
void Initialize()
{
	//Set Random Seed
	Util::Set_Random_Seed();
	//Pre-processing the Sphere
	Shader::Initialize();
	//Initialize the Scene
	scene.Initialize();
}

void myDisplay(void)
{
	scene.Scene_Render();
}

void myReshape(int w, int h)
{
	scene.Window_Resize(w, h);
}

void Update_View(int val)
{
	scene.Update_State();
	myDisplay();
	glutTimerFunc(10, Update_View, 0);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	SceneManager::Keyboard_Detect(key, 1);
	scene.Keyboard_Events_Down(key);
}

void myKeyboardUpFunc(unsigned char key, int x, int y)
{
	SceneManager::Keyboard_Detect(key, 0);
}

void myKeyboardFunc_Special(int key, int x, int y)
{
	SceneManager::Keyboard_Detect_Special(key, 1);
	scene.Keyboard_Events_Down_Special(key);
}

void myKeyboardUpFunc_Special(int key, int x, int y)
{
	SceneManager::Keyboard_Detect_Special(key, 0);
}

void myMouse_Func(int button, int state, int x, int y) {
	switch (state) {
	case GLUT_DOWN:
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			scene.Mouse_Clicking_Events(x, y);
			break;
		}
		break;
	}
}

void Register_Functions() {
	glutDisplayFunc(&myDisplay);
	glutTimerFunc(10, Update_View, 0);
	//Set Keyboard/Mouse Functions
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(myKeyboardFunc);
	glutKeyboardUpFunc(myKeyboardUpFunc);
	glutSpecialFunc(myKeyboardFunc_Special);
	glutSpecialUpFunc(myKeyboardUpFunc_Special);
	glutMouseFunc(myMouse_Func);
}

Err_Code Task_main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	Initialize();
	Register_Functions();
	Shader::SetRC();
	glutMainLoop();
	return Err_Code::NO_ERR;
}