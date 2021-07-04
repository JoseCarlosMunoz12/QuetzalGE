#pragma once
#include "Animation.h"
#include "Blend_Animation.h"
using M_S_A = std::map<std::string, S_P<Animation>>;
using M_S_B = std::map<std::string, S_P<Blend_Animation>>;
using M_S_BI = std::map<std::string, Bone_Information>;

class AnimationData
{
private:
	//Name
	std::string Name;
	//base data of the whole model for animation
	S_P<Skels> Anim_Skels;
	M_S_BI Skels_Data;
	std::vector<glm::mat4> Anim_Mats;
	//Animation data and how it blends with each other
	M_S_A Anims;
	M_S_B Blends;
	std::string CurAnim;
	float dt;//adds how much time has passed, to be used in the Blend system
	void UpdateMatrices(S_P<Skels> CurNode, glm::mat4 ParMat);
	void BuildMatrices();
public:
	AnimationData(std::string InitName, S_P<Skels> InitSkeleton, M_S_BI InitSkelsData);
	AnimationData(std::string InitName, S_P<Skels> InitSkeleton, M_S_BI InitSKelsData,
		M_S_A InitAnims);
	AnimationData(std::string InitName, S_P<Skels> InitSkeleton,M_S_BI InitSkelsData,
		M_S_A InitAnims, std::string InitAnim);
	~AnimationData();
	void AddAnimation(S_P<Animation> NewAnim);
	void AddAnimations(Vec_SH<Animation> NewAnims);
	void ChangeAnim(std::string NewAnimChoosen);
	void Update(float dt);
	void SetName(std::string NewName);
	std::vector<glm::mat4> GetMatrices(glm::mat4 WrldMat);
	std::vector<std::string> GetAllAnims();
	std::vector<std::string> GetAllBlends();
	S_P<Animation> GetCurrentAnim();
	std::string GetName()           { return this->Name; }
	std::string GetAnimId()         { return this->CurAnim; }
	M_S_B GetBlends()               { return this->Blends; }
};
