#include "DynamicCollisions.h"

using namespace CoatlPhysicsEngine;

DynamicCollisions::DynamicCollisions()
{
	this->ColMan = std::make_shared<CollisionManager>();
	this->AlgoType = Alg_Type::B_F;
}

void DynamicCollisions::UpdateBodies(S_P<KinematicCollisions> Kin, S_P<StaticCollisions> Static, double dt)
{
}
