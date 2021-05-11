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
	void SetBezier(Bezier_Bais NewBias);
	void SetType(InterType NewType);
};

class Anim_Skels
{
private:

public:
	Anim_Skels();
};

