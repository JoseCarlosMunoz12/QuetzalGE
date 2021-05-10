#include "IG_All_Items.h"

void IG_All_Items::DisplayChildren(S_P<Node> Nd)
{
    glm::vec3 Pos = Nd->GetPos();
    float Ps[3] = { Pos.x, Pos.y, Pos.z };
    glm::vec3 Ofs = Nd->GetOffset();
    float OS[3] = {Ofs.x, Ofs.y, Ofs.z};
    glm::quat Rot = Nd->GetRot();
    Quat rs; rs.SetQuat(Rot);
    glm::vec3 Scl = Nd->GetScale();
    float Scle[3] = {Scl.x, Scl.y, Scl.z};
    Vec_SH<Node> Chlds = Nd->GetChildren();

    if (ImGui::DragFloat3("Position", Ps, 1, -20, 20))
    {
        Pos.x = Ps[0];
        Pos.y = Ps[1];
        Pos.z = Ps[2];
        Nd->SetPos(Pos);        
    }
    if (ImGui::DragFloat3("Offset", OS, 1, -20, 20))
    {
        Ofs.x = OS[0];
        Ofs.y = OS[1];
        Ofs.z = OS[2];
        Nd->SetOffset(Ofs);
    }
    if (ImGui::DragFloat("Angle",&rs.Angle,1,-180,180))
        Nd->SetRot(rs.GetQuat());

    for (auto& ii : Chlds)
    {
        if (ImGui::TreeNode("ChildS"))
        {
            this->DisplayChildren(ii);
            ImGui::TreePop();
        }
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
                    this->DisplayChildren(ii->GetNodes());
                    ImGui::TreePop();
                }
            }
            end();
        }
    }
}
