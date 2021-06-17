#pragma once

#include <vector>
#include <map>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Render_Items/Vertex.h"
#include "Animation.h"

class A_Primitive

{
private:
	std::vector<AnimVertex> vertices;
	std::vector<GLuint> indices;

public:
	A_Primitive() {}
	virtual ~A_Primitive() {}
	void set(const AnimVertex* vertices, const unsigned nrofVertices,
		const GLuint* indices, const unsigned nrOfIndices)
	{
		for (int i = 0; i < nrofVertices; i++)
			this->vertices.push_back(vertices[i]);
		for (int i = 0; i < nrOfIndices; i++)
			this->indices.push_back(indices[i]);
	}
	void set(std::vector<AnimVertex> vertexFound, std::vector<GLuint> indicesFound)
	{
		this->vertices = vertexFound;
		this->indices = indicesFound;
	}
	inline AnimVertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class A_ASSIMP_LOAD
{
public:
	A_ASSIMP_LOAD(const char* FileLoc)
	{
		File = "Models/ModelCol/";
		File += FileLoc;		
	}
	Vec_UP<A_Primitive> GetPrimitives(glm::mat4& InitInv,
		std::map<std::string, glm::mat4>& BnInits, std::map<std::string,glm::mat4>& InitTransMat, std::map<std::string,int>& matLocs, Vec_SH<Animation>& Animations)
	{
		Assimp::Importer importer;
		Vec_UP<A_Primitive> Mshs;
		const aiScene* scene = importer.ReadFile(File, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
		if (!scene)
		{
			std::cout << "Error";
			return Mshs;
		}
		//Find all Bones in the animations along with offsets
		int msh_num = scene->mNumMeshes;
		Vec_SH<Anim_Skels> Bones;
		for (int ii = 0; ii < msh_num; ii++)
			this->FindAllBones(scene,scene->mMeshes[ii],Bones);
		BnInits = this->BoneOffsets;
		matLocs = BoneLoc;
		//Get relationships of Childs and parents along with offsets
		int Count = 0;
		int Par = 0;
		this->FindChilds(scene->mRootNode, Par, Count);
		//create correct id and Create the root nodes
		//And load meshes into the primitives
		for (int ii = 0; ii < msh_num; ii++)
		{
			std::vector<AnimVertex> rs = this->A_FinalVertex(scene->mMeshes[ii]);
			std::vector<GLuint> Indices = this->A_FinalGluint(scene->mMeshes[ii]);
			this->SetBonesId(scene->mMeshes[ii], rs);
			Mshs.push_back(std::make_unique<A_Primitive>());
			Mshs[ii]->set(rs, Indices);
		}
		//create the Skel Node
		this->SetTree(Bones);
		int anims = scene->mNumAnimations;
		for (int ii = 0; ii < anims; ii++)
		{
			int Size = Animations.size();
			Animations.push_back(std::make_shared<Animation>());
			this->GetAnimations(scene->mAnimations[ii], Animations[Size],Bones);
			Animations[Size]->SetInvMatrix(InitInv);
		}		
		InitInv = this->GetLocalMatrix(scene->mRootNode, Bones[0]->GetName());
		InitTransMat = TransMats;
		importer.FreeScene();
		return Mshs;
	}
private:
	struct Par_Child_Rel
	{
		int Par;
		int Id;
	};
	std::string File;
	std::map<std::string, Par_Child_Rel> BoneId;
	glm::mat4 A_aiMatToglmMat(aiMatrix4x4 from)
	{
		glm::mat4 to{};
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}
	glm::vec3 A_aiVecToglmVec(aiVector3D aiVal)
	{
		return glm::vec3(aiVal.x, aiVal.y, aiVal.z);
	}
	glm::quat A_aiQuatToglmQuat(aiQuaternion aiVal)
	{
		return glm::quat(aiVal.w, aiVal.x, aiVal.y, aiVal.z);
	}
protected:
	std::map<std::string, glm::mat4> BoneOffsets;
	std::map<std::string, glm::mat4> TransMats;
	std::map <std::string, int> BoneLoc;
	void ClearMaps()
	{
		this->BoneOffsets.clear();
		this->TransMats.clear();
		this->BoneLoc.clear();
		this->BoneId.clear();
	}
	//functions to load Ints and Vertecies
	std::vector<AnimVertex> A_FinalVertex(const aiMesh* Meshes)
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
	std::vector<GLuint> A_FinalGluint(const aiMesh* Meshes)
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
	//functions to load Bone data from file
	void FindAllBones(const aiScene* scene, aiMesh* meshes,Vec_SH<Anim_Skels>& Bones)
	{
		for (int ii = 0; ii < meshes->mNumBones; ii++)
		{
			aiBone* TempBone = meshes->mBones[ii];
			std::string BoneName = TempBone->mName.C_Str();
			if (BoneOffsets.find(BoneName) == BoneOffsets.end())
			{
				int Skels = BoneOffsets.size();
				BoneOffsets[BoneName] = A_aiMatToglmMat(TempBone->mOffsetMatrix);
				BoneLoc[BoneName] = Skels;
				glm::mat4 TransMat = this->A_aiMatToglmMat(scene->mRootNode->FindNode(BoneName.c_str())->mTransformation);
				TransMats[BoneName] = TransMat;
				glm::vec3 Offsets; glm::vec3 Scale; glm::quat Rot;
				Math::Decompose(TransMat, Offsets, Rot, Scale);
				Bones.push_back(std::make_shared<Anim_Skels>(BoneName, TransMat, Offsets, Rot, Scale));
				BoneId[BoneName].Id = Skels;
			}
		}
	}
	void SetBonesId(aiMesh* meshes, std::vector<AnimVertex>& Vertx)
	{
		for (int ii = 0; ii < meshes->mNumBones; ii++)
		{
			aiBone* TempBone = meshes->mBones[ii];
			std::string BoneName = TempBone->mName.C_Str();
			for (int jj = 0; jj < TempBone->mNumWeights; jj++)
			{
				int VertId = TempBone->mWeights[jj].mVertexId;
				float Weight = TempBone->mWeights[jj].mWeight;
				this->SetIndex(&Vertx[VertId], BoneLoc[BoneName], Weight);
			}
		}
	}
	void SetIndex(AnimVertex* Vert, int BoneID, float BoneWieght)
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
	//Functions to load Animations
	void GetAnimations(aiAnimation* Anim, S_P<Animation>& SetAnims, Vec_SH<Anim_Skels> Base_Bones)
	{
		//Init the animation and set the bast information
		SetAnims->SetCurTime(0);
		float TcksPerSec = Anim->mTicksPerSecond;
		float NumTick = Anim->mDuration;
		float TotalTime = NumTick / TcksPerSec;
		SetAnims->SetTimeLength(TotalTime);
		SetAnims->SetName(Anim->mName.C_Str());		
		int NumChannels = Anim->mNumChannels;
		Vec_SH<Anim_Skels> Bones;
		//creates base Bones to add animation data
		this->CopyValues(Bones, Base_Bones);
		//set frames, transmat and OffsetMatrix
		for (int ii = 0; ii < NumChannels; ii++)
		{
			aiNodeAnim* rs = Anim->mChannels[ii];
			std::string Bone_Name = rs->mNodeName.C_Str();
			if (BoneOffsets.find(Bone_Name) != BoneOffsets.end())
			{
				int NumOfRot = rs->mNumRotationKeys;
				Vec_SH<Frames> Frms;			
				for (int jj = 0; jj < NumOfRot; jj++)
				{
					float F_Time = rs->mRotationKeys[jj].mTime;
					F_Time = F_Time / NumTick * TotalTime;
					glm::quat Rot = this->A_aiQuatToglmQuat(rs->mRotationKeys[jj].mValue);
					glm::vec3 Scale = this->A_aiVecToglmVec(rs->mScalingKeys[jj].mValue);
					glm::vec3 Offset = this->A_aiVecToglmVec(rs->mPositionKeys[jj].mValue);
					Joint T_Joint = {Offset, Rot, Scale};
					Frms.push_back(std::make_shared<Frames>(F_Time, T_Joint));
				}
				//add animation frames to the bones
				for (auto& kk : Bones)
					if (kk->GetName() == Bone_Name)
					{
						kk->SetFrames(Frms);
						break;
					}
			}
		}
		while (Bones.size() != 1)
			Bones.pop_back();
		SetAnims->SetSkels(Bones[0]);
	}
	void FindChilds(aiNode* Node,int Par, int& Count)
	{
		std::string name = Node->mName.C_Str();
		if (BoneOffsets.find(name) != BoneOffsets.end())
		{
			Count++;
			BoneId[name].Par = Par-1;
		}
		int ParID = Count;		
		int NumChilds = Node->mNumChildren;
		for (int ii = 0; ii < NumChilds; ii++)
			this->FindChilds(Node->mChildren[ii],ParID,Count);
	}
	void SetTree(Vec_SH<Anim_Skels>& BaseBones)
	{
		for (auto& jj : BaseBones)
		{
			int Id = BoneId[jj->GetName()].Par;
			if (Id > -1)
				BaseBones[Id]->SetChild(jj);
		}
	}
	void CopyValues(Vec_SH<Anim_Skels>& NewSkels, Vec_SH<Anim_Skels> BaseSkels)
	{
		glm::vec3 Offsets;
		glm::quat Rot;
		glm::vec3 Scale;
		std::string BoneName;
		glm::mat4 TransMat = glm::mat4(1.f);
		for (auto& jj : BaseSkels)
		{
			//Copy basic Data
			Offsets = jj->GetCurOffset();
			Rot = jj->GetCurRot();
			Scale = jj->GetCurScale();
			BoneName = jj->GetName();
			//Get Transmat
			TransMat = glm::mat4(1.f);
			TransMat = glm::translate(TransMat,Offsets);
			TransMat = TransMat * glm::mat4_cast(Rot);
			TransMat = glm::scale(TransMat, Scale);
			//Create AnimSkel to use
			NewSkels.push_back(std::make_shared<Anim_Skels>(BoneName, TransMat, Offsets, Rot, Scale));
		}
		//set Childrens
		this->SetTree(NewSkels);
	}
	glm::mat4 GetLocalMatrix(aiNode* AnimNode, std::string BoneName)
	{
		aiNode* Root = AnimNode->FindNode(BoneName.c_str());
		aiNode* Par = Root->mParent;
		glm::mat4 R = glm::mat4(1.f);
		if (!Par)
			return R;
		R = this->A_aiMatToglmMat(Par->mTransformation);
		return this->GetParMatrix(Par) * R;
	}
private:
	glm::mat4 GetParMatrix(aiNode* CurNode)
	{
		aiNode* Par = CurNode->mParent;
		glm::mat4 r = glm::mat4(1.f);
		if (!Par)
			return r;
		r = this->A_aiMatToglmMat(Par->mTransformation);
		return this->GetParMatrix(Par) * r;
	}
};