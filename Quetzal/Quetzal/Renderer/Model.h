#pragma once
#include "Render_Items/Vertex.h"
#include "Render_Items/Shader.h"
#include "Render_Items/Texture.h"
#include "Render_Items/Material.h"
#include "Render_Items/Mesh.h"

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
	std::string Name;
	//Holds Physics, Collision information of the Model
	 
	//Render and Update Recursively
	void UpdateMatrices(std::shared_ptr<Node> chld);
	void RenderNodes(std::shared_ptr<Shader> Cur_Shader, glm::mat4 ParMatrix, std::shared_ptr<Node> chld);
	//----------------------------------
public:
	Model(std::string NewName);
	Model(std::string NewName,glm::vec3 InitPos);
	Model(std::string NewName,glm::vec3 InitPos,
		std::vector<std::shared_ptr<Mesh>> Meshes, std::vector<std::shared_ptr<Texture>> Textures, std::vector<std::shared_ptr<Material>> Materials);
	~Model() {}
	//Setters
	void SetPos(glm::vec3 NewPos);
	//Getters
	glm::vec3 GetPos()    { return this->Position; }
	std::string GetName() { return this->Name; }
	//Render Model
	void Render(std::shared_ptr<Shader> Shader_Run);
	//UpdateMatrices
	void Update();
	void UpdateUniforms();
};