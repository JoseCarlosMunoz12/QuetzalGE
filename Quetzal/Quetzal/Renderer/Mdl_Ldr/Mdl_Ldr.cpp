#include "Mdl_Ldr.h"

Vec_UP<Primitive> Mdl_Ldr::CreateStatic(const aiScene* Scene)
{
	int Amount_Mshs = Scene->mNumMeshes;
	glm::mat4 SceneMat;
	std::vector<std::string> MshNames;
	Vec_UP<Primitive> Mshs;
	S_P<Node> MdlNodes = std::make_shared<Node>();
	//load meshes and get Meshes names
	for (int ii = 0; ii < Amount_Mshs; ii++)
	{
		MshNames.push_back(Scene->mMeshes[ii]->mName.C_Str());
		Mshs.push_back(std::make_unique<Primitive>());
		Mshs[ii]->set(this->FinalVertex(Scene->mMeshes[ii]), this->FinalGluint(Scene->mMeshes[ii]));
	}
	//Get the Meshes relative Transform to the Scene
	SceneMat = this->aiMatToglmMat(Scene->mRootNode->mTransformation);
	MdlNodes->SetW_Mat(SceneMat);
	//find all relative Transform to the scene for nodes
	int NumChld = Scene->mRootNode->mNumChildren;
	for(int ii = 0; ii < NumChld; ii++)
		this->GetChlds(Scene->mRootNode->mChildren[ii], 1, MshNames, MdlNodes);
	//create the models and meshes

	return Mshs;
}

Vec_UP<A_Primitive> Mdl_Ldr::CreateDynamic(const aiScene* Scene)
{
	return Vec_UP<A_Primitive>();
}

void Mdl_Ldr::GetChlds(aiNode* Curnd, int Lvl, std::vector<std::string> bns, S_P<Node> MdlNodes)
{
	//Checks if node is an actual
	if (Curnd->mNumMeshes == 0)
		return;
	std::string nm = Curnd->mName.C_Str();
	S_P<Node> Rs = std::make_shared<Node>();
	//Sets the ID mesh for the Node
	for (int jj = 0; jj < Curnd->mNumMeshes; jj++)
		Rs->SetMeshId(Curnd->mMeshes[jj]);
	//Sets Node Location
	glm::mat4 Transform = this->aiMatToglmMat(Curnd->mTransformation);
	Rs->SetW_Mat(Transform);
	//Checks for children if there is any
	for (int ii = 0; ii < Curnd->mNumChildren; ii++)
		this->GetChlds(Curnd->mChildren[ii], Lvl + 1, bns, Rs);
		MdlNodes->AddChild(Rs);
}

Mdl_Ldr::Mdl_Ldr()
	:ASSIMPLOAD_M("")
{
}

void Mdl_Ldr::LoadFile(std::string FileName)
{
	File;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(File + FileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
	//Checks if file is valid or exists
	if (!scene)
	{
		std::cout << "Error";
		return;
	}
	//checks file to see if it has bones, to see if it's an A_Primitive
	int MshNums = scene->mNumMeshes;
	bool IsDynamic = false;
	for (int ii = 0; ii < MshNums; ii++)
		if (scene->mMeshes[ii]->HasBones())
		{
			IsDynamic = true;
			break;
		}
	//Creates anim or static model to be used
	if (!IsDynamic)
		this->CreateStatic(scene);
	else
		this->CreateDynamic(scene);
}
