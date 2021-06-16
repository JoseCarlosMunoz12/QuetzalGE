#include "Mdl_Ldr.h"

S_P<Model> Mdl_Ldr::CreateStatic(const aiScene* Scene, Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs, S_P<Texture> Txts, S_P<Shader> Shdrs)
{
	int Amount_Mshs = Scene->mNumMeshes;
	glm::mat4 SceneMat;
	std::vector<std::string> MshNames;
	Vec_UP<Primitive> Prm;
	S_P<Node> MdlNodes = std::make_shared<Node>();
	//load meshes and get Meshes names
	for (int ii = 0; ii < Amount_Mshs; ii++)
	{
		MshNames.push_back(Scene->mMeshes[ii]->mName.C_Str());
		Prm.push_back(std::make_unique<Primitive>());
		Prm[ii]->set(this->FinalVertex(Scene->mMeshes[ii]), this->FinalGluint(Scene->mMeshes[ii]));
	}
	//Get the Meshes relative Transform to the Scene
	SceneMat = this->aiMatToglmMat(Scene->mRootNode->mTransformation);
	MdlNodes->SetW_Mat(SceneMat);
	//find all relative Transform to the scene for nodes
	int NumChld = Scene->mRootNode->mNumChildren;
	for (int ii = 0; ii < NumChld; ii++)
		this->GetChlds(Scene->mRootNode->mChildren[ii], MdlNodes);
	//create the meshes to add to main render and to reuse
	Vec_SH<Mesh> Rs;
	int Count = 0;
	for (auto& ii : Prm)
	{
		Rs.push_back(std::make_shared<Mesh>(std::move(ii), MshNames[Count]));
		Mshs.push_back(Rs[Count]);
		Count++;
	}
	//Create model and send out
	S_P<Model> Mdl = std::make_shared<Model>("FileName");
	for (auto& ii : Rs)
		Mdl->AddMeshes(ii);
	Mdl->AddShaders(Shdrs);
	Mdl->AddTextures(Txts);
	Mdl->SetWMat(MdlNodes->GetMatrix());
	for (auto& jj : MdlNodes->GetChildren())
		Mdl->AddNode(jj);
	Mdls.push_back(Mdl);
	return Mdl;
}

Vec_UP<A_Primitive> Mdl_Ldr::CreateDynamic(const aiScene* Scene)
{
	return Vec_UP<A_Primitive>();
}

void Mdl_Ldr::GetChlds(aiNode* Curnd, S_P<Node> MdlNodes)
{
	//Checks if node is an actual
	if (Curnd->mNumMeshes == 0)
		return;
	std::string nm = Curnd->mName.C_Str();
	S_P<Node> Rs = std::make_shared<Node>();
	//Sets the ID mesh for the Node
	for (int jj = 0; jj < Curnd->mNumMeshes; jj++)
		Rs->SetMeshId(Curnd->mMeshes[jj]);
	Rs->AddShaderId(0);
	//Sets Node Location
	glm::mat4 Transform = this->aiMatToglmMat(Curnd->mTransformation);
	Rs->SetW_Mat(Transform);
	//Checks for children if there is any
	for (int ii = 0; ii < Curnd->mNumChildren; ii++)
		this->GetChlds(Curnd->mChildren[ii], Rs);
		MdlNodes->AddChild(Rs);
}

Mdl_Ldr::Mdl_Ldr()
	:ASSIMPLOAD_M("")
{
}

void Mdl_Ldr::LoadFile(std::string FileName, Vec_SH<Texture> Txts, Vec_SH<Shader> Shdrs,
	Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs,
	 Vec_SH<Anim_Model>& A_Mdls,Vec_SH<Anim_Mesh>& A_Mshs)
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
		this->CreateStatic(scene,Mdls,Mshs,Txts[0],Shdrs[0]);
	else
		this->CreateDynamic(scene);
}
