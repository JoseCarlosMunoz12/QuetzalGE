#pragma once
#include "../../Maths/Q_Math.h"
#include <iostream>
#include <string>
#include <vector>
//math items
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
		SetQuat(InitQuat);
	}
	glm::quat GetQuat()
	{
		if (Angle == 360.f)
			Angle = 0;
		float RadAngle = Angle / 180.f * glm::pi<float>();
		return glm::angleAxis(RadAngle, UnitVec);
	}
	void SetQuat(glm::quat NewQuat)
	{
		if (NewQuat.w > 1.f)
			NewQuat = glm::normalize(NewQuat);
		float s = glm::sqrt(1 - NewQuat.w * NewQuat.w);
		this->Angle = 2.f * glm::acos(NewQuat.w) * 180.f / glm::pi<float>();;
		if (Angle == 0.f)
		{
			this->UnitVec = glm::vec3(0.f, 1.f, 0.f);
		}
		else
		{
			this->UnitVec = glm::vec3(NewQuat.x / s,
				NewQuat.y / s, NewQuat.z / s);
		}
	}
	void Cout()
	{
		std::cout << this->Angle << "\n";
		std::cout << this->UnitVec.x << "*" << this->UnitVec.y << "*" << this->UnitVec.z << "\n";

	}
};
//basic structures needed
template <typename T>
using U_P = std::unique_ptr<T>;
template <typename T>
using S_P = std::shared_ptr<T>;
template <typename T>
using Vec_SH = std::vector<S_P<T>>;
template <typename T>
using Vec_UP = std::vector<U_P<T>>;
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
	glm::quat Rot;
	glm::mat4 Matrix;
	//ID for Meshes and Textures
	std::vector<int> TextureID;
	int MeshId;
	int MatId;
	int ShaderId;
public:
	Node()
		:Position(glm::vec3(0.f)),Offset(glm::vec3(0.f)), Scale(glm::vec3(1.f)),
		Matrix(glm::mat4(1.f)),ShaderId(-1)
	{
		Quat Rs;
		Rot = Rs.GetQuat();
		this->MeshId = -1;
		this->MatId = -1;
	}
	Node(glm::vec3 InitPos, glm::vec3 InitOffset,
		glm::vec3 InitScale, glm::quat InitRot, int InitMeshId, int InitMatId)
		:Position(InitPos), Offset(InitOffset),
		Scale(InitScale),Rot(InitRot), Matrix(glm::mat4(1.f)),
		MeshId(InitMeshId), MatId(InitMatId), ShaderId(-1)
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
		glm::mat4 Temps = glm::mat4_cast(this->Rot);
		Matrix *= Temps;
		this->Matrix = glm::translate(this->Matrix, this->Offset);
		this->Matrix = glm::scale(this->Matrix, this->Scale);
	}
	glm::mat4 GetMatrix()
	{
		return this->Matrix;
	}
	//Getters
	glm::vec3 GetPos()           { return this->Position; }
	glm::vec3 GetOffset()	     { return this->Offset; }
	glm::vec3 GetScale()         { return this->Scale; }
	glm::quat GetRot()           { return this->Rot; }
	std::vector<int> GetTextId() { return this->TextureID; }
	int GetMeshId()              { return this->MeshId; }
	int GetMatId()               { return this->MatId; }
	int GetShaderId()            { return this->ShaderId; }
	//Setters
	void SetPos(glm::vec3 NewPos)       { this->Position = NewPos; }
	void SetOffset(glm::vec3 NewOffset) { this->Offset = NewOffset; }
	void SetScale(glm::vec3 NewScale)   { this->Scale = NewScale; }
	void SetRot(glm::quat NewRot)       { this->Rot = NewRot; }
	//set Matrices in correct in opengl space
	void SetW_Mat(glm::mat4 InitW)
	{
		Math::Decompose(InitW, this->Position, this->Rot, this->Scale);
		this->UpdateMatrix();
	}
	//Mesh and Texture relatd Function
	void AddTextureId(std::vector<int> NewIds) { this->TextureID.insert(this->TextureID.end(), NewIds.begin(), NewIds.end()); }
	void AddTextureId(int NewId)               { this->TextureID.push_back(NewId); }
	void SetMeshId(int NewId)                  { this->MeshId = NewId; }
	void AddShaderId(int NewId)                { this->ShaderId = NewId; }
	void ChangeModel(int NewID)	               { this->MeshId = NewID;	}
	void RemoveTextureId(int Id)               { this->TextureID.erase(this->TextureID.begin() + Id);	}
	void RemoveMeshId()                        { this->MeshId = -1; }
	void RemovedMatId()                        { this->MatId = -1; }
	void RemoveShaderId()                      { this->ShaderId = -1; }
};
//Data Structures for dynamic models
struct AnimVertex
{
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::ivec4 MatId;
	glm::vec4 Weights;
};
