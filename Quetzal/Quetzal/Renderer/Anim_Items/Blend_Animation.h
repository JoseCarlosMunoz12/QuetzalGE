#pragma once
#include "Animation.h"
using M_S_F = std::map<std::string, float>;
using M_S_A = std::map<std::string, S_P<Animation>>;
class Blend_Animation
{
private:
	//Blend data
	M_S_F BlendRatios;
	std::string BlendName;
	std::vector<std::string> AnimNames;
	//holds mats of Anims to update and blend
	std::vector<glm::mat4> MatsOfAnim0;
	std::vector<glm::mat4> MatsOfAnim1;
	glm::mat4 GetBlend(std::string BoneName, glm::mat4 AnimMat0, glm::mat4 Animmat1);
public:
	Blend_Animation(std::string InitName, std::vector<std::string> InitAnimNames);
	Blend_Animation(std::string InitName, M_S_M BonesName, std::vector<std::string> InitAnimNames);
	Blend_Animation(std::string InitName, M_S_F InitRatios, std::vector<std::string> InitAnimNames);
	void SetAnimsToUse(std::vector<std::string> InitAnimNames);
	M_S_F GetBlendRatios()                    { return this->BlendRatios; }
	std::vector<std::string> GetAnimsBlends() { return this->AnimNames; }
	void SetBlendRatio(std::string BoneName, float Ratios);
	void SetBlendRatios(float Ratio);
	void UpdateAnimations(std::vector<glm::mat4> Mats, M_S_A Anims,
		M_S_M Offsett, M_S_M TransMats,	M_S_I BoneId, float dt);
};
