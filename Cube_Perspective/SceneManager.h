#pragma once

#ifndef _TEST_SceneManager
#define _TEST_SceneManager

enum class PlayerState {
	FIRST_PERSON,
	THIRD_PERSON,
	TRANSITION
};

class SceneManager {
public:
	//static variables
	static const float raycast_maxdist;
	//Keyboard Detect
	static bool* key_dict;
	static bool* special_key_dict;
	static void Keyboard_Detect(const unsigned char&, const bool&);
	static void Keyboard_Detect_Special(const unsigned char&, const bool&);
	//Initialize
	//SceneManager() {};
	void Initialize();
	void Register_Functions();
	//Basic Functions
	void Reset_Position();
	void Reset_Position_Animation();
	void Change_Mode(RotateMode);
	void Toggle_Pause();
	void Update_Timer();
	void Update_State();
	void ReturnToThird();
	void ReturnToFirst();
	void Reset_World();
	void CameraTransition(Entity*);
	void Window_Resize(const int&, const int&);
	void Window_Close();
	//Move Functions
	void Move_x(const float&);
	void Move_y(const float&);
	void Move_z(const float&);
	void Rotate_x(const float&);
	void Rotate_y(const float&);
	void Rotate_z(const float&);
	void Rotate_Cube_y(const float&);
	void Rotate_Cube_x(const float&);
	void Rotate_Cube_z(const float&);
	//Change Gears
	void Change_MoveSpeed(const int&);
	void Change_RotateSpeed(const int&);
	void Change_CubeRotateSpeed(const int&);
	//Mouse RayCast
	CRay767 Mouse_Raycast(const int&, const int&, const int&, const int&);
	//Keyboard Events
	void Mouse_Clicking_Events(const int&, const int&);
	void Keyboard_Events_Hold();
	void Keyboard_Events_Down(const unsigned char&);
	void Keyboard_Events_Down_Special(const unsigned char&);
	//Render Functions
	void Scene_Render();

private:
	//Window Variables
	char* window_captain{};
	int window_width{}, window_height{};
	float angle_of_view{}, near_plane{}, far_plane{};
	//Entities
	std::vector<Entity*> game_objects;
	//Variables
	Rotating_Cube start_global_cube;
	Rotating_Cube global_cube;
	Player start_first_position;
	Player start_third_position;
	Player player_first_person;
	Player player_third_person;
	Player camera_A, camera_B;
	Gears move_speed_gear;
	Gears camera_rotate_speed_gear;
	Gears cube_rotate_speed_gear;
	//State Variables
	Player* current_player{};
	Entity* binding_object{};
	RotateMode camera_mode{};
	float move_speed{};
	float camera_rotate_speed{};
	float cube_rotate_speed{};
	//Matrices
	CMatrix767 View_Matrix;
	CMatrix767 Projection_Matrix;
	//Transition
	int transition_countdown{};
	int transition_timer{};
	PlayerState transition_state{};
	PlayerState goal_transition_state{};
	//Pause State
	bool isFreezed{};
	bool isPaused{};
	//Keyboard Functions
	std::map<unsigned char, std::function<void()>> Keyboard_Events_Down_Map;
	std::map<unsigned char, std::function<void()>> Keyboard_Events_Hold_Map;
	std::map<unsigned char, std::function<void()>> Keyboard_Events_Down_Special_Map;
	std::map<unsigned char, std::function<void()>> Keyboard_Events_Hold_Special_Map;
};

#endif