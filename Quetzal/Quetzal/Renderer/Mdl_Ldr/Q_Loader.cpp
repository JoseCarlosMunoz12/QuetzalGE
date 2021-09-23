#include "Q_Loader.h"
using namespace Q_Parser;
Q_Loader::Q_Loader()
	:ASSIMPLOAD_M("")
{
}

std::vector<std::string> Q_Loader::tokenize(std::string s, std::string del)
{
	int start = 0;
	int end = s.find(del);
	int length = s.length();
	std::vector<std::string> Parts;
	while (end != -1)
	{
		Parts.push_back(s.substr(start, end - start));
		start = end + del.size();
		end = s.find(del, start);
	}
	Parts.push_back(s.substr(start, length - 1));
	return Parts;
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
	std::vector<std::string> Parse = tokenize(FileName,"\\");
	int size = Parse.size();
	std::string Loc = "";
	for (int ii = 0; ii < size - 1; ii++)
		Loc += Parse[ii] + "\\";
	//search for all related files to load
	for (auto& jj : Models)
	{
		std::string ModLoc = Loc + jj.FileName;
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(ModLoc, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
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
	}
}
