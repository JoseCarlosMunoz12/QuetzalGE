#include "ContactCreation.h"
using namespace CoatlPhysicsEngine;

std::vector<std::shared_ptr<Contact>> ContactCreation::ContactCreate(Sphere Sph0, std::shared_ptr<Bodies> Bod0, std::shared_ptr<Bodies> Bod1)
{
	std::vector<std::shared_ptr<Contact>> Temp;
	return Temp;
}

std::vector<std::shared_ptr<Contact>> ContactCreation::ContactCreate(Capsule Cap, std::shared_ptr<Bodies> Bod0, std::shared_ptr<Bodies> Bod1)
{
	std::vector<std::shared_ptr<Contact>> Temp;
	return Temp;
}

std::vector<std::shared_ptr<Contact>> ContactCreation::ContactCreate(std::shared_ptr<Bodies> Bod0, std::shared_ptr<Bodies> Bod1)
{
	std::vector<std::shared_ptr<Contact>> Temp;
	return Temp;
}

std::vector<std::shared_ptr<Contact>> ContactCreation::MakeContacts(std::shared_ptr<Bodies> Bod0, std::shared_ptr<Bodies> Bod1)
{
	if (std::shared_ptr<Sphere> Sphere0 = std::dynamic_pointer_cast<Sphere>(Bod0->GetShapes()))
	{
		return ContactCreate(*Sphere0, Bod0, Bod1);
	}
	else if (std::shared_ptr<Capsule> Cap0 = std::dynamic_pointer_cast<Capsule>(Bod0->GetShapes()))
	{
		return ContactCreate(*Cap0, Bod0, Bod1);
	}
	return ContactCreate(Bod0, Bod1);
}

float ContactCreation::GetLowestFric(std::shared_ptr<Bodies> Bod0, std::shared_ptr<Bodies> Bod1)
{
	if (!Bod1->GetParticle())
		return Bod0->GetParticle()->GetFriction();
	float Fric[2] = { Bod0->GetParticle()->GetFriction(),Bod1->GetParticle()->GetFriction() };
	return (Fric[0] < Fric[1] ? Fric[0] : Fric[1]);
}

float ContactCreation::GetLowestRest(std::shared_ptr<Bodies> Bod0, std::shared_ptr<Bodies> Bod1)
{
	if (!Bod1->GetParticle())
		return Bod0->GetParticle()->GetRestitution();
	float Rest[2] = { Bod0->GetParticle()->GetRestitution(),Bod1->GetParticle()->GetRestitution() };
	return (Rest[0] < Rest[1] ? Rest[0] : Rest[1]);
}

ContactCreation::ContactCreation()
{
	SAT_ = std::make_unique<SAT>();
}

ContactCreation::~ContactCreation()
{
}

std::vector<std::shared_ptr<Contact>>ContactCreation::MakeManifold(std::shared_ptr<Bodies> Bod0, std::shared_ptr<Bodies> Bod1, float dt0, float dt1)
{
	float Fric = GetLowestFric(Bod0, Bod1);
	float Rest = GetLowestRest(Bod0, Bod1);
	std::vector<std::shared_ptr<Contact>> T = MakeContacts(Bod0, Bod1);
	for (auto& ii : T)
	{
		ii->Friction = Fric;
		ii->Restituion = Rest;
		ii->dt0 = dt0;
		ii->dt1 = dt1;
	}
	return T;
}

void ContactCreation::MakeJointManifold(std::vector<std::shared_ptr<Contact>>& R, std::vector<std::shared_ptr<ColJoints>> BodJoints)
{
}