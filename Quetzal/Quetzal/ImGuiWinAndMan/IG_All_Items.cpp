#include "IG_All_Items.h"

void IG_All_Items::DisplayChildren(Vec_SH<Node> Chld)
{
    for (auto& ii : Chld)
    {
        ii->GetPos();
    }

}

void IG_All_Items::DisplayChildren(S_P<Node> Nd)
{
    glm::vec3 Pos = Nd->GetPos();
    glm::vec3 Ofs = Nd->GetOffset();
    glm::quat Rot = Nd->GetRot();
    glm::vec3 Scl = Nd->GetScale();
    Vec_SH<Node> Chlds = Nd->GetChildren();
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
