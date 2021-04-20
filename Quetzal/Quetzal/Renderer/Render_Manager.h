#pragma once
#include "Model.h"

class Render_Manager
{
private:
	std::vector<std::shared_ptr<Shader>> All_Shader;
	std::vector<std::shared_ptr<Texture>> All_Texture;
	std::vector<std::shared_ptr<Mesh>> All_Meshes;
	std::vector<std::shared_ptr<Material>> All_Materials;
	std::vector<std::shared_ptr<Model>> All_Models;
public:
	Render_Manager() {}
	//Updates Positions, animations for all Models in the world
	void Update(float dt);
	//Renders all
	void Render();
};

