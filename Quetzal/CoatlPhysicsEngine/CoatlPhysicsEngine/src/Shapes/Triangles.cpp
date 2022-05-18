#include "Triangles.h"
using namespace CoatlPhysicsEngine;

Triangles::Triangles(std::vector<glm::vec3> InitPoints)
	:ColShapes()
{
	for (int ii = 0; ii < 3; ii++)
	{
		this->Points[ii] = InitPoints[ii];
	}
}

Triangles::~Triangles()
{
}

std::vector<glm::vec3> Triangles::GetSegments(glm::vec3 pos, glm::quat quatAngle)
{
	glm::mat4 R = glm::mat4_cast(quatAngle);
	glm::mat4 T = glm::translate(glm::mat4(1.f), pos);
	std::vector<glm::vec3> SegPoints;
	for (auto& jj : Points)
	{
		glm::vec4 Set = glm::vec4(jj,1.f);
		SegPoints.push_back(T * R * Set);
	}
	return SegPoints;
}

glm::vec3 Triangles::GetClosestPoint(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle)
{	
	return MATH::ClosestPoint_Seg(GetSegments(pos, quatAngle), pos, Point);
}

glm::vec3 Triangles::Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> Pnts = this->GetSegments(pos, quatAngle);
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

glm::vec3 Triangles::EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	return this->Support(Dir,pos, quatAngle);
}

std::vector<glm::vec3> Triangles::GetVertices(glm::vec3 pos, glm::quat quatAngle)
{
	return this->GetSegments(pos, quatAngle);
}

std::vector<glm::vec3> Triangles::GetNormals(glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> T = this->GetSegments(pos, quatAngle);
	std::vector<glm::vec3> T_N = { glm::normalize(T[1] - T[0]),
		glm::normalize(T[2] - T[0]) };
	return T_N;
}