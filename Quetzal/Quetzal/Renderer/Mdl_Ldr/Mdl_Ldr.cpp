#include "Mdl_Ldr.h"

void Mdl_Ldr::CreateStatic(const aiScene* Scene,
	Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs, S_P<Texture> Txts, S_P<Shader> Shdrs)
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
}

void Mdl_Ldr::CreateDynamic(const aiScene* Scene,
	Vec_SH<Anim_Model>& Mdls, Vec_SH<Anim_Mesh>& Mshs, S_P<Texture> Txts, S_P<Shader> Shdrs, S_P<AnimHandler> AnimHndler)
{
	M_S_BI BoneInf;
	Vec_UP<A_Primitive> A_Mshs;
	Vec_SH<Animation> Animations;
	std::vector<std::string> MshNames;
	S_P<Node> MdlNodes = std::make_shared<Node>();
	int msh_num = Scene->mNumMeshes;
	//Get Bones Data
	for (int ii = 0; ii < msh_num; ii++)
		this->FinalAllBones(Scene, Scene->mMeshes[ii], BoneInf);
	//Get Vertex Data
	for (int ii = 0; ii < msh_num; ii++)
	{
		std::vector<AnimVertex> rs = this->A_FinalVertex(Scene->mMeshes[ii]);
		std::vector<GLuint> Indices = this->A_FinalGluint(Scene->mMeshes[ii]);
		A_Mshs.push_back(std::make_unique<A_Primitive>());
		this->SetBonesID(Scene->mMeshes[ii], rs, BoneInf);
		A_Mshs[ii]->set(rs, Indices);
		MshNames.push_back(Scene->mMeshes[ii]->mName.C_Str());
	}
	//Create the Skeleton
	std::cout << "e";
}

void Mdl_Ldr::GetChlds(aiNode* Curnd, S_P<Node> MdlNodes)
{
	S_P<Node> Rs = MdlNodes;
	//Checks if node is an actual
	if (Curnd->mNumMeshes != 0)
	{
		Rs = std::make_shared<Node>();
		std::string nm = Curnd->mName.C_Str();
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
}

glm::mat4 Mdl_Ldr::GetMainNode(aiNode* CurNd, std::string RootName)
{
	aiNode* Par = CurNd->mParent;
	if (!Par)
		return glm::mat4(1.f);
	if (Par->mName.C_Str() == RootName)
		return this->aiMatToglmMat(CurNd->mTransformation);
	return this->GetMainNode(Par,RootName) * this->aiMatToglmMat(CurNd->mTransformation);
}

void Mdl_Ldr::AnimChkChlds(aiNode* CurNd, std::vector<std::string>& MshNames)
{

}

void Mdl_Ldr::FinalAllBones(const aiScene* scene, aiMesh* meshes, M_S_BI& BonesInf)
{
	for (int jj = 0; jj < meshes->mNumBones; jj++)
	{
		aiBone* TempBone = meshes->mBones[jj];
		std::string BoneName = TempBone->mName.C_Str();
		if (BonesInf.find(BoneName) == BonesInf.end())
		{
			int Skels = BonesInf.size();
			BonesInf[BoneName].BoneOffset = aiMatToglmMat(TempBone->mOffsetMatrix);
			BonesInf[BoneName].Id = Skels;
			glm::mat4 TransMat = this->aiMatToglmMat(scene->mRootNode->FindNode(BoneName.c_str())->mTransformation);
			BonesInf[BoneName].TransMats = TransMat;
		}
	}
}

void Mdl_Ldr::SetIndex(AnimVertex* Vert, int BoneID, float BoneWieght)
{
	if (Vert->MatId.x == -1)
	{
		Vert->MatId.x = BoneID;
		Vert->Weights.x = BoneWieght;
	}
	else if (Vert->MatId.y == -1)
	{
		Vert->MatId.y = BoneID;
		Vert->Weights.y = BoneWieght;
	}
	else if (Vert->MatId.z == -1)
	{
		Vert->MatId.z = BoneID;
		Vert->Weights.z = BoneWieght;
	}
	else if (Vert->MatId.w == -1)
	{
		Vert->MatId.w = BoneID;
		Vert->Weights.w = BoneWieght;
	}

}

void Mdl_Ldr::SetBonesID(aiMesh* meshes, std::vector<AnimVertex>& Vertx, M_S_BI BonesInf)
{
	for (int ii = 0; ii < meshes->mNumBones; ii++)
	{
		aiBone* TempBone = meshes->mBones[ii];
		std::string BoneName = TempBone->mName.C_Str();
		for (int jj = 0; jj < TempBone->mNumWeights; jj++)
		{
			int VertId = TempBone->mWeights[jj].mVertexId;
			float Weight = TempBone->mWeights[jj].mWeight;
			this->SetIndex(&Vertx[VertId], BonesInf[BoneName].Id, Weight);
		}
	}
}

std::vector<AnimVertex> Mdl_Ldr::A_FinalVertex(aiMesh* Meshes)
{
	std::vector<AnimVertex> TempVerts;
	for (int ii = 0; ii < Meshes->mNumVertices; ii++)
	{
		AnimVertex NewVertex{};
		//Position
		NewVertex.position.x = Meshes->mVertices[ii].x;
		NewVertex.position.y = Meshes->mVertices[ii].y;
		NewVertex.position.z = Meshes->mVertices[ii].z;
		//Normals
		NewVertex.normal.x = Meshes->mNormals[ii].x;
		NewVertex.normal.y = Meshes->mNormals[ii].y;
		NewVertex.normal.z = Meshes->mNormals[ii].z;
		//Texture Coordinates
		NewVertex.texcoord.x = Meshes->mTextureCoords[0][ii].x;
		NewVertex.texcoord.y = Meshes->mTextureCoords[0][ii].y;
		//MatIDs
		NewVertex.MatId.x = -1;
		NewVertex.MatId.y = -1;
		NewVertex.MatId.z = -1;
		NewVertex.MatId.w = -1;
		//MatWieghts
		NewVertex.Weights.x = 0.f;
		NewVertex.Weights.y = 0.f;
		NewVertex.Weights.z = 0.f;
		NewVertex.Weights.w = 0.f;

		TempVerts.push_back(NewVertex);
	}
	return TempVerts;
}

std::vector<GLuint> Mdl_Ldr::A_FinalGluint(aiMesh* Meshes)
{
	std::vector<GLuint> TempInd;
	for (int ii = 0; ii < Meshes->mNumFaces; ii++)
	{
		aiFace face = Meshes->mFaces[ii];
		TempInd.push_back(face.mIndices[0]);
		TempInd.push_back(face.mIndices[1]);
		TempInd.push_back(face.mIndices[2]);
	}
	return TempInd;
}

Mdl_Ldr::Mdl_Ldr()
	:ASSIMPLOAD_M("")
{
}

void Mdl_Ldr::LoadFile(std::string FileName, Vec_SH<Texture> Txts, Vec_SH<Shader> Shdrs,
	Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs,
	 Vec_SH<Anim_Model>& A_Mdls,Vec_SH<Anim_Mesh>& A_Mshs, S_P<AnimHandler> AnimHndler)
{
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
		this->CreateDynamic(scene,A_Mdls,A_Mshs,Txts[1],Shdrs[1], AnimHndler);
}
