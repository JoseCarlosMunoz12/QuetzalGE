#include "AnimHandler.h"

AnimHandler::AnimHandler()
{
}

AnimHandler::~AnimHandler()
{
}

void AnimHandler::AddAnims(M_S_M Offsets, M_S_M TransMats, M_S_I BoneLocs)
{
	this->AllAnims.push_back(std::make_shared<AnimationData>(Offsets, TransMats, BoneLocs));
}

void AnimHandler::Update(float dt)
{
	for (auto& jj : AllAnims)
		jj->Update(dt);
}
