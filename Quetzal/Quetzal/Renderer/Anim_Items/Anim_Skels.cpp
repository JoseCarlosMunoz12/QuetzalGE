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

Anim_Skels::Anim_Skels()
{
}
