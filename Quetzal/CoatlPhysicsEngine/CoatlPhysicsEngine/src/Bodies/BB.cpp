#include "BB.h"
using namespace CoatlPhysicsEngine;
BB::BB(Vec3D initDimen, Vec3D initPos, Quat initRot)
	:Body(initPos, initRot), Dimensions(initDimen)
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
