#pragma once
#include "../Anim_Items/Anim_Primitive.h"
#include "../Static_Items/Primitive.h"
class Mdl_Ldr :public ASSIMPLOAD_M
{
private:
	std::string File = "Models/ModelCol/";
	//After Check, create the either dynamic or static Primitives to be used in the New Model
	Vec_UP<Primitive> CreateStatic(const aiScene* Scene);
	Vec_UP<A_Primitive> CreateDynamic();
public:
	Mdl_Ldr();
	void LoadFile(std::string FileName);

};

