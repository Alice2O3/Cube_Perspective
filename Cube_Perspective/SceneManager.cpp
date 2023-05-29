#include "stdafx.h"
#include "Scene.h"

using namespace std;

const float SceneManager::raycast_maxdist = 1e3;
bool* SceneManager::key_dict = new bool[256]();
bool* SceneManager::special_key_dict = new bool[256]();

void SceneManager::Initialize() {
	//Register Functions
	Register_Functions();
	//Initialize Variables
	camera_mode = RotateMode::EULER_ROTATION;
	transition_countdown = 50;
	//Players
	start_first_position = Player(CVector767(0, 0, 150), CEuler767(0, 0, 0));
	start_third_position = Player(CVector767(0, 0, 400), CEuler767(0, 0, 0));
	//start_global_cube = Rotating_Cube(-30, 30, -40, 40, -20, 20);
	start_global_cube = Rotating_Cube(-50, 50, -50, 50, -50, 50);
	start_global_cube.Set_Euler(CVector767(0, 0, 0), CEuler767(0, 0, 0));
	Reset_Position();
	//Set Entities
	game_objects.push_back(&player_first_person);
	game_objects.push_back(&player_third_person);
	game_objects.push_back(new CPlane767(CVector767(0, -100, 0), CEuler767(0, 0, 0)) );
	game_objects.push_back(new CAxis767(CVector767(0, 0, 0), CEuler767(0, 0, 0)) );
	game_objects.push_back(&global_cube);
	binding_object = &global_cube;
	//Set The Positions
	Reset_World();
	//Set Gears
	move_speed_gear = Gears(8, 4, new float[8]{ 0.05f, 0.1f, 0.25f, 0.5f, 1.0f, 2.0f, 5.0f, 10.0f }, &move_speed);
	camera_rotate_speed_gear = Gears(8, 4, new float[8]{ 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 1.5f, 3.0f, 5.0f }, &camera_rotate_speed);
	cube_rotate_speed_gear = Gears(8, 4, new float[8]{ 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 1.5f, 3.0f, 5.0f }, &cube_rotate_speed);
	//Set Window
	window_captain = "Cube Perspective";
	window_width = 800;
	window_height = 600;
	angle_of_view = 60.0f;
	near_plane = 1;
	far_plane = 2e6;
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow(window_captain);
}

//Control Functions
void SceneManager::Move_x(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Move_x(t * move_speed, camera_mode);
}

void SceneManager::Move_y(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Move_y(t * move_speed, camera_mode);
}

void SceneManager::Move_z(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Move_z(t * move_speed, camera_mode);
}

void SceneManager::Rotate_x(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Rotate_x(t * camera_rotate_speed, camera_mode);
}

void SceneManager::Rotate_y(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Rotate_y(t * camera_rotate_speed, camera_mode);
}

void SceneManager::Rotate_z(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Rotate_z(t * camera_rotate_speed, camera_mode);
}

void SceneManager::Change_MoveSpeed(const int& t) {
	if (isFreezed) {
		return;
	}
	move_speed_gear.Change_Gear(t);
}

void SceneManager::Change_RotateSpeed(const int& t) {
	if (isFreezed) {
		return;
	}
	camera_rotate_speed_gear.Change_Gear(t);
}

void SceneManager::Change_CubeRotateSpeed(const int& t) {
	if (isFreezed) {
		return;
	}
	cube_rotate_speed_gear.Change_Gear(t);
}

void SceneManager::Rotate_Cube_y(const float& t) {
	if (isFreezed) {
		return;
	}
	global_cube.Rotate_y(t * cube_rotate_speed);
}

void SceneManager::Rotate_Cube_x(const float& t) {
	if (isFreezed) {
		return;
	}
	global_cube.Rotate_x(t * cube_rotate_speed);
}

void SceneManager::Rotate_Cube_z(const float& t) {
	if (isFreezed) {
		return;
	}
	global_cube.Rotate_z(t * cube_rotate_speed);
}

void SceneManager::Change_Mode(RotateMode mode) {
	if (isFreezed) {
		return;
	}
	camera_mode = mode;
}

void SceneManager::Toggle_Pause() {
	if (isFreezed) {
		return;
	}
	isPaused ^= 1;
}

void SceneManager::Reset_Position() {
	if (isFreezed) {
		return;
	}
	//binding_object = NULL;
	player_third_person = start_third_position;
	player_first_person = start_first_position;
	current_player = &player_third_person;
	transition_state = PlayerState::THIRD_PERSON;
}

void SceneManager::Reset_Position_Animation() {
	if (isFreezed) {
		return;
	}
	camera_A = *current_player;
	player_third_person = start_third_position;
	player_first_person = start_first_position;
	camera_B = player_third_person;
	current_player = &player_third_person;
	transition_state = PlayerState::TRANSITION;
	goal_transition_state = PlayerState::THIRD_PERSON;
}

void SceneManager::Reset_World() {
	if (isFreezed) {
		return;
	}
	global_cube = start_global_cube;
}

void SceneManager::ReturnToThird() { //Will not reset states
	if (transition_state != PlayerState::FIRST_PERSON) {
		return;
	}
	camera_A = player_first_person;
	camera_B = player_third_person;
	current_player = &player_third_person;
	transition_state = PlayerState::TRANSITION;
	goal_transition_state = PlayerState::THIRD_PERSON;
}

void SceneManager::ReturnToFirst() { //Will not reset states
	if (transition_state != PlayerState::THIRD_PERSON || binding_object == NULL) {
		return;
	}
	camera_A = player_third_person;
	camera_B = player_first_person;
	current_player = &player_first_person;
	transition_state = PlayerState::TRANSITION;
	goal_transition_state = PlayerState::FIRST_PERSON;
}

void SceneManager::CameraTransition(Entity* e) { //Will also reset states
	if (e == NULL) {
		return;
	}
	binding_object = e;
	camera_A = *current_player;
	player_first_person = start_first_position;
	player_first_person.Bind_Object(binding_object);
	camera_B = player_first_person;
	current_player = &player_first_person;
	transition_state = PlayerState::TRANSITION;
	goal_transition_state = PlayerState::FIRST_PERSON;
}

//Window Functions
void SceneManager::Window_Resize(const int& w, const int& h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle_of_view, GLfloat(w) / h, near_plane, far_plane);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_PROJECTION_MATRIX, Projection_Matrix);
	window_width = w, window_height = h;
}

void SceneManager::Window_Close() {
	if (!glutGetWindow()) {
		return;
	}
	exit(0);
}

void SceneManager::Update_Timer() {
	transition_timer++;
	if (transition_timer >= transition_countdown) {
		transition_timer = 0;
		transition_state = goal_transition_state;
	}
}

void SceneManager::Update_State() {
	//Update States
	if (!isFreezed && isPaused == 0) {
		//TODO
	}
	//Execute Keyboard Events
	Keyboard_Events_Hold();
	//Bind the bubble
	player_first_person.Bind_Object(binding_object);
	//Update Cameras
	if (transition_state == PlayerState::TRANSITION) {
		isFreezed = 1;
		View_Matrix = camera_A.Slerp(camera_B, Util::Ratio(transition_timer, transition_countdown));
		Update_Timer();
	}
	else {
		isFreezed = 0;
		View_Matrix = current_player->IView_MG;
	}
}

//Keyboard Functions
void SceneManager::Keyboard_Detect(const unsigned char& key, const bool& s) {
	key_dict[key] = s;
}

void SceneManager::Keyboard_Detect_Special(const unsigned char& key, const bool& s) {
	special_key_dict[key] = s;
}

void SceneManager::Keyboard_Events_Hold() {
	for (auto p : Keyboard_Events_Hold_Map) {
		if (key_dict[p.first]) {
			p.second();
		}
	}
	for (auto p : Keyboard_Events_Hold_Special_Map) {
		if (special_key_dict[p.first]) {
			p.second();
		}
	}
}

void SceneManager::Keyboard_Events_Down(const unsigned char& key) {
	if (Keyboard_Events_Down_Map.count(key)) {
		Keyboard_Events_Down_Map[key]();
	}
}

void SceneManager::Keyboard_Events_Down_Special(const unsigned char& key) {
	if (Keyboard_Events_Down_Special_Map.count(key)) {
		Keyboard_Events_Down_Special_Map[key]();
	}
}

//Mouse Functions
CRay767 SceneManager::Mouse_Raycast(const int& width, const int& height, const int& mouse_x, const int& mouse_y) {
	float x = (2.0f * mouse_x) / width - 1.0f, y = 1.0f - (2.0f * mouse_y) / height;
	//4d Homogeneous Clip Coordinates
	CVector767_ext ray_clip = CVector767_ext(x, y, -1.0, 1.0);
	//4d Eye Coordinates
	CVector767_ext ray_eye = Projection_Matrix.GetInverse() * ray_clip;
	ray_eye.z = -1.0f, ray_eye.w = 0.0f;
	//4d World Coordinates
	CVector767 ray_dir = (current_player->View_MG * ray_eye).To3DVector();
	//Set the position vector
	CVector767 ray_pos = current_player->View_M.posMul(current_player->posL);
	return CRay767(ray_pos, ray_dir);
}

void SceneManager::Mouse_Clicking_Events(const int& mouse_x, const int& mouse_y) {
	if (isFreezed) {
		return;
	}
	CRay767 ray = Mouse_Raycast(window_width, window_height, mouse_x, mouse_y);
}

//Render Functions
void SceneManager::Scene_Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Set View Matrix
	glPushMatrix();
	glMultMatrixf(View_Matrix);
	//Draw Entities
	for (Entity* e : game_objects) {
		e->Render();
	}
	//Draw HUD
	string HUD = Util::format("Cube: h0:%.2f, p0:%.2f, b0:%.2f",
		global_cube.h0,
		global_cube.p0,
		global_cube.b0
	);
	Shader::Font2D(HUD, CVector767(1, 0, 1), -0.95, 0.85, 4);
	CEuler767 player_dir = current_player->EG.ToEuler();
	HUD = Util::format("Player: h:%.2f, p:%.2f, b:%.2f",
		player_dir.h,
		player_dir.p,
		player_dir.b
	);
	Shader::Font2D(HUD, CVector767(1, 0, 1), -0.95, 0.75, 4);
	HUD = Util::format("Window: width:%d, height:%d", window_width, window_height);
	Shader::Font2D(HUD, CVector767(1, 0, 1), -0.95, 0.65, 4);
	//Reset Matrix
	glPopMatrix();
	glutSwapBuffers();
}

void SceneManager::Register_Functions() {
	Keyboard_Events_Down_Map = {
		{ 27,  [&]() { ReturnToThird(); } }, //ESCAPE KEY
		{ 'p', [&]() { Toggle_Pause(); } },
		{ 'r', [&]() { Reset_Position_Animation(); } },
		{ '[', [&]() { Change_MoveSpeed(-1); } },
		{ ']', [&]() { Change_MoveSpeed(1); } },
		{ '-', [&]() { Change_RotateSpeed(-1); } },
		{ '=', [&]() { Change_RotateSpeed(1); } },
		{ ';', [&]() { Change_CubeRotateSpeed(-1); } },
		{ '\'',[&]() { Change_CubeRotateSpeed(1); } },
		{ '/', [&]() { Reset_World(); } },
		{ '0', [&]() { ReturnToFirst(); } },
		{ '1', [&]() { Change_Mode(RotateMode::EULER_ROTATION); } },
		{ '2', [&]() { Change_Mode(RotateMode::FREE_ROTATION); } }
	};

	Keyboard_Events_Down_Special_Map = {
		{GLUT_KEY_END, [&]() { Window_Close(); }}
	};

	Keyboard_Events_Hold_Map = {
		{ 'd', [&]() { Move_x(1); } },
		{ 'a', [&]() { Move_x(-1); } },
		{ 'e', [&]() { Move_y(1); } },
		{ 'q', [&]() { Move_y(-1); } },
		{ 's', [&]() { Move_z(1); }},
		{ 'w', [&]() { Move_z(-1); } },
		{ 'i', [&]() { Rotate_x(1); } },
		{ 'k', [&]() { Rotate_x(-1); } },
		{ 'j', [&]() { Rotate_y(1); } },
		{ 'l', [&]() { Rotate_y(-1); } },
		{ 'o', [&]() { Rotate_z(1); } },
		{ 'u', [&]() { Rotate_z(-1); } },
		{ ',', [&]() { Rotate_Cube_z(1); } },
		{ '.', [&]() { Rotate_Cube_z(-1); } }
	};

	Keyboard_Events_Hold_Special_Map = {
		{GLUT_KEY_UP,    [&]() { Rotate_Cube_x(-1); }},
		{GLUT_KEY_DOWN,  [&]() { Rotate_Cube_x(1); }},
		{GLUT_KEY_LEFT,  [&]() { Rotate_Cube_y(-1); }},
		{GLUT_KEY_RIGHT, [&]() { Rotate_Cube_y(1); }}
	};
}