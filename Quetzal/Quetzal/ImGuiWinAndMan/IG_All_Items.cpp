#include "IG_All_Items.h"

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
                    glm::vec3 pos = ii->GetPos();
                    float ps[3] = { pos.x, pos.y, pos.z };
                    if (ImGui::DragFloat3("position", ps))
                    {
                        pos.x = ps[0];
                        pos.y = ps[1];
                        pos.z = ps[2];
                        ii->SetPos(pos);
                    }
                    /// <summary>
                    /// child nodes
                    /// </summary>
                    ImGui::TreePop();
                }
            }
            end();
        }
    }
}
