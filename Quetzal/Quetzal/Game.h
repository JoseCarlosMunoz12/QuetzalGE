#pragma once

#include "libs.h"
#include <random>

//Enumerations
enum shader_enums
{
	SHADER_DEBUGS,
	SHADER_CORE_PROGRAM,
	SHADER_TERRAIN,
	SHADERS_TERRAIN,
	SHADER_SHADOWS
};
enum texture_enum 
{
	TEX_PUSHEEM,TEX_PUSHEEN_SPECULAR,
	TEX_CONTAINER,TEX_CONTAINER_SPECULAR,
	TEX_FLOWER,TEX_FLOWER_SPECULAR
};
enum material_ennum
{
	MAT_0,
	MAT_1 ,
	MAT_2
};
enum mesh_enum
{
	MESH_QUAD = 0,
	MESH_PLANE_TERRAIN,
	MESH_CUSTOM_TERRAIN,
	MESH_TRIANGLE,
	MESH_PYRAMID,
	MESH_CUBE,
	MESH_SPHERE,
	MESH_CYLINDER,
	MESH_CONE
};
enum heighMaps_enum
{
	HEIGHTMAP_1
};

class Game
{
private:
	//Variables
	//Delta Time
	float dt;
	float cuTime;
	float lastTime;
	//Mouse Input
	float Amount = 0;
	float AmountZ = 0;
	
	int MapWidth;
	int MapHeigth;

	//window
	GLFWwindow* window;
	const int Window_Width;
	const int Window_Height;
	int frameBufferWidth;
	int frameBufferHeight;
	bool OtherWindow = true;
	//OpenGl context
	const int GLVerMajor;
	const int GLVerMinor;
	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;
	glm::vec3 SkyColor;
	bool MakeMesh = false;
	//Variable that changes item to click
	int ModelToMake = -1;
	int AnimModelToMake = -1;
	//Position where the Mouse Click does not affect
	ImVec2 ScreenPos;
	ImVec2 WinSize;
	// Collision and PHysics world and other informations
	bool AddShape = false;
	int  ShapeID;
	int BodId;
	/// <summary>
	/// ImGui Window Manager
	/// </summary>
	std::unique_ptr<ImGuiWindowManager> ImManager;
	std::shared_ptr<Render_Manager> R_Manager;
	//Private Functions
	//--Inits
	void initGLFW();
	void initWindow(const char* title,bool resizable);
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	void InitRenderManager();
	void InitLights();
	void initUniforms();
	void initImGui();
	//--Updates
	void updateDT();
	void updateKeyboardInput();
	void updateMouseInput();
	void updateInput();
	void updateController();
	void ImGuiOptions();

	void updateUniforms();
	void updateOpenGLOptions();
public:
	//Constructors/destructors
	Game(const char * title,
		const int width, const int height,
		int GLmajorVer, int GLminorVer, bool resizable,glm::vec3 SkyColor);
	virtual ~Game();
	//Accessors
	int getWindowShouldClose();
	//Modifiers
	void setWindowShouldClose();
	//Functions
	void update();
	void render();
	//Static Functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
	//ImGui Manager
};

