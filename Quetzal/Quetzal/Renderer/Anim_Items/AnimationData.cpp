#include "AnimationData.h"

void AnimationData::UpdateMatrices(S_P<Skels> CurNode, glm::mat4 ParMat)
{
	//Get basic Dat
	std::string BoneId = CurNode->GetId();
	glm::mat4 BoneOffset = this->Skels_Data[BoneId].BoneOffset;
	glm::mat4 BoneTrans = this->Skels_Data[BoneId].TransMats;
	int BoneLoc = this->Skels_Data[BoneId].Id;
	glm::mat4 CurMat = ParMat;
	//Calc Data
	if (this->Anims.find(this->CurAnim) != this->Anims.end())
		 CurMat = ParMat * this->Anims[this->CurAnim]->GetMat(BoneId);
	else if (this->Blends.find(this->CurAnim) != this->Blends.end())
		this->Blends[this->CurAnim];
	else
		CurMat = ParMat * BoneTrans;
	this->Anim_Mats[BoneLoc] = CurMat * BoneOffset;
	//Check Children
	Vec_SH<Skels> Chlds = CurNode->GetChilds();
	for (auto& jj : Chlds)
		this->UpdateMatrices(jj, CurMat);
}

AnimationData::AnimationData(std::string InitName)
{
	this->SetName(InitName);
}

AnimationData::AnimationData(std::string InitName, M_S_BI InitSkelsData)
	:Name(InitName),Skels_Data(InitSkelsData)
{
}


AnimationData::AnimationData(std::string InitName, M_S_BI InitSKelsData, M_S_A InitAnims)
	:Name(InitName), Skels_Data(InitSKelsData)
{
	this->Anims = InitAnims;
}

AnimationData::AnimationData(std::string InitName, M_S_BI InitSkelsData, M_S_A InitAnims, std::string InitAnim)\
	:Name(InitName), Skels_Data(InitSkelsData)
{
	this->Anims = InitAnims;
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
	this->dt = dt;
}

void AnimationData::SetName(std::string NewName)
{
	this->Name = NewName;
}

std::vector<glm::mat4> AnimationData::GetMatrices(glm::mat4 WrldMat)
{
	this->UpdateMatrices(this->Anim_Skels, WrldMat);
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
