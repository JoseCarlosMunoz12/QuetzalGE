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
	//Init Size of the Mats to Adjust
	this->MatsOfAnim0 = std::vector<glm::mat4>(BlendRatios.size());
	this->MatsOfAnim1 = std::vector<glm::mat4>(BlendRatios.size());
}

Blend_Animation::Blend_Animation(std::string InitName, M_S_F InitRatios, std::vector<std::string> InitAnimNames)
	:BlendName(InitName), BlendRatios(InitRatios)
{
	//Init Size of the Mats to Adjust
	this->MatsOfAnim0 = std::vector<glm::mat4>(BlendRatios.size());
	this->MatsOfAnim1 = std::vector<glm::mat4>(BlendRatios.size());
	this->SetAnimsToUse(InitAnimNames);
}

void Blend_Animation::SetAnimsToUse(std::vector<std::string> InitAnimNames)
{
	this->AnimNames = InitAnimNames;
}

void Blend_Animation::SetBlendRatio(std::string BoneName, float Ratios)
{
	this->BlendRatios[BoneName] = Ratios;
}

void Blend_Animation::SetBlendRatios(float Ratio)
{
	for (auto& jj : this->BlendRatios)
		jj.second = Ratio;
}

void Blend_Animation::UpdateAnimations(std::vector<glm::mat4> Mats, M_S_A Anims, float dt)
{
	
}

glm::mat4 Blend_Animation::GetBlend(std::string BoneName, glm::mat4 AnimMat0, glm::mat4 Animmat1)
{
	float ratio = this->BlendRatios[BoneName];
	glm::mat4 Mix = ratio * AnimMat0 + (1.f - ratio) * Animmat1;
	return Mix;
}
