#pragma once
#include "Render_Items/Vertex.h"
#include "Render_Items/Shader.h"
#include "Render_Items/Texture.h"
#include "Render_Items/Material.h"

#include "Anim_Items/Anim_Mesh.h"
#include "Anim_Items/Animation.h"

class Anim_Model
{
private:
	//Holds pointer to Textures, Meshes, and Materials to use
	Vec_SH<Texture> Textures_Inf;
	Vec_SH<Anim_Mesh> Meshes_Inf;
	Vec_SH<Material> Materials_Inf;
	Vec_SH<Shader> Shaders_Inf;
	S_P<Node> Roots;
	//Holds All Animations
	Vec_SH<Animation> Anims;
	//Determines if the animation is dependent on time or not
	bool RunTime;
	int CurAnim;
	//General information of Model
	glm::vec3 Position;
	std::string Name;
	//Holds Physics, Collision information of the Model

	//Render and Update Recursively
	void RenderNodes(glm::mat4 ParMatrix, S_P<Node> Chld, std::vector<glm::mat4> AllMats);
	void UpdateNodes(S_P<Node> Par);
public:
	Anim_Model();
	~Anim_Model();
	void Update(float dt);
	void Render();
	//Getters
	glm::vec3 GetPos()                { return this->Position; }
	std::string GetName()             { return this->Name; }
	Vec_SH<Anim_Mesh> GetMeshes()     { return this->Meshes_Inf; }
	Vec_SH<Texture> GetTextures()     { return this->Textures_Inf; }
	Vec_SH<Material> GetMaterials()   { return this->Materials_Inf; }
	Vec_SH<Animation> GetAnimations() { return this->Anims; }
	Vec_SH<Shader> GetShaders()       { return this->Shaders_Inf; }
	S_P<Node> GetNodes()              { return this->Roots; }
	//Setters
	void AddMesh(S_P<Anim_Mesh> NewMesh);
	void AddTexture(S_P<Texture> NewTexture);
	void AddMaterial(S_P<Material> NewMaterial);
	void AddAnimation(S_P<Animation> NewAnimation);
	void AddShader(S_P<Shader> NewShader);
	void AddBaseNode(S_P<Node> InitRoot);
};

