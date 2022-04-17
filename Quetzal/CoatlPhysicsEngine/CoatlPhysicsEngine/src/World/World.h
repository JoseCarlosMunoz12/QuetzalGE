#pragma once
#include "../define.h"
#include "DynamicCollisions.h"
#include "../CollisionManager/CollisionManager.h"

namespace CoatlPhysicsEngine {
	class COATL_API World
	{
	private:
		S_P<CollisionManager> Col;
		Vec3D Gravity;
		S_P<StaticCollisions> StaticWorld;
		S_P<KinematicCollisions> KinWorld;
		S_P<DynamicCollisions> DynWorld;
	public:
		World();
		~World();
		void UpdateRun(double dt);
		void SetGravity(Vec3D initGrav);
		
		void CreateAllWorlds();

		void CreateStaticWorld();
		void CreateKinematicWorld();
		void CreateDynamicWorld();

		void DeleteStatic();
		void DeleteKinematic();
		void DeleteDynamic();
		
		void DeleteAllWorlds();

		S_P<StaticCollisions> GetStaticWorld();
		S_P<KinematicCollisions> GetKinematicWorld();
		S_P<DynamicCollisions> GetDynamicWorld();
	};
}