#pragma once
#include "Model.h"
template <typename T>
using S_P = std::shared_ptr<T>;
template <typename T>
using Vec_SH = std::vector<S_P<T>>;
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
	S_P<Texture> Main_Texture;
	S_P<Model> Main_Model;
public:
	Render_Manager();
	//Updates Positions, animations for all Models in the world
	void Update(float dt);
	//Renders all
	void Render();
	//Getters
	Vec_SH<Texture> GetAllTextures()   { return this->All_Texture; }
	Vec_SH<Shader> GetAllShaders()     { return this->All_Shader; }
	Vec_SH<Mesh> GetAllMeshes()        { return this->All_Meshes; }
	Vec_SH<Material> GetAllMaterials() { return this->All_Materials; }
	Vec_SH<Model> GetAllModels()       { return this->All_Models; }
	//Setters
	void AddTextures(std::shared_ptr<Texture> NewTexture);
	void AddShader(std::shared_ptr<Shader> NewShader);
	void AddMesh(std::shared_ptr<Mesh> NewMesh);
	void AddMaterials(std::shared_ptr<Material> NewMaterial);
	void AddModel(std::shared_ptr<Model> NewModel);
	//Remove Items
};