#pragma once
#include "Animation.h"
using M_S_F = std::map<std::string, float>;
class Blend_Animation
{
private:
	M_S_F BlendRatios;
	std::string BlendName;
	std::vector<std::string> AnimNames;
public:
	Blend_Animation(std::string InitName, std::vector<std::string> InitAnimNames);
	Blend_Animation(std::string InitName, M_S_M BonesName, std::vector<std::string> InitAnimNames);
	Blend_Animation(std::string InitName, M_S_F InitRatios, std::vector<std::string> InitAnimNames);
	void SetAnimsToUse(std::vector<std::string> InitAnimNames);
	M_S_F GetBlendRatios() { return this->BlendRatios; }
	void SetBlendRatio(std::string BoneName, float Ratios);
	void SetBlendRatios(float Ratio);
};
