#include "ContactCreation.h"
using namespace CoatlPhysicsEngine;

std::vector<S_P<Contact>> ContactCreation::ContactCreate(S_P<Sphere> Sph0, S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	std::vector<S_P<Contact>> Temp;
	return Temp;
}

std::vector<S_P<Contact>> ContactCreation::ContactCreate(S_P<Capsule> Cap, S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	std::vector<S_P<Contact>> Temp;
	return Temp;
}

std::vector<S_P<Contact>> ContactCreation::ContactCreate(S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	std::vector<S_P<Contact>> Temp;
	return Temp;
}

std::vector<S_P<Contact>> ContactCreation::MakeContacts(S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	if (S_P<Sphere> Sphere0 = std::dynamic_pointer_cast<Sphere>(Bod0->GetShapes()))
	{
		return ContactCreate(Sphere0, Bod0, Bod1);
	}
	else if (S_P<Capsule> Cap0 = std::dynamic_pointer_cast<Capsule>(Bod0->GetShapes()))
	{
		return ContactCreate(Cap0, Bod0, Bod1);
	}
	return ContactCreate(Bod0, Bod1);
}

float ContactCreation::GetLowestFric(S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	if (!Bod1->GetParticle())
		return Bod0->GetParticle()->GetFriction();
	float Fric[2] = { Bod0->GetParticle()->GetFriction(),Bod1->GetParticle()->GetFriction() };
	return (Fric[0] < Fric[1] ? Fric[0] : Fric[1]);
}

float ContactCreation::GetLowestRest(S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	if (!Bod1->GetParticle())
		return Bod0->GetParticle()->GetRestitution();
	float Rest[2] = { Bod0->GetParticle()->GetRestitution(),Bod1->GetParticle()->GetRestitution() };
	return (Rest[0] < Rest[1] ? Rest[0] : Rest[1]);
}

ContactCreation::ContactCreation()
{
}

ContactCreation::~ContactCreation()
{
}

std::vector<S_P<Contact>>ContactCreation::MakeManifold(S_P<Bodies> Bod0, S_P<Bodies> Bod1, float dt0, float dt1)
{
	float Fric = GetLowestFric(Bod0, Bod1);
	float Rest = GetLowestRest(Bod0, Bod1);
	std::vector<S_P<Contact>> T = MakeContacts(Bod0, Bod1);
	for (auto& ii : T)
	{
		ii->Friction = Fric;
		ii->Restitution = Rest;
		ii->dt0 = dt0;
		ii->dt1 = dt1;
	}
	return T;
}

void ContactCreation::MakeJointManifold(std::vector<S_P<Contact>>& R, std::vector<S_P<ColJoints>> BodJoints)
{
}
