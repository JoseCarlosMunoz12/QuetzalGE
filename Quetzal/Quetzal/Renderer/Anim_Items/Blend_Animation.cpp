#include "Blend_Animation.h"

Blend_Animation::Blend_Animation(std::string InitName, std::vector<std::string> InitAnimNames)
	:BlendName(InitName)
{
	this->SetAnimsToUse(InitAnimNames);
	this->SetAnimStart0(0.f);
	this->SetAnimStart1(0.f);
}

Blend_Animation::Blend_Animation(std::string InitName, M_S_M BonesName, std::vector<std::string> InitAnimNames,
	float AnimStart0, float AnimStart1)
	:BlendName(InitName)
{
	this->SetAnimsToUse(InitAnimNames);
	//Creates Base ratios to be edited
	for (auto& jj : BonesName)
		BlendRatios[jj.first] = 1.f;
	//Init Size of the Mats to Adjust
	this->MatsOfAnim0 = std::vector<glm::mat4>(BlendRatios.size());
	this->MatsOfAnim1 = std::vector<glm::mat4>(BlendRatios.size());
	this->SetAnimStart0(AnimStart0);
	this->SetAnimStart1(AnimStart1);
}

Blend_Animation::Blend_Animation(std::string InitName, M_S_F InitRatios, std::vector<std::string> InitAnimNames,
	float AnimStart0, float AnimStart1)
	:BlendName(InitName), BlendRatios(InitRatios)
{
	//Init Size of the Mats to Adjust
	this->MatsOfAnim0 = std::vector<glm::mat4>(BlendRatios.size());
	this->MatsOfAnim1 = std::vector<glm::mat4>(BlendRatios.size());
	this->SetAnimsToUse(InitAnimNames);
	this->SetAnimStart0(AnimStart0);
	this->SetAnimStart1(AnimStart1);
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

void Blend_Animation::SetAnimStart0(float Start)
{
	this->Anim_Start0 = Start;
}

void Blend_Animation::SetAnimStart1(float Start)
{
	this->Anim_Start1 = Start;
}

void Blend_Animation::UpdateAnimations(std::vector<glm::mat4>& Mats, M_S_A Anims,
	M_S_M Offsett, M_S_M TransMats, M_S_I BoneId, float dt)
{
	//Update time for animations
	for (auto& jj : this->AnimNames)
		Anims[jj]->updateTime(dt);
	//Get the Updated Matrices
	Anims[this->AnimNames[0]]->GetAllMatrix(this->MatsOfAnim0, Offsett, TransMats, BoneId);
	Anims[this->AnimNames[0]]->GetAllMatrix(this->MatsOfAnim1, Offsett, TransMats, BoneId);
	//Blend Matrices with corresponding Ratios
	for (auto& jj : BoneId)
		Mats[jj.second] = GetBlend(jj.first, this->MatsOfAnim0[jj.second], this->MatsOfAnim1[jj.second]);
}

glm::mat4 Blend_Animation::GetBlend(std::string BoneName, glm::mat4 AnimMat0, glm::mat4 Animmat1)
{
	float ratio = this->BlendRatios[BoneName];
	glm::mat4 Mix = ratio * AnimMat0 + (1.f - ratio) * Animmat1;
	return Mix;
}
