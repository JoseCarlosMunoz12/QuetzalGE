#include "AnimHandler.h"

AnimHandler::AnimHandler()
{
}

AnimHandler::~AnimHandler()
{
}

void AnimHandler::AddAnims(std::string Name, M_S_M Offsets, M_S_M TransMats, M_S_I BoneLocs)
{
}

void AnimHandler::AddAnims(std::string Name, M_S_M Offsets, M_S_M TransMats, M_S_I BoneLocs, Vec_SH<Animation> Anims)
{
	
}

void AnimHandler::AddAnims(S_P<AnimationData> NewAnim)
{
	this->AllAnims.push_back(NewAnim);
}

void AnimHandler::Update(float dt)
{
	for (auto& jj : AllAnims)
		jj->Update(dt);
}
