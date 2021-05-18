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
	A_Primitive()
	{

	}
	virtual ~A_Primitive()
	{

	}
	void set(const AnimVertex* vertices, const unsigned nrofVertices,
		const GLuint* indices, const unsigned nrOfIndices)
	{
		for (int i = 0; i < nrofVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}
		for (int i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
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
	std::vector<A_Primitive> GetPrimitives(glm::mat4& InitInv)
	{
		Assimp::Importer importer;
		std::vector<A_Primitive> Mshs;
		const aiScene* scene = importer.ReadFile(File, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
		if (!scene)
		{

			std::cout << "Error";
			return Mshs;
		}
		int msh_num = scene->mNumMeshes;
		for (int ii = 0; ii < msh_num; ii++)
		{
			Mshs.push_back(this->GetMesh(scene->mMeshes[ii]));
		}
		InitInv = this->aiMatToglmMat(scene->mRootNode->mTransformation);
	}
	std::vector<A_Primitive> GetPrimitives(glm::mat4& InitInv, Vec_SH<Animation>& Animations)
	{
		Assimp::Importer importer;
		std::vector<A_Primitive> Mshs;
		const aiScene* scene = importer.ReadFile(File, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
		if (!scene)
		{

			std::cout << "Error";
			return Mshs;
		}
		int msh_num = scene->mNumMeshes;
		for (int ii = 0; ii < msh_num; ii++)
		{
			scene->mMeshes[ii];
		}
		InitInv = this->aiMatToglmMat(scene->mRootNode->mTransformation);
		
		int anims = scene->mNumAnimations;
		for (int ii = 0; ii < anims; ii++)
		{
		}
	}
	void Test()
	{
		Assimp::Importer importer;
		std::vector<A_Primitive> Mshs;
		const aiScene* scene = importer.ReadFile(File, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
		//Get All Meshes
		std::vector<AnimVertex> rs = this->FinalVertex(scene->mMeshes[0]);
		std::vector<GLuint> Indices = this->FinalGluint(scene->mMeshes[0]);
		//Set the Ides for all the Meshes
		this->SetBonesId(scene->mMeshes[0], rs);
		//Get the Animation skeleton frames
		Vec_SH<Animation> Animations = {};
		if (scene->HasAnimations())
		{
			Animations.push_back(std::make_shared<Animation>());
			this->GetAnimations(scene->mAnimations[0], Animations[0]);
		}
		std::cout << "arse\n";
	}
private:
	std::string File;
	glm::mat4 aiMatToglmMat(aiMatrix4x4 aiVal)
	{
		glm::mat4 glmVal = glm::mat4(aiVal.a1, aiVal.b1, aiVal.c1, aiVal.d1,
			aiVal.a2, aiVal.b2, aiVal.c2, aiVal.d2,
			aiVal.a3, aiVal.b3, aiVal.c3, aiVal.d3,
			aiVal.a4, aiVal.b4, aiVal.c4, aiVal.d4);
		return glmVal;
	}
	glm::vec3 aiVecToglmVec(aiVector3D aiVal)
	{
		return glm::vec3(aiVal.x, aiVal.y, aiVal.z);
	}
	A_Primitive GetMesh(const aiMesh* mesh)
	{
		A_Primitive Msh;
		Msh.set(this->FinalVertex(mesh),this->FinalGluint(mesh));
	}
	//functions to load Ints and Vertecies
	std::vector<AnimVertex> FinalVertex(const aiMesh* Meshes)
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
	std::vector<GLuint> FinalGluint(const aiMesh* Meshes)
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
	void SetBonesId(aiMesh* meshes, std::vector<AnimVertex>& Vertx)
	{
		for (int ii = 0; ii < meshes->mNumBones; ii++)
		{
			std::string BoneName = meshes->mBones[ii]->mName.C_Str();
			aiBone* TempBone = meshes->mBones[ii];
			for (int jj = 0; jj < TempBone->mNumWeights; jj++)
			{
				int VertId = TempBone->mWeights[jj].mVertexId;
				float Weight = TempBone->mWeights[jj].mWeight;
				this->SetIndex(Vertx[VertId], ii, Weight);
			}
		}
	}
	void SetIndex(AnimVertex& Vert, int BoneID, float BoneWieght)
	{
		if (Vert.MatId.x == -1)
		{
			Vert.MatId.x = BoneID;
			Vert.Weights.x = BoneWieght;
		}
		else if (Vert.MatId.y == -1)
		{
			Vert.MatId.y = BoneID;
			Vert.Weights.y = BoneWieght;
		}
		else if (Vert.MatId.z == -1)
		{
			Vert.MatId.z = BoneID;
			Vert.Weights.z = BoneWieght;
		}
		else if (Vert.MatId.w == -1)
		{
			Vert.MatId.w = BoneID;
			Vert.Weights.w = BoneWieght;
		}
	}
	//Functions to load Animations
	void GetAnimations(aiAnimation* Anim, S_P<Animation>& SetAnims)
	{
		SetAnims->SetCurTime(0);
		SetAnims->SetTimeLength(Anim->mDuration);
		SetAnims->GetName()
	}
};