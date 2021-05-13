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
	S_P<Node> AllNodes;
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
public:
	Anim_Model();
	~Anim_Model();
	void Update(float dt);
	void Render();
	glm::vec3 GetPos() { return this->Position; }
	std::string GetName() { return this->Name; }
	Vec_SH<Anim_Mesh> GetMeshes() { return this->Meshes_Inf; }
	Vec_SH<Texture> GetTextures() { return this->Textures_Inf; }
	Vec_SH<Material> GetMaterials() { return this->Materials_Inf; }
	Vec_SH<Animation> GetAnimations() { return this->Anims; }
};

