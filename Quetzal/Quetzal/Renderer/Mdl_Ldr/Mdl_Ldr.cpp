#include "Mdl_Ldr.h"


Vec_UP<Primitive> Mdl_Ldr::CreateStatic(const aiScene* Scene)
{
	int Amount_Mshs = Scene->mNumMeshes;
	std::vector<std::string> MshNames;
	Vec_UP<Primitive> Mshs;
	for (int ii = 0; ii < Amount_Mshs; ii++)
	{
		MshNames.push_back(Scene->mMeshes[ii]->mName.C_Str());
		Mshs.push_back(std::make_unique<Primitive>());
		Mshs[ii]->set(this->FinalVertex(Scene->mMeshes[ii]), this->FinalGluint(Scene->mMeshes[ii]));
	}

	return Mshs;
}

Vec_UP<A_Primitive> Mdl_Ldr::CreateDynamic(const aiScene* Scene)
{
	return Vec_UP<A_Primitive>();
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
