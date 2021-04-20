#include "Render_Manager.h"

Render_Manager::Render_Manager(bool Win_Start = false)
	:R_Window(Win_Start)
{
	//Create Default Framebuffer Texture and Main Model to draw on Screen
}

void Render_Manager::Update(float dt)
{
	for (auto& ii : this->All_Models)
	{
		ii->Update();
		ii->UpdateUniforms();
	}
}

void Render_Manager::Render()
{
	for (auto& ii : this->All_Models)
		ii->Render(this->All_Shader[0]);
}

void Render_Manager::RenderToWindow()
{
	this->Main_Model->Render(this->Main_Shader);
}

void Render_Manager::AddTextures(std::shared_ptr<Texture> NewTexture)
{
	this->All_Texture.push_back(NewTexture);
}

void Render_Manager::AddShader(std::shared_ptr<Shader> NewShader)
{
	this->All_Shader.push_back(NewShader);
}

void Render_Manager::AddMesh(std::shared_ptr<Mesh> NewMesh)
{
	this->All_Meshes.push_back(NewMesh);
}

void Render_Manager::AddMaterials(std::shared_ptr<Material> NewMaterial)
{
	this->All_Materials.push_back(NewMaterial);
}

void Render_Manager::AddModel(std::shared_ptr<Model> NewModel)
{
	this->All_Models.push_back(NewModel);
}

void Render_Manager::ChangeRenderTarget(bool ToWindow)
{
	this->R_Window = ToWindow;
}

void Render_Manager::RemoveTexture(int Id)
{
	this->All_Texture.erase(this->All_Texture.begin() + Id);
}

void Render_Manager::RemoveShader(int Id)
{
	this->All_Shader.erase(this->All_Shader.begin() + Id);
}

void Render_Manager::RemoveMesh(int Id)
{
	this->All_Meshes.erase(this->All_Meshes.begin() + Id);
}

void Render_Manager::RemoveMaterial(int Id)
{
	this->All_Materials.erase(this->All_Materials.begin() + Id);
}

void Render_Manager::RemoveModel(int Id)
{
	this->All_Models.erase(this->All_Models.begin() + Id);
}
