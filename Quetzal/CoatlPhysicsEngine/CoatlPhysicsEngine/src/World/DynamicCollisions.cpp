#include "DynamicCollisions.h"

using namespace CoatlPhysicsEngine;

bool DynamicCollisions::BinaryCollisionDetection(S_P<Body> Bod0, S_P<Body> Bod1, double t0, double t1, double& newDt)
{
	if ((t1 - t0) < EPSILON)
	{
		newDt = t1;
		return true;
	}
	double mid = t0 + (t1 - t0) / 2.0;
	if (!this->ColMan->CheckCollide(Bod0->GetShape(), Bod1->GetShape()))
	{
		return false;
	}
	return false;
}

DynamicCollisions::DynamicCollisions()
{
	this->ColMan = std::make_shared<CollisionManager>();
	this->AlgoType = Alg_Type::B_F;
}

void DynamicCollisions::UpdateBodies(S_P<KinematicCollisions> Kin, S_P<StaticCollisions> Static, double dt)
{
	//remake the 
	this->SetupAlgo();

	for (auto& jj : GetAllBodies())
	{
		if (Static)
		{
			Vec_SH<Body> Que = Static->GetBodies(jj);
			for (auto& ii : Que)
			{

			}
		}
	}
}
