#include "Render_Manager.h"

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
