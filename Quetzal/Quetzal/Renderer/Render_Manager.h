#pragma once
#include "Model.h"
#include "Camera.h"
class Render_Manager
{
private:
	//All Items in Render Manager
	Vec_SH<Texture> All_Texture;
	Vec_SH<Shader> All_Shader;
	Vec_SH<Mesh> All_Meshes;
	Vec_SH<Material> All_Materials;
	Vec_SH<Model> All_Models;
	//Default Model, Texture, and Shader to show on main window
	S_P<Shader> Main_Shader;
	S_P<Frame_Buffer> Main_Texture;
	S_P<Model> Main_Model;
	//If Render to ImGui or Render to Window
	bool R_Window;
	//Camera information And Windows ID
	GLFWwindow* MainWindow;
	int Frame_Buffer_Width;
	int Frame_Bufer_Height;
	glm::mat4 Projection;
	S_P<Camera> Main_Cam;
	float NearPlane;
	float FarPlane;
	float Fov;
	//shader version
	const int GLVerMajor;
	const int GLVerMinor;
	void UpdateMatrices();
public:
	Render_Manager(GLFWwindow* window, const int GlVerMajorInit, const int GlVerMinorInit, bool Win_Start = false);
	//Updates Positions, animations for all Models in the world
	void Update(float dt);
	//Renders all
	void Render();
	void RenderToWindow();
	//Getters
	Vec_SH<Texture> GetAllTextures()   { return this->All_Texture; }
	Vec_SH<Shader> GetAllShaders()     { return this->All_Shader; }
	Vec_SH<Mesh> GetAllMeshes()        { return this->All_Meshes; }
	Vec_SH<Material> GetAllMaterials() { return this->All_Materials; }
	Vec_SH<Model> GetAllModels()       { return this->All_Models; }
	bool ToWindow()                    { return this->R_Window; }
	S_P<Frame_Buffer> GetMainTexture()	   { return this->Main_Texture; }
	//Setters
	void AddTextures(std::shared_ptr<Texture> NewTexture);
	void AddShader(std::shared_ptr<Shader> NewShader);
	void AddMesh(std::shared_ptr<Mesh> NewMesh);
	void AddMaterials(std::shared_ptr<Material> NewMaterial);
	void AddModel(std::shared_ptr<Model> NewModel);
	void ChangeRenderTarget(bool ToWindow);
	//Remove Items
	void RemoveTexture(int Id);
	void RemoveShader(int Id);
	void RemoveMesh(int Id);
	void RemoveMaterial(int Id);
	void RemoveModel(int Id);
};