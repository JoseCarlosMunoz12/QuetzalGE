#include "CollisionWorld.h"

using namespace CoatlPhysicsEngine;

void CollisionWorld::ResolveContacts()
{

}

void CollisionWorld::StepCollisionCheck(float dt)
{
	// Update Bodies
	if (this->Kin)
		this->Kin->UpdateBodies(dt);
	if (this->Dynamics)
		this->Dynamics->UpdateBodies(dt);
	//Detect Collision
	if (this->Dynamics)
	{
		auto bods = this->Dynamics->GetAllBods();
		for (auto jj : bods)
		{
			if (this->Statics)
			{
				auto sBods = this->Statics->GetBods(jj);
				for (auto kk : sBods)
					this->ColBods(jj, kk);
			}

			if (this->Kin)
			{
				auto kBods = this->Kin->GetBods(jj);

			}
		}

		for (auto iter0 = bods.begin(); iter0 != bods.end(); iter0++)
		{
			for (auto iter1 = iter0 + 1; iter1 != bods.end(); iter1++)
			{
				if (this->ColBods(*iter0, *iter1))
				{

				}
			}
		}
	}

}

void CollisionWorld::ContinousCollisionCheck(float)
{

}

CollisionWorld::CollisionWorld(std::string SetWName)
	:WorldName(SetWName),Gravity(0.f,0.f,-9.81f), IsStep(true),
	WorldCollisionHandler()
{
}

CollisionWorld::CollisionWorld(CollisionWorldSetup SetUp)
	:WorldName(SetUp.Name),Gravity(SetUp.Gravity), IsStep(SetUp.IsStep),
	WorldCollisionHandler()
{
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
		this->Statics = std::make_shared<StaticCollisions>(Name);
}

void CollisionWorld::CreateDynamicCol(std::string Name)
{
	if (!Dynamics)
		this->Dynamics = std::make_shared<DynamicCollisions>(Name);
}

void CollisionWorld::CreateKinCol(std::string Name)
{
	if (!this->Kin)
		this->Kin = std::make_shared<KinematicsCollisions>(Name);
}

S_P<StaticCollisions> CollisionWorld::GetCollision()
{
	if (this->Statics)
		return this->Statics;
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
	//Does Physics Maths and Dynamic Collisions
	if (IsStep)
		this->StepCollisionCheck(dt);
	else
		this->ContinousCollisionCheck(dt);
	//Solves All Collision Resolution
	this->ResolveContacts();
}
