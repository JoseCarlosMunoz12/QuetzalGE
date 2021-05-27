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

Anim_Model::Anim_Model(std::string InitName, M_S_M I_B_O, M_S_I BoneLoc)
	:CurAnim(0),RunTime(true),Name(InitName),Position(glm::vec3(0.f))
{
}

Anim_Model::Anim_Model(std::string InitName, M_S_M I_B_O, M_S_I BoneLoc, glm::vec3 InitPos)
	:Name(InitName), Position(InitPos), CurAnim(0), RunTime(true)
{
}

Anim_Model::Anim_Model(std::string InitName, glm::vec3 InitPos, M_S_M I_B_O, M_S_I BoneLoc,
	Vec_SH<Anim_Mesh> Meshes, Vec_SH<Texture> Textures, Vec_SH<Material> Materials)
	:Name(InitName),Position(InitPos),CurAnim(0),RunTime(true)
{
	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
}

Anim_Model::Anim_Model(std::string InitName, glm::vec3 InitPos, M_S_M I_B_O, M_S_I BoneLoc, int InitCurAnim, bool Run,
	Vec_SH<Anim_Mesh> Meshes, Vec_SH<Texture> Textures, Vec_SH<Material> Materials,
	S_P<Node> InitRoot, Vec_SH<Animation> InitAnims)
	:Name(InitName),Position(InitPos), CurAnim(InitCurAnim), RunTime(Run)
{
	this->Meshes_Inf = Meshes;
	this->Textures_Inf = Textures;
	this->Materials_Inf = Materials;
	this->Roots = InitRoot;
}

Anim_Model::~Anim_Model()
{
}

void Anim_Model::Update(float dt)
{
	this->AnimData->Update(dt);
	this->UpdateNodes(this->Roots);
}

void Anim_Model::UpdateUniforms()
{
}

void Anim_Model::Render()
{
	if (!this->Roots)
		return;
	//Calcualtes all the matrices for the Model and its meshes	
	this->AllMats = this->AnimData->GetMatrices();
	//Render all meshes with textues, materials and shaders
	glm::mat4 r = glm::mat4(1.f);
	this->RenderNodes(r, this->Roots, this->AllMats);
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

void Anim_Model::AddBaseNode(S_P<Node> InitRoot)
{
	this->Roots = InitRoot;
	this->Roots->SetPos(this->Position);
}

void Anim_Model::SetName(std::string NewName)
{
	this->Name = NewName;
}

void Anim_Model::ChangeCurAnim(int NewAnim)
{
	this->AnimData->ChangeAnim(NewAnim);
}
