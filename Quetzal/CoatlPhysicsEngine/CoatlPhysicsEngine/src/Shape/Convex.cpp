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
}

std::string Convex::GetStr()
{
	return std::string();
}

std::vector<Vec3D> Convex::GetVertices()
{
	return std::vector<Vec3D>();
}

std::vector<Vec3D> Convex::GetNormals()
{
	return std::vector<Vec3D>();
}

Vec3D Convex::Support(Vec3D dir)
{
	return Vec3D();
}

Vec3D Convex::EPA_Support(Vec3D dir)
{
	return Vec3D();
}
