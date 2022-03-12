#include "Shape.h"
using namespace CoatlPhysicsEngine;

void Shape::DisplayInternals()
{
	std::cout << "-Position: ";
	this->Position.Display();
	std::cout << "-Rotation: ";
	this->Rotation.Display();
	std::cout << "-Velocity: ";
	this->Velocity.Display();
	std::cout << "-Angular Velocity: ";
	this->AngularVelocity.Display();
	std::cout << "Mass: ";
	if (this->MassInv == 0.0)
		std::cout << "Infinite Mass\n";
	else
	{
		double mass = 1 / MassInv;
		printf("%.5f\n", mass);
	}	
	std::cout << "Interntia Matrix:";
	this->InertiaInv.GetInverse().DisplayMatrix();
}

std::string Shape::GetInternals()
{
	std::string str = "Position: ";
	str += this->Position.GetStr();
	str += "Rotation :";
	str += this->Rotation.GetStr();
	str += "Velocity :";
	str += this->Velocity.GetStr();
	str += "Angular Velocity";
	str += this->AngularVelocity.GetStr();
	str += "Mass: ";
	if (this->MassInv == 0.0)
		std::cout << "Infinite Mass\n";
	else
	{
		double mass = 1 / MassInv;
		str += std::to_string(mass) + "\n";
	}
	str += "Interntia Matrix:\n";
	str += this->InertiaInv.GetInverse().GetStr();
	return str;
}

Shape::Shape(double initMass, Matrix3x3 initIntert,
	Vec3D initPos, Quat initRot)
{
	this->SetInertia(initIntert);
	this->SetMass(initMass);
	this->SetVelocity(Vec3D(0.0));
	this->SetAngularVelocity(Vec3D(0.0));
	this->SetPosition(initPos);
	this->SetRotation(initRot);
}

Shape::Shape(Vec3D initPos, Quat initRot)
{
	this->SetMassInfinite();
	this->SetIntertiaInfinite();
	this->SetVelocity(Vec3D(0.0));
	this->SetAngularVelocity(Vec3D(0.0));
	this->SetPosition(initPos);
	this->SetRotation(initRot);
}

Shape::~Shape()
{
}

double Shape::GetInvMass()
{
	return this->MassInv;
}

void Shape::SetMass(double newMass)
{
	this->MassInv = 1.0 / newMass;
}

void Shape::SetMassInfinite()
{
	this->MassInv = 0.0;
}

Matrix3x3 Shape::GetInvInertia()
{
	return this->InertiaInv;
}

void Shape::SetInertia(Matrix3x3 newInertia)
{
	this->InertiaInv = newInertia;
}

void Shape::SetIntertiaInfinite()
{
	this->InertiaInv = Matrix3x3();

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

Vec3D Shape::GetVelocity()
{
	return this->Velocity;
}

void Shape::SetVelocity(Vec3D newVel)
{
	this->Velocity = newVel;
}

Vec3D Shape::GetAngularVelocity()
{
	return this->AngularVelocity;
}

void Shape::SetAngularVelocity(Vec3D newVel)
{
	this->AngularVelocity = newVel;
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
