#include "Anim_Skels.h"

Frames::Frames(float InitTime, Joint InitJoint, InterType InitType)
{
    this->Time_Stamp = InitTime;
    this->Jnt = InitJoint;
    this->Type = InitType;
    this->Bias = {0.f,0.f};
}

glm::quat Frames::GetRot()
{
    return this->Jnt.Rotation;
}

glm::vec3 Frames::GetOffset()
{
    return this->Jnt.Offset;
}

glm::vec3 Frames::GetScale()
{
    return this->Jnt.Scale;
}

Bezier_Bais Frames::GetBezier()
{
    return this->Bias;
}

InterType Frames::GetType()
{
    return this->Type;
}

float Frames::GetTimeStamp()
{
    return this->Time_Stamp;
}

void Frames::SetRot(glm::quat NewRot)
{
    this->Jnt.Rotation = NewRot;
}

void Frames::SetOffset(glm::vec3 NewOffset)
{
    this->Jnt.Offset = NewOffset;
}

void Frames::SetScale(glm::vec3 NewScale)
{
    this->Jnt.Scale = NewScale;
}

void Frames::SetBezier(Bezier_Bais NewBias)
{
    this->Bias = NewBias;
}

void Frames::SetType(InterType NewType)
{
    this->Type = NewType;
}

///------------------------------------------------------------------------------------------------------------
/// Skeleton class
///------------------------------------------------------------------------------------------------------------

Vec_SH<Frames> Anim_Skels::GetFrames(float Time)
{
    int Count = 0;
    for (auto& Frm : Skel_Frames)
    {
        if (Frm->GetTimeStamp() > Time)
            break;
        Count++;
    }
    if(Count == 0)
        return { Skel_Frames[Count], Skel_Frames[Count + 1]};
    if (Count == Skel_Frames.size())
        return { Skel_Frames[Count - 1], Skel_Frames[Count - 1] };
    return { Skel_Frames[Count-1], Skel_Frames[Count]};
}

glm::vec3 Anim_Skels::LinInter(glm::vec3 Init, glm::vec3 Final, float Ratio)
{
    glm::vec3 rt_Chng = Final - Init;    
    return Init + rt_Chng * Ratio;
}

float Anim_Skels::GetTimeRatio(float Time, Vec_SH<Frames> Frms)
{
    float TimeLeft = Time - Frms[0]->GetTimeStamp();
    float FrameDiff = Frms[1]->GetTimeStamp() - Frms[0]->GetTimeStamp();
    if (FrameDiff == 0)
        return 0.f;
    return TimeLeft / FrameDiff;
}

void Anim_Skels::GetInterpolations(glm::vec3& NewCurO, glm::vec3& NewCurS, glm::quat& NewCurR, float Time)
{
    //Get Frames and time ratio to calculate
    Vec_SH<Frames> Frms = this->GetFrames(Time);
    float TimeRatio = this->GetTimeRatio(Time, Frms);
    InterType Type = Frms[0]->GetType();
    //Get New parts of the Matrix
    switch (Type)
    {
    case InterType::HOLD:
        NewCurR = Frms[0]->GetRot();
        NewCurO = Frms[0]->GetOffset();
        NewCurS = Frms[0]->GetScale();
        break;
    case InterType::LINEAR:
        NewCurR = glm::slerp(Frms[0]->GetRot(), Frms[1]->GetRot(), TimeRatio);
        NewCurO = this->LinInter(Frms[0]->GetOffset(), Frms[1]->GetOffset(), TimeRatio);
        break;
    case InterType::QUADBENZ:
        break;
    case InterType::CUBEBENZ:
        break;
    }
}

void Anim_Skels::UpdateMatrix(float Time)
{
    if (this->Skel_Frames.size() != 0)
    {
        //Gets local offsets, rotation and scale based on the time and frames
        this->GetInterpolations(this->CurOffset, this->CurScale, this->CurRot,Time);
        //Calculate the matrix
        this->Matrix = glm::mat4(1.f);
        this->Matrix = glm::translate(this->Matrix, this->CurOffset);
        this->Matrix = this->Matrix * glm::mat4_cast(this->CurRot);
        this->Matrix = glm::scale(this->Matrix, this->CurScale);
    }
    else
    {
        this->Matrix = this->TransMat;
        Math::Decompose(this->Matrix, this->CurOffset, this->CurRot, this->CurScale);
    }
}

Anim_Skels::Anim_Skels(Vec_SH<Frames> InitFrames, std::string InitName, glm::mat4 InitMat, glm::mat4 IOffset,
    glm::vec3 InitOffset, glm::quat InitQuat, glm::vec3 InitScale)
    :CurOffset(InitOffset), CurScale(InitScale), CurRot(InitQuat)
{
    this->Bone_Name = InitName;
    this->Skel_Frames = InitFrames;
    this->Matrix = InitMat;
    this->Offset = IOffset;
}

glm::mat4 Anim_Skels::GetMatrix(float CurTime)
{
    this->UpdateMatrix(CurTime);
    return this->Matrix;
}

glm::mat4 Anim_Skels::GetOffset()
{
    return this->Offset;
}

Vec_SH<Anim_Skels> Anim_Skels::GetChildren()
{
    return this->Chlds;
}

glm::vec3 Anim_Skels::GetCurOffset()
{
    return this->CurOffset;
}

glm::vec3 Anim_Skels::GetCurScale()
{
    return this->CurScale;
}

glm::quat Anim_Skels::GetCurRot()
{
    return this->CurRot;
}

Vec_SH<Frames> Anim_Skels::GetFrames()
{
    return this->Skel_Frames;
}

void Anim_Skels::SetCurOffset(glm::vec3 NewOffset)
{
    this->CurOffset = NewOffset;
}

void Anim_Skels::SetCurScale(glm::vec3 NewScale)
{
    this->CurScale = NewScale;
}

void Anim_Skels::SetCurRot(glm::quat NewRot)
{
    this->CurRot = NewRot;
}

void Anim_Skels::SetChild(S_P<Anim_Skels> NewChld)
{
    this->Chlds.push_back(NewChld);
}

void Anim_Skels::SetChilds(Vec_SH<Anim_Skels> NewChlds)
{
    for (auto& chld : NewChlds)
        this->SetChild(chld);
}

void Anim_Skels::DeleteFrame(int FrameId)
{
    this->Skel_Frames.erase(this->Skel_Frames.begin() + FrameId);
}

void Anim_Skels::AddFrame(float NewTime)
{
    int Count = 0;
    for (auto& frm : this->Skel_Frames)
    {
        if (frm->GetTimeStamp() > NewTime)
            break;
        Count++;
    }
    std::shared_ptr<Joint> TempJoint = std::make_shared<Joint>();
    TempJoint->Offset = this->CurOffset;
    TempJoint->Rotation = this->CurRot;
    TempJoint->Scale = this->CurScale;
    if (this->Skel_Frames.size() == 0)
        this->Skel_Frames.push_back(std::make_shared<Frames>(NewTime, TempJoint));
    else
        this->Skel_Frames.insert(this->Skel_Frames.begin() + Count, std::make_shared<Frames>(NewTime, TempJoint));
}
