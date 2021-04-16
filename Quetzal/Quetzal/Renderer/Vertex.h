#pragma once
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
#include <iostream>
#include <string>
#include <vector>
//Universal Data Structures

struct Quat
{
	float Angle;
	glm::vec3 UnitVec;
	Quat()
	{
		this->Angle = 0.f;
		this->UnitVec = glm::vec3(0.f, 0.f, 1.f);
	}
	Quat(float InitAngle)
	{
		this->Angle = InitAngle;
		this->UnitVec = glm::vec3(0.f, 1.f, 0.f);
	}
	Quat(float InitAngle, glm::vec3 InitVec)
	{
		this->Angle = InitAngle;
		this->UnitVec = glm::normalize(InitVec);
	}
	Quat(glm::quat InitQuat)
	{
		if (InitQuat.w > 1.f)
			InitQuat = glm::normalize(InitQuat);
		float s = glm::sqrt(1 - InitQuat.w * InitQuat.w);
		this->Angle = 2.f * glm::acos(InitQuat.w) * 180.f / glm::pi<float>();;
		if (Angle == 0.f)
		{
			this->UnitVec = glm::vec3(0.f, 0.f, 1.f);
		}
		else
		{

			this->UnitVec = glm::vec3(InitQuat.x / s,
				InitQuat.y / s, InitQuat.z / s);
		}
	}
	glm::quat GetQuat()
	{
		glm::quat Temp{};
		float RadAngle = Angle / 180.f * glm::pi<float>();
		Temp.x = UnitVec.x * glm::sin(RadAngle / 2);
		Temp.y = UnitVec.y * glm::sin(RadAngle / 2);
		Temp.z = UnitVec.z * glm::sin(RadAngle / 2);
		Temp.w = glm::cos(RadAngle / 2);
		return Temp;

	}
	void Cout()
	{
		std::cout << this->Angle << "\n";
		std::cout << this->UnitVec.x << "*" << this->UnitVec.y << "*" << this->UnitVec.z << "\n";

	}
};
//Data Structure for static models
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};
class Nodes
{
private:
	//Children
	std::vector<std::shared_ptr<Nodes>> Children;
	std::weak_ptr<Nodes> Par;
	//basic information
	glm::vec3 Position;
	glm::vec3 Offset;
	glm::vec3 Scale;
	Quat Rot;
public:
	Nodes(glm::vec3 InitPos, glm::vec3 InitOffset,
		glm::vec3 InitScale, Quat InitRot)
		:Position(InitPos), Offset(InitOffset),
		Scale(InitScale),Rot(InitRot)
	{

	}
	std::vector<std::shared_ptr<Nodes>> GetChildren()
	{
		return this->Children;
	}
	void AddChild(std::shared_ptr<Nodes> NewChild)
	{
		this->Children.push_back(NewChild);
	}
};
//Data Structures for dynamic models
struct AnimVertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::ivec4 MatId;
	glm::vec4 Weights;
};
