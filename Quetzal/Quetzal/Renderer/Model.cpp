#include "Model.h"

void Model::UpdateMatrices(std::shared_ptr<Node> chld_Node)
{
	std::vector<std::shared_ptr<Node>> Chlds = chld_Node->GetChildren();
	chld_Node->UpdateMatrix();
	for (auto& ii : Chlds)
		UpdateMatrices(ii);
}

Model::Model(std::string NewName)
	:Position(glm::vec3(0.f))
{
	this->Name = NewName;
}

Model::Model(std::string NewName,glm::vec3 InitPos)
{
	this->Name = NewName;
	this->Position = InitPos;
}

Model::Model(std::string NewName,glm::vec3 InitPos,
	std::vector<std::shared_ptr<Mesh>> Meshes, std::vector<std::shared_ptr<Texture>> Textures, std::vector<std::shared_ptr<Material>> Materials)
{
	this->Name = NewName;
	this->Position = InitPos;
	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
}

void Model::SetPos(glm::vec3 NewPos)
{
	this->Position = NewPos;
	if (Nodes_Inf.size() > 0)
		Nodes_Inf[0]->SetPos(NewPos);
}

void Model::Render(std::shared_ptr<Shader> Shader_Run)
{

}

void Model::Update()
{
	for (auto& ii : this->Nodes_Inf)
		this->UpdateMatrices(ii);
}
