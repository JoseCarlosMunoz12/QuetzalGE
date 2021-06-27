#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "../Render_Items/Vertex.h"

using M_S_M = std::map<std::string, glm::mat4>;
using M_S_I = std::map<std::string, int>;

struct Bone_Information
{
	glm::mat4 BoneOffset;
	glm::mat4 TransMats;
	int Id;
};

enum class InterType
{
	HOLD,
	LINEAR,
	QUADBENZ,
	CUBEBENZ
};

struct Bezier_Bais {
	float Point0;
	float Point1;
};

struct Joint
{
	glm::vec3 Offset;
	glm::quat Rotation;
	glm::vec3 Scale;
};

class Frames
{
private:
	float Time_Stamp;
	Joint Jnt;
	InterType Type;
	Bezier_Bais Bias;
public:
	Frames(float InitTime, Joint InitJoint, InterType InitType = InterType::LINEAR);
	~Frames() {}
	glm::quat GetRot();
	glm::vec3 GetOffset();
	glm::vec3 GetScale();
	Bezier_Bais GetBezier();
	InterType GetType();
	float GetTimeStamp();
	void SetRot(glm::quat NewRot);
	void SetOffset(glm::vec3 NewOffset);
	void SetScale(glm::vec3 NewScale);
	void SetBezier(Bezier_Bais NewBias);
	void SetType(InterType NewType);
};

class Skels
{
private:
	Vec_SH<Skels> Chlds;
	std::string Name;
public:
	Skels(std::string SetName) { this->Name = SetName; }
	~Skels() {}
	Vec_SH<Skels> GetChilds() { return this->Chlds; }
	void AddChild(S_P<Skels> NewChild) { this->Chlds.push_back(NewChild); }
	void AddChilds(Vec_SH<Skels> NewChlds)
	{
		for (auto& jj : NewChlds)
			this->AddChild(jj);
	}
	std::string GetId() { return this->Name; }
};
