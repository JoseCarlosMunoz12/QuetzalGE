#pragma once
#include "Animation.h"
#include "Blend_Animation.h"
using M_S_A = std::map<std::string, S_P<Animation>>;
using M_S_B = std::map<std::string, S_P<Blend_Animation>>;
class AnimationData
{
private:
	//Name
	std::string Name;
	//base data of the whole model for animation
	M_S_M Offsets;
	M_S_M TransMats;
	M_S_I BoneId;
	std::vector<glm::mat4> AnimMats;
	M_S_B Blends;
	//Animation data and how it blends with each other
	M_S_A Anims;
	std::string CurAnim;
	float dt;//adds how much time has passed, to be used in the Blend system
	void InitOffsets(M_S_M InitOffsets);
	void InitTransMat(M_S_M InitTransMat);
	void InitBoneId(M_S_I InitBoneId);
public:
	AnimationData(std::string InitName);
	AnimationData(std::string InitName, M_S_M InitOffsets, M_S_M TransMats, M_S_I InitBoneId);
	AnimationData(std::string InitName, M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId,
		Vec_SH<Animation> InitAnims);
	~AnimationData();
	void InitAnimData(M_S_M InitOffsets, M_S_M InitTransmats, M_S_I InitBoneId);
	void AddAnimation(S_P<Animation> NewAnim);
	void AddAnimations(Vec_SH<Animation> NewAnims);
	void ChangeAnim(std::string NewAnimChoosen);
	void Update(float dt);
	void SetName(std::string NewName);
	std::vector<glm::mat4> GetMatrices();
	std::vector<std::string> GetAllAnims();
	std::vector<std::string> GetAllBlends();
	S_P<Animation> GetCurrentAnim() { return this->Anims[this->CurAnim]; }
	std::string GetName()           { return this->Name; }
	std::string GetAnimId()                 { return this->CurAnim; }
	M_S_B GetBlends() { return this->Blends; }
};
