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
	float TimeLength;
	float CurTime;
public:
	Animation(std::string InitName, float InitFloat, M_S_F Inti_Frames);
	Animation();
	~Animation();
	void updateTime(float dt);
	void GetAllMatrix(std::vector<glm::mat4>& AllMats,
		M_S_M BnOff, M_S_M TrnsMat, M_S_I MatLoc);
	//Getters
	float GetCurTime();
	float GetTimeLength();
	int GetLoopId();
	std::string GetName() { return this->Name; }
	//Setters
	void SetCurTime(float NewCur);
	void SetTimeLength(float NewLength);
	void SetLoopId(int NewId);
	void SetName(std::string NewName);
	void SetSkels();
	void SetInvMatrix(glm::mat4 NewInv);
};

