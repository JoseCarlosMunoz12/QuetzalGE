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
                    //this->DisplayChildren(Nd->GetChildren());
                    ImGui::TreePop();
                }
            }
            end();
        }
    }
}
