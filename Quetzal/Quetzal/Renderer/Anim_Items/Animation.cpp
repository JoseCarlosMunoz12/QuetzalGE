#include "Animation.h"

Animation::Animation(S_P<Anim_Skels> InitSkels, std::string InitName, float InitFloat, glm::mat4 InitInv)
{
}

Animation::~Animation()
{
}

void Animation::updateTime(float dt)
{
    this->CurTime += dt;
}

std::vector<glm::mat4> Animation::GetAllMatrix()
{
    return std::vector<glm::mat4>();
}
