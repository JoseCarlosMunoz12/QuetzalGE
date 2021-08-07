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
        if (length - 1 == 0)
            Parts.push_back(s);
        else
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
            int ldcount = 0;
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                values = attr.value();
                std::vector<std::string> vars = tokenize(values, " ");
                switch (ldcount)
                {
                case 0:
                    DataFound[count].Position = glm::vec3(std::stof(vars[0]), std::stof(vars[1]), std::stof(vars[2]));
                    break;
                case 1:
                    DataFound[count].Rotation = glm::quat(std::stof(vars[3]), std::stof(vars[0]), std::stof(vars[1]),std::stof(vars[2]));
                    break;
                default:
                    DataFound[count].Scale= glm::vec3(std::stof(vars[0]), std::stof(vars[1]), std::stof(vars[2]));
                    break;
                }
                ldcount++;
            }
        }
        return DataFound;
	}
    TextureData GetTextureData(pugi::xml_node Texture_Data)
    {
        TextureData Data;
        pugi::xml_node TextFiles = Texture_Data.child("TextureData");
        for (pugi::xml_node tool = TextFiles.child("FileName"); tool; tool = tool.next_sibling("FileName"))
        {
            std::string r = tool.attribute("FileName").value();
            Data.FilesName.push_back(r);
        }
        pugi::xml_node TextInf = Texture_Data.child("TextureNodes");
        for (pugi::xml_node tool = TextInf.child("NodeFormat"); tool; tool = tool.next_sibling("NodeFormat"))
        {
            int count = 0;
            NodeData nData;
            for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
            {
                std::vector<std::string> vars = tokenize(attr.value(), " ");
                switch (count)
                {
                case 0:
                    nData.ModelId = std::stoi(vars[0]);
                    break;
                case 1:
                    for (auto& jj : vars)
                        nData.NodeId.push_back(std::stoi(jj));
                    break;
                default:
                    for (auto& jj : vars)
                        nData.ShaderID.push_back(std::stoi(jj));
                    break;
                }
                count++;
            }
            Data.BasicData.push_back(nData);
        }
        return Data;
    }
    ShaderData GetShaderData(pugi::xml_node Shader_Data)
    {
        int FileTypeID = std::stoi( Shader_Data.attribute("FileType").value());
        pugi::xml_node sData = Shader_Data.child("ShaderData");
        for (pugi::xml_node tool = sData.child("FileName"); tool; tool = tool.next_sibling("FileName"))
        {

        }
        pugi::xml_node nData = Shader_Data.child("ShaderNodes");

        return ShaderData();
    }
    std::vector<NodeData> GetNodeData(pugi::xml_node Node_Data)
    {
        return std::vector<NodeData>();
    }
}