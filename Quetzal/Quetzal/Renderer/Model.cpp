#include "Model.h"

Model::Model(std::string NewName)
	:Position(glm::vec3(0.f)), Rotation(Quat()), Scale(glm::vec3(1.f))
{
	this->Name = NewName;
}

Model::Model(std::string NewName,
	glm::vec3 InitPos, Quat InitRot, glm::vec3 InitScale)
{
	this->Name = NewName;
	this->Position = InitPos;
	this->Rotation = InitRot;
	this->Scale = InitScale;
}

Model::Model(std::string NewName,
	glm::vec3 InitPos, Quat InitRot, glm::vec3 InitScale,
	std::vector<std::shared_ptr<Mesh>> Meshes, std::vector<std::shared_ptr<Texture>> Textures, std::vector<std::shared_ptr<Material>> Materials)
{
	this->Name = NewName;
	this->Position = InitPos;
	this->Rotation = InitRot;
	this->Scale = InitScale;
	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
}
