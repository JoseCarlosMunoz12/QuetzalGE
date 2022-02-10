#include "Maths.h"
using namespace MATH;

Vec3D  ClosestPoint_Seg(std::vector<Vec3D> trianlge, Vec3D Pos, Vec3D Point)
{
	Vec3D AB = trianlge[1] - trianlge[0];
	Vec3D AC = trianlge[2] - trianlge[0];
	Vec3D AP = Point - (trianlge[0] - Pos);
	double D1 = AB * AP;
	double D2 = AC * AP;
	if (D1 <= 0.0 && D2 <= 0.0)
		return (trianlge[0] + Pos);

	Vec3D BP = Point - (trianlge[1] + Pos);
	double D3 = AB * BP;
	double D4 = AC * BP;
	if (D3 <= 0.0 && D4 <= 0.0)
		return (trianlge[1] + Pos);

	return Vec3D();
}

Vec3D ClosestPoint_Seg(std::vector<Vec3D> Seg, Vec3D Point)
{
	return Vec3D();
}

Vec3D ClosestPoint_Pnt(std::vector<Vec3D> Seg, Vec3D Pos, Vec3D Point)
{
	return Vec3D();
}

void ClosestSeg_Seg(std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1, Vec3D& Pos0, Vec3D& Pos1)
{
}

double Distance_Pnt(std::vector<Vec3D> Seg, Vec3D Pos, Vec3D Point)
{
	return 0.0;
}

double Distance_Seg(std::vector<Vec3D> Seg0, Vec3D Pos, std::vector<Vec3D> Seg1)
{
	return 0.0;
}

double Distance_Seg(std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1)
{
	return 0.0;
}

double Distance_Tr_Pnt(std::vector<Vec3D> Tr, Vec3D Pos, Vec3D Pnt)
{
	return 0.0;
}

bool ProjColl(std::vector<Vec3D> Seg, std::vector<Vec3D> Sh_Vert0, std::vector<Vec3D> Sh_Vert1)
{
	return false;
}

bool ProjColl(Vec3D Normal, std::vector<Vec3D> Sh_Vert0, std::vector<Vec3D> Sh_Vert1)
{
	return false;
}

bool SATColCheck(std::vector<Vec3D> Norm0, std::vector<Vec3D> Norm1, std::vector<Vec3D> Pnts0, std::vector<Vec3D> Pnts1)
{
	return false;
}

void SetMaxMins(Vec3D& Max, Vec3D& Min, Vec3D NewVal)
{
}

Vec3D SetMax(Vec3D Max, Vec3D NewVal)
{
	return Vec3D();
}

Vec3D SetMin(Vec3D Min, Vec3D NewVal)
{
	return Vec3D();
}

Vec3D CreateNormal(std::vector<Vec3D> Seg)
{
	return Vec3D();
}

Vec3D Normalize(Vec3D Vec)
{
	return Vec3D();
}

Vec3D ClampLowest(Vec3D Vec, float Limit)
{
	return Vec3D();
}

bool IsSame(Vec3D Vec0, Vec3D Vec1)
{
	return false;
}
