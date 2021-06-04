#include "Blend_Animation.h"

Blend_Animation::Blend_Animation(std::string InitName, std::vector<std::string> InitAnimNames)
	:BlendName(InitName)
{
	this->SetAnimsToUse(InitAnimNames);
}

Blend_Animation::Blend_Animation(std::string InitName, M_S_M BonesName, std::vector<std::string> InitAnimNames)
	:BlendName(InitName)
{
	this->SetAnimsToUse(InitAnimNames);
	//Creates Base ratios to be edited
	for (auto& jj : BonesName)
		BlendRatios[jj.first] = 1.f;
}

Blend_Animation::Blend_Animation(std::string InitName, M_S_F InitRatios, std::vector<std::string> InitAnimNames)
	:BlendName(InitName), BlendRatios(InitRatios)
{
	this->SetAnimsToUse(InitAnimNames);
}

void Blend_Animation::SetAnimsToUse(std::vector<std::string> InitAnimNames)
{
	this->AnimNames = InitAnimNames;
}
