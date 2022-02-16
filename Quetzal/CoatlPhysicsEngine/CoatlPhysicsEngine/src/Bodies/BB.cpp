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
