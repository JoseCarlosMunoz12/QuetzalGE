#pragma once
#include "../Model.h"
#include "../Anim_Model.h"
#include "../AnimHandler.h"
class Mdl_Ldr :public ASSIMPLOAD_M
{
private:
	std::string File = "Models/ModelCol/";
	//After Check, create the either dynamic or static Primitives to be used in the New Model
	void CreateStatic(const aiScene* Scene, Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs,
		S_P<Texture> Txts, S_P<Shader> Shdrs);
	void GetChlds(aiNode* Curnd, S_P<Node> MdlNodes);
	glm::mat4 GetMainNode(aiNode* CurNd, std::string RootName);
	//Get Data for the Animation Model and its other functions
	void CreateDynamic(const aiScene* Scene, Vec_SH<Anim_Model>& Mdls,Vec_SH<Anim_Mesh>& Mshs,
		S_P<Texture> Txts, S_P<Shader> Shdrs, S_P<AnimHandler> AnimHndler);
	void AnimChkChlds(aiNode* CurNd, std::vector<std::string>& MshNames);
	std::vector<AnimVertex> A_FinalVertex(aiMesh* Meshes);
	std::vector<GLuint> A_FinalGluint(aiMesh* Meshes);
public:
	Mdl_Ldr();
	void LoadFile(std::string FileName, Vec_SH<Texture> Txts, Vec_SH<Shader> Shdrs,
		Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs,
		Vec_SH<Anim_Model>& A_Mshs, Vec_SH<Anim_Mesh>& A_Mdls, S_P<AnimHandler> AnimHndler);

};

