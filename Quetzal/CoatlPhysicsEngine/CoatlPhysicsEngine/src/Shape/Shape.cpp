#include "Shape.h"
using namespace CoatlPhysicsEngine;

Shape::Shape(Vec3D initPos, Quat initRot)
{
	this->SetPosition(initPos);
	this->SetRotation(initRot);
}

Shape::~Shape()
{
}

Vec3D Shape::GetPosition()
{
	return this->Position;
}

void Shape::SetPosition(Vec3D newPos)
{
	this->Position = newPos;
}

Quat Shape::GetRotation()
{
	return Rotation;
}

void Shape::SetRotation(Quat newRot)
{
	this->Rotation = newRot;
}

void Shape::DisplayInfo()
{
	std::cout << "empty\n";
}

std::string Shape::GetStr()
{
	return "";
}

std::vector<Vec3D> Shape::GetNormals()
{
	return std::vector<Vec3D>();
}

std::vector<Vec3D> Shape::GetVertices()
{
	return std::vector<Vec3D>();
}

Vec3D Shape::Support(Vec3D Dir)
{
	return Vec3D();
}

Vec3D Shape::EPA_Support(Vec3D Dir)
{
	return Vec3D();
}
