#pragma once

#include "Anim_Skels.h"

enum LoopID
{
	MANUAL = -1,
	LOOP,
	ONCE
};

using M_S_Fr = std::map<std::string, Vec_SH<Frames>>;

class Animation
{
private:
	std::string Name;
	M_S_Fr Frame_Data;
	float TimeLength;
	float CurTime;
	//
	glm::mat4 GetMat(Vec_SH<Frames> Frms);
	Vec_SH<Frames> GetFrames(Vec_SH<Frames> Frms);
	glm::vec3 LinInter(glm::vec3 Vec0, glm::vec3 Vec1, float Ratio);
	glm::mat4 UpdatMatrix(glm::vec3 CurOffset, glm::quat CurRot, glm::vec3 CurScale);
	float GetTimeRatio(Vec_SH<Frames> Frms);
public:
	Animation(std::string InitName, float InitFloat, M_S_Fr Init_Frames);
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
	glm::mat4 GetMat(std::string BoneName);
	void AddFrame(float NewTime, std::string BoneName, S_P<Frames> NewFrame);
};

