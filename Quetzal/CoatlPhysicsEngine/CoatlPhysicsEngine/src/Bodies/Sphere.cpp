#include "Sphere.h"

using namespace CoatlPhysicsEngine;

Sphere::Sphere(double initRadius, Vec3D initPos, Quat initRot)
	:Body(initPos, initRot), Radius(initRadius)
{
}

double Sphere::GetRadius()
{
	return this->Radius;
}

void Sphere::SetRadius(double newRadius)
{
	this->Radius = newRadius;
}
