#include "Animation.h"

Animation::Animation(S_P<Anim_Skels> InitSkels, std::string InitName, float InitFloat, glm::mat4 InitInv)
{
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
	default:		
		break;
	}
	//update Skeletons with Time

}

std::vector<glm::mat4> Animation::GetAllMatrix()
{
    return std::vector<glm::mat4>();
}
