#pragma once
#include "Model.h"
#include "Anim_Model.h"
#include "Camera.h"
class Render_Manager
{
private:
	//All Items in Render Manager
	Vec_SH<Texture> All_Texture;
	Vec_SH<Shader> All_Shader;
	Vec_SH<Material> All_Materials;
	Vec_SH<Mesh> All_Meshes;
	Vec_SH<Anim_Mesh> All_Anim_Meshes;
	Vec_SH<Model> All_Models;
	Vec_SH<Anim_Model> All_Anim_Models;
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
	Vec_SH<Texture> GetAllTextures()	 { return this->All_Texture; }
	Vec_SH<Shader> GetAllShaders()		 { return this->All_Shader; }
	Vec_SH<Material> GetAllMaterials()	 { return this->All_Materials; }
	Vec_SH<Mesh> GetAllMeshes()			 { return this->All_Meshes; }
	Vec_SH<Anim_Mesh> GetAllAnimMeshs()  { return this->All_Anim_Meshes; }
	Vec_SH<Model> GetAllModels()         { return this->All_Models; }
	Vec_SH<Anim_Model> GetAllAnimModel() { return this->All_Anim_Models; }
	bool ToWindow()                      { return this->R_Window; }
	S_P<Frame_Buffer> GetMainTexture()   { return this->Main_Texture; }
	//Get Some Matrices
	glm::mat4 GetProjMatrix() { return Projection; }
	glm::mat4 GetCamMatrix()  { return this->Main_Cam->GetViewMatrix(); }
	//Setters
	void AddTextures(S_P<Texture> NewTexture);
	void AddShader(S_P<Shader> NewShader);
	void AddMesh(S_P<Mesh> NewMesh);
	void AddAnimMesh(S_P<Anim_Mesh> NewMesh);
	void AddMaterials(S_P<Material> NewMaterial);
	void AddModel(S_P<Model> NewModel);
	void AddAnimModel(S_P<Anim_Model> NewModel);
	void ChangeRenderTarget(bool ToWindow);
	//Remove Items
	void RemoveTexture(int Id);
	void RemoveShader(int Id);
	void RemoveMaterial(int Id);
	void RemoveMesh(int Id);
	void RemoveAnimMesh(int Id);
	void RemoveModel(int Id);
	void RemoveAnimModel(int Id);
};