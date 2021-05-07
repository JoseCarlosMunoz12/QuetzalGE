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
                    ImGui::Text("General information");
                    S_P<Node> Nd = ii->GetNodes();
                    glm::vec3 angles = (180.f / glm::pi<float>()) * glm::eulerAngles(Nd->GetRot());
                    if (ImGui::SliderFloat("X-axis",&angles.x,-180,180))
                    {
                        angles = (glm::pi<float>() / 180.f) * angles;
                        Nd->SetRot(glm::quat(angles));
                    }
                    if (ImGui::SliderFloat("Y-axis", &angles.y, 0, 360))
                    {
                        angles = (glm::pi<float>() / 180.f) * angles;
                        Nd->SetRot(glm::quat(angles));
                    }
                    if (ImGui::SliderFloat("Z-axis", &angles.z, -180, 180))
                    {
                        angles = (glm::pi<float>() / 180.f) * angles;
                        Nd->SetRot(glm::quat(angles));
                    }
                    this->DisplayChildren(Nd->GetChildren());
                    ImGui::TreePop();
                }
            }
            end();
        }
    }
}
