#pragma once
#include "../Model.h"
#include "../Anim_Model.h"
#include "../AnimHandler.h"
#include "ParsingData.h"

using namespace Q_Parser;
class Q_Loader : public ASSIMPLOAD_M
{
private:
	
public:
	Q_Loader();
	void LoadQ_File(std::string FileName, Vec_SH<Texture> Txts, Vec_SH<Shader> Shdrs,
		Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs,
		Vec_SH<Anim_Model>& A_Mdls, Vec_SH<Anim_Mesh>& A_Mshs, S_P<AnimHandler> AnimHndler);
};