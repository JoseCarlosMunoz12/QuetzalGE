#pragma once
#include "Render_Items/Vertex.h"
#include "Render_Items/Shader.h"
#include "Render_Items/Texture.h"
#include "Render_Items/Material.h"

#include "Anim_Items/Anim_Mesh.h"
#include "Anim_Items/Animation.h"
#include "Anim_Items/AnimationData.h"

class Anim_Model
{
private:
	//Holds pointer to Textures, Meshes, and Materials to use
	Vec_SH<Texture> Textures_Inf;
	Vec_SH<Anim_Mesh> Meshes_Inf;
	Vec_SH<Material> Materials_Inf;
	Vec_SH<Shader> Shaders_Inf;
	Vec_SH<Node> Nodes;
	//Holds All Animations and animation data
	S_P<AnimationData> AnimData;
	std::vector<glm::mat4> AllMats;
	//General information of Model
	glm::vec3 Position;
	glm::quat Rot;
	glm::vec3 Scale;
	glm::mat4 ModMatrix;
	//Name
	std::string Name;
	//Holds Physics, Collision information of the Model

	//Render and Update Recursively
	void RenderNodes(glm::mat4 ParMatrix, S_P<Node> Chld, std::vector<glm::mat4> AllMats);
	void UpdateNodes(S_P<Node> Par);
	void UpdateMatrix();
public:
	Anim_Model(std::string InitName);
	Anim_Model(std::string InitName, glm::vec3 InitPos);
	Anim_Model(std::string InitName, glm::vec3 InitPos,
		Vec_SH<Anim_Mesh> Meshes, Vec_SH<Texture> Textures, Vec_SH<Material> Materials);
	Anim_Model(std::string InitName, glm::vec3 InitPos,
		Vec_SH<Anim_Mesh> Meshes, Vec_SH<Texture> Textures, Vec_SH<Material> Materials,
		S_P<Node> InitRoot);
	~Anim_Model();
	void Update(float dt);
	void UpdateUniforms();
	void Render();
	//Getters
	glm::vec3 GetPos()                { return this->Position; }
	std::string GetName()             { return this->Name; }
	Vec_SH<Anim_Mesh> GetMeshes()     { return this->Meshes_Inf; }
	Vec_SH<Texture> GetTextures()     { return this->Textures_Inf; }
	Vec_SH<Material> GetMaterials()   { return this->Materials_Inf; }
	S_P<AnimationData> GetAnimsInf()  { return this->AnimData; }
	Vec_SH<Shader> GetShaders()       { return this->Shaders_Inf; }
	Vec_SH<Node> GetNodes()           { return this->Nodes; }
	//Setters
	void AddMeshes(S_P<Anim_Mesh> NewMesh);
	void AddTextures(S_P<Texture> NewTexture);
	void AddMaterials(S_P<Material> NewMaterial);
	void AddShaders(S_P<Shader> NewShader);
	void AddNode(S_P<Node> InitRoot);
	void SetAnimationData(S_P<AnimationData> InitHandler);
	void SetName(std::string NewName);
	void SetWMat(glm::mat4 WrldMat);
};
