#pragma once
#include "pugixml.hpp"
#include <vector>

namespace Q_Parser
{
	struct ParseM_Data
	{
		std::vector<std::string> FileNames;
		std::vector<std::string> BasicData;
	};
	ParseM_Data GetModelData(pugi::xml_node ModelData);
	ParseM_Data GetTextureData(pugi::xml_node TextureData);
	ParseM_Data GetTextureData(pugi::xml_node TextureData);
	ParseM_Data GetTextureData(pugi::xml_node TextureData);
}