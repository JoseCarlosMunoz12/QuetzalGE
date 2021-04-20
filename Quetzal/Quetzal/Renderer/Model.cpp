#include "Model.h"

void Model::UpdateMatrices(std::shared_ptr<Node> chld)
{
	std::vector<std::shared_ptr<Node>> Chlds = chld->GetChildren();
	chld->UpdateMatrix();
	for (auto& ii : Chlds)
		UpdateMatrices(ii);
}

void Model::RenderNodes(std::shared_ptr<Shader> Cur_Shader, glm::mat4 ParMatrix, std::shared_ptr<Node> chld)
{
	//Calc Current Matrix Level
	glm::mat4 CurMatrix = ParMatrix * chld->GetMatrix();
	//Get Current Level IDs
	std::vector<int> TexId = chld->GetTextId();
	int MeshId = chld->GetMeshId();
	int MatId = chld->GetMatId();
	//Binds and render
	this->Materials_Inf[MatId]->SendToShader(Cur_Shader);
	int Count = 0;
	for (auto& ii : TexId)
	{
		this->Textures_Inf[ii]->Bind(Count);
		Count++;
	}
	this->Meshes_Inf[MeshId]->Render(CurMatrix, Cur_Shader);
	//Send to Child Nodes
	std::vector<std::shared_ptr<Node>> Chlds = chld->GetChildren();
	for (auto& ii : Chlds)
		RenderNodes(Cur_Shader, CurMatrix, ii);
}

Model::Model(std::string NewName)
	:Position(glm::vec3(0.f))
{
	this->Name = NewName;
}

Model::Model(std::string NewName,glm::vec3 InitPos)
{
	this->Name = NewName;
	this->Position = InitPos;
}

Model::Model(std::string NewName,glm::vec3 InitPos,
	std::vector<std::shared_ptr<Mesh>> Meshes, std::vector<std::shared_ptr<Texture>> Textures, std::vector<std::shared_ptr<Material>> Materials)
{
	this->Name = NewName;
	this->Position = InitPos;
	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
}

void Model::SetPos(glm::vec3 NewPos)
{
	this->Position = NewPos;
	if (Nodes_Inf.size() > 0)
		Nodes_Inf[0]->SetPos(NewPos);
}

void Model::Render(std::shared_ptr<Shader> Shader_Run)
{
	glm::mat4 Par = glm::mat4(1.f);
	for (auto& ii : this->Nodes_Inf)
		this->RenderNodes(Shader_Run, Par, ii);
}

void Model::Update()
{
	for (auto& ii : this->Nodes_Inf)
		this->UpdateMatrices(ii);
}

void Model::UpdateUniforms()
{

}
