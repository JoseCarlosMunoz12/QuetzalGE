#include "AnimationData.h"

AnimationData::AnimationData(std::string InitName)
{
	this->SetName(InitName);
}

AnimationData::AnimationData(std::string InitName, M_S_BI InitSkelsData)
{
}


AnimationData::AnimationData(std::string InitName, M_S_BI InitSKelsData, Vec_SH<Animation> InitAnims)
{
}

AnimationData::AnimationData(std::string InitName, M_S_BI InitSkelsData, Vec_SH<Animation> InitAnims, std::string InitAnim)
{
}

AnimationData::~AnimationData()
{
}

void AnimationData::AddAnimation(S_P<Animation> NewAnim)
{
	this->Anims[NewAnim->GetName()] = NewAnim;
}

void AnimationData::AddAnimations(Vec_SH<Animation> NewAnims)
{
	for (auto& jj : NewAnims)
		this->AddAnimation(jj);
}

void AnimationData::ChangeAnim(std::string NewAnimChoosen)
{
	this->CurAnim = NewAnimChoosen;
}

void AnimationData::Update(float dt)
{
	if (this->Anims.find(this->CurAnim) != this->Anims.end())
		this->Anims[this->CurAnim]->updateTime(dt);
	this->dt = dt;
}

void AnimationData::SetName(std::string NewName)
{
	this->Name = NewName;
}

std::vector<glm::mat4> AnimationData::GetMatrices()
{
	return this->Anim_Mats;
}

std::vector<std::string> AnimationData::GetAllAnims()
{
	std::vector<std::string> AllNames;
	for (auto& jj : this->Anims)
		AllNames.push_back(jj.first);
	return AllNames;
}

std::vector<std::string> AnimationData::GetAllBlends()
{
	std::vector<std::string> AllNames;
	for (auto& jj : this->Blends)
		AllNames.push_back(jj.first);
	return AllNames;
}
