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
