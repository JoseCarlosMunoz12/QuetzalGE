#include "AnimationData.h"

void AnimationData::InitOffsets(M_S_M InitOffsets)
{
	this->Offsets = InitOffsets;
	this->AnimMats = std::vector<glm::mat4>(this->Offsets.size());
}

void AnimationData::InitTransMat(M_S_M InitTransMat)
{
	this->TransMats = InitTransMat;
}

void AnimationData::InitBoneId(M_S_I InitBoneId)
{
	this->BoneId = InitBoneId;
}

AnimationData::AnimationData(std::string InitName)
	:AnimID(-1)
{
	this->SetName(InitName);
}

AnimationData::AnimationData(std::string InitName, M_S_M InitOffsets, M_S_M TransMats, M_S_I InitBoneId)
	:AnimID(-1)
{
	this->SetName(InitName);
	this->InitOffsets(InitOffsets);
	this->InitTransMat(TransMats);
	this->InitBoneId(InitBoneId);
}

AnimationData::AnimationData(std::string InitName, M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId, Vec_SH<Animation> InitAnims)
	:AnimID(0)
{
	this->SetName(InitName);
	this->InitOffsets(InitOffsets);
	this->InitTransMat(InitTransmats);
	this->InitBoneId(InitBoneId);
	this->Anims = InitAnims;
}

AnimationData::~AnimationData()
{
}

void AnimationData::InitAnimData(M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId)
{
	this->InitOffsets(InitOffsets);
	this->InitTransMat(InitTransmats);
	this->InitBoneId(InitBoneId);
}

void AnimationData::AddAnimation(S_P<Animation> NewAnim)
{
	this->Anims.push_back(NewAnim);
}

void AnimationData::AddAnimations(Vec_SH<Animation> NewAnims)
{
	for (auto& jj : NewAnims)
		this->AddAnimation(jj);
}

void AnimationData::ChangeAnim(int AnimId)
{
	this->AnimID = AnimId;
}

void AnimationData::Update(float dt)
{
	this->Anims[this->AnimID]->updateTime(dt);
}

void AnimationData::SetName(std::string NewName)
{
	this->Name = NewName;
}

std::vector<glm::mat4> AnimationData::GetMatrices()
{
	this->Anims[this->AnimID]->GetAllMatrix(this->AnimMats,this->Offsets, this->TransMats, this->BoneId);	
	return this->AnimMats;
}

std::vector<std::string> AnimationData::GetAllAnims()
{
	std::vector<std::string> AllNames;
	for (auto& jj : Anims)
		AllNames.push_back(jj->GetName());
	return AllNames;
}
