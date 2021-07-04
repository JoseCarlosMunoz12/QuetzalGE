#include "IG_All_Items.h"

void IG_All_Items::DisplayChildren(S_P<Node> Nd, Vec_SH<Mesh> VecMesh, Vec_SH<Texture>VecTex, Vec_SH<Material> VecMat)
{
    //Standard position, rotation and scale data
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
    if (ImGui::DragFloat3("Position", Ps, 1.f, -20.f, 20.f))
    {
        Pos.x = Ps[0];
        Pos.y = Ps[1];
        Pos.z = Ps[2];
        Nd->SetPos(Pos);        
    }
    if (ImGui::DragFloat3("Offset", OS, 1.f, -20.f, 20.f))
    {
        Ofs.x = OS[0];
        Ofs.y = OS[1];
        Ofs.z = OS[2];
        Nd->SetOffset(Ofs);
    }
    if (ImGui::DragFloat("Angle",&rs.Angle,.1f,-180.f,180.f))
        Nd->SetRot(rs.GetQuat());
    if (ImGui::DragFloat3("UnitVec", Unit, .01f, -1.f, 1.f))
    {
        rs.UnitVec.x = Unit[0];
        rs.UnitVec.y = Unit[1];
        rs.UnitVec.z = Unit[2];
        rs.UnitVec = glm::normalize(rs.UnitVec);
        Nd->SetRot(rs.GetQuat());
    }
    if (ImGui::DragFloat3("Scale", Scle,1.f,0.f,5.f))
    {
        Scl.x = Scle[0];
        Scl.y = Scle[1];
        Scl.z = Scle[2];
        Nd->SetScale(Scl);
    }
    //Information about the Textures and Materials used for this
    if (ImGui::TreeNode("See Other Information"))
    {
        std::vector<int> Tx_Id = Nd->GetTextId();
        int Ms_Id = Nd->GetMeshId();
        int Mt_Id = Nd->GetMatId();
        if (Tx_Id.size() > 0)
            for (auto& ii : Tx_Id)
                ImGui::Text(VecTex[ii]->GiveChar());
        else
            ImGui::Text("No Texture Assigned!");
        if (Ms_Id >= 0)
            ImGui::Text(VecMesh[Ms_Id]->GiveName());
        else
            ImGui::Text("No Mesh Assigned!!!");
        if (Mt_Id >= 0)
            ImGui::Text(VecMat[Mt_Id]->GetName());
        else
            ImGui::Text("No Material Assigned");
        ImGui::TreePop();
    }
    //Display Child Data
    if (ImGui::TreeNode("Child Information"))
    {
        for (auto& ii : Chlds)
        {
            if (ImGui::TreeNode("ChildS"))
            {
                this->DisplayChildren(ii, VecMesh, VecTex, VecMat);
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
}

void IG_All_Items::DisplayChildren(S_P<Node> Nd, Vec_SH<Anim_Mesh> VecMesh, Vec_SH<Texture>VecTex, Vec_SH<Material> VecMat)
{
    //Standard position, rotation and scale data
    glm::vec3 Pos = Nd->GetPos();
    float Ps[3] = { Pos.x, Pos.y, Pos.z };
    glm::vec3 Ofs = Nd->GetOffset();
    float OS[3] = { Ofs.x, Ofs.y, Ofs.z };
    glm::quat Rot = Nd->GetRot();
    Quat rs; rs.SetQuat(Rot);
    float Unit[3] = { rs.UnitVec.x, rs.UnitVec.y,rs.UnitVec.z };
    glm::vec3 Scl = Nd->GetScale();
    float Scle[3] = { Scl.x, Scl.y, Scl.z };
    Vec_SH<Node> Chlds = Nd->GetChildren();
    //Information of the position relative to the item
    if (ImGui::DragFloat3("Position", Ps, 0.1f, -20.f, 20.f))
    {
        Pos.x = Ps[0];
        Pos.y = Ps[1];
        Pos.z = Ps[2];
        Nd->SetPos(Pos);
    }
    if (ImGui::DragFloat3("Offset", OS, 0.1f, -20.f, 20.f))
    {
        Ofs.x = OS[0];
        Ofs.y = OS[1];
        Ofs.z = OS[2];
        Nd->SetOffset(Ofs);
    }
    if (ImGui::DragFloat("Angle", &rs.Angle, .1f, -180.f, 180.f))
        Nd->SetRot(rs.GetQuat());
    if (ImGui::DragFloat3("UnitVec", Unit, .01f, -1.f, 1.f))
    {
        rs.UnitVec.x = Unit[0];
        rs.UnitVec.y = Unit[1];
        rs.UnitVec.z = Unit[2];
        rs.UnitVec = glm::normalize(rs.UnitVec);
        Nd->SetRot(rs.GetQuat());
    }
    if (ImGui::DragFloat3("Scale", Scle, 0.1f, 0.f, 5.f))
    {
        Scl.x = Scle[0];
        Scl.y = Scle[1];
        Scl.z = Scle[2];
        Nd->SetScale(Scl);
    }
    //Information about the Textures and Materials used for this
    if (ImGui::TreeNode("See Other Information"))
    {
        std::vector<int> Tx_Id = Nd->GetTextId();
        int Ms_Id = Nd->GetMeshId();
        int Mt_Id = Nd->GetMatId();
        if (Tx_Id.size() > 0)
            for (auto& ii : Tx_Id)
                ImGui::Text(VecTex[ii]->GiveChar());
        else
            ImGui::Text("No Texture Assigned!");
        if (Ms_Id >= 0)
            ImGui::Text(VecMesh[Ms_Id]->GiveName());
        else
            ImGui::Text("No Mesh Assigned!!!");
        if (Mt_Id >= 0)
            ImGui::Text(VecMat[Mt_Id]->GetName());
        else
            ImGui::Text("No Material Assigned");
        ImGui::TreePop();
    }
    //Display Child Data
    if (ImGui::TreeNode("Child Information"))
    {
        for (auto& ii : Chlds)
        {
            if (ImGui::TreeNode("ChildS"))
            {
                this->DisplayChildren(ii, VecMesh, VecTex, VecMat);
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
}

void IG_All_Items::DisplayData(S_P<Model> Mdl)
{
    if (ImGui::TreeNode(Mdl->GetName().c_str()))
    {
        Vec_SH<Mesh> Mshs = Mdl->GetMeshes();
        Vec_SH<Texture> Txt = Mdl->GetTextures();
        Vec_SH<Material> Mts = Mdl->GetMaterials();
        glm::vec3 Pos = Mdl->GetPos();
        glm::vec3 Scale = Mdl->GetScale();
        glm::quat Rot = Mdl->GetRot();
        //display general position, rotation and scale of the Model
        float mPs[3] = { Pos.x, Pos.y, Pos.z };
        float Scl[3] = { Scale.x, Scale.y, Scale.z };
        Quat rs; 
        float Vecs[3] = { rs.UnitVec.x,rs.UnitVec.y, rs.UnitVec.z };
        rs.SetQuat(Rot);
        float Unit[3] = { rs.UnitVec.x, rs.UnitVec.y,rs.UnitVec.z };
        if (ImGui::SliderFloat3("Model Position", mPs, -20.f, 20.f))
        {
            Pos.x = mPs[0]; Pos.y = mPs[1]; Pos.z = mPs[2];
            Mdl->SetPos(Pos);
        }
        if (ImGui::SliderFloat3("Model Scale", Scl, 0.f, 20.f))
        {
            Scale.x = Scl[0]; Scale.y = Scl[1]; Scale.z = Scl[2];
            Mdl->SetScale(Scale);
        }
        if (ImGui::SliderFloat("Model Unit Angle", &rs.Angle, -180.f, 180.f))
            Mdl->SetRot(rs.GetQuat());
        if (ImGui::SliderFloat3("Model Unit Vector",Vecs, 0.f, 1.f))
        {
            rs.UnitVec.x = Vecs[0]; rs.UnitVec.y = Vecs[2]; rs.UnitVec.z = Vecs[2];
            rs.UnitVec = glm::normalize(rs.UnitVec);
            Mdl->SetRot(rs.GetQuat());
        }
        //Internal Node Data
        if (ImGui::TreeNode("Model Nodes Information"))
        {
            for (auto& jj : Mdl->GetNodes())
                this->DisplayChildren(jj, Mshs, Txt, Mts);
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

void IG_All_Items::DisplayData(S_P<Anim_Model> Mdl)
{
    if (ImGui::TreeNode(Mdl->GetName().c_str()))
    {
        //Get basic Data From Anim Model
        S_P<AnimationData> Anims = Mdl->GetAnimsInf();
        M_S_B Blnds =  Anims->GetBlends();
        S_P<Animation> CurAnim = Anims->GetCurrentAnim();
        std::vector<std::string> A_Names = Anims->GetAllAnims();// all Animations
        std::vector<std::string> B_Names = Anims->GetAllBlends();// all Blending creation
        std::string CurAnimId = Anims->GetAnimId();// current animation or blending system
        //display Animation data
        if (ImGui::TreeNode("All Animations Assign to the Model"))
        {
            if (A_Names.size() != 0)
            {   
                bool AnimInUse = false;
                for (auto& jj : A_Names)
                {
                    if (!AnimInUse)
                        AnimInUse = jj == CurAnimId;
                    if (ImGui::Selectable(jj.c_str(), jj == CurAnimId))
                        Anims->ChangeAnim(jj);
                }
            }
            else
                ImGui::Text("Animation Model has no Animation");
            ImGui::TreePop();
        }
        //Display Bledning Data and if it exist, display all ratios
        if (ImGui::TreeNode("All Blending Assign to the Model"))
        {
            if (B_Names.size() != 0)
            {
                bool BlendInUse = false;
                for (auto& jj : B_Names)
                {
                    if (!BlendInUse)
                        BlendInUse = jj == CurAnimId;
                    if (ImGui::Selectable(jj.c_str(), jj == CurAnimId))
                        Anims->ChangeAnim(jj);
                }
                if (BlendInUse)
                {
                    std::string CurAnimID = Anims->GetAnimId();
                    M_S_F Rts = Blnds[CurAnimID]->GetBlendRatios();
                    for (auto& jj : Rts)
                    {
                        float Rt = jj.second;
                        if (ImGui::SliderFloat(jj.first.c_str(), &Rt, 0, 1))
                            Rts[jj.first] = Rt;
                    }
                }
            }
            else
                ImGui::Text("Animation Model has no blending Animation");
            ImGui::TreePop();
        }
        //display Data about the nodes
        Vec_SH<Anim_Mesh> Mshs = Mdl->GetMeshes();
        Vec_SH<Texture> Txt = Mdl->GetTextures();
        Vec_SH<Material> Mts = Mdl->GetMaterials();
        for(auto& jj : Mdl->GetNodes())
            this->DisplayChildren(jj, Mshs, Txt, Mts);
        ImGui::TreePop();
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
            end();
        else
        {           
            ImGui::Text("All Items avaliable in the world");
            Vec_SH<Model> Mdls = this->Base_Render->GetAllModels();
            Vec_SH<Anim_Model> AMdls = this->Base_Render->GetAllAnimModel();
            for (auto& ii : Mdls)
            {
                this->DisplayData(ii);
            }
            for (auto& ii : AMdls)
            {
                this->DisplayData(ii);
            }
            end();
        }
    }
}
