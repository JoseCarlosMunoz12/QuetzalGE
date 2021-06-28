#include "Animation.h"


Animation::Animation(std::string InitName, float InitFloat, M_S_F Inti_Frames)
{
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

glm::mat4 Animation::GetMat(std::string BoneName, float CurTime)
{
	if (this->Frame_Data.find("") != this->Frame_Data.end())
		return glm::mat4(1.f);
	Vec_SH<Frames> BoneFrames = this->Frame_Data[BoneName];
	return glm::mat4();
}

void Animation::AddFrame(float NewTime, std::string BoneName, S_P<Frames> NewFrame)
{
}
