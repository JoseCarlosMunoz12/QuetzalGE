#pragma once
#include "../Model.h"
#include "../Anim_Model.h"
class Mdl_Ldr :public ASSIMPLOAD_M
{
private:
	std::string File = "Models/ModelCol/";
	//After Check, create the either dynamic or static Primitives to be used in the New Model
	Vec_UP<Primitive> CreateStatic(const aiScene* Scene);
	Vec_UP<A_Primitive> CreateDynamic(const aiScene* Scene);
	void GetChlds(aiNode* Curnd, int Lvl, std::vector<std::string> bns);
public:
	Mdl_Ldr();
	void LoadFile(std::string FileName);

};

