#include "Q_Loader.h"
using namespace Q_Parser;
Q_Loader::Q_Loader()
{
}

void Q_Loader::LoadQ_File(std::string FileName, Vec_SH<Texture> Txts, Vec_SH<Shader> Shdrs, Vec_SH<Model>& Mdls, Vec_SH<Mesh>& Mshs, Vec_SH<Anim_Model>& A_Mdls, Vec_SH<Anim_Mesh>& A_Mshs, S_P<AnimHandler> AnimHndler)
{
	pugi::xml_document doc;
	if (!doc.load_file(FileName.c_str()))
		return;
	pugi::xml_node Model_Data = doc.child("FileID").child("Model");
	pugi::xml_node Texture_Data = doc.child("FileID").child("Texture");
	pugi::xml_node Shader_Data = doc.child("FileID").child("Shader");
	pugi::xml_node Nodes_Data = doc.child("FileID").child("Nodes");
	std::vector<Q_Parser::ModelData> Models = Q_Parser::GetModelData(Model_Data);
	TextureData Textures = GetTextureData(Texture_Data);
	ShaderData Shaders = Q_Parser::GetShaderData(Shader_Data);
	std::vector<Q_Parser::ModNodeRel> Nodes = Q_Parser::GetNodeData(Nodes_Data);
	//Generate Models with Data
	for (auto& jj : Models)
	{
	}
}
