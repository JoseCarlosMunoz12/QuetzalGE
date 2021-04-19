#include "Model.h"

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
