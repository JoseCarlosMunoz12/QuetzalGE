#include "World.h"
using namespace CoatlPhysicsEngine;

World::World()
{
}

 World::~World()
{
}

void World::UpdateRun(double dt)
{
}

void  World::SetGravity(Vec3D initGrav)
{
}

void  World::CreateStaticWorld()
{
}

void  World::CreateKinematicWorld()
{
}

void  World::DynamicWorld()
{
}

void  World::DeleteStatic()
{
}

void  World::DeleteKinematic()
{
}

void  World::DeleteDynamic()
{
}

S_P<StaticCollisions>  World::GetStaticWorld()
{
	return this->StaticWorld;
}

S_P<KinematicCollisions>  World::GetKinematicWorld()
{
	return this->KinWorld;
}

S_P<DynamicCollisions>  World::GetDynamicWorld()
{
	return this->DynWorld;
}
