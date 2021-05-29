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

AnimationData::AnimationData()
	:AnimID(-1)
{
}

AnimationData::AnimationData(M_S_M InitOffsets, M_S_M TransMats, M_S_I InitBoneId)
	:AnimID(-1)
{
	this->InitOffsets(InitOffsets);
	this->InitTransMat(TransMats);
	this->InitBoneId(InitBoneId);
}

AnimationData::AnimationData(M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId, Vec_SH<Animation> InitAnims)
	:AnimID(-1)
{
	this->InitOffsets(InitOffsets);
	this->InitTransMat(TransMats);
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

std::vector<glm::mat4> AnimationData::GetMatrices()
{
	this->Anims[this->AnimID]->GetAllMatrix(this->AnimMats, this->TransMats,this->Offsets, this->BoneId);	
	return this->AnimMats;
}
