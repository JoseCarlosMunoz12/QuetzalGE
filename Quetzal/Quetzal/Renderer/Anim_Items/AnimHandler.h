#pragma once
#include "Animation.h"
using M_S_M = std::map<std::string, glm::mat4>;
using M_S_I = std::map<std::string, int>;
class AnimHandler
{
private:
	//base data of the whole model for animation
	M_S_M Offsets;
	M_S_M TransMats;
	M_S_I BoneId;
	std::vector<glm::mat4> AnimMats;
	//Animation data and how it blends with each other
	Vec_SH<Animation> Anims;
	int AnimID;
public:
	AnimHandler();
	AnimHandler(M_S_M InitOffsets, M_S_M TransMats,	M_S_I InitBoneId);
	AnimHandler(M_S_M InitOffsets, M_S_M InitTransmats,	M_S_I InitBoneId,
		Vec_SH<Animation> InitAnims);
	~AnimHandler();
	void InitOffsets(M_S_M InitOffsets);
	void InitTransMat(M_S_M InitTransMat);
	void InitBoneId(M_S_I InitBoneId);
	void AddAnimation(S_P<Animation> NewAnim);
	void AddAnimations(Vec_SH<Animation> NewAnims);
	void ChangeAnim(int AnimId);
	void Update(float dt);
	std::vector<glm::mat4> GetMatrices();
};
