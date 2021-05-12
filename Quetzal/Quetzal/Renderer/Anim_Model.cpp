#include "Anim_Model.h"

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
	//Calcualtes all the matrices for the Model and its meshes
	std::vector<glm::mat4> AllMats = this->Anims[CurAnim]->GetAllMatrix();
	//Render all meshes with textues, materials and shaders
	//TO DO
	//
}
