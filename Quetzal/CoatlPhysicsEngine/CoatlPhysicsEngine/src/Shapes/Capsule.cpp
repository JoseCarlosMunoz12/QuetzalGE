#include "Capsule.h"
using namespace CoatlPhysicsEngine;

Capsule::Capsule(float InitRadius, float InitLength)
	:ColShapes(),UnitVec(glm::vec3(0.f,0.f,1.f))
{
	this->Radius = InitRadius;
	this->BPos = glm::vec3(0.f,0.f,InitLength/2.f);
	this->APos = -glm::vec3(0.f, 0.f, InitLength/2.f);
}

Capsule::~Capsule()
{
}

float Capsule::GetRadius()
{
	return this->Radius;
}

glm::vec3 Capsule::ClosestPoint_P(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle)
{
	return MATH::ClosestPoint_Pnt(GetSegment(pos, quatAngle), pos, Point);
}

float Capsule::Distance(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle)
{
	return MATH::Distance_Pnt(GetSegment(pos, quatAngle), pos, Point);
}

float Capsule::Distance(std::vector<glm::vec3> Segment, glm::vec3 pos, glm::quat quatAngle)
{
	return MATH::Distance_Seg(GetSegment(pos, quatAngle), pos, Segment);
}

std::vector<glm::vec3> Capsule::GetSegment(glm::vec3 pos, glm::quat quatAngle)
{

	glm::mat4 R = glm::mat4_cast(quatAngle);
	glm::mat4 T = glm::translate(glm::mat4(1.f), pos);
	std::vector<glm::vec3> Verx;
	{
		glm::vec4 Set = glm::vec4(APos,	1.f);
		Verx.push_back( T * R * Set);
	}
	{
		glm::vec4 Set = glm::vec4(this->BPos, 1.f);
		Verx.push_back( T * R * Set);
	}
	return Verx;
}

glm::vec3 Capsule::GetUnitVec()
{
	return this->UnitVec;
}

void Capsule::SetVec(glm::vec3 NewVec)
{
	this->UnitVec = glm::normalize(NewVec);
}

glm::vec3 Capsule::Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> Pnts = this->GetSegment(pos, quatAngle);
	float S = glm::dot(Pnts[0], Dir);
	glm::vec3 MaxPnt = Pnts[0];
	int Size = Pnts.size();
	for (int ii = 1; ii < Size; ii++)
	{
		float T = glm::dot(Pnts[ii], Dir);
		if (T > S)
		{
			S = T;
			MaxPnt = Pnts[ii];
		}
	}
	glm::vec3 Norm = glm::normalize(Dir);
	return MaxPnt + (this->Radius) * Norm;
}

glm::vec3 Capsule::EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> Pnts = this->GetSegment(pos, quatAngle);
	float S = glm::dot(Pnts[0], Dir);
	glm::vec3 MaxPnt = Pnts[0];
	int Size = Pnts.size();
	for (int ii = 1; ii < Size; ii++)
	{
		float T = glm::dot(Pnts[ii], Dir);
		if (T > S)
		{
			S = T;
			MaxPnt = Pnts[ii];
		}
	}
	return MaxPnt;
}

std::vector<glm::vec3> Capsule::GetVertices(glm::vec3 pos, glm::quat quatAngle)
{
	return this->GetSegment(pos, quatAngle);
}

std::vector<glm::vec3> Capsule::GetNormals(glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> Pnts = this->GetSegment(pos, quatAngle);
	glm::vec3 Norm = Pnts[1] - Pnts[0];
	Norm = glm::normalize(Norm);
	return {Norm};
}

glm::mat3 Capsule::GetInertia(float Mass)
{
	//Calculates the volumes and mass of both Sphere and Cylinder
	float Height = glm::distance(this->APos, this->BPos);
	float Vol_C = this->Radius * this->Radius * glm::pi<float>() * Height;
	float Vol_S = this->Radius * this->Radius * this->Radius * 4.f / 3.f * glm::pi<float>();
	float Vol_t = Vol_C + Vol_S;
	float Density = Mass / Vol_t;
	float Cy_M = Density * Vol_C;
	float Sp_M = Density * Vol_S;
	//calculates the inertia parts
	float XX = Cy_M *(glm::pow(Height,2.f)/16.f + glm::pow(this->Radius,2.f) / 4.f);
	XX += Sp_M * (2 * glm::pow(this->Radius,2.f) / 5 + glm::pow(Height, 2.f) / 2.f + 3.f * Height *this->Radius / 8.f);
	float YY = Cy_M * (glm::pow(this->Radius,2.f) / 2.f);
	YY += Sp_M * (2 * glm::pow(Radius,2.f) / 5.f);
	float ZZ = XX;
	//builds matrix
	glm::vec3 Col0(XX, 0.f, 0.f);
	glm::vec3 Col1(0.f, YY, 0.f);
	glm::vec3 Col2(0.f, 0.f, ZZ);
	return glm::mat3(Col0, Col1, Col2);
}
