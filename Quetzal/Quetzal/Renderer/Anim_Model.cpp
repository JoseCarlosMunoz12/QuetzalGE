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
	glm::mat4 r = glm::mat4(1.f);
	for (auto& Nd : this->AllNodes)
		if (Nd.MeshId != -1 && Nd.ShaderId != -1)
		{
			if (Nd.MatId != -1)
			{
				this->Materials_Inf[Nd.MatId]->SendToShader(this->Shaders_Inf[Nd.ShaderId]);
			}
			int Count = 0;
			std::vector<int> Txts = Nd.TextIds;
			for (auto& Txt : Txts)
			{
				this->Textures_Inf[Txt]->Bind(Count);
				Count++;
			}
			this->Meshes_Inf[Nd.MeshId]->Render(r,this->Shaders_Inf[Nd.ShaderId], AllMats);
		}
}
