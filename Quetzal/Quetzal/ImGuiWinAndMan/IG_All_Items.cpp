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
    if (ImGui::DragFloat3("Scale", Scle, 1.f, 0.f, 5.f))
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
        this->DisplayChildren(Mdl->GetNodes(), Mshs, Txt, Mts);
        ImGui::TreePop();
    }
}

void IG_All_Items::DisplayData(S_P<Anim_Model> Mdl)
{
    if (ImGui::TreeNode(Mdl->GetName().c_str()))
    {
        //Get basic Data From Anim Modle
        Vec_SH<Anim_Mesh> Mshs = Mdl->GetMeshes();
        Vec_SH<Texture> Txt = Mdl->GetTextures();
        Vec_SH<Material> Mts = Mdl->GetMaterials();
        S_P<AnimationData> Anims = Mdl->GetAnimsInf();
        S_P<Animation> CurAnim = Anims->GetCurrentAnim();
        std::vector<std::string> A_Names = Anims->GetAllAnims();
        //See if it is running or not
        bool rt = CurAnim->GetLoopId() == -1;
        //track the current time for current animation
        float A_Dt = CurAnim->GetCurTime();
        if (ImGui::Checkbox("Manual", &rt))
        {
            if (rt)
                CurAnim->SetLoopId(-1);
            else
                CurAnim->SetLoopId(0);
        }
        //display Animation data
        if (ImGui::TreeNode("All Animations Assign to the Model"))
        {
            for (auto& jj : A_Names)
                ImGui::Text(jj.c_str());
            ImGui::TreePop();
        }
        //display Data about the nodes
        this->DisplayChildren(Mdl->GetNodes(), Mshs, Txt, Mts);
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
