#pragma once
#include "Animation.h"
#include "Blend_Animation.h"
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
	//Animation data and how it blends with each other
	Vec_SH<Animation> Anims;
	int AnimID;
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
	void ChangeAnim(int AnimId);
	void Update(float dt);
	void SetName(std::string NewName);
	void SetAnimId(int NewID);
	std::vector<glm::mat4> GetMatrices();
	std::vector<std::string> GetAllAnims();
	S_P<Animation> GetCurrentAnim() { return this->Anims[AnimID]; }
	std::string GetName()           { return this->Name; }
	int GetAnimId()                 { return this->AnimID; }
};
