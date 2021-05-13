#include "Model.h"

void Model::UpdateMatrices(std::shared_ptr<Node> chld)
{
	Vec_SH<Node> Chlds = chld->GetChildren();
	chld->UpdateMatrix();
	for (auto& ii : Chlds)
		UpdateMatrices(ii);
}

void Model::RenderNodes(glm::mat4 ParMatrix, std::shared_ptr<Node> chld)
{
	//Check that there is a mesh to render if not ignore it
	int MeshId = chld->GetMeshId();
	//Calc Current Matrix Level
	glm::mat4 CurMatrix = ParMatrix * chld->GetMatrix();
	if (MeshId != -1)
	{
		int ShaderID = chld->GetShaderId();
		//Get Current Level IDs
		std::vector<int> TexId = chld->GetTextId();
		int MatId = chld->GetMatId();
		//Binds and render
		if(MatId != -1)
			this->Materials_Inf[MatId]->SendToShader(this->Shader_Inf[ShaderID]);
		int Count = 0;
		for (auto& ii : TexId)
	{
		this->Textures_Inf[ii]->Bind(Count);
		Count++;
	}
		this->Meshes_Inf[MeshId]->Render(CurMatrix, this->Shader_Inf[ShaderID]);
	}
	//Send to Child Nodes
	std::vector<std::shared_ptr<Node>> Chlds = chld->GetChildren();
	for (auto& ii : Chlds)
		RenderNodes(CurMatrix, ii);
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
	if (Nodes_Inf)
		Nodes_Inf->SetPos(NewPos);
}

void Model::AddMeshes(S_P<Mesh> NewMesh)
{
	this->Meshes_Inf.push_back(NewMesh);
}

void Model::AddTextures(S_P<Texture> NewTexture)
{
	this->Textures_Inf.push_back(NewTexture);
}

void Model::AddMaterials(S_P<Material> NewMaterial)
{
	this->Materials_Inf.push_back(NewMaterial);
}

void Model::AddBaseNode(S_P<Node> NewNode)
{
	this->Nodes_Inf =NewNode;
	this->Nodes_Inf->SetPos(this->Position);
}

void Model::AddShaders(S_P<Shader> NewShader)
{
	this->Shader_Inf.push_back(NewShader);
}

void Model::Render()
{
	glm::mat4 Par = glm::mat4(1.f);
	if (this->Nodes_Inf)
		this->RenderNodes( Par, this->Nodes_Inf);
}

void Model::Update()
{
	this->UpdateMatrices(this->Nodes_Inf);
}

void Model::UpdateUniforms()
{

}
