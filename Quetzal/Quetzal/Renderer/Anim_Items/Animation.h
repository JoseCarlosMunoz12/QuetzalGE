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
	// 0 loop to beginning
	// 1 from start to end once
	int LoopId;
	void UpdateSkels(S_P<Anim_Skels> Bone);
	void CalcMatrix(glm::mat4 Par, std::vector<glm::mat4>& Collection, S_P<Anim_Skels> Bone,
		std::map<std::string, glm::mat4> BnsOff, std::map<std::string, glm::mat4> TransMat, std::map<std::string, int> MatLoc);
public:
	Animation(S_P<Anim_Skels> InitSkels, std::string InitName, float InitFloat, glm::mat4 InitInv);
	Animation();
	~Animation();
	void updateTime(float dt);
	void GetAllMatrix(std::vector<glm::mat4>& AllMats,
		std::map<std::string, glm::mat4> BnOff, std::map < std::string,glm::mat4> TrnsMat, std::map<std::string, int> MatLoc);
	//Getters
	float GetCurTime();
	float GetTimeLength();
	int GetLoopId();
	std::string GetName() { return this->Name; }
	S_P<Anim_Skels> GetAnimSkels() { return this->Skels; }
	glm::mat4 GetInvMatrix() { return this->Inv; }
	//Setters
	void SetCurTime(float NewCur);
	void SetTimeLength(float NewLength);
	void SetLoopId(int NewId);
	void SetName(std::string NewName);
	void SetSkels(S_P<Anim_Skels> InitSkels);
	void SetInvMatrix(glm::mat4 NewInv);
};

