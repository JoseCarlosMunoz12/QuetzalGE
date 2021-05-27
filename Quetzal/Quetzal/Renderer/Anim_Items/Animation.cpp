#include "Animation.h"

void Animation::UpdateSkels(S_P<Anim_Skels> Bone)
{
	Bone->UpdateMatrix(this->CurTime);
	Vec_SH<Anim_Skels> chlds = Bone->GetChildren();
	for (auto& jj : chlds)
		this->UpdateSkels(jj);
}

void Animation::CalcMatrix(glm::mat4 Par, std::vector<glm::mat4>& Collection, S_P<Anim_Skels> Bone,
	std::map<std::string, glm::mat4> Bn, std::map<std::string, int> MatLoc)
{
	glm::mat4 ParMatrix = Par * Bone->GetMatrix();
	std::string nme = Bone->GetName();
	glm::mat4 TempMatrix =  ParMatrix * Bn[nme];
	Collection[MatLoc[nme]] = TempMatrix;
	Vec_SH<Anim_Skels> Chlds = Bone->GetChildren();
	for (auto& jj : Chlds)
		this->CalcMatrix(ParMatrix, Collection, jj,Bn,MatLoc);
}

void Animation::CalcMatrix(glm::mat4 Par,
	std::vector<glm::mat4>& Collection,
	S_P<Anim_Skels> Bone, std::map<std::string, glm::mat4> BnsOff, std::map<std::string, glm::mat4> TransMat, std::map<std::string, int> MatLoc)
{

}

Animation::Animation(S_P<Anim_Skels> InitSkels, std::string InitName, float InitFloat, glm::mat4 InitInv)
	:Name(InitName),TimeLength(InitFloat), Inv(InitInv)
{
	this->Skels = InitSkels;
	this->CurTime = 0.f;
	this->LoopId = 1;
}

Animation::Animation()
	:Name(""), TimeLength(0),Inv(glm::mat4(1.f))
{
	this->CurTime = 0;
	this->LoopId = 1;
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
		if (this->CurTime > this->TimeLength)
			this->CurTime = this->TimeLength;
		break;
	case 1:
		this->CurTime += dt;
		if (this->CurTime > this->TimeLength)
			this->CurTime = 0;
	}
	//update Skeletons with Time
	this->UpdateSkels(this->Skels);
}

void Animation::GetAllMatrix(std::vector<glm::mat4> AllMats,
	std::map<std::string, glm::mat4> BnOff, std::map<std::string, glm::mat4> TrnsMat,
	std::map<std::string, int> MatLoc)
{
	glm::mat4 wrld = glm::mat4(1.f);
	this->CalcMatrix(wrld, AllMats, this->Skels, BnOff, MatLoc);
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

void Animation::SetName(std::string NewName)
{
	this->Name = NewName;
}

void Animation::SetSkels(S_P<Anim_Skels> InitSkels)
{
	this->Skels = InitSkels;
}

void Animation::SetInvMatrix(glm::mat4 NewInv)
{
	this->Inv = glm::inverse(NewInv);
}
