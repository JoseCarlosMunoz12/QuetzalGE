#pragma once

#include "Anim_Skels.h"

class Animation
{
private:
	S_P<Anim_Skels> Skels;
	std::string Name;
	float TimeLength;
	float CurTime;
	glm::mat4 Inv;
public:
	Animation(S_P<Anim_Skels> InitSkels, std::string InitName, float InitFloat, glm::mat4 InitInv);
	~Animation();
	void updateTime(float dt);
	std::vector<glm::mat4> GetAllMatrix();
};

