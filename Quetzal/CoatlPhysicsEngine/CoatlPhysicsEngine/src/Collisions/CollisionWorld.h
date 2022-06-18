#pragma once
#include <string>
#include <vector>
#include "DynamicCollisions.h"
#include "StaticCollisions.h"
#include "KinematicsCollisions.h"
#include "../CollisionManager/CollisionManager.h"
#include "WorldCollisionHandler.h"

namespace CoatlPhysicsEngine {
	COATL_API struct CollisionWorldSetup
	{
		std::string Name;
		glm::vec3 Gravity = glm::vec3(0.f, 0.f, -9.81);
		bool IsStep;
	};
	class COATL_API CollisionWorld : public WorldCollisionHandler
	{
	private:
		glm::vec3 Gravity;
		S_P<StaticCollisions> Statics;
		S_P<KinematicsCollisions> Kin;
		S_P<DynamicCollisions> Dynamics;
		Vec_SH<Contact> AllContacts;
		std::string WorldName;
		bool CheckStatics = false;
		bool IsStep;
		void ResolveContacts();
		void StepCollisionCheck(float dt);
		void ContinousCollisionCheck(float dt);
	public:
		CollisionWorld(std::string SetWName);
		CollisionWorld(CollisionWorldSetup SetUp);
		~CollisionWorld();
		std::string ShowName();
		glm::vec3 GetGravity();
		void ChangeName(std::string NewName);
		void CreateStaticCol(std::string Name);
		void CreateDynamicCol(std::string Name);
		void CreateKinCol(std::string Name);
		S_P<StaticCollisions> GetCollision();
		S_P<DynamicCollisions> GetDynCol();
		S_P<KinematicsCollisions> GetKinCol();
		void DeleteStatics();
		void DeleteDynamics();
		void DeleteKinematics();
		void UpdateWorld(float dt);
	};
}