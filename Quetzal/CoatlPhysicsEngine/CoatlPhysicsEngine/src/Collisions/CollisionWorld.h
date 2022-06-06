#pragma once
#include <string>
#include <vector>
#include "DynamicCollisions.h"
#include "StaticCollisions.h"
#include "KinematicsCollisions.h"
#include "../CollisionManager/CollisionManager.h"
namespace CoatlPhysicsEngine {
	COATL_API struct CollisionWorldSetup
	{
		std::string Name;
		glm::vec3 Gravity = glm::vec3(0.f, 0.f, -9.81);
	};
	class COATL_API CollisionWorld
	{
	private:
		glm::vec3 Gravity;
		S_P<StaticCollisions> Statics;
		S_P<KinematicsCollisions> Kin;
		S_P<DynamicCollisions> Dynamics;
		std::string WorldName;
		bool CheckStatics = false;
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