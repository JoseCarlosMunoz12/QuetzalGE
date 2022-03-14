#include "GJK.h"
using namespace CoatlPhysicsEngine;

GJK::GJK()
{
}

GJK::~GJK()
{
}

double GJK::F3Box(Vec3D A, Vec3D B, Vec3D C)
{
	Vec3D N = A ^ B;
	return N * C;
}

Vec3D GJK::TripleCross(Vec3D A, Vec3D B)
{
	Vec3D T = A ^ B;
	return T ^ A;
}

int GJK::Tr_Farthest_Point(std::vector<Vec3D> Vec)
{

	Vec3D Zed(0.0);
	float R = MATH::Distance(Zed, Vec[0]);
	int Id = 0;
	int Count = 0;
	for (auto& ii : Vec)
	{
		double S = ii.length();
		if (R < S)
		{
			R = S;
			Id = Count;
		}
		Count++;
	}
	return Id;
}

Vec3D GJK::Support(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D Dir)
{
	return Shape0->Support(Dir) - Shape1->Support(Dir);
}

Vec3D GJK::Support(S_P<Shape> Shape0, S_P<Shape> Shape1, std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1, Vec3D Dir)
{
	Vec3D Sp0 = Support(Seg0, Dir) + Shape0->Support(Dir);
	Dir.Multiply(-1.0);
	Vec3D Sp1 = Support(Seg1, Dir) + Shape1->Support(Dir);
	return Sp0 - Sp1;
}

Vec3D GJK::Support(std::vector<Vec3D> Seg, Vec3D Dir)
{
	double S = Seg[0] * Dir;
	Vec3D MaxPnt = Seg[0];
	int Size = Seg.size();
	for (int ii = 1; ii < Size; ii++)
	{
		float T = Seg[ii] * Dir;
		if (T > S)
		{
			S = T;
			MaxPnt = Seg[ii];
		}
	}
	return MaxPnt;
}

bool GJK::Simplex_Maker(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D Pos0, Vec3D Pos1, std::vector<Vec3D>& Verts, Vec3D& Dir)
{
	int Size = Verts.size();
	switch (Size)
	{
	case 0: {
		Vec3D S_Pos0 = Shape0->GetPosition() + Pos0;
		Vec3D S_Pos1 = Shape1->GetPosition() + Pos1;
		Dir = S_Pos0 - S_Pos1;
	}break;
	case 1: {
		Dir = Verts[0];
		Dir.Multiply(-1.0);
	}break;
	case 2: {
		Vec3D AB = Verts[0] - Verts[1];
		Vec3D A0 = Verts[1];
		A0.Multiply(-1.0);
		if ( AB * A0 > 0.0)
			Dir = TripleCross(AB, A0);
		else
			Dir = A0;
	}break;
	case 3: {
		Vec3D A = Verts[2];
		Vec3D B = Verts[1];
		Vec3D C = Verts[0];

		Vec3D AB = B - A;
		Vec3D AC = C - A;
		Vec3D A0 = A;
		A0.Multiply(-1.0);
		Vec3D ABC = AB ^ AC;

		Vec3D ABC_AC = ABC ^ AC;
		Vec3D AB_ABC = AB ^ ABC;

		if (ABC_AC * A0 > 0.0)
		{
			if (AC * A0 > 0.0)
				Dir = TripleCross(AC, A0);
			else
			{
				if (AB * A0 > 0.0)
					Dir = TripleCross(AB, A0);
				else
					Dir = A0;
			}
		}
		else
		{
			if (AB_ABC * A0 > 0.0)
			{
				if (AB * A0 > 0.0)
					Dir = TripleCross(AB, A0);
				else
					Dir = A0;
			}
			else
			{
				if (ABC * A0 > 0.0)
					Dir = ABC;
				else
				{
					Dir = ABC;
					Dir.Multiply(-1.0);
				}
			}
		}
	}break;
	case 4: {
		Vec3D A = Verts[3];
		Vec3D B = Verts[2];
		Vec3D C = Verts[1];
		Vec3D D = Verts[0];

		Vec3D AC = C - A;
		Vec3D AD = D - A;
		Vec3D AB = B - A;
		Vec3D A0 = A;
		A0.Multiply(-1.0);

		Vec3D AC_AB = AC ^ AB;
		Vec3D AB_AD = AB ^ AD;
		Vec3D AD_AC = AD ^ AC;

		float vABC = AC_AB * A0;
		float vABD = AB_AD * A0;
		float vADC = AD_AC * A0;

		int neg = 0;
		int pos = 0;

		if (vABC >= 0)
			pos++;
		else
			neg++;

		if (vABD > 0)
			pos++;
		else
			neg++;

		if (vADC > 0)
			pos++;
		else
			neg++;

		if (neg == 3)
			return true;
		if (pos == 3)
			return true;
		if (neg == 2 and pos == 1)
		{
			if (vADC > 0.f)
			{
				Verts.erase(Verts.begin() + 1);
				Dir = AD_AC;
			}
			else if (vABD > 0.f)
			{
				Verts.erase(Verts.begin() + 2);
				Dir = AB_AD;
			}
			else
			{
				Verts.erase(Verts.begin() + 0);
				Dir = AC_AB;
			}
		}
		else
		{
			if (vADC < 0.f)
			{
				Verts.erase(Verts.begin() + 1);
				Dir = AD_AC;
				Dir.Multiply(-1.0);
			}
			else if (vABD < 0.f)
			{
				Verts.erase(Verts.begin() + 2);
				Dir = AB_AD;
				Dir.Multiply(-1.0);
			}
			else
			{
				Verts.erase(Verts.begin() + 0);
				Dir = AC_AB;
				Dir.Multiply(-1.0);
			}
		}
	}break;
	default:
		break;
	}
	return false;
}

Vec3D GJK::EPA_Support(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D Dir)
{
	Vec3D negDir = Dir;
	negDir.Multiply(-1.0);
	return Shape0->EPA_Support(Dir) - Shape1->EPA_Support(negDir);
}

Vec3D GJK::EPA(std::vector<Vec3D> Vertex, S_P<Shape> Shape0, S_P<Shape> Shape1, double& Pen)
{
	Vec3D Faces[EPA_MAX_NUM_FACES][4];//Array of faces, each with 3 verts and a normal	
	//A = 3
	//B = 2
	//C = 1
	//D = 0
	Faces[0][0] = Vertex[3];
	Faces[0][1] = Vertex[2];
	Faces[0][2] = Vertex[1];
	Faces[0][3] = ((Vertex[2] - Vertex[3]) ^ (Vertex[1] - Vertex[3])).SetNormalize(); //ABC	
	Faces[1][0] = Vertex[3];
	Faces[1][1] = Vertex[1];
	Faces[1][2] = Vertex[0];
	Faces[1][3] = ((Vertex[1] - Vertex[3]) ^(Vertex[0] - Vertex[3])).SetNormalize(); //ACD	
	Faces[2][0] = Vertex[3];
	Faces[2][1] = Vertex[0];
	Faces[2][2] = Vertex[2];
	Faces[2][3] = ((Vertex[0] - Vertex[3]) ^( Vertex[2] - Vertex[3])).SetNormalize(); //ADB	
	Faces[3][0] = Vertex[2];
	Faces[3][1] = Vertex[0];
	Faces[3][2] = Vertex[1];
	Faces[3][3] = ((Vertex[0] - Vertex[2]) ^ (Vertex[1] - Vertex[2])).SetNormalize(); //BDC	
	int Num_Face = 4;
	int ClosestFace;
	Vec3D Zed(0.f);
	for (int It = 0; It < EPA_MAX_NUM_ITERATIONS; It++)
	{
		//Find Face that's closest to origin
		float Min_Dist = MATH::Distance_Tr_Pnt({ Faces[0][0] ,Faces[0][1] ,Faces[0][2] }, Zed, Zed);
		ClosestFace = 0;
		for (int ii = 1; ii < Num_Face; ii++)
		{
			float dist = MATH::Distance_Tr_Pnt({ Faces[ii][0] ,Faces[ii][1] ,Faces[ii][2] }, Zed, Zed);
			if (dist < Min_Dist)
			{
				Min_Dist = dist;
				ClosestFace = ii;
			}
		}
		//search normal to face that's closets to origin	
		Vec3D Search_Dir = Faces[ClosestFace][3];
		Vec3D P = EPA_Support(Shape0, Shape1, Search_Dir);
		double Dif = (P * Search_Dir) - Min_Dist;
		if (Dif < EPA_TOLERANCE)
		{
			Pen = MATH::Distance_Tr_Pnt({ Faces[ClosestFace][0] ,Faces[ClosestFace][1] ,Faces[ClosestFace][2] }, Zed, Zed);
			return Faces[ClosestFace][3];
		}
		Vec3D LooseEdges[EPA_MAX_NUM_FACES][2];
		int NumLooseEdge = 0;
		//find all triangles that are facing P	
		for (int ii = 0; ii < Num_Face; ii++)
		{
			if (Faces[ii][3] * (P - Faces[ii][0]) > 0.0)
			{
				for (int jj = 0; jj < 3; jj++)
				{
					Vec3D CurEdg[2] = { Faces[ii][jj],Faces[ii][(jj + 1) % 3] };
					bool FoundEdge = false;
					for (int kk = 0; kk < NumLooseEdge; kk++)
					{
						if (LooseEdges[kk][1] == CurEdg[0] && LooseEdges[kk][0] == CurEdg[1])
						{
							LooseEdges[kk][0] = LooseEdges[NumLooseEdge - 1][0];
							LooseEdges[kk][1] = LooseEdges[NumLooseEdge - 1][1];
							NumLooseEdge--;
							FoundEdge = true;
							kk = NumLooseEdge;
						}
					}
					if (!FoundEdge)
					{
						if (NumLooseEdge >= EPA_MAX_NUM_LOOSE_EDGES)break;
						LooseEdges[NumLooseEdge][0] = CurEdg[0];
						LooseEdges[NumLooseEdge][1] = CurEdg[1];
						NumLooseEdge++;
					}
				}
				Faces[ii][0] = Faces[Num_Face - 1][0];
				Faces[ii][1] = Faces[Num_Face - 1][1];
				Faces[ii][2] = Faces[Num_Face - 1][2];
				Faces[ii][3] = Faces[Num_Face - 1][3];
				Num_Face--;
				ii--;
			}
		}
		//Reconstruct polytope with p added	
		for (int ii = 0; ii < NumLooseEdge; ii++)
		{
			if (Num_Face >= EPA_MAX_NUM_FACES) break;
			Faces[Num_Face][0] = LooseEdges[ii][0];
			Faces[Num_Face][1] = LooseEdges[ii][1];
			Faces[Num_Face][2] = P;
			Faces[Num_Face][3] = ((LooseEdges[ii][0] - LooseEdges[ii][1]) ^ ( LooseEdges[ii][0] - P)).SetNormalize();
			float bias = 0.000001f;
			float Diff = (Faces[Num_Face][0] * Faces[Num_Face][3]) + bias;
			if (Dif < 0)
			{
				Vec3D Temp = Faces[Num_Face][0];
				Faces[Num_Face][0] = Faces[Num_Face][1];
				Faces[Num_Face][1] = Temp;
				Faces[Num_Face][3] = Faces[Num_Face][3];
				Faces[Num_Face][3].Multiply(-1.0);
			}
			Num_Face++;
		}
	}
	Pen = Faces[ClosestFace][0] * Faces[ClosestFace][3];
	return Faces[ClosestFace][3];
}

Vec3D GJK::ClosestPoint(std::vector<Vec3D> Verts)
{
	Vec3D Zed(0.0);
	switch (Verts.size())
	{
	case 1:
		return Verts[0];
		break;
	case 2:
		return MATH::ClosestPoint_Seg(Verts, Zed);
		break;
	case 3:
		return MATH::ClosestPoint_Seg(Verts, Zed, Zed);
		break;
	default:
		break;
	}
	return Zed;
}

std::vector<Vec3D> GJK::NewSimplex(std::vector<Vec3D> Verts, Vec3D NewPoint)
{
	int Vec[6] = { 0,1,0,2,1,2 };
	int Vals = 0;
	Vec3D Zed(0.0);
	Vec3D Dis = MATH::ClosestPoint_Seg({ Verts[0],Verts[1],NewPoint }, Zed, Zed);
	float P_Dis = MATH::Distance(Zed, Dis);
	for (int ii = 1; ii < 3; ii++)
	{
		Vec3D NewDis = MATH::ClosestPoint_Seg({ Verts[Vec[2 * ii]],Verts[Vec[2 * ii + 1]],NewPoint }, Zed, Zed);
		float T_Dis = MATH::Distance(Zed, NewDis);
		if (T_Dis < P_Dis)
		{
			P_Dis = T_Dis;
			Vals = ii;
		}
	}
	return { Verts[Vec[2 * Vals]], Verts[Vec[2 * Vals + 1]], NewPoint };
}

double GJK::Cl_Dist(std::vector<Vec3D> Verts)
{
	Vec3D Cl_P = ClosestPoint(Verts);
	return Cl_P.length();
}

Vec3D GJK::C_F_E(S_P<Shape> Shape0, S_P<Shape> Shape1)
{
	std::vector<Vec3D> Verts;
	Vec3D NewDir;
	Simplex_Maker(Shape0, Shape1, Verts, NewDir);
	Verts.push_back(EPA_Support(Shape0, Shape1, NewDir));
	Vec3D Zed(0.0);
	NewDir = this->ClosestPoint(Verts);
	float Cl_Dis = MATH::Distance(Zed, NewDir);
	Vec3D negDir = NewDir;
	negDir.Multiply(-1.0);
	Vec3D A = EPA_Support(Shape0, Shape1, negDir);
	for (int ii = 0; ii < 20; ii++)
	{
		if (std::find(Verts.begin(), Verts.end(), A) != Verts.end())
			break;
		if (Verts.size() == 3)
			Verts = this->NewSimplex(Verts, A);
		else
			Verts.push_back(A);
		NewDir = this->ClosestPoint(Verts);
		double Cur_Dis = MATH::Distance(Zed, NewDir);
		if (Cur_Dis < Cl_Dis)
			Cl_Dis = Cur_Dis;
		else if ((Cur_Dis - Cl_Dis) < 0.00001f)
			break;
		negDir = NewDir;
		negDir.Multiply(-1.0);
		A = EPA_Support(Shape0, Shape1, negDir);
	}
	return this->ClosestPoint(Verts);
}

bool GJK::Simplex_Maker(S_P<Shape> Shape0, S_P<Shape> Shape1, std::vector<Vec3D>& Verts, Vec3D& Dir)
{
	int Size = Verts.size();
	switch (Size)
	{
	case 0: {
		Dir = Shape0->GetPosition() - Shape1->GetPosition();
	}break;
	case 1: {
		Dir = Verts[0];
		Dir.Multiply(-1.0);
	}break;
	case 2: {
		Vec3D AB = Verts[0] - Verts[1];
		Vec3D A0 = Verts[1];
		A0.Multiply(-1.0);
		if ((AB * A0) > 0.0)
			Dir = TripleCross(AB, A0);
		else
			Dir = A0;
	}break;
	case 3: {
		Vec3D A = Verts[2];
		Vec3D B = Verts[1];
		Vec3D C = Verts[0];

		Vec3D AB = B - A;
		Vec3D AC = C - A;
		Vec3D A0 = A;
		A0.Multiply(-1.0);
		Vec3D ABC = AB ^ AC;

		Vec3D ABC_AC = ABC ^ AC;
		Vec3D AB_ABC = AB ^ ABC;

		if ((ABC_AC * A0) > 0.0)
		{
			if ((AC * A0) > 0.0)
				Dir = TripleCross(AC, A0);
			else
			{
				if ((AB * A0) > 0.0)
					Dir = TripleCross(AB, A0);
				else
					Dir = A0;
			}
		}
		else
		{
			if ((AB_ABC * A0) > 0.0)
			{
				if ((AB * A0) > 0.0)
					Dir = TripleCross(AB, A0);
				else
					Dir = A0;
			}
			else
			{
				if ((ABC * A0) > 0.f)
					Dir = ABC;
				else
				{
					Dir = ABC;
					Dir.Multiply(-1.0);
				}
			}
		}
	}break;
	case 4: {
		Vec3D A = Verts[3];
		Vec3D B = Verts[2];
		Vec3D C = Verts[1];
		Vec3D D = Verts[0];

		Vec3D AC = C - A;
		Vec3D AD = D - A;
		Vec3D AB = B - A;
		Vec3D A0 = A;
		A0.Multiply(-1.0);

		Vec3D AC_AB = AC ^ AB;
		Vec3D AB_AD = AB ^ AD;
		Vec3D AD_AC = AD ^ AC;

		float vABC = AC_AB * A0;
		float vABD = AB_AD * A0;
		float vADC = AD_AC * A0;

		int neg = 0;
		int pos = 0;

		if (vABC >= 0)
			pos++;
		else
			neg++;

		if (vABD > 0)
			pos++;
		else
			neg++;

		if (vADC > 0)
			pos++;
		else
			neg++;

		if (neg == 3)
			return true;
		if (pos == 3)
			return true;
		if (neg == 2 and pos == 1)
		{
			if (vADC > 0.f)
			{
				Verts.erase(Verts.begin() + 1);
				Dir = AD_AC;
			}
			else if (vABD > 0.f)
			{
				Verts.erase(Verts.begin() + 2);
				Dir = AB_AD;
			}
			else
			{
				Verts.erase(Verts.begin() + 0);
				Dir = AC_AB;
			}
		}
		else
		{
			if (vADC < 0.f)
			{
				Verts.erase(Verts.begin() + 1);
				Dir = AD_AC;
				Dir.Multiply(-1.0);
			}
			else if (vABD < 0.f)
			{
				Verts.erase(Verts.begin() + 2);
				Dir = AB_AD;
				Dir.Multiply(-1.0);
			}
			else
			{
				Verts.erase(Verts.begin() + 0);
				Dir = AC_AB;
				Dir.Multiply(-1.0);
			}
		}
	}break;
	default:
		break;
	}
	return false;
}

std::vector<int> GJK::C_F_S(std::vector<Vec3D>& Verts)
{
	Vec3D A = Verts[3];
	Vec3D B = Verts[2];
	Vec3D C = Verts[1];
	Vec3D D = Verts[0];

	Vec3D AC = C - A;
	Vec3D AD = D - A;
	Vec3D AB = B - A;
	Vec3D A0 = A;
	A0.Multiply(-1.0);

	Vec3D AC_AB = AC ^ AB;
	Vec3D AB_AD = AB ^ AD;
	Vec3D AD_AC = AD ^ AC;

	float vABC = AC_AB * A0;
	float vABD = AB_AD * A0;
	float vADC = AD_AC * A0;

	int neg = 0;
	int pos = 0;

	if (vABC > 0)
		pos++;
	else
		neg++;

	if (vABD > 0)
		pos++;
	else
		neg++;

	if (vADC > 0)
		pos++;
	else
		neg++;
	if (neg == 2 and pos == 1)
	{
		if (vADC > 0.f)
			return { 0, 2 };
		else if (vABD > 0.f)
			return { 0, 1 };
		else
			return { 1, 2 };
	}
	else
	{
		if (vADC < 0.f)
			return { 0, 2 };
		else if (vABD < 0.f)
			return { 0, 1 };
		else
			return { 1, 2 };
	}
}

bool GJK::GJK_Col(S_P<Shape> Shape0, S_P<Shape> Shape1)
{
	std::vector<Vec3D> Verts;
	Vec3D Dir;
	Simplex_Maker(Shape0, Shape1, Verts, Dir);
	Verts.push_back(Support(Shape0, Shape1, Dir));
	Simplex_Maker(Shape0, Shape1, Verts, Dir);
	for (int ii = 0; ii < 20; ii++)
	{
		Vec3D A = Support(Shape0, Shape1, Dir);
		if ((A * Dir) <= 0.0)
			return false;
		if (std::find(Verts.begin(), Verts.end(), A) != Verts.end())
			break;
		Verts.push_back(A);
		if (Simplex_Maker(Shape0, Shape1, Verts, Dir))
			return true;
	}
	return false;
}

bool GJK::GJK_Col(S_P<Shape> Shape0, S_P<Shape> Shape1, std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1)
{
	std::vector<Vec3D> Verts;
	Vec3D Pos0 = (Seg0[1] + Seg0[0]);
	Pos0.Multiply(1.0 / 2.0);
	Vec3D Pos1 = (Seg1[1] + Seg1[0]);
	Pos1.Multiply(1.0 / 2.0);
	Vec3D Dir;
	Simplex_Maker(Shape0, Shape1, Pos0, Pos1, Verts, Dir);
	Verts.push_back(Support(Shape0, Shape1, Seg0, Seg1, Dir));
	Simplex_Maker(Shape0, Shape1, Pos0, Pos1, Verts, Dir);
	for (int ii = 0; ii < 20; ii++)
	{
		Vec3D A = Support(Shape0, Shape1, Seg0, Seg1, Dir);
		if ((A * Dir) <= 0.f)
			return false;
		if (std::find(Verts.begin(), Verts.end(), A) != Verts.end())
			break;
		Verts.push_back(A);
		if (Simplex_Maker(Shape0, Shape1, Pos0, Pos1, Verts, Dir))
			return true;
	}
	return false;
}

bool GJK::EPA_GJK(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D& DistVect, double& Pen)
{
	std::vector<Vec3D> Verts;
	Vec3D Dir;
	Simplex_Maker(Shape0, Shape1, Verts, Dir);
	Verts.push_back(EPA_Support(Shape0, Shape1, Dir));
	Simplex_Maker(Shape0, Shape1, Verts, Dir);
	bool Col = false;
	Vec3D Zed(0.0);
	for (int ii = 0; ii < 20; ii++)
	{
		Vec3D A = EPA_Support(Shape0, Shape1, Dir);
		if ((A * Dir) <= 0.f)
			break;
		if (std::find(Verts.begin(), Verts.end(), A) != Verts.end())
			break;
		Verts.push_back(A);
		Col = Simplex_Maker(Shape0, Shape1, Verts, Dir);
		if (Col)
			break;
	}

	if (Col)
	{
		DistVect = EPA(Verts, Shape0, Shape1, Pen);
		DistVect.Multiply(-1.0);
	}
	else
	{
		DistVect = C_F_E(Shape0, Shape1);
		Pen = DistVect.length();
	}
	if (DistVect != Vec3D(0.0))
		DistVect = DistVect.SetNormalize();
	return Col;
}
