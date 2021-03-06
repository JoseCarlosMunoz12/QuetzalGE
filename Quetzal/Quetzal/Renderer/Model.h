#pragma once
#include "Render_Items/Vertex.h"
#include "Render_Items/Shader.h"
#include "Render_Items/Texture.h"
#include "Render_Items/Material.h"
#include "Static_Items/Mesh.h"

class Model
{
private:
	//Holds pointer to Textures, Meshes, and Materials to use
	Vec_SH<Texture> Textures_Inf;
	Vec_SH<Mesh> Meshes_Inf;
	Vec_SH<Material> Materials_Inf;
	Vec_SH<Shader> Shader_Inf;
	//Tree hierarchy of the Model
	S_P<Node> Nodes_Inf;
	Vec_SH<Node> LclNodes;
	//Location, orientation and scale of whole model
	glm::vec3 Position;
	glm::quat Rot;
	glm::vec3 Scale;
	glm::mat4 ModMatrix;
	//Model Name
	std::string Name;
	//Holds Physics, Collision information of the Model
	 
	//Render and Update Recursively
	void UpdateMatrix();
	void UpdateMatrices(std::shared_ptr<Node> chld);
	void RenderNodes(glm::mat4 ParMatrix, std::shared_ptr<Node> chld);
	//----------------------------------
public:
	Model(std::string NewName);
	Model(std::string NewName,glm::vec3 InitPos);
	Model(std::string NewName,glm::vec3 InitPos,
		std::vector<std::shared_ptr<Mesh>> Meshes, std::vector<std::shared_ptr<Texture>> Textures, std::vector<std::shared_ptr<Material>> Materials);
	~Model() {}
	//Setters
	void SetPos(glm::vec3 NewPos)     { this->Position = NewPos; };
	void SetRot(glm::quat NewRot)     { this->Rot = NewRot; }
	void SetScale(glm::vec3 NewScale) { this->Scale = NewScale; }
	void SetWMat(glm::mat4 Inv);
	//Getters
	glm::vec3 GetPos()              { return this->Position; }
	glm::quat GetRot()              { return this->Rot; }
	glm::vec3 GetScale()            { return this->Scale; }
	std::string GetName()           { return this->Name; }
	Vec_SH<Mesh> GetMeshes()        { return this->Meshes_Inf; }
	Vec_SH<Texture> GetTextures()   { return this->Textures_Inf; }
	Vec_SH<Material> GetMaterials() { return this->Materials_Inf; }
	Vec_SH<Node> GetNodes()         { return this->LclNodes; }
	Vec_SH<Shader> GetShaders()     { return this->Shader_Inf; }
	//Add Items
	void AddMeshes(S_P<Mesh> NewMesh);
	void AddTextures(S_P<Texture> NewTexture);
	void AddMaterials(S_P<Material> NewMaterial);
	void AddNode(S_P<Node> NewNode);
	void AddShaders(S_P<Shader> NewShader);
	//Render Model
	void Render();
	//UpdateMatrices
	void Update();
	void UpdateUniforms();
};