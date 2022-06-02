#include "CollisionWorld.h"

using namespace CoatlPhysicsEngine;

CollisionWorld::CollisionWorld(std::string SetWName)
	:WorldName(SetWName),Gravity(glm::vec3(0.f,0.f,-9.81f))
{
	this->ColMan = std::make_shared<CollisionManager>();
}

CollisionWorld::CollisionWorld(CollisionWorldSetup SetUp)
	:WorldName(SetUp.Name),Gravity(SetUp.Gravity)
{
	this->ColMan = std::make_shared<CollisionManager>();
}

CollisionWorld::~CollisionWorld()
{
}

std::string CollisionWorld::ShowName()
{
	return this->WorldName;
}

glm::vec3 CollisionWorld::GetGravity()
{
	return this->Gravity;
}

void CollisionWorld::ChangeName(std::string NewName)
{
	this->WorldName = NewName;
}

void CollisionWorld::CreateStaticCol(std::string Name)
{
	if (!Statics)
	{
		this->Statics = std::make_shared<StaticCollisions>(Name);
	}
}

void CollisionWorld::CreateDynamicCol(std::string Name)
{
	if (!Dynamics)
	{
		this->Dynamics = std::make_shared<DynamicCollisions>(Name);
	}
}

void CollisionWorld::CreateKinCol(std::string Name)
{
	if (!this->Kin)
	{
		this->Kin = std::make_shared<KinematicsCollisions>(Name);
	}
}

S_P<StaticCollisions> CollisionWorld::GetCollision()
{
	if (this->Statics)
	{
		return this->Statics;
	}
	return NULL;
}

S_P<DynamicCollisions> CollisionWorld::GetDynCol()
{
	if (this->Dynamics)
		return this->Dynamics;
	return NULL;
}

S_P<KinematicsCollisions> CollisionWorld::GetKinCol()
{
	if (this->Kin)
		return this->Kin;
	return NULL;
}

void CollisionWorld::DeleteStatics()
{
	this->Statics.reset();
}

void CollisionWorld::DeleteDynamics()
{
	this->Dynamics.reset();
}

void CollisionWorld::DeleteKinematics()
{
	this->Kin.reset();
}

void CollisionWorld::UpdateWorld(float dt)
{
	//check where the Statics are if touching the Terrain
	if (this->Statics && CheckStatics)
		this->Statics->UpdateCollisionCheck();
	//moves Kinematic objects
	if (this->Kin)
		this->Kin->UpdateBodies(dt);
	//Does Physics Maths and Dynamic Collisions
	if (this->Dynamics)
		this->Dynamics->CheckCollision(this->Statics,this->Kin,dt);
}

void CollisionWorld::ToggleStaticCheck()
{
	this->CheckStatics = !this->CheckStatics;
}

bool CollisionWorld::StaticCheckStatus()
{
	return this->CheckStatics;
}
