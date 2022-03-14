#include "Capsule.h"
using namespace CoatlPhysicsEngine;

Capsule::Capsule(double initRadius, Vec3D initSeg0, Vec3D initSeg1, Vec3D initPos, Quat initRot)
	:Shape(initPos, initRot), Seg0(initSeg0), Seg1(initSeg1), Radius(initRadius)
{
}

void Capsule::SetRadius(double newRadius)
{
	this->Radius = newRadius;
}

double Capsule::GetRadius()
{
	return this->Radius;
}

void Capsule::GetSegment(Vec3D& outSeg0, Vec3D outSeg1)
{
	outSeg0 = this->Seg0;
	outSeg1 = this->Seg1;
}

void Capsule::SetSegment(Vec3D newSeg0, Vec3D newSeg1)
{
	this->Seg0 = newSeg0;
	this->Seg1 = newSeg0;
}

double Capsule::GetLength()
{
	return MATH::Distance(this->Seg0, this->Seg1);
}

void Capsule::DisplayInfo()
{
	std::cout << "Capsule Information:\n";
	printf("Radius : %.5f", this->Radius);
	printf("Segment 0 X:%.5f Y:%.5f Z:%.5f\n", this->Seg0[0], this->Seg0[1], this->Seg0[2]);
	printf("Segment 1 X:%.5f Y:%.5f Z:%.5f\n", this->Seg1[0], this->Seg1[1], this->Seg1[2]);
	this->DisplayInternals();
}

std::string Capsule::GetStr()
{
	std::string str = "Capsule Information:\n";
	str += "Radius: " + std::to_string(this->Radius) + "\n";
	str += "Segment 0 " + this->Seg0.GetStr();
	str += "Segment 1 " + this->Seg1.GetStr();
	str += this->GetInternals();
	return str;
}

std::vector<Vec3D> Capsule::GetVertices()
{
	Matrix3x3 R(this->Rotation);
	Vec3D S0 = R * (this->Position + this->Seg0);
	Vec3D S1 = R * (this->Position + this->Seg1);
	return {S0, S1};
}

std::vector<Vec3D> Capsule::GetNormals()
{
	std::vector<Vec3D> Pnts = this->GetVertices();
	Vec3D Norm = Pnts[1] - Pnts[0];
	Norm.Normalize();
	return { Norm };
}

Vec3D Capsule::Support(Vec3D dir)
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
	dir.Multiply(this->Radius);
	return MaxPnt + dir;
}

Vec3D Capsule::EPA_Support(Vec3D dir)
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
