#include "ParsingData.h"
#include "glm.hpp"
namespace Q_Parser
{
    ParseM_Data GetModelData(pugi::xml_node ModelData)
	{
        ParseM_Data DataFound;
        pugi::xml_node ModData = ModelData.child("ModelData");
        pugi::xml_node ModInformation = ModelData.child("ModelInformation");
        for (pugi::xml_node tool = ModData.child("ModName"); tool; tool = tool.next_sibling("ModName"))
        {
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
                DataFound.FileNames.push_back(attr.value());
        }

        for (pugi::xml_node tool = ModInformation.child("Init"); tool; tool = tool.next_sibling("Init"))
        {
            std::string values = "";
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                values += attr.name();
                values += "*";
                values += attr.value();
                values += "@";
            }
            DataFound.BasicData.push_back(values);
        }
        return DataFound;
	}
}