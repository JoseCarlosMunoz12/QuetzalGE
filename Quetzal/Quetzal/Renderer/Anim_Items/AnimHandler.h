#pragma once
#include "Animation.h"
class AnimHandler
{
private:
	//base data of the whole model for animation
	std::map<std::string, glm::mat4> Offsets;
	std::map<std::string, glm::mat4> TransMats;
	std::map<std::string, int> BoneId;
	std::vector<glm::mat4> AnimMats;
	//Animation data and how it blends with each other
	Vec_SH<Animation> Anims;
public:
	AnimHandler();
	AnimHandler(std::map<std::string,glm::mat4> InitOffsets, std::map<std::string,glm::mat4>TransMats,
		std::map<std::string,int> InitBoneId);
	~AnimHandler();
	void InitOffsets(std::map<std::string, glm::mat4> InitOffsets);
	void InitTransMat(std::map<std::string, glm::mat4> InitTransMat);
	void InitBoneId(std::map<std::string, int> InitBoneId);
	void AddAnimation();
	void ChangeAnim(int AnimId);
	std::vector<glm::mat4> GetMatrices();
};

