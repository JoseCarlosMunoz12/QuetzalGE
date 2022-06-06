#include "Bodies.h"
using namespace CoatlPhysicsEngine;

Bodies::Bodies(int InitID)
	:Max(glm::vec3(0.f)), Min(glm::vec3(0.f)), Mid(glm::vec3(0.f))
{
	this->BodParticle = std::make_shared<RigidBodies>(glm::vec3(0.f));
	this->ID = InitID;
}

Bodies::Bodies(S_P<ColShapes> InitShapes, int InitID)
	:Max(glm::vec3(0.f)), Min(glm::vec3(0.f)), Mid(glm::vec3(0.f))
{
	this->ID = InitID;
	this->BodParticle = std::make_shared<RigidBodies>(glm::vec3(0.f));
	this->BodPart = InitShapes;
}

Bodies::~Bodies()
{
}

void Bodies::AddShapes(S_P<ColShapes> NewShape)
{
	this->BodPart = NewShape;
	if (this->BodParticle)
	{
		float mass = this->BodParticle->GetMass();
		glm::mat3 inertia = this->BodPart->GetInertia(mass);
		this->BodParticle->SetInertia(inertia);
	}
}

int Bodies::GetID()
{
	return this->ID;
}

void Bodies::SetPosition(glm::vec3 NewPos)
{
	this->BodParticle->SetPos(NewPos);
}

void Bodies::UpdateAABB()
{
	Max = this->Support(Units[0]);
	Min = this->Support(Units[3]);
	for (auto& jj : Units)
	{
		glm::vec3 T = this->Support(jj);
		Max = MATH::SetMax(Max, T);
		Min = MATH::SetMin(Min, T);
	}
	this->Mid = (Max + Min) / 2.f;
}

void Bodies::UpdatePos(float dt)
{
	this->BodParticle->UpdatePos(dt);
}

void Bodies::MovePosition(glm::vec3 Add)
{
	glm::vec3 OldPos = this->BodParticle->GetPos();
	OldPos += Add;
	this->SetPosition(OldPos);
}

void Bodies::SetParticle(int ShapeID)
{
	this->BodParticle = std::make_shared<Particle>(this->GetPos());
}

void Bodies::SetRigidBody(int ShapeID)
{
}

void Bodies::SetQuat(glm::quat NewQuat)
{
	this->BodParticle->SetQuat(NewQuat);
}

bool Bodies::HasCollided()
{
	return this->IsCollided;
}

glm::vec3 Bodies::GetPos()
{
	return this->BodParticle->GetPos();	
}

glm::quat Bodies::GetQuat()
{
	return this->BodParticle->GetQuat();
}

S_P<ColShapes> Bodies::GetShapes()
{
	return this->BodPart;
}


S_P<Bod_Base> Bodies::GetParticle()
{
	return this->BodParticle;
}

bool Bodies::IsValid()
{
	return this->BodPart && this->BodParticle;
}

glm::vec3 Bodies::Support(glm::vec3 Dir)
{
	if (!this->BodPart)
		return glm::vec3(0.f);
	return this->BodPart->Support(Dir, this->GetPos(), this->GetQuat());
}

glm::vec3 Bodies::EPA_Support(glm::vec3 Dir)
{
	if (!this->BodPart)
		return glm::vec3(0.f);
	return this->BodPart->EPA_Support(Dir, this->GetPos(), this->GetQuat());
}
