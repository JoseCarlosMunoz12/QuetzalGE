#include "AnimHandler.h"

AnimHandler::AnimHandler()
{
}

AnimHandler::AnimHandler(std::map<std::string, glm::mat4> InitOffsets, std::map<std::string, glm::mat4> TransMats, std::map<std::string, int> InitBoneId)
{
}

AnimHandler::AnimHandler(std::map<std::string, glm::mat4> InitOffsets, std::map<std::string, glm::mat4> InitTransmats, std::map<std::string, int> InitBoneId, Vec_SH<Animation> InitAnims)
{
}

AnimHandler::~AnimHandler()
{
}

void AnimHandler::InitOffsets(std::map<std::string, glm::mat4> InitOffsets)
{
}

void AnimHandler::InitTransMat(std::map<std::string, glm::mat4> InitTransMat)
{
}

void AnimHandler::InitBoneId(std::map<std::string, int> InitBoneId)
{
}

void AnimHandler::AddAnimation(S_P<Animation> NewAnim)
{
}

void AnimHandler::AddAnimations(Vec_SH<Animation> NewAnims)
{
}

void AnimHandler::ChangeAnim(int AnimId)
{
}

std::vector<glm::mat4> AnimHandler::GetMatrices()
{
	return std::vector<glm::mat4>();
}
