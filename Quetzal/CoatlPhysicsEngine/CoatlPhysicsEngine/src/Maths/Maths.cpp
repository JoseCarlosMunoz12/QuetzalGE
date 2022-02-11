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
	double EPSILON = 0.00000001;
	Vec3D D1 = Seg0[1] - Seg0[0];
	Vec3D D2 = Seg1[1] - Seg1[0];
	Vec3D R = Seg0[0] - Seg1[0];

	double A = D1 * D1;
	double E = D2 * D2;
	double F = D2 * R;

	double S = 0.0;
	double T = 0.0;
	if (A <= EPSILON && E <= EPSILON)
	{
		Pos0 = Seg0[0];
		Pos1 = Seg1[0];
		return;
	}
	if (A <= EPSILON)
	{
		S = 0.0;
		T = F / E;
		T = std::clamp(T, 0.0, 1.0);
	}
	else
	{
		double C = D1 * R;
		if (E <= EPSILON)
		{
			T = 0.0;
			S = std::clamp(-C / A, 0.0, 1.0);
		}
		else
		{
			double B = D1 * D2;
			double denom = A * E - B * B;
			if (denom != 0.0)
				S = std::clamp((B * F - C * E) / denom, 0.0, 1.0);
			else
				S = 0.0;
			T = ((B * S) + F) / E;
			if (T < 0.0)
			{
				T = 0;
				S = std::clamp(-C / A, 0.0, 1.0);
			}
			else
			{
				T = 1.0;
				S = std::clamp((B - C) / A, 0.0, 1.0);
			}
		}
	}
	Pos0 = Seg0[0] + D1 * S;
	Pos1 = Seg1[0] + D2 * T;
}

double MATH::Distance_Pnt(std::vector<Vec3D> Seg, Vec3D Pos, Vec3D Point)
{
	Vec3D P1 = MATH::ClosestPoint_Pnt(Seg, Pos, Point);
	Vec3D D = P1 - Pos;
	double mag = D * D;
	return std::sqrt(mag);

}

double MATH::Distance_Seg(std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1)
{
	Vec3D Pos0;
	Vec3D Pos1;
	MATH::ClosestSeg_Seg(Seg0, Seg1, Pos0, Pos1);
	Vec3D D = Pos0 - Pos1;
	double mag = D * D;
	return std::sqrt(mag);
}

double MATH::Distance_Tr_Pnt(std::vector<Vec3D> Tr, Vec3D Pos, Vec3D Pnt)
{
	Vec3D dis = MATH::ClosestPoint_Seg(Tr, Pos, Pnt);
	double mag = dis * dis;
	return std::sqrt(mag);
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
