#include "AnimHandler.h"

void AnimHandler::InitOffsets(M_S_M InitOffsets)
{
	this->Offsets = InitOffsets;
	this->AnimMats = std::vector<glm::mat4>(this->Offsets.size());
}

void AnimHandler::InitTransMat(M_S_M InitTransMat)
{
	this->TransMats = InitTransMat;
}

void AnimHandler::InitBoneId(M_S_I InitBoneId)
{
	this->BoneId = InitBoneId;
}

AnimHandler::AnimHandler()
	:AnimID(-1)
{
}

AnimHandler::AnimHandler(M_S_M InitOffsets, M_S_M TransMats, M_S_I InitBoneId)
	:AnimID(-1)
{
	this->InitOffsets(InitOffsets);
	this->InitTransMat(TransMats);
	this->InitBoneId(InitBoneId);
}

AnimHandler::AnimHandler(M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId, Vec_SH<Animation> InitAnims)
	:AnimID(-1)
{
	this->InitOffsets(InitOffsets);
	this->InitTransMat(TransMats);
	this->InitBoneId(InitBoneId);
	this->Anims = InitAnims;
}

AnimHandler::~AnimHandler()
{
}

void AnimHandler::InitAnimData(M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId)
{
	this->InitOffsets(InitOffsets);
	this->InitTransMat(InitTransmats);
	this->InitBoneId(InitBoneId);
}

void AnimHandler::AddAnimation(S_P<Animation> NewAnim)
{
	this->Anims.push_back(NewAnim);
}

void AnimHandler::AddAnimations(Vec_SH<Animation> NewAnims)
{
	for (auto& jj : NewAnims)
		this->AddAnimation(jj);
}

void AnimHandler::ChangeAnim(int AnimId)
{
	this->AnimID = AnimId;
}

void AnimHandler::Update(float dt)
{
	this->Anims[this->AnimID]->updateTime(dt);
}

std::vector<glm::mat4> AnimHandler::GetMatrices()
{
	this->Anims[this->AnimID]->GetAllMatrix(this->AnimMats, this->TransMats,this->Offsets, this->BoneId);	
	return this->AnimMats;
}
