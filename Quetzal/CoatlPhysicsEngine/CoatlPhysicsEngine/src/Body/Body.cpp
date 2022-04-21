#include "Body.h"

Body::Body(S_P<Shape> initShape, double initMass, Matrix3x3 initInert)
	:_Shape(initShape), MassInv(initMass), InertiaInv(initInert)
{
}

void Body::DisplayInternals()
{
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
	std::string str = "Velocity :";
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

void Body::DisplayInfo()
{
	this->_Shape->DisplayInfo();
	this->DisplayInternals();
}

std::string Body::GetStr()
{
	std::string str = this->_Shape->GetStr();
	str += this->GetInternals();
	return str;
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

S_P<Shape> Body::GetShape()
{
	return this->_Shape;
}

void Body::Update(double dt)
{
	if (this->_Shape)
	{
		Vec3D curPos = this->_Shape->GetPosition();
		curPos = curPos + this->Velocity * dt;
		this->_Shape->SetPosition(curPos);
		Matrix4x3 S(this->_Shape->GetRotation());
		Quat S_i = S * this->AngularVelocity;
		S_i.Multiply(dt * 0.5);
		this->_Shape->SetRotation(S_i);
	}
}

int Body::GetID()
{
	return 0;
}
