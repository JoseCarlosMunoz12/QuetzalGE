#include "Anim_Model.h"

void Anim_Model::RenderNodes(glm::mat4 ParMatrix, S_P<Node> Chld, std::vector<glm::mat4> AllMats)
{

}

Anim_Model::Anim_Model()
{
}

Anim_Model::~Anim_Model()
{
}

void Anim_Model::Update(float dt)
{
	this->Anims[this->CurAnim]->updateTime(dt);
}

void Anim_Model::Render()
{
	if (!this->AllNodes)
		return;
	//Calcualtes all the matrices for the Model and its meshes
	std::vector<glm::mat4> AllMats = this->Anims[CurAnim]->GetAllMatrix();
	//Render all meshes with textues, materials and shaders
	glm::mat4 r = glm::mat4(1.f);
	this->RenderNodes(r, this->AllNodes, AllMats);
}
