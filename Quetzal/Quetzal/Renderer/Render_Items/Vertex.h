#pragma once
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
#include <iostream>
#include <string>
#include <vector>
template <typename T>
using S_P = std::shared_ptr<T>;
template <typename T>
using Vec_SH = std::vector<S_P<T>>;
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
		return glm::angleAxis(RadAngle, UnitVec);
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
	glm::vec2 texcoord;
	glm::vec3 normal;
};
class Node
{
private:
	//Children
	std::vector<std::shared_ptr<Node>> Children;
	//basic information
	glm::vec3 Position;
	glm::vec3 Offset;
	glm::vec3 Scale;
	Quat Rot;
	glm::mat4 Matrix;
	glm::mat4 W_Mat = glm::mat4(1.f);
	//ID for Meshes and Textures
	std::vector<int> TextureID;
	int MeshId;
	int MatId;
public:
	Node()
		:Position(glm::vec3(0.f)),Offset(glm::vec3(0.f)), Scale(glm::vec3(1.f)),
		Rot(Quat()),Matrix(glm::mat4(1.f))
	{
		this->MeshId = -1;
		this->MatId = -1;
	}
	Node(glm::vec3 InitPos, glm::vec3 InitOffset,
		glm::vec3 InitScale, Quat InitRot, int InitMeshId, int InitMatId)
		:Position(InitPos), Offset(InitOffset),
		Scale(InitScale),Rot(InitRot), Matrix(glm::mat4(1.f)),
		MeshId(InitMeshId), MatId(InitMatId)
	{
		this->TextureID = {};

	}
	~Node() {}
	//Child related functions
	std::vector<std::shared_ptr<Node>> GetChildren()
	{
		return this->Children;
	}
	void AddChild(std::shared_ptr<Node> NewChild)
	{
		this->Children.push_back(NewChild);
	}
	void RemoveChild(int ChildId) 
	{
		this->Children.erase(this->Children.begin() + ChildId);
	}
	//Matrix related function
	void UpdateMatrix()
	{
		this->Matrix = glm::mat4(1.f);
		this->Matrix = glm::translate(this->Matrix, this->Position);
		glm::mat4 Temps = glm::mat4_cast(this->Rot.GetQuat());
		Matrix *= Temps;
		this->Matrix = glm::translate(this->Matrix, this->Offset);
		this->Matrix = glm::scale(this->Matrix, this->Scale);
	}
	glm::mat4 GetMatrix()
	{
		return this->W_Mat * this->Matrix;
	}
	//Getters
	glm::vec3 GetPos()           { return this->W_Mat * glm::vec4(this->Position,1.f); }
	glm::vec3 GetOffset()	     { return this->W_Mat * glm::vec4(this->Offset, 1.f); }
	glm::vec3 GetScale()         { return this->Scale; }
	Quat GetRot()                { return this->Rot; }
	std::vector<int> GetTextId() { return this->TextureID; }
	int GetMeshId()              { return this->MeshId; }
	int GetMatId()               { return this->MatId; }
	//Setters
	void SetPos(glm::vec3 NewPos)       { this->Position= glm::inverse(this->W_Mat) * glm::vec4(NewPos,1.f);}
	void SetOffset(glm::vec3 NewOffset) { this->Offset = NewOffset; }
	void SetScale(glm::vec3 NewScale)   { this->Scale = NewScale; }
	void SetRot(Quat NewRot)            { this->Rot = NewRot; }
	void SetW_Mat(glm::mat4 InitW)      { this->W_Mat = InitW; }
	//Mesh and Texture relatd Function
	void AddTextureId(std::vector<int> NewIds) { this->TextureID.insert(this->TextureID.end(), NewIds.begin(), NewIds.end()); }
	void AddTextureId(int NewId)               { this->TextureID.push_back(NewId); }
	void SetMeshId(int NewId)                  { this->MeshId = NewId; }
	void ChangeModel(int NewID)	               { this->MeshId = NewID;	}
	void RemoveTextureId(int Id)               { this->TextureID.erase(this->TextureID.begin() + Id);	}
	void RemoveMeshId()                        { this->MeshId = -1; }
	void RemovedMatId()                        { this->MatId = -1; }
};
//Data Structures for dynamic models
struct AnimVertex
{
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::ivec3 MatId;
	glm::vec3 Weights;
};
