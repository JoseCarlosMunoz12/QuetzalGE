#include "ParsingData.h"
#include "glm.hpp"
namespace Q_Parser
{

    std::vector<std::string> tokenize(std::string s, std::string del)
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
    std::vector<ModelData> GetModelData(pugi::xml_node Model_Data)
	{
        std::vector<ModelData> DataFound;
        pugi::xml_node ModData = Model_Data.child("ModelData");
        pugi::xml_node ModInformation = Model_Data.child("ModelInformation");
        for (pugi::xml_node tool = ModData.child("ModName"); tool; tool = tool.next_sibling("ModName"))
        {
            ModelData NewModel;
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                NewModel.FileName = attr.value();
                DataFound.push_back(NewModel);
            }
        }
        int count = 0;
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
        }
        return DataFound;
	}
}