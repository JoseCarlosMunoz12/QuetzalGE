#include "IG_All_Items.h"

void IG_All_Items::DisplayChildren(Vec_SH<Node> Chld)
{
    for (auto& ii : Chld)
    {
        ii->GetPos();
    }

}

IG_All_Items::IG_All_Items(std::string Name)
	:WinName(Name)
{
    this->ERs = glm::vec3(0.f, 90.f, 0.f);
    this->QRs = glm::quat((glm::pi<float>() / 180.f) * ERs);
}

IG_All_Items::~IG_All_Items()
{
}

void IG_All_Items::Update()
{
    if (show)
    {
        if (!Begin(this->WinName.c_str()))
        {
            end();
        }
        else
        {           
            ImGui::Text("All Items avaliable in the world");
            Vec_SH<Model> Mdls = this->Base_Render->GetAllModels();
            for (auto& ii : Mdls)
            {
                if (ImGui::TreeNode(ii->GetName().c_str()))
                {
                    this->ERs = glm::eulerAngles(this->QRs);
                    this->ERs = (180.f / glm::pi<float>()) * this->ERs;
                    ImGui::Text("General information");
                    if (ImGui::SliderFloat("X-Axis", &ERs.x, -180, 180))
                        this->QRs = glm::quat((glm::pi<float>() / 180.f) * this->ERs);
                    if (ImGui::SliderFloat("Y-Axis", &ERs.y, -180, 180))
                    {
                        this->ERs = (glm::pi<float>() / 180.f) * this->ERs;
                        this->QRs = glm::quat(this->ERs);
                    }
                    if (ImGui::SliderFloat("Z-Axis", &ERs.z, -180, 180))
                        this->QRs = glm::quat((glm::pi<float>() / 180.f) * this->ERs);
                    //this->DisplayChildren(Nd->GetChildren());
                    ImGui::TreePop();
                }
            }
            end();
        }
    }
}
