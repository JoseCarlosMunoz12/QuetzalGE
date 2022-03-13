#include "Convex.h"
using namespace CoatlPhysicsEngine;

Convex::Convex(std::vector<Vec3D> initPnts, Vec3D initPos, Quat initRot)
	:Shape(initPos,initRot)
{
	this->Pnts = initPnts;
}

Convex::~Convex()
{
}

void Convex::DisplayInfo()
{
	std::cout << "Shape Information Information:\n";
	int size = this->Pnts.size();
	printf("Number of Points : %d", size);
	this->DisplayInternals();
}

std::string Convex::GetStr()
{
	std::string str = "Capsule Information:\n";
	int size = this->Pnts.size();
	str += "Number of Points: " + std::to_string(size) + "\n";
	str += this->GetInternals();
	return str;
}

std::vector<Vec3D> Convex::GetVertices()
{
	return this->Pnts;
}

std::vector<Vec3D> Convex::GetNormals()
{
	return std::vector<Vec3D>();
}

Vec3D Convex::Support(Vec3D dir)
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

Vec3D Convex::EPA_Support(Vec3D dir)
{
	return Vec3D();
}
