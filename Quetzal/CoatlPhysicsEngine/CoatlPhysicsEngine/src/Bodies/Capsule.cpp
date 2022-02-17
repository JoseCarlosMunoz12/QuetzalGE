#include "Capsule.h"
using namespace CoatlPhysicsEngine;

Capsule::Capsule(double initRadius, Vec3D initSeg0, Vec3D initSeg1, Vec3D initPos, Quat initRot)
	:Body(initPos, initRot), Seg0(initSeg0), Seg1(initSeg1), Radius(initRadius)
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
