#pragma once

#include "Anim_Skels.h"

enum LoopID
{
	MANUAL = -1,
	LOOP,
	ONCE
};

using M_S_F = std::map<std::string, Vec_SH<Frames>>;

class Animation
{
private:
	std::string Name;
	M_S_F Frame_Data;
	float TimeLength;
	float CurTime;
public:
	Animation(std::string InitName, float InitFloat, M_S_F Inti_Frames);
	~Animation();
	//Getters
	float GetCurTime();
	float GetTimeLength();
	std::string GetName() { return this->Name; }
	//Setters
	void SetCurTime(float NewCur);
	void SetTimeLength(float NewLength);
	//Animation Matrices
	void Update(float dt);
	glm::mat4 GetMat(std::string BoneName, float CurTime);
	void AddFrame(float NewTime, std::string BoneName, S_P<Frames> NewFrame);
};

