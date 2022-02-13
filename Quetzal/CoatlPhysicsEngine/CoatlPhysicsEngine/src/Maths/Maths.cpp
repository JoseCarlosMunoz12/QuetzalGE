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

double MATH::Distance(Vec3D Pos0, Vec3D Pos1)
{
	Vec3D D = Pos0 - Pos1;
	double mag = D * D;
	return std::sqrt(mag);
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
	//Max Min of Shape 0
	Vec3D Max0;
	Vec3D Min0;
	//Max Min of Shape 1
	Vec3D Max1;
	Vec3D Min1;

	Vec3D AB = Seg[1] - Seg[0];
	int Count = 0;
	for (auto& jj : Sh_Vert0)
	{
		if (Count == 0)
		{
			Max0 = jj;
			Min0 = jj;
			Count++;
		}
		Vec3D AJJ = jj - Seg[0];
		double Num = AJJ * AB;
		double Denom = AB * AB;
		Vec3D TempPos = Seg[0] + AB * Num / Denom ;
		MATH::SetMaxMins(Max0, Min0, TempPos);
	}
	Count = 0;
	for (auto& jj : Sh_Vert1)
	{
		if (Count == 0)
		{
			Max1 = jj;
			Min1 = jj;
			Count++;
		}
		Vec3D AJJ = jj - Seg[0];
		double Num = AJJ * AB;
		double Denom = AB * AB;
		Vec3D TempPos = Seg[0] + AB *Num / Denom  ;
		MATH::SetMaxMins(Max1, Min1, TempPos);
	}
	double SegDis0 = MATH::Distance(Max0, Min0);
	double SegDis1 = MATH::Distance(Max1, Min1);
	double MaxMin0 = MATH::Distance(Max0, Min1);
	double MaxMin1 = MATH::Distance(Max1, Min0);

	double TotalLength = SegDis0 + SegDis1;
	double MaxL = std::max(MaxMin0, MaxMin1);

	return MaxL > TotalLength;
}

bool MATH::ProjColl(Vec3D Normal, std::vector<Vec3D> Sh_Vert0, std::vector<Vec3D> Sh_Vert1)
{
	//Max Min of Shape 0
	Vec3D Max0;
	Vec3D Min0;
	//Max Min of Shape 1
	Vec3D Max1;
	Vec3D Min1;

	int Count = 0;
	for (auto& jj : Sh_Vert0)
	{
		if (Count == 0)
		{
			Max0 = jj;
			Min0 = jj;
			Count++;
		}
		double Num = jj * Normal;
		double Denom = Normal * Normal;
		Vec3D TempPos =  Normal * Num / Denom;
		MATH::SetMaxMins(Max0, Min0, TempPos);
	}
	Count = 0;
	for (auto& jj : Sh_Vert1)
	{
		if (Count == 0)
		{
			Max1 = jj;
			Min1 = jj;
			Count++;
		}
		double Num = jj * Normal;
		double Denom = Normal * Normal;
		Vec3D TempPos = Normal * Num / Denom;
		MATH::SetMaxMins(Max1, Min1, TempPos);
	}
	double SegDis0 = MATH::Distance(Max0, Min0);
	double SegDis1 = MATH::Distance(Max1, Min1);
	double MaxMin0 = MATH::Distance(Max0, Min1);
	double MaxMin1 = MATH::Distance(Max1, Min0);

	double TotalLength = SegDis0 + SegDis1;
	double MaxL = std::max(MaxMin0, MaxMin1);

	return MaxL > TotalLength;
}

void MATH::SetMaxMins(Vec3D& Max, Vec3D& Min, Vec3D NewVal)
{
	if (Max[0] < NewVal[0])
	{
		Max[0] = NewVal[0];
	}
	if (Max[1] < NewVal[1])
	{
		Max[1] = NewVal[1];
	}
	if (Max[2] < NewVal[2])
	{
		Max[2] = NewVal[2];
		return;
	}
	//Check if Greater in Min
	if (Min[0] > NewVal[0])
	{
		Min[0] = NewVal[0];
	}
	if (Min[1] > NewVal[1])
	{
		Min[1] = NewVal[1];
	}
	if (Min[2] > NewVal[2])
	{
		Min[2] = NewVal[2];
	}
}

Vec3D MATH::SetMax(Vec3D Max, Vec3D NewVal)
{
	if (Max[0] < NewVal[0])
	{
		Max[0] = NewVal[0];
	}
	if (Max[1] < NewVal[1])
	{
		Max[1] = NewVal[1];
	}
	if (Max[2] < NewVal[2])
	{
		Max[2] = NewVal[2];
	}
	return Max;
}

Vec3D MATH::SetMin(Vec3D Min, Vec3D NewVal)
{
	if (Min[0] > NewVal[0])
	{
		Min[0] = NewVal[0];
	}
	if (Min[1] > NewVal[1])
	{
		Min[1] = NewVal[1];
	}
	if (Min[2] > NewVal[2])
	{
		Min[2] = NewVal[2];
	}
	return Min;
}

Vec3D MATH::CreateNormal(std::vector<Vec3D> Seg)
{
	Vec3D Dir = Seg[1] - Seg[0];
	Dir.Normalize();
	return Dir;
}
