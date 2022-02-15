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
