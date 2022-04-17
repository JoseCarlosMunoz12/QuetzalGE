#include "World.h"
using namespace CoatlPhysicsEngine;

World::World()
{
	this->Col = std::make_shared<CollisionManager>();
}

World::~World()
{
}

void World::UpdateRun(double dt)
{
}

void World::SetGravity(Vec3D initGrav)
{
	this->Gravity = initGrav;
}

void World::CreateAllWorlds()
{
	this->CreateStaticWorld();
	this->CreateKinematicWorld();
	this->CreateDynamicWorld();
}

void World::CreateStaticWorld()
{
	if (!StaticWorld)
		this->StaticWorld = std::make_shared<StaticCollisions>();
}

void World::CreateKinematicWorld()
{
	if (!this->KinWorld)
		this->KinWorld = std::make_shared<KinematicCollisions>();
}

void World::CreateDynamicWorld()
{
	if (!this->DynWorld)
		this->DynWorld = std::make_shared<DynamicCollisions>();
}

void World::DeleteStatic()
{
	this->StaticWorld.reset();
}

void World::DeleteKinematic()
{
	this->KinWorld.reset();
}

void World::DeleteDynamic()
{
	this->DynWorld.reset();
}

void World::DeleteAllWorlds()
{
	this->DeleteStatic();
	this->DeleteKinematic();
	this->DeleteDynamic();
}

S_P<StaticCollisions> World::GetStaticWorld()
{
	return this->StaticWorld;
}

S_P<KinematicCollisions> World::GetKinematicWorld()
{
	return this->KinWorld;
}

S_P<DynamicCollisions> World::GetDynamicWorld()
{
	return this->DynWorld;
}
