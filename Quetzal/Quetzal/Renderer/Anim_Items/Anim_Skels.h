#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "../Render_Items/Vertex.h"

using M_S_M = std::map<std::string, glm::mat4>;
using M_S_I = std::map<std::string, int>;

struct Bone_Inf
{
	glm::mat4 Offsets;
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

class Anim_Skels
{
private:
	//Holds children of skeletons
	Vec_SH<Anim_Skels> Chlds;
	//Holds Frames skeleton movement
	Vec_SH<Frames> Skel_Frames;
	//Current changes of the Skeleton
	glm::vec3 CurOffset;
	glm::vec3 CurScale;
	glm::quat CurRot;
	//Holds Current Matrix calculations
	glm::mat4 Matrix;
	//Bone Name
	std::string Bone_Name;
	Vec_SH<Frames> GetFrames(float Time);
	glm::vec3 LinInter(glm::vec3 Init, glm::vec3 Final, float Ratio);
	float GetTimeRatio(float Time, Vec_SH<Frames> Frms);
	void GetInterpolations(glm::vec3& NewCurO, glm::vec3& NewCurS, glm::quat& NewCurR, float Time);
public:
	Anim_Skels(Vec_SH<Frames> InitFrames, std::string InitName, glm::mat4 InitMat,
		glm::vec3 InitOffset, glm::quat InitQuat, glm::vec3 InitScale = glm::vec3(1.f));
	Anim_Skels(std::string InitName, glm::mat4 InitMat,
		glm::vec3 InitOffset, glm::quat InitQuat, glm::vec3 InitScale = glm::vec3(1.f));
	Anim_Skels(std::string Name);
	//Matrix To get
	void UpdateMatrix(float Time);
	bool GetMatrix(glm::mat4& CurMat);
	//Getters
	Vec_SH<Anim_Skels> GetChildren();
	glm::vec3 GetCurOffset();
	glm::vec3 GetCurScale();
	glm::quat GetCurRot();
	Vec_SH<Frames> GetFrames();
	std::string GetName();
	//Setters
	void SetCurOffset(glm::vec3 NewOffset);
	void SetCurScale(glm::vec3 NewScale);
	void SetCurRot(glm::quat NewRot);
	void SetChild(S_P<Anim_Skels> NewChld);
	void SetChilds(Vec_SH<Anim_Skels> NewChlds);
	void SetFrames(Vec_SH<Frames> NewFrames);
	//frame edits
	void DeleteFrame(int FrameId);
	void AddFrame(float NewTime);
};