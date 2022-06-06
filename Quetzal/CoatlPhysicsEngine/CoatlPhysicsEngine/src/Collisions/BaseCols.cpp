#include "BaseCols.h"
using namespace CoatlPhysicsEngine;

bool BaseCols::UpdateBodies(S_P<Sphere> Sph0, S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{	
	if (S_P<Sphere> Sphere0 = std::dynamic_pointer_cast<Sphere>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Sph0, Sphere0,
			Bod0->GetPos(),Bod0->GetQuat(),
			Bod1->GetPos(), Bod1->GetQuat());
	}
	else if (S_P<Capsule> Cap = std::dynamic_pointer_cast<Capsule>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Sph0, Cap,Bod0->GetPos(),Bod0->GetQuat(), Bod1->GetPos(), Bod1->GetQuat());
	}
	return GJK_Alg::GJK(Bod1,Bod0);
}

bool BaseCols::UpdateBodies(S_P<Capsule> Cap0, S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	if (S_P<Sphere> Sphere0 = std::dynamic_pointer_cast<Sphere>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Cap0, Sphere0,Bod0->GetPos(),Bod0->GetQuat(), Bod1->GetPos(), Bod1->GetQuat());
	}
	else if (S_P<Capsule> Cap = std::dynamic_pointer_cast<Capsule>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Cap0, Cap,Bod0->GetPos(),Bod0->GetQuat(), Bod1->GetPos(), Bod1->GetQuat());
	}
	return GJK_Alg::GJK(Bod1,Bod0);
}

bool BaseCols::ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	return GJK_Alg::GJK(Bod0, Bod1);
}

bool BaseCols::ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1,
	Vec<glm::vec3> Seg0, Vec<glm::vec3> Seg1)
{
	return GJK_Alg::GJK(Bod0, Bod1, Seg0, Seg1);
}

BaseCols::BaseCols(std::string Name)
{
	this->Name = Name;
}

BaseCols::~BaseCols()
{
}

Vec_SH<Contact> CoatlPhysicsEngine::BaseCols::GetColRel()
{
	return this->ColRel;
}

Vec_SH<Collection> BaseCols::GetCollections()
{
	return this->AllCollections;
}
