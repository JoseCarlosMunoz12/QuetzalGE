#include "Animation.h"


glm::mat4 Animation::GetMat(Vec_SH<Frames> Frms)
{
	Vec_SH<Frames> Frames = this->GetFrames(Frms);
    float Ratio = this->GetTimeRatio(Frames);
    InterType Type = Frms[0]->GetType();  switch (Type)
    {
    case InterType::HOLD:
        this->CurRot = Frms[0]->GetRot();
        this->CurOffset = Frms[0]->GetOffset();
        this->CurScale = Frms[0]->GetScale();
        break;
    case InterType::LINEAR:
        this->CurRot = glm::slerp(Frms[0]->GetRot(), Frms[1]->GetRot(), Ratio);
        this->CurOffset = this->LinInter(Frms[0]->GetOffset(), Frms[1]->GetOffset(), Ratio);
        this->CurScale = this->LinInter(Frms[0]->GetScale(), Frms[1]->GetScale(), Ratio);
        break;
    case InterType::QUADBENZ:
        break;
    case InterType::CUBEBENZ:
        break;

    }
    return UpdatMatrix();
}

Vec_SH<Frames> Animation::GetFrames(Vec_SH<Frames> Frms)
{
    int Count = 0;
    for (auto& Frm : Frms)
    {
        if (Frm->GetTimeStamp() > this->CurTime)
            break;
        Count++;
    }
    if (Count == 0)
        return { Frms[Count], Frms[Count + 1] };
    if (Count == Frms.size())
        return { Frms[Count - 1], Frms[Count - 1] };
    return { Frms[Count - 1], Frms[Count] };
}

glm::vec3 Animation::LinInter(glm::vec3 Vec0, glm::vec3 Vec1, float Ratio)
{
    return (1.f - Ratio) * Vec0 + Ratio * Vec1;
}

glm::mat4 Animation::UpdatMatrix()
{ //Calculate the matrix
    glm::mat4 Matrix = glm::mat4(1.f);
    Matrix = glm::translate(Matrix, this->CurOffset);
    Matrix = Matrix * glm::mat4_cast(this->CurRot);
    Matrix = glm::scale(Matrix, this->CurScale);
    return Matrix;
}

float Animation::GetTimeRatio(Vec_SH<Frames> Frms)
{
    float TimeLeft = this->CurTime- Frms[0]->GetTimeStamp();
    float FrameDiff = Frms[1]->GetTimeStamp() - Frms[0]->GetTimeStamp();
    if (FrameDiff == 0)
        return 0.f;
    return TimeLeft / FrameDiff;;
}

Animation::Animation(std::string InitName, float InitFloat, M_S_Fr Init_Frames)
    :Name(InitName),TimeLength(InitFloat),CurTime(0.f),
    CurOffset(glm::vec3(0.f)), CurScale(glm::vec3(1.f))
{
    Quat r;
    this->CurRot = r.GetQuat();
    this->Frame_Data = Init_Frames;
}

Animation::~Animation()
{
}

float Animation::GetCurTime()
{
	return CurTime;
}

float Animation::GetTimeLength()
{
	return this->TimeLength;
}


void Animation::SetCurTime(float NewCur)
{
	this->CurTime = NewCur;
}

void Animation::SetTimeLength(float NewLength)
{
	this->TimeLength = NewLength;
}

void Animation::Update(float dt)
{
	this->CurTime += dt;
}

glm::mat4 Animation::GetMat(std::string BoneName)
{
	if (this->Frame_Data.find(BoneName) == this->Frame_Data.end())
		return glm::mat4(1.f);
	return this->GetMat(this->Frame_Data[BoneName]);
}

void Animation::AddFrame(float NewTime, std::string BoneName, S_P<Frames> NewFrame)
{

}
