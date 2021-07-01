#include "Anim_Model.h"

void Anim_Model::RenderNodes(glm::mat4 ParMatrix, S_P<Node> par, std::vector<glm::mat4> AllMats)
{
	//Calculate the Current Matrix
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

void Anim_Model::UpdateMatrix()
{
	this->ModMatrix = glm::mat4(1.f);
	this->ModMatrix = glm::translate(this->ModMatrix, this->Position);
	glm::mat4 Temps = glm::mat4_cast(this->Rot);
	this->ModMatrix *= Temps;
	this->ModMatrix = glm::scale(this->ModMatrix, this->Scale);
}

Anim_Model::Anim_Model(std::string InitName)
	:Name(InitName),Position(glm::vec3(0.f)), Scale(glm::vec3(1.f))
{
	Quat rs;
	this->Rot = rs.GetQuat();
	this->UpdateMatrix();
}

Anim_Model::Anim_Model(std::string InitName, glm::vec3 InitPos)
	:Name(InitName), Position(InitPos), Scale(glm::vec3(1.f))
{
	Quat rs;
	this->Rot = rs.GetQuat();
	this->UpdateMatrix();
}

Anim_Model::Anim_Model(std::string InitName, glm::vec3 InitPos,
	Vec_SH<Anim_Mesh> Meshes, Vec_SH<Texture> Textures, Vec_SH<Material> Materials)
	:Name(InitName),Position(InitPos), Scale(glm::vec3(1.f))
{
	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
	Quat rs;
	this->Rot = rs.GetQuat();
	this->UpdateMatrix();
}

Anim_Model::Anim_Model(std::string InitName, glm::vec3 InitPos,
	Vec_SH<Anim_Mesh> Meshes, Vec_SH<Texture> Textures, Vec_SH<Material> Materials,
	S_P<Node> InitRoot)
	:Name(InitName),Position(InitPos),Scale(glm::vec3(1.f))
{

	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
	this->Nodes.push_back(InitRoot);
	Quat rs;
	this->Rot = rs.GetQuat();
	this->UpdateMatrix();
}

Anim_Model::~Anim_Model()
{
}

void Anim_Model::Update(float dt)
{
	this->UpdateMatrix();
	for(auto& jj : this->Nodes)
		this->UpdateNodes(jj);
}

void Anim_Model::UpdateUniforms()
{
}

void Anim_Model::Render()
{
	//Calcualtes all the matrices for the Model and its meshes
	if(this->AnimData)
		this->AllMats = this->AnimData->GetMatrices(this->ModMatrix);
	//Render all meshes with textues, materials and shaders
	for(auto& jj : this->Nodes)
		this->RenderNodes(this->ModMatrix, jj, this->AllMats);
}

void Anim_Model::AddMeshes(S_P<Anim_Mesh> NewMesh)
{
	this->Meshes_Inf.push_back(NewMesh);
}

void Anim_Model::AddTextures(S_P<Texture> NewTexture)
{
	this->Textures_Inf.push_back(NewTexture);
}

void Anim_Model::AddMaterials(S_P<Material> NewMaterial)
{
	this->Materials_Inf.push_back(NewMaterial);
}

void Anim_Model::AddShaders(S_P<Shader> NewShader)
{
	this->Shaders_Inf.push_back(NewShader);
}

void Anim_Model::AddNode(S_P<Node> InitRoot)
{
	this->Nodes.push_back(InitRoot);
}

void Anim_Model::SetAnimationData(S_P<AnimationData> InitHandler)
{
	this->AnimData = InitHandler;
}

void Anim_Model::SetName(std::string NewName)
{
	this->Name = NewName;
}

void Anim_Model::SetWMat(glm::mat4 WrldMat)
{
	Math::Decompose(WrldMat, this->Position, this->Rot, this->Scale);
}
