#include "Maths.h"

Vec3D MATH::ClosestPoint_Seg(std::vector<Vec3D> trianlge, Vec3D Pos, Vec3D Point)
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

	double VC = D1 * D4 - D3 * D2;
	if (VC <= 0.0 && D1 >= 0.0 && D3 <= 0.0)
	{
		double V = D1 / (D1 - D3);
		return Pos + trianlge[0] + AB * V;
	}

	Vec3D CP = Point - (trianlge[2] + Pos);
	double D5 = AB * CP;
	double D6 = AC * CP;
	if (D6 >= 0.0 && D5 <= D6)
		return (trianlge[2] + Pos);
	double VB = D5 * D2 - D1 * D6;
	if (VB <= 0.0 && D2 >= 0.0 && D6 <= 0.0)
	{
		float W = (D4 - D3) / ((D4 - D3) + (D5 - D6));
		return( Pos + trianlge[1] + (trianlge[2] - trianlge[1]) * W);
	}
	double VA = D3 * D6 - D5 * D4;
	if (VA <= 0.0 && (D4 - D3) >= 0.0 && (D5 - D6) >= 0.0)
	{
		double W = (D4 - D3) / ((D4 - D3) + (D5 - D6));
		return Pos + trianlge[1] + (trianlge[2] - trianlge[1]) * W;
	}

	double Denom = 1.0 / (VA + VB + VC);
	double V = VB * Denom;
	return Vec3D();
}

Vec3D MATH::ClosestPoint_Seg(std::vector<Vec3D> Seg, Vec3D Point)
{
	Vec3D AB = Seg[1] - Seg[0];
	double s = AB * AB;
	if (s == 0.0)
		return Seg[0];
	double d = (Point - Seg[0]) * AB / s;
	d = std::clamp(d, 0.0, 1.0);
	return Seg[0] + AB * d;
}

Vec3D MATH::ClosestPoint_Pnt(std::vector<Vec3D> Seg, Vec3D Pos, Vec3D Point)
{
	Vec3D AB = Seg[1] - Seg[0];
	double s = AB * AB;
	if (s == 0.0)
		return Pos +Seg[0];
	double d = (Point - (Pos +Seg[0])) * AB / s;
	d = std::clamp(d, 0.0, 1.0);
	return Pos + Seg[0] + AB * d;
}

void MATH::ClosestSeg_Seg(std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1, Vec3D& Pos0, Vec3D& Pos1)
{
}

double MATH::Distance_Pnt(std::vector<Vec3D> Seg, Vec3D Pos, Vec3D Point)
{
	return 0.0;
}

double MATH::Distance_Seg(std::vector<Vec3D> Seg0, Vec3D Pos, std::vector<Vec3D> Seg1)
{
	return 0.0;
}

double MATH::Distance_Seg(std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1)
{
	return 0.0;
}

double MATH::Distance_Tr_Pnt(std::vector<Vec3D> Tr, Vec3D Pos, Vec3D Pnt)
{
	return 0.0;
}

bool MATH::ProjColl(std::vector<Vec3D> Seg, std::vector<Vec3D> Sh_Vert0, std::vector<Vec3D> Sh_Vert1)
{
	return false;
}

bool MATH::ProjColl(Vec3D Normal, std::vector<Vec3D> Sh_Vert0, std::vector<Vec3D> Sh_Vert1)
{
	return false;
}

bool MATH::SATColCheck(std::vector<Vec3D> Norm0, std::vector<Vec3D> Norm1, std::vector<Vec3D> Pnts0, std::vector<Vec3D> Pnts1)
{
	return false;
}

void MATH::SetMaxMins(Vec3D& Max, Vec3D& Min, Vec3D NewVal)
{
}

Vec3D MATH::SetMax(Vec3D Max, Vec3D NewVal)
{
	return Vec3D();
}

Vec3D MATH::SetMin(Vec3D Min, Vec3D NewVal)
{
	return Vec3D();
}

Vec3D MATH::CreateNormal(std::vector<Vec3D> Seg)
{
	return Vec3D();
}

Vec3D MATH::Normalize(Vec3D Vec)
{
	return Vec3D();
}

Vec3D MATH::ClampLowest(Vec3D Vec, float Limit)
{
	return Vec3D();
}

bool MATH::IsSame(Vec3D Vec0, Vec3D Vec1)
{
	return false;
}
