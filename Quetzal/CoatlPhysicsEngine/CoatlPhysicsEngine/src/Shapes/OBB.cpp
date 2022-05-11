#include "OBB.h"
using namespace CoatlPhysicsEngine;
OBB::OBB(float DimXYZ)
	:ColShapes()
{
	this->Ex.x = DimXYZ;
	this->Ex.y = DimXYZ;
	this->Ex.z = DimXYZ;
}

OBB::OBB(float DimX, float DimYZ)
	:ColShapes()
{
	this->Ex.x = DimX;
	this->Ex.y = DimYZ;
	this->Ex.z = DimYZ;
}

OBB::OBB(float DimX, float DimY, float DimZ)
	:ColShapes()
{
	this->Ex.x = DimX;
	this->Ex.y = DimY;
	this->Ex.z = DimZ;
}

OBB::~OBB()
{
}

std::vector<glm::vec3> OBB::GetSegments(glm::vec3 pos, glm::quat quatAngle)
{
	glm::mat4 R = glm::mat4_cast(quatAngle);
	glm::mat4 T = glm::translate(glm::mat4(1.f), pos);

	glm::vec3 Positions[] =
	{
		//Bottom Plane
		glm::vec3(Ex.x,-Ex.y,-Ex.z), glm::vec3(Ex.x, Ex.y,-Ex.z),
		glm::vec3(-Ex.x, Ex.y,-Ex.z), glm::vec3(-Ex.x,-Ex.y,-Ex.z),
		//Top Plane 
		glm::vec3(Ex.x,-Ex.y, Ex.z), glm::vec3(Ex.x, Ex.y, Ex.z),
		glm::vec3(-Ex.x, Ex.y, Ex.z), glm::vec3(-Ex.x,-Ex.y, Ex.z)
	};
	std::vector<glm::vec3> Lines(std::begin(Positions), std::end(Positions));

	for (auto& jj : Lines)
	{
		glm::vec4 Set = glm::vec4(jj, 1.f);
		jj = T * R * Set;
	}
	return Lines;
}

glm::vec3 OBB::GetLenghts()
{
	return this->Ex;
}

glm::vec3 OBB::GetClosestPoint(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> Segs = this->GetSegments(pos, quatAngle);
	glm::vec3 ClsPoints;
	std::vector<int> Ind = {0,1,1,2,2,3,3,0,
		4,5,5,6,6,7,7,4,
		0,4,1,5,2,6,3,7 };
	float Min;
	int Count = 0;
	for (int jj = 0; jj < 6; jj++)
	{
		int Val = jj * 2;
		glm::vec3 TempVec = MATH::ClosestPoint_Seg({ Segs[Ind[Val]], Segs[Ind[Val + 1]]}, Point);
		float Temp = glm::distance(Point, TempVec);
		if (Count > 0)
		{
			if (Min >Temp)
			{
				Min = Temp;
				ClsPoints = TempVec;
			}
		}
		else
		{
			Min = Temp;
			ClsPoints = TempVec;
		}
		Count++;
	}
	return ClsPoints;
}

glm::vec3 OBB::Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
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

glm::vec3 OBB::EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	return this->Support(Dir, pos, quatAngle);
}

std::vector<glm::vec3> OBB::GetVertices( glm::vec3 pos, glm::quat quatAngle)
{
	return this->GetSegments(pos,quatAngle);
}

std::vector<glm::vec3> OBB::GetNormals(glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> T = this->GetSegments(pos, quatAngle);
	std::vector<glm::vec3> OBB_N = { glm::normalize(T[1] - T[0]),
		glm::normalize(T[3] - T[0]) ,
		glm::normalize(T[4] - T[0]) };
	return OBB_N;
}
