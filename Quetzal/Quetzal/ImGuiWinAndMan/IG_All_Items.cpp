#include "IG_All_Items.h"

void IG_All_Items::DisplayChildren(S_P<Node> Nd, Vec_SH<Mesh> VecMesh, Vec_SH<Texture>VecTex, Vec_SH<Material> VecMat)
{
    glm::vec3 Pos = Nd->GetPos();
    float Ps[3] = { Pos.x, Pos.y, Pos.z };
    glm::vec3 Ofs = Nd->GetOffset();
    float OS[3] = {Ofs.x, Ofs.y, Ofs.z};
    glm::quat Rot = Nd->GetRot();
    Quat rs; rs.SetQuat(Rot);
    float Unit[3] = {rs.UnitVec.x, rs.UnitVec.y,rs.UnitVec.z};
    glm::vec3 Scl = Nd->GetScale();
    float Scle[3] = {Scl.x, Scl.y, Scl.z};
    Vec_SH<Node> Chlds = Nd->GetChildren();
    //Information of the position relative to the item
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
    if (ImGui::DragFloat3("UnitVec", Unit, .01, 5, 5))
    {
        rs.UnitVec = glm::normalize(rs.UnitVec);
        Nd->SetRot(rs.GetQuat());
    }
    if (ImGui::DragFloat3("Scale", Scle,1,0,5))
    {
        Scl.x = Scle[0];
        Scl.y = Scle[1];
        Scl.z = Scle[2];
        Nd->SetScale(Scl);
    }
    //Information about the Textures and Materials used for this
    std::vector<int> Tx_Id = Nd->GetTextId();
    int Ms_Id = Nd->GetMeshId();
    int Mt_Id = Nd->GetMatId();
    //Display Child Data
    for (auto& ii : Chlds)
    {
        if (ImGui::TreeNode("ChildS"))
        {
            this->DisplayChildren(ii,VecMesh,VecTex,VecMat);
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
                    Vec_SH<Mesh> Mshs = ii->GetMeshes();
                    Vec_SH<Texture> Txt = ii->GetTextures();
                    Vec_SH<Material> Mts = ii->GetMaterials();
                    this->DisplayChildren(ii->GetNodes(),Mshs,Txt,Mts);
                    ImGui::TreePop();
                }
            }
            end();
        }
    }
}
