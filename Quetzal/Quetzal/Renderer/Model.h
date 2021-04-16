#pragma once
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

class Model
{
private:
	//Holds pointer to Textures being used
	std::vector<std::shared_ptr<Texture>> Textures_Inf;
	std::vector<std::shared_ptr<Mesh>> Meshes_Inf;
	std::vector<std::shared_ptr<Node>> Nodes_Inf;

public:

};

