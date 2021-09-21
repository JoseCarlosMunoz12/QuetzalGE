#pragma once
#include "../Model.h"
#include "../Anim_Model.h"
#include "../AnimHandler.h"
#include "ParsingData.h"
#include "Q_Loader.h"
using M_S_Sk = std::map<std::string, S_P<Skels>>;
class Mdl_Ldr :public ASSIMPLOAD_M,public Q_Loader
{
private:
	glm::quat aiQuatToglmQuat(aiQuaternion aiVal);
	std::string File = "Models/ModelCol/";
	std::string TextureFile = "Images/";
	//After Check, create the either dynamic or static Primitives to be used in the New Model
	void CreateStatic(const aiScene* Scene, Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs,
		S_P<Texture> Txts, S_P<Shader> Shdrs, std::string Filename);
	void GetChlds(aiNode* Curnd, S_P<Node> MdlNodes, std::string RootNode);
	glm::mat4 GetMainNode(aiNode* CurNd, std::string RootName);
	//Get Data for the Animation Model and its other functions
	void CreateDynamic(const aiScene* Scene, Vec_SH<Anim_Model>& Mdls, Vec_SH<Anim_Mesh>& Mshs,
		S_P<Texture> Txts, S_P<Shader> Shdrs, S_P<AnimHandler> AnimHndler, std::string Filename);
	S_P<Animation> MakeAnimation(aiAnimation* animation);
	void FinalAllBones(const aiScene* scene, aiMesh* meshes, M_S_BI& BonesInf,M_S_Sk& BonesSkel);
	S_P<Skels> Skeleton(const aiScene* scene, M_S_Sk Bones);
	void SetIndex(AnimVertex* Vert, int BoneID, float BoneWieght);
	void SetBonesID(aiMesh* meshes, std::vector<AnimVertex>& Vertx, M_S_BI BonesInf);
	std::vector<AnimVertex> A_FinalVertex(aiMesh* Meshes);
	std::vector<GLuint> A_FinalGluint(aiMesh* Meshes);
	std::vector<std::string> tokenize(std::string s, std::string del = " ");
public:
	Mdl_Ldr();
	void LoadFile(std::string FileName, Vec_SH<Texture> Txts, Vec_SH<Shader> Shdrs,
		Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs,
		Vec_SH<Anim_Model>& A_Mshs, Vec_SH<Anim_Mesh>& A_Mdls, S_P<AnimHandler> AnimHndler);

};

