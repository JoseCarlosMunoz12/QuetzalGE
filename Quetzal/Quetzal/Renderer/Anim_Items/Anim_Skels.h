#pragma once
#include <iostream>
#include <vector>

#include "../Render_Items/Vertex.h"
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
	//Hold init position
	glm::mat4 TransMat;
	glm::mat4 Offset;
	//Holds Current Matrix calculations
	glm::mat4 Matrix;
	//Bone Name
	std::string Bone_Name;
	Vec_SH<Frames> GetFrames(float Time);
	float GetTimeRatio(float Time, Vec_SH<Frames> Frms);
	void GetInterpolations(glm::vec3& NewCurO, glm::vec3& NewCurS, glm::quat& NewCurR, float Time);
	void UpdateMatrix(float Time);
public:
	Anim_Skels();
	//Matrix To get
	glm::mat4 GetMatrix(float CurTime);
	glm::mat4 GetOffset();
	//Getters
	Vec_SH<Anim_Skels> GetChildren();
	glm::vec3 GetCurOffset();
	glm::vec3 GetCurScale();
	glm::quat GetCurRot();
	Vec_SH<Frames> GetFrames();
	//Setters
	void SetCurOffset(glm::vec3 NewOffset);
	void SetCurScale(glm::vec3 NewScale);
	void SetCurRot(glm::quat NewRot);
	//frame edits
	void DeleteFrame(int FarameId);
	void AddFrame(float NewTime);
};