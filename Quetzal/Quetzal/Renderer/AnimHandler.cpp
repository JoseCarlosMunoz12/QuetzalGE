#include "AnimHandler.h"

AnimHandler::AnimHandler()
{
}

AnimHandler::~AnimHandler()
{
}

void AnimHandler::AddAnims(std::string Name, M_S_M Offsets, M_S_M TransMats, M_S_I BoneLocs)
{
	this->AllAnims.push_back(std::make_shared<AnimationData>(Name, Offsets, TransMats, BoneLocs));
}

void AnimHandler::AddAnims(std::string Name, M_S_M Offsets, M_S_M TransMats, M_S_I BoneLocs, Vec_SH<Animation> Anims)
{
	this->AllAnims.push_back(std::make_shared<AnimationData>(Name,Offsets, TransMats, BoneLocs, Anims));
}

void AnimHandler::Update(float dt)
{
	for (auto& jj : AllAnims)
		jj->Update(dt);
}
