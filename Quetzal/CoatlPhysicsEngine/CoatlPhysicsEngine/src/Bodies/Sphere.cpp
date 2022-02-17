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

void Sphere::DisplayInfo()
{
	std::cout << "Sphere Information:\n";
	printf("Radius: %.5f", this->Radius);
	this->DisplayInternals();
}

std::string Sphere::GetStr()
{
	std::string str =  "Sphere Information:\n";
	str += "Radius: " + std::to_string(this->Radius) + "\n";
	str += this->GetInternals();
	return str;
}
