#pragma once
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

class Model
{
private:
	//Holds pointer to Textures, Meshes, and Materials to use
	std::vector<std::shared_ptr<Texture>> Textures_Inf;
	std::vector<std::shared_ptr<Mesh>> Meshes_Inf;
	std::vector<std::shared_ptr<Material>> Materials_Inf;
	//Tree hierarchy of the Model
	std::vector<std::shared_ptr<Node>> Nodes_Inf;
	//Location, orientation and scale of whole model
	glm::vec3 Position;
	Quat Rotation;
	glm::vec3 Scale;
	std::string Name;
	//Holds Physics, Collision information of the Model
public:
	Model(std::string NewName);
	Model(std::string NewName,
		glm::vec3 InitPos, Quat InitRot, glm::vec3 InitScale);
	Model(std::string NewName,
		glm::vec3 InitPos, Quat InitRot, glm::vec3 InitScale,
		std::vector<std::shared_ptr<Mesh>> Meshes, std::vector<std::shared_ptr<Texture>> Textures, std::vector<std::shared_ptr<Material>> Materials);

	~Model() {}
	//Setters
	void SetPos(glm::vec3 NewPos)     { this->Position = NewPos; }
	void SetRot(Quat NewRot)          { this->Rotation = NewRot; }
	void SetScale(glm::vec3 NewScale) { this->Scale = NewScale; }
	//Getters
	glm::vec3 GetPos()    { return this->Position; }
	Quat GetRot()         { return this->Rotation; }
	glm::vec3 GetScale()  { return this->Scale; }
	std::string GetName() { return this->Name; }
	//Render Model
};