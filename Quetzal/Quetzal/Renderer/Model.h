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

};