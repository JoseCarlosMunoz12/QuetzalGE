#include "Body.h"
using namespace CoatlPhysicsEngine;

void Body::DisplayInternals()
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

std::string Body::GetInternals()
{
	std::string str = "Position: ";
	str += this->Position.GetStr();
	str += "Rotation :";
	return str;
}

Body::Body(double initMass, Matrix3x3 initIntert,
	Vec3D initPos, Quat initRot)
{
	this->SetInertia(initIntert);
	this->SetMass(initMass);
	this->SetVelocity(Vec3D(0.0));
	this->SetAngularVelocity(Vec3D(0.0));
	this->SetPosition(initPos);
	this->SetRotation(initRot);
}

Body::Body(Vec3D initPos, Quat initRot)
{
	this->SetMassInfinite();
	this->SetIntertiaInfinite();
	this->SetVelocity(Vec3D(0.0));
	this->SetAngularVelocity(Vec3D(0.0));
	this->SetPosition(initPos);
	this->SetRotation(initRot);
}

Body::~Body()
{
}

double Body::GetInvMass()
{
	return this->MassInv;
}

void Body::SetMass(double newMass)
{
	this->MassInv = 1.0 / newMass;
}

void Body::SetMassInfinite()
{
	this->MassInv = 0.0;
}

Matrix3x3 Body::GetInvInertia()
{
	return this->InertiaInv;
}

void Body::SetInertia(Matrix3x3 newInertia)
{
	this->InertiaInv = newInertia;
}

void Body::SetIntertiaInfinite()
{
	this->InertiaInv = Matrix3x3();

}

Vec3D Body::GetPosition()
{
	return this->Position;
}

void Body::SetPosition(Vec3D newPos)
{
	this->Position = newPos;
}

Quat Body::GetRotation()
{
	return Rotation;
}

void Body::SetRotation(Quat newRot)
{
	this->Rotation = newRot;
}

Vec3D Body::GetVelocity()
{
	return this->Velocity;
}

void Body::SetVelocity(Vec3D newVel)
{
	this->Velocity = newVel;
}

Vec3D Body::GetAngularVelocity()
{
	return this->AngularVelocity;
}

void Body::SetAngularVelocity(Vec3D newVel)
{
	this->AngularVelocity = newVel;
}

void Body::DisplayInfo()
{
	std::cout << "empty\n";
}
