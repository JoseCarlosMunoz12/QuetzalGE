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
                    ii->GetNodes()->GetMatrix();                        
                    ImGui::Text("General information");
                    glm::vec3 pos = ii->GetPos();
                    float ps[3] = { pos.x, pos.y, pos.z };
                    if (ImGui::SliderFloat3("Position",ps,-20,20))
                    {
                        pos.x = ps[0];
                        pos.y = ps[1];
                        pos.z = ps[2];
                        ii->SetPos(pos);
                    }
                    S_P<Node> s =ii->GetNodes();
                    if (ImGui::TreeNode("Node Rotation"))
                    {
                        glm::quat sd = s->GetRot();
                        Quat Temp(sd);
                        float AxisAngle = Temp.Angle;
                        glm::vec3 UnitVec = Temp.UnitVec;
                        //Orientation
                        if (ImGui::SliderFloat("Axis Angle",&AxisAngle,0.f,360.f))
                        {
                            Temp.Angle = AxisAngle;
                            s->SetRot(Temp.GetQuat());
                        }
                        //Unit vector
                        if (ImGui::SliderFloat("X Vector",&UnitVec.x,-1,1))
                        {
                            UnitVec= glm::normalize(UnitVec);
                            Temp.UnitVec = UnitVec;
                            s->SetRot(Temp.GetQuat());
                        }
                        if (ImGui::SliderFloat("Y Vector", &UnitVec.y, -1, 1))
                        {
                            UnitVec = glm::normalize(UnitVec);
                            Temp.UnitVec = UnitVec;
                            s->SetRot(Temp.GetQuat());
                        }
                        if (ImGui::SliderFloat("Z Vector", &UnitVec.z, -1, 1))
                        {
                            UnitVec = glm::normalize(UnitVec);
                            Temp.UnitVec = UnitVec;
                            s->SetRot(Temp.GetQuat());
                        }
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
            }
            end();
        }
    }
}
