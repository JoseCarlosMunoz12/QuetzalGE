#include "Model.h"

void Model::UpdateMatrix()
{
	this->ModMatrix = glm::mat4(1.f);
	this->ModMatrix = glm::translate(this->ModMatrix, this->Position);
	glm::mat4 Temps = glm::mat4_cast(this->Rot);
	this->ModMatrix *= Temps;
	this->ModMatrix = glm::scale(this->ModMatrix, this->Scale);
}

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
	int ShaderID = chld->GetShaderId();
	if (MeshId != -1 && ShaderID !=-1)
	{
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
	:Position(glm::vec3(0.f)), Scale(glm::vec3(1.f))
{
	Quat rs;
	this->Rot = rs.GetQuat();
	this->UpdateMatrix();
	this->Name = NewName;
}

Model::Model(std::string NewName, glm::vec3 InitPos)
	:Scale(glm::vec3(1.f))
{
	this->Name = NewName;
	this->Position = InitPos;
	Quat rs;
	this->Rot = rs.GetQuat();
	this->UpdateMatrix();
}

Model::Model(std::string NewName,glm::vec3 InitPos,
	std::vector<std::shared_ptr<Mesh>> Meshes, std::vector<std::shared_ptr<Texture>> Textures, std::vector<std::shared_ptr<Material>> Materials)
	:Scale(glm::vec3(1.f))
{
	this->Name = NewName;
	this->Position = InitPos;
	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
	Quat rs;
	this->Rot = rs.GetQuat();
	this->UpdateMatrix();
}

void Model::SetWMat(glm::mat4 Inv)
{
	Math::Decompose(Inv, this->Position, this->Rot, this->Scale);
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

void Model::AddNode(S_P<Node> NewNode)
{
	this->LclNodes.push_back(NewNode);
}

void Model::AddShaders(S_P<Shader> NewShader)
{
	this->Shader_Inf.push_back(NewShader);
}

void Model::Render()
{
	for (auto& jj : this->LclNodes)
		this->RenderNodes(this->ModMatrix, jj);
}

void Model::Update()
{
	this->UpdateMatrix();
	for (auto& jj : this->LclNodes)
		this->UpdateMatrices(jj);
}

void Model::UpdateUniforms()
{

}
