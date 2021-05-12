#include "Animation.h"

void Animation::UpdateSkels(S_P<Anim_Skels> Bone)
{
	Bone->UpdateMatrix(this->CurTime);
	Vec_SH<Anim_Skels> chlds = Bone->GetChildren();
	for (auto& jj : chlds)
		this->UpdateSkels(jj);
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

}

std::vector<glm::mat4> Animation::GetAllMatrix()
{
    return std::vector<glm::mat4>();
}
