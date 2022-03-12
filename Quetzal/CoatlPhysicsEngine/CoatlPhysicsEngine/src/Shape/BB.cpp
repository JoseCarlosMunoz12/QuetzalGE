#include "BB.h"
using namespace CoatlPhysicsEngine;
BB::BB(Vec3D initDimen, Vec3D initPos, Quat initRot)
	:Shape(initPos, initRot), Dimensions(initDimen)
{
}

BB::~BB()
{
}

Vec3D BB::GetDimensions()
{
	return this->Dimensions;
}

void BB::SetDimensions(Vec3D newDimen)
{
	this->Dimensions = newDimen;
}

Vec3D BB::GetClosestPoint(Vec3D pnt)
{
	std::vector<Vec3D> Segs = this->GetVertices();
	Vec3D clstPnt;
	std::vector<int> Ind = { 0,1,1,2,2,3,3,0,
		4,5,5,6,6,7,7,4,
		0,4,1,5,2,6,3,7 };
	double Min;
	int Count = 0;
	for (int jj = 0; jj < 6; jj++)
	{
		int Val = jj * 2;
		Vec3D t = MATH::ClosestPoint_Seg({ Segs[Ind[Val]], Segs[Ind[Val + 1]]}, pnt);
		double temp = t.length();
		if (Count > 0)
		{
			if (Min > temp)
			{
				Min = temp;
				clstPnt = t;
			}
		}
		else
		{
			Min = temp;
			clstPnt = temp;
		}
		Count++;
	}
	return clstPnt;
}

void BB::DisplayInfo()
{
	std::cout << "Bounding Box information:\n";
	printf("X:%.5f Y:%.5f Z:%.5f\n", this->Dimensions[0], this->Dimensions[1], this->Dimensions[2]);
	this->DisplayInternals();
}

std::string BB::GetStr()
{
	std::string str = "Bounding Box Information\n";
	str += "X:" + std::to_string(this->Dimensions[0]) + "\n";
	str += "Y:" + std::to_string(this->Dimensions[1]) + "\n";
	str += "Z:" + std::to_string(this->Dimensions[2]) + "\n";
	str += this->GetInternals();
	return str;
}

std::vector<Vec3D> BB::GetVertices()
{
	Matrix4x4 R(this->Rotation);
	Matrix4x4 T;
	T[0][3] = this->Position[0]; T[1][3] = this->Position[1]; T[2][3] = this->Position[2];
	Vec3D Positions[] =
	{
		//Bottom Plane
		Vec3D(Dimensions[0],-Dimensions[1], -Dimensions[2]), Vec3D(Dimensions[0], Dimensions[1], -Dimensions[2]),
		Vec3D(-Dimensions[0], Dimensions[1],-Dimensions[2]), Vec3D(-Dimensions[0],-Dimensions[1],-Dimensions[2]),
		//Top Plane 
		Vec3D(Dimensions[0],-Dimensions[1], Dimensions[2]),  Vec3D(Dimensions[0], Dimensions[1], Dimensions[2]),
		Vec3D(-Dimensions[0], Dimensions[1], Dimensions[2]), Vec3D(-Dimensions[0],-Dimensions[1], Dimensions[2])
	};
	std::vector<Vec3D> Lines(std::begin(Positions), std::end(Positions));
	for (auto& jj : Lines)
	{
		Vec4D Set = Vec4D(jj, 1.f);
		Vec4D Res = T * Set;
		Res = R * Res;
		jj = Res.GetVec3();
	}
	return Lines;
}

std::vector<Vec3D> BB::GetNormals()
{
	std::vector<Vec3D> T = this->GetVertices();
	std::vector<Vec3D> OBB_N = { MATH::CreateNormal({T[1],T[0]}),
		 MATH::CreateNormal({T[3],T[0]}),
		 MATH::CreateNormal({T[4],T[0]}) };
	return OBB_N;
}

Vec3D BB::Support(Vec3D dir)
{

	std::vector<Vec3D> Pnts = this->GetVertices();
	double S = Pnts[0] * dir;
	Vec3D MaxPnt = Pnts[0];
	int Size = Pnts.size();
	for (int ii = 1; ii < Size; ii++)
	{
		double T = Pnts[ii] * dir;
		if (T > S)
		{
			S = T;
			MaxPnt = Pnts[ii];
		}
	}
	return MaxPnt;
}

Vec3D BB::EPA_Support(Vec3D dir)
{
	return this->Support(dir);
}
