#include "Animation.h"

void Animation::UpdateSkels(S_P<Anim_Skels> Bone)
{
	Bone->UpdateMatrix(this->CurTime);
	Vec_SH<Anim_Skels> chlds = Bone->GetChildren();
	for (auto& jj : chlds)
		this->UpdateSkels(jj);
}

void Animation::CalcMatrix(glm::mat4 Par, std::vector<glm::mat4>& Collection, S_P<Anim_Skels> Bone)
{
	glm::mat4 ParMatrix = Par * Bone->GetMatrix();
	glm::mat4 TempMatrix = ParMatrix * Bone->GetOffset();
	Collection.push_back(TempMatrix);
	Vec_SH<Anim_Skels> Chlds = Bone->GetChildren();
	for (auto& jj : Chlds)
		this->CalcMatrix(ParMatrix, Collection, jj);
}

Animation::Animation(S_P<Anim_Skels> InitSkels, std::string InitName, float InitFloat, glm::mat4 InitInv)
	:Name(InitName),TimeLength(InitFloat), Inv(InitInv)
{
	this->Skels = InitSkels;
	this->CurTime = 0.f;
	this->LoopId = 0;
}

Animation::~Animation()
{
}

void Animation::updateTime(float dt)
{
	//updates the Time
	switch (LoopId)
	{
	case 0:
		this->CurTime += dt;
		if (this->CurTime > 0)
			this->CurTime = this->TimeLength;
		break;
	case 1:
		this->CurTime += dt;
		if (this->CurTime > 0)
			this->CurTime = 0;
	}
	//update Skeletons with Time
	this->UpdateSkels(this->Skels);
}

std::vector<glm::mat4> Animation::GetAllMatrix()
{
	std::vector<glm::mat4> Collection;
	this->CalcMatrix(this->Inv, Collection, this->Skels);
    return Collection;
}

float Animation::GetCurTime()
{
	return CurTime;
}

float Animation::GetTimeLength()
{
	return this->TimeLength;
}

int Animation::GetLoopId()
{
	return this->LoopId;
}

void Animation::SetCurTime(float NewCur)
{
	this->CurTime = NewCur;
}

void Animation::SetTimeLength(float NewLength)
{
	this->TimeLength = NewLength;
}

void Animation::SetLoopId(int NewId)
{
	this->LoopId = NewId;
}
