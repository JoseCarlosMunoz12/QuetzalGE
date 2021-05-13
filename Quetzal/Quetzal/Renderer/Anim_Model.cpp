#include "Anim_Model.h"

void Anim_Model::RenderNodes(glm::mat4 ParMatrix, S_P<Node> par, std::vector<glm::mat4> AllMats)
{
	glm::mat4 CurMat = ParMatrix * par->GetMatrix();
	int MeshId = par->GetMeshId();
	int ShaderId = par->GetShaderId();
	if (MeshId != -1 && ShaderId != -1)
	{
		//Get Current Level IDs
		std::vector<int> TexId = par->GetTextId();
		int MatId = par->GetMatId();
		//Binds and render
		if (MatId != -1)
			this->Materials_Inf[MatId]->SendToShader(this->Shaders_Inf[ShaderId]);
		int Count = 0;
		for (auto& ii : TexId)
		{
			this->Textures_Inf[ii]->Bind(Count);
			Count++;
		}
		this->Meshes_Inf[MeshId]->Render(CurMat, this->Shaders_Inf[ShaderId],AllMats);
	}
	//Send to Child Nodes
	Vec_SH<Node> Chlds = par->GetChildren();
	for (auto& chld : Chlds)
		this->RenderNodes(CurMat, chld, AllMats);
}

void Anim_Model::UpdateNodes(S_P<Node> Par)
{
	Par->UpdateMatrix();
	Vec_SH<Node> Chlds = Par->GetChildren();
	for (auto& Chld : Chlds)
		this->UpdateNodes(Chld);
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
	this->UpdateNodes(this->Roots);
}

void Anim_Model::Render()
{
	if (!this->Roots)
		return;
	//Calcualtes all the matrices for the Model and its meshes
	std::vector<glm::mat4> AllMats = this->Anims[CurAnim]->GetAllMatrix();
	//Render all meshes with textues, materials and shaders
	glm::mat4 r = glm::mat4(1.f);
	this->RenderNodes(r, this->Roots, AllMats);
}
