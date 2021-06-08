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
{
	this->SetName(InitName);
}

AnimationData::AnimationData(std::string InitName, M_S_M InitOffsets, M_S_M TransMats, M_S_I InitBoneId)
{
	this->SetName(InitName);
	this->InitOffsets(InitOffsets);
	this->InitTransMat(TransMats);
	this->InitBoneId(InitBoneId);
}

AnimationData::AnimationData(std::string InitName, M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId, Vec_SH<Animation> InitAnims)
{
	this->SetName(InitName);
	this->InitOffsets(InitOffsets);
	this->InitTransMat(InitTransmats);
	this->InitBoneId(InitBoneId);
	for (auto& jj : InitAnims)
		this->Anims[jj->GetName()] = jj;
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
	if (this->Anims.find(this->CurAnim) != this->Anims.end())
		this->Anims[this->CurAnim]->GetAllMatrix(this->AnimMats, this->Offsets, this->TransMats, this->BoneId);
	else if (this->Blends.find(this->CurAnim) != this->Blends.end())
		this->Blends[this->CurAnim]->UpdateAnimations(this->AnimMats,this->Anims,
			this->Offsets, this->TransMats, this->BoneId, this->dt);	
	return this->AnimMats;
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
