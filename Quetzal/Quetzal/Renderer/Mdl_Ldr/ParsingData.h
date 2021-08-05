#pragma once
#include "pugixml.hpp"
#include <vector>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>

namespace Q_Parser
{
	struct ModelData
	{
		std::string FileName;
		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;
	};
	struct NodeData
	{
		int ModelId;
		std::vector<int> NodeId;
		std::vector<int> ShaderID;
	};
	struct TextureData
	{
		std::vector<std::string> FilesName;
		std::vector<NodeData> BasicData;
	};
	struct ShaderData
	{
		std::vector<std::string> FileNames;
		std::vector<NodeData> BasicData;
	};
	struct ParseM_Data
	{
		std::vector<std::string> FileNames;
		std::vector<std::string> BasicData;
	};
	std::vector<std::string> tokenize(std::string s, std::string del);
	std::vector<ModelData> GetModelData(pugi::xml_node ModelData);
	ParseM_Data GetTextureData(pugi::xml_node TextureData);
	ParseM_Data GetTextureData(pugi::xml_node TextureData);
	ParseM_Data GetTextureData(pugi::xml_node TextureData);
}