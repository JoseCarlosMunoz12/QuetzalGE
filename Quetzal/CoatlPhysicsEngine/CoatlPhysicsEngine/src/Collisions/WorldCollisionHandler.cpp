#include "WorldCollisionHandler.h"
using namespace CoatlPhysicsEngine;

bool WorldCollisionHandler::UpdateBodies(S_P<Sphere> Sph0, S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	if (S_P<Sphere> Sphere0 = std::dynamic_pointer_cast<Sphere>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Sph0, Sphere0,
			Bod0->GetPos(), Bod0->GetQuat(),
			Bod1->GetPos(), Bod1->GetQuat());
	}
	else if (S_P<Capsule> Cap = std::dynamic_pointer_cast<Capsule>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Sph0, Cap, Bod0->GetPos(), Bod0->GetQuat(), Bod1->GetPos(), Bod1->GetQuat());
	}
	return GJK_Alg::GJK(Bod1, Bod0);
}

bool WorldCollisionHandler::UpdateBodies(S_P<Capsule> Cap0, S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	if (S_P<Sphere> Sphere0 = std::dynamic_pointer_cast<Sphere>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Cap0, Sphere0, Bod0->GetPos(), Bod0->GetQuat(), Bod1->GetPos(), Bod1->GetQuat());
	}
	else if (S_P<Capsule> Cap = std::dynamic_pointer_cast<Capsule>(Bod1->GetShapes()))
	{
		return CollisionManager::CheckCollide(Cap0, Cap, Bod0->GetPos(), Bod0->GetQuat(), Bod1->GetPos(), Bod1->GetQuat());
	}
	return GJK_Alg::GJK(Bod1, Bod0);
}

bool WorldCollisionHandler::ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1)
{
	return GJK_Alg::GJK(Bod0, Bod1);
}

bool WorldCollisionHandler::ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1, Vec<glm::vec3> Seg0, Vec<glm::vec3> Seg1)
{
	return GJK_Alg::GJK(Bod0, Bod1, Seg0, Seg1);
}

bool WorldCollisionHandler::BinColDetection(S_P<Bodies> Bod0, S_P<Bodies> Bod1, glm::vec3 Vel0, glm::vec3 Vel1, float t0, float t1, float& NewDt)
{
	if ((t1 - t0) < EPSILON)
	{
		NewDt = t1;
		return true;
	}
	float Mid = t0 + (t1 - t0) / 2.f;
	if (!this->ColBods(Bod0, Bod1, { Vel0 * t0, Vel0 * t1 }, { Vel1 * t0, Vel1 * t1 }))
	{
		return false;
	}
	if (BinColDetection(Bod0, Bod1, Vel0, Vel1, t0, Mid, NewDt))
	{
		return true;
	}
	return BinColDetection(Bod0, Bod1, Vel0, Vel1, Mid, t1, NewDt);
}

bool WorldCollisionHandler::StepCollision(S_P<Bodies> Bod0, S_P<Bodies> Bod1, float t0)
{
	return false;
}
